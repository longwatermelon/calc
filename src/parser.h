#ifndef PARSER_H
#define PARSER_H

struct Node
{
    enum
    {
        NODE_NUM,
        NODE_ADD,
        NODE_SUB,
        NODE_MUL,
        NODE_DIV
    } type;

    // num
    float num_value;

    // operator
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
struct Node *parser_parse_op(struct Parser *self, struct Node *root, int token, int op);

struct Node *parser_num_from_token(struct Parser *self, int token);

#endif

