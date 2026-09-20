#include <err.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int			value;
	struct node	*next;
}				node;

typedef struct queue
{
	node		*head;
	node		*tail;
}				queue;

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

queue	*init_queue(int first_value)
{
	queue	*queue;
	node	*first_node;

	queue = malloc(sizeof(queue));
	if (queue == NULL)
	{
		return (NULL);
	}
	first_node = create_node(first_value);
	queue->head = first_node;
	queue->tail = first_node;
	return (queue);
}

void	enqueue(queue *queue, int new_value)
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

void	dequeue(queue *queue)
{
	node	*head;

	if (queue->head == NULL)
	{
		return ;
	}
	head = queue->head;
	queue->head = queue->head->next;
	free(head);
	return ;
}

void	display_queue(queue *queue)
{
	node	*node;

	if (queue == NULL || queue->head == NULL)
	{
		return ;
	}
	node = queue->head;
	while (node != NULL)
	{
		printf("value of node %d\n", node->value);
		node = node->next;
	}
	return ;
}

void	queue_free(queue *queue)
{
	node	*node;

	if (queue == NULL || queue->head == NULL)
	{
		return ;
	}
	node = queue->head;
	while (queue->head != NULL)
	{
		dequeue(queue);
	}
	return ;
}

int	size_queue(queue *queue)
{
	int		i;
	node	*node;

	i = 0;
	if (queue == NULL || queue->head == NULL)
	{
		return (i);
	}
	node = queue->head;
	while (node != NULL)
	{
		i++;
		node = node->next;
	}
	return (i);
}

int	main(void)
{
	queue *queue;

	printf("len of queue is %d\n", size_queue(queue));
	queue = init_queue(10);
	printf("queue first node value is %d\n", queue->head->value);
	printf("queue last node value is %d\n", queue->tail->value);

	enqueue(queue, 15);
	display_queue(queue);
	printf("len of queue is %d\n", size_queue(queue));

	queue_free(queue);
	display_queue(queue);
	printf("len of queue is %d\n", size_queue(queue));

	return (0);
}