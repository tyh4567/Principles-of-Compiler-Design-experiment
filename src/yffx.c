#include "../include/util.h"


struct token* next; 
struct token* nextnext; 
struct token* nextnextnext; 
struct token tokens_yffx[1000000];

void init_yffx(struct token* t1);
void run_yffx();
void looknextnextnext();
void looknextnext();
void nextpoint(); 
void parserCompUnit();
void parserDecl();
void parserConstDecl();
void parserBType();
void parserConstDef();
void parserConstInitVal();
void parserVarDecl();
void parserVarDef();
void parserInitVal();
void parserFuncDef();
void parserMainFuncDef();
void parserFuncType();
void parserFuncFParams();
void parserFuncFParam();
void parserBlock();
void parserBlockItem();
void parserStmt();
void parserExp();
void parserCond();
void parserLVal();
void parserPrimaryExp();
void parserNumber();
void parserUnaryExp();
void parserUnaryOp();
void parserFuncRParams();
void parserMulExp();
void parserAddExp();
void parserRelExp();
void parserEqExp();
void parserLAndExp();
void parserLOrExp();
void parserConstExp();

#define ruleBType (next->type == INTTK)
#define ruleVarDecl (next->type == INTTK)
#define ruleVarDef (next->type == IDENFR)
#define ruleConstDef (next->type == IDENFR)
#define ruleMainFuncDef (next->type == INTTK)
#define ruleFuncType (next->type == VOIDTK || next->type == INTTK)
#define ruleBlock (next->type == LBRACE)
#define ruleLVal (next->type == IDENFR)
#define rulePrimaryExp (next->type == INTCON || next->type == IDENFR || next->type == LPARENT)
#define ruleNumber (next->type == INTCON)
#define ruleUnaryOp (next->type == PLUS || next->type == MINU || next->type == NOT)
#define ruleConstDecl (next->type == CONSTTK)
#define ruleStmt (next->type == IDENFR || next->type == INTCON || next->type == IDENFR || next->type == LPARENT || next->type == LBRACE || next->type == SEMICN || next->type == IFTK  || next->type == WHILETK || next->type == BREAKTK || next->type == CONTINUETK || next->type == RETURNTK || next->type == PRINTFTK)

#define ruleCompUnit (ruleDecl || ruleFuncDef || ruleMainFuncDef)
#define ruleDecl (ruleConstDecl || ruleVarDecl)

#define ruleInitVal (ruleExp || next->type == LBRACE)//(next->type == INTCON || next->type == IDENFR || next->type == LPARENT || next->type == PLUS || next->type == MINU || next->type == NOT || next->type == LBRACE)
#define ruleFuncDef (ruleFuncType)//(next->type == VOIDTK || next->type == INTTK)

#define ruleFuncFParams (ruleFuncFParam)//(next->type == INTTK)
#define ruleFuncFParam (ruleBType)//(next->type == INTTK)
#define ruleBlockItem (ruleDecl || ruleStmt)//(next->type == CONSTTK || next->type == INTTK || next->type == IDENFR || next->type == INTCON || next->type == IDENFR || next->type == LPARENT || next->type == LBRACE || next->type == SEMICN || next->type == IFTK  || next->type == WHILETK || next->type == BREAKTK || next->type == RETURNTK || next->type == PRINTFTK)
#define ruleCond (ruleLOrExp)//(next->type == INTCON || next->type == IDENFR || next->type == LPARENT || next->type == PLUS || next->type == MINU || next->type == NOT)
#define ruleUnaryExp (rulePrimaryExp || ruleUnaryOp || next->type == IDENFR)  //(next->type == INTCON || next->type == IDENFR || next->type == LPARENT || next->type == PLUS || next->type == MINU || next->type == NOT)
#define ruleFuncRParams (ruleExp)//(next->type == INTCON || next->type == IDENFR || next->type == LPARENT || next->type == PLUS || next->type == MINU || next->type == NOT)
#define ruleMulExp (ruleUnaryExp)//(next->type == INTCON || next->type == IDENFR || next->type == LPARENT || next->type == PLUS || next->type == MINU || next->type == NOT)
#define ruleAddExp (ruleMulExp)//(next->type == INTCON || next->type == IDENFR || next->type == LPARENT || next->type == PLUS || next->type == MINU || next->type == NOT)
#define ruleExp  (ruleAddExp)// (next->type == INTCON || next->type == IDENFR || next->type == LPARENT || next->type == PLUS || next->type == MINU || next->type == NOT)
#define ruleRelExp (ruleAddExp)//(next->type == INTCON || next->type == IDENFR || next->type == LPARENT || next->type == PLUS || next->type == MINU || next->type == NOT)
#define ruleConstExp (ruleAddExp)//(next->type == INTCON || next->type == IDENFR || next->type == LPARENT || next->type == PLUS || next->type == MINU || next->type == NOT)
#define ruleEqExp (ruleRelExp) //(next->type == INTCON || next->type == IDENFR || next->type == LPARENT || next->type == PLUS || next->type == MINU || next->type == NOT)
#define ruleLAndExp (ruleEqExp)//(next->type == INTCON || next->type == IDENFR || next->type == LPARENT || next->type == PLUS || next->type == MINU || next->type == NOT)
#define ruleLOrExp (ruleLAndExp)//(next->type == INTCON || next->type == IDENFR || next->type == LPARENT || next->type == PLUS || next->type == MINU || next->type == NOT)
#define ruleConstInitVal (ruleConstExp || next->type == LBRACE) //(next->type == LBRACE || next->type == IDENFR || next->type == LPARENT)

