#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum {
	FILE_OPEN_ERROR, MEMORY_ALLOCATION_ERROR
};

#define NAME(a) #a
#define CATCH(error) do{printf(NAME(error));exit(0);}while(false)
#define CALLOC(type,data_num,ptr) do{if(!(ptr=(type*)calloc(data_num,sizeof(type)))){CATCH(MEMORY_ALLOCAION_ERROR);}}while(false)

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
	FILE* fp;fopen_s(&fp, FILE_NAME, "r");
	int int_input; 
	if (fp)
	{
		while (fscanf_s(fp, "%d", &int_input) != EOF) list_in(int_input);
		
		fclose(fp);
	}
	else CATCH(FILE_OPEN_ERROR);

	printf("The ordered list contains : \n");
	print_list();

	delete_odd_data();
	printf("After deleting node with odd data\n");

	printf("\nThe ordered list contains : \n");
	print_list();

	return 0;
}

void list_in(int data)
{
	listPointer tmp; CALLOC(listNode, 1, tmp);
	tmp->data = data; tmp->link = NULL;

	if (!head)
		head = tmp;
	else
	{
		listPointer scaf;
		for (scaf = head; scaf->link && scaf->link->data < tmp->data; scaf = scaf->link);

		if (scaf == head && scaf->data > tmp->data)
		{
			tmp->link = scaf;
			head = tmp;
		}
		else
		{
			tmp->link = scaf->link;
			scaf->link = tmp;
		}
	}
}

void print_list(void)
{
	listPointer tmp;
	for (tmp = head;tmp;tmp = tmp->link)
		printf("(%p,%3d,%p)\n", tmp, tmp->data, tmp->link);
	printf("\n");
}

void delete_odd_data(void)
{
	listPointer front = head, trail = NULL;
	
	while (front)
	{
		if ((front->data) % 2 == 1)
		{
			if (front == head)
			{
				head = front->link;
				free(front);
				front = head;
			}
			else
			{
				trail->link = front->link;
				free(front);
				front = trail->link;
			}
		}
		else
		{
			trail = front;
			front = front->link;
		}
	}
}