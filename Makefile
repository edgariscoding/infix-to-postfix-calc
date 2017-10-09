SOURCES = main.cpp
INC_DIR = include

start:	main.cpp
	@mkdir -p build
	g++ -Wall -std=c++11 -o infix_to_postfix $(SOURCES) -I$(INC_DIR)

run: infix_to_postfix
	./infix_to_postfix

clean:
	rm -rf infix_to_postfix