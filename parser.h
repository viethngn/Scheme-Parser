//
//  parser.h
//  parser
//
//  Created by Viet Hong Nguyen on 2/27/18.
//  Copyright © 2018 Viet Hong Nguyen. All rights reserved.
//

#ifndef PARSER
#define PARSER
#include <stdlib.h>
//define ConsCell type

typedef struct conscell
{
    char data[20];
    struct conscell *first;
    struct conscell *rest;
}*ConsCell;
extern int list;
extern ConsCell env;
extern ConsCell var;
ConsCell createConsCell();
ConsCell S();
ConsCell S_Expression();
void printList(ConsCell cc);
void printHelper(ConsCell cc, int mark);

#endif /* parser_h */
