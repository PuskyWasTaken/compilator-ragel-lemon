#!/bin/sh
ragel lexer.rl
lem parser.y
gcc lexer.c

