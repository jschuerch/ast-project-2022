from __future__ import print_function
from socketserver import ThreadingUnixStreamServer
import sys

# specify which bugs to try to inject
BUG = {
  "guarded_malloc_const": True,
  "malloc_const": False,
  "scanf_num": True,
}

bug_injected = False

sys.path.extend(['.', '..'])
from pycparser import parse_file, c_parser, c_generator, c_ast

def block(block_items):
    for j in range(len(block_items)): # add more blocks (if, for, etc?)
        _item = block_items[j]
        if isinstance(_item, c_ast.Assignment):
            _item = found_assignment(_item)
        elif isinstance(_item, c_ast.FuncCall):
            _item = function_call(_item)
        elif isinstance(_item, c_ast.Compound): # <- Brackets { ... } in code
            block(_item.block_items)
        elif isinstance(_item, c_ast.Compound):
            block(_item.block_items)
        elif isinstance(_item, c_ast.If):
            if isinstance(_item.iftrue, c_ast.Compound):
                block(_item.iftrue.block_items)
            if isinstance(_item.iffalse, c_ast.Compound):
                block(_item.iftrue.block_items)
        elif isinstance(_item, c_ast.For):
            if isinstance(_item.stmt, c_ast.Compound):
                block(_item.stmt.block_items)
        block_items[j] = _item
            

def found_assignment(_item):
    _item_new = None
    if isinstance(_item.rvalue, c_ast.Cast):
        if (isinstance(_item.rvalue.expr, c_ast.FuncCall)):
            _item_new = function_call(_item.rvalue.expr, _item)
    elif isinstance(_item.rvalue, c_ast.FuncCall):
        _item_new = function_call(_item.rvalue, _item)
    if (_item_new is not None):
        return _item_new
    return _item


def function_call(_item, _outer=None):
    global bug_injected
    _item_new = None
    if (_item.name.name == "malloc"):
        if (BUG["guarded_malloc_const"]):
            # need to make this more dynamic with pre analysis
            _item_new = c_ast.If(c_ast.BinaryOp('==', c_ast.ID('n'), c_ast.Constant('int', '123456789')), 
                iftrue=c_ast.Compound([c_ast.Assignment('=', lvalue=_outer.lvalue, rvalue=c_ast.FuncCall(c_ast.ID('malloc'),c_ast.ExprList([c_ast.Constant('int', '10')])))]), 
                iffalse=c_ast.Compound([_outer]))
        elif (BUG["malloc_const"]): # not sophisticated enough
            _item.args.exprs = [c_ast.Constant('int', '1123423758')]
        bug_injected = True
    if (_item.name.name == "fscanf"): # fscanf(fp, "%d", b);
        if (isinstance(_item.args.exprs[1], c_ast.Constant) 
            and _item.args.exprs[1].type == "string" 
            and _item.args.exprs[1].value == '"%d"'
            and isinstance(_item.args.exprs[2], c_ast.UnaryOp)
            and _item.args.exprs[2].op == "&"
            and BUG["scanf_num"]):
            varname = _item.args.exprs[2].expr.name
            _item.args.exprs[2] = c_ast.ID(name=varname)
            bug_injected = True
    if _item_new is not None:
        return _item_new
    return _item


    

def insert_bug(filename):
    print("injecting bugs to %s" % filename)
    ast = parse_file(filename, use_cpp=True, cpp_args=r'-Iutils/fake_libc_include')
    
    ast_out = c_ast.FileAST([])

    n = len(ast.ext)
    for i in range(n):
        _ext = ast.ext[i]
        if isinstance(_ext, c_ast.FuncDef):
            #print(_ext.body)
            block(_ext.body.block_items)
                
        if not isinstance(_ext, c_ast.Typedef):
            ast_out.ext.append(_ext)

    if (bug_injected == False):
        print("no bugs injected!")
    else:
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
        print("Buggy program: %s" % out_filename)

if __name__ == "__main__":
    if len(sys.argv) > 1:
        key_found = True
        if len(sys.argv) == 3:
            key_found = False
            for b in BUG:
                if sys.argv[2] == b:
                    key_found = True
                    BUG[b] = True
                else:
                    BUG[b] = False
        if not key_found:
            print("bug type '%s' is not supported! Please choose one of the following:" % sys.argv[2])
            for b in BUG:
                print("'%s', " % b, end="")
            print()
        else:
            insert_bug(sys.argv[1])
    else:
        print("Please provide a filename as argument")