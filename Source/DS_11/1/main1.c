#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

enum {
	FILE_OPEN_ERROR, MEMORY_ALLOCATION_ERROR
};

#define NAME(a) #a
#define CATCH(ERROR) do{printf(NAME(ERROR));exit(0);}while(false)
#define CALLOC(type,data_num,ptr) do{if(!(ptr=(type*)calloc(data_num,sizeof(type)))){CATCH(MEMORY_ALLOCATION_ERROR);}}while(false)

typedef struct node* link;
typedef struct node{
	int data;
	link next;
} node;
link* set;
bool* is_printed;

int* stack;
int top = -1;
void push(int data);
int pop(void);
bool stack_empty(void);

void list_in(int x, int y);

void print_set(int set_size);

void find_equivalence_class(int set_size);

#define FILE_NAME "input.txt"
int main(void)
{
	FILE* fp;fopen_s(&fp, FILE_NAME, "r");
	int set_size;
	int x, y;
	if (fp)
	{
		fscanf_s(fp, "%d", &set_size);
		CALLOC(link, set_size, set);
		CALLOC(bool, set_size, is_printed);
		CALLOC(int, set_size, stack);

		while (fscanf_s(fp, "%d %d", &x, &y) != EOF)
			list_in(x, y);

		fclose(fp);
	}
	else CATCH(FILE_OPEN_ERROR);

	printf("current size of S : %d\n", set_size);
	printf("S = { 0 ");
	int i;
	for (i = 1;i < set_size;i++)
		printf(", %d ", i);
	printf("}\n\n");

	print_set(set_size);

	find_equivalence_class(set_size);

	return 0;
}

void push(int data)
{
	stack[++top] = data;
}

int pop(void)
{
	return stack[top--];
}

bool stack_empty(void)
{
	return top <= -1;
}

void list_in(int x, int y)
{
	link tmp1; CALLOC(node, 1, tmp1);
	tmp1->data = y;
	tmp1->next = set[x];
	set[x] = tmp1;

	link tmp2; CALLOC(node, 1, tmp2);
	tmp2->data = x;
	tmp2->next = set[y];
	set[y] = tmp2;
}

void print_set(int set_size)
{
	printf("< Symmetric 관계 Linked List >\n");
	int i; link tmp;
	for (i = 0;i < set_size;i++)
	{
		printf("%2d symmetric 관계\n", i);
		for (tmp = set[i];tmp;tmp = tmp->next)
			printf("(%p %2d %p)\n", tmp, tmp->data, tmp->next);	}
	printf("\n");
}

void find_equivalence_class(int set_size)
{
	printf("< Equivalence Class >\n");
	int count = 0;
	int i; int tmp; link scaf;
	for (i = 0;i < set_size;i++)
	{
		if (!is_printed[i])
		{
			printf("\nequivalence class[%d] : ", ++count);
			printf("%3d", i);is_printed[i] = true;
			push(i);
			while (!stack_empty())
			{
				tmp = pop();
				for (scaf = set[tmp];scaf;scaf = scaf->next)
				{
					if (!is_printed[scaf->data])
					{
						printf("%3d", scaf->data);is_printed[scaf->data] = true;
						push(scaf->data);
					}
				}
			}
		}
	}
	printf("\n");
}