void init_yffx(struct token* t1)
{
    for(int i = 0; i < 1000000; i++)
    {
        tokens_yffx[i] = t1[i];
    }
    next = tokens_yffx;
}

void run_yffx()
{
    parserCompUnit();
    printf("语法分析成功\n");
}

void nextpoint()
{
    switch(next->type)
        {
            case IDENFR     : printf("IDENFR     :   %s\n", next->value); break;
            case INTCON     : printf("INTCON     :   %s\n", next->value); break;
            case STRCON     : printf("STRCON     :   %s\n", next->value); break;
            case MAINTK     : printf("MAINTK     :   %s\n", next->value); break;
            case CONSTTK    : printf("CONSTTK    :   %s\n", next->value); break;
            case INTTK      : printf("INTTK      :   %s\n", next->value); break;
            case BREAKTK    : printf("BREAKTK    :   %s\n", next->value); break;
            case CONTINUETK : printf("CONTINUETK :   %s\n", next->value); break;
            case IFTK       : printf("IFTK       :   %s\n", next->value); break;
            case ELSETK     : printf("ELSETK     :   %s\n", next->value); break;
            case NOT        : printf("NOT        :   %s\n", next->value); break;
            case AND        : printf("AND        :   %s\n", next->value); break;
            case OR         : printf("OR         :   %s\n", next->value); break;
            case WHILETK    : printf("WHILETK    :   %s\n", next->value); break;
            case GETINTTK   : printf("GETINTTK   :   %s\n", next->value); break;
            case PRINTFTK   : printf("PRINTFTK   :   %s\n", next->value); break;
            case RETURNTK   : printf("RETURNTK   :   %s\n", next->value); break;
            case PLUS       : printf("PLUS       :   %s\n", next->value); break;
            case MINU       : printf("MINU       :   %s\n", next->value); break;
            case VOIDTK     : printf("VOIDTK     :   %s\n", next->value); break;
            case MULT       : printf("MULT       :   %s\n", next->value); break;
            case DIV        : printf("DIV        :   %s\n", next->value); break;
            case MOD        : printf("MOD        :   %s\n", next->value); break;
            case LSS        : printf("LSS        :   %s\n", next->value); break;
            case LEQ        : printf("LEQ        :   %s\n", next->value); break;
            case GRE        : printf("GRE        :   %s\n", next->value); break;
            case GEQ        : printf("GEQ        :   %s\n", next->value); break;
            case EQL        : printf("EQL        :   %s\n", next->value); break;
            case NEQ        : printf("NEQ        :   %s\n", next->value); break;
            case ASSIGN     : printf("ASSIGN     :   %s\n", next->value); break;
            case SEMICN     : printf("SEMICN     :   %s\n", next->value); break;
            case COMMA      : printf("COMMA      :   %s\n", next->value); break;
            case LPARENT    : printf("LPARENT    :   %s\n", next->value); break;
            case RPARENT    : printf("RPARENT    :   %s\n", next->value); break;
            case LBRACK     : printf("LBRACK     :   %s\n", next->value); break;
            case RBRACK     : printf("RBRACK     :   %s\n", next->value); break;
            case LBRACE     : printf("LBRACE     :   %s\n", next->value); break;
            case RBRACE     : printf("RBRACE     :   %s\n", next->value); break;
            case NOTYPE     : printf("NOTYPE     :   %s\n", next->value); break;
        }
    next += 1;
}

