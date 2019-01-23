
%{
    #include <stdlib.h>
    #include "node.h" /* Must be here beffore y.yab */
    #include "y.tab.h"

    int yylineo;
    void yyerror(char* );    

%}

%%

[1-9][0-9]*     { yylval.value = atoi(yytext); return NUMBER; }
[0]             { yylval.value = atoi(yytext); return NUMBER; }
[a-z]           { yylval.name = *yytext; return IDEN; }
[-/=+*)(;}{><]    { return *yytext; }   
[ \t\n]+ ;
"+="    { return PEQ;   }
"-="    { return SEQ;   }
"*="    { return MEQ;   }
"/="    { return DEQ;   }
"if"    { return IF;    }
"while" { return WHILE; }
"do"    { return DO;    }
"int"   { return INT;   }
"else"  { return ELSE;  }
"=="    { return EQ;    }
"!="    { return NEQ;   }
"&&"    { return AND;   }
"||"    { return OR;    }
"for"   { return FOR;   }
"<="    { return LEQ;   }
">="    { return BEQ;   }
%%

int yywrap()
{
    return 1;
}