#include "monty.h"

/**
 * pall - Prints all the values on the stack
 * starting from the top of the stack
 * @monty: Pointer to the current state of the stack.
 * @line_num: Line number
 */
void pall(monty_t *monty, unsigned int line_num)
{
	stack_t *curr;
	(void)line_num;

	if (monty->stack == NULL)
		return;

	for (curr = monty->stack; curr != NULL; curr = curr->next)
	{
		printf("%d\n", curr->n);
	}
}

/**
 * pint - Prints the value at the top of the stack
 * @monty: Pointer to the current state of the stack.
 * @line_num: Line number
 */
void pint(monty_t *monty, unsigned int line_num)
{
	if (monty->stack == NULL)
	{
		fprintf(stderr, "L%d: can't pint, stack empty\n", line_num);
		exit(EXIT_FAILURE);
	}
	printf("%d\n", (monty->stack)->n);
}

/**
 * nop - The opcode that doesn’t do anything
 * @monty: Pointer to the current state of the stack.
 * @line_num: Line number
 */
void nop(monty_t *monty, unsigned int line_num)
{
	(void)monty;
	(void)line_num;
}

/**
 * pchar - Prints the char at the top of the stack
 * @monty: Pointer to the current state of the stack.
 * @line_num: Line number
 */
void pchar(monty_t *monty, unsigned int line_num)
{
	int ascii_val;

	if (monty->stack == NULL)
	{
		fprintf(stderr, "L%d: can't pchar, stack empty\n", line_num);
		exit(EXIT_FAILURE);
	}

	ascii_val = (monty->stack)->n;
	if (ascii_val < 0 || ascii_val > 127)
	{
		fprintf(stderr, "L%d: can't pchar, value out of range\n", line_num);
		exit(EXIT_FAILURE);
	}

	printf("%c\n", ascii_val);
}

/**
 * files - Processes the file containing Monty byte codes
 * @fn: File name
 * @monty: Pointer to the current state of the stack.
 */
void files(const char *fn, monty_t *monty)
{
	FILE *file = fopen(fn, "r");
	char line[512];
	unsigned int line_num = 1;

	if (file == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", fn);
		exit(EXIT_FAILURE);
	}
	while (fgets(line, sizeof(line), file) != NULL)
	{
		char *op = strtok(line, " \t\n");

		/* If the line is a comment or empty, skip to the next line */
		if (op == NULL || op[0] == '#')
			continue;
		if (strcmp(op, "stack") == 0)
		{
			monty->mode = 0;
			continue;
		}
		else if (strcmp(op, "queue") == 0)
		{
			monty->mode = 1;
			continue;
		}

		process_opcode(op, monty, line_num, file);
		line_num++;
	}
	fclose(file);
	free_stack(monty);

}
