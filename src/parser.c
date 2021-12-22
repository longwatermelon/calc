#include "parser.h"
#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>

#define PRIORITY_OP(x) (x == NODE_MUL || x == NODE_DIV)

void node_free(struct Node *node)
{
    if (node->type != NODE_NUM)
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

    self->token = 0;

    return self;
}


void parser_free(struct Parser *self)
{
    free(self);
}


struct Node *parser_parse(struct Parser *self)
{
    struct Node *root = 0;

    while (self->token < self->ntokens)
    {
        if (self->tokens[self->token].type == TOKEN_INT)
        {
            ++self->token;
            continue;
        }

        switch (self->tokens[self->token].type)
        {
        case TOKEN_ADD:
            root = parser_parse_op(self, root, NODE_ADD);
            break;
        case TOKEN_SUB:
            root = parser_parse_op(self, root, NODE_SUB);
            break;
        case TOKEN_MUL:
            root = parser_parse_op(self, root, NODE_MUL);
            break;
        case TOKEN_DIV:
            root = parser_parse_op(self, root, NODE_DIV);
            break;
        default: break;
        }
    }

    return root;
}


struct Node *parser_parse_op(struct Parser *self, struct Node *root, int op)
{
    struct Node *node = malloc(sizeof(struct Node));
    node->type = op;

    if (!root) // Encountered first operator, no expressions possible on left
    {
        node->left = parser_num_from_token(self, self->token - 1);
    }
    else
    {
        // If op is not priority (* or /) or the previous node type is priority then evaluate left to right
        if (!PRIORITY_OP(op) || PRIORITY_OP(root->type))
        {
            node->left = root;
        }
        else // Evaluate current expression and attach to root, right to left
        {
            node->left = root->right;
            root->right = node;
        }
    }

    node->right = parser_num_from_token(self, ++self->token);

    // Evaluating left to right, root is part of node
    if (!root || !PRIORITY_OP(op) || PRIORITY_OP(root->type))
        return node;
    else // Evaluating right to left, node is part of root
        return root;
}


struct Node *parser_num_from_token(struct Parser *self, int token)
{
    if (token < 0 || token >= self->ntokens)
    {
        fprintf(stderr, "Error: index out of range (%d)\n", token);
        exit(1);
    }

    if (self->tokens[token].type != TOKEN_INT)
    {
        fprintf(stderr, "Error: expected a number on token %d\n", token + 1);
        exit(1);
    }

    struct Node *node = malloc(sizeof(struct Node));
    node->type = NODE_NUM;
    node->num_value = self->tokens[token].value;

    return node;
}

