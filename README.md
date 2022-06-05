# ast-project-2022

This is the repository for the project of the ETH course Automated Software Testing by Jennifer Schürch and Johan Stettler. 

1. [Bug injection](#bug-injection)
2. [AFL++-evaluation](#afl-evaluation)
2. [Additional Comments](#additional-comments)

<br/>

## Bug injection

To inject bugs into arbitrary c programs, we used pycparser (https://github.com/eliben/pycparser) to parse the c code into a abstract syntax tree (AST). All of the following commands in this subsection should be run in the pycparser root folder
```
cd ast-project-2022/pycparser/
```

For debugging purposes we wrote a small script to dumpt the function definitions of the ast tree into a file. All type defs were filtered out, since we did not work with those.

Dump ast tree of c-file into a file for debugging (saves file in the same folder as source file)
```
python3 bug_injection/ast_dump.py <filename>
```

<br/>
<br/>

Here are some examples of injecting bugs into programs.


### Replace all **malloc** occurances with a constant:
```
# Inject bug
python3 bug_injection/inject_bugs.py cfile_examples/simple_malloc.c

# Trigger bug
gcc cfile_examples/simple_malloc_buggy.c -o cfile_examples/simple_malloc_buggy.out
./cfile_examples/simple_malloc_buggy.out
>> user input: 1123423758

# Non-triggering input
./cfile_examples/simple_malloc_buggy.out 
>> user input: 100

```

*Minor Problem: if there is no print statement before the malloc and we try to run the code, we get the following error for all inputs, which makes it a trivial error. However, we can simply insert a print statement at the beginning of the execution to circumvent this problem*
```
malloc(): corrupted top size
Aborted
```

<br/>

### **scanf** read number from file bug:
```
# Inject bug
python3 bug_injection/inject_bugs.py cfile_examples/scanf.c

# Trigger bug
gcc cfile_examples/scanf_buggy.c -o cfile_examples/scanf_buggy.out
./cfile_examples/scanf_buggy.out cfile_examples/in/b.txt 

# Non-triggering input
./cfile_examples/scanf_buggy.out cfile_examples/in/a.txt

```
b.txt contains numbers

a.txt contains strings

<br/>

### Corrupt **fgets** size:
```
# Inject bug
python3 bug_injection/inject_bugs.py cfile_examples/nodeTree.c fgets_add

# Trigger bug
gcc cfile_examples/nodeTreec_buggy.c -o cfile_examples/nodeTree_buggy.out
./cfile_examples/nodeTree_buggy.out
>> user input: 0000000000000000000000000000000000000000000000000000000000000000

# Non-triggering input
./cfile_examples/nodeTree_buggy.out 
>> user input: 123

```

<br/>
<br/>

By default it tries to add all implemented bug types. 
However, if you only want to inject specific bugs, there is an additional parameter that to specify which bug. 
Currently we only support specifying 1 bug type. 
```
python3 bug_injection/inject_bugs.py <filename> <optional bug type>
```
Some supported bugtypes are: guarded_malloc_const, malloc_const, scanf_num, fgets_add

<br/>

## AFL++ evaluation

To set up the AFL++ environemnt, follow the instructions given here in the afl-training github project: https://github.com/mykter/afl-training/tree/main/quickstart

Run the following command before running afl:
```
~/AFLplusplus/afl-system-config
```

In the folder ast-project-2022/afl-evaluation/ we provide some example buggy programs we used to evaluate AFL++. Each buggy program has its own folder including the program itself, the makefile and the input folder used by AFL++.

To run the afl fuzzer on the provided examples use the following commands:
```
cd ast-project-2022/afl-evaluation/<program folder>

CC=afl-clang-fast AFL_HARDEN=1 make

# Read input from stdin (for example 01_simple_malloc):
afl-fuzz -i in/ -o out ./<program>

# Read input from file as 1st argument (for example 02_scanf):
afl-fuzz -i in/ -o out ./<program> @@
``` 

<br/>
