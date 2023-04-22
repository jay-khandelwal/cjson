#include <stdio.h>
#include <stdlib.h>
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
