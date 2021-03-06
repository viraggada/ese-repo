ECEN 5013- Embedded Software Essentials : Project 1

Authors: Vishal Vishnani & Virag Gada

Date: 02/12/2017

Supported Platforms: HOST LINUX-Ubuntu, Freedom Freescale KL25Z, BeagleBone Black

Goals:
1. Making architecture-independent softwares
2. Cross compiling for 3 different platforms
3. Getting familiar with Build System using GCC

Requirements for Build system and Makefile:

1. Flags:
-Wall = Used to enable warning messages
-Werror = Converts all warnings to errors
-g = Produce's debugging informatiion in OS's native format.
-O0 = Used to optimize for compilation time
-std=c99 = Compatible with c99 standard
-mcpu=cortex-m0plus = Architecture specific flag for Freedom Freescale Board
-mcpu=cortex-a8 = Architecture specific flag for BeagleBone Black
-I = To include folder names in the recipe to find required prerequisites
-CC = Enables us to include cross and native compilers
-CFLAGS = Enables us to add flags to recipe
-M = To create dependency file

2. Utilities:
-size = To see the size of the object file in decimal and hex
-ar = Used to create archive for files like a static library
-objdump = Used to dump the output of object file

3. Outputs:
.map = -Map flag used to create map file
.dep = Using -M flag options to create dependency file
.out = Target executable file made using object files
.o = Individual object file made with .c files

4. PHONY:
.PHONY protection required for all target files.

Target Specifications used were:
1. preprocess: Used to create preprocessed output for all source files.
   Command : make preprocess

2. %i: Used to create preprocessed output for a specific source file.
   command : make filename.i

3. asmfile : Used to create assembly output for all source files.
   command : make asmfile
   
4. %.s : Used to create assembly output for a specific source file.
   command : make filename.s
   
5. %.o : Used to create object file of the specified c file. The file is not linked.
   command : make filename.o
   
6. compile-all : Used to generate object files for all the source files without linking them. 
   command : make compile-all
  
7. build : Used to compile and link source file, creates executable and memory map file.
   command : make build
   
8. clean : Used to clean all the files generated by make.
   command : make clean

9. dependencies : Used to create dependency file for all .c files. Makes use of -M flag. 
   command : make dependencies 

10. project.out : Used to create executable file using all .o files.
    command : make project.out
	
11. build-lib : Used generate a library of memory.c and data.c into an archive called libproject1.a. Makes use of ar.
    command : make build-lib

12. direct_link : Used to directly invoke the linker without using GCC. Makes use of ld.
    command : make direct_link

	
Using Compile time switch "switch":
Project compilation is switched off when value OFF is written to "switch" using command line.
The default value is ON.

Using Compile time switch "PLATFORM":
It is used to set the platform for which we want to run the commands.
The platforms are HOST LINUX-Ubuntu, Freedom Freescale KL25Z, BeagleBone Black.
The default platform us HOST LINUX-Ubuntu.

Using Compile time switch "DEVICE":
It is used to determine the architecture we are currently working on. This is done using shell arch command.

Dependencies:
1. All .c files are present in SOURCES folder.
2. All .h files are present in headers folder.
3. sources.mk is present in same directory as makefile.