
#line 1 "lexer.rl"
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


#line 43 "lexer.c"
static const char _Lexer_actions[] = {
	0, 1, 0, 1, 1, 1, 2, 1, 
	3, 1, 4, 1, 5, 1, 6, 1, 
	7, 1, 8, 1, 9, 1, 10, 1, 
	11, 1, 12, 1, 13, 1, 14, 1, 
	15, 1, 16, 1, 17, 1, 18, 1, 
	19, 1, 20, 1, 21, 1, 22, 1, 
	23, 1, 24, 1, 25, 1, 26, 1, 
	27, 1, 28, 1, 29, 1, 30, 1, 
	31, 1, 32, 1, 33, 1, 34, 1, 
	35, 1, 36
};

static const char _Lexer_key_offsets[] = {
	0, 0, 1, 2, 3, 4, 5, 6, 
	7, 8, 9, 10, 38, 41, 42, 43, 
	44, 45, 47, 48, 49, 50, 51, 52, 
	53, 55
};

static const char _Lexer_trans_keys[] = {
	61, 38, 115, 101, 114, 116, 105, 108, 
	101, 124, 32, 33, 38, 40, 41, 42, 
	43, 45, 47, 48, 59, 60, 61, 62, 
	100, 101, 102, 105, 119, 123, 124, 125, 
	9, 10, 49, 57, 97, 122, 32, 9, 
	10, 61, 61, 61, 61, 48, 57, 61, 
	61, 61, 111, 108, 111, 102, 110, 104, 
	0
};

static const char _Lexer_single_lengths[] = {
	0, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 22, 1, 1, 1, 1, 
	1, 0, 1, 1, 1, 1, 1, 1, 
	2, 1
};

static const char _Lexer_range_lengths[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 3, 1, 0, 0, 0, 
	0, 1, 0, 0, 0, 0, 0, 0, 
	0, 0
};

static const char _Lexer_index_offsets[] = {
	0, 0, 2, 4, 6, 8, 10, 12, 
	14, 16, 18, 20, 46, 49, 51, 53, 
	55, 57, 59, 61, 63, 65, 67, 69, 
	71, 74
};

static const char _Lexer_trans_targs[] = {
	11, 0, 11, 0, 4, 11, 11, 11, 
	11, 11, 11, 11, 8, 11, 9, 11, 
	11, 11, 11, 0, 12, 1, 2, 11, 
	11, 13, 14, 15, 16, 11, 11, 18, 
	19, 20, 21, 22, 23, 24, 25, 11, 
	10, 11, 12, 17, 11, 0, 12, 12, 
	11, 11, 11, 11, 11, 11, 11, 11, 
	11, 17, 11, 11, 11, 11, 11, 11, 
	11, 11, 11, 3, 11, 5, 11, 11, 
	6, 11, 7, 11, 11, 11, 11, 11, 
	11, 11, 11, 11, 11, 11, 11, 11, 
	11, 11, 11, 11, 11, 11, 11, 11, 
	11, 0
};

static const char _Lexer_trans_actions[] = {
	41, 0, 43, 0, 0, 73, 37, 73, 
	47, 73, 35, 73, 0, 73, 0, 73, 
	31, 73, 45, 0, 0, 0, 0, 19, 
	21, 0, 0, 0, 0, 7, 23, 0, 
	0, 0, 0, 5, 5, 5, 5, 25, 
	0, 27, 0, 0, 9, 0, 0, 0, 
	71, 15, 65, 11, 63, 13, 57, 17, 
	59, 0, 53, 51, 69, 39, 61, 49, 
	67, 33, 55, 0, 55, 0, 55, 29, 
	0, 55, 0, 55, 73, 73, 73, 73, 
	73, 73, 73, 71, 65, 63, 57, 59, 
	53, 69, 61, 67, 55, 55, 55, 55, 
	55, 0
};

static const char _Lexer_to_state_actions[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 1, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0
};

static const char _Lexer_from_state_actions[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 3, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0
};

