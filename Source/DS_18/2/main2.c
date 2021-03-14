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
typedef struct node {
	int to;
	link next;
} node;

link* graph;

void undirected_graph_in(int from, int to);

void print_graph(void);

bool* is_print;
void bfs(int vertex);
void bfs_all(void);

int* stack;
int top = -1;
void push(int data)
{
	stack[++top] = data;
}
int pop()
{
	return stack[top--];
}
bool stack_empty()
{
	return top == -1;
}

#define FILE_NAME "input.txt"
int vertex_num, edge_num;
int tmp_from, tmp_to;
int main(void)
{
	FILE* fp; fopen_s(&fp, FILE_NAME, "r");
	if (fp)
	{
		fscanf_s(fp, "%d %d", &vertex_num, &edge_num);
		CALLOC(link, vertex_num, graph);
		int i;
		for (i = 0;i < edge_num;i++)
		{
			fscanf_s(fp, "%d %d", &tmp_from, &tmp_to);
			undirected_graph_in(tmp_from, tmp_to);
		}

		fclose(fp);
	}
	else CATCH(FILE_OPEN_ERROR);

	print_graph();
	CALLOC(bool, vertex_num, is_print);
	CALLOC(int, vertex_num, stack);

	bfs_all();
	return 0;
}

void undirected_graph_in(int from, int to)
{
	link tmp1; CALLOC(node, 1, tmp1);
	tmp1->to = to;
	tmp1->next = graph[from];
	graph[from] = tmp1;

	link tmp2;CALLOC(node, 1, tmp2);
	tmp2->to = from;
	tmp2->next = graph[to];
	graph[to] = tmp2;
}

void print_graph(void)
{
	printf("< Adjacency List >\n");
	int i; link tmp;
	for (i = 0;i < vertex_num;i++)
	{
		printf("graph[%d] : ", i);
		for (tmp = graph[i];tmp;tmp = tmp->next)
			printf("%3d", tmp->to);
		printf("\n");
	}
	printf("\n");
}

void bfs(int vertex)
{
	printf("%3d", vertex); is_print[vertex] = true; push(vertex);
	link tmp; int scaf;
	while (!stack_empty())
	{
		scaf = pop();
		for (tmp = graph[scaf];tmp;tmp = tmp->next)
			if (!is_print[tmp->to])
			{
				printf("%3d", tmp->to); is_print[tmp->to] = true; push(tmp->to);
			}
	}
}

void bfs_all(void)
{
	printf("< BFS >\n");
	int i, j;
	for (i = 0;i < vertex_num;i++)
	{
		for (j = 0;j < vertex_num;j++) is_print[j] = false;
		printf("BFS<%d> : ", i); bfs(i);
		printf("\n");
	}
}