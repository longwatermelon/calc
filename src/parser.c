#include "parser.h"
#include "lexer.h"
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
        switch (self->tokens[i].type)
        {
        case TOKEN_ADD:
            root = parser_parse_add(self, root, i);
            break;
        default:
            continue;
        }
    }

    return root;
}


struct Node *parser_parse_add(struct Parser *self, struct Node *root, int token)
{
    struct Node* node = malloc(sizeof(struct Node));
    node->type = NODE_ADD;

    if (!root) // Encountered first operator, no expressions possible on left
    {
        node->left = malloc(sizeof(struct Node));
        node->left->type = NODE_INT;
        node->left->int_value = atoi(self->tokens[token - 1].value);
    }
    else
    {
        node->left = root;
    }

    node->right = malloc(sizeof(struct Node));
    node->right->type = NODE_INT;
    node->right->int_value = atoi(self->tokens[token + 1].value);

    return node;
}

