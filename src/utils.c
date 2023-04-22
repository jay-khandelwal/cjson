#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "json_token.h"
#include "json_parser.h"

char *read_file(char *file_name) {
  FILE *fptr = fopen(file_name, "rb");
  if (fptr == NULL) {
    return NULL;
  }

  // obtain file size:
  fseek(fptr, 0, SEEK_END);
  size_t file_size = ftell(fptr);
  rewind(fptr);

  char *buffer = (char *)malloc(file_size + 1);

  size_t bytes_read = fread(buffer, 1, file_size, fptr);
  buffer[bytes_read] = '\0';

  fclose(fptr);
  return buffer;
}

int get_percentage_value(int value, int percentage) {
  return (percentage * value) / 100;
}

char *num_to_str(int num) {
  int copy = num;
  int digits = 0;
  while (copy != 0) {
    copy /= 10;
    digits++;
  }
  char *str = malloc(sizeof(char) * (digits + 1));
  int i = 0;
  while (num != 0) {
    str[digits - i - 1] = (num % 10) + '0';
    num /= 10;
    i++;
  }
  str[digits] = '\0';
  return str;
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

char *get_json_data_in_string(json_element_t *node, char *string) {
  json_object_t *object_ptr;
  json_array_t *array_ptr;
  json_property_t *properties_ptr;
  json_element_t *element;
  char *_string;
  int *num;

  if (string == NULL) {
    string = malloc(sizeof(char) * 5000);
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
      get_json_data_in_string(properties_ptr[i].value, string);
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
      get_json_data_in_string(element, string);
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
    strcat(string, "NULL");
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
