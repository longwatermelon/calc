#include "visitor.h"


int visitor_visit(struct Node *node)
{
    switch (node->type)
    {
    case NODE_ADD: return visitor_visit_add(node);
    case NODE_INT: return node->int_value;
    }

    // Should never reach here
    return 0;
}


int visitor_visit_add(struct Node *node)
{
    return visitor_visit(node->left) + visitor_visit(node->right);
}

