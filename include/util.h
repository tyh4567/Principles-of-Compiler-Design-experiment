#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum{
    IDENFR,  //Ident
    INTCON,  //IntConst
    STRCON,  //FormatString
    MAINTK,  //main
    CONSTTK, //const
    INTTK,   //int
    BREAKTK, //break
    CONTINUETK, //continue
    IFTK,  //if
    ELSETK, //else
    NOT, //!
    AND, //&&
    OR, //||
    WHILETK, //while
    GETINTTK,//getint
    PRINTFTK,//printf
    RETURNTK,//return
    PLUS,//+
    MINU,//-
    VOIDTK,//void
    MULT,//*
    DIV,// /
    MOD,//%
    LSS,//<
    LEQ,//<=
    GRE,//>
    GEQ,//>=
    EQL,//==
    NEQ,//!=
    ASSIGN,//=
    SEMICN,//;
    COMMA,//,
    LPARENT,//(
    RPARENT,//)
    LBRACK,//[
    RBRACK,//]
    LBRACE,//{
    RBRACE, //}
    NOTYPE //空格
};

struct token
{
    int type; 
    char value[16];
};

void run_cffx(struct token* tokens_init);
void init_yffx(struct token* t1);
void run_yffx();
