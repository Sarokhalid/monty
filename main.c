#include "monty.h"

/**
 * main - Entry point of the program
 * @argc: Argument Count
 * @argv: Argument vector
 * Return: 0 on success, EXIT_FAILURE on failure
 */
int main(int argc, char *argv[])
{
	const char *fn = argv[1] ? argv[1] : "";
	monty_t monty = {0, NULL};
	int error;

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}

	error = files(fn, &monty);
	if (error != 0)
		exit(EXIT_FAILURE);

	return (EXIT_SUCCESS);
}
