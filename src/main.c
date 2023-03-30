#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "json_token.h"
#include "utils.h"

int main()
{
    FILE *fptr;
    long file_size;
    char *buffer;

    fptr = fopen("helper/json_files/quotes.json", "rb");

    if (fptr == NULL)
    {
        return 1;
    }

    fseek(fptr, SEEK_SET, SEEK_END);
    file_size = ftell(fptr);
    rewind(fptr);

    buffer = (char *)malloc(sizeof(char) * file_size);

    fread(buffer, 1, file_size, fptr);

    if (tokenize(buffer) == NULL)
    {
        perror("Invalid JSON");
        exit(EXIT_FAILURE);
    }

    // json_state_tokenization("{\"name\":\"John\",\"age\":30,\"city\":null, \"married\":false, \"alcoholic\":true}");
    return 0;
}