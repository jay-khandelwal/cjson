#include <stdio.h>
#include <stdlib.h>
#include "cjson.h"

int main() {
  // read the contents of the JSON file into a buffer
  char *buffer = read_file("helper/json_files/person-info.json");

  // tokenize and parse the JSON data in the buffer
  json_element_t *json_data = parse_json(buffer);

  // extract specific values from the JSON object by key
  json_element_t *name = json_object_get(json_data, "\"name\"");
  json_element_t *age = json_object_get(json_data, "\"age\"");
  json_element_t *address_object = json_object_get(json_data, "\"address\"");
  json_element_t *street = json_object_get(address_object, "\"street\"");
  json_element_t *city = json_object_get(address_object, "\"city\"");
  json_element_t *state = json_object_get(address_object, "\"state\"");
  json_element_t *zip = json_object_get(address_object, "\"zip\"");

  // print the extracted JSON data to the console
  printf("name: %s \n", json_to_string(name, NULL));
  printf("age: %s \n", json_to_string(age, NULL));
  printf("street: %s \n", json_to_string(street, NULL));
  printf("city: %s \n", json_to_string(city, NULL));
  printf("state: %s \n", json_to_string(state, NULL));
  printf("zip: %s \n", json_to_string(zip, NULL));

  // add a new key-value pair to the "address" object
  json_object_add(address_object, "\"isPrimaryResidence\"",
                  json_new_boolean(1));

  // create a new JSON array and append values to it
  json_element_t *hobbies_array = json_new_array();
  json_array_append(hobbies_array, json_new_string("\"reading\""));
  json_array_append(hobbies_array, json_new_string("\"traveling\""));

  // add a new key-value pair with the JSON array as its value to the top-level
  // JSON object
  json_object_add(json_data, "\"hobbies\"", hobbies_array);

  // convert the modified JSON data back into a string
  char *new_buffer = json_to_string(json_data, NULL);

  // print the modified JSON string to the console
  puts(new_buffer);

  // write the modified JSON string to a file
  write_to_file(new_buffer, "updated-person-info.json");

  // free memory used by the JSON elements and buffers
  free(buffer);
  free(new_buffer);
  clean_json_data(json_data);

  return 0;
}
