# simple make file for the sample program and to 
# deploy the library to '/usr/include'. You may need 
# to create the folder '/usr/include/serialize' before deploying

all: main deploy

main: main.cpp main.h lib/serializer.h lib/serializable.h
	g++ -o main -std=c++11 -march=native -O3 main.cpp

deploy: lib/serializer.h lib/serializable.h
	cp ./lib/serializable.h /usr/include/serialize/serializable.h
	cp ./lib/serializer.h /usr/include/serialize/serializer.h