static const char _Lexer_eof_trans[] = {
	0, 0, 0, 83, 83, 83, 83, 83, 
	83, 83, 0, 0, 84, 85, 86, 87, 
	88, 89, 90, 91, 92, 97, 97, 97, 
	97, 97
};

static const int Lexer_start = 11;
static const int Lexer_first_final = 11;
static const int Lexer_error = 0;

static const int Lexer_en_main = 11;


#line 81 "lexer.rl"



void init(char* p_, char* pe_)
{
	p = p_;
	pe = pe_;
	eof = pe_;
	
#line 166 "lexer.c"
	{
	cs = Lexer_start;
	ts = 0;
	te = 0;
	act = 0;
	}

#line 90 "lexer.rl"
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
	
#line 199 "lexer.c"
	{
	int _klen;
	unsigned int _trans;
	const char *_acts;
	unsigned int _nacts;
	const char *_keys;

	if ( p == pe )
		goto _test_eof;
	if ( cs == 0 )
		goto _out;
_resume:
	_acts = _Lexer_actions + _Lexer_from_state_actions[cs];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 ) {
		switch ( *_acts++ ) {
	case 1:
#line 1 "NONE"
	{ts = p;}
	break;
#line 220 "lexer.c"
		}
	}

	_keys = _Lexer_trans_keys + _Lexer_key_offsets[cs];
	_trans = _Lexer_index_offsets[cs];

	_klen = _Lexer_single_lengths[cs];
	if ( _klen > 0 ) {
		const char *_lower = _keys;
		const char *_mid;
		const char *_upper = _keys + _klen - 1;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + ((_upper-_lower) >> 1);
			if ( (*p) < *_mid )
				_upper = _mid - 1;
			else if ( (*p) > *_mid )
				_lower = _mid + 1;
			else {
				_trans += (unsigned int)(_mid - _keys);
				goto _match;
			}
		}
		_keys += _klen;
		_trans += _klen;
	}

	_klen = _Lexer_range_lengths[cs];
	if ( _klen > 0 ) {
		const char *_lower = _keys;
		const char *_mid;
		const char *_upper = _keys + (_klen<<1) - 2;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + (((_upper-_lower) >> 1) & ~1);
			if ( (*p) < _mid[0] )
				_upper = _mid - 2;
			else if ( (*p) > _mid[1] )
				_lower = _mid + 2;
			else {
				_trans += (unsigned int)((_mid - _keys)>>1);
				goto _match;
			}
		}
		_trans += _klen;
	}

