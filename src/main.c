#include "json_token.h"
#include "utils.h"

int main()
{
    char *buffer = read_file("helper/json_files/big_chunk.json");

    json_token_t *tokens = tokenize(buffer);

    if  (tokens== NULL)
    {
        perror("Invalid JSON");
        exit(EXIT_FAILURE);
    }

    free(tokens);
    free(buffer);
    return 0;
}