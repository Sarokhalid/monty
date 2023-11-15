#include "monty.h"

/**
 * pstr - Prints the string starting at the top of the stack
 * @stack: Double pointer to the top of the stack
 * @line_num: The line number
 * If the stack is empty, it prints only a new line.
 */
void pstr(stack_t **stack, unsigned int line_num)
{
	stack_t *current_node = *stack;

	(void)line_num;

	while (current_node != NULL && current_node->n > 0 && current_node->n <= 127)
	{
		printf("%c", current_node->n);
		current_node = current_node->next;
	}
	printf("\n");
}

/**
 * rotl - Rotates the stack to the top
 * @stack: Double pointer to the top of the stack
 * @line_num: The line number
 */
void rotl(stack_t **stack, unsigned int line_num)
{
	stack_t *last_node;

	(void)line_num;

	if (*stack == NULL || (*stack)->next == NULL)
	{
		return;
	}

	last_node = *stack;
	while (last_node->next != NULL)
	{
		last_node = last_node->next;
	}

	last_node->next = *stack;
	(*stack)->prev = last_node;
	*stack = (*stack)->next;
	(*stack)->prev->next = NULL;
	(*stack)->prev = NULL;
}

/**
 * rotr - Rotates the stack to the bottom
 * @stack: Double pointer to the top of the stack
 * @line_num: The line number
 *
 */
void rotr(stack_t **stack, unsigned int line_num)
{
	stack_t *last_node;

	(void)line_num;
	if (*stack == NULL || (*stack)->next == NULL)
	{
		return;
	}
	last_node = *stack;
	while (last_node->next != NULL)
	{
		last_node = last_node->next;
	}
	last_node->next = *stack;
	(*stack)->prev = last_node;
	*stack = last_node;
	last_node->prev->next = NULL;
	last_node->prev = NULL;
}
