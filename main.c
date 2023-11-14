#include "monty.h"

int main(int argc, char *argv[])
{
	const char *fn = argv[1];

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
	files(fn);
	return (0);
}
