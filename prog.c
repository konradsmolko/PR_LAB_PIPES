#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <stdlib.h>

#define ODCZYT 0
#define ZAPIS 1

int main()
{
	int potok[2], potok2[2];
	puts("main starting");
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
		//printf("%i\n", len);
		//puts(line); // Tu jet OK...
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
		close(potok[ZAPIS]);
		read(potok[ODCZYT], &len, sizeof(len));
		char *line = (char*)malloc(len * sizeof(char));
		read(potok[ODCZYT], line, len * sizeof(char));
		close(potok[ODCZYT]);
		//puts("Test...");
		printf("%i\n", len);
		//puts(line);
		// line = (char*)toupper(line);
		for(int i = 0; i < len; i++)
			line[i] = (char)toupper(line[i]);

		close(potok2[ODCZYT]);
		write(potok2[ZAPIS], &len, sizeof(len));
		write(potok2[ZAPIS], line, len * sizeof(char));
		close(potok2[ZAPIS]);
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
		//printf("%i\n", len);
		puts(line);
		free(line);
	}

	return 0;
}
