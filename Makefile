# Group 36
# 2017B4A70495P Manan Soni
# 2017B4A70549P Siddharth Singh
# 2017B4A70636P Nayan Khanna
# 2017B4A70636P Aditya Tulsyan


all:  type_expression_checker.o machine_grammar
	gcc -o driver.exe *.o

machine_grammar:
	python3 generate_grammar.py -o grammar/machine_grammar.txt --grammar-struct-out final_code/grammar_structs --json_in grammar/symbols.json grammar/grammar.txt

grammar_structs.o: machine_grammar
	gcc -c final_code/grammar_structs.c

read_grammar.o: final_code/read_grammar.c
	gcc -c final_code/read_grammar.c

tokenizer_structs.o: final_code/tokenizer_structs.c final_code/tokenizer_structs.h final_code/tokenizer_structs.c
	gcc -c final_code/tokenizer_structs.c

tokenizer.o: final_code/tokenizer.c
	gcc -c final_code/tokenizer.c

parse_tree: tokenizer_structs.o grammar_structs.o read_grammar.o tokenizer.o machine_grammar
		gcc -o parse_tree.exe final_code/parse_tree.c read_grammar.o tokenizer_structs.o grammar_structs.o

parse_tree.o: final_code/parse_tree.c
	gcc -c final_code/parse_tree.c

parse_tree_traverse: parse_tree.o tokenizer_structs.o grammar_structs.o read_grammar.o tokenizer.o machine_grammar
		gcc -o parse_tree.exe final_code/traverse_parse.c parse_tree.o read_grammar.o tokenizer_structs.o grammar_structs.o

type_expression_checker.o:
	gcc -c ./data_structures/*.c ./data_structures/TypeExpressionDS/*.c final_code/*.c

.PHONY: clean
clean:
	rm *.o
	rm *.exe
	rm grammar/machine_grammar.txt
