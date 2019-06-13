#include <stdio.h>
#include <unistd.h>
#define ODCZYT 0
#define ZAPIS 1

int main()
{
	int potok[2];
	puts("main starting");
	pipe(potok);

	if(fork())
	{
		// Proces macierzysty
		puts("input text to process");
		char *line = NULL;
		size_t len = 0;
		getline(&line, &len, stdin);

	}
	else
	{
		// Proces potomny

	}

	return 0;
}
