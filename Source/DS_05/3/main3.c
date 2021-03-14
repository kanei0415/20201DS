#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_SIZE 20
#define MAX_QUEUE_SIZE 3

typedef struct {
	int key;
	char name[MAX_NAME_SIZE];
} element;

element queue[MAX_QUEUE_SIZE];
int front = 0, rear = 0;

bool queue_full(void);
void add_q(element data);
bool queue_empty(void);
element delete_q(void);
void qprint(void);

int main(void)
{
	printf("<< Circular queue operation where MAX_QUEUE_SIZE is 3 >>\n");
	printf("add 1 Jung\n");
	printf("delete\n");
	printf("******************************************************\n");
	char menu[MAX_NAME_SIZE];
	element tmp;
	while (true)
	{
		scanf_s("%s", menu, sizeof(menu));
		if (strcmp(menu, "add") == 0)
		{
			scanf_s("%d %s", &tmp.key, &tmp.name, sizeof(tmp.name));
			add_q(tmp);
		}
		else if (strcmp(menu, "delete") == 0)
		{
			tmp = delete_q();
			printf("%d %s\n", tmp.key, tmp.name);
		}
		else if (strcmp(menu, "qprint") == 0) qprint();
		else printf("wrong command! try again!\n");
	}
	return 0;
}

bool queue_full(void)
{
	return (rear + 1) % MAX_QUEUE_SIZE == front;
}

void add_q(element data)
{
	if (queue_full())
	{
		printf("queue is full, not added\n");
		return;
	}
	queue[rear].key = data.key;
	strcpy_s(queue[rear].name, sizeof(queue[rear].name), data.name);
	rear = (rear + 1) % MAX_QUEUE_SIZE;
}

bool queue_empty(void)
{
	return front == rear;
}

element delete_q(void)
{
	if (queue_empty())
	{
		printf("queue is empty, cannot delete element.\n");
		exit(0);
	}
	int tmp = front;
	front = (front + 1) % MAX_QUEUE_SIZE;
	return queue[tmp];
}

void qprint(void)
{
	int i;
	for (i = front; i != rear; i = (i + 1) % MAX_QUEUE_SIZE)
		printf("%d %s\n", queue[i].key, queue[i].name);
	printf("\n");
}