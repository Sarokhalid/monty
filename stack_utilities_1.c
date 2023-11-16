#include "monty.h"

/**
 * pstr - Prints The string starting at the top of the stack
 * @monty: Pointer to the current state of the stack.
 * @line_num: The line number
 * If the stack is empty, it prints only a new line.
 * Return: 0 in Success, -1 in Error
 */
int pstr(monty_t *monty, unsigned int line_num)
{
	stack_t *current_node = monty->stack;

	(void)line_num;

	while (current_node != NULL && current_node->n > 0 && current_node->n <= 127)
	{
		printf("%c", current_node->n);
		current_node = current_node->next;
	}
	printf("\n");
	return (0);
}

/**
 * rotl - Rotates the stack to the top
 * @monty: Pointer to the current state of the stack.
 * @line_num: The line number
 * Return: 0 in Success, -1 in Error
 */
int rotl(monty_t *monty, unsigned int line_num)
{
	stack_t *last_node;

	(void)line_num;

	if (monty->stack == NULL || (monty->stack)->next == NULL)
	{
		return (0);
	}

	last_node = monty->stack;
	while (last_node->next != NULL)
	{
		last_node = last_node->next;
	}

	last_node->next = monty->stack;
	(monty->stack)->prev = last_node;
	monty->stack = (monty->stack)->next;
	(monty->stack)->prev->next = NULL;
	(monty->stack)->prev = NULL;
	return (0);
}

/**
 * rotr - Rotates the stack to the bottom
 * @monty: Pointer to the current state of the stack.
 * @line_num: The line number
 * Return: 0 in Success, -1 in Error
 */
int rotr(monty_t *monty, unsigned int line_num)
{
	stack_t *last_node;

	(void)line_num;
	if (monty->stack == NULL || (monty->stack)->next == NULL)
	{
		return (0);
	}
	last_node = monty->stack;
	while (last_node->next != NULL)
	{
		last_node = last_node->next;
	}
	last_node->next = monty->stack;
	(monty->stack)->prev = last_node;
	monty->stack = last_node;
	last_node->prev->next = NULL;
	last_node->prev = NULL;
	return (0);
}
