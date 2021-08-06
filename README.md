# external-code-loader [ecl.h]

This utility is a sort of replacement of the eval() function known in some interpreted languages.
It contains evalc() for loading char arrays and evalf() for loading files.
The utility uses the dynamic library loader to open files using dlopen() and getting function
pointers dlsym(). Because of that, the utility COULD NOT run on Windows (MacOSX untested) and
must be compiled using the -ldl in gcc (example below).
Also, the utility REQUIRES gcc or g++ or other compilers(depends of the project)
to be installed in the user's machine (compilation done at runtime requires compilers).
All the defined preprocessors can be called alone as for every modules of the utility.
The preprocessors are defined using the ECL_ prefix.

Initialisation of custom compiling argument isn't required, but suggested for more optimisation.
Hard coded compilation arguments are defined as following: "gcc/g++ -shared -o tmp.so tmp.c".
To specify compilation arguments, define ECL_COMPILE_ARGUMENT in the translation unit in which
the tool is included, with a string as argument. (gcc compiler by default but can be changed).

INFO:

  The utility only execute arguments inside of a specific function registered as __init__().
  The __init__() function COULD NOT receive parsed arguments.
  If the external file or char array doesn't contain this function, the program is expected to crash and log
  a Segmentation Fault.
  External libraries or internal modules (previously declared inside of the program, not external) can be included
  and used inside of the arbitrary executed code.

WARNING:

  While using c++ projects (inside of the injected code), the __init__() function must be declared using
  extern "C" in order to be recognised by the c++ mangle name specification.
  If not done, the function causes undefined behaviours that log as Segmentation Fault when calling the __init__()
  function of the program.
  When using elc.h and soc.h together in linux and adding new items using the add_item() function inside of
  an evaluated file evalf(), please link you program using the linking option --export-dynamic as following:
  ```
  gcc -Wl,--export-dynamic
  ```
  Otherwise, the dynamic library generated for interpretation of C code will have different global variables.
  The variables item_list[256] and num_item will not be shared.

FUNCTION USAGE:
  ```c
  evalc(const char data[256])     //Where data represents the input char array
  evalf(const char* file)         //Where file represents the input file
  ```

EXAMPLES:
```c
 //File example in C:
    #include<stdio.h>
    void __init__(){
      printf("Hello World in C from external file !\n");
    }
```
```c++    
  //File example in C++:
    #include<iostream>
      extern "C" void __init__(){
        std::cout<<"Hello World in C++ from external file !"<<std::endl;
  }
```
```c
  //Char array example in C:
    "#include<stdio.h>\n void __init(){printf(\"Hello World in C from external file !\");}"
```
```c++
  //Char array example in C++:
    "#include<iostream>\n extern "C" void __init(){std::cout<<\"Hello World in C from external file !\"<<std::endl;}"
```

--------------------------------------------------------------------------------------------------------------

# structure-objects-in-c [soc.h]

This file can be used to create a pseudo object oriented programming using C structs.
Of course, this module is not compatible with C++ because it supports classes.
The file contains 3 functions: add_item, del_item and upt_item. Further examples below.
It also contains definitions for the num_item, and a typedef of void and typedef of struct.
A preprocessor is also defined.

WARNING:

When using ecl.h with this module, function used as <ITEM_NAME>.func musn't be redefined inside the external evaluated file.
Otherwise, a Segmentation Fault will be returned by the main program.
You still can use functions implemented by the main program or previously evaluated external files, 
but it will be required to resolve missing dependencies (including linking against the main program's extenal
libraries such as OpenGL) using the ECL_COMPILE_INSTRUCTION 
(but this might not be the case, only of a Segmentation Fault occures).

EXAMPLES:
```c
  //Examples in sample program (main.c, int main())
    
    //Declaration of the "structural object" object_instance with predefined type ITEM
    ITEM object_instance;
    
    //Defining the data of object_instance by casting <TYPE> to <VARIABLE>
    object_instance.data=((<TYPE>*)<VARIABLE>);
    
    //Defining the function (func) of object_instance
    object_instance.func=<FUNCTION>;
    
    //Adding object_instance to the item_list[] array
    add_item(object_instance);
    
    //Updating all the items inside the item_list[] array
    upt_item();
    
    //Removing item by if 0
    del_item(0);
    
    //Accessing all object in the item_list and printing their id
    ITEM_LOOP(printf("%d",item_list[i].id);)
```

--------------------------------------------------------------------------------------------------------------

# auto-inapp-recompiler [rcp.h]

This auto-recompile utility supports C and C++ projects, 
it must be included in the main source file in order to work properly.
All the macros defined in this file could be used inside the main application.
All the defined preprocessors can be called alone as for every modules of the utility.
The preprocessors are defined using RCP_ prefix.

In order to initialyse it, 4 parameters must be defined:
AUTO_RECOMPILE: 	used to compile and then process the utility.
RECOMPILE_HEADERS: 	for calling the compilation of the extra "header" bin.
SOURCE_PATH: 		the path to the "source" bin.
HEADER_PATH:		the path to the "header" bin.

The paths must lead to a (chosen extension and named) file that will feed a system() function
and parse all the line as OS speecific argument. 

--------------------------------------------------------------------------------------------------------------

# terminal-key-hook [tkh.h]

The minimal terminal key hook utility is a really basic key registration system based
around the kbhit() and getch() ncurses functions. Though, they have been remastered to prevent
the execution lag due to input wait time. A special function is integrated, called tkhPollKeys().
This function allows the application to register the last pressed input (using the last two functions)
and put the key (only one available per frame) inside the tkh_key_buffer[].
This key buffer will remain unchanged if the poll key function isn't called again, allowing calculation
using the content of the key buffer.
The utility also contains key macros, giving name to the pressed keys. In that fashion, keys inside the 
key buffer can be called by their preprocessor name, such as TKH_KEY_A for the 'a' character/key.

WARNING: This input registation method is really limited because of it's closeness to the terminal emulator running the program.
Because of this, unfocussing the terminal (lastly the front process) will completely disable the input registration.
Key detection is also affected by the terminal emulator's speed and ability to register key events.
Most of the terminal emulators will repeat the last key pressed after some time, not doing it instantly, making the utility
horrible for game purposes. And still, only one key can be processed at the time (again due to terminal emulators).
And yet, this utility is only entended for linux.
