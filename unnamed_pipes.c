#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define ODCZYT 0
#define ZAPIS 1

int main()
{
	int potok[2], potok2[2];
	if (pipe(potok) == -1)
	{
		puts("pipe 1 failed");
		return 1;
	}
	if (pipe(potok2) == -1)
	{
		puts("pipe 2 failed");
		return 2;
	}

	if(fork())
	{
		// Proces macierzysty
		// Zadanie: wczytać ciąg znaków i przekazać dalej
		puts("input text to process");
		char *line = NULL;
		size_t len = 0;
		getline(&line, &len, stdin);
		close(potok[ODCZYT]);
		write(potok[ZAPIS], &len, sizeof(len));
		write(potok[ZAPIS], line, len * sizeof(char));
		close(potok[ZAPIS]);
		free(line);
	}
	else if(fork())
	{
		// fork 1
		// Zadanie: odebrać ciąg znaków, zmienić je na duże litery
		// i przekazać dalej
		size_t len;
		// close(potok[ZAPIS]);
		// read(potok[ODCZYT], &len, sizeof(len));
		int f = open("pipe_one", O_RDONLY);
		read(f, &len, sizeof(len));
		char *line = (char*)malloc(len * sizeof(char));
		// read(potok[ODCZYT], line, len * sizeof(char));
		// close(potok[ODCZYT]);
		read(f, line, len * sizeof(char));
		close(f);

		for(int i = 0; i < len; i++)
			line[i] = (char)toupper(line[i]);

		// close(potok2[ODCZYT]);
		// write(potok2[ZAPIS], &len, sizeof(len));
		// write(potok2[ZAPIS], line, len * sizeof(char));
		// close(potok2[ZAPIS]);

		f = open("pipe_two", O_WRONLY);
		write(f, &len, sizeof(len));
		write(f, line, len * sizeof(char));
		close(f);
		free(line);
	}
	else
	{
		// fork 2
		size_t len;
		close(potok2[ZAPIS]);
		read(potok2[ODCZYT], &len, sizeof(len));
		char *line = (char*)malloc(len * sizeof(char));
		read(potok2[ODCZYT], line, len * sizeof(char));
		close(potok2[ODCZYT]);
		puts(line);
		free(line);
	}

return 0;
}
