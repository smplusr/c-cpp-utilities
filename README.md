# arbitrary-hex-loader [ahl.h]
This utility is used to directly execute machine code instructions stored in a buffer.
This method of arbitrary code execution is commonly named shellcode and is mostly used in the
"hacking" domains of programation, and especialy starting shell or terminal emulator from the client
(application runner).
However, shellcodes can be used to run any kind of code during runtime.
In order to use this utility, correct instructions must be entered (example bellow) which must be corresponding
to the running application's architecture (as it is technically machine code).

INFO:

  Shellcodes can be extracted from various utilities like GDB or Objdump from compiled (but not linked)
  C or C++ codes.
  It is recommended to use the -fno-pic and -no-pie during the shellcode compilation in order to get
  static stack memory pointer allocation and getting rid of unnecessary sections.
  The Optimisation flags -O(x) are also recommended as they creates shorter shellcodes.

WARN:
  
  The functions used in the shellcodes (if they are compiled from c) SHALL NOT be named main().
  The usage of the main() function might cause unexpected results (mostly unnecessary lines).
  The flags -fno-stack-protector and -zexecstack should be passed to the compiler while
  compiling the main application. Not toggling those flags might stop the program with
  Segmentation Faults or Illegal Instruction errors.
  Be careful when pushing memory address to a assembly register. The address might be inverted !
  The stack execution flags must be turned on when calling function within the main program
  from the shellcode.

Examples:
```c
  /* Examples of functions: */
  
    // Read user input from terminal
    ahlReadInput();
  
    // Read char array from file
    ahlReadFile(<FILENAME>);
  
    /* Read direct char array and updates the buffer
     * This function is called by the upward functions */
    ahlUpdateBuffer(<CHARACTERS>);
  
    /* Takes buffer and gives it a pointer
     * Called by all functions from the utility */
    ahlAttribPointer(<BUFFER>);
  
  
  /* Examples of variables: */
  
    // Generic "all purpose" function pointer
    ahl_funcptr <DATA>;
  
    // Main buffer (result of functions), must be used with ahlAttribPointer()
    ahl_buffer;
  
  
  /* Examples of program */
  
    #include"ahl.h"	// The utility header

    int main(){
    	ahlUpdateBuffer("b8 0a 00 00 00 c3");	// Buffer that will return 10 (might be content of file)
	
	ahl_funcptr func=ahlAttribPointer(ahl_buffer);	// Declaration of function "func" (attribution of pointer)
	printf("%d\n",func());	// Printing result of function as integer (result is 10, due to return operation of buffer)
    }
```

Explanation of the example's shellcode:
```c
Disassembly of section .text:

00000000 <func>:
	0:	b8 0a 00 00 00		mov	$0xa, %eax		// Setting 10 as raw data in memory
	1:	c3			ret				// Returning (previous declared data)
```

Explanation of the example's shellcode:
```c
Disassembly of section .text:

00000000 <func>:
	0:	48 c7 c0 78 56 34 12   	mov	$0x12345678, %rax	// Set register 'rax' to address, see WARN section
	1:	ff e0			jmp	%rax			// Jump to stored address
	2:	c3			ret				// Returning, otherwise app will SegFault
	
	OR:
	
	0:	b8 78 56 43 12		mov	$0x12345678, %eax	// Same but with 'eax' register
	1:	ff d0			call	%eax			// Using call unstead of jump
	2:	c3			ret				// Always returning
```

Important links:
```
Chart of assembly/opcode instructions:		http://sparksandflames.com/files/x86InstructionChart.html
List of assemly/opcode instructions:		http://ref.x86asm.net/coder32.html
Other list of instructions:			http://www.mathemainzel.info/files/x86asmref.html

Hello world in shellcode:			https://stackoverflow.com/questions/15593214/linux-shellcode-hello-world
Calling c functions from shellcode:		https://stackoverflow.com/questions/43282303/calling-c-functions-shellcode
Jump instruction shellcode:			https://stackoverflow.com/questions/9815448/jmp-instruction-hex-code
```

--------------------------------------------------------------------------------------------------------------

# external-code-loader [ecl.h]

This utility is a sort of replacement of the eval() function known in some interpreted languages.
It contains evalc() for loading char arrays and evalf() for loading files.
The utility uses the dynamic library loader to open files using dlopen() and getting function
pointers dlsym(). Because of that, the utility COULD NOT run on Windows (MacOSX untested) and
must be compiled using -ldl in gcc (example below).
Also, the utility REQUIRES gcc or g++ or other compilers (depends of the project)
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

# raw-system-input [rsi.h]

This input utility is a mouse and keyboard handler for linux.
It is similar to glut (freeglut) or glfw input managing system, but only supports linux (as of current version).
See the following example for more information about how to use the api.

EXAMPLE:
```c
/* Must be defined before including the rki or rmi header file.
 * If the dev input file is not declared before including rki.h or rmi.h, it will be defined
 * inside the headers with the default input file (same as following). */
#define RSI_MOUSE_INPUT_FILE "/dev/input/by-path/platform-i8042-serio-0-event-kbd"
#define RSI_MOUSE_INPUT_FILE "/dev/input/mice"
#include"rsi.h"

#include<stdio.h>

int key_buffer[256];

void key_callback(int key,int act){
	if(act==RKI_KEY_PRESSED) key_buffer[key]=1;
	if(act==RKI_KEY_RELEASE) key_buffer[key]=0;
}
void mouse_callback(int x,int y,int button[3]){
	printf("x=%d, y=%d, l=%d, m=%d, r=%d\n",x,y,button[0],button[1],button[2]);
}

int main(void){
	/* Defining callbacks for keyboard and mouse. */
	rsiBindCallback(&key_callback,&mouse_callback);
	while(!key_buffer[KEY_ESC]){
		/* The key is in raw format (KEY_Q or code 16 is mapped on A
		 * azerty keyboards). */
		if(key_buffer[KEY_Q]) printf("%s\n","Hello World!");
		/* Polling events from keyboard and mouse.
		 * similar to keybrPollEvents(); mousePollEvents(); */
		 rsiPollEvents();
	}
		
}
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
