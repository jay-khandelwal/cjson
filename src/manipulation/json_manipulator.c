#include <stdlib.h>
#include "json_token.h"
#include "json_parser.h"
#include "json_manipulator.h"

// void add_json_object;
// void remove_json_object;
// void modify_json_object;
// void append_json_element;
// void remove_json_element_by_index;

json_property_t create_pair(char key[], json_element_t *value) {
  json_property_t pair;
  pair.key = key;
  pair.value = value;
  return pair;
}

// json_element_t create_value(){
//     json_element_t node;
// }

json_element_t *add_json_pair(json_element_t *json_object_node,
                              json_property_t pair) {
  json_object_t *json_object;
  json_property_t *json_pairs;

  if (json_object_node->type != JSON_TYPE_OBJECT) {
    debug_printf("pair can only be added inn json object");
    return NULL;
  }

  json_object = (json_object_t *)json_object_node->value;
  json_pairs = json_object->pairs;
  json_pairs =
      realloc(json_pairs, sizeof(json_property_t) * json_object->length);
  if (json_pairs == NULL) {
    return NULL;
  }
  json_pairs[json_object->length] = pair;
  json_object->length += 1;
  return json_object_node;
}
