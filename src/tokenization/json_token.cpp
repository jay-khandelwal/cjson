#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include "json_token.h"
#include "errors.h"

#define input_length_percentage 20;

// tokens
#define OBJECT_START_CHARATER '{'
#define OBJECT_END_CHARATER '}'
#define ARRAY_OPEN_CHARATER '['
#define ARRAY_END_CHARATER ']'
#define STRING_START_CHARATER '"'
#define TRUE_START_CHARATER 't'
#define FALSE_START_CHARATER 'f'
#define NULL_START_CHARATER 'n'
#define COLON_CHARATER ':'
#define COMMA_CHARATER ','

json_token_t *tokenize(char *input)
{
#ifdef DEBUG
    printf("Debug message \n");
#endif
    char *input_pos = input;
    int curr_array_pos = 0, tokens_array_len = 0;
    int obj_key_len;

#ifdef DEBUG
    char *string_ptr;
#endif

    json_token_t *tokens;
    container_t curr_container;
    token_state_t next_state = TOKEN_STATE_START;

    // If this token_array_len won't be sufficent then will reallocate more.
    tokens_array_len = forcast_token_number(strlen(input));

    // Allocating memory to store tokens
    tokens = (json_token_t *)malloc(sizeof(json_token_t) * tokens_array_len);

    // return invalid_json_error();

    while (*input_pos != '\0')
    {
        // printf("%c \n", *input_pos);
        // skip_whitespace(input_pos);
        while (isspace(*input_pos))
        {
            input_pos++;
        }

        // printf("%c", *input_pos);

        switch (next_state)
        {
        case TOKEN_STATE_START:
            switch (*input_pos)
            {
            case OBJECT_START_CHARATER:
                next_state = TOKEN_STATE_KEY;
                curr_container = CONTAINER_OBJECT;
                tokens[curr_array_pos] = new_token(TOKEN_TYPE_OBJECT_BEGIN, input_pos, NULL);
                curr_array_pos++;
                break;

            case ARRAY_OPEN_CHARATER:
                curr_container = CONTAINER_ARRAY;
                tokens[curr_array_pos] = new_token(TOKEN_TYPE_ARRAY_START, input_pos, NULL);
                curr_array_pos++;
                break;

            default:
                // return invalid_json_error();
                break;
            }
            break;

        case TOKEN_STATE_KEY:
            obj_key_len = get_string_length(input_pos);

            if (obj_key_len == NULL)
            {
                debug_printf("Something wrong with the key \n");
                return invalid_json_error();
            }

            debug_print_string_from_input(input_pos, obj_key_len);

            next_state = TOKEN_STATE_COLON;
            tokens[curr_array_pos] = new_token(TOKEN_TYPE_STRING, input_pos, input_pos + obj_key_len);

            // subtracting 1 bcz in the end of while loop we were always incrementing input_pos by 1
            input_pos += obj_key_len - 1;
            curr_array_pos++;
            break;

        case TOKEN_STATE_COLON:
            if (*input_pos != COLON_CHARATER)
            {
                debug_printf("Colon expected \n");
                return invalid_json_error();
            }
            tokens[curr_array_pos] = new_token(TOKEN_TYPE_COLON, input_pos, input_pos);
            next_state = TOKEN_STATE_VALUE;
            curr_array_pos++;

        // case TOKEN_STATE_VALUE:
            // obj_key_len = get_string_length(input_pos);

            // if (obj_key_len == NULL)
            // {
            //     debug_printf("Something wrong with the key \n");
            //     return invalid_json_error();
            // }

            // debug_print_string_from_input(input_pos, obj_key_len);

            // next_state = TOKEN_STATE_START;
            // tokens[curr_array_pos] = new_token(TOKEN_TYPE_STRING, input_pos, input_pos + obj_key_len);

            // // subtracting 1 bcz in the end of while loop we were always incrementing input_pos by 1
            // input_pos += obj_key_len - 1;
            // curr_array_pos++;
            // break;

        }
        input_pos++;
    }

    print_tokens(tokens, curr_array_pos);
    return tokens;
}

json_token_t new_token(token_type_t token_type, char *start_ptr, char *end_ptr)
{
    json_token_t token = {token_type, start_ptr, end_ptr};
    return token;
}

int forcast_token_number(int input_length)
{
    // will use input_length_percentage here!!
    return (20 / input_length) * 100;
}

void skip_whitespace(char *input)
{
    while (isspace(*input))
    {
        input++;
    }
}

void print_tokens(json_token_t *tokens, int curr_array_pos)
{
    for (int i = 0; i < curr_array_pos; i++)
    {
        debug_printf("%d \n", tokens[i].type);
    }
}

int invalid_json_error()
{
    errno = -1;
    return NULL;
}

int get_string_length(char *input)
{

    if (*input == *(input + 1))
    {
        printf("h1 \n");
        return NULL;
    }

    // counter=1 bcz for `"`
    int counter = 1;

    for (size_t i = 1; input[i] != '"'; i++)
    {
        counter++;
    }

    counter++; // for last `"`

    return counter;
}

void print_string_from_input(char *input, int string_len)
{
    char string_ptr[string_len + 1];
    string_ptr[string_len] = '\0';
    strncpy(string_ptr, input, string_len);
    puts(string_ptr);
}