// #define DEBUG

#ifdef DEBUG
#define debug_printf(...) printf(__VA_ARGS__)
#define debug_print_string_from_input(...) print_string_from_input(__VA_ARGS__)
#else
#define debug_printf(...)
#define debug_print_string_from_input(...)
#endif

typedef enum token_type_t
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

} token_type_t;

typedef enum token_state_t
{
    TOKEN_STATE_START,
    TOKEN_STATE_KEY,
    TOKEN_STATE_KEY_END,
    TOKEN_STATE_VALUE,
    TOKEN_STATE_VALUE_END,
    TOKEN_STATE_END,
} token_state_t;

typedef enum container_t
{
    CONTAINER_OBJECT,
    CONTAINER_ARRAY
} container_t;

typedef struct container_depth_t
{
    int depth;
    container_t container;
    struct container_depth_t *parent;
} container_depth_t;

typedef struct json_token_t
{
    token_type_t type;
    char *start;
    char *end;
} json_token_t;

json_token_t *tokenize(char *input);
json_token_t new_token(token_type_t token_type, char *start_ptr, char *end_ptr);
int forcast_token_number(int input_length);
void skip_whitespace(char *input);
void print_tokens(json_token_t *tokens, int token_no);
int invalid_json_error();
int get_string_length(char *input);
int get_number_length(char *input);
int compare_value_from_input(char *input, int counter, char cmp_value[]);
void print_string_from_input(char *input, int string_len);
container_depth_t *get_new_container_depth(container_t container, container_depth_t *parent);
container_depth_t *get_container_depth_parent(container_depth_t *container_depth);
void print_container_depth(container_depth_t *container_depth);

// // json_token *tokenize_json_string(char *input);
// json_token *json_state_tokenization(char *input);
// // static void get_string_count(char *input, int curr_pos, int *counter);
// static void print_tokenized_data(json_token *json_token_arr);

// // struct json_obj
// // {
// //     char *key;
// //     enum json_type type;
// //     union
// //     {
// //         char * str;
// //         int num;
// //         struct json_obj obj;
// //         json_array arr;
// //     } value;

// // };

// typedef enum token_state_t
// {
//     TOKEN_STATE_START,
//     // TOKEN_STATE_OBJECT_START,
//     // TOKEN_STATE_OBJECT_END,
//     // TOKEN_STATE_ARRAY_START,
//     // TOKEN_STATE_ARRAY_END,
//     TOKEN_STATE_COLON,
//     // TOKEN_STATE_COMMA,
//     TOKEN_STATE_KEY,
//     TOKEN_STATE_VALUE,
//     TOKEN_STATE_VALUE_END,
//     // TOKEN_STATE_NUMBER,
//     TOKEN_STATE_END,
// } token_state_t;

// typedef enum token_state_t
// {
//     TOKEN_STATE_START,
//     TOKEN_STATE_KEY,
//     TOKEN_STATE_KEY_END,
//     TOKEN_STATE_VALUE,
//     TOKEN_STATE_VALUE_END,
//     TOKEN_STATE_END,
// } token_state_t;

// switch(){

//     case TOKEN_STATE_START:
//         switch (charater)
//         {
//         case '{':
//             next_state = TOKEN_STATE_KEY
//             break;

//         case '[':
//             next_state = TOKEN_STATE_VALUE
//             break;

//         default:
//             //raise error
//             break;
//         }
//         break;

//     case TOKEN_STATE_VALUE:
//         //object start
//         //array start
//         //string
//         //number
//         //boolean
//         //null
//         switch (character)
//         {
//         case '{'
//             next_state = TOKEN_STATE_KEY
//             break;

//         case '['
//             next_state = TOKEN_STATE_VALUE
//             break;

//         case '"':
//             // fetch string
//             next_state = TOKEN_STATE_VALUE_END
//             break;

//         case 'number':
//             // fetch number
//             next_state = TOKEN_STATE_VALUE_END
//             break;

//         case 'boolean':
//             // fetch boolean
//             next_state = TOKEN_STATE_VALUE_END
//             break;

//         case 'null':
//             // fetch null
//             next_state = TOKEN_STATE_VALUE_END

//         default:
//             // raise error
//             break;
//         }
//         break;

//     case TOKEN_STATE_KEY:
//         // check the string and set next_state as TOKEN_STATE_COLON
//         next_state = TOKEN_STATE_COLON
//         break;

//     case TOKEN_STATE_COLON:
//         // char should be `:`
//         next_state = TOKEN_STATE_VALUE
//         break;

//     case TOKEN_STATE_VALUE_END:
//         // char should be ' , ' or '}' in case of container is object or ']' in case of container is array
//         // if depth =0, means the json ends
//         // if greatet that 0 means its inside some object or array
//         switch (character)
//         {
//         case ',':
//             if (container=object)
//             {
//                 next_state = TOKEN_STATE_KEY
//             }

//             else if (container=array)
//             {
//                 next_state = TOKEN_STATE_VALUE
//             }

//             else{
//                 //raise error
//             }

//         case '}':
//             // check if input charater is also ']. means object over
//             next_state = TOKEN_STATE_VALUE_END
//             break;

//         case ']':
//             // check if input charater is also ']. means array over
//             next_state = TOKEN_STATE_VALUE_END
//             break;

//         default:
//             //raise error
//             break;
//         }
//         break;
// }