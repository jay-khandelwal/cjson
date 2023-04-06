#include "json_parser.h"
#include "json_token.h"
#include "utils.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  char *buffer = read_file("helper/json_files/basic.json");
  int tokens_count;

  json_token_t *tokens = tokenize(buffer, &tokens_count);

  if (tokens == NULL) {
    perror("Invalid JSON");
    exit(EXIT_FAILURE);
  }

  parser(tokens, tokens_count);

  free(tokens);
  free(buffer);
  return 0;
}
