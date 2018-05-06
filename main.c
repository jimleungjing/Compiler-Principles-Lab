/*
 *  @file   main.c
 *  @brief  
 *  @author jim
 *  @date   2018-5-4
 *  @version v1.0
**/

#include <stdio.h>
#include "SyntaxTree.h"
extern FILE *yyin;
extern int yylex (void);
extern void yyrestart(FILE * input_file );
extern int yyparse (void);
extern int yydebug;

FILE *pscanner;
struct SyntaxTreeNode* root;
int error_hint = 0;
int main(int argc, char** argv) {
    FILE *pfile;
    if (argc > 1) {
        if (!(pfile = fopen(argv[1], "r+"))) {
            perror(argv[1]);
        return 1;
        }
    }
    //yydebug = 1;
    pscanner = fopen("scanneroutput.txt","r+");
    yyrestart(pfile);
    yyparse();
    if(error_hint == 0)
        PreOrderTraverse(root,0);
    //while(yylex());
    fclose(pscanner);
    return 0;
}