void looknextnext()
{
    nextnext = next + 1;
}

void looknextnextnext()
{
    nextnextnext = next + 2;
}


void parserCompUnit()
{
    while(next->type == CONSTTK || (next->type == INTTK && nextnext->type == IDENFR && (nextnextnext->type == LBRACK || nextnextnext->type == ASSIGN)))
    {

        parserDecl();
        looknextnext(); 
        looknextnextnext();
    }

    looknextnext(); 
    looknextnextnext();
    while((next->type == VOIDTK || next->type == INTTK) && nextnext->type == IDENFR && nextnextnext->type == LPARENT)
    {
        printf("#$#$#\n");
        parserFuncDef();
        looknextnext(); 
        looknextnextnext();
    }

    if(next->type == INTTK)
    {
        printf("#$#$#1\n");
        parserMainFuncDef();
    }
    else
    {
        printf("error in : %s", next->value); exit(-1); 
    }
    printf("<CompUnit>\n");
    return;
    // if(next->type == CONSTTK)
    // {
    //     parserDecl();
    // }
    // else if(next->type == VOIDTK)
    // {
    //     parserFuncDef();
    // }
    // else if(next->type == INTTK)
    // {
    //     looknextnext();
    //     if(nextnext->type == MAINTK)
    //     {
    //         parserMainFuncDef();
    //     }
    //     else if(nextnext->type == IDENFR)
    //     {
    //         looknextnextnext();
    //         if(nextnextnext->type == LPARENT)
    //         {
    //             parserFuncDef();
    //         }
    //         else
    //         {
    //             parserDecl();
    //         }
    //     }
    //     else
    //     {
    //         printf("error in : %s", next->value); exit(-1); 
    //     }
    // }
    // else
    // {
    //     printf("error in : %s", next->value); exit(-1); 
    // }
    // printf("<CompUnit>\n");
    // return;
}

void parserDecl() //Decl first(next->type == CONSTTK || next->type == INTTK)
{
    if(ruleConstDecl) 
    {
        parserConstDecl();  
    }
    else if(ruleVarDecl)
    {
        parserVarDecl(); 
    }
    else 
    {
        printf("error in : %s", next->value); exit(-1);  
    }
    //printf("<Decl>\n");
    return; 
}

void parserConstDecl()
{
    if(next->type == CONSTTK)
    {
        nextpoint();
    }
    else 
    {
        printf("error in : %s", next->value); exit(-1);  
    }
    if(ruleBType) ///hit btype
    {
        parserBType();
    }
    else
    {
        printf("error in : %s", next->value); exit(-1);  
    }
    if(ruleConstDef) //hit constdef
    {
        parserConstDef();
    }
    else
    {
        printf("error in : %s", next->value); exit(-1);  
    }
    while(next->type == COMMA)
    {
        nextpoint(); 
        if(ruleConstDef) //hit constdef
        {
            parserConstDef();
        }
        else 
        {
            printf("error in : %s", next->value); exit(-1);  
        }
    }
    if(next->type == SEMICN)
    {
        nextpoint(); 
    }
    else
    {
        printf("error in : %s", next->value); exit(-1);  
    }
    printf("<ConstDecl>\n");
    return; 
}

void parserBType() //BType first(next->type == INTTK)
{
    if(next->type == INTTK)
    {
        nextpoint(); 
    }
    else
    {
        printf("error in : %s", next->value); exit(-1);  
    }
    //printf("<BType>\n");
    return;
}

void parserConstDef()// ConstDef first(next->type == IDENFR)
{
    if(next->type == IDENFR)
    {
        nextpoint();
    }
    else
    {
        printf("error in : %s", next->value); exit(-1); 
    }

    while(next->type == LBRACK)
    {
        nextpoint();
        if(ruleConstExp)
        {
            parserConstExp(); 
        }
        else
        {
            printf("error in : %s", next->value); exit(-1); 
        }

        if(next->type == RBRACK)
        {
            nextpoint();
        }
        else 
        {
            printf("error in : %s", next->value); exit(-1); 
        }
    }

    if(next->type == ASSIGN)
    {
        nextpoint();
    }
    else{
        printf("error in : %s", next->value); exit(-1); 
    }

    if(ruleConstInitVal)
    {
        parserConstInitVal(); 
    }
    else 
    {
        printf("error in : %s", next->value); exit(-1); 
    }
    printf("<ConstDef>\n");
    return;
}

