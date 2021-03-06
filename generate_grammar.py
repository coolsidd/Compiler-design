#!/usr/bin/env python3
"""
generate_grammar.py --- This module converts the grammar written in easy to read format (BNF) to a more parsable format
"""

"""
Group 36
2017B4A70495P Manan Soni
2017B4A70549P Siddharth Singh
2017B4A70636P Nayan Khanna
2017B4A70740P Aditya Tulsyan
"""

import argparse
import os
import re
import json
from pprint import pprint

parser = argparse.ArgumentParser(
    description="This module converts the grammar written in easy to read format (BNF) to a more parsable format"
)
parser.add_argument(
    "input_file",
    metavar="input file",
    type=str,
    help="input file written in BNF format",
)
parser.add_argument(
    "--grammar-struct-out",
    metavar="Grammar output file",
    dest="output_grammar_structs",
    type=str,
    help="outputs grammar structures locations",
    default="./output_file_structs",
)

parser.add_argument(
    "--json_in",
    dest="json_in",
    metavar="json input file",
    type=str,
    default="symbols.json",
    help="Input json for terminal/non-terminals to chars",
)
parser.add_argument(
    "-o",
    dest="output_file",
    metavar="output file",
    type=str,
    default="grammar.out",
    help="Output file name/location",
)
parser.add_argument(
    "--derives_symbol",
    dest="derives_symbol",
    metavar="Derives symbol",
    type=str,
    default="->",
    help="Derives symbol used in BNF",
)


def parse_file(
    input_file_location,
    output_file_location,
    delim=" ",
    generate_c_structs=True,
    c_structs_location=None,
    json_in=None,
):
    non_term_regex = re.compile("<(.*?)>")
    input_file = open(input_file_location)
    output_file = open(output_file_location, "w")
    non_terminals = set()
    terminals = set()
    json_input_file = open(json_in)
    terminals_json = json.load(json_input_file)
    json_input_file.close()
    for line in input_file:
        line = line.strip()
        line_wo_comment = line.split("//")[0].strip()
        if (len(line_wo_comment)) <= 0:
            continue

        line_wo_comment = non_term_regex.sub("\\1", line_wo_comment)
        line_split = line_wo_comment.split("->")
        non_term = line_split[0].strip()
        non_terminals.add(non_term)
        rhs = line_split[1].strip()

        terminals = terminals.union(rhs.split())
        for rhs_tok in rhs.split("|"):
            rhs_tok = " ".join([terminals_json.get(x, x) for x in rhs_tok.split()])
            rhs_tok.strip()
            output_file.writelines("{}{}{}\n".format(non_term, delim, rhs_tok))
    input_file.close()
    output_file.close()
    terminals = terminals.difference(non_terminals)
    terminals.remove("|")
    terminals.add("UNKNOWN")
    terminals = sorted(terminals)
    non_terminals = sorted(non_terminals)
    print("Terminals :", len(terminals))
    print("Non_Terminals :", len(non_terminals))
    if generate_c_structs:
        output_file_structs = open(c_structs_location + ".h", "w")
        output_file_structs.write(
            """/* Header guard */\n#ifndef GRAMMAR_STRUCT_H\n#define GRAMMAR_STRUCT_H\n/***************/\n#include <stdio.h>\n#include <string.h>\ntypedef enum {{ false, true }} bool;\n\ntypedef enum {{ // list all the non terminals or terminals\n{}\n}} BaseSymbol;\n\ntypedef struct symbol {{ // symbol with info if it is terminal or not\n    bool is_terminal;\n    BaseSymbol s;\n}} Symbol;\n\nSymbol toSymbol(char *enustr);\nchar *toStringSymbol(Symbol symb);\nvoid printSymbol(Symbol symb);\n\n#endif\n""".format(
                "\n".join(
                    ["    " + x + "," for x in non_terminals]
                    + ["    " + x + "," for x in terminals]
                )
            )
        )
        output_file_structs.close()
        json_input_file = open(json_in)
        terminals_json = json.load(json_input_file)
        json_input_file.close()
        with open(c_structs_location + ".c", "w") as output_file_structs:
            template_str_toSymbol = """    if (strcmp(enustr, "{2}") == 0) {{\n        ans.is_terminal = {1};\n        ans.s = {0};\n        return ans;\n    }}\n"""
            template_filled_toSymbol = [
                template_str_toSymbol.format(x, "true", terminals_json[x])
                for x in terminals
            ] + [template_str_toSymbol.format(x, "false", x) for x in non_terminals]
            template_str_print = (
                """    case ({0}):\n        return "{0}";\n        break;"""
            )
            template_filled_print = [
                template_str_print.format(x)
                for x in terminals + non_terminals
            ]
            output_file_structs.write(
                """#include "grammar_structs.h"\n#include <stdio.h>\n#include <string.h>\n\nSymbol toSymbol(char *enustr) {{\n    Symbol ans;\n    ans.is_terminal = false;\n    ans.s = UNKNOWN;\n{}\n    return ans;\n}}\n
char *toStringSymbol(Symbol symb) {{
    switch (symb.s) {{
{}
    }}
}}\nvoid printSymbol(Symbol symb) {{\n    printf("Symbol variable : ");\n    printf("%s", toStringSymbol(symb));\n    printf("    is_terminal : %s\\n", symb.is_terminal ? "true" : "false");\n}}\n""".format(
                    "\n".join(template_filled_toSymbol),
                    "\n".join(template_filled_print),
                )
            )


if __name__ == "__main__":
    args = parser.parse_args()
    parse_file(
        args.input_file,
        args.output_file,
        c_structs_location=args.output_grammar_structs,
        json_in=args.json_in
    )
