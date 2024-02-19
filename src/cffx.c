#include "../include/util.h"


struct regex_rule
{
    const char* rule; 
    int type; 
}rules[] = 
{
    {"main", MAINTK},  //main
    {"const", CONSTTK}, //const
    {"int", INTTK},   //int
    {"break", BREAKTK}, //break
    {"continue", CONTINUETK}, //continue
    {"if", IFTK},  //if
    {"else", ELSETK}, //else

    {"&&", AND}, //&&
    {"\\|{2}", OR}, //||
    {"while", WHILETK}, //while
    {"getint", GETINTTK},//getint
    {"printf", PRINTFTK},//printf
    {"return", RETURNTK},//return
    {"\\+", PLUS},//+
    {"\\-", MINU},//-
    {"void", VOIDTK},//void
    {"\\*", MULT},//*
    {"\\/", DIV},// /
    {"%", MOD},//%
    {"<=", LEQ},//<=
    {"<", LSS},//<
    {">=", GEQ},//>=
    {">", GRE},//>
    {"==", EQL},//==
    {"!=", NEQ},//!=
    {"=", ASSIGN},//=
    {"[\\!]", NOT}, //!
    {";{1}", SEMICN},//;
    {",", COMMA},//,
    {"\\(", LPARENT},//(
    {"\\)", RPARENT},//)
    {"\\[", LBRACK},//[
    {"\\]", RBRACK},//]
    {"\\{", LBRACE},//{
    {"\\}", RBRACE}, //}
    {"\\s+", NOTYPE}, //空格
    {"[0-9]+", INTCON},  //IntConst
    {"\"([^\"]*)\"", STRCON},  //FormatString
    {"[a-z1-9]+", IDENFR}  //Ident
};

struct token tokens[1000000];

#define REGEX_SUM sizeof(rules)/sizeof(rules[0])
static regex_t compiled_regex[REGEX_SUM];
int tokens_sum; 
char file_buffer[10000];
int file_sum = 0; 

void init_regex()
{
    char error_msg[128];
    for(int i = 0; i < REGEX_SUM; i++)
    {
        int res = regcomp(&compiled_regex[i], rules[i].rule, REG_EXTENDED);
        if(res != 0)
        {
            regerror(res, &compiled_regex[i], error_msg, 128);
            printf("regex compilation failed: %s\n%s\n", error_msg, rules[i].rule);
            printf("error: the rule is no.%d\n", rules[i].type); 
        }
    }
}

void read_file()
{
    FILE* file; 
    char file_name[]= "/home/ubuntu/file/byyl/test/test.c"; 

    file = fopen(file_name, "r");
    if(file == NULL) 
    {
        printf("error to read file\n"); 
        return;
    }
    
    char temp; 
    int pos = 0; 
	while(1)
	{  
		temp = fgetc(file);  
		if(temp == EOF) break;  
		file_buffer[pos++] = temp;  
	} 
    file_buffer[pos] = '\0';
    file_sum = pos--;
}