void parserConstInitVal() //ConstExp first(IDENFR,LPARENT) ConstInitVal first(LBRACE,IDENFR,LPARENT)
{
    if(ruleConstExp)
    {
        parserConstExp(); 
    }
    else if(next->type == LBRACE)
    {
        nextpoint(); 
        if(ruleConstInitVal)
        {
            parserConstInitVal(); 
            while(next->type == COMMA)
            {
                nextpoint(); 
                if(ruleConstInitVal)
                {
                    parserConstInitVal(); 
                }
            }

        }
        if(next->type == RBRACE)
        {
            nextpoint(); 
        }
        else 
        {
            printf("error in : %s", next->value); exit(-1);  
        }
    }
    else
    {
        printf("error in : %s", next->value); exit(-1);  
    }
    printf("<ConstInitVal>\n");
    return; 
}

void parserVarDecl() //VarDecl first(next->type == INTTK)
{
    if(ruleBType)
    {
        parserBType(); 
    }
    else 
    {
        printf("error in : %s", next->value); exit(-1);  
    }

    if(ruleVarDef)
    {
        parserVarDef();
    }
    else
    {
        printf("error in : %s", next->value); exit(-1); 
    }

    while(next->type == COMMA)
    {
        nextpoint(); 
        if(next->type == IDENFR)
        {
            parserVarDef();
        }
    }

    if(next->type == SEMICN)
    {
        nextpoint();
    }
    else 
    {
        printf("error in : %s", next->value); exit(-1); 
    }
    printf("<VarDecl>\n");
    return;
}

void parserVarDef() //VarDef first(next->type == IDENFR)
{
    if(next->type == IDENFR)
    {
        nextpoint();
    }
    else 
    {
        return;
    }

    while(next->type == LBRACK)
    {
        nextpoint();
        if(ruleConstExp)
        {
            parserConstExp(); 
        }
        else
        {
            printf("error in : %s", next->value); exit(-1); 
        }

        if(next->type == RBRACK)
        {
            nextpoint();
        }
        else 
        {
            printf("error in : %s", next->value); exit(-1); 
        }
    }


    if(next->type == ASSIGN)
    {
        nextpoint();
        if(ruleInitVal)
        {
            parserInitVal();
        }
        else
        {
            printf("error in : %s", next->value); exit(-1); 
        }
    }
    printf("<VarDef>\n");
    return;
}

void parserInitVal() //InitVal first(next->type == INTCON || next->type == IDENFR || next->type == LPARENT || next->type == PLUS || next->type == MINU || next->type == NOT || next->type == LBRACE)
{
    if(ruleExp)
    {
        parserExp();
    }
    else if(next->type == LBRACE)
    {
        nextpoint();
        if(ruleInitVal)
        {
            parserInitVal();
            while(next->type == COMMA)
            {
                nextpoint();
                if(ruleInitVal)
                {
                    parserInitVal();
                }
                else
                {
                    printf("error in : %s", next->value); exit(-1); 
                }
            }

        }

        if(next->type == RBRACE)
        {
            nextpoint();
        }
        else
        {
            printf("error in : %s", next->value); exit(-1); 
        }
    }
    else 
    {
        printf("error in : %s", next->value); exit(-1); 
    }
    printf("<InitVal>\n");
    return;
}

void parserFuncDef() //FuncDef first(next->type == VOIDTK || next->type == INTTK)
{
    if(ruleFuncType)
    {
        parserFuncType();
    }
    else 
    {
        printf("error in : %s", next->value); exit(-1); 
    }

    if(next->type == IDENFR)
    {
        nextpoint();
    }
    else
    {
        printf("error in : %s", next->value); exit(-1); 
    }

    if(next->type == LPARENT)
    {
        nextpoint();
    }
    else
    {
        printf("error in : %s", next->value); exit(-1); 
    }

    if(ruleFuncFParams)
    {
        parserFuncFParams();
    }

    if(next->type == RPARENT)
    {
        nextpoint();
    }
    else
    {
        printf("error in : %s", next->value); exit(-1); 
    }

    if(ruleBlock)
    {
        parserBlock();
    }
    else
    {
        printf("error in : %s", next->value); exit(-1); 
    }

    printf("<FuncDef>\n");
    return;
}

