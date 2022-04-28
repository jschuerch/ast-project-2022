from __future__ import print_function
import sys

sys.path.extend(['.', '..'])
from pycparser import parse_file, c_parser, c_generator, c_ast

def change_malloc(filename):
    ast = parse_file(filename, use_cpp=True, cpp_args=r'-Iutils/fake_libc_include')
    
    ast_out = c_ast.FileAST([])

    n = len(ast.ext)
    for i in range(n):
        _ext = ast.ext[i]
        if isinstance(_ext, c_ast.FuncDef):
            #print(_ext.body)
            for j in range(len(_ext.body.block_items)):
                _item = _ext.body.block_items[j]
                if isinstance(_item, c_ast.Assignment):
                    #print(_item.rvalue)
                    if isinstance(_item.rvalue, c_ast.Cast):
                        #print(_item.rvalue.expr)
                        if (isinstance(_item.rvalue.expr, c_ast.FuncCall)):
                            if (_item.rvalue.expr.name.name == "malloc"):
                                #print(_item.rvalue.expr.name)
                                _item.rvalue.expr.args.exprs = [c_ast.Constant('int', '10')]
                        #print(_item.rvalue.expr)
        if not isinstance(_ext, c_ast.Typedef):
            ast_out.ext.append(_ext)

    # write buggy code to file
    generator = c_generator.CGenerator()

    include_string = ""
    f = open(filename, "r")
    for line in f.readlines():
        line = line.strip()
        if (line.startswith("#include")):
            include_string += line + "\n"

    out_filename = filename[:-2] + "_buggy.c"
    f = open(out_filename, "w")
    f.write(include_string)
    f.write(generator.visit(ast_out))
    f.close()

if __name__ == "__main__":
    if len(sys.argv) > 1:
        change_malloc(sys.argv[1])
    else:
        print("Please provide a filename as argument")