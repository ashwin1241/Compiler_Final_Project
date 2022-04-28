#! /bin/bash
g++ lexer.cpp -o lexer
./lexer
g++ parser.cpp -o parser
./parser