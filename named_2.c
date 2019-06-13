#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
  // fork 1
  // Zadanie: odebrać ciąg znaków, zmienić je na duże litery
  // i przekazać dalej
  size_t len;
  int f = open("pipe_one", O_RDONLY);
  read(f, &len, sizeof(len));
  char *line = (char*)malloc(len * sizeof(char));
  read(f, line, len * sizeof(char));
  close(f);

  for(int i = 0; i < len; i++)
    line[i] = (char)toupper(line[i]);

  f = open("pipe_two", O_WRONLY);
  write(f, &len, sizeof(len));
  write(f, line, len * sizeof(char));
  close(f);
  free(line);
}
