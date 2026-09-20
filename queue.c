#include <stdio.h>
#include <stdlib.h>

typedef struct queue
{
	node	*head;
	node	*tail;
}			queue;

typedef struct node
{
	int		value;
	node	*next;
}			node;

node	*create_node(int value)
{
	node	*first;

	first = malloc(sizeof(node));
	if (first == NULL)
	{
		err(EXIT_FAILURE, "malloc");
	}
	first->value = value;
	first->next = NULL;
	return (first);
}

queue	*init_queue(queue *queue, int first_value)
{
	node	*first_node;

	queue->head = NULL;
	queue->tail = NULL;
	first_node = create_node(first_value);
	queue->head = first_node;
	queue->tail = first_node;
	return (queue);
}

void	*enqueue(queue *queue, int new_value)
{
	node	*node;

	if (queue == NULL || queue->head == NULL)
	{
		return ;
	}
	node = queue->head;
	while (node->next != NULL)
	{
		node = node->next;
	}
	node->next = create_node(new_value);
	queue->tail = node->next;
	return ;
}

void	*queue_free(node *queue_head)
{
}