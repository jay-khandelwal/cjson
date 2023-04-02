#include <stdio.h>
#include <stdlib.h>

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
