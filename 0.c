#include "monty.h"

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

void mod(stack_t **stack, unsigned int line_num)
{
	int remainder;

	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%d: can't mod, stack too short\n", line_num);
		exit(EXIT_FAILURE);
	}

	if ((*stack)->n == 0)
	{
		fprintf(stderr, "L%d: division by zero\n", line_num);
		exit(EXIT_FAILURE);
	}

	remainder = (*stack)->next->n % (*stack)->n;
	pop(stack, line_num);
	(*stack)->n = remainder;
}

void mul(stack_t **stack, unsigned int line_num)
{
	int product;

	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%d: can't mul, stack too short\n", line_num);
		exit(EXIT_FAILURE);
	}

	product = (*stack)->next->n * (*stack)->n;
	pop(stack, line_num);
	(*stack)->n = product;
}

void div_stack(stack_t **stack, unsigned int line_num)
{
	int quotient;

	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%d: can't div, stack too short\n", line_num);
		exit(EXIT_FAILURE);
	}

	if ((*stack)->n == 0)
	{
		fprintf(stderr, "L%d: division by zero\n", line_num);
		exit(EXIT_FAILURE);
	}

	quotient = (*stack)->next->n / (*stack)->n;
	pop(stack, line_num);
	(*stack)->n = quotient;
}

void sub(stack_t **stack, unsigned int line_num)
{
	int diff;

	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%d: can't sub, stack too short\n", line_num);
		exit(EXIT_FAILURE);
	}

	diff = (*stack)->next->n - (*stack)->n;
	pop(stack, line_num);
	(*stack)->n = diff;
}

void nop(stack_t **stack, unsigned int line_num)
{
	(void)stack;
	(void)line_num;
}

void add(stack_t **stack, unsigned int line_num)
{
	int sum;

	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%d: can't add, stack too short\n", line_num);
		exit(EXIT_FAILURE);
	}

	sum = (*stack)->n + (*stack)->next->n;
	pop(stack, line_num);
	(*stack)->n = sum;
}

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

		/* If the line is a comment or empty, skip to the next line */
		if (op == NULL || op[0] == '#')
			continue;

		process_opcode(op, &s, line_num, file);
		line_num++;
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
