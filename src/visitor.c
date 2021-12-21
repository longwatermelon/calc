#include "visitor.h"


int visitor_visit(struct Node *node)
{
    switch (node->type)
    {
    case NODE_ADD:
        return visitor_visit(node->left) + visitor_visit(node->right);
    case NODE_SUB:
        return visitor_visit(node->left) - visitor_visit(node->right);
    case NODE_MUL:
        return visitor_visit(node->left) * visitor_visit(node->right);
    case NODE_INT:
        return node->int_value;
    }

    // Should never reach here
    return 0;
}

