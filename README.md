# Simple
This is an iteration of the Simple language. In this version, Flex and Yacc are used to clarify what the language looks like.

Simple is a very simple language that implements single inheritance objects. All methods must be implemented inside a class, but classes do not needs to be implemented all in the same file. When a "new" definition for a class is encountered, duplicate methods are simply replaced with the new one. Inheritance is accomplished by simply adding the methods and attributes of the child class to the base class and renaming the result to the new name. 

The run time strategy is to compile to byte code as the source is encountered and run in a virtual machine.

The general philosophy of the language is to keep it simple. (surprise) 
* All numbers are double precision floats.
* Strings, numbers, bools, lists, and hashes are the only data types. 
* All data elements are handled as internal classes that can have definitions in the code. All of the native types can be converted to or from strings using a cast. 
* There are no pointers.
* Blocks are defined using "{}"
* All statements are terminated by a ";"
* The number of operators is kept to a minimum.
* Multiples files for a program is supported by using an "include" keyword. The source code of a program is concatinated as if it was a single file before it is compiled.
* Things like printing and reading files are handled as libraries, not as language features. Libraries are added to the program using an "import" keyword. A library is simply a module that has been pre-compiled.
* Symbols are "decorated" with its type. They are accessed using the "." operator. 
* Method overloading is supported but decorating the name with the input and output types.
* Methods are definined with explicit input and output vars. 
  * for example: ```method_name(num x, str y)(num v){}```
    * input variables are z and y and they are passed into the method by value.
    * output variable is v, which is passed into the method by reference. 
    * input and output variables must be referenced in the method or is't a syntax error.
* Comments are prefixed with a "#" marker. When there is just one marker, then the comment extends to the end of the line. When there are more than one markers, the comment is a multi-line comment. For example:
```
#############
# This is a multi-line comment
# and single #'s are ignored.
## not in the comment # this is another comment.
```
