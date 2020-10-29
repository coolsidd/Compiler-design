# Group 36
# 2017B4A70495P Manan Soni
# 2017B4A70549P Siddharth Singh
# 2017B4A70636P Nayan Khanna
# 2017B4A70740P Aditya Tulsyan


all:  all_dependencies machine_grammar
	gcc -o driver.exe *.o

machine_grammar:
	python3 generate_grammar.py -o machine_grammar.txt --grammar-struct-out grammar_structs --json_in symbols.json grammar.txt

all_dependencies: machine_grammar
	gcc -c *.c

.PHONY: clean
clean:
	rm *.o
	rm *.exe
