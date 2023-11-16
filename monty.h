#ifndef MONTY_H
#define MONTY_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

/**
 * struct stack_s - doubly linked list representation of a stack (or queue)
 * @n: integer
 * @prev: points to the previous element of the stack (or queue)
 * @next: points to the next element of the stack (or queue)
 * Description: doubly linked list node structure
 * for stack, queues, LIFO, FIFO
 */
typedef struct stack_s
{
	int n;
	struct stack_s *prev;
	struct stack_s *next;
} stack_t;

/**
 * struct monty_s - Structure to hold the state of the stack or queue
 * @mode: Mode of operation, 0 for stack (LIFO) and 1 for queue (FIFO)
 * @stack: Pointer to the top (or bottom, depending on mode)
 * of the stack or queue
 *
 */
typedef struct monty_s
{
	int mode;
	stack_t *stack;
} monty_t;

/**
 * struct instruction_s - Opcode and its function
 * @opcode: the opcode
 * @f: function to handle the opcode
 * Description: opcode and its function
 * for stack, queues, LIFO, FIFO
 */
typedef struct instruction_s
{
	char *opcode;
	int (*f)(monty_t *monty, unsigned int line_number);
} instruction_t;



int push(monty_t *monty, unsigned int line_num);
void push_to_stack(monty_t *monty, stack_t *new_node);
void push_to_queue(monty_t *monty, stack_t *new_node);
int pall(monty_t *monty, unsigned int line_num);
int pint(monty_t *monty, unsigned int line_num);
int pop(monty_t *monty, unsigned int line_num);
int swap(monty_t *monty, unsigned int line_num);
int add(monty_t *monty, unsigned int line_num);
int nop(monty_t *monty, unsigned int line_num);
int sub(monty_t *monty, unsigned int line_num);
int div_stack(monty_t *monty, unsigned int line_num);
int mul(monty_t *monty, unsigned int line_num);
int mod(monty_t *monty, unsigned int line_num);
int pchar(monty_t *monty, unsigned int line_num);
int pstr(monty_t *monty, unsigned int line_num);
int rotl(monty_t *monty, unsigned int line_num);
int rotr(monty_t *monty, unsigned int line_num);
int files(const char *fn, monty_t *monty);
void free_stack(monty_t *monty);
int is_integer(const char *str);
int process_opcode(char *op, monty_t *monty,
		unsigned int line_num);


#endif /* MONTY_H */
