#include "monty.h"

/**
 * push - Pushes an element to the stack
 * @stack: Stack
 * @line_num: Line number
 */
void push(stack_t **stack, unsigned int line_num)
{
	int val;
	char *argument;
	stack_t *new_node;

	argument = strtok(NULL, " \t\n");
	if (!argument || !is_integer(argument))
	{
		fprintf(stderr, "L%d: usage: push integer\n", line_num);
		free_stack(stack);
		exit(EXIT_FAILURE);
	}

	val = atoi(argument);
	new_node = malloc(sizeof(stack_t));
	if (new_node == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		free_stack(stack);
		exit(EXIT_FAILURE);
	}

	new_node->n = val;
	new_node->prev = NULL;
	new_node->next = *stack;

	if (*stack != NULL)
		(*stack)->prev = new_node;
	*stack = new_node;
}

/**
 * pop - Removes the top element of the stack
 * @stack: Stack
 * @line_num: Line number
 */
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

/**
 * swap - Swaps the top two elements of the stack
 * @stack: Stack
 * @line_num: Line number
 */
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
