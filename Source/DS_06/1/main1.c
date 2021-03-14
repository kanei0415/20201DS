#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef enum {
	MEMORY_ALLOCATION_ERROR
};

#define NAME(a) #a
#define CATCH(error) do{printf(NAME(error));exit(0);}while(false)
#define CALLOC(type, data_num, ptr) do{if(!(ptr=(type*)calloc(data_num,sizeof(type)))){CATCH(MEMORY_ALLOCATION_ERROR);}}while(false)

#define INIT_QUEUE_SIZE 2
#define NAME_SIZE 20

typedef struct {
	int id;
	char name[NAME_SIZE];
} element;

element* queue;
int capacity = INIT_QUEUE_SIZE;
int front = 0, rear = 0;

bool queue_full(void);
void copy(element* adr_start_c, element* adr_end_o, element* destination);
void add_q(element data);
element delete_q(void);
qprint(void);

int main(void)
{
	printf("<< Circular Queue operantions using dynamic allocated array, where the inital capacity is 2 >>\n");
	printf("add 1 Jung\n");
	printf("delete\n");
	printf("***********************************************************************************************\n");
	char menu[NAME_SIZE];
	element tmp; CALLOC(element, capacity, queue);
	while (true)
	{
		scanf_s("%s", menu, sizeof(menu));
		if (strcmp(menu, "add") == 0)
		{
			scanf_s("%d %s", &tmp.id, &tmp.name, sizeof(tmp.name));
			add_q(tmp);
		}
		else if (strcmp(menu, "delete") == 0)
		{
			tmp = delete_q();
			printf("%d %s\n", tmp.id, tmp.name);
		}
		else if (strcmp(menu, "qprint") == 0) qprint();
		else printf("wrong command! try again!\n");
	}
	return 0;
}

bool queue_full(void)
{
	return (rear + 1) % capacity == front;
}

void copy(element* adr_start_c, element* adr_end_o, element* destination)
{
	while (adr_start_c != adr_end_o)
		*destination++ = *adr_start_c++;
}

void add_q(element data)
{
	if (queue_full()) // Reallocation (Size = 2 * capacity)
	{
		element* buff; CALLOC(element, capacity * 2, buff);
		int start = (front + 1) % capacity;

		if (start < 2) // there is no interval in data seqence
			copy(queue + start, queue + start + capacity - 1, buff);
		else // there is interval in data seqence
		{
			copy(queue + start, queue + capacity, buff);
			copy(queue, queue + rear + 1, buff + capacity - start);
		}

		front = 2 * capacity - 1;
		rear = capacity - 2;
		capacity *= 2;

		free(queue); queue = buff;

		printf("queue capacity is doubled\n");
		printf("current queue capacity is %d\n", capacity);
	}

	rear = (rear + 1) % capacity;

	queue[rear].id = data.id;
	strcpy_s(queue[rear].name, sizeof(queue[rear].name), data.name);
}

element delete_q(void)
{
	front = (front + 1) % capacity;
	return queue[front];
}

qprint(void)
{
	int i;
	for (i = (front + 1) % capacity; i != rear;i = (i + 1) % capacity)
		printf("%d %s\n", queue[i].id, queue[i].name);
	printf("%d %s\n", queue[i].id, queue[i].name);
	printf("\n");
}