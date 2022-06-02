Run the following commands in the pycparser root folder
```
cd ast-project-2022/pycparser/
```

Dump ast tree of c-file into a file for debugging (saves file in the same folder as source file)
```
python3 bug_injection/ast_dump.py <filename>
```

## simple **malloc** bug:
```
# Inject bug
python3 bug_injection/inject_bugs.py jsc_examples/simple_malloc.c

# Trigger bug
gcc simple_malloc_buggy.c -o simple_malloc_buggy.out
./simple_malloc_buggy.out 100000

# Non-triggering input
./simple_malloc_buggy.out 100

```
Problem: if there is no print statement before the malloc and we try to run the code, we get the following error for all inputs, which makes it a trivial error
```
malloc(): corrupted top size
Aborted
```


## **scanf** read number from file bug:
```
# Inject bug
python3 bug_injection/inject_bugs.py jsc_examples/scanf.c

# Trigger bug
gcc scanf_buggy.c -o scanf_buggy.out
./scanf_buggy.out in/b.txt 

# Non-triggering input
./scanf_buggy.out in/a.txt

```
b.txt contains numbers

a.txt contains strings