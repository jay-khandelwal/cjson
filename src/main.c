#include "json_token.h"
#include "utils.h"

int main()
{
    char *buffer = read_file("helper/json_files/big_chunk.json");

    // puts(buffer);

    // for (int i=0; buffer[i]!='\0'; i++){
    //     printf("%c \n", buffer[i]);
    // }

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