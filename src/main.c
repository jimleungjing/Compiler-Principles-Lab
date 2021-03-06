/*
 *  @file   main.c
 *  @brief  
 *  @author jim
 *  @date   2018-5-4
 *  @version v1.0
**/

#include <stdio.h>
#include <string.h>
#include "main.h"

extern FILE *yyin;
extern int yylex (void);
extern void yyrestart(FILE * input_file );
extern int yyparse (void);

FILE *pscanner;
FILE* pic = NULL;
FILE* pcg = NULL;

struct SyntaxTreeNode* root;
int error_hint = 0;
int main(int argc, char** argv) {
    FILE *pfile;
    if (argc > 1) {
        if(argc == 2){  /*Normal Mode*/
            if (!(pfile = fopen(argv[1], "r+"))) {
                perror(argv[1]);
                return 1;
            }
        }
    }
    //pscanner = fopen("./Output/scanner.output","w+");
    yyrestart(pfile);
    yyparse();
    if(error_hint == 0){
        pic = fopen("./out.ir","w+");
        pcg = fopen("./code.s","w+");
        if(!pic){
            printf("Failed to open out.ir\n");
            return 0;
        }
        if(!pcg){
            printf("Failed to open code.s\n");
            return 0;
        }
        //PreOrderTraverse(root,0);
        ST_Program(root);
        DestructTree(root);
        // generate assembly
        CodeGenerator(pcg);
        fclose(pcg);
        fclose(pic);
    }
    //fclose(pscanner);
    return 0;
}

