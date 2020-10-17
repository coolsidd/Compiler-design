#!/usr/bin/env python3
"""
generate_grammar.py --- This module converts the grammar written in easy to read format (BNF) to a more parsable format
"""
import argparse
import os
import re

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


def parse_file(input_file_location, output_file_location, delim=" "):
    non_term_regex = re.compile("<(.*?)>")
    input_file = open(input_file_location)
    output_file = open(output_file_location, "w")
    for line in input_file:
        line = line.strip()
        if (len(line)) <= 0:
            continue
        line_wo_comment = line.split("//")[0]
        line_wo_comment = non_term_regex.sub("\\1", line_wo_comment)
        line_split = line_wo_comment.split("->")
        non_term = line_split[0].strip()
        rhs = line_split[1].strip()
        for rhs_tok in rhs.split("|"):
            rhs_tok.strip()
            output_file.writelines("{}{}{}\n".format(non_term, delim, rhs_tok))


if __name__ == "__main__":
    args = parser.parse_args()
    print(args)
    parse_file(args.input_file, args.output_file)
