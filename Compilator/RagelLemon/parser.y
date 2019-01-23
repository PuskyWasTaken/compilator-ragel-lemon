%include 
{
	#include <assert.h>
	#include <stdio.h>
	#include <conio.h>
	#include <stdlib.h>
	#include <stdarg.h>
	#include "main.h"
	#include "node.h"

	char* concat(const char *s1, const char *s2)
	{
		char *result = malloc(strlen(s1) + strlen(s2) + 1);
		strcpy(result, s1);
		strcat(result, " ");
		strcat(result, s2);
		return result;
	}

	/* Functions */
	Node* createConstant(int value)
	{
		Node* newNode = (Node*) malloc(sizeof(Node));

		//char* tempChar = (char*)malloc(1);
		//tempChar[0] = value;

		newNode->type = CONST;
		newNode->constant.value = value;

		return newNode;  
	}

	Node* createId(int name)
	{
		Node* newNode = (Node*) malloc(sizeof(Node));

		newNode->type = ID;
		newNode->id.name = (char)name;

		return newNode;  
	}

	Node* createOpr(int type, int noOfOpr, ...)
	{
		Node* newNode = (Node*) malloc(sizeof(Node) + noOfOpr * sizeof(Node*));

		newNode->type = OPR;
		newNode->opr.noOfOpr = noOfOpr;
		newNode->opr.type = type;

		va_list operands;
		va_start(operands, noOfOpr);

		for (int i = 0; i < noOfOpr; ++i)
			newNode->opr.operands[i] = va_arg(operands, Node*);

		va_end(operands);

		return newNode;  
	}

	void freeNode(Node* node)
	{
		if ( OPR == node->type )
			for (int i = 0; i <  node->opr.noOfOpr; ++i)
				free(node->opr.operands[i]);

		free(node);
	}

	/* Functions for file output */
	void initFile(char*);
	void freeFile();

}

//=====< LEMON >=====//

%parse_accept { printf("The parser has completed successfully!\n"); freeFile(); }
%parse_failure { fprintf(stderr, "Parse failure!\n"); freeFile(); }
%syntax_error { fprintf(stderr, "Syntax Error!\n"); freeFile(); }

%start_symbol program

%token_type { int }
%default_type { int }

%type NUMBER { int }
%type IDEN { int }
//type INT IF ELSE NEQ EQ AND OR WHILE PEQ SEQ MEQ DEQ DO FOR

%right ASSIGN PEQ SEQ MEQ DEQ. // '='
%left OR.
%left AND.
%left EQ NEQ.
%left BTHAN LTHAN LEQ BEQ. // '>' '<' '<=' '>='
%left ADD SUB. // '+' '-'
%left MUL DIV. // '*' /
%left LPAREN RPAREN. // '(' ')'

// Token Types
%type expr {Node*}
%type statement {Node*}
%type variableDeclaration {Node*}
%type declaration {Node*}
%type block {Node*}
%type declarationList {Node*}

program ::= declarationList.

declarationList ::= declarationList declaration(A). { initFile("assembly.o"); initialize(); generate(A); freeNode(A); }
declarationList ::= .

declaration(A) ::= variableDeclaration(B).  { A = B; }
declaration(A) ::= statement(B).            { A = B; }

variableDeclaration(A) ::= INT IDEN(B) ASSIGN expr(C) SEMICOLON. { A = createOpr(INT, 2, createId(B), C); freeAccumulators();}
variableDeclaration(A) ::= INT IDEN(B) SEMICOLON.        { A = createOpr(INT, 1, createId(B)); freeAccumulators();}

statement(A) ::= expr(B) SEMICOLON.                                 							{ A = B; freeAccumulators(); }
statement(A) ::= IF LPAREN expr(B) RPAREN statement(C).                 						{ A = createOpr(IF, 2, B, C); freeAccumulators(); }
statement(A) ::= IF LPAREN expr(B) RPAREN statement(C) ELSE statement(D).  						{ A = createOpr(IF, 3, B, C, D); freeAccumulators(); }
statement(A) ::= WHILE LPAREN expr(B) RPAREN statement(C).              						{ A = createOpr(WHILE, 2, B, C); freeAccumulators(); } 
statement(A) ::= DO statement(B) WHILE LPAREN expr(C) RPAREN.               					{ A = createOpr(DO, 2, B, C); freeAccumulators(); }
statement(A) ::= FOR LPAREN expr(B) SEMICOLON expr(C) SEMICOLON expr(D) RPAREN statement(E). 	{ A = createOpr(FOR, 4, B, C, D, E); freeAccumulators(); }
statement(A) ::= LBRACKET block(B) RBRACKET.                             						{ A = B; }
statement(A) ::= SEMICOLON.                                       								{ A = NULL; freeAccumulators(); }

block(A) ::= declaration(B).                  { A = B; }
block(A) ::= block(B) declaration(C).         { A = createOpr(';', 2, B, C); }

expr(A) ::= IDEN(B) ASSIGN expr(C).     	{ A = createOpr('=', 2, createId(B), C); }
expr(A) ::= IDEN(B) PEQ expr(C).     	{ A = createOpr(PEQ, 2, createId(B), C); }
expr(A) ::= IDEN(B) SEQ expr(C).     	{ A = createOpr(SEQ, 2, createId(B), C); }
expr(A) ::= IDEN(B) MEQ expr(C).     	{ A = createOpr(MEQ, 2, createId(B), C); }
expr(A) ::= IDEN(B) DEQ expr(C).     	{ A = createOpr(DEQ, 2, createId(B), C); }
expr(A) ::= expr(B) ADD expr(C).   		{ A = createOpr('+', 2, B, C); }
expr(A) ::= expr(B) SUB expr(C).  		{ A = createOpr('-', 2, B, C); }
expr(A) ::= expr(B) MUL expr(C).  		{ A = createOpr('*', 2, B, C); }
expr(A) ::= expr(B) DIV expr(C).   		{ A = createOpr('/', 2, B, C); }
expr(A) ::= expr(B) LEQ expr(C).     	{ A = createOpr(LEQ, 2, B, C); }
expr(A) ::= expr(B) BEQ expr(C).     	{ A = createOpr(BEQ, 2, B, C); }
expr(A) ::= expr(B) LTHAN expr(C).     	{ A = createOpr('<', 2, B, C); }
expr(A) ::= expr(B) BTHAN expr(C).     	{ A = createOpr('>', 2, B, C); }
expr(A) ::= expr(B) EQ  expr(C).   		{ A = createOpr( EQ, 2, B, C); }
expr(A) ::= expr(B) NEQ expr(C).   		{ A = createOpr(NEQ, 2, B, C); }
expr(A) ::= expr(B) AND expr(C).   		{ A = createOpr(AND, 2, B, C); }
expr(A) ::= expr(B) OR  expr(C).   		{ A = createOpr( OR, 2, B, C); }
expr(A) ::= LPAREN expr(B) RPAREN.    	{ A = B; }
expr(A) ::= NUMBER(B).            		{ A = createConstant(B); } 
expr(A) ::= IDEN(B).              		{ A = createId(B); } 
