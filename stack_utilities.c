#include "monty.h"

/**
 * process_opcode - Processes an Opcode
 * @op: Opcode
 * @monty: Pointer to the current state of the stack.
 * @line_num: Line number
 * Return: 0 in Success, -1 in Error
 */
int process_opcode(char *op, monty_t *monty,
		unsigned int line_num)
{
	int i = 0;
	int error;

	instruction_t opcodes[] = {
		{"push", push}, {"pall", pall}, {"pint", pint}, {"pop", pop}, {"swap", swap},
		{"add", add}, {"nop", nop}, {"sub", sub}, {"div", div_stack}, {"mul", mul},
		{"mod", mod}, {"pchar", pchar}, {"pstr", pstr}, {"rotl", rotl},
		{"rotr", rotr}, {NULL, NULL}
	};

	while (opcodes[i].opcode != NULL)
	{
		if (strcmp(op, opcodes[i].opcode) == 0)
		{
			error = opcodes[i].f(monty, line_num);
			if (error != 0)
				return (-1);
			return (0);
		}
		i++;
	}

	fprintf(stderr, "L%d: unknown instruction %s\n", line_num, op);
	return (-1);
}

/**
 * free_stack - Frees a stack
 * @monty: Pointer to the current state of the stack.
 */
void free_stack(monty_t *monty)
{
	stack_t *current_node = monty->stack;
	stack_t *next_node;

	while (current_node != NULL)
	{
		next_node = current_node->next;
		free(current_node);
		current_node = next_node;
	}
	monty->stack = NULL;
}

/**
 * is_integer - Checks if a string is a valid integer
 * @str: The string to check
 *
 * Return: 1 if the string is a valid integer, 0 otherwise
 */
int is_integer(const char *str)
{
	int i = 0;

	if (str[0] == '-')
		i = 1;
	for (; str[i]; i++)
	{
		if (!isdigit((unsigned char)str[i]))
			return (0);
	}
	return (1);
}
