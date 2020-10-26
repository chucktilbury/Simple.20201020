This is a rough sketch of my todo list in this project.

* Connect error module to the configure module for verbosity.
* Implement parse rules for initializing lists and dicts.
* Implement first cut at expressions. (without symbols)
* ~~Implement parser syntax for program entry point with syntax checking.~~
* ~~Implement parser flag manager~~.
* ~~Implement compound symbols.~~
* ~~Implement includes.~~
  * ~~need to look for circular includes. Probably just go with a depth limit.~~
* ~~Fix the bug where function call output parameters can be a constant value.~~
* ~~get rid of the need for empty parens after class symbol.~~
* ~~casts are broken~~ Casts no longer make sense because there is only one kind of number.
  * Casts are used to convert numbers to strings and back. Other things could be cast to a string.
* ~~Implement a print_flags function~~
* ~~fix the error reporting~~
  * ~~clarify error messages for category~~
  * ~~if there is no file open, then don't try to report the name.~~