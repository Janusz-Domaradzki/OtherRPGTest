__start__: obj gameRPG


obj: 
	mkdir obj

CPPFLAGS=-Wall -pedantic -std=c++17 -iquote inc

gameRPG: obj/main.o obj/Character.o obj/Item.o
	g++ -o gameRPG obj/main.o obj/Character.o obj/Item.o

obj/main.o: src/main.cpp inc/Character.hh src/Character.cpp inc/Item.hh src/Item.cpp
	g++ -c ${CPPFLAGS} -o obj/main.o src/main.cpp

obj/Character.o: src/Character.cpp inc/Character.hh inc/Item.hh
	g++ -c ${CPPFLAGS} -o obj/Character.o src/Character.cpp

obj/Item.o: src/Item.cpp inc/Item.hh
	g++ -c ${CPPFLAGS} -o obj/Item.o src/Item.cpp

clean:
	rm -f obj/* gameRPG core*
