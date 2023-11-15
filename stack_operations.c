#include "monty.h"

/**
 * push - Adds a new node to the stack or queue.
 * @stack: Double pointer to the top of the stack.
 * @line_num: The line number where the instruction appears.
 *
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

	if (mode == 0)  /* Stack mode */
		push_to_stack(stack, new_node);
	else  /* Queue mode */
		push_to_queue(stack, new_node);
}

/**
 * push_to_stack - Adds a new node to the top of the stack.
 * @stack: Double pointer to the top of the stack.
 * @new_node: Pointer to the new node.
 *
 */
void push_to_stack(stack_t **stack, stack_t *new_node)
{
	new_node->next = *stack;
	if (*stack != NULL)
		(*stack)->prev = new_node;
	*stack = new_node;
}

/**
 * push_to_queue - Adds a new node to the end of the queue.
 * @stack: Double pointer to the top of the stack.
 * @new_node: Pointer to the new node.
 *
 */
void push_to_queue(stack_t **stack, stack_t *new_node)
{
	if (*stack != NULL)
	{
		stack_t *last = *stack;

		while (last->next != NULL)
			last = last->next;
		last->next = new_node;
		new_node->prev = last;
	}
	else
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

	if (mode == 0)  /* Stack mode*/
	{
		r = *stack;
		*stack = (*stack)->next;
		if (*stack != NULL)
			(*stack)->prev = NULL;
	}
	else  /* Queue mode */
	{
		r = *stack;
		while (r->next != NULL)
			r = r->next;
		if (r->prev != NULL)
			r->prev->next = NULL;
	}

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
	stack_t *first, *second;

	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%d: can't swap, stack too short\n", line_num);
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

	temp = first->n;
	first->n = second->n;
	second->n = temp;
}