void parserMainFuncDef() //MainFuncDef first(next->type == INTTK)
{
    if(next->type == INTTK)
    {
        nextpoint();
    }
    else 
    {
        printf("error in : %s", next->value); exit(-1); 
    }

    if(next->type == MAINTK)
    {
        nextpoint();
    }
    else 
    {
        printf("error in : %s", next->value); exit(-1); 
    }

    if(next->type == LPARENT)
    {
        nextpoint();
    }
    else 
    {
        printf("error in : %s", next->value); exit(-1); 
    }

    if(next->type == RPARENT)
    {
        nextpoint();
    }
    else 
    {
        printf("error in : %s", next->value); exit(-1); 
    }
    if(ruleBlock)
    {
        parserBlock();
    }
    else
    {
        printf("error in : %s", next->value); exit(-1); 
    }
    
    printf("<MainFuncDef>\n");
    return;
}

void parserFuncType() //FuncType first(next->type == VOIDTK || next->type == INTTK)
{
    if(next->type == VOIDTK || next->type == INTTK)
    {
        nextpoint();
    }
    else
    {
        printf("error in : %s", next->value); exit(-1); 
    }
    printf("<FuncType>\n");
    return;
}

void parserFuncFParams() //FuncFParams first(next->type == INTTK) 
{
    if(ruleFuncFParam)
    {
        parserFuncFParam();
    }
    else
    {
        printf("error in : %s", next->value); exit(-1); 
    }

    while(next->type == COMMA)
    {
        nextpoint();
        if(ruleFuncFParam)
        {
            parserFuncFParam();
        }
        else
        {
            printf("error in : %s", next->value); exit(-1); 
        }
    }

    printf("<FuncFParams>\n");
    return;
}

void parserFuncFParam()//FuncFParam first(next->type == INTTK) 
{
    if(ruleBType)
    {
        parserBType();
    }
    else 
    {
        printf("error in : %s", next->value); exit(-1); 
    }

    if(next->type == IDENFR)
    {
        nextpoint();
    }
    else
    {
        printf("error in : %s", next->value); exit(-1); 
    }

    if(next->type == LBRACK)
    {
        nextpoint();
        if(next->type == RBRACK)
        {
            nextpoint();

            while(next->type == LBRACK)
            {
                nextpoint();
                if(ruleConstExp)
                {
                    parserConstExp();
                }
                else
                {
                    printf("error in : %s", next->value); exit(-1); 
                }

                if(next->type == RBRACK)
                {
                    nextpoint();
                }
                else
                {
                    printf("error in : %s", next->value); exit(-1); 
                }
            }

        }
        else
        {
            printf("error in : %s", next->value); exit(-1); 
        }
    }

    printf("<FuncFParam>\n");
    return;
}

void parserBlock() // Block first(next->type == LBRACE)
{
    if(next->type == LBRACE)
    {
        nextpoint();
    }
    else 
    {
        printf("error in : %s", next->value); exit(-1); 
    }
 
    while(ruleBlockItem)
    {
        parserBlockItem();
    }
    
    if(next->type == RBRACE)
    {
        nextpoint();
    }
    else 
    {
        printf("error in : %s", next->value); exit(-1); 
    }
    printf("<Block>\n");
    return;
}

void parserBlockItem() //BlockItem first(next->type == CONSTTK || next->type == INTTK || next->type == IDENFR || next->type == INTCON || next->type == IDENFR || next->type == LPARENT || next->type == LBRACE || next->type == SEMICN || next->type == IFTK  || next->type == WHILETK || next->type == BREAKTK || next->type == RETURNTK || next->type == PRINTFTK)
{
    if(ruleDecl)
    {
        parserDecl();
    }
    else if(ruleStmt)
    {
        parserStmt();
    }
    else
    {
        printf("error in : %s", next->value); exit(-1); 
    }
    //printf("<BlockItem>\n");
    return;
}

