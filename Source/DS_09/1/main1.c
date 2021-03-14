#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum {
	FILE_OPEN_ERROR, MEMORY_ALLOCATION_ERROR
};

#define NAME(a) #a
#define CATCH(ERROR) do{printf(NAME(ERROR));exit(0);}while(false)
#define CALLOC(type,data_num, ptr) do{if(!(ptr=(type*)calloc(data_num,sizeof(type)))){CATCH(MEMORY_ALLOCATION_ERROR);}}while(false)

typedef struct {
	int id;
	int grade; 
} element;

typedef struct stack* stackPointer;
typedef struct stack {
	element data;
	stackPointer link;
}Node;

#define MAX_STACKS 3
stackPointer top[MAX_STACKS];

void stack_push(int sub, int id, int grade);
element stack_pop(int sub);
bool stack_empty(int sub);
void print_stack(void);

#define FILE_NAME "input.txt"
int main(void)
{
	FILE* fp; fopen_s(&fp, FILE_NAME, "r");
	int sub, id, grade;
	if (fp)
	{
		while (fscanf_s(fp, "%d %d %d", &sub, &id, &grade) != EOF)
			stack_push(sub, id, grade);
		fclose(fp);
	}
	else CATCH(FILE_OPEN_ERROR);

	print_stack();

	return 0;
}

void stack_push(int sub, int id, int grade)
{
	stackPointer tmp; CALLOC(Node, 1, tmp);
	tmp->data.id = id; tmp->data.grade = grade;

	tmp->link = top[sub];
	top[sub] = tmp;
}

element stack_pop(int sub)
{
	element tmp;
	tmp.id = top[sub]->data.id; tmp.grade = top[sub]->data.grade;
	stackPointer scaf = top[sub];
	top[sub] = top[sub]->link;
	free(scaf);
	return tmp;
}

bool stack_empty(int sub)
{
	return (!top[sub]) ? true : false;
}

void print_stack(void)
{
	int i;
	element tmp;
	printf("sub id grade\n");
	for (i = 0;i < MAX_STACKS;i++)
	{
		printf("************\n");
		for (tmp = stack_pop(i);!stack_empty(i);tmp = stack_pop(i))
			printf("%3d %3d %3d\n", i, tmp.id, tmp.grade);
		printf("%3d %3d %3d\n", i, tmp.id, tmp.grade);
		printf("************\n");
	}
}