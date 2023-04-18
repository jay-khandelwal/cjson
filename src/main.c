#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "json_token.h"
#include "json_parser.h"
#include "json_manipulator.h"
#include "utils.h"

int main() {
  char *buffer = read_file("helper/json_files/employee.json");
  int tokens_count;
  json_element_t *node;
  json_element_t *value = malloc(sizeof(json_element_t) * 1);

  value->type = JSON_TYPE_TRUE;

  json_token_t *tokens = tokenize(buffer, &tokens_count);

  if (tokens == NULL) {
    perror("Invalid JSON");
    exit(EXIT_FAILURE);
  }

  node = parser(tokens, tokens_count);

  add_json_pair(node, create_pair("\"test_key\"", value));

  print_node(node);
  printf("\n");

  free(tokens);
  free(buffer);
  return 0;
}
