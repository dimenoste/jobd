

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