void parserStmt() // BlockItem first() next->type == IDENFR || next->type == INTCON || next->type == IDENFR || next->type == LPARENT || next->type == LBRACE || next->type == SEMICN || next->type == IFTK  || next->type == WHILETK || next->type == BREAKTK || next->type == RETURNTK || next->type == PRINTFTK
{
    
    if(next->type == IFTK)
    {
        nextpoint();
        if(next->type == LPARENT)
        {
            nextpoint();
            if(ruleCond)
            {
                parserCond();
                if(next->type == RPARENT)
                {
                    nextpoint();
                    if(ruleStmt)
                    {
                        parserStmt();
                        if(next->type == ELSETK)
                        {
                            nextpoint();
                            if(ruleStmt)
                            {
                                parserStmt();
                            }
                            else
                            {
                                printf("error in : %s", next->value); exit(-1); 
                            }
                        }
                    }
                    else
                    {
                        printf("error in : %s", next->value); exit(-1); 
                    }
                }
                else
                {
                    printf("error in : %s", next->value); exit(-1); 
                }
            }
            else
            {
                printf("error in : %s", next->value); exit(-1); 
            }
        }
        else
        {
            printf("error in : %s", next->value); exit(-1); 
        }
    }  
    else if(next->type == WHILETK)
    {
        nextpoint();
        if(next->type == LPARENT)
        {
            nextpoint();
            if(ruleCond)
            {
                parserCond();
                if(next->type == RPARENT)
                {
                    nextpoint();
                    if(ruleStmt)
                    {
                        parserStmt();
                    }
                    else
                    {
                        printf("error in : %s", next->value); exit(-1); 
                    }
                }
                else
                {
                    printf("error in : %s", next->value); exit(-1); 
                }
            }
            else
            {
                printf("error in : %s", next->value); exit(-1); 
            }
        }
        else
        {
            printf("error in : %s", next->value); exit(-1); 
        }
    }
    else if(next->type == BREAKTK)
    {
        nextpoint(); 
        if(next->type == SEMICN)
        {
            nextpoint();
        }
        else 
        {
            printf("error in : %s", next->value); exit(-1); 
        }
    }
    else if(next->type == CONTINUETK)
    {
        nextpoint(); 
        if(next->type == SEMICN)
        {
            nextpoint();
        }
        else 
        {
            printf("error in : %s", next->value); exit(-1); 
        }
    }
    else if(next->type == RETURNTK)
    {
        nextpoint();
        if(ruleExp)
        {
            parserExp();
        }
        if(next->type == SEMICN)
        {
            nextpoint();
        }
        else 
        {
            printf("error in : %s", next->value); exit(-1); 
        }
    }
    else if(next->type == PRINTFTK)
    {
        
        nextpoint();
        if(next->type == LPARENT)
        {
            nextpoint();
            if(next->type == STRCON)
            {
                nextpoint();
                while(next->type == COMMA)
                {
                    nextpoint();
                    if(ruleExp)
                    {
                        parserExp();
                    }
                    else 
                    {
                        printf("error in : %s", next->value); exit(-1); 
                    }
                }
                
                if(next->type == RPARENT)
                {
                    nextpoint();
                    if(next->type == SEMICN)
                    {
                        nextpoint();
                    }
                    else
                    {
                        printf("error in : %s", next->value); exit(-1); 
                    }
                }
                else 
                {
                    printf("error in : %s", next->value); exit(-1); 
                }
            }
            else 
            {
                printf("error in : %s", next->value); exit(-1); 
            }
        }
        else 
        {
            printf("error in : %s", next->value); exit(-1); 
        }
    
    }
    else if(ruleBlock)
    {
        parserBlock();
    }
    else if(next->type == SEMICN)
    {
        nextpoint();
    }
    else if(ruleLVal)
    {
        //不能确定
        
        struct token* ls = next;
        parserLVal();
        if(next->type != ASSIGN)//应该用exp归约
        {
            next = ls; 
            parserExp();
            if(next->type == SEMICN)
            {
                nextpoint();
            }
            else
            {
                printf("error in : %s", next->value); exit(-1); 
            }
        }
        else
        {
            nextpoint();
            if(next->type == GETINTTK)
            {
                nextpoint();
                if(next->type == LPARENT)
                {
                    nextpoint();
                    if(next->type == RPARENT)
                    {
                        nextpoint();
                        if(next->type == SEMICN)
                        {
                            nextpoint();
                        }
                        else 
                        {
                            printf("error in : %s", next->value); exit(-1); 
                        }
                    }
                    else 
                    {
                        printf("error in : %s", next->value); exit(-1); 
                    }
                }
                else 
                {
                    printf("error in : %s", next->value); exit(-1); 
                }
            }
            else if(ruleExp)
            {
                parserExp();
                if(next->type == SEMICN)
                {
                    nextpoint();
                }
                else 
                {
                    printf("error in : %s", next->value); exit(-1); 
                }
            }
            else 
            {
                printf("error in : %s", next->value); exit(-1); 
            }

        }
    }
    else if(ruleExp)
    {
        parserExp();
        if(next->type == SEMICN)
        {
            nextpoint();
        }
        else
        {
            printf("error in : %s", next->value); exit(-1); 
        }
    }
    else 
    {
        printf("error in : %s", next->value); exit(-1); 
    }
    
    printf("<Stmt>\n");
    return;
}

