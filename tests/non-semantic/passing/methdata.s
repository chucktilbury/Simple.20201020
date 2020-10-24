<-
    This tests that class data types and assignment syntax
    is accepted.
->

class classname() {

    func fname()() {
        string str;
        string str = "this is a string";
        string str = 'this is a string';
        string str = "this is a string":(123, abc);
        string str = 'this is a string':(123, abc);
        string str = "this is a string":(compound.name);
        string str = 'this is a string':(asd[123], asd['asd']);
        string str = 'this is a string':(1+2*3/4);

        number num;
        number num = 123;
        number num = 123.123;
        number num = 123.123e10;
        number num = 123.123e-10;
        number num = 0.0;
        number num = 0;
        number num = asd[1];
        number num = asd['asd'];
        number num = 1+2/3*4;

        bool bval;
        bool bval = true;
        bool bval = false;
        bool bval = asd neq 0 and 123 gt 0;

        list lst; << TODO: list init not implemented
        dict dct; << TODO: dict ini not implemented
    }
}