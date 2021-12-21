#ifndef VISITOR_H
#define VISITOR_H

#include "parser.h"

int visitor_visit(struct Node *node);
int visitor_visit_add(struct Node *node);

#endif