void parserExp() //Exp first(next->type == INTCON || next->type == IDENFR || next->type == LPARENT || next->type == PLUS || next->type == MINU || next->type == NOT)
{
    
    if(ruleAddExp)
    {
        parserAddExp();
    }
    else 
    {
        printf("error in : %s", next->value); exit(-1); 
    }
    printf("<Exp>\n");
    return;
}

void parserCond() //Cond first(next->type == INTCON || next->type == IDENFR || next->type == LPARENT || next->type == PLUS || next->type == MINU || next->type == NOT)
{
    if(ruleLOrExp)
    {
        parserLOrExp();
    }
    else
    {
        printf("error in : %s", next->value); exit(-1); 
    }
    
    printf("<Cond>\n");
    return;
}

void parserLVal()//LVal first(next->type == IDENFR)
{
    if(next->type == IDENFR)
    {
        nextpoint();
    }
    else
    {
        printf("error in : %s", next->value); exit(-1); 
    }

    while(next->type == LBRACK)
    {
        nextpoint();
        if(ruleExp)
        {
            parserExp();
        }
        else
        {
            printf("error in : %s", next->value); exit(-1); 
        }
        if(next->type == RBRACK)
        {
            nextpoint();
        }
        else
        {
            printf("error in : %s", next->value); exit(-1); 
        }
    }

    printf("<LVal>\n");
    return;
}

void parserPrimaryExp() //PrimaryExp first(next->type == INTCON || next->type == IDENFR || next->type == LPARENT)
{
    if(next->type == LPARENT)
    {
        if(ruleExp)
        {
            parserExp();
        }
        else
        {
            printf("error in : %s", next->value); exit(-1); 
        }

        if(next->type == RPARENT)
        {
            nextpoint();
        }
        else
        {
            printf("error in : %s", next->value); exit(-1); 
        }
    }
    else if(ruleLVal)
    {
        parserLVal();
    }
    else if(ruleNumber)
    {
        parserNumber();
    }
    else
    {
        printf("error in : %s", next->value); exit(-1); 
    }
    
    printf("<PrimaryExp>\n");
    return;
}

void parserNumber() //Number first(next->type == INTCON)
{
    if(next->type == INTCON)
    {
        nextpoint();
    }
    else
    {
        printf("error in : %s", next->value); exit(-1); 
    }
    
    printf("<Number>\n");
    return;
}

//undo
void parserUnaryExp() //UnaryExp first(next->type == INTCON || next->type == IDENFR || next->type == LPARENT || next->type == PLUS || next->type == MINU || next->type == NOT) 
{
    looknextnext();
    if(next->type == IDENFR && nextnext->type == LPARENT)
    {
        printf("$$\n");
        nextpoint();
        nextpoint();
        if(ruleFuncRParams)
        {
            parserFuncRParams();
        }
        if(next->type == RPARENT)
        {
            nextpoint();
        }
        else
        {
            printf("error in : %s", next->value); exit(-1); 
        }
    }
    else if(rulePrimaryExp)
    {
        parserPrimaryExp();
    }
    else if(ruleUnaryOp)
    {
        parserUnaryOp();
    }
    else
    {
        printf("error in : %s", next->value); exit(-1); 
    }

    printf("<UnaryExp>\n");
    return;
}

void parserUnaryOp() //UnaryOp first(next->type == PLUS || next->type == MINU || next->type == NOT)
{
    if(next->type == PLUS || next->type == MINU || next->type == NOT)
    {
        nextpoint();
    }
    else
    {
        printf("error in : %s", next->value); exit(-1); 
    }
    printf("<UnaryOp>\n");
    return;
}

void parserFuncRParams() //FuncRParams first(next->type == INTCON || next->type == IDENFR || next->type == LPARENT || next->type == PLUS || next->type == MINU || next->type == NOT)
{
    if(ruleExp)
    {
        parserExp();
    }
    else
    {
        printf("error in : %s", next->value); exit(-1); 
    }

    while(next->type == COMMA)
    {
        nextpoint();
        if(ruleExp)
        {
            parserExp();
        }
        else
        {
            printf("error in : %s", next->value); exit(-1); 
        }
    }

    printf("<FuncRParams>\n");
    return;
}

