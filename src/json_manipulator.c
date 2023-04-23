#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "json_token.h"
#include "json_parser.h"
#include "json_manipulator.h"

// not in use @deprecated
json_property_t create_pair(char key[], json_element_t *value) {
  json_property_t pair;
  pair.key = key;
  pair.value = value;
  return pair;
}

json_element_t *json_new_object() {
  json_element_t *new_object_node = malloc(sizeof(json_element_t));
  json_object_t *new_object = malloc(sizeof(json_object_t));
  new_object->length = 0;
  new_object_node->type = JSON_TYPE_OBJECT;
  new_object_node->value = new_object;
  return new_object_node;
}

json_element_t *json_new_array() {
  json_element_t *new_object_node = malloc(sizeof(json_element_t));
  json_array_t *new_array = malloc(sizeof(json_array_t));
  new_array->length = 0;
  new_object_node->type = JSON_TYPE_ARRAY;
  new_object_node->value = new_array;
  return new_object_node;
}

json_element_t *json_new_number(int number) {
  json_element_t *new_int_node = malloc(sizeof(json_element_t));
  int *num = malloc(sizeof(int));
  *num = number;
  new_int_node->type = JSON_TYPE_NUMBER;
  new_int_node->value = num;
  return new_int_node;
}

json_element_t *json_new_string(char *string) {
  json_element_t *new_int_node = malloc(sizeof(json_element_t));
  char *str = malloc(sizeof(char) * (strlen(string) + 1));
  strcpy(str, string);
  str[strlen(string)] = '\0';
  new_int_node->type = JSON_TYPE_STRING;
  new_int_node->value = str;
  return new_int_node;
}

json_element_t *json_new_boolean(int num) {
  char *str;
  json_element_t *new_boolean_node = malloc(sizeof(json_element_t));
  if (num > 0) {
    str = malloc(sizeof(char) * 5);
    strcpy(str, "true");
    str[4] = '\0';
    new_boolean_node->type = JSON_TYPE_TRUE;
  } else {
    str = malloc(sizeof(char) * 6);
    strcpy(str, "false");
    str[5] = '\0';
    new_boolean_node->type = JSON_TYPE_FALSE;
  }
  new_boolean_node->value = str;
  // verify if free worth
  free(str);
  return new_boolean_node;
}

void *json_object_add(json_element_t *json_object_node, char key[],
                      json_element_t *value) {
  json_object_t *json_object;
  json_property_t new_pair;

  new_pair.key = malloc(sizeof(char) * (strlen(key) + 1));
  new_pair.key[strlen(key)] = '\0';
  strcpy(new_pair.key, key);
  new_pair.value = value;

  if (json_object_node->type != JSON_TYPE_OBJECT) {
    debug_printf("pair can only be added in json object");
    return NULL;
  }

  json_object = (json_object_t *)json_object_node->value;

  for (size_t i = 0; i < json_object->length; i++) {
    if (strcmp(json_object->pairs[i].key, key) == 0) {
      free(json_object->pairs[i].value);
      json_object->pairs[i].value = value;
      return NULL;
    }
  }

  if (json_object->length == 0) {
    json_object->pairs = (json_property_t *)malloc(sizeof(json_property_t));
  } else {
    json_object->pairs =
        realloc(json_object->pairs,
                sizeof(json_property_t) * (json_object->length + 1));
  }

  if (json_object->pairs == NULL) {
    return NULL;
  }
  json_object->pairs[json_object->length] = new_pair;
  json_object->length += 1;

  return NULL;
}

void *json_array_append(json_element_t *json_array_node,
                        json_element_t *value) {
  json_array_t *json_array;

  if (json_array_node->type != JSON_TYPE_ARRAY) {
    debug_printf("element can only be added in json array");
    return NULL;
  }
  json_array = (json_array_t *)json_array_node->value;
  if (json_array->length == 0) {
    json_array->values = (json_element_t **)malloc(sizeof(json_element_t *));
  } else {
    json_array->values = realloc(
        json_array->values, sizeof(json_element_t) * json_array->length + 1);
  }
  json_array->values[json_array->length] = value;
  json_array->length += 1;
  return NULL;
}

json_element_t *json_object_get(json_element_t *json_object_node, char key[]) {
  json_object_t *json_object;

  if (json_object_node->type != JSON_TYPE_OBJECT) {
    debug_printf("pair can only be added in json object");
    return NULL;
  }

  json_object = (json_object_t *)json_object_node->value;

  for (size_t i = 0; i < json_object->length; i++) {
    if (strcmp(json_object->pairs[i].key, key) == 0) {
      return json_object->pairs[i].value;
    }
  }
  debug_printf("key not found. \n");
  return NULL;
}

json_element_t *json_array_get(json_element_t *json_array_node, int index) {
  json_array_t *json_array;

  if (json_array_node->type != JSON_TYPE_ARRAY) {
    debug_printf("element can only be added in json array");
    return NULL;
  }

  json_array = (json_array_t *)json_array_node->value;

  if (index >= json_array->length) {
    debug_printf("Index out of range \n");
  }
  return json_array->values[index]->value;
}

void *json_object_remove(json_element_t *json_object_node, char key[]) {
  json_object_t *json_object;

  if (json_object_node->type != JSON_TYPE_OBJECT) {
    debug_printf("pair can only be added in json object");
    return NULL;
  }

  json_object = (json_object_t *)json_object_node->value;

  for (size_t i = 0; i < json_object->length; i++) {
    if (strcmp(json_object->pairs[i].key, key) == 0) {
      json_object->pairs[i] = json_object->pairs[json_object->length - 1];
      json_object->length--;
      json_object->pairs = realloc(json_object->pairs, sizeof(json_property_t) *
                                                           json_object->length);
    }
  }
  return NULL;
}

void *json_array_remove(json_element_t *json_array_node, int index) {
  json_array_t *json_array;

  if (json_array_node->type != JSON_TYPE_ARRAY) {
    debug_printf("element can only be added in json array");
    return NULL;
  }

  json_array = (json_array_t *)json_array_node->value;

  if (index >= json_array->length) {
    debug_printf("Index out of range \n");
    return NULL;
  }
  free(json_array->values[index]->value);
  for (size_t i = index; i < json_array->length - 1; i++) {
    json_array->values[i] = json_array->values[i + 1];
  }
  json_array->length--;
  json_array->values =
      realloc(json_array->values, sizeof(json_element_t) * json_array->length);
  return NULL;
}
