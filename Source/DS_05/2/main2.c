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
	printf("<< Linear queue operation where MAX_QUEUE_SIZE is 3 >>\n");
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
		else printf("Wrong command! try again!\n");
	}
	return 0;
}

bool queue_full(void)
{
	return rear == MAX_QUEUE_SIZE;
}

void add_q(element data)
{
	if (queue_full())
	{
		if (front == 0)
		{
			printf("queue is full, not added\n");
			return;
		}
		printf("data shift\n");
		int data_num = rear - front;
		int i, j;
		for (i = 0; i < MAX_QUEUE_SIZE - data_num; i++)
			for (j = 0; j < MAX_QUEUE_SIZE - 1; j++)
				queue[j] = queue[j + 1];
		front = 0; rear = data_num;
	}
	queue[rear].key = data.key;
	strcpy_s(queue[rear].name, sizeof(queue[rear].name), data.name);
	rear++;
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
	return queue[front++];
}

void qprint(void)
{
	int i;
	for (i = front; i < rear; i++)
		printf("%d %s\n", queue[i].key, queue[i].name);
	printf("\n");
}