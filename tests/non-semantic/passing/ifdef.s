<-
    Verify that if/else clause syntax is accepted.
->

cname {
    fname()() {
        if(x equ 0) {}

        if(x equ 0){}
        else {}

        if(x equ 0){}
        else(x equ 10) {}
        else {}

        if(x equ 0){}
        else(x equ 10) {}
        else(x equ 11) {}
        else(x equ 12) {}
        else(x equ 13) {}
        else{}
    }
}