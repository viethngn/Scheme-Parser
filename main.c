//
//  main.c
//  parser
//
//  Created by Viet Hong Nguyen on 2/27/18.
//  Copyright © 2018 Viet Hong Nguyen. All rights reserved.
//

#include "parser.h"
#include "lexer.h"
#include "eval.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    printf("[vienguyen:cs170/Scheme] ./runscheme3\n");
    printf("A parser for a subset of Scheme.\n");
    printf("Type Scheme expressions using quote,\n");
    printf("car, cdr, cons and symbol?.\n");
    printf("The function call (exit) quits.\n");
    //variable environment
    env = createConsCell();
    env->first = env;
    var = env;
    while(1)
    {
        printList(eval(S_Expression()));
    }
    return 0;
}
