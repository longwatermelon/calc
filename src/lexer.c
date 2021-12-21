#include "lexer.h"
#include "util.h"
#include <string.h>
#include <ctype.h>
#include <stdio.h>


struct Lexer *lexer_alloc(char *expr)
{
    struct Lexer *self = malloc(sizeof(struct Lexer));
    self->expr = expr;
    self->idx = 0;
    self->curr_ch = expr[self->idx];

    return self;
}


void lexer_free(struct Lexer *self)
{
    free(self);
}


void lexer_advance(struct Lexer *self)
{
    if (self->idx < strlen(self->expr))
    {
        self->curr_ch = self->expr[++self->idx];
    }
}


char *lexer_collect_int(struct Lexer *self)
{
    size_t start = self->idx;

    while (isdigit(self->curr_ch) && self->idx < strlen(self->expr))
        lexer_advance(self);

    size_t len = self->idx - start;

    char *substr = malloc(sizeof(char) * (len + 1));
    memcpy(substr, &self->expr[start], len);
    substr[len] = '\0';

    return substr;
}


struct Token lexer_get_next_token(struct Lexer *self)
{
    while (self->idx < strlen(self->expr))
    {
        while (isspace(self->curr_ch))
            lexer_advance(self);

        if (isdigit(self->curr_ch))
            return (struct Token){
                .type = TOKEN_INT,
                .value = lexer_collect_int(self)
            };

        switch (self->curr_ch)
        {
        case '+':
            lexer_advance(self);
            return (struct Token){
                .type = TOKEN_ADD,
                .value = util_ch_to_str('+')
            };
        case '-':
            lexer_advance(self);
            return (struct Token){
                .type = TOKEN_SUB,
                .value = util_ch_to_str('-')
            };
        case '*':
            lexer_advance(self);
            return (struct Token){
                .type = TOKEN_MUL,
                .value = util_ch_to_str('*')
            };
        case '/':
            lexer_advance(self);
            return (struct Token){
                .type = TOKEN_DIV,
                .value = util_ch_to_str('/')
            };
        }

        fprintf(stderr, "Unrecognized character '%c'\n", self->curr_ch);
        exit(1);
    }

    return (struct Token){ .type = TOKEN_EOL, .value = 0 };
}

