//
//  eval.c
//  parser
//
//  Created by Viet Hong Nguyen on 5/3/18.
//  Copyright © 2018 Viet Hong Nguyen. All rights reserved.
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "lexer.h"
#include "parser.h"
#include "eval.h"

//eval()
ConsCell eval(ConsCell cc)
{
    if (cc == NULL)
    {
        return cc;
    }
    ConsCell temp;
    //exit function
    if (!strcmp(cc->first->data, "exit"))
    {
        printf("Have a nice day!\n");
        printf("[vienguyen:cs170/Scheme]\n");
        exit(0);
    }
    //quote function
    else if (!strcmp(cc->first->data, "quote"))
    {
        //check if input is a list
        int n = 1;
        if (strcmp(cc->rest->data, ""))
        {
            n = 0;
        }
        //eval the rest of the list
        temp = eval(cc->rest->first);
        
        //check if input is a list
        if (n == 0)
        {
            list = 0;
        }
        else
        {
            list = 1;
        }
        return quote(temp);
    }
    //car function
    else if (!strcmp(cc->first->data, "car"))
    {
        //eval the rest of the list
        temp = eval(cc->rest->first);
        //check if the car is a list
        if (strcmp(temp->data, ""))
        {
            list = 0;
        }
        return car(temp);
    }
    //cdr function
    else if (!strcmp(cc->first->data, "cdr"))
    {
        //eval the rest of the list
        temp = eval(cc->rest->first);
        return cdr(temp);
    }
    //symbol? function
    else if (!strcmp(cc->first->data, "symbol?"))
    {
        //eval the rest of the list
        temp = eval(cc->rest->first);
        //check if input is a list
        if (strcmp(temp->data, "") && temp->rest == NULL)
        {
            list = 0;
        }
        return symbol(temp);
    }
    //cons function
    else if (!strcmp(cc->first->data, "cons"))
    {
        int i = 0;
        ConsCell c1 = eval(cc->rest->first);
        if (list == 1)
        {
            i = 1;
            list = 0;
        }
        ConsCell c2 = eval(cc->rest->rest->first);
        return cons(c1, c2, i);
    }
    else if (!strcmp(cc->first->data, "null?"))
    {
        if (!strcmp(cc->rest->data, ""))
        {
            list = 1;
        }
        else
        {
            list = 0;
        }
        temp = eval(cc->rest->first);
        return null(temp);
    }
    else if (!strcmp(cc->first->data, "append"))
    {
        if (strcmp(cc->rest->data, ""))
        {
            list = 0;
        }
        ConsCell c1 = eval(cc->rest->first);
        list = 1;
        if (strcmp(cc->rest->rest->data, ""))
        {
            list = 0;
        }
        ConsCell c2 = eval(cc->rest->rest->first);
        if (!strcmp(c1->data, "()") && !strcmp(c2->data, "()"))
        {
            list = 0;
            temp = createConsCell();
            temp->first = temp;
            strcpy(temp->data, "()");
            return temp;
        }
        if (!strcmp(c1->data, "()"))
        {
            list = 1;
            return c2;
        }
        else if (!strcmp(c2->data, "()"))
        {
            list = 1;
            return c1;
        }
        return append(c1, c2);
    }
    else if (!strcmp(cc->first->data, "equal?"))
    {
        ConsCell c1 = eval(cc->rest->first);
        ConsCell c2 = eval(cc->rest->rest->first);
        return equal(c1, c2);
    }
    else if (!strcmp(cc->first->data, "assoc"))
    {
        return assoc(eval(cc->rest->first), eval(cc->rest->rest->first));
    }
    else if (!strcmp(cc->first->data, "cond"))
    {
        return cond(cc->rest);
    }
    else if (!strcmp(cc->first->data, "define"))
    {
        return define(eval(cc->rest->first), eval(cc->rest->rest->first));
    }
    else if (!strcmp(cc->first->data, "list?"))
    {
        int i = 0;
        if (strcmp(cc->rest->data, ""))
        {
            i = 0;
        }
        else
        {
            i = 1;
        }
        //eval the rest of the list
        temp = eval(cc->rest->first);
        
        return isList(temp, i);
    }
    else if (!strcmp(cc->first->data, "function?"))
    {
        //eval the rest of the list
        temp = eval(cc->rest->first);
        return function(temp);
    }
    //if none of the function is called, return the list
    else{
        if (strcmp(cc->data, "") && list == 0)
        {
            temp = assoc(cc, env);
            if (strcmp(temp->data, "()"))
            {
                list = 1;
                return temp->rest->first;
            }
            else
            {
                return cc;
            }
        }
        else{
            return cc;
        }
    }
}

