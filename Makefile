all: server test

server: calculator.o lexer.o shunting_yard.o server.o serialport.o
	g++ calculator.o lexer.o shunting_yard.o server.o serialport.o -o server -Wall -O3 -std=c++14

test: test.o calculator.o lexer.o shunting_yard.o
	g++ test.o calculator.o lexer.o shunting_yard.o -o test -Wall -O3 -std=c++14
	


server.o: server.cpp
	g++ server.cpp -o server.o -c -Wall -O3 -std=c++14

test.o: test.cpp
	g++ test.cpp -o test.o -c -Wall -O3 -std=c++14



calculator.o: calculator.cpp calculator.h
	g++ calculator.cpp -o calculator.o -c -Wall -O3 -std=c++14

lexer.o: lexer.h lexer.cpp
	g++ lexer.cpp -o lexer.o -c -Wall -O3 -std=c++14

shunting_yard.o: shunting_yard.h shunting_yard.cpp
	g++ shunting_yard.cpp -o shunting_yard.o -c -Wall -O3 -std=c++14

serial_port.o: serialport.h serialport.cpp
	g++ serialport.cpp -o serialport.o -c -Wall -O3 -std=c++14

clean:
	@rm shunting_yard.o lexer.o calculator.o server.o test.o test serialport.o server