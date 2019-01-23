#include <stdio.h>
#include <malloc.h>
#include <conio.h>
#include <string.h>
#include <assert.h>
#include "parser.h"
#include "parser.c"

/* Lemon Stuff */
// #include "simple_c_grammar.h"

#define   YYCTYPE     char
#define   YYCURSOR    s->cur
#define   YYMARKER    s->ptr
#define MAXCHAR 1000

/* Functions to interface the lemon parser */
void *ParseAlloc();
void ParseFree();

/* Default Value */
const int END = 0;

typedef int bool;
#define true 1
#define false 0

/* Input start */
static char* p;

/* Input end */
static char* pe;
static char* eof;
static int cs;
static char* ts;
static char* te;
static int act;

%%{
  machine Lexer;
  write data;
    
  main := |*

	[1-9][0-9]*  =>   { ret = NUMBER; fbreak;};
	[0]			 =>   { ret = NUMBER; fbreak;};
	[a-z]		 =>   { ret = IDEN; fbreak;};

	'+='     =>   { ret = PEQ; fbreak;};
	'-='     =>   { ret = SEQ; fbreak;};
	'*='     =>   { ret = MEQ; fbreak;};
	'/='     =>   { ret = DEQ; fbreak;};

	'-' =>   { ret = SUB; fbreak;};
	'/' =>   { ret = DIV; fbreak;};
	'=' =>   { ret = ASSIGN; fbreak;};
	'+' =>   { ret = ADD; fbreak;};
	'*' =>   { ret = MUL; fbreak;};
	'(' =>   { ret = LPAREN; fbreak;};
	')' =>   { ret = RPAREN; fbreak;};
	';' =>   { ret = SEMICOLON; fbreak;};
	'{' =>   { ret = LBRACKET; fbreak;};
	'}' =>   { ret = RBRACKET; fbreak;};
	'>' =>   { ret = BTHAN; fbreak;};
	'<' =>   { ret = LTHAN; fbreak;};

	[ \t\n]+ ;
	'if'     =>   { ret = IF; fbreak;};
	'while'  =>   { ret = WHILE; fbreak;};
	'do'     =>   { ret = DO; fbreak;};
	'int'    =>   { ret = INT; fbreak;};
	'else'   =>   { ret = ELSE; fbreak;};
	'=='     =>   { ret = EQ; fbreak;};
	'!='     =>   { ret = NEQ; fbreak;};
	'&&'     =>   { ret = AND; fbreak;};
	'||'     =>   { ret = OR; fbreak;};
	'for'    =>   { ret = FOR; fbreak;};
	'>='     =>   { ret = LEQ; fbreak;};
	'<='     =>   { ret = BEQ; fbreak;};
  *|;
}%%


void init(char* p_, char* pe_)
{
	p = p_;
	pe = pe_;
	eof = pe_;
	%% write init;
}

bool isNumeric(const char* c)
{
	if ( *c >= '0' && *c <= '9' )
		return true;
	
	return false;
}

bool isCharacter(const char* c)
{
	if ( ( *c >= 'a' && *c <= 'z' ) || ( *c >= 'A' && *c <= 'Z' ) )
		return true;
	
	return false;
}

static int ret;

void writeExec()
{
	/* Execute */
	%% write exec;
}

