#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "json_token.h"
#include "json_parser.h"
#include "utils.h"

json_element_t *parse_json(char *input) {
  int tokens_count;

  json_token_t *tokens = tokenize(input, &tokens_count);

  if (tokens == NULL) {
    perror("Invalid JSON");
    exit(EXIT_FAILURE);
  }

  json_element_t *node;
  node = parser(tokens, tokens_count);
  free(tokens);
  return node;
}

void *clean_json_data(json_element_t *node) {
  json_object_t *object_ptr;
  json_array_t *array_ptr;
  json_property_t *properties_ptr;
  json_element_t *element;
  char *string;
  int *num;

  switch (node->type) {
  case JSON_TYPE_OBJECT:
    object_ptr = (json_object_t *)node->value;
    properties_ptr = (json_property_t *)object_ptr->pairs;
    for (int i = 0; i < object_ptr->length; i++) {
      if (properties_ptr[i].key == NULL) {
        continue;
      }
      free(properties_ptr[i].key);
      clean_json_data(properties_ptr[i].value);
    }
    if (object_ptr->length > 0) {
      free(properties_ptr);
    }
    free(object_ptr);
    break;

  case JSON_TYPE_ARRAY:
    array_ptr = (json_array_t *)node->value;
    for (int i = 0; i < array_ptr->length; i++) {
      element = array_ptr->values[i];
      clean_json_data(element);
    }
    if (array_ptr->length > 0) {
      free(array_ptr->values);
    }
    free(array_ptr);
    break;

  case JSON_TYPE_STRING:
    string = (char *)(char *)node->value;
    free(string);
    break;

  case JSON_TYPE_NUMBER:
    num = (int *)node->value;
    free(num);
    break;

  case JSON_TYPE_NULL:
    break;

  case JSON_TYPE_TRUE:
    break;

  case JSON_TYPE_FALSE:
    break;

  default:
    break;
  }
  free(node);
  return NULL;
}

char *json_to_string(json_element_t *node, char *string) {
  json_object_t *object_ptr;
  json_array_t *array_ptr;
  json_property_t *properties_ptr;
  json_element_t *element;
  char *_string;
  int *num;

  if (string == NULL) {
    string = malloc(sizeof(char) * 10000);
    strcpy(string, "");
  }

  switch (node->type) {
  case JSON_TYPE_OBJECT:
    strcat(string, "{ ");
    object_ptr = (json_object_t *)node->value;
    properties_ptr = (json_property_t *)object_ptr->pairs;
    for (int i = 0; i < object_ptr->length; i++) {
      if (i > 0) {
        strcat(string, ", ");
      }
      strcat(string, properties_ptr[i].key);
      strcat(string, ": ");
      json_to_string(properties_ptr[i].value, string);
    }
    strcat(string, " }");
    break;

  case JSON_TYPE_ARRAY:
    strcat(string, "[ ");
    array_ptr = (json_array_t *)node->value;
    for (int i = 0; i < array_ptr->length; i++) {
      if (i > 0) {
        strcat(string, ", ");
      }
      element = array_ptr->values[i];
      json_to_string(element, string);
    }
    strcat(string, " ]");
    break;

  case JSON_TYPE_STRING:
    _string = (char *)(char *)node->value;
    strcat(string, _string);
    break;

  case JSON_TYPE_NUMBER:
    num = (int *)(int *)node->value;
    _string = num_to_str(*num);
    strcat(string, _string);
    free(_string);
    break;

  case JSON_TYPE_NULL:
    strcat(string, "null");
    break;

  case JSON_TYPE_TRUE:
    strcat(string, "true");
    break;

  case JSON_TYPE_FALSE:
    strcat(string, "false");
    break;

  default:
    break;
  }
  return string;
}
