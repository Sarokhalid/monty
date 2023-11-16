#include "monty.h"

/**
 * pall - Prints All the values on the stack
 * starting from the top of the stack
 * @monty: Pointer to the current state of the stack.
 * @line_num: Line number
 * Return: 0 in Success, -1 in Error
 */
int pall(monty_t *monty, unsigned int line_num)
{
	stack_t *curr;
	(void)line_num;

	if (monty->stack == NULL)
		return (0);

	for (curr = monty->stack; curr != NULL; curr = curr->next)
	{
		printf("%d\n", curr->n);
	}
	return (0);
}

/**
 * pint - Prints the value at the top of the stack
 * @monty: Pointer to the current state of the stack.
 * @line_num: Line number
 * Return: 0 in Success, -1 in Error
 */
int pint(monty_t *monty, unsigned int line_num)
{
	if (monty->stack == NULL)
	{
		fprintf(stderr, "L%d: can't pint, stack empty\n", line_num);
		return (-1);
	}
	printf("%d\n", (monty->stack)->n);
	return (0);
}

/**
 * nop - The opcode that doesn’t do anything
 * @monty: Pointer to the current state of the stack.
 * @line_num: Line number
 * Return: 0 in Success
 */
int nop(monty_t *monty, unsigned int line_num)
{
	(void)monty;
	(void)line_num;
	return (0);
}

/**
 * pchar - Prints the char at the top of the stack
 * @monty: Pointer to the current state of the stack.
 * @line_num: Line number
 * Return: 0 in Success, -1 in Error
 */
int pchar(monty_t *monty, unsigned int line_num)
{
	int ascii_val;

	if (monty->stack == NULL)
	{
		fprintf(stderr, "L%d: can't pchar, stack empty\n", line_num);
		return (-1);
	}

	ascii_val = (monty->stack)->n;
	if (ascii_val < 0 || ascii_val > 127)
	{
		fprintf(stderr, "L%d: can't pchar, value out of range\n", line_num);
		return (-1);
	}

	printf("%c\n", ascii_val);
	return (0);
}

/**
 * files - Processes the file containing Monty byte codes
 * @fn: File name
 * @monty: Pointer to the current state of the stack.
 * Return: 0 in Success, -1 in Error
 */
int files(const char *fn, monty_t *monty)
{
	FILE *file = fopen(fn, "r");
	char line[512];
	unsigned int line_num = 1;
	int error;

	if (file == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", fn);
		return (-1);
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

		error = process_opcode(op, monty, line_num);
		if (error != 0)
		{
			fclose(file);
			free_stack(monty);
			return (-1);
		}
		line_num++;
	}
	fclose(file);
	free_stack(monty);
	return (0);
}
