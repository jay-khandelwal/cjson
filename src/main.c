#include "json_token.h"
#include "utils.h"

int main()
{
    char *buffer = read_file("helper/json_files/quotes.json");

    json_token_t *tokens = tokenize(buffer);

    if  (tokens== NULL)
    {
        perror("Invalid JSON");
        exit(EXIT_FAILURE);
    }

    free(buffer);
    free(tokens);
    return 0;
}