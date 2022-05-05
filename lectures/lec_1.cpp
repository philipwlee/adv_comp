/* LECTURE NOTES
 *
 * C++ is compiled; it does not need to interface with a VM (like Python or Java)
 * Therefore, it lacks a garbage collector that deletes unused variables.
 * Without the VM translation layer, it is much faster.
 *
 * preprocessor finds and replaces directives (#) to translate the code for compilation.
 * Compiler transforms the code into ASSEMBLY (.s extension, hard to understand)
 *
 * Python imports load everything into the memory.
 *
 * #define NUMBER 100
 * ^ macro loses the notion of type (C++ is strongly typed)
 * preprocessor does the replacements for #define
 *
 * Assembler outputs machine code (practically unreadable)
 *
 * Linker adds the system libraries
 *
 * Namespace collision: two namespaces used; functions of the same name
 *
 * Interpreter v compiler: Interpreter uses a VM and allows running line by line
 * Linker combines object files and assembles an executable.
 * #include directive adds header files
 *
 * Why do we avoid globals? Different files may use globals of the same name; fails to link (?)
 * Major steps of compilation (3 major phases):
 *   1. Front end: parser. Converts code into an AST (Abstract Syntax Tree). Very important
 *      for compiler optimization.
 *   2. Middle end: most complex. Analyze and optimize code.
 *   3. Back end: convert into assembly. Contains information on computer architecture:
 *      the machine model.
 *
 * How memory works:
 * Visualize memory as cells.
 */


#include <iostream> // preprocessor directive to import input output stream
#include <string>

typedef std::string str;

// Sometimes you don't want to overload a function a bunch of times because
// it takes an argument of the same form...
template <typename T>
void print(T s) // do this for int, double, float, char, str... annoying...
{
    std::cout << s << '\n'; // all the overloaded functions do this line exactly!
}

template <typename U>
auto len(U s)
{
    print(sizeof(s));
    print(sizeof(typeid(s[0])));
    return sizeof(s)/sizeof(typeid(s[0]));
}

int f1(int a)
{
    int* c {new int}; // allocated to the HEAP. new is a system call that tells it to allocate memory.
    *c = 3; // assign 3 but c will not be used
    int b {3}; // b will be returned...
    return b; // returns a, a is allocatd in the stack
} // MEMORY LEAK! c is not returned... memory is allocated, but the address of c is lost.

int* f1()
{
    int* c {new int};
    *c = 3;
    return c;
} // NOT MEMORY LEAK. c is returned; not lost.

int lec_1()
{
    std::cout << "L1 has started\n";
    print("Function template demo here");
    print(4);

    print("\nUndefined behavior:");
    float a; // a is not defined here
    print(a);

    print(' ');
    str string { "this is a string that was declared as str using typedef."};
    print(string);

    str* ss { &string }; // initialize pointer with address of string
    // the type of the pointer is used by the compiler to incrementally jump.
    // str* will jump by sizeof(s[0]) for example.
    print(ss); // better to pass the pointer than the str because pointer avoids copying
    print(*ss); // print using dereference *

    char ar[5] {'p', 'h', 'i', 'l', '\0'}; // '\0' is string end character
    print(ar);
    print(ar[0]);
    print(sizeof(ar)/sizeof(ar[0])); // length of ar normalized by size of character

    print(' ');
    // wrong pointer type is not allowed; does not compile.
    int* bad { reinterpret_cast<int*>(&ar) };
    print(bad);
    print(*bad); // WTF is this shit?

    print(' ');
    int tab[] {1,2,3,4,5,6,7,8,9,10};
    // array tab is actually a pointer.
    int* tab_st { tab }; // tab is a pointer!!!

    for(int k {0}; k<sizeof(tab)/sizeof(int); k++)
    { // therefore, this following line
        std::cout << (tab_st+k) << ':' << *(tab_st+k) << ", ";
        // tab_st knows how much to add to the memory address during +k because it is int*
    }

    print('\n');
    std::cout << tab; // note that cout << tab prints the address of the first element
                      // exactly the same thing as cout << tab_st (which is a pointer)
    print(len(tab));

    print(*f1());

    return 0;
}
