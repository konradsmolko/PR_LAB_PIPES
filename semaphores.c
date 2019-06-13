// Proces macierzysty
// Zadanie: wczytać ciąg znaków i przekazać dalej
char *line = NULL;
size_t len = 0;
puts("input text to process");
getline(&line, &len, stdin);
int f = open("pipe_one", O_WRONLY);
printf("%i = open\n", f);
write(f, &len, sizeof(len));
write(f, line, len * sizeof(char));
close(f);
free(line);
