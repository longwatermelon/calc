#ifndef PARSER_H
#define PARSER_H

struct Node
{
    enum
    {
        NODE_INT,
        NODE_ADD
    } type;

    // int
    int int_value;

    // add
    struct Node *left, *right;
};

void node_free(struct Node *node);

struct Parser
{
    struct Token *tokens;
    int ntokens;
};

struct Parser *parser_alloc(struct Token *tokens, int ntokens);
void parser_free(struct Parser *self);

struct Node *parser_parse(struct Parser *self);

struct Node *parser_parse_add(struct Parser *self, struct Node *root, int token);

#endif

