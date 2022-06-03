from __future__ import print_function
import sys
sys.path.extend(['.', '..'])
from pycparser import parse_file, c_parser, c_generator, c_ast

def insert_bug(filename):
    print("creating AST dump for: %s" % filename)
    ast = parse_file(filename, use_cpp=True, cpp_args=r'-Iutils/fake_libc_include')
    
    ast_out = c_ast.FileAST([])

    n = len(ast.ext)
    for i in range(n):
        _ext = ast.ext[i]
        if not isinstance(_ext, c_ast.Typedef):
            ast_out.ext.append(_ext)


    out_filename = filename[:-2] + "_ast.txt"
    f = open(out_filename, "w")
    f.write(str(ast_out))
    f.close()
    print("AST written to: %s" % out_filename)

if __name__ == "__main__":
    if len(sys.argv) > 1:
        insert_bug(sys.argv[1])
    else:
        print("Please provide a filename as argument")