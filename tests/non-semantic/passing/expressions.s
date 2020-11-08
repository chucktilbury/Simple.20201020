/*
    This is a cursory test for expressions to check the
    syntax is being accepted.
*/

some_class_name {

    number xyz = asd.dfg;
    number asdf = 123+234*85;
    bool qwe = (qwe.we == wer) and (123 > 1);
    bool qwe = string:(qwe.we equ wer) and (123 gt 1);
    bool qwe = bool:((qwe.we equ wer) and (123 gt 1));
    bool qwe = ((qwe.we equ wer) and (bool:123 gt 1));

    some_func_name()() {
        // var = var1[1+2*3];
        var = "some string":(ver, 1+2*3, qwe.erw);
        var = 10/2+1;
    }
}