_match:
_eof_trans:
	cs = _Lexer_trans_targs[_trans];

	if ( _Lexer_trans_actions[_trans] == 0 )
		goto _again;

	_acts = _Lexer_actions + _Lexer_trans_actions[_trans];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 )
	{
		switch ( *_acts++ )
		{
	case 2:
#line 1 "NONE"
	{te = p+1;}
	break;
	case 3:
#line 46 "lexer.rl"
	{te = p+1;{ ret = NUMBER; {p++; goto _out; }}}
	break;
	case 4:
#line 47 "lexer.rl"
	{te = p+1;{ ret = IDEN; {p++; goto _out; }}}
	break;
	case 5:
#line 49 "lexer.rl"
	{te = p+1;{ ret = PEQ; {p++; goto _out; }}}
	break;
	case 6:
#line 50 "lexer.rl"
	{te = p+1;{ ret = SEQ; {p++; goto _out; }}}
	break;
	case 7:
#line 51 "lexer.rl"
	{te = p+1;{ ret = MEQ; {p++; goto _out; }}}
	break;
	case 8:
#line 52 "lexer.rl"
	{te = p+1;{ ret = DEQ; {p++; goto _out; }}}
	break;
	case 9:
#line 59 "lexer.rl"
	{te = p+1;{ ret = LPAREN; {p++; goto _out; }}}
	break;
	case 10:
#line 60 "lexer.rl"
	{te = p+1;{ ret = RPAREN; {p++; goto _out; }}}
	break;
	case 11:
#line 61 "lexer.rl"
	{te = p+1;{ ret = SEMICOLON; {p++; goto _out; }}}
	break;
	case 12:
#line 62 "lexer.rl"
	{te = p+1;{ ret = LBRACKET; {p++; goto _out; }}}
	break;
	case 13:
#line 63 "lexer.rl"
	{te = p+1;{ ret = RBRACKET; {p++; goto _out; }}}
	break;
	case 14:
#line 68 "lexer.rl"
	{te = p+1;{ ret = IF; {p++; goto _out; }}}
	break;
	case 15:
#line 69 "lexer.rl"
	{te = p+1;{ ret = WHILE; {p++; goto _out; }}}
	break;
	case 16:
#line 70 "lexer.rl"
	{te = p+1;{ ret = DO; {p++; goto _out; }}}
	break;
	case 17:
#line 71 "lexer.rl"
	{te = p+1;{ ret = INT; {p++; goto _out; }}}
	break;
	case 18:
#line 72 "lexer.rl"
	{te = p+1;{ ret = ELSE; {p++; goto _out; }}}
	break;
	case 19:
#line 73 "lexer.rl"
	{te = p+1;{ ret = EQ; {p++; goto _out; }}}
	break;
	case 20:
#line 74 "lexer.rl"
	{te = p+1;{ ret = NEQ; {p++; goto _out; }}}
	break;
	case 21:
#line 75 "lexer.rl"
	{te = p+1;{ ret = AND; {p++; goto _out; }}}
	break;
	case 22:
#line 76 "lexer.rl"
	{te = p+1;{ ret = OR; {p++; goto _out; }}}
	break;
	case 23:
#line 77 "lexer.rl"
	{te = p+1;{ ret = FOR; {p++; goto _out; }}}
	break;
	case 24:
#line 78 "lexer.rl"
	{te = p+1;{ ret = LEQ; {p++; goto _out; }}}
	break;
	case 25:
#line 79 "lexer.rl"
	{te = p+1;{ ret = BEQ; {p++; goto _out; }}}
	break;
	case 26:
#line 45 "lexer.rl"
	{te = p;p--;{ ret = NUMBER; {p++; goto _out; }}}
	break;
	case 27:
#line 47 "lexer.rl"
	{te = p;p--;{ ret = IDEN; {p++; goto _out; }}}
	break;
	case 28:
#line 54 "lexer.rl"
	{te = p;p--;{ ret = SUB; {p++; goto _out; }}}
	break;
	case 29:
#line 55 "lexer.rl"
	{te = p;p--;{ ret = DIV; {p++; goto _out; }}}
	break;
	case 30:
#line 56 "lexer.rl"
	{te = p;p--;{ ret = ASSIGN; {p++; goto _out; }}}
	break;
	case 31:
#line 57 "lexer.rl"
	{te = p;p--;{ ret = ADD; {p++; goto _out; }}}
	break;
	case 32:
#line 58 "lexer.rl"
	{te = p;p--;{ ret = MUL; {p++; goto _out; }}}
	break;
	case 33:
#line 64 "lexer.rl"
	{te = p;p--;{ ret = BTHAN; {p++; goto _out; }}}
	break;
	case 34:
#line 65 "lexer.rl"
	{te = p;p--;{ ret = LTHAN; {p++; goto _out; }}}
	break;
	case 35:
#line 67 "lexer.rl"
	{te = p;p--;}
	break;
	case 36:
#line 47 "lexer.rl"
	{{p = ((te))-1;}{ ret = IDEN; {p++; goto _out; }}}
	break;
#line 425 "lexer.c"
		}
	}

_again:
	_acts = _Lexer_actions + _Lexer_to_state_actions[cs];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 ) {
		switch ( *_acts++ ) {
	case 0:
#line 1 "NONE"
	{ts = 0;}
	break;
#line 438 "lexer.c"
		}
	}

	if ( cs == 0 )
		goto _out;
	if ( ++p != pe )
		goto _resume;
	_test_eof: {}
	if ( p == eof )
	{
	if ( _Lexer_eof_trans[cs] > 0 ) {
		_trans = _Lexer_eof_trans[cs] - 1;
		goto _eof_trans;
	}
	}

	_out: {}
	}

#line 114 "lexer.rl"
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