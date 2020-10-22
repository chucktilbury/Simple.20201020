/*
 * Hash table uses the
 *
 */
#define XXH_INLINE_ALL
#include "xxhash.h"
#include "../include/hash_table.h"
#include "../include/memory.h"
#include "../include/misc.h"
#include "../include/errors.h"

#define TABLE_MAX_LOAD 0.75

/*
 * Return the smaller of the two parameters.
 */
static inline size_t _min(size_t v1, size_t v2) { return (v1 < v2) ? v1 : v2; }

/*
 * This is a “FNV-1a” hash function. Do not mess with the constants.
 */
static uint32_t make_hash(const char* key)
{
    uint32_t hash = 2166136261u;

    for(int i = 0; i < (int)strlen(key); i++)
    {
        hash ^= key[i];
        hash *= 16777619;
    }

    return hash;
}

/*
 * If the entry is found, return the slot, if the entry is not found, then the
 * slot returned is where to put the entry. Check the slot's key to tell the
 * difference.
 */
static _table_entry_t* find_slot(_table_entry_t* ent, size_t cap, const char* key)
{
    uint32_t index = make_hash(key) & (cap - 1);

    while(1)
    {
        _table_entry_t* entry = &ent[index];

        // depends on left evaluate before right
        if((entry->key == NULL) || (!strcmp(key, entry->key)))
        {
#ifdef __TESTING_HASH_TABLE_C__
            if(entry->key != NULL)
                printf("found: index: %-2u key: %-12s value: %s\n", index, key, (char*)entry->data);
            else
                printf("insert: index: %-2u key: %-12s\n", index, key);
#endif
            return entry;
        }

        index = (index + 1) & (cap - 1);
    }
}

/*
 * Grow the table if it needs it. Since the hash values change when the table
 * size changes, this function simply re-adds them to the new table, then
 * updates the data structure.
 */
static void grow_table(hash_table_t* tab)
{
    if(tab->count + 2 > tab->capacity * TABLE_MAX_LOAD)
    {
#ifdef __TESTING_HASH_TABLE_C__
        printf("\ngrowing table\n");
        printf("  table capacity: %lu\n", tab->capacity);
        printf("  table count: %lu\n", tab->count);
#endif
        // table must always be an even power of 2 for this to work.
        size_t capacity = tab->capacity << 1;

        _table_entry_t* entries = (_table_entry_t*)CALLOC(capacity, sizeof(_table_entry_t));

        if(entries == NULL) fatal_error("cannot allocate %lu bytes for hash table", capacity * sizeof(_table_entry_t));

        // re-add the table entries to the new table.
        if(tab->entries != NULL)
        {
            for(int i = 0; i < (int)tab->capacity; i++)
            {
                if(tab->entries[i].key != NULL)
                {
                    _table_entry_t* ent = find_slot(entries, capacity, tab->entries[i].key);

                    // if the key is the same, (i.e. not NULL) the replace the data. There
                    // can be no duplicate entries. No need to check it.
                    ent->key = tab->entries[i].key;
                    ent->size = tab->entries[i].size;
                    ent->data = tab->entries[i].data;
                }
            }
            // free the old table
            free(tab->entries);
        }

        tab->entries = entries;
        tab->capacity = capacity;
#ifdef __TESTING_HASH_TABLE_C__
        printf("\nfinished growing table\n");
        printf("  table capacity: %lu\n", tab->capacity);
        printf("  table count: %lu\n", tab->count);
#endif
    }
}

hash_table_t* create_hash_table(void)
{
    hash_table_t* tab;

    tab = MALLOC(sizeof(hash_table_t));
    if(tab == NULL)
    {
        fatal_error("cannot allocate %lu bytes for hash table structure", sizeof(hash_table_t));
    }

    tab->capacity = 0x01 << 3;
    tab->entries = (_table_entry_t*)CALLOC(tab->capacity, sizeof(_table_entry_t));
    return tab;
}

void destroy_hash_table(hash_table_t* tab)
{
    if(tab != NULL)
    {
        if(tab->entries != NULL)
        {
            for(int i = 0; i < (int)tab->capacity; i++)
            {
                if(tab->entries[i].data != NULL)
                    FREE(tab->entries[i].data);
                if(tab->entries[i].key != NULL)
                    FREE((void*)tab->entries[i].key);
            }
            FREE(tab->entries);
        }
        FREE(tab);
    }
}

/*
 * Refuse to replace an entry.
 */
int insert_hash_table(hash_table_t* tab, const char* key, void* data, size_t size)
{
    grow_table(tab);

    _table_entry_t* entry = find_slot(tab->entries, tab->capacity, key);
    int retv = (entry->key == NULL) ? HASH_NO_ERROR : HASH_EXIST;

    if(retv == HASH_NO_ERROR) {
        entry->key = STRDUP(key);
        if(entry->key == NULL)
            fatal_error("cannot allocate %lu bytes for hash table key", strlen(key));

        entry->data = MALLOC(size);
        if(entry->data == NULL)
            fatal_error("cannot allocate %lu bytes for hash table data", size);

        memcpy(entry->data, data, size);
        entry->size = size;
        tab->count++;
    }

    return retv;
}

int find_hash_table(hash_table_t* tab, const char* key, void* data, size_t size)
{
    _table_entry_t* entry = find_slot(tab->entries, tab->capacity, key);
    int retv = HASH_NO_ERROR;

    if(entry->key != NULL)
    {
        if(entry->data != NULL)
        {
            //if(entry->size != size)
            //    retv = HASH_DATA_SIZE;
            memcpy(data, entry->data, _min(size, entry->size));
        }
        //else
        //    retv = HASH_NO_DATA;
    }
    else
        retv = HASH_NOT_FOUND;

    return retv;
}

size_t find_hash_table_entry_size(hash_table_t* tab, const char* key) {

    _table_entry_t* entry = find_slot(tab->entries, tab->capacity, key);
    size_t retv = 0;

    if(entry->key != NULL) {
        retv = entry->size;
    }

    return retv;
}

/*
 * Iterate all of the keys in the hash table. Used for various dump utilities.
 *
 * Make reset != 0 to reset to the beginning of the table.
 */
const char* iterate_hash_table(hash_table_t* tab, int reset) {

    static int ht_index = -1;

    if(reset)
        ht_index = -1;

    for(ht_index++; ht_index < tab->capacity; ht_index++) {
        if(tab->entries[ht_index].key != NULL) {
            return tab->entries[ht_index].key;
        }
    }

    return NULL;
}
