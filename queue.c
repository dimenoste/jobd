#include <stdio.h>
#include <stdlib.h>
#include <err.h>


typedef struct node
{
    int		value;
    struct node	*next;
}			node;

typedef struct queue
{
	node	*head;
	node	*tail;
}			queue;

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

void	init_queue(int first_value)
{
    queue *queue;
	node	*first_node;
	first_node = create_node(first_value);

	queue->head = first_node;
	queue->tail = first_node;
    
    queue = malloc(sizeof(queue));
	return ;
}

void enqueue(queue *queue, int new_value)
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


void dequeue(queue *queue)
{

    node *head;
    
    head = queue->head;
    if (queue->head->next != NULL)
    {
        return ;
    }
    queue->head = queue->head->next;
    free(head);
    return ;
}



void queue_free(queue *queue)
{
    node	*node;

	if (queue == NULL || queue->head == NULL)
	{
		return ;
	}
	node = queue->head;
    while(queue->head != NULL)
    {
        dequeue(queue);
    }
	return ;
}

int main(void)
{


    
    queue = init_queue(10);
    printf("queue first node value is %d\n", queue->head->value);
    printf("queue last node value is %d\n", queue->tail->value);
    return (0);
}