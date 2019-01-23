#include <stdio.h>
#include "node.h"
#include <stdlib.h>
#include "y.tab.h"

int yyparse();


int main()
{
    yyparse();

    return 0;
}

// only for interpretor
int environment[32];

#define TRUE 1
#define FALSE 0

int visited[32]; // From 2 to 29 // 26 vars
int declared[32];

int accumulator1 = 28;
int accumulator2 = 29;
int accumulator3 = 30;

int getReserveRegistry()
{
    /* Go through all of our registries and find a empty one */
    for (int i = 2; i < 32; ++i)
        if (FALSE == declared[i] && FALSE == visited[i])
            return i;
}


void init()
{
    /* They are always declared soo... */
    declared[accumulator1] = 1;
    declared[accumulator2] = 1;
    declared[accumulator3] = 1;
}

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

int isAssignment(int type)
{
    if ( '=' == type || PEQ == type || MEQ == type || DEQ == type || SEQ == type )
        return TRUE;
    return FALSE;
}



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
                case BEQ: // >=
                case LEQ: // <=
                case EQ:  // ==
                case NEQ: // !=
                case OR:  // ||
                case AND: // &&
                case PEQ: // +=
                case SEQ: // -=
                case MEQ: // *=
                case DEQ: // /*
                case '>':
                case '<':
                case '=':
                case '/':
                case '*':
                case '-':
                case '+': 
                {

                    Operand leftOperand = generate(node->opr.operands[0]);
                    Operand rightOperand = generate(node->opr.operands[1]);

                    int leftReg, rightReg;
                    int returnedValue; // We in order to manage our memory we need to somehow find out the returned value
                    // of a expression 

                    if (VALUE == leftOperand.type)
                    {            
                        leftReg = getFreeAccumulator();

                        /* If our registry is -1 then assign one from the unused registers for variable declaration */
                        if ( leftReg == -1 )
                            leftReg = getReserveRegistry();


                        printf("li $%d %d\n", leftReg, leftOperand.data);
                        visited[leftReg] = TRUE;

                        /* Can't have a value to the left on a assignment */
                        if ( TRUE == isAssignment(node->opr.type) )
                        {
                            puts("Error, value not expected for the leftOperand of a assignment");
                            exit(-1);
                        }

                    } 
                    else if (REG == leftOperand.type)
                    {
                        if (TRUE == declared[leftOperand.data])
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

                        /* If our registry is -1 then assign one from the unused registers for variable declaration */
                        if ( rightReg == -1 )
                            rightReg = getReserveRegistry();

                        printf("li $%d %d\n", rightReg, rightOperand.data);
                        visited[rightReg] = TRUE;
                    
                    } 
                    else if (REG == rightOperand.type)
                    {
                        if (TRUE == declared[rightOperand.data])
                            rightReg = rightOperand.data;
                        else
                        {
                            puts("ERROR: Trying to use undeclared variable");
                            exit (-1);
                        }
                    }

                    int enteredSwitch = TRUE;
                    int returnAcumul = getFreeAccumulator();

                    if (returnAcumul == -1)
                        returnAcumul = leftReg;

                    if (leftReg != returnAcumul)
                        visited[leftReg] = FALSE;
                    visited[returnAcumul] = TRUE;

                    /* We always free the rightReg */
                    visited[rightReg] = FALSE;
                    
                    switch (node->opr.type)
                    {
                        case '-': printf("sub $%d, $%d, $%d\n",  returnAcumul, leftReg, rightReg);                            break;
                        case '+': printf("add $%d, $%d, $%d\n",  returnAcumul, leftReg, rightReg);                            break;
                        case '/': printf("div $%d, $%d, $%d\n",  returnAcumul, leftReg, rightReg);                            break;
                        case '*': printf("mult $%d, $%d, $%d\n", returnAcumul, leftReg, rightReg);                            break;
                        case NEQ: printf("xor $%d, $%d, $%d\n",  returnAcumul, leftReg, rightReg);                            break;
                        case OR : printf("or $%d, $%d, $%d\n",   returnAcumul, leftReg, rightReg);                            break;
                        case AND: printf("and $%d, $%d, $%d\n",  returnAcumul, leftReg, rightReg);                            break;
                        case '<': printf("slt $%d, $%d, $%d\n",  returnAcumul, leftReg, rightReg);                            break;
                        case PEQ: printf("add $%d, $%d $%d\n",   leftReg, leftReg, rightReg);                                 break;
                        case SEQ: printf("sub $%d, $%d, $%d\n",  leftReg, leftReg, rightReg);                                 break;
                        case MEQ: printf("mult $%d, $%d, $%d\n", leftReg, leftReg, rightReg);                                 break;
                        case DEQ: printf("div $%d, $%d, $%d\n",  leftReg, leftReg, rightReg);                                 break;
                        case '=': printf("li $%d, $%d\n",        leftReg, rightReg);                                          break;
                        case EQ:  
                        {
                            /* Place a 0 inside returnAcumul */
                            printf("li $%d, 0\n", returnAcumul);
                            
                            /* See if they are equal or not using bne - branch on not equal */
                            printf("bne $%d, $%d, L%d\n", leftReg, rightReg, labelCounter++);

                            /* If they were equal then our returnAcumul will be 1 (equal) */
                            printf("li $%d 1\n", returnAcumul);

                            /* Print the label it will jump to in case it's not equal */
                            printf("L%d: \n", labelCounter - 1);

                            break;
                        }
                        case '>':
                        {
                            /* Check if it's bigger */
                            printf("slt $%d, $%d, $%d\n",  returnAcumul, leftReg, rightReg);

                            /* If leftReg > rightReg go to lableCounter++ (everything is fine) */
                            printf("beq $%d, 1, L%d\n",  returnAcumul, labelCounter++);

                            /* If they aren't then return 0 I guess */
                            printf("li $%d 0\n", returnAcumul);

                            /* Finally, print the lable we promised */
                            printf("L%d: \n", labelCounter - 1);

                            break;
                        }
                        case LEQ:
                        {
                            /* Check if it's less than */
                            printf("slt $%d, $%d, $%d\n",  returnAcumul, leftReg, rightReg);

                            /* If leftReg < rightReg go to lableCounter++ (everything is fine) */
                            printf("beq $%d, 1, L%d\n",  returnAcumul, labelCounter++);
    
                            /* Set to 1 in preparation if they are equal (if everything will be fine) */
                            printf("li $%d, 1\n", returnAcumul);
                            
                            /* See if they are equal - branch if they are equal (everything is fine) */
                            printf("beq $%d, $%d, L%d\n", leftReg, rightReg, labelCounter - 1);

                            /* If it's not less than and not even equal then set the acumul to 0 (everything is not fine) */
                            printf("li $%d, 0\n", returnAcumul);
                            
                            /* Finally print the lable */
                            printf("L%d: \n", labelCounter - 1);

                            break;
                        }
                        case BEQ:
                        {
                            /* Check if it's less than */
                            printf("slt $%d, $%d, $%d\n",  rightReg, leftReg, rightReg);

                            /* Set to 0. Prepare the returnAcumul (in case everything is not fine) */
                            printf("li $%d, 0\n", returnAcumul);

                            /* If leftReg < rightReg go to lableCounter++ (everything is not fine) */
                            printf("beq $%d, 1, L%d\n",  rightReg, labelCounter++);
    
                            /* Set to 1 in preparation if they are equal (if everything will be fine) */
                            printf("li $%d, 1\n", returnAcumul);
                            
                            /* Finally print the lable */
                            printf("L%d: \n", labelCounter - 1);

                            break;
                        }
                        default: enteredSwitch = FALSE; break;
                    }
                                        
                    // printf("\n %d: %d %d: %d %d: %d \n\n", leftReg, visited[leftReg], rightReg, visited[rightReg], returnAcumul, visited[returnAcumul]);

                    return (Operand) { REG, returnAcumul };
                }
                case INT:
                {
                    Operand value = generate(node->opr.operands[0]);
                    
                    if ( FALSE == declared[value.data] )
                        declared[value.data] = TRUE;
                    else
                    {
                        puts("ERROR: Redeclaration of variable!");
                        exit(-1);
                    }

                    /* If we also have an expression */
                    if (node->opr.noOfOpr == 2)
                    {    
                        Operand expr = generate(node->opr.operands[1]);

                        if (VALUE == expr.type)
                            printf("li $%d %d\n", value.data, expr.data);
                        else
                        {
                            printf("li $%d $%d\n", value.data, expr.data);
                            declared[expr.data] = FALSE;
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
                    
                    if ( REG == eval.type)
                    {
                        printf("beq $%d, $%d, L%d\n", eval.data, accumulator1, labelCounter);
                    }
                    else if ( VALUE == eval.type )
                    {
                        printf("li $%d 1\n", accumulator2);
                        visited[accumulator2] = FALSE;

                        printf("beq $%d, $%d, L%d\n", accumulator2, accumulator1, labelCounter);
                    }

                    int endLabel = labelCounter++;
                    generate(node->opr.operands[1]);
                    freeAccumulators();

                    printf("j L%d \n", endLabel - 1);
                    printf("L%d: \n", endLabel);

                    break;
                }
                case DO:
                {
                    /* Label to which we will jump to */
                    printf("L%d: \n", labelCounter++);
                    
                    /* Generate the code */
                    generate(node->opr.operands[0]);
                    freeAccumulators();

                    /* The condition */
                    Operand eval = generate(node->opr.operands[1]);
                    printf("li $%d, 0\n", accumulator1);
                    visited[accumulator1] = FALSE;
                    
                    if ( REG == eval.type)
                    {
                        printf("beq $%d, $%d, L%d\n", eval.data, accumulator1, labelCounter);
                    }
                    else if ( VALUE == eval.type )
                    {
                        printf("li $%d 1\n", accumulator2);
                        visited[accumulator2] = FALSE;

                        printf("beq $%d, $%d, L%d\n", accumulator2, accumulator1, labelCounter);
                    }

                    int endLabel = labelCounter++;
                   
                    /* Finally, jump BACK UP */
                    printf("j L%d \n", endLabel - 1);
                    printf("L%d: \n", endLabel);

                    break;
                }
                case FOR:
                {
                    /* Label to which we will jump to */
                    printf("L%d: \n", labelCounter++);
                    
                    /* Execute the first expression */
                    Operand exprToWrite = generate(node->opr.operands[0]);
                    freeAccumulators();

                    /* This is the if from within the for basically */
                    Operand eval = generate(node->opr.operands[1]);
                    
                    printf("li $%d, 0\n", accumulator1);
                    visited[accumulator1] = FALSE;
                    
                    if ( REG == eval.type)
                    {
                        printf("beq $%d, $%d, L%d\n", eval.data, accumulator1, labelCounter);
                    }
                    else if ( VALUE == eval.type )
                    {
                        printf("li $%d 1\n", accumulator2);
                        visited[accumulator2] = FALSE;

                        printf("beq $%d, $%d, L%d\n", accumulator2, accumulator1, labelCounter);
                    }

                    int endLabel = labelCounter++;

                    /* Generate the code */
                    generate(node->opr.operands[3]);
                    freeAccumulators();

                    /* Before jumping generate the last bit of the for */
                    generate(node->opr.operands[2]);
                    freeAccumulators();

                    /* Finally, do the jump */
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