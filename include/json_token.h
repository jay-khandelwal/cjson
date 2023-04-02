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
void *invalid_json_error();
int get_string_length(char *input, int is_key);
int get_number_length(char *input);
int compare_value_from_input(char *input, int counter, char cmp_value[]);
void print_string_from_input(char *input, int string_len);
container_depth_t *get_new_container_depth(container_t container, container_depth_t *parent);
container_depth_t *get_container_depth_parent(container_depth_t *container_depth);
void print_container_depth(container_depth_t *container_depth);
