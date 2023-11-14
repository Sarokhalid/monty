#include "monty.h"

/**
 * add - Adds the top two elements of the stack
 * @stack: Stack
 * @line_num: Line number
 */
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

/**
 * sub - Subtracts the top element of the stack
 * from the second top element of the stack
 * @stack: Stack
 * @line_num: Line number
 */
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

/**
 * div_stack - Divides the second top element of the stack
 * by the top element of the stack
 * @stack: Stack
 * @line_num: Line number
 */
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

/**
 * mul - Multiplies the second top element of the stack
 * with the top element of the stack
 * @stack: Stack
 * @line_num: Line number
 */
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

/**
 * mod - Computes the remainder of the division of the second
 * top element of the stack by the top element of the stack
 * @stack: Stack
 * @line_num: Line number
 */
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
