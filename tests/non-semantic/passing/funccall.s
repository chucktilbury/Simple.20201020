<-
    Verify function call syntax works.
->

class cname() {
    func fname()() {
        asd()();
        asd(123)();
        asd()(compound.name);

        << TODO: Fix this. output parameters are passed by reference.
        asd(asd, asd,asd)(asd[123]);

        asd(asd.asd, 1234.0)(asd.asd.asd.asd);
    }
}