#include "lexer.h"
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
    struct Token t;

    while ((t = lexer_get_next_token(lexer)).type != TOKEN_EOL)
    {
        printf("Type %d | Value %s\n", t.type, t.value);
    }

    lexer_free(lexer);

    return 0;
}