void exec_regex()
{
    int pos = 0; 
    int tokens_pos = 0; 
    while(pos < file_sum)
    {
        int i = 0; 
        for(i = 0; i < REGEX_SUM; i++)
        {
            regmatch_t pmatch; 
            if(regexec(&compiled_regex[i], file_buffer + pos, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0)
            {
                char* start_str = file_buffer + pos; 
                int str_len = pmatch.rm_eo; 
                if(rules[i].type == NOTYPE)
                {
                    pos += str_len;
                    break; 
                }
                memcpy(tokens[tokens_pos].value, start_str, str_len);
                pos += str_len;
                tokens[tokens_pos++].type = rules[i].type;
                break;
            }
        }
        if(i == REGEX_SUM) 
        {
            printf("no match at position %d\n%s\n%*.s^\n",pos, file_buffer, pos, "");
            printf("%c", file_buffer[pos]);
            printf("%c", file_buffer[pos+1]);
            printf("%d", pos);
            printf("%d", rules[i].type);
            return; 
        }
        
    }

    tokens_sum = tokens_pos--;
    return; 
}

void print_exec_regex_result()
{
    printf("print_exec_regex_result:\n");
    for(int i = 0; i < tokens_sum; i++)
    {
        // printf("%s : %d\n", tokens[i].value, tokens[i].type); 
        switch(tokens[i].type)
        {
            case IDENFR     : printf("IDENFR     :   %s\n", tokens[i].value); break;
            case INTCON     : printf("INTCON     :   %s\n", tokens[i].value); break;
            case STRCON     : printf("STRCON     :   %s\n", tokens[i].value); break;
            case MAINTK     : printf("MAINTK     :   %s\n", tokens[i].value); break;
            case CONSTTK    : printf("CONSTTK    :   %s\n", tokens[i].value); break;
            case INTTK      : printf("INTTK      :   %s\n", tokens[i].value); break;
            case BREAKTK    : printf("BREAKTK    :   %s\n", tokens[i].value); break;
            case CONTINUETK : printf("CONTINUETK :   %s\n", tokens[i].value); break;
            case IFTK       : printf("IFTK       :   %s\n", tokens[i].value); break;
            case ELSETK     : printf("ELSETK     :   %s\n", tokens[i].value); break;
            case NOT        : printf("NOT        :   %s\n", tokens[i].value); break;
            case AND        : printf("AND        :   %s\n", tokens[i].value); break;
            case OR         : printf("OR         :   %s\n", tokens[i].value); break;
            case WHILETK    : printf("WHILETK    :   %s\n", tokens[i].value); break;
            case GETINTTK   : printf("GETINTTK   :   %s\n", tokens[i].value); break;
            case PRINTFTK   : printf("PRINTFTK   :   %s\n", tokens[i].value); break;
            case RETURNTK   : printf("RETURNTK   :   %s\n", tokens[i].value); break;
            case PLUS       : printf("PLUS       :   %s\n", tokens[i].value); break;
            case MINU       : printf("MINU       :   %s\n", tokens[i].value); break;
            case VOIDTK     : printf("VOIDTK     :   %s\n", tokens[i].value); break;
            case MULT       : printf("MULT       :   %s\n", tokens[i].value); break;
            case DIV        : printf("DIV        :   %s\n", tokens[i].value); break;
            case MOD        : printf("MOD        :   %s\n", tokens[i].value); break;
            case LSS        : printf("LSS        :   %s\n", tokens[i].value); break;
            case LEQ        : printf("LEQ        :   %s\n", tokens[i].value); break;
            case GRE        : printf("GRE        :   %s\n", tokens[i].value); break;
            case GEQ        : printf("GEQ        :   %s\n", tokens[i].value); break;
            case EQL        : printf("EQL        :   %s\n", tokens[i].value); break;
            case NEQ        : printf("NEQ        :   %s\n", tokens[i].value); break;
            case ASSIGN     : printf("ASSIGN     :   %s\n", tokens[i].value); break;
            case SEMICN     : printf("SEMICN     :   %s\n", tokens[i].value); break;
            case COMMA      : printf("COMMA      :   %s\n", tokens[i].value); break;
            case LPARENT    : printf("LPARENT    :   %s\n", tokens[i].value); break;
            case RPARENT    : printf("RPARENT    :   %s\n", tokens[i].value); break;
            case LBRACK     : printf("LBRACK     :   %s\n", tokens[i].value); break;
            case RBRACK     : printf("RBRACK     :   %s\n", tokens[i].value); break;
            case LBRACE     : printf("LBRACE     :   %s\n", tokens[i].value); break;
            case RBRACE     : printf("RBRACE     :   %s\n", tokens[i].value); break;
            case NOTYPE     : printf("NOTYPE     :   %s\n", tokens[i].value); break;
        }
    }
}

void run_cffx(struct token* tokens_init)
{
    init_regex();
    read_file();
    int i = 0; 
    for(int i = 0; i < file_sum; i++)
    {
        printf("%c", file_buffer[i]); 
    }
    printf("\n");
    exec_regex();
    print_exec_regex_result();
    for(int i = 0; i < 1000000; i++)
    {
        tokens_init[i] = tokens[i];
    }
    printf("词法分析成功\n");
    return; 
}