all: read_grammar.o tokenizer.o tokenizer_structs.o grammar_structs.o tokenizer_structs.o parse_tree.o machine_grammar
	gcc -o driver.exe final_code/driver.c read_grammar.o tokenizer.o grammar_structs.o tokenizer_structs.o parse_tree.o

machine_grammar:
	python generate_grammar.py -o grammar/machine_grammar.txt --grammar-struct-out final_code/grammar_structs --json_in grammar/symbols.json grammar/grammar.txt

grammar_structs.o: machine_grammar
	gcc -c final_code/grammar_structs.c

read_grammar.o:
	gcc -c final_code/read_grammar.c

tokenizer_structs.o: final_code/tokenizer_structs.c final_code/tokenizer_structs.h
	gcc -c final_code/tokenizer_structs.c

tokenizer.o:
	gcc -c final_code/tokenizer.c

parse_tree: tokenizer_structs.o grammar_structs.o read_grammar.o tokenizer.o machine_grammar
		gcc -o parse_tree.exe final_code/parse_tree.c read_grammar.o tokenizer_structs.o grammar_structs.o

parse_tree.o:
	gcc -c final_code/parse_tree.c

parse_tree_traverse: parse_tree.o tokenizer_structs.o grammar_structs.o read_grammar.o tokenizer.o machine_grammar
		gcc -o parse_tree.exe final_code/traverse_parse.c parse_tree.o read_grammar.o tokenizer_structs.o grammar_structs.o


.PHONY: clean
clean:
	rm grammar/machine_grammar.txt
	rm *.o
	rm *.exe