void parserMulExp() //MulExp first(next->type == INTCON || next->type == IDENFR || next->type == LPARENT || next->type == PLUS || next->type == MINU || next->type == NOT)
{
    if(ruleUnaryExp)
    {
        parserUnaryExp();
    }
    else
    {
        printf("error in : %s", next->value); exit(-1); 
    }

    while(next->type == MULT || next->type == DIV || next->type == MOD)
    {
        nextpoint();
        if(ruleUnaryExp)
        {
            parserUnaryExp();
        }
        else
        {
            printf("error in : %s", next->value); exit(-1); 
        }
    }
    printf("<MulExp>\n");
    return;
}

void parserAddExp() //AddExp first(next->type == INTCON || next->type == IDENFR || next->type == LPARENT || next->type == PLUS || next->type == MINU || next->type == NOT)
{
    if(ruleMulExp)
    {
        parserMulExp();
    }
    else
    {
        printf("error in : %s", next->value); exit(-1); 
    }

    while(next->type == PLUS || next->type == MINU)
    {
        nextpoint();
        if(ruleMulExp)
        {
            parserMulExp();
        }
        else
        {
            printf("error in : %s", next->value); exit(-1); 
        }
    }

    printf("<AddExp>\n");
    return;
}

void parserRelExp() //RelExp first(next->type == INTCON || next->type == IDENFR || next->type == LPARENT || next->type == PLUS || next->type == MINU || next->type == NOT)
{

    if(ruleAddExp)
    {
        parserAddExp();
    }
    else
    {
        printf("error in : %s", next->value); exit(-1); 
    }

    while(next->type == LSS || next->type == LEQ || next->type == GRE || next->type == GEQ)
    {
        nextpoint();
        if(ruleAddExp)
        {
            parserAddExp();
        }
        else
        {
            printf("error in : %s", next->value); exit(-1); 
        }
    }

    printf("<RelExp>\n");
    return;
}

void parserEqExp() //EqExp first(next->type == INTCON || next->type == IDENFR || next->type == LPARENT || next->type == PLUS || next->type == MINU || next->type == NOT)
{
    
    if(ruleRelExp)
    {
        parserRelExp();
    }
    else
    {
        
        printf("error in : %s", next->value); exit(-1); 
    }

    while(next->type == EQL || next->type == NEQ)
    {
        nextpoint();
        if(ruleRelExp)
        {
            parserRelExp();
        }
        else
        {

            printf("error in : %s", next->value); exit(-1); 
        }
    }

    printf("<EqExp>\n");
    return;
}

void parserLAndExp()//LAndExp first(next->type == INTCON || next->type == IDENFR || next->type == LPARENT || next->type == PLUS || next->type == MINU || next->type == NOT)
{
    
    if(ruleEqExp)
    {
        parserEqExp();
    }
    else
    {
        printf("error in : %s", next->value); exit(-1); 
    }

    while(next->type == AND)
    {
        nextpoint();
        if(ruleEqExp)
        {
            parserEqExp();
        }
        else
        {
            printf("error in : %s", next->value); exit(-1); 
        }
    }

    printf("<LAndExp>\n");
    return;
}

void parserLOrExp() //LOrExp first(next->type == INTCON || next->type == IDENFR || next->type == LPARENT || next->type == PLUS || next->type == MINU || next->type == NOT)
{

    if(ruleLAndExp)
    {
        parserLAndExp();
    }
    else
    {
        printf("error in : %s", next->value); exit(-1); 
    }

    while(next->type == OR)
    {
        nextpoint();
        if(ruleLAndExp)
        {
            parserLAndExp();
        }
        else
        {
            printf("error in : %s", next->value); exit(-1); 
        }
    }

    printf("<LOrExp>\n");
    return;
}

void parserConstExp() //ConstExp first(next->type == INTCON || next->type == IDENFR || next->type == LPARENT || next->type == PLUS || next->type == MINU || next->type == NOT)
{
    if(ruleAddExp)
    {
        parserAddExp();
    }
    else
    {
        printf("error in : %s", next->value); exit(-1); 
    }
    
    printf("<ConstExp>\n");
    return;
}