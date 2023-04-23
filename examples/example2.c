#include <stdio.h>
#include "cjson.h"

/*
reading example2.json file
and adding one more employe data in the employees arrayj
*/

int main() {
  char *buffer = read_file("helper/json_files/employee.json");
  json_element_t *node = parse_json(buffer);

  // Extract `employees` array from json data
  json_element_t *employee_array = json_object_get(node, "\"employees\"");

  // create new employee data object
  json_element_t *new_object = json_new_object();
  json_object_add(new_object, "\"name\"", json_new_string("\"jack sparrow\""));
  json_object_add(new_object, "\"age\"", json_new_number(33));
  json_object_add(new_object, "\"email\"",
                  json_new_string("\"jack.sparrow@dc.com\""));

  // append new employee to employees array
  json_array_append(employee_array, new_object);

  char *str = json_to_string(node, NULL);

  puts(str);

  write_to_file(str, "employee.json");

  return 0;
}
