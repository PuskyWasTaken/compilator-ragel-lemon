#include <stdio.h>
#include <stdlib.h>
#include "node.h"

int yyparse();

// only for interpretor
int environment[32];

#define TRUE 1
#define FALSE 0

int visited[32]; // From 2 to 29 // 26 vars
int accumulator1 = 28;
int accumulator2 = 29;
int accumulator3 = 30;
//int accumulator4 = 31;

int registerIndex(char name)
{
    return name - 'a' + 2; // First 2 are reservered
}

int getFreeAccumulator()
{
    return visited[accumulator1] == FALSE ? accumulator1
         : visited[accumulator2] == FALSE ? accumulator2 
         : visited[accumulator3] == FALSE ? accumulator3 
         : -1;
}

void freeAccumulators()
{
    visited[accumulator1] = FALSE;
    visited[accumulator2] = FALSE;
    visited[accumulator3] = FALSE;
}

int labelCounter = 0;

// reg(variable_name) = variable_name - 'a';
// acumulator1, acumultator2


Operand generate(Node* node) {
    switch(node->type) {
        case CONST:
        {   
            return (Operand) { VALUE, node->constant.value };
        }
        case ID:
        {
            return (Operand) { REG , registerIndex(node->id.name) };
        }
        case OPR:
        {
            switch(node->opr.type) 
            {
                // case EQ :
                case NEQ:
                case OR:
                case AND:
                case '=':
                case '/':
                case '*':
                case '-':
                case '+': 
                {

                    Operand leftOperand = generate(node->opr.operands[0]);
                    Operand rightOperand = generate(node->opr.operands[1]);

                    int leftReg, rightReg;

                    if (VALUE == leftOperand.type)
                    {            
                        leftReg = getFreeAccumulator();
                        printf("li $%d %d\n", leftReg, leftOperand.data);
                        visited[leftReg] = TRUE;

                        /* Can't have a value to the left on a assignment */
                        if ( '=' == node->opr.type )
                        {
                            puts("Error, value not expected for the leftOperand of a assignment");
                            exit(-1);
                        }

                    } 
                    else if (REG == leftOperand.type)
                    {
                        if (TRUE == visited[leftOperand.data])
                            leftReg = leftOperand.data;
                        else
                        {
                            puts("ERROR: Trying to use undeclared variable");
                            exit (-1);
                        }
                    }

                    
                    if (VALUE == rightOperand.type)
                    {
                        rightReg = getFreeAccumulator();
                        printf("li $%d %d\n", rightReg, rightOperand.data);
                        visited[rightReg] = TRUE;
                    
                    } 
                    else if (REG == rightOperand.type)
                    {
                        if (TRUE == visited[rightOperand.data])
                            rightReg = rightOperand.data;
                        else
                        {
                            puts("ERROR: Trying to use undeclared variable");
                            exit (-1);
                        }
                    }

                    int enteredSwitch = FALSE;
                    int returnAcumul;
                    
                    /* So we don't bother to get a free Accumulator since we don't even use one for assignment */
                    if ( '=' != node->opr.type )
                    {
                        returnAcumul = getFreeAccumulator();
                        
                        if (returnAcumul == -1)
                            returnAcumul = leftReg;

                        enteredSwitch = TRUE;
                    }

                    switch (node->opr.type)
                    {
                         case '-': printf("sub $%d, $%d, $%d\n",  returnAcumul, leftReg, rightReg);  break;
                         case '+': printf("add $%d, $%d, $%d\n",  returnAcumul, leftReg, rightReg);  break;
                         case '/': printf("div $%d, $%d, $%d\n",  returnAcumul, leftReg, rightReg);  break;
                         case '*': printf("mult $%d, $%d, $%d\n", returnAcumul, leftReg, rightReg);  break;
                         case NEQ: printf("xor $%d, $%d, $%d\n",  returnAcumul, leftReg, rightReg);  break;
                         case OR : printf("or $%d, $%d, $%d\n",   returnAcumul, leftReg, rightReg);  break;
                         case AND: printf("and $%d, $%d, $%d\n",  returnAcumul, leftReg, rightReg);  break;
                         case '=': printf("li $%d, $%d\n",        leftReg, rightReg);                break;
                         default: enteredSwitch = FALSE; break;
                         // case EQ:  printf("xor $%d, $%d, $%d\n", accumulator3, leftReg, rightReg); break;
                    }
                    
                    if (TRUE == enteredSwitch)
                    {
                        if (leftReg != returnAcumul)
                            visited[leftReg] = FALSE;
                        visited[rightReg] = FALSE;
                        visited[returnAcumul] = TRUE;
                    }
                    
                    // printf("\n %d: %d %d: %d %d: %d \n\n", leftReg, visited[leftReg], rightReg, visited[rightReg], returnAcumul, visited[returnAcumul]);

                    return (Operand) { REG, returnAcumul };
                }
                case INT:
                {
                    Operand value = generate(node->opr.operands[0]);
                    
                    if ( FALSE == visited[value.data] )
                        visited[value.data] = TRUE;
                    else
                    {
                        puts("ERROR: Redeclaration of variable!");
                        exit(-1);
                    }

                    /* If we also have an expression */
                    if (node->opr.noOfOpr == 2)
                    {    
                        Operand expr = generate(node->opr.operands[1]);

                        if (VALUE ==expr.type)
                            printf("li $%d %d\n", value.data, expr.data);
                        else
                        {
                            printf("li $%d $%d\n", value.data, expr.data);
                            visited[expr.data] = FALSE;
                        }
                    }
                                        
                    break;
                }
                case IF:
                {   
                    Operand eval = generate(node->opr.operands[0]);
                    printf("li $%d, 0\n", accumulator1);
                    visited[accumulator1] = FALSE;

                    printf("beq $%d, $%d, L%d\n", eval.data, accumulator1, labelCounter);
                    int endLabel = ++labelCounter;
                    generate(node->opr.operands[1]);
                    freeAccumulators();
                    
                    /* If we have an else there will be 3 arguments */
                    if (node->opr.noOfOpr == 3)
                    {
                        printf("j L%d \n", labelCounter);
                        printf("L%d: \n", labelCounter - 1);
                        endLabel = ++labelCounter;
                        generate(node->opr.operands[2]);
                        freeAccumulators();
                        printf("L%d: \n", endLabel - 1);
                    }
                    else
                    {
                        printf("L%d: \n", endLabel - 1);
                    }
                    break;
                }
                case WHILE:
                {
                    /* Label to which we will jump to */
                    printf("L%d: \n", labelCounter++);
                    
                    Operand eval = generate(node->opr.operands[0]);
                    printf("li $%d, 0\n", accumulator1);
                    visited[accumulator1] = FALSE;
                    
                    printf("beq $%d, $%d, L%d\n", eval.data, accumulator1, labelCounter);
                    int endLabel = labelCounter++;
                    generate(node->opr.operands[1]);
                    freeAccumulators();

                    printf("j L%d \n", endLabel - 1);
                    printf("L%d: \n", endLabel);

                    break;
                }
                default: puts("Operator not implemented!, You should get to doing that soon!"); break;
            }
            break;
        }
    }

    // puts("Not implemented\n");
    // exit(0);
}