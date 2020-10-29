# PPL Assignment-1

> Group 36
> 2017B4A70495P Manan Soni
> 2017B4A70549P Siddharth Singh
> 2017B4A70636P Nayan Khanna
> 2017B4A70740P Aditya Tulsyan

## Usage
- Create executable (driver.exe): ```make```
- Remove all unwanted files: ```make clean```

After running ```make``` run the driver file.  
It takes a command line arguement of a valid filename which it will parse according to the assignment specifications.  
Example: ```./driver.exe t1.txt```

### Grammar

- The grammar file we wrote is stored in ```grammar.txt```
- Use the ```generate_grammar.py``` script to convert this grammar into a machine readable format (```machine_grammar.txt```) along with generation of terminals, non-terminals and utility functions (to get and print grammar symbols).  
- The grammar parser is written in ```read_grammar.c``` and the data structures for storing the grammar are in ```grammar.h```

### Tokenizer

- The tokenizer is written in ```tokenizer.c``` and the data structures are defined in ```tokenizer_structs.h```

### Parse tree

### Type checking and type expressions

According to the assignment PDF, The Type Expression Table is expected to store the following:
 + Field 1: The name of variable extracted from the declaration statement and to be used in the
assignment statement.
 + Field 2: The information about whether it is an array or not, if yes, then whether it is rectangular
array or a jagged array.  
Use numbers enumerated values of 0, 1 and 2 for primitive data type, rectangular array and jagged array respectively.  
The value 0 corresponds to integer, real and Boolean types. However, these primitive type details are filled in the fourth field  
explicitly defining the integer, real or Boolean specifications appropriately.
 + Field 3: If the type is a rectangular array, then whether it is static or dynamic based on the typeof range parameters used in  
defining the array type. If it is not a rectangular array this value is stored as “not_applicable”.
 + Field 4: type expression, which is implemented using the union data type.
