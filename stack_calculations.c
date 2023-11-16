#include "monty.h"

/**
 * add - Adds The top two elements of the stack
 * @monty: Pointer to the current state of the stack.
 * @line_num: Line number
 * Return: 0 in Success, -1 in Error
 */
int add(monty_t *monty, unsigned int line_num)
{
	int sum = 0;
	stack_t *first, *second;

	if (monty->stack == NULL || (monty->stack)->next == NULL)
	{
		fprintf(stderr, "L%d: can't add, stack too short\n", line_num);
		return (-1);
	}

	if (monty->mode == 0)  /* Stack mode */
	{
		first = monty->stack;
		second = (monty->stack)->next;
	}
	else  /* Queue mode */
	{
		first = monty->stack;
		while (first->next != NULL)
			first = first->next;

		second = first->prev;
	}
	sum = first->n + second->n;
	if (monty->mode == 0)
	{ /* Stack mode */
		pop(monty, line_num);
		(monty->stack)->n = sum;
	}
	else
	{ /* Queue mode */
		second->n = sum;
		pop(monty, line_num);
	}
	return (0);
}

/**
 * sub - Subtracts the top element of the stack
 * from the second top element of the stack
 * @monty: Pointer to the current state of the stack.
 * @line_num: Line number
 * Return: 0 in Success, -1 in Error
 */
int sub(monty_t *monty, unsigned int line_num)
{
	int diff;
	stack_t *first, *second;

	if (monty->stack == NULL || (monty->stack)->next == NULL)
	{
		fprintf(stderr, "L%d: can't sub, stack too short\n", line_num);
		return (-1);
	}

	if (monty->mode == 0)  /* Stack mode */
	{
		first = monty->stack;
		second = (monty->stack)->next;
	}
	else  /* Queue mode */
	{
		first = monty->stack;
		while (first->next != NULL)
			first = first->next;
		second = first->prev;
	}

	diff = second->n - first->n;
	pop(monty, line_num);
	(monty->stack)->n = diff;
	return (0);
}
/**
 * div_stack - Divides the second top element of the stack
 * by the top element of the stack
 * @monty: Pointer to the current state of the stack.
 * @line_num: Line number
 * Return: 0 in Success, -1 in Error
 */
int div_stack(monty_t *monty, unsigned int line_num)
{
	int quotient;
	stack_t *first, *second;

	if (monty->stack == NULL || (monty->stack)->next == NULL)
	{
		fprintf(stderr, "L%d: can't div, stack too short\n", line_num);
		return (-1);
	}

	if (monty->mode == 0)  /* Stack mode */
	{
		first = monty->stack;
		second = (monty->stack)->next;
	}
	else  /* Queue mode */
	{
		first = monty->stack;
		while (first->next != NULL)
			first = first->next;
		second = first->prev;
	}

	if (first->n == 0)
	{
		fprintf(stderr, "L%d: division by zero\n", line_num);
		return (-1);
	}

	quotient = second->n / first->n;
	pop(monty, line_num);
	(monty->stack)->n = quotient;
	return (0);
}

/**
 * mul - Multiplies the second top element of the stack
 * with the top element of the stack
 * @monty: Pointer to the current state of the stack.
 * @line_num: Line number
 * Return: 0 in Success, -1 in Error
 */
int mul(monty_t *monty, unsigned int line_num)
{
	int product;
	stack_t *first, *second;

	if (monty->stack == NULL || (monty->stack)->next == NULL)
	{
		fprintf(stderr, "L%d: can't mul, stack too short\n", line_num);
		return (-1);
	}

	if (monty->mode == 0)  /* Stack mode */
	{
		first = monty->stack;
		second = (monty->stack)->next;
	}
	else  /* Queue mode */
	{
		first = monty->stack;
		while (first->next != NULL)
			first = first->next;
		second = first->prev;
	}

	product = first->n * second->n;
	pop(monty, line_num);
	(monty->stack)->n = product;
	return (0);
}

/**
 * mod - Computes the remainder of the division of the second
 * top element of the stack by the top element of the stack
 * @monty: Pointer to the current state of the stack.
 * @line_num: Line number
 * Return: 0 in Success, -1 in Error
 */
int mod(monty_t *monty, unsigned int line_num)
{
	int remainder;
	stack_t *first, *second;

	if (monty->stack == NULL || (monty->stack)->next == NULL)
	{
		fprintf(stderr, "L%d: can't mod, stack too short\n", line_num);
		return (-1);
	}

	if (monty->mode == 0)  /* Stack mode */
	{
		first = monty->stack;
		second = (monty->stack)->next;
	}
	else  /* Queue mode */
	{
		first = monty->stack;
		while (first->next != NULL)
			first = first->next;
		second = first->prev;
	}

	if (first->n == 0)
	{
		fprintf(stderr, "L%d: division by zero\n", line_num);
		return (-1);
	}

	remainder = second->n % first->n;
	pop(monty, line_num);
	(monty->stack)->n = remainder;
	return (0);
}
