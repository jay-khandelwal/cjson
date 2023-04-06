
typedef enum json_type {
  JSON_TYPE_STRING,
  JSON_TYPE_NUMBER,
  JSON_TYPE_OBJECT,
  JSON_TYPE_ARRAY,
  JSON_TYPE_TRUE,
  JSON_TYPE_FALSE,
  JSON_TYPE_NULL
} json_type;

typedef struct json_element_t {
  json_type type;
  void *value;
  struct json_element_t *parent;
} json_element_t;

typedef struct json_property_t {
  char *key;
  json_element_t *value;
} json_property_t;

typedef struct json_object_t {
  size_t length;
  size_t capacity;
  json_property_t *pairs;
} json_object_t;

typedef struct json_array_t {
  size_t length;
  size_t capacity;
  json_element_t *value;
} json_array_t;

json_element_t *parser(json_token_t *tokens, int tokens_count);
json_element_t *get_json_values(json_token_t *token,
                                json_element_t *parent_element);
