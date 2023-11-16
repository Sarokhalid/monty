#include "monty.h"

/**
 * push - Adds a New node to the stack or queue.
 * @monty: Pointer to the current state of the stack.
 * @line_num: The line number where the instruction appears.
 * Return: 0 in Success, -1 in Error
 */
int push(monty_t *monty, unsigned int line_num)
{
	int val;
	char *argument;
	stack_t *new_node;

	argument = strtok(NULL, " \t\n");
	if (!argument || !is_integer(argument))
	{
		fprintf(stderr, "L%d: usage: push integer\n", line_num);
		free_stack(monty);
		return (-1);
	}

	val = atoi(argument);
	new_node = malloc(sizeof(stack_t));
	if (new_node == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		free_stack(monty);
		return (-1);
	}

	new_node->n = val;
	new_node->prev = NULL;

	if (monty->mode == 0)  /* Stack mode */
		push_to_stack(monty, new_node);
	else  /* Queue mode */
		push_to_queue(monty, new_node);
	return (0);
}

/**
 * push_to_stack - Adds a new node to the top of the stack.
 * @monty: Pointer to the current state of the stack.
 * @new_node: Pointer to the new node.
 *
 */
void push_to_stack(monty_t *monty, stack_t *new_node)
{
	new_node->next = monty->stack;
	if (monty->stack != NULL)
		(monty->stack)->prev = new_node;
	monty->stack = new_node;
}

/**
 * push_to_queue - Adds a new node to the end of the queue.
 * @monty: Pointer to the current state of the stack.
 * @new_node: Pointer to the new node.
 *
 */
void push_to_queue(monty_t *monty, stack_t *new_node)
{
	if (monty->stack != NULL)
	{
		stack_t *last = monty->stack;

		while (last->next != NULL)
		{
			last = last->next;
		}
		new_node->next = NULL;
		new_node->prev = last;
		last->next = new_node;
	}
	else
	{
		monty->stack = new_node;
	}
	new_node->next = NULL;
}

/**
 * pop - Removes the top element of the stack
 * @monty: Pointer to the current state of the stack.
 * @line_num: Line number
 * Return: 0 in Success, -1 in Error
 */
int pop(monty_t *monty, unsigned int line_num)
{
	stack_t *r;

	if (monty->stack == NULL)
	{
		fprintf(stderr, "L%d: can't pop an empty stack\n", line_num);
		return (-1);
	}

	if (monty->mode == 0)  /* Stack mode */
	{
		r = monty->stack;
		monty->stack = (monty->stack)->next;
		if (monty->stack != NULL)
			(monty->stack)->prev = NULL;
	}
	else  /* Queue mode */
	{
		r = monty->stack;
		while (r->next != NULL)
			r = r->next;

		if (r->prev != NULL)
		{
			r->prev->next = NULL;
			r->prev = NULL;
		}
		else
		{
			monty->stack = NULL;
		}
	}
	free(r);
	return (0);
}


/**
 * swap - Swaps the top two elements of the stack
 * @monty: Pointer to the current state of the stack.
 * @line_num: Line number
 * Return: 0 in Success, -1 in Error
 */
int swap(monty_t *monty, unsigned int line_num)
{
	int temp;
	stack_t *first, *second;

	if (monty->stack == NULL || (monty->stack)->next == NULL)
	{
		fprintf(stderr, "L%d: can't swap, stack too short\n", line_num);
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

	temp = first->n;
	first->n = second->n;
	second->n = temp;
	return (0);
}
