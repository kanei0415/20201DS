#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

enum {
	FILE_OPEN_ERROR, MEMORY_ALLOCATION_ERROR
};

#define NAME(a) #a
#define CATCH(ERROR) do{printf(NAME(ERROR));exit(0);}while(false)
#define CALLOC(type,data_num,ptr) do{if(!(ptr=(type*)calloc(data_num,sizeof(type)))){CATCH(MEMORY_ALLOCATION_ERROR);}}while(false)

typedef struct {
	int id;
	int grade;
} element;

typedef struct queue* queuePointer;
typedef struct queue {
	element data;
	queuePointer link;
}Node;

#define MAX_QUEUES 3
queuePointer front[MAX_QUEUES], rear[MAX_QUEUES];

void add_q(int sub, int id, int grade);
element delete_q(int sub);
bool queue_empty(int sub);
void print_queue(void);

#define FILE_NAME "input.txt"
int main(void)
{
	FILE* fp;fopen_s(&fp, FILE_NAME, "r");
	int sub, id, grade;
	if (fp)
	{
		while (fscanf_s(fp,"%d %d %d", &sub, &id, &grade)!=EOF)
			add_q(sub, id, grade);
		fclose(fp);
	}
	else CATCH(FILE_OPEN_ERROR);

	print_queue();

	return 0;
}

void add_q(int sub, int id, int grade)
{
	queuePointer tmp; CALLOC(Node, 1, tmp);
	tmp->data.id = id; tmp->data.grade = grade;

	if (!rear[sub])
		front[sub] = rear[sub] = tmp;
	else
	{
		rear[sub]->link = tmp;
		rear[sub] = tmp;
	}
}

element delete_q(int sub)
{
	element tmp;
	tmp.id = front[sub]->data.id; tmp.grade = front[sub]->data.grade;
	queuePointer scaf = front[sub];
	front[sub] = front[sub]->link;
	free(scaf);
	return tmp;
}

bool queue_empty(int sub)
{
	return (!front[sub]) ? true : false;
}

void print_queue(void)
{
	int i;
	element tmp;
	printf("sub id grade\n");
	for (i = 0;i < MAX_QUEUES;i++)
	{
		printf("************\n");
		for (tmp = delete_q(i);!queue_empty(i);tmp = delete_q(i))
			printf("%3d %3d %3d\n", i, tmp.id, tmp.grade);
		printf("%3d %3d %3d\n", i, tmp.id, tmp.grade);
		printf("************\n");
	}
}