

typedef enum token_type
{
    TOKEN_TYPE_NONE,
    TOKEN_TYPE_OBJECT_BEGIN,
    TOKEN_TYPE_OBJECT_END,
    TOKEN_TYPE_ARRAY_START,
    TOKEN_TYPE_ARRAY_END,
    TOKEN_TYPE_STRING,
    TOKEN_TYPE_NUMBER,
    TOKEN_TYPE_TRUE,
    TOKEN_TYPE_FALSE,
    TOKEN_TYPE_NULL,
    TOKEN_TYPE_COMMA,
    TOKEN_TYPE_COLON,

} token_type;


typedef struct json_token
{
    token_type type;
    char *value;
} json_token;

// json_token *tokenize_json_string(char *input);
json_token *json_state_tokenization(char *input);
// static void get_string_count(char *input, int curr_pos, int *counter);
static void print_tokenized_data(json_token *json_token_arr);



// struct json_obj
// {
//     char *key;
//     enum json_type type;
//     union
//     {
//         char * str;
//         int num;
//         struct json_obj obj;
//         json_array arr;
//     } value;

// };


typedef enum token_state
{
    TOKEN_STATE_START,
    TOKEN_STATE_OBJECT_START,
    TOKEN_STATE_OBJECT_END,
    TOKEN_STATE_ARRAY_START,
    TOKEN_STATE_ARRAY_END,
    TOKEN_STATE_COLON,
    TOKEN_STATE_COMMA,
    TOKEN_STATE_KEY,
    TOKEN_STATE_VALUE,
    TOKEN_STATE_NUMBER,
    TOKEN_STATE_END,
    // TOKEN_STATE_STRING_START,
    // TOKEN_STATE_STRING_END,
} token_state;