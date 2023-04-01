#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include "json_token.h"
#include "errors.h"

#define input_length_percentage 30 // 29//66

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

#define JSON_TRUE_VALUE "true"
#define JSON_TRUE_VALUE_LEN 4
#define JSON_FALSE_VALUE "false"
#define JSON_FALSE_VALUE_LEN 5
#define JSON_NULL_VALUE "null"
#define JSON_NULL_VALUE_LEN 4

json_token_t *tokenize(char *input)
{
#ifdef DEBUG
    printf("Debug message \n");
    char *string_ptr;
#endif

    char *input_pos = input;
    int curr_array_pos = 0, tokens_array_len = 0;
    int obj_key_len;

    json_token_t *tokens;
    container_depth_t *curr_countainer_depth = NULL;
    token_state_t next_state = TOKEN_STATE_START;

    /*
    Allocating some percentage of input length for tokens
    will reallocate memory in case allocated memory is not sufficent
    */
    tokens_array_len = forcast_token_number(strlen(input));
    tokens = (json_token_t *)malloc(sizeof(json_token_t) * tokens_array_len);

    if (tokens == NULL)
    {
        return NULL;
    }

    while (*input_pos != '\0')
    {
        if (curr_array_pos == tokens_array_len - 1)
        {
            tokens_array_len += tokens_array_len;
            tokens = realloc(tokens, sizeof(json_token_t) * tokens_array_len);
            if (tokens == NULL)
            {
                return NULL;
            }
        }
        while (isspace(*input_pos))
        {
            input_pos++;
        }

        switch (next_state)
        {
        case TOKEN_STATE_START:
            switch (*input_pos)
            {
            case OBJECT_START_CHARATER:
                next_state = TOKEN_STATE_KEY;
                curr_countainer_depth = get_new_container_depth(CONTAINER_OBJECT, curr_countainer_depth);
                tokens[curr_array_pos] = new_token(TOKEN_TYPE_OBJECT_BEGIN, input_pos, input_pos + 1);
                curr_array_pos++;
                break;

            case ARRAY_OPEN_CHARATER:
                next_state = TOKEN_STATE_VALUE;
                curr_countainer_depth = get_new_container_depth(CONTAINER_ARRAY, curr_countainer_depth);
                tokens[curr_array_pos] = new_token(TOKEN_TYPE_ARRAY_START, input_pos, input_pos + 1);
                curr_array_pos++;
                break;

            default:
                return invalid_json_error();
                break;
            }
            break;

        case TOKEN_STATE_KEY:
            obj_key_len = get_string_length(input_pos, 1);

            if (obj_key_len == -1)
            {
                debug_printf("Something wrong with the key \n");
                return invalid_json_error();
            }

            debug_print_string_from_input(input_pos, obj_key_len);

            next_state = TOKEN_STATE_KEY_END;
            tokens[curr_array_pos] = new_token(TOKEN_TYPE_STRING, input_pos, input_pos + obj_key_len); // subtracting `-1` maybe check
            curr_array_pos++;
            input_pos += obj_key_len - 1;
            break;

        case TOKEN_STATE_KEY_END:
            if (*input_pos != COLON_CHARATER)
            {
                return invalid_json_error();
            }
            tokens[curr_array_pos] = new_token(TOKEN_TYPE_COLON, input_pos, input_pos + 1);
            next_state = TOKEN_STATE_VALUE;
            curr_array_pos++;
            break;

        case TOKEN_STATE_VALUE:
            switch (*input_pos)
            {
            case OBJECT_START_CHARATER:
                next_state = TOKEN_STATE_KEY;
                curr_countainer_depth = get_new_container_depth(CONTAINER_OBJECT, curr_countainer_depth);
                tokens[curr_array_pos] = new_token(TOKEN_TYPE_OBJECT_BEGIN, input_pos, input_pos + 1);
                curr_array_pos++;
                break;
            case ARRAY_OPEN_CHARATER:
                next_state = TOKEN_STATE_VALUE;
                curr_countainer_depth = get_new_container_depth(CONTAINER_ARRAY, curr_countainer_depth);
                tokens[curr_array_pos] = new_token(TOKEN_TYPE_ARRAY_START, input_pos, input_pos + 1);
                curr_array_pos++;
                break;

            case STRING_START_CHARATER:
                obj_key_len = get_string_length(input_pos, 0);

                if (obj_key_len == -1)
                {
                    debug_printf("Something wrong with the key \n");
                    return invalid_json_error();
                }

                debug_print_string_from_input(input_pos, obj_key_len);

                next_state = TOKEN_STATE_VALUE_END;
                tokens[curr_array_pos] = new_token(TOKEN_TYPE_STRING, input_pos, input_pos + obj_key_len);
                curr_array_pos++;
                input_pos += obj_key_len - 1;
                break;

            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                obj_key_len = get_number_length(input_pos);

                debug_print_string_from_input(input_pos, obj_key_len);

                next_state = TOKEN_STATE_VALUE_END;
                tokens[curr_array_pos] = new_token(TOKEN_TYPE_NUMBER, input_pos, input_pos + obj_key_len);
                curr_array_pos++;
                input_pos += obj_key_len - 1;
                break;

            case TRUE_START_CHARATER:
                if (compare_value_from_input(input_pos, JSON_TRUE_VALUE_LEN, JSON_TRUE_VALUE) == 0)
                {
                    next_state = TOKEN_STATE_VALUE_END;
                    tokens[curr_array_pos] = new_token(TOKEN_TYPE_TRUE, input_pos, input_pos + JSON_TRUE_VALUE_LEN);
                    curr_array_pos++;
                    input_pos += JSON_TRUE_VALUE_LEN - 1;
                }
                else
                {
                    return invalid_json_error();
                }
                break;

            case FALSE_START_CHARATER:
                if (compare_value_from_input(input_pos, JSON_FALSE_VALUE_LEN, JSON_FALSE_VALUE) == 0)
                {
                    next_state = TOKEN_STATE_VALUE_END;
                    tokens[curr_array_pos] = new_token(TOKEN_TYPE_FALSE, input_pos, input_pos + JSON_FALSE_VALUE_LEN);
                    curr_array_pos++;
                    input_pos += JSON_FALSE_VALUE_LEN - 1;
                }
                else
                {
                    return invalid_json_error();
                }
                break;

            case NULL_START_CHARATER:
                if (compare_value_from_input(input_pos, JSON_NULL_VALUE_LEN, JSON_NULL_VALUE) == 0)
                {
                    next_state = TOKEN_STATE_VALUE_END;
                    tokens[curr_array_pos] = new_token(TOKEN_TYPE_NULL, input_pos, input_pos + JSON_NULL_VALUE_LEN);
                    curr_array_pos++;
                    input_pos += JSON_NULL_VALUE_LEN - 1;
                }
                else
                {
                    return invalid_json_error();
                }
                break;

            default:
                break;
            }
            break;

        case TOKEN_STATE_VALUE_END:
            switch (*input_pos)
            {
            case COMMA_CHARATER:
                if (curr_countainer_depth->container == CONTAINER_OBJECT)
                {
                    next_state = TOKEN_STATE_KEY;
                }
                else if (curr_countainer_depth->container == CONTAINER_ARRAY)
                {
                    next_state = TOKEN_STATE_VALUE;
                }
                else
                {
                    printf("in else \n");
                    // this won't always means json is incorrect. it may means something is wrong with the code
                    return invalid_json_error();
                }
                tokens[curr_array_pos] = new_token(TOKEN_TYPE_COMMA, input_pos, input_pos + 1);
                curr_array_pos++;
                break;

            case OBJECT_END_CHARATER:
            case ARRAY_END_CHARATER:
                curr_countainer_depth = get_container_depth_parent(curr_countainer_depth);
                if (curr_countainer_depth == NULL)
                {
                    next_state = TOKEN_STATE_END;
                }
                else
                {
                    next_state = TOKEN_STATE_VALUE_END;
                }
                break;

            default:
                return invalid_json_error();
            }
            break;

        case TOKEN_STATE_END:
            if (*input_pos=='\0'){
                continue;
            }
            return invalid_json_error();

        default:
            return invalid_json_error();
            break;
        }
        input_pos++;
    }
    // print_container_depth(curr_countainer_depth); // not working bcz it is null
    // print_tokens(tokens, curr_array_pos);
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
    return (input_length_percentage * input_length) / 100;
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

void *invalid_json_error()
{
    errno = -1;
    return NULL;
}


// `is_key=1` means using for getting key count
// needed to check if string is not blank
// because key cannot be blank `""`
int get_string_length(char *input, int is_key)
{

    if (is_key && (*input == *(input + 1)))
    {
        return -1;
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

int get_number_length(char *input)
{
    int counter = 0;

    for (size_t i = 0; isdigit(input[i]); i++)
    {
        counter++;
    }

    return counter;
}

int compare_value_from_input(char *input, int counter, char cmp_value[])
{
    char input_value[counter + 1];
    strncpy(input_value, input, counter);
    input_value[counter] = '\0';
    return strcmp(input_value, cmp_value);
}

void print_string_from_input(char *input, int string_len)
{
    char string_ptr[string_len + 1];
    strncpy(string_ptr, input, string_len);
    string_ptr[string_len] = '\0';
    puts(string_ptr);
}

container_depth_t *get_new_container_depth(container_t container, container_depth_t *parent)
{
    container_depth_t *new_container_depth = malloc(sizeof(container_depth_t));

    if (new_container_depth == NULL)
    {
        return NULL;
    }

    if (parent == NULL)
    {
        new_container_depth->depth = 1;
    }
    else
    {
        new_container_depth->depth = parent->depth + 1;
    }
    new_container_depth->container = container;
    new_container_depth->parent = parent;
    return new_container_depth;
}

container_depth_t *get_container_depth_parent(container_depth_t *container_depth)
{
    container_depth_t *parent = container_depth->parent;
    free(container_depth);
    return parent;
}

void print_container_depth(container_depth_t *container_depth)
{
    if (container_depth->parent != NULL)
    {
        print_container_depth(container_depth->parent);
    }
    printf("container is %d, depth is %d, parent is %d \n", container_depth->container, container_depth->depth, container_depth->parent != NULL);
}