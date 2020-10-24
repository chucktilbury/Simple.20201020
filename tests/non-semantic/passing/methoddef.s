<-
    This test verifies that method declarations accept
    correct syntax.
->

<< class definition is required
class somename()
{

    func funcname()() {} << function definitions can be empty
    func fname(number simple_name)(<- empty ->) {}
    func fname(number x, number y, number z)(<- empty ->) {}
    func fname(<- empty ->)(number simple_name) {}
    func fname(<- empty ->)(number x, number y, number z) {}
    func fname(number simple_name)(number x, number y, number z) {}
    func fname(complex.name x)(complex.name y) {}

    <- make sure all acceptible types are accepted ->
    func fname(string str)(string str) {}
    func fname(dict str)(dict str) {}
    func fname(list str)(list str) {}
    func fname(bool str)(bool str) {}
    func fname(number str)(number str) {}
    func fname(compound.name str)(compound.name str) {}
}