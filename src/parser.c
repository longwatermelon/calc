#include "parser.h"
#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>


void node_free(struct Node *node)
{
    if (node->type != NODE_INT)
    {
        node_free(node->left);
        node_free(node->right);
    }

    free(node);
}


struct Parser *parser_alloc(struct Token *tokens, int ntokens)
{
    struct Parser *self = malloc(sizeof(struct Parser));
    self->tokens = tokens;
    self->ntokens = ntokens;

    return self;
}


void parser_free(struct Parser *self)
{
    free(self);
}


struct Node *parser_parse(struct Parser *self)
{
    struct Node *root = 0;

    for (int i = 0; i < self->ntokens; ++i)
    {
        int type = -1;

        switch (self->tokens[i].type)
        {
        case TOKEN_ADD: type = NODE_ADD; break;
        case TOKEN_SUB: type = NODE_SUB; break;
        case TOKEN_MUL: type = NODE_MUL; break;
        case TOKEN_DIV: type = NODE_DIV; break;
        default: break;
        }

        if (type != -1)
            root = parser_parse_op(self, root, i, type);
    }

    return root;
}


struct Node *parser_parse_op(struct Parser *self, struct Node *root, int token, int op)
{
    // TODO clean this up later
    struct Node *node = malloc(sizeof(struct Node));
    node->type = op;

    if (!root) // Encountered first operator, no expressions possible on left
    {
        node->left = malloc(sizeof(struct Node));
        node->left->type = NODE_INT;
        node->left->int_value = atoi(self->tokens[token - 1].value);
    }
    else
    {
        if (op == NODE_ADD || op == NODE_SUB)
        {
            node->left = root;
        }
        else if (op == NODE_MUL || op == NODE_DIV)
        {
            node->left = root->right;
            root->right = node;
        }
    }

    node->right = malloc(sizeof(struct Node));
    node->right->type = NODE_INT;
    node->right->int_value = atoi(self->tokens[token + 1].value);

    if (op == NODE_ADD || op == NODE_SUB)
        return node;
    else
    {
        if (!root)
            return node;
        else
            return root;
    }
}

