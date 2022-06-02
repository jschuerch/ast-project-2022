# ast-project-2022

This is the repository for the project of the ETH course Automated Software Testing by Jennifer Schürch and Johan Stettler. 

1. [Bug injection](#bug-injection)
2. [AFL++-evaluation](#afl-evaluation)
2. [Additional Comments](#additional-comments)

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

Here are some examples of injecting bugs into programs.
In case you only want to inject specific bugs, there is a 

### Replace all **malloc** occurances with a constant:
```
# Inject bug
python3 bug_injection/inject_bugs.py cfile_examples/simple_malloc.c

# Trigger bug
gcc cfile_examples/simple_malloc_buggy.c -o cfile_examples/simple_malloc_buggy.out
./cfile_examples/simple_malloc_buggy.out 1123423758

# Non-triggering input
./cfile_examples/simple_malloc_buggy.out 100

```
*Problem: if there is no print statement before the malloc and we try to run the code, we get the following error for all inputs, which makes it a trivial error*
```
malloc(): corrupted top size
Aborted
```


### **scanf** read number from file bug:
```
# Inject bug
python3 bug_injection/inject_bugs.py cfile_examples/scanf.c

# Trigger bug
gcc scanf_buggy.c -o scanf_buggy.out
./scanf_buggy.out in/b.txt 

# Non-triggering input
./scanf_buggy.out in/a.txt

```
b.txt contains numbers

a.txt contains strings


## AFL++ evaluation


## Additional Comments