//quote function
ConsCell quote(ConsCell cc)
{
    return cc;
}

//car function
ConsCell car(ConsCell cc)
{
    //make the rest of the list NULL
    if (cc == NULL)
    {
        return NULL;
    }
    if (strcmp(cc->data, ""))
    {
        ConsCell temp = createConsCell();
        temp->first = temp;
        strcpy(temp->data, cc->data);
        return temp->first;
    }
    else
    {
        return cc->first;
    }
}

//cdr function
ConsCell cdr(ConsCell cc)
{
    if (cc == NULL)
    {
        return NULL;
    }
    //check if the cdr is empty
    /*if (cc->rest == NULL)
     {
     ConsCell temp = createConsCell();
     strcpy(temp->data, "");
     //return ()
     return temp;
     }
     else{/*/
    list = 1;
    return cc->rest;
    //}
}

//symbol? function
ConsCell symbol(ConsCell cc)
{
    ConsCell temp = createConsCell();
    //return #t if true
    if (list == 0)
    {
        strcpy(temp->data, "#t");
        return temp;
    }
    //return () if false
    else
    {
        strcpy(temp->data, "");
        return temp;
    }
}

//cons function
ConsCell cons(ConsCell c1, ConsCell c2, int i)
{
    if (c1 == NULL)
    {
        return c2;
    }
    else if (c2 == NULL)
    {
        return c1;
    }
    //check if either parameter is #f
    if (!strcmp(c1->data, "#f"))
    {
        ConsCell temp = createConsCell();
        temp->first = c2;
        return temp;
    }
    else if (!strcmp(c2->data, "#f"))
    {
        ConsCell temp = createConsCell();
        temp->first = c1;
        return temp;
    }
    //check if the second parameter is ()
    else if (!strcmp(c2->data, "()"))
    {
        return c1;
    }
    else
    {
        ConsCell temp = createConsCell();
        //the first conscell is a list
        if (i == 1)
        {
            temp->first = c1;
        }
        //the first conscell is just a key
        else
        {
            temp = c1;
            temp->first = temp;
        }
        temp->rest = c2->first;
        return temp;
    }
}

//null? function
ConsCell null (ConsCell cc)
{
    ConsCell temp = createConsCell();
    temp->first = temp;
    //check for NULL
    if (cc == NULL)
    {
        list = 0;
        strcpy(temp->data, "#t");
        return temp;
    }
    //check for is a list or not
    if (!strcmp(cc->data, "") || list == 1)
    {
        list = 0;
        strcpy(temp->data, "()");
        return temp;
    }
    //else true
    else
    {
        list = 0;
        strcpy(temp->data, "#t");
        return temp;
    }
}

//append function
ConsCell append(ConsCell c1, ConsCell c2)
{
    if (c1 == NULL)
    {
        return c2;
    }
    else
    {
        return cons(car(c1), append(cdr(c1), c2), 0);
    }
}

//equal? function
ConsCell equal(ConsCell c1, ConsCell c2)
{
    ConsCell temp = createConsCell();
    list = 0;
    //if true return #t
    if (equalHelper(c1, c2) == 1)
    {
        temp->first = temp;
        strcpy(temp->data, "#t");
        return temp;
    }
    //else return ()
    else
    {
        temp->first = temp;
        strcpy(temp->data, "()");
        return temp;
    }
}

