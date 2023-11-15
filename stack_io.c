#include "monty.h"

/**
 * pall - Prints all the values on the stack
 * starting from the top of the stack
 * @stack: Stack
 * @line_num: Line number
 */
void pall(stack_t **stack, unsigned int line_num)
{
	stack_t *curr = *stack;
	(void) line_num;

	if (curr == NULL)
		return;

	while (curr != NULL)
	{
		printf("%d\n", curr->n);
		curr = curr->next;
	}
}

/**
 * pint - Prints the value at the top of the stack
 * @stack: Stack
 * @line_num: Line number
 */
void pint(stack_t **stack, unsigned int line_num)
{
	if (*stack == NULL)
	{
		fprintf(stderr, "L%d: can't pint, stack empty\n", line_num);
		exit(EXIT_FAILURE);
	}
	printf("%d\n", (*stack)->n);
}

/**
 * nop - The opcode that doesn’t do anything
 * @stack: Stack
 * @line_num: Line number
 */
void nop(stack_t **stack, unsigned int line_num)
{
	(void)stack;
	(void)line_num;
}

/**
 * pchar - Prints the char at the top of the stack
 * @stack: Stack
 * @line_num: Line number
 */
void pchar(stack_t **stack, unsigned int line_num)
{
	int ascii_val;

	if (*stack == NULL)
	{
		fprintf(stderr, "L%d: can't pchar, stack empty\n", line_num);
		exit(EXIT_FAILURE);
	}

	ascii_val = (*stack)->n;
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
 */
void files(const char *fn)
{
	stack_t *s = NULL;
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

		process_opcode(op, &s, line_num, file);
		line_num++;
	}
	fclose(file);
	free_stack(&s);

}
