#ifndef JOBD_H_ 
#define JOBD_H_

#include <err.h>
#include <stdio.h>
#include <stdlib.h>


///////////////////////// queue interface ///////////////////
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

node	*create_node(int value);
queue	*init_queue(int first_value);
void	enqueue(queue *queue, int new_value);
void	dequeue(queue *queue);
void	display_queue(queue *queue);
void	queue_free(queue *queue);
int	size_queue(queue *queue);
////////////////////////////////////////////////////////////


///////////////////////// queue interface ///////////////////

////////////////////////////////////////////////////////////

#endif // FOO_H_