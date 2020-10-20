#!/usr/bin/env python3
"""
generate_grammar.py --- This module converts the grammar written in easy to read format (BNF) to a more parsable format
"""
import argparse
import os
import re
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
    default="./output_file_structs"
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


def parse_file(input_file_location, output_file_location, delim=" ", generate_c_structs=True, c_structs_location=None):
    non_term_regex = re.compile("<(.*?)>")
    input_file = open(input_file_location)
    output_file = open(output_file_location, "w")
    non_terminals = set()
    terminals = set()
    for line in input_file:
        line = line.strip()
        if (len(line)) <= 0:
            continue
        line_wo_comment = line.split("//")[0]
        line_wo_comment = non_term_regex.sub("\\1", line_wo_comment)
        line_split = line_wo_comment.split("->")
        non_term = line_split[0].strip()
        non_terminals.add(non_term)
        rhs = line_split[1].strip()
        terminals = terminals.union(rhs.split())
        for rhs_tok in rhs.split("|"):
            rhs_tok.strip()
            output_file.writelines("{}{}{}\n".format(non_term, delim, rhs_tok))
    input_file.close()
    output_file.close()
    terminals = terminals.difference(non_terminals)
    terminals.remove("|")
    print("Terminals :")
    print(sorted(terminals))
    print("Non_Terminals :")
    print(sorted(non_terminals))
    if generate_c_structs:
        output_file_structs = open(c_structs_location+".h", "w")
        output_file_structs.write("""/* Header guard */\n#ifndef GRAMMAR_H\n#define GRAMMAR_H\n/***************/\n\ntypedef enum{{ // list all the non terminals\n{}\n\}}NonTerminal;\ntypedef enum {{ // list all the terminals\n{}}}Terminal;\n#endif""".format(",\n".join([x for x in sorted(non_terminals)]), ",\n".join([x for x in sorted(terminals)])))
        output_file_structs.close()
        # with open(c_structs_location+".c", "w") as output_file_structs:
        #     output_file_structs.write("""
        #     """)


if __name__ == "__main__":
    args = parser.parse_args()
    parse_file(args.input_file, args.output_file, c_structs_location=args.output_grammar_structs)