#include "visitor.h"


float visitor_visit(struct Node *node)
{
    // TODO use floats
    switch (node->type)
    {
    case NODE_ADD:
        return visitor_visit(node->left) + visitor_visit(node->right);
    case NODE_SUB:
        return visitor_visit(node->left) - visitor_visit(node->right);
    case NODE_MUL:
        return visitor_visit(node->left) * visitor_visit(node->right);
    case NODE_DIV:
        return visitor_visit(node->left) / visitor_visit(node->right);
    case NODE_NUM:
        return node->num_value;
    }

    // Should never reach here
    return 0;
}

