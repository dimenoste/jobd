#include "jobd.h"

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

