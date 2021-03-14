#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_SIZE 20
#define MAX_STACK_SIZE 5

typedef struct {
	int id;
	char name[MAX_NAME_SIZE];
} element;

element stack[MAX_STACK_SIZE];
int top = -1;

bool stack_full(void)
{
	return top == MAX_STACK_SIZE - 1;
}

void sprint(void)
{
	printf("current stack elements : \n");
	int i;
	for (i = 0;i <= top;i++)
		printf("%d %s\n", stack[i].id, stack[i].name);
	printf("\n");
}

void push(element data)
{
	if (stack_full())
	{
		printf("stack is full cannot add element\n");
		sprint();
		exit(0);
	}
	top++;
	stack[top].id = data.id;
	strcpy_s(stack[top].name, sizeof(stack[top].name), data.name);
}

bool stack_empty(void)
{
	return top == -1;
}

element pop(void)
{
	if (stack_empty())
	{
		printf("stack is empty cannot pop element\n");
		exit(0);
	}
	return stack[top--];
}

int main(void)
{
	printf("<< stack operations where MAX_STACK_SIZE 5 >>\n");
	printf("push 1 Jung\n");
	printf("pop\n");
	printf("*********************************************\n");

	element tmp;
	char menu[MAX_NAME_SIZE];

	while (true)
	{
		scanf_s("%s", menu, sizeof(menu));
		if (strcmp(menu, "push") == 0)
		{
			scanf_s("%d %s", &tmp.id, &tmp.name, sizeof(tmp.name));
			push(tmp);
		}
		else if (strcmp(menu, "pop") == 0)
		{
			tmp = pop();
			printf("%d %s\n", tmp.id, tmp.name);
		}
		else if (strcmp(menu, "sprint") == 0)
			sprint();
		else
			printf("wrong command! try again!\n");
	}

	return 0;
}