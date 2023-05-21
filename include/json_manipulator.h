json_element_t *json_new_object();
json_element_t *json_new_array();
json_element_t *json_new_number(int number);
json_element_t *json_new_string(char string[]);
json_element_t *json_new_boolean(int boolean);
void *json_object_add(json_element_t *json_object_node, char key[],
                      json_element_t *value);
void *json_array_append(json_element_t *json_object_node,
                        json_element_t *value);
json_property_t create_pair(char key[], json_element_t *value);
json_element_t *json_object_get(json_element_t *json_object_node, char key[]);
json_element_t *json_array_get(json_element_t *json_array_node, int index);
void *json_object_remove(json_element_t *json_object_node, char key[]);
void *json_array_remove(json_element_t *json_array_node, int index);
