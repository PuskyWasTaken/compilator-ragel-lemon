#!/bin/sh
bison -y -d parser.y
flex lexer.l
gcc -g *.c
