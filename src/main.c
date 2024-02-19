#include "../include/util.h"

struct token tokens_init[1000000];
//printf("success to run, next = %s\n", next->value);
int main()
{
    printf("\n开始词法分析\n");
    run_cffx(tokens_init);
    printf("\n开始语法分析\n");
    init_yffx(tokens_init);
    run_yffx();
    return 0; 
}