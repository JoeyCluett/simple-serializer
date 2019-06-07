GXX = g++
CFLAGS = -std=c++11 -c -I./inc # compile flags

obj/MultiType.o: inc/MultiType.h src/MultiType.cpp
	$(GXX) $(CFLAGS) -o obj/MultiType.o src/MultiType.cpp

obj/Document.o: inc/Document.h src/Document.cpp obj/MultiType.o
	$(GXX) $(CFLAGS) -o obj/Document.o src/Document.cpp

obj/Database.o: inc/Database.h src/Database.cpp obj/Document.o
	$(GXX) $(CFLAGS) -o obj/Database.o src/Database.cpp

all: obj/Database.o
