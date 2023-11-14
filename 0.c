#include "monty.h"


void swap(stack_t **stack, unsigned int line_num)
{
	int temp;

	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%d: can't swap, stack too short\n", line_num);
		exit(EXIT_FAILURE);
	}

	temp = (*stack)->n;
	(*stack)->n = (*stack)->next->n;
	(*stack)->next->n = temp;
}
void push(stack_t **stack, unsigned int line_num)
{
	int val;
	char *argument;
	stack_t *new_node;

	argument = strtok(NULL, " \t\n");
	if (!argument)
	{
		fprintf(stderr, "L%d: usage: push integer\n", line_num);
		exit(EXIT_FAILURE);
	}
	val = atoi(argument);
	if (val == 0 && strcmp(argument, "0") != 0)
	{
		fprintf(stderr, "L%d: usage: push integer\n", line_num);
		exit(EXIT_FAILURE);
	}
	new_node = malloc(sizeof(stack_t));
	if (new_node == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}
	new_node->n = val;
	new_node->prev = NULL;
	new_node->next = *stack;
	if (*stack != NULL)
		(*stack)->prev = new_node;
	*stack = new_node;
}

void pall(stack_t **stack, unsigned int line_num)
{
	stack_t *curr = *stack;
	(void) line_num;

	while (curr != NULL)
	{
		printf("%d\n", curr->n);
		curr = curr->next;
	}
}

void pint(stack_t **stack, unsigned int line_num)
{
	if (*stack == NULL)
	{
		fprintf(stderr, "L%d: can't print, stack empty\n", line_num);
		exit(EXIT_FAILURE);
	}
	printf("%d\n", (*stack)->n);
}

void pop(stack_t **stack, unsigned int line_num)
{
	stack_t *r;

	if (*stack == NULL)
	{
		fprintf(stderr, "L%d: can't pop an empty stack\n", line_num);
		exit(EXIT_FAILURE);
	}
	r = *stack;
	*stack = (*stack)->next;
	if (*stack != NULL)
		(*stack)->prev = NULL;
	free(r);
}


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
	else
	{
		fprintf(stderr, "L%d: unkown instruction %s\n", line_num, op);
		fclose(file);
		exit(EXIT_FAILURE);
	}
}

void files(const char *fn)
{
	stack_t *s = NULL;
	FILE *file = fopen(fn, "r");
	char line[256];
	unsigned int line_num = 1;

	if (file == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", fn);
		exit(EXIT_FAILURE);
	}
	while (fgets(line, sizeof(line), file) != NULL)
	{
		char *op = strtok(line, " \t\n");

		if (op != NULL)
		{
			process_opcode(op, &s, line_num, file);
			line_num++;
		}
	}
	fclose(file);
	free_stack(&s);
}

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
