#pragma once

typedef struct Const Const;
typedef struct Id Id;
typedef struct Opr Opr;
typedef struct Node Node;
typedef enum NodeType NodeType; 

struct Const
{
    int value;
};

struct Id
{
    char name;
};

struct Opr
{
    int type;
    int noOfOpr;

    Node* operands[];

};

enum NodeType
{
  CONST,
  ID,
  OPR

};


struct Node
{
    NodeType type;

    union
    {
        Const constant;
        Id id;
        Opr opr;
    };

};

typedef struct Operand Operand;
typedef enum OperandType OperandType;

enum OperandType {
    REG,
    VALUE
};

struct Operand {
    OperandType type; // Reg, Val
    int data;
};

