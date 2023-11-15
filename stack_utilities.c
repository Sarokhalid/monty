#include "monty.h"

/**
 * process_opcode - Processes an opcode
 * @op: Opcode
 * @s: Stack
 * @line_num: Line number
 * @file: File
 */
void process_opcode(char *op, stack_t **s, unsigned int line_num, FILE *file)
{
	if (strcmp(op, "push") == 0)
		push(s, line_num);
	else if (strcmp(op, "pall") == 0)
		pall(s, line_num);
	else if (strcmp(op, "pint") == 0)
		pint(s, line_num);
	else if (strcmp(op, "pop") == 0)
		pop(s, line_num);
	else if (strcmp(op, "swap") == 0)
		swap(s, line_num);
	else if (strcmp(op, "add") == 0)
		add(s, line_num);
	else if (strcmp(op, "nop") == 0)
		nop(s, line_num);
	else if (strcmp(op, "sub") == 0)
		sub(s, line_num);
	else if (strcmp(op, "div") == 0)
		div_stack(s, line_num);
	else if (strcmp(op, "mul") == 0)
		mul(s, line_num);
	else if (strcmp(op, "mod") == 0)
		mod(s, line_num);
	else if (strcmp(op, "pchar") == 0)
		pchar(s, line_num);
	else if (strcmp(op, "pstr") == 0)
		pstr(s, line_num);
	else if (strcmp(op, "rotl") == 0)
		rotl(s, line_num);
	else if (strcmp(op, "rotr") == 0)
		rotr(s, line_num);
	else
	{
		fprintf(stderr, "L%d: unknown instruction %s\n", line_num, op);
		fclose(file);
		exit(EXIT_FAILURE);
	}
}

/**
 * free_stack - Frees a stack
 * @stack: Stack
 */
void free_stack(stack_t **stack)
{
	stack_t *current_node = *stack;
	stack_t *next_node;

	while (current_node != NULL)
	{
		next_node = current_node->next;
		free(current_node);
		current_node = next_node;
	}
	*stack = NULL;
}

/**
 * is_integer - Checks if a string is a valid integer
 * @str: The string to check
 *
 * Return: 1 if the string is a valid integer, 0 otherwise
 */
int is_integer(const char *str)
{
	int i;

	if (str[0] == '+' || str[0] == '-')
	{
		i = 1;
	}
	else
	{
		i = 0;
	}

	for (; str[i] != '\0'; i++)
	{
		if (!isdigit(str[i]))
		{
			return (0);
		}
	}
	return (1);
}
