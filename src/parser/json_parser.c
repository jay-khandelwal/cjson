#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "json_token.h"
#include "json_parser.h"
#include "utils.h"

json_element_t *parser(json_token_t *tokens, int tokens_count) {
  json_element_t *node = get_json_values(&tokens, tokens_count, NULL);
  // print_node(node);
  // printf("\n");
  return node;
}

json_element_t *get_json_values(json_token_t **tokens, int tokens_count,
                                json_element_t *parent_element) {

  json_token_t *token = *tokens;
  json_element_t *curr_node, **values;
  json_object_t *curr_object;
  json_array_t *curr_array;
  json_property_t *properties;
  int string_length, curr_capacity, curr_index, *num;
  char *string;

  static int num_int = 0;

  num_int++;

  // check if colon needed
  if (token->type == TOKEN_TYPE_COMMA || token->type == TOKEN_TYPE_COLON) {
    token++;
  }

  switch (token->type) {

  case TOKEN_TYPE_OBJECT_BEGIN:
    token++;
    curr_index = 0;
    curr_capacity = get_percentage_value(tokens_count, 20);

    curr_object = malloc(sizeof(json_object_t) * 1);
    curr_node = create_node(JSON_TYPE_OBJECT, curr_object, parent_element);
    properties =
        (json_property_t *)malloc(sizeof(json_property_t) * curr_capacity);

    // adding properties data
    while (!(token->type == TOKEN_TYPE_OBJECT_END ||
             token->type == TOKEN_TYPE_NONE)) {

      // reallocating memory
      if (curr_index == curr_capacity - 1) {
        curr_capacity *= 2;
        properties =
            realloc(properties, sizeof(json_property_t) * curr_capacity);
        if (properties == NULL) {
          return NULL;
        }
      }

      if (token->type == TOKEN_TYPE_KEY) {

        // fetching key
        string_length = labs(token->end - token->start);
        string = malloc(sizeof(char) * (string_length + 1));
        strncpy(string, token->start, string_length);
        string[string_length] = '\0';
        properties[curr_index].key = string;

        // incrementing token
        // incrementing by 2, to get move to key's value. excaping colon token
        token += 2;

        // fetching key's value
        properties[curr_index].value =
            get_json_values(&token, tokens_count, curr_node);
        curr_index++;

        // breaking loop on objects end
        if (token->type == TOKEN_TYPE_OBJECT_END) {
          break;
        }

        token++;

      } else {
        debug_printf("key else error \n");
        return NULL;
      }
    }

    // reallocating properties
    properties = realloc(properties, sizeof(json_token_t) * curr_index);

    // updating object length and pair
    // pair should only be update after all the properties pointer gets filled &
    // also reallocated. because at reallocating pointer address gets changed
    curr_object->length = curr_index;
    curr_object->pairs = properties;

    break;

  case TOKEN_TYPE_ARRAY_START:
    token++;
    curr_index = 0;
    curr_capacity = get_percentage_value(tokens_count, 20);

    curr_array = malloc(sizeof(json_array_t) * 1);
    curr_node = create_node(JSON_TYPE_ARRAY, curr_array, parent_element);
    values =
        (json_element_t **)malloc(sizeof(json_element_t *) * curr_capacity);

    while (!(token->type == TOKEN_TYPE_ARRAY_END ||
             token->type == TOKEN_TYPE_NONE)) {
      // reallocating memory
      if (curr_index == curr_capacity - 1) {
        curr_capacity *= 2;
        values = realloc(values, sizeof(json_element_t) * curr_capacity);
        if (values == NULL) {
          return NULL;
        }
      }

      values[curr_index] = get_json_values(&token, tokens_count, curr_node);
      curr_object = (json_object_t *)values[curr_index]->value;
      curr_index++;
      if (token->type == TOKEN_TYPE_ARRAY_END) {
        break;
      }
      token++;
    }

    // reallocating values
    values = realloc(values, sizeof(json_element_t) * curr_index);

    curr_array->length = curr_index;
    curr_array->values = values;

    break;

  case TOKEN_TYPE_STRING:
    string_length = labs(token->end - token->start);
    string = malloc(sizeof(char) * (string_length + 1));
    strncpy(string, token->start, string_length);
    string[string_length] = '\0';
    curr_node = create_node(JSON_TYPE_STRING, string, parent_element);
    break;

  case TOKEN_TYPE_NUMBER:
    string_length = labs(token->end - token->start);
    string = malloc(sizeof(char) * string_length);
    strncpy(string, token->start, string_length);
    num = malloc(sizeof(int) * 1);
    *num = atoi(string);
    curr_node = create_node(JSON_TYPE_NUMBER, num, parent_element);
    break;

  case TOKEN_TYPE_TRUE:
    curr_node = create_node(JSON_TYPE_TRUE, NULL, parent_element);
    break;

  case TOKEN_TYPE_FALSE:
    curr_node = create_node(JSON_TYPE_FALSE, NULL, parent_element);
    break;

  case TOKEN_TYPE_NULL:
    curr_node = create_node(JSON_TYPE_NULL, NULL, parent_element);
    break;

  // check it
  default:
    printf("num_int: %d \n", num_int);
    printf("default type me: %d \n", token->type);
    curr_node = malloc(sizeof(json_element_t) * 1);
    curr_node->type = JSON_TYPE_NULL;
    curr_node->value = NULL;
    curr_node->parent = parent_element;
    break;
  }
  token++;
  *tokens = token;
  return curr_node;
}

void print_node(json_element_t *node) {
  json_object_t *object_ptr;
  json_array_t *array_ptr;
  json_property_t *properties_ptr;
  json_element_t *element;
  char *string;
  int *num;

  switch (node->type) {
  case JSON_TYPE_OBJECT:
    printf("{ ");
    object_ptr = (json_object_t *)node->value;
    properties_ptr = (json_property_t *)object_ptr->pairs;
    for (int i = 0; i < object_ptr->length; i++) {
      if (i > 0) {
        printf(" , ");
      }
      printf("%s", properties_ptr[i].key);
      printf(": ");
      print_node(properties_ptr[i].value);
    }
    printf(" }");
    break;

  case JSON_TYPE_ARRAY:
    printf("[ ");
    array_ptr = (json_array_t *)node->value;
    for (int i = 0; i < array_ptr->length; i++) {
      if (i > 0) {
        printf(" , ");
      }
      element = array_ptr->values[i];
      print_node(element);
    }
    printf(" ]");
    break;

  case JSON_TYPE_STRING:
    string = (char *)(char *)node->value;
    printf("%s", string);
    break;

  case JSON_TYPE_NUMBER:
    num = (int *)(int *)node->value;
    printf("%d", *num);
    break;

  case JSON_TYPE_NULL:
    printf(" NULL");
    break;

  case JSON_TYPE_TRUE:
    printf(" true");
    break;

  case JSON_TYPE_FALSE:
    printf(" false");
    break;

  default:
    break;
  }
}

json_element_t *create_node(json_type node_type, void *node_value,
                            json_element_t *node_parent) {
  json_element_t *node = malloc(sizeof(json_element_t) * 1);
  node->type = node_type;
  node->value = node_value;
  node->parent = node_parent;
  return node;
}

json_object_t *create_json_object(json_property_t *properties) {
  json_object_t *json_object = malloc(sizeof(json_object_t) * 1);
  json_object->pairs = properties;
  return json_object;
}
