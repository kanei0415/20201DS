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
void dfs(int vertex);
void conntected_component(void);

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

	conntected_component();
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

void dfs(int vertex)
{
	link tmp;
	printf("%3d", vertex); is_print[vertex] = true;
	for (tmp = graph[vertex]; tmp;tmp = tmp->next)
		if (!is_print[tmp->to])
			dfs(tmp->to);
}

void conntected_component(void)
{
	printf("< Conntected Component >\n");
	int i, count = 0;
	for (i = 0;i < vertex_num;i++)
	{
		if (!is_print[i])
		{
			printf("component %d : ", ++count); dfs(i);
			printf("\n");
		}
	}
}