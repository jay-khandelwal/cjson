#include "json_parser.h"
#include "json_token.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

json_element_t *parser(json_token_t *tokens, int tokens_count) {
  json_element_t *node = get_json_values(tokens, NULL);
  printf("done \n");
  return node;
}

json_element_t *get_json_values(json_token_t *token,
                                json_element_t *parent_element) {
  // static json_token_t token = &tokens;
  int key_count = 0;
  // static var = 0;
  // var++;
  int key_length, curr_key, curr_capacity, *number;
  char *key, *string;
  json_property_t *properties;
  json_object_t *curr_object;
  json_element_t *curr_node;
  json_element_t *values;
  json_array_t *curr_array;

  if (token->type == TOKEN_TYPE_COMMA || token->type == TOKEN_TYPE_COLON) {
    token++;
  }

  printf("add: %lu \n", token);

  printf("token is %d \n", token->type);

  switch (token->type) {
  case TOKEN_TYPE_OBJECT_BEGIN:
    token++;
    curr_key = 0;
    curr_capacity = 10;
    properties = malloc(sizeof(json_property_t) * curr_capacity);

    curr_object = malloc(sizeof(json_object_t) * 1);
    curr_object->capacity = curr_capacity;
    curr_object->length = curr_capacity;
    curr_object->pairs = properties;

    curr_node = malloc(sizeof(json_element_t) * 1);
    curr_node->type = JSON_TYPE_OBJECT;
    curr_node->value = curr_object;
    curr_node->parent = parent_element;

    while (token->type != TOKEN_TYPE_OBJECT_END) {
      switch (token->type) {
      case TOKEN_TYPE_KEY:

        key_count++;

        key_length = labs(token->end - token->start);
        key = malloc(sizeof(char) * key_length);
        strncpy(key, token->start, key_length);
        properties[curr_key].key = key;
        properties[curr_key].value =
            get_json_values(token + 1, curr_node); // +2 for escaping colon;
        curr_key++;
        break;
      case TOKEN_TYPE_COMMA:
        break;
      default:
        break;
      }
      printf("addd: %lu \n", token);
      token++;
    }
    printf("object ends \n");
    token++;
    return curr_node;
    break;

  case TOKEN_TYPE_ARRAY_START:
    token++;
    curr_key = 0;
    curr_capacity = 10;
    values = malloc(sizeof(json_element_t) * curr_capacity);
    curr_array = malloc(sizeof(json_array_t) * 1);
    curr_array->capacity = curr_capacity;
    curr_array->length = curr_capacity;
    curr_array->value = values;

    curr_node = malloc(sizeof(json_element_t) * 1);
    curr_node->type = JSON_TYPE_ARRAY;
    curr_node->value = curr_array;
    curr_node->parent = parent_element;

    while (token->type != TOKEN_TYPE_ARRAY_END) {
      if (token->type == TOKEN_TYPE_COMMA) {
        continue;
      }
      values[curr_key].value = get_json_values(token + 2, curr_node);
    }

    token++;
    return curr_node;
    break;

  default:
    token++;
    curr_node = malloc(sizeof(json_element_t) * 1);
    curr_node->type = JSON_TYPE_NULL;
    curr_node->value = NULL;
    curr_node->parent = parent_element;
    return curr_node;
    break;
  }
}

// if (token->type==TOKEN_TYPE_OBJECT_BEGIN)
// {
//   int curr_key = 0;
//   int curr_capacity = 10;
//   json_property_t *properties =
//   malloc(sizeof(json_property_t)*curr_capacity); json_object_t *curr_object =
//   {curr_capacity, curr_capacity, properties}; json_element_t *curr_node =
//   {JSON_TYPE_OBJECT, curr_object, parent_element};

//   token++;

//   while (token->type!=TOKEN_TYPE_OBJECT_END)
//   {
//     switch (token->type)
//     {
//     case TOKEN_TYPE_KEY:
//       key_length = labs(token->end - token->start);
//       key = malloc(sizeof(char)*key_length);
//       strncpy(key, token->start, key_length);
//       printf("aa %s \n", key);
//       properties[curr_key].key = key;
//       properties[curr_key].value = get_json_values(token+1, curr_node); // +2
//       for escaping colon; curr_key++; break;
//     case TOKEN_TYPE_COMMA:
//       break;
//     default:
//       break;
//     }

//     printf("curr_key : %d \n", curr_key);

//     token++;
//   }
//   token++;
//   return curr_node;
// }

// else if (token->type==TOKEN_TYPE_ARRAY_START)
// {
//   curr_key = 0;
//   curr_capacity = 10;
//   json_element_t *values = malloc(sizeof(json_element_t)*curr_capacity);
//   json_array_t *curr_array = {curr_capacity, curr_array, values};
//   json_element_t *curr_node = {JSON_TYPE_ARRAY, curr_array, parent_element};

//   token++;

//   while (token->type!=TOKEN_TYPE_ARRAY_END)
//   {
//     if (token->type ==TOKEN_TYPE_COMMA){
//       continue;
//     }
//     values[curr_key].value = get_json_values(token+2, curr_node);
//   }

//   token++;
//   return curr_node;

// }

// else{
//   printf("in else \n");
//   json_element_t *curr_node = {JSON_TYPE_NULL, NULL, parent_element};
//   token++;
//   return curr_node;
// }

// else if (token->type==TOKEN_TYPE_STRING)
// {
//   key_length = labs(token->end - token->start);
//   *string = malloc(sizeof(char)*key_length);
//   strncpy(string, token->start, key_length);
//   json_element_t *curr_node = {JSON_TYPE_STRING, string, parent_element};

//   token++;
//   return curr_node;
// }

// else if (token->type==TOKEN_TYPE_NUMBER)
// {
//   key_length = labs(token->end - token->start);
//   string = malloc(sizeof(char)*key_length);
//   strncpy(string, token->start, key_length);
//   number = atoi(string);
//   json_element_t *curr_node = {JSON_TYPE_NUMBER, number, parent_element};

//   token++;
//   return curr_node;
// }

// else if (token->type==TOKEN_TYPE_NULL)
// {
//   json_element_t *curr_node = {JSON_TYPE_NULL, NULL, parent_element};

//   token++;
//   return curr_node;
// }

// else if (token->type==TOKEN_TYPE_TRUE)
// {
//   json_element_t *curr_node = {JSON_TYPE_TRUE, NULL, parent_element};

//   token++;
//   return curr_node;
// }

// else if (token->type==TOKEN_TYPE_FALSE)
// {
//   json_element_t *curr_node = {TOKEN_TYPE_FALSE, NULL, parent_element};

//   token++;
//   return curr_node;
// }

// else{
//   debug_printf("stucks with some unknow thing \n");
//   return NULL;
// }

// }
