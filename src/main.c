#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "json_token.h"
#include "json_parser.h"
#include "json_manipulator.h"
#include "utils.h"
#include "cjson.h"

int main() {
  char *buffer = read_file("helper/json_files/employee.json");
  // int tokens_count;

  // json_token_t *tokens = tokenize(buffer, &tokens_count);

  // if (tokens == NULL) {
  //   perror("Invalid JSON");
  //   exit(EXIT_FAILURE);
  // }

  json_element_t *node;
  // node = parser(tokens, tokens_count);
  node = parse_json(buffer); // parser(tokens, tokens_count);

  // creating new json object & adding key/value
  json_element_t *new_object;
  new_object = json_new_object();
  json_object_add(new_object, "\"new_key\"", json_new_number(100));

  // creating new json array & adding element
  json_element_t *new_array;
  new_array = json_new_array();
  json_array_append(new_array, json_new_string("\"in array\""));
  json_array_append(new_array, new_object);

  // modify, adding key/value in json object
  json_object_add(node, "\"employeees\"", json_new_number(100));
  json_object_add(node, "\"new_string\"",
                  json_new_string("\"jay khandelwal\""));
  // json_object_add(node, "\"new_object\"", new_object);
  json_object_add(node, "\"new_array\"", new_array);

  // Extract value from json object
  json_element_t *employee_array;
  employee_array = json_object_get(node, "\"new_array\"");
  json_array_append(employee_array, json_new_string("\"jay khandelwal2\""));

  // json_object_remove(node, "\"new_string\"");

  // json_array_remove(employee_array, 4);

  char *str;
  str = get_json_data_in_string(node, NULL);
  puts(str);

  // print_node(node);
  // printf("\n");

  // print_node(employee_array);
  // printf("\n");

  free(buffer);
  clean_json_data(node);
  return 0;
}
