<-
    This test verifies that method declarations accept
    correct syntax.
->

<< class definition is required
somename()
{

    funcname()() {} << function definitions can be empty
    fname(number simple_name)(<- empty ->) {}
    fname(number x, number y, number z)(<- empty ->) {}
    fname(<- empty ->)(number simple_name) {}
    fname(<- empty ->)(number x, number y, number z) {}
    fname(number simple_name)(number x, number y, number z) {}
    fname(complex.name x)(complex.name y) {}

    <- make sure all acceptible types are accepted ->
    fname(string str)(string str) {}
    fname(dict str)(dict str) {}
    fname(list str)(list str) {}
    fname(bool str)(bool str) {}
    fname(number str)(number str) {}
    fname(compound.name str)(compound.name str) {}
    constructor(){}
    destructor{}
}