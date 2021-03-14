#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

enum {
	FILE_OPEN_ERROR, MEMORY_ALLOCATION_ERROR
};

#define NAME(a) #a
#define CATCH(ERROR) do{printf(NAME(ERROR));exit(0);}while(false)
#define CALLOC(type,data_num,ptr) do{if(!(ptr=(type*)calloc(data_num,sizeof(type)))){CATCH(MEMORY_ALLOCATION_ERROR);}}while(false)

typedef struct listNode* listPointer;
typedef struct listNode {
	int data;
	listPointer link;
} listNode;

listPointer head = NULL;

void list_in(int data);
void print_list(void);
void delete_odd_data(void);

#define FILE_NAME "input.txt"
int main(void)
{
	FILE* fp; fopen_s(&fp, FILE_NAME, "r");
	int input_int;
	if (fp)
	{
		while (fscanf_s(fp, "%d", &input_int) != EOF)
			list_in(input_int);
		fclose(fp);
	}
	else CATCH(FILE_OPEN_ERROR);

	print_list();

	delete_odd_data();
	printf("\nAfter deleting nodes with odd data\n\n");

	print_list();

	return 0;
}

void list_in(int data)
{
	listPointer tmp; CALLOC(listNode, 1, tmp);
	tmp->data = data;

	if (!head)
		tmp->link = tmp;
	else
	{
		tmp->link = head->link;
		head->link = tmp;
	}

	head = tmp;
}

void print_list(void)
{
	printf("The Circularly Linked List contains\n");
	listPointer tmp;
	for (tmp = head->link; tmp != head; tmp = tmp->link)
		printf("(%p %2d %p)\n", tmp, tmp->data, tmp->link);
	printf("(%p %2d %p)\n", tmp, tmp->data, tmp->link);
}

void delete_odd_data(void)
{
	listPointer front = head->link, trail = head;
	while (front != head)
	{
		if ((front->data) % 2 == 1)
		{
			trail->link = front->link;
			free(front);
			front = trail->link;
		}
		trail = front;
		front = front->link;
	}

	if ((front->data) % 2 == 1)
	{
		head = trail;
		trail->link = front->link;
		free(front);
	}
}