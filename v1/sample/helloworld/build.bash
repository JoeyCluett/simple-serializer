#!/bin/bash

OBJ="./../../lib/obj"
OPTS="-std=c++11 -march=native -O3 -I./../../lib/inc"
BOOST="-lboost_system -lboost_filesystem"

OTHER="main.cpp" # we will always need main in order to generate a final executable

OBJLIST=( "MultiType" "Document" "Database" )
for item in "${OBJLIST[@]}"; do
    OTHER="${OTHER} ${OBJ}/${item}.o"
done

# generate the final executable
g++ -o main ${OPTS} ${OTHER} ${BOOST}


