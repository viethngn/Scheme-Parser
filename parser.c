//
//  parser.c
//  parser
//
//  Created by Viet Hong Nguyen on 2/27/18.
//  Copyright © 2018 Viet Hong Nguyen. All rights reserved.
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "lexer.h"
#include "parser.h"

ConsCell createConsCell()
{
    ConsCell cc = malloc(sizeof(*cc));
    if (cc == NULL)
    {
        printf("Out of memory!\n");
        exit(1);
    }
    strcpy(cc->data, "");
    cc->first = NULL;
    cc->rest = NULL;
    return cc;
}

ConsCell env;
ConsCell var;
ConsCell S_Expression()
{
    char token[20];
    startTokens(20);
    printf("\n");
    printf("scheme> ");
    //get next token
    strcpy(token, getToken());
    ConsCell cur = createConsCell();
    return S(cur, token);
}

//boolean to mark if input is a list
int list = 0;
//Helper method for S_Expression()
ConsCell S(ConsCell cur, char* token)
{
    ConsCell local;
    ConsCell temp;
    //if token is "("
    if (!strcmp(token, "("))
    {
        //check if input is a list
        list = 1;
        //create the new conscell
        local = createConsCell();
        //skip over the (
        strcpy(token, getToken());
        //recurse on next token and put it in next conscell
        local->first = S(local, token);
        //get next token
        strcpy(token, getToken());
        //store the header
        temp = local;
        //build the rest conscell in the same level
        while (strcmp(token, ")"))
        {
            temp->rest = createConsCell();
            //move to the next token on the same level
            temp = temp->rest;
            temp->first = S(temp, token);
            //get next token
            strcpy(token, getToken());
        }
        //when reach the end of a level, mark the end as NULL
        temp->rest = NULL;
        //return the consecell level
        return local;
    }
    //handle the keys
    else{
        //put the keys in the data part of the conscell
        strcpy(cur->data, token);
        if (list == 0)
        {
            cur->first = cur;
        }
        //return the conscell
        return cur;
    }
}

//printList function
void printList(ConsCell cc)
{
    if (list == 1)
    {
        printHelper(cc, 0);
    }
    else{
        printHelper(cc, 1);
    }
    list = 0;
}

void printHelper(ConsCell cc, int mark)
{
    //base case
    if (cc == NULL)
    {
        //mark is the boolean signify the end of a level
        if (mark == 1 && list == 1)
        {
            printf(")");
        }
        return;
    }
    ConsCell cur = cc;
    ConsCell next;
    //if this conscell is the beginning
    if (!strcmp(cur->data, ""))
    {
        //write the ( if this is the beginning
        if (mark == 0)
        {
            printf("(");
        }
        //recurse to print the next level if there is any
        printHelper(cur->first, 0);
        //store the header
        next = cur;
        //print out the rest of the keys in the same level
        while (next != NULL)
        {
            next = next->rest;
            //print space if there is a key ahead
            if (next != NULL)
            {
                //if the next item is a list
                if (!strcmp(next->data, ""))
                {
                    printf(" ");
                    printHelper(next->first, 0);
                }
                //else break the loop
                else
                {
                    printHelper(next->first, 1);
                    break;
                }
            }
            else
            {
                //print the next key in the same level
                printHelper(next, 1);
            }
        }
    }
    //if this conscell already contains a key
    else
    {
        
        //write ( if this is the beginning
        if (mark == 0)
        {
            printf("(");
        }
        //print key
        printf(" %s", cur->data);
        //print space if there is no key ahead
        if (cur->rest == NULL)
        {
            printf(" ");
        }
        //print space if the next item is a list
        else if (!strcmp(cur->rest->data, ""))
        {
            printf(" ");
        }
        //print the next key in the current list level
        printHelper(cur->rest, 1);
        return;
    }
}

/*Assignment 1
//Count for tab space
int n = 0;

//Main method
void S_Expression()
{
    char token[20];
    startTokens(20);
    printf("\n");
    printf("scheme> ");
    //get next token
    strcpy(token, getToken());
    S(token);
    return;
}

//Helper method for S_Expression()
void S (char* token)
{
    //if token is "("
    if (!strcmp(token, "("))
	{
        //print tab space
        for (int i = 0; i < n; i++)
        {
            printf("  ");
        }
        //print S_Expression
		printf("S_Expression\n");
        //print tab space
        for (int i = 0; i < n; i++)
        {
            printf("  ");
        }
        //print "("
		printf("%s\n", token);
        //if token is "(", increase tab space by 1
		n = n + 1;
        //get next token
		strcpy(token, getToken());
        //recurse to next token
		S(token);
        //if token is not ")" then continue to recurse on next token
		while (strcmp(token, ")"))
		{
			S(token);
		}
        //if token is ")", decrease tab space by 1
		n = n - 1;
        //print tab space
		for (int i = 0; i < n; i++)
        {
            printf("  ");
        }
        //print ")"
		printf("%s\n", token);
        //return if n tab space is 0, meaning the end of the input
        if (n == 0)
        {
            return;
        }
        //else continue
        else{
            strcpy(token, getToken());
        }
	}
	else
	{
        //print tab space
        for (int i = 0; i < n; i++)
        {
            printf("  ");
        }
        //print S_Expression
		printf("S_Expression\n");
        //print tab space
        for (int i = 0; i < n + 1; i++)
        {
            printf("  ");
        }
        //print letters
		printf("%s\n", token);
        //return if n is 0, meaning the end of the input
        if (n == 0)
        {
            return;
        }
        //else continue
        else{
            strcpy(token, getToken());
        }
	}
}*/
