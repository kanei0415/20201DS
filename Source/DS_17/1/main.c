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

void directed_graph_in(int from, int to);
void undirected_graph_in(int from, int to);

enum {
	UNDIRECTED_GRAPH = 'u',
	DIRECTED_GRAPH = 'd'
};

void print_graph(void);

#define FILE_NAME "input.txt"
char type_of_graph;
int vertex_num, edge_num;
int tmp_from, tmp_to;
void (*graph_in)(int, int);
int main(void)
{
	FILE* fp; fopen_s(&fp, FILE_NAME, "r");
	if (fp)
	{
		fscanf_s(fp, "%c %d %d", &type_of_graph, sizeof(type_of_graph), &vertex_num, &edge_num);
		CALLOC(link, vertex_num, graph);
		graph_in = (type_of_graph == UNDIRECTED_GRAPH) ? &undirected_graph_in : &directed_graph_in;
		
		int i;
		for (i = 0;i < edge_num;i++)
		{
			fscanf_s(fp, "%d %d", &tmp_from, &tmp_to);
			graph_in(tmp_from, tmp_to);
		}

		fclose(fp);
	}
	else CATCH(FILE_OPEN_ERROR);

	print_graph();

	return 0;
}

void directed_graph_in(int from, int to)
{
	link tmp;CALLOC(node, 1, tmp);
	tmp->to = to;
	tmp->next = graph[from];
	graph[from] = tmp;
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