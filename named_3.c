#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
  // fork 2
  size_t len;
  int f = open("pipe_two", O_RDONLY);
  read(f, &len, sizeof(len));
  char *line = (char*)malloc(len * sizeof(char));
  read(f, line, len * sizeof(char));
  close(f);
  puts(line);
  free(line);
}
