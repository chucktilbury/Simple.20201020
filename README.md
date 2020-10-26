# Simple
This is an iteration of the Simple language. In this version, Flex and Yacc are used to clarify what the language looks like, but the final version will be written in C.

Simple is a very simple language that implements single inheritance objects. All methods must be implemented inside a class, but classes do not needs to be implemented all in the same file. When a "new" definition for a class is encountered, duplicate methods are simply replaced with the new one and new methods are simply added. There is no notion such as Python's "super". Inheritance is accomplished by simply adding the methods and attributes of the child class to the base class and renaming the result to the new name.

The run time strategy is to compile to byte code as the source is encountered and run in a virtual machine.

In general, the syntax of Simple is C-like. I find it clear to read and fairly standard for people who know other C-like languages.
* Blocks are defined using "{}"
* All statements are terminated by a ";"
* Multiples files for a program is supported by using an "import" keyword. The source code of a program is concatinated as if it was a single file before it is compiled.

The general philosophy of the language is to keep it simple. (surprise) Here are some of the unique features.
* All numbers are double precision floats.
* Strings, numbers, bools, lists, and hashes are the only data types.
* All data elements are handled as internal classes that can have definitions in the code. All of the native types can be converted to or from strings using a cast.
* There are no pointers.
* The number of operators is kept to a minimum.
* Things like printing and reading files are handled as libraries, not as language features. Libraries are added to the program using an "import" keyword. A library is simply a module that has been pre-compiled.
* Symbols are "decorated" with its type. They are accessed using the "." operator.
* Method overloading is supported but decorating the name with the input and output types.
* Methods are definined with explicit input and output vars.
  * for example: ```method_name(num x, str y)(num v){}```
    * input variables are z and y and they are passed into the method by value.
    * output variable is v, which is passed into the method by reference.
    * input and output variables must be referenced in the method or is't a syntax error.
* Multi-line comments are made using the <- and -> symbols. Single line comments start with a << marker. For example:
```
<-
 This is a multi-line comment.
->
<< this is a single line comment.
```
* The program entry point is defined by a special class named "Entry". The constructor of this class is the entry point
of the program. That must be exactly one entry point in a valid Simple program.
