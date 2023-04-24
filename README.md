# cjson

cjson is a library for parsing and manipulating JSON in C programming language. It provides a set of functions to parse, create, and modify JSON data.

## JSON Helper Functions

This is a collection of helper functions to create JSON objects, arrays, numbers, strings, and booleans.

### `json_new_object()`

This function creates a new empty JSON object and returns a `json_element_t` datatype.

An object is a collection of key-value pairs, where the keys are strings and the values can be any JSON datatype (objects, arrays, numbers, strings, booleans, or null). You can use this function to create a new object and then add key-value pairs to it.

### `json_new_array()`

This function creates a new empty JSON array and returns a `json_element_t` datatype.

An array is an ordered list of values, where each value can be any JSON datatype. You can use this function to create a new array and then add values to it.

### `json_new_number(int number)`

This function takes an integer as an argument and returns a `json_element_t` datatype representing that number.

JSON numbers are similar to numbers in programming languages. As of now can only be positive integer. You can use this function to create a new number element with the specified integer value.

### `json_new_string(char string[])`

This function takes a character array as an argument and returns a `json_element_t` datatype representing that string.

JSON strings are a sequence of zero or more Unicode characters, wrapped in double quotes. You can use this function to create a new string element with the specified character array.

### `json_new_boolean(int boolean)`

This function takes an integer as an argument. If the integer is greater than 0, it returns a `json_element_t` datatype representing true. Otherwise, it returns a `json_element_t` datatype representing false.

JSON boolean values can be either true or false. You can use this function to create a new boolean element with the specified integer value.
