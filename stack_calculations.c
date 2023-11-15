#include "monty.h"

/**
 * add - Adds the top two elements of the stack
 * @stack: Stack
 * @line_num: Line number
 */
void add(stack_t **stack, unsigned int line_num)
{
	int sum;
	stack_t *first, *second;

	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%d: can't add, stack too short\n", line_num);
		exit(EXIT_FAILURE);
	}
	if (mode == 0)  /* Stack mode */
	{
		first = *stack;
		second = (*stack)->next;
	}
	else  /* Queue mode */
	{
		first = *stack;
		while (first->next != NULL)
			first = first->next;
		second = first->prev;
	}

	sum = first->n + second->n;
	pop(stack, line_num);
	(*stack)->n = sum;
}

/**
 * sub - Subtracts the top element of the stack
 * from the second top element of the stack
 * @stack: Stack
 * @line_num: Line number
 */
void sub(stack_t **stack, unsigned int line_num)
{
	int diff;
	stack_t *first, *second;

	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%d: can't sub, stack too short\n", line_num);
		exit(EXIT_FAILURE);
	}

	if (mode == 0)  /* Stack mode */
	{
		first = *stack;
		second = (*stack)->next;
	}
	else  /* Queue mode */
	{
		first = *stack;
		while (first->next != NULL)
			first = first->next;
		second = first->prev;
	}

	diff = first->n - second->n;
	pop(stack, line_num);
	(*stack)->n = diff;
}
/**
 * div_stack - Divides the second top element of the stack
 * by the top element of the stack
 * @stack: Stack
 * @line_num: Line number
 */
void div_stack(stack_t **stack, unsigned int line_num)
{
	int quotient;
	stack_t *first, *second;

	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%d: can't div, stack too short\n", line_num);
		exit(EXIT_FAILURE);
	}

	if (mode == 0)  /* Stack mode */
	{
		first = *stack;
		second = (*stack)->next;
	}
	else  /* Queue mode */
	{
		first = *stack;
		while (first->next != NULL)
			first = first->next;
		second = first->prev;
	}

	if (first->n == 0)
	{
		fprintf(stderr, "L%d: division by zero\n", line_num);
		exit(EXIT_FAILURE);
	}

	quotient = second->n / first->n;
	pop(stack, line_num);
	(*stack)->n = quotient;
}

/**
 * mul - Multiplies the second top element of the stack
 * with the top element of the stack
 * @stack: Stack
 * @line_num: Line number
 */
void mul(stack_t **stack, unsigned int line_num)
{
	int product;
	stack_t *first, *second;

	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%d: can't mul, stack too short\n", line_num);
		exit(EXIT_FAILURE);
	}

	if (mode == 0)  /* Stack mode */
	{
		first = *stack;
		second = (*stack)->next;
	}
	else  /* Queue mode */
	{
		first = *stack;
		while (first->next != NULL)
			first = first->next;
		second = first->prev;
	}

	product = first->n * second->n;
	pop(stack, line_num);
	(*stack)->n = product;
}

/**
 * mod - Computes the remainder of the division of the second
 * top element of the stack by the top element of the stack
 * @stack: Stack
 * @line_num: Line number
 */
void mod(stack_t **stack, unsigned int line_num)
{
	int remainder;
	stack_t *first, *second;

	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%d: can't mod, stack too short\n", line_num);
		exit(EXIT_FAILURE);
	}

	if (mode == 0)  /* Stack mode */
	{
		first = *stack;
		second = (*stack)->next;
	}
	else  /* Queue mode */
	{
		first = *stack;
		while (first->next != NULL)
			first = first->next;
		second = first->prev;
	}

	if (first->n == 0)
	{
		fprintf(stderr, "L%d: division by zero\n", line_num);
		exit(EXIT_FAILURE);
	}

	remainder = second->n % first->n;
	pop(stack, line_num);
	(*stack)->n = remainder;
}
