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
	int to;
	link next;
}node;
typedef struct {
	int precedence_num;
	bool is_printed;
	link next;
} header;
header* graph;

int vertex_num;

void graph_in(int from, int to);

void sort(void);

#define FILE_NAME "input.txt"
int main(void)
{
	FILE* fp;fopen_s(&fp, FILE_NAME, "r");
	int tmp_from, tmp_to;
	if (fp)
	{
		fscanf_s(fp, "%d", &vertex_num);
		CALLOC(header, vertex_num, graph);

		while (fscanf_s(fp, "%d %d", &tmp_from, &tmp_to) != EOF)
			graph_in(tmp_from, tmp_to);

		fclose(fp);
	}
	else CATCH(FILE_OPEN_ERROR);

	sort();

	return 0;
}

void graph_in(int from, int to)
{
	link tmp; CALLOC(node, 1, tmp);
	tmp->to = to;
	tmp->next = graph[from].next;
	graph[from].next = tmp;
	graph[to].precedence_num++;
}

void sort(void)
{
	int i, j;
	link tmp;
	for (i = 0;i < vertex_num;i++)
	{
		for(j=vertex_num-1;j>=0;j--)
			if (!graph[j].is_printed && !graph[j].precedence_num)
			{
				printf("%3d", j); graph[j].is_printed = true;
				for (tmp = graph[j].next;tmp;tmp = tmp->next)
					graph[tmp->to].precedence_num--;
				break;
			}
	}
	printf("\n");
}