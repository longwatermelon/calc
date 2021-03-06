#ifndef LEXER_H
#define LEXER_H

#include <stdlib.h>

struct Token
{
    enum
    {
        TOKEN_ADD,
        TOKEN_SUB,
        TOKEN_INT,
        TOKEN_MUL,
        TOKEN_DIV,
        TOKEN_EOL
    } type;

    int value;
};

void token_free(struct Token *t);

struct Lexer
{
    char *expr;
    size_t idx;
    char curr_ch;
};

struct Lexer *lexer_alloc(char *expr);
void lexer_free(struct Lexer *self);

void lexer_advance(struct Lexer *self);
int lexer_collect_int(struct Lexer *self);

struct Token lexer_get_next_token(struct Lexer *self);

#endif