void ragel(char* pathInput, char* pathOutput)
{
	/* Our Input File */
	FILE* infile;
	infile = fopen(pathInput, "r");

	/* Check the file was opened succesfully */
	if (infile == NULL)
	{
		printf("ERROR: Input FILE not found");
		return;
	}

	char* currentInput = NULL;
	int character = NULL;

	/* Output File */
	FILE* ofile;
	ofile = fopen(pathOutput, "w");


	while (true)
	{
		/* First input scan */
		int fileSize = 0;
		character = getc(infile);
		currentInput = (char*)malloc(sizeof(char));

		while ( character != -1 && character != ' ' && character != '\n' && character != '\t' )
		{
			if (character == -1)
				break;
			
			currentInput[fileSize] = (char)(character);
			++fileSize;
			
			/* Realloc */
			char* temp = (char*)malloc(fileSize);
			for (int i = 0; i < fileSize; ++i)
				temp[i] = currentInput[i];

			/* This crashes??? */
			//free(currentInput);
			currentInput = temp;

			character = getc(infile);
		}

		int size = 0;
		bool execute = false;
		bool haveExecuted = false;
		bool specialCase = false;
		char* input = NULL; char* previousInput = NULL;
		input = currentInput;

		//printf("\n%s", currentInput);

		for (int i = 0; i < fileSize; ++i)
		{
			input = &currentInput[i];
			
			/* Special Symbol cases */
			if ( *input == '!' || *input == '=' || *input == '|' || *input == '&' ||
					*input == '+' || *input == '-' || *input == '*' || *input == '/' ||
					*input == '>' || *input == '<' )
			{
				
				if ( (i + 1) < fileSize && 
					( currentInput[i+1] == '=' || currentInput[i+1] == '|' || currentInput[i+1] == '&' ) )	
				{
					previousInput = input;
					
					/* Reset ret */
					ret = END;

					/* Init */
					init(previousInput - size, previousInput);

					/* Execute */
					writeExec();

					if (i != 0)
					{
						fprintf(ofile, "%d ", ret);
						fprintf(ofile, "\n");
					}

					for (int i = size - 1; i >= 0; --i)
					{
						char c = *(previousInput - i - 1);
						fprintf(ofile, "%c", c);
					}
					
					
					input = &currentInput[++i];

					/* Reset ret */
					ret = END;

					/* Init */
					init(previousInput, input + 1);

					/* Execute */
					writeExec();

					fprintf(ofile, "\n");
					fprintf(ofile, "%d ", ret);

					char c = *previousInput;
					fprintf(ofile, "%c", c);

					c = *input;
					fprintf(ofile, "%c", c);

					size = 0;
					specialCase = true;
					
				}
				else
				{
					execute = true;
				}
			}

			else if (previousInput == NULL)
			{
				size++;
			}
			/* Check for number */
			else if (isNumeric(input))
			{
				/* If we had a symbol before, separate */
				if (!isCharacter(previousInput) && !isNumeric(previousInput))
				{
					execute = true;
				}
				else
				{
					size++;
				}
			}

			/* Check for character */
			else if (isCharacter(input))
			{
				/* If we didn't have a character before, separate */
				if (!isCharacter(previousInput))
				{
					execute = true;
				}
				else
				{
					size++;
				}
			}

			/* If not, it's a symbol */
			else
			{	
				execute = true;
			}

			previousInput = input;

			if (i == fileSize - 1 && specialCase == false )
			{
				if (execute == false)
				{
					/* Print to file */
					printf("\n");
					
					/* Reset ret */
					ret = END;
					
					/* Init */
					init(previousInput - i, previousInput + 1);
					
					/* Execute */
					writeExec();

					fprintf(ofile, "\n");
					fprintf(ofile, "%d ", ret);
						
					for (int i = size - 1; i >= 0; --i)
					{						
						char c = *(previousInput - i);
						fprintf(ofile, "%c", c);
					}

					// if ( previousInput[size - 1] >= 'a' && previousInput[size - 1] <= 'z' )
					// {
						// fprintf(ofile, "\n0 0");
					// }
				}
				else if (execute == true)
				{
					if (haveExecuted == true)
					{
						execute = false;

						/* Reset ret */
						ret = END;
						
						/* Init */
						init(previousInput, previousInput + 1);
						
						/* Execute */
						writeExec();

						fprintf(ofile, "\n");
						fprintf(ofile, "%d ", ret);

						char c = *(input);
						fprintf(ofile, "%c", c);
					}
				}
			}
			
			
			if (execute == true)
			{
				/* Reset size and prepare for exec */
				execute = false;
				if (haveExecuted == false)
					haveExecuted = true;

				/* Reset ret */
				ret = END;

				/* Init */
				init(previousInput - size, previousInput + 1);

				/* Execute */
				writeExec();

				if (size != 0)
				{
					fprintf(ofile, "\n");
					fprintf(ofile, "%d ", ret);
				}

				for (int i = size - 1; i >= 0; --i)
				{
					char c = *(previousInput - i - 1);
					fprintf(ofile, "%c", c);
				}

				/* Reset ret */
				ret = END;
				
				/* Init */
				init(previousInput, previousInput + 1);

				/* Execute */
				writeExec();

				fprintf(ofile, "\n");
				fprintf(ofile, "%d ", ret);

				char c = *(input);
				fprintf(ofile, "%c", c);
				
				size = 0;
			}
		}

		if (character == -1)
			break;
	}
	
	/* This is needed for the END_TOKEN */
	// fprintf(ofile, "\n");
	// char endToken[5];
	// itoa(END_TOKEN, endToken, 10);
	// fprintf(ofile, "%d %d", endToken, endToken);

	fprintf(ofile, "\n0 0\n");
	
	fclose(infile);
	fclose(ofile);
}

void lemon(char* tokenInput, char* traceOutput)
{
	FILE *fp, *traceFile;
	long size;
	char *buff, *buff_end;
	char* name_str = (char*)malloc(MAXCHAR);
	size_t bytes;
	int name_length, token;
	void *parser;

	/* Open input file */
	fp = fopen(tokenInput, "r");
	if (fp == NULL)
	{
		fprintf(stderr, "Can't open input file!\n");
		exit(-1);
	}

	/* Open trace file */
	traceFile = fopen(traceOutput, "w");
	if (traceFile == NULL)
	{
		fprintf(stderr, "Can't open trace file!\n");
		exit(-1);
	}

	/* Get file size */
	fseek(fp, 0L, SEEK_END);
	size = ftell(fp);
	rewind(fp);

	/* Create parser and set up tracing */
	parser = ParseAlloc(malloc);
	ParseTrace(traceFile, "parser >> ");


	while ((fgets(name_str, MAXCHAR, fp) != NULL))
	{
		fprintf(traceFile, "%s", name_str);

		char copy[MAXCHAR];
		strcpy(copy, name_str);
		strtok(copy, " ");
		int token = atoi(copy);

		char* ptr = strchr(name_str, ' ');
		
		if (ptr == NULL || *ptr == '\n')
			continue;

		name_str = ptr + 1;
		strtok(name_str, "\n");

		/* Send strings to the parser with NAME tokens */
		if ( token == NUMBER )
		{
			name_str[strlen(name_str)] = '\0';
			
			Parse(parser, token, atoi(name_str));
		}
		else if ( token == IDEN )
		{
			name_str[strlen(name_str)] = '\0';
			
			Parse(parser, token, (int)(name_str[0]));
		}
		else
		{
			Parse(parser, token, 0);
		}
	}

	//Parse(parser, 0, 0);

	/* Deallocate parser */
	ParseFree(parser, free);
	fclose(fp);
}

int main(int argc, char *argv[])
{
	if ( argc >= 4 )
	{	
		/* Ragel Stuff (Lexer) */
		ragel(argv[1], argv[2]);
		
		/* Lemon Stuff (Parser) */
		lemon(argv[2], argv[3]);
	}
	else
	{
		/* Ragel Stuff (Lexer) */
		ragel("in.txt", "out.txt");
		
		/* Lemon Stuff (Parser) */
		lemon("out.txt", "trace.txt");
	}
}