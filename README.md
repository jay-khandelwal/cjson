# cjson

cjson is a library for parsing and manipulating JSON in C programming language. It provides a set of functions to parse, create, and modify JSON data.

`json_element_t` is a C struct used to represent various JSON datatypes, such as strings, numbers, arrays, objects, and more. This struct provides a way to store JSON data in a C program and manipulate it using various functions.

## JSON Helper Functions

This is a collection of helper functions to create JSON objects, arrays, numbers, strings, and booleans, as well as add, retrieve, and remove elements from objects and arrays.

### json_element_t *json_new_object()

This function creates a new empty JSON object and returns a `json_element_t` datatype.

An object is a collection of key-value pairs, where the keys are strings and the values can be any JSON datatype (objects, arrays, numbers, strings, booleans, or null). You can use this function to create a new object and then add key-value pairs to it.

### json_element_t *json_new_array()

This function creates a new empty JSON array and returns a `json_element_t` datatype.

An array is an ordered list of values, where each value can be any JSON datatype. You can use this function to create a new array and then add values to it.

### json_element_t *json_new_number(int number)

This function takes an integer as an argument and returns a `json_element_t` datatype representing that number.

JSON numbers are similar to numbers in programming languages. As of now can only be positive integer. You can use this function to create a new number element with the specified integer value.

### json_element_t *json_new_string(char string[])

This function takes a character array as an argument and returns a `json_element_t` datatype representing that string.

JSON strings are a sequence of zero or more Unicode characters, wrapped in double quotes. You can use this function to create a new string element with the specified character array.

### json_element_t *json_new_boolean(int boolean)

This function takes an integer as an argument. If the integer is greater than 0, it returns a `json_element_t` datatype representing true. Otherwise, it returns a `json_element_t` datatype representing false.

JSON boolean values can be either true or false. You can use this function to create a new boolean element with the specified integer value.

### void json_object_add(json_element_t *json_object_node, char key[], json_element_t *value)`

This function adds a key-value pair to an existing JSON object. It takes a pointer to the object node, a string key, and a pointer to the value node as arguments.

### void json_array_append(json_element_t *json_array_node, json_element_t *value)

This function appends a value to an existing JSON array. It takes a pointer to the array node and a pointer to the value node as arguments.

### json_element_t *json_object_get(json_element_t *json_object_node, char key[])

This function retrieves the value associated with a specified key from an existing JSON object. It takes a pointer to the object node and a string key as arguments. It returns a pointer to the value node, or NULL if the key is not found.

### json_element_t *json_array_get(json_element_t *json_array_node, size_t index)

This function retrieves the value at a specified index from an existing JSON array. It takes a pointer to the array node and an index as arguments. It returns a pointer to the value node, or NULL if the index is out of range.

### void json_object_remove(json_element_t *json_object_node, char key[])

This function removes a key-value pair from an existing JSON object. It takes a pointer to the object node and a string key as arguments.

### void json_array_remove(json_element_t *json_array_node, size_t index)

This function removes a value from an existing JSON array. It takes a pointer to the array node and an index as arguments.

## Example

## sample JSON (person-info.json)
```json
{
  "name": "John Doe",
  "age": 30,
  "address": {
    "street": "123 Main St",
    "city": "Anytown",
    "state": "CA",
    "zip": "12345"
  }
}
```

## sample code
```c
#include <stdio.h>
#include <stdlib.h>
#include "cjson.h"

int main() {
  // read the contents of the JSON file into a buffer
  char *buffer = read_file("person-info.json");

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

  // add a new key-value pair with JSON boolean as its value to the "address"
  // object
  json_object_add(address_object, "\"isPrimaryResidence\"",
                  json_new_boolean(1));

  // create a new JSON array and append values to it
  json_element_t *hobbies_array = json_new_array();
  json_array_append(hobbies_array, json_new_string("\"reading\""));
  json_array_append(hobbies_array, json_new_string("\"traveling\""));

  // add a new key-value pair with the JSON array as its value to the top-level
  // JSON object
  json_object_add(json_data, "\"hobbies\"", hobbies_array);

  // add a new key-value pair with JSON boolean as its value to the top-level
  // JSON object
  json_object_add(json_data, "\"birthYear\"", json_new_number(1985));

  // extract value from the JSON array by index
  json_element_t *second_hobby = json_array_get(hobbies_array, 1);
  printf("second_hobby: %s \n", json_to_string(second_hobby, NULL));

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
```

