#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "json_token.h"
#include "json_parser.h"

char *read_file(char *file_name) {
  FILE *fptr = fopen(file_name, "rb");
  if (fptr == NULL) {
    return NULL;
  }

  // obtain file size:
  fseek(fptr, 0, SEEK_END);
  size_t file_size = ftell(fptr);
  rewind(fptr);

  char *buffer = (char *)malloc(file_size + 1);

  size_t bytes_read = fread(buffer, 1, file_size, fptr);
  buffer[bytes_read] = '\0';

  fclose(fptr);
  return buffer;
}

int get_percentage_value(int value, int percentage) {
  return (percentage * value) / 100;
}

char *num_to_str(int num) {
  int copy = num;
  int digits = 0;
  while (copy != 0) {
    copy /= 10;
    digits++;
  }
  char *str = malloc(sizeof(char) * (digits + 1));
  int i = 0;
  while (num != 0) {
    str[digits - i - 1] = (num % 10) + '0';
    num /= 10;
    i++;
  }
  str[digits] = '\0';
  return str;
}
