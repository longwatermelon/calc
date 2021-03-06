#include "lexer.h"
#include "parser.h"
#include "visitor.h"
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char **argv)
{
    if (argc == 1)
    {
        fprintf(stderr, "No expression provided\n");
        exit(1);
    }

    struct Lexer *lexer = lexer_alloc(argv[1]);

    struct Token *tokens = 0;
    int ntokens = 0;

    struct Token t;

    while ((t = lexer_get_next_token(lexer)).type != TOKEN_EOL)
    {
        tokens = realloc(tokens, sizeof(struct Token) * ++ntokens);
        tokens[ntokens - 1] = t;
    }

    struct Parser *parser = parser_alloc(tokens, ntokens);
    struct Node *root = parser_parse(parser);

    float result = visitor_visit(root);
    printf("%f\n", result);

    free(tokens);
    node_free(root);
    lexer_free(lexer);
    parser_free(parser);

    return 0;
}

