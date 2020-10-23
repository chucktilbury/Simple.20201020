<-
    This file contains incorrect import statements to
    check for correct errors.

    The 3 token rule of the parser means that a valid import
    statement needs to be inserted between the errors.
->

import 1somename;
import somename;

import somename
import somename;

import "somename";
import somename;

import some.name;
import somename;

import;
