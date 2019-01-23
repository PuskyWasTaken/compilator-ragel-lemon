%{
    #include <stdlib.h>
    #include <stdio.h>
    #include <stdarg.h>
    #include "node.h"
    
    extern int yylineo;
    void yyerror(char* );

    int yylex();
    void freeNode(Node* node);
    Node* createOpr(int type, int noOfOpr, ...);
    Node* createId(char name);
    Node* createConstant(int value);    

    int generate(Node* node);
    void init();
    void freeAccumulators();

%}

%union
{
    int value;
    char name;
    Node* node;
};

%token <value> NUMBER
%token <name> IDEN
%token INT IF ELSE NEQ EQ AND OR WHILE PEQ SEQ MEQ DEQ DO FOR

%right '=' PEQ SEQ MEQ DEQ // -= += *= /=
%left OR
%left AND
%left EQ NEQ
%left '>' '<' LEQ BEQ // >= <=
%left '+' '-'
%left '*' '/'
%left '(' ')'

%type <node> expr statement variableDeclaration declaration block

%%

program: declarationList ;

declarationList:
    declarationList declaration { init(); generate($2); freeNode($2); }
    |
    ;

declaration:
    variableDeclaration { $$ = $1; }
    | statement         { $$ = $1; }
    ;

variableDeclaration:
    INT IDEN '=' expr ';' { $$ = createOpr(INT, 2, createId($2), $4); freeAccumulators(); }
    | INT IDEN ';'        { $$ = createOpr(INT, 1, createId($2)); freeAccumulators(); }
    ;

statement:
    expr ';'                                        { $$ = $1; freeAccumulators(); }
    | IF '(' expr ')' statement                     { $$ = createOpr(IF, 2, $3, $5); freeAccumulators(); }
    | IF '(' expr ')' statement ELSE statement      { $$ = createOpr(IF, 3, $3, $5, $7); freeAccumulators(); }
    | WHILE '(' expr ')' statement                  { $$ = createOpr(WHILE, 2, $3, $5); freeAccumulators(); }
    | DO statement WHILE '(' expr ')'               { $$ = createOpr(DO, 2, $2, $5); freeAccumulators(); }
    | FOR '(' expr ';' expr ';' expr ')' statement  { $$ = createOpr(FOR, 4, $3, $5, $7, $9); freeAccumulators(); }
    | '{' block '}'                                 { $$ = $2; }
    | ';'                                           { $$ = NULL;  freeAccumulators(); }
    ;

block:
    declaration                 { $$ = $1; }
    | block declaration         { $$ = createOpr(';', 2, $1, $2); }
    ;

expr:
    NUMBER              { $$ = createConstant($1); } 
    | IDEN              { $$ = createId($1); } 
    | IDEN '=' expr     { $$ = createOpr('=', 2, createId($1), $3); }
    | IDEN PEQ expr     { $$ = createOpr(PEQ, 2, createId($1), $3); }
    | IDEN SEQ expr     { $$ = createOpr(SEQ, 2, createId($1), $3); }
    | IDEN MEQ expr     { $$ = createOpr(MEQ, 2, createId($1), $3); }
    | IDEN DEQ expr     { $$ = createOpr(DEQ, 2, createId($1), $3); }
    | expr '+' expr     { $$ = createOpr('+', 2, $1, $3); }
    | expr '-' expr     { $$ = createOpr('-', 2, $1, $3); }
    | expr '*' expr     { $$ = createOpr('*', 2, $1, $3); }
    | expr '/' expr     { $$ = createOpr('/', 2, $1, $3); }
    | expr LEQ expr     { $$ = createOpr(LEQ, 2, $1, $3); }
    | expr BEQ expr     { $$ = createOpr(BEQ, 2, $1, $3); }
    | expr '<' expr     { $$ = createOpr('<', 2, $1, $3); }
    | expr '>' expr     { $$ = createOpr('>', 2, $1, $3); }
    | expr EQ  expr     { $$ = createOpr( EQ, 2, $1, $3); }
    | expr NEQ expr     { $$ = createOpr(NEQ, 2, $1, $3); }
    | expr AND expr     { $$ = createOpr(AND, 2, $1, $3); }
    | expr OR  expr     { $$ = createOpr( OR, 2, $1, $3); }
    | '(' expr ')'      { $$ = $2; }
    ;
    
%%

Node* createConstant(int value)
{
    Node* newNode = (Node*) malloc(sizeof(Node));

    newNode->type = CONST;
    newNode->constant.value = value;

    return newNode;  
}

Node* createId(char name)
{
    Node* newNode = (Node*) malloc(sizeof(Node));

    newNode->type = ID;
    newNode->id.name = name;

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

void yyerror(char* argv1)
{
    printf("ERROR: %s\n", argv1);
}