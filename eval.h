//
//  eval.h
//  parser
//
//  Created by Viet Hong Nguyen on 5/3/18.
//  Copyright © 2018 Viet Hong Nguyen. All rights reserved.
//

#ifndef eval_h
#define eval_h

#include <stdio.h>

ConsCell eval(ConsCell cc);
ConsCell quote(ConsCell cc);
ConsCell car(ConsCell cc);
ConsCell cdr(ConsCell cc);
ConsCell symbol(ConsCell cc);
ConsCell cons(ConsCell c1, ConsCell c2, int i);
ConsCell null(ConsCell cc);
ConsCell append(ConsCell c1, ConsCell c2);
ConsCell equal(ConsCell c1, ConsCell c2);
int equalHelper(ConsCell c1, ConsCell c2);
ConsCell assoc(ConsCell c1, ConsCell c2);
ConsCell assocHelper(ConsCell c1, ConsCell c2);
ConsCell cond(ConsCell);
ConsCell define(ConsCell c1, ConsCell c2);
ConsCell defineHelper(ConsCell c1, ConsCell c2);
ConsCell isList(ConsCell cc, int i);
ConsCell function(ConsCell cc);

#endif /* eval_h */
