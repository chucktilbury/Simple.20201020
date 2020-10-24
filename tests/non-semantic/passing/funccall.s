<-
    Verify function call syntax works.
->

class cname() {
    func fname()() {
        asd()();
        asd(123)();
        asd()(123);

        << TODO: Fix this. output parameters are passed by reference.
        asd(asd, asd,asd)(123.348);

        asd(asd.asd, 1234.0)(asd.asd.asd.asd);
    }
}