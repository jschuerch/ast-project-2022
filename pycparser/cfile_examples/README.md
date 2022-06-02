Run the following commands in the pycparser root folder
```
cd ast-project-2022/pycparser/
```

Dump ast tree of c-file into a file for debugging (saves file in the same folder as source file)
```
python3 bug_injection/ast_dump.py <filename>
```

To inject bugs run the following command
```
python3 bug_injection/inject_bugs.py <filename> <optional bug type>
```