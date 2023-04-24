# cjson

cjson is a library for parsing and manipulating JSON in C programming language. It provides a set of functions to parse, create, and modify JSON data.

`json_element_t` is a C struct used to represent various JSON datatypes, such as strings, numbers, arrays, objects, and more. This struct provides a way to store JSON data in a C program and manipulate it using various functions.

## JSON Helper Functions

This is a collection of helper functions to create JSON objects, arrays, numbers, strings, and booleans, as well as add, retrieve, and remove elements from objects and arrays.

### json_element_tjson_new_object()

This function creates a new empty JSON object and returns a `json_element_t` datatype.

An object is a collection of key-value pairs, where the keys are strings and the values can be any JSON datatype (objects, arrays, numbers, strings, booleans, or null). You can use this function to create a new object and then add key-value pairs to it.

### json_element_t json_new_array()

This function creates a new empty JSON array and returns a `json_element_t` datatype.

An array is an ordered list of values, where each value can be any JSON datatype. You can use this function to create a new array and then add values to it.

### json_element_tjson_new_number(int number)

This function takes an integer as an argument and returns a `json_element_t` datatype representing that number.

JSON numbers are similar to numbers in programming languages. As of now can only be positive integer. You can use this function to create a new number element with the specified integer value.

### json_element_tjson_new_string(char string[])

This function takes a character array as an argument and returns a `json_element_t` datatype representing that string.

JSON strings are a sequence of zero or more Unicode characters, wrapped in double quotes. You can use this function to create a new string element with the specified character array.

### json_element_tjson_new_boolean(int boolean)

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