//helper for equal
int equalHelper(ConsCell c1, ConsCell c2)
{
    //check for NULL, base case
    if (c1 == NULL)
    {
        if (c2 == NULL)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    if (c2 == NULL)
    {
        if (c1 == NULL)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    //if both key are the same
    if (!strcmp(c1->data, c2->data))
    {
        //check if the key is in a list
        if (strcmp(c1->first->data, c1->data))
        {
            int m;
            if (strcmp(c2->first->data, c2->data))
            {
                //recurse on the next key
                m = equalHelper(c1->first, c2->first);
            }
            else
            {
                return 0;
            }
            //recurse on the outer level list
            int n = equalHelper(c1->rest, c2->rest);
            if (m == 0 || n == 0)
            {
                return 0;
            }
            else
            {
                return 1;
            }
        }
        //the next key is not a list
        else
        {
            //recurse on the outer level list next key
            return equalHelper(c1->rest, c2->rest);
        }
    }
    //else return false
    else
    {
        return 0;
    }
}

//assoc function
ConsCell local;
ConsCell assoc(ConsCell c1, ConsCell c2)
{
    local = createConsCell();
    ConsCell temp = local;
    assocHelper(c1, c2);
    //if the built list is NULL, return () as no such item in the list has key
    if (temp->rest == NULL && temp->first == NULL)
    {
        list = 0;
        strcpy(temp->data, "()");
        return temp;
    }
    //else list the list
    else
    {
        list = 1;
        return temp->first;
    }
}

//assoc helper
ConsCell assocHelper(ConsCell c1, ConsCell c2)
{
    //base case
    if (c2 == NULL)
    {
        return local;
    }
    //if the current item in the list has the key
    if (!strcmp(c2->first->data, c1->data))
    {
        //put the item into the return list
        if (local == NULL)
        {
            local = createConsCell();
        }
        local->first = c2->first;
        local = local->rest;
    }
    //recurse on the next item in the list
    return assocHelper(c1, c2->rest);
}

//cond function
ConsCell cond(ConsCell cc)
{
    //base case #t
    if (!strcmp(eval(cc->first->first)->data, "#t"))
    {
        return eval(cc->first->rest->first);
    }
    else
    {
        //else recurse on the next clause
        return cond(cc->rest);
    }
}

//define function
ConsCell define(ConsCell c1, ConsCell c2)
{
    //var is an extern pointer for the environment
    //check if the environment is empty
    //if yes, put the current variable into the environment
    if (var->rest == NULL && !strcmp(var->first->data, ""))
    {
        ConsCell temp = createConsCell();
        temp->first = temp;
        strcpy(temp->data, c1->data);
        c1->rest = createConsCell();
        c1->rest->first = c2;
        var->first = c1;
        //list = 1;
        //printList(env);
        list = 0;
        return temp;
    }
    //else if the current slot in the environment is not taken then put the variable into the environment
    else if (var->rest == NULL)
    {
        ConsCell temp = createConsCell();
        temp->first = temp;
        strcpy(temp->data, c1->data);
        var->rest = createConsCell();
        var = var->rest;
        c1->rest = createConsCell();
        c1->rest->first = c2;
        var->first = c1;
        //list = 1;
        //printList(env);
        list = 0;
        return temp;
    }
    //else go to the next slot
    else
    {
        var = var->rest;
        return define(c1, c2);
    }
}

ConsCell isList (ConsCell cc, int i)
{
    ConsCell temp = createConsCell();
    temp->first = temp;
    if (i == 1)
    {
        list = 0;
        strcpy(temp->data, "#t");
        return temp;
    }
    else
    {
        list = 0;
        strcpy(temp->data, "#f");
        return temp;
    }
}

ConsCell function(ConsCell cc)
{
    ConsCell temp = createConsCell();
    temp->first = temp;
    if (!strcmp(assoc(cc, env)->data, "()"))
    {
        list = 0;
        strcpy(temp->data, "#f");
        return temp;
    }
    else
    {
        list = 0;
        strcpy(temp->data, "#t");
        return temp;
    }
}
