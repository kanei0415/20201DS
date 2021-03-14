#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

enum {
	FILE_OPEN_ERROR, MEMORY_ALLOCAION_ERROR
};

#define NAME(a) #a
#define CATCH(ERROR) do{printf(NAME(ERROR));exit(0);}while(false)
#define CALLOC(type,data_num,ptr) do{if(!(ptr=(type*)calloc(data_num,sizeof(type)))){CATCH(MEMORY_ALLOCAION_ERROR);}}while(false)
#define CALLOC_2D(type,row,col,ptr) do{CALLOC(type*,row,ptr);int i_2d;for(i_2d=0;i_2d<row;i_2d++)CALLOC(type,col,ptr[i_2d]);}while(false)

int vertex_num, edge_num;

#define INF 123456789
int** graph;
void init_graph(void);
void graph_in(int from, int to, int weight);
void print_graph(void);

int* dist;

bool* is_in_cloud;
void init_is_in_cloud(void);

#define END_OF_PATH -1
int* path;
void init_path(void);

#define PRINT_OF(num) do{if(num==INF)printf(" INF");else printf("%4d",num);}while(false)
int get_next_vertex(void);
void print_dist(void);
void find_shortest_path(int start_vertex);

typedef struct {
	int from;
	int to;
} item;
item* stack;
int top = -1;
void push(item data);
item pop(void);
bool stack_empty(void);

void print_paths(int start_vertex);

#define FILE_NAME "input.txt"
int main(void)
{
	FILE* fp;fopen_s(&fp, FILE_NAME, "r");
	int tmp_from, tmp_to, tmp_weight;
	if (fp)
	{
		fscanf_s(fp, "%d %d", &vertex_num, &edge_num);
		CALLOC_2D(int, vertex_num, vertex_num, graph);
		init_graph();

		while (fscanf_s(fp, "%d %d %d", &tmp_from, &tmp_to, &tmp_weight) != EOF)
			graph_in(tmp_from, tmp_to, tmp_weight);
		fclose(fp);
	}
	else CATCH(FILE_OPEN_ERROR);

	print_graph();

	CALLOC(int, vertex_num, dist);
	CALLOC(int, vertex_num, path);
	init_path();
	CALLOC(bool, vertex_num, is_in_cloud);
	init_is_in_cloud();
	CALLOC(item, vertex_num, stack);
	find_shortest_path(0);

	return 0;
}

void init_graph(void)
{
	int i, j;
	for (i = 0;i < vertex_num;i++)
		for (j = 0;j < vertex_num;j++)
			graph[i][j] = (i == j) ? 0 : INF;
}

void graph_in(int from, int to, int weight)
{
	graph[from][to] = weight;
	graph[to][from] = weight;
}

void print_graph(void)
{
	printf("< Graph >\n");
	int i, j;
	for (i = 0;i < vertex_num;i++)
	{
		for (j = 0;j < vertex_num;j++)
			PRINT_OF(graph[i][j]);
		printf("\n");
	}
	printf("\n");
}

void init_is_in_cloud(void)
{
	int i;
	for (i = 0;i < vertex_num;i++)
		is_in_cloud[i] = false;
}

void init_path(void)
{
	int i;
	for (i = 0;i < vertex_num;i++)
		path[i] = END_OF_PATH;
}

int get_next_vertex(void)
{
	int next_vertex = -1, min_dist = INF;
	
	int i;
	for(i=0;i<vertex_num;i++)
		if (!is_in_cloud[i] && dist[i] < min_dist)
		{
			next_vertex = i;
			min_dist = dist[i];
		}

	return next_vertex;
}

void print_dist(void)
{
	int i;
	for (i = 0;i < vertex_num;i++)
		PRINT_OF(dist[i]);
}

void find_shortest_path(int start_vertex)
{
	printf("< Find Shortest Path >\n");
	int current_vertex, next_vertex;
	int i;

	current_vertex = start_vertex;
	is_in_cloud[current_vertex] = true;
	for (i = 0;i < vertex_num;i++)
		dist[i] = graph[start_vertex][i];
	printf("%d : ", current_vertex); print_dist(); printf("\n");

	int j;

	for (i = 0;i < vertex_num - 1;i++)
	{
		next_vertex = get_next_vertex();
		is_in_cloud[next_vertex] = true;
		if (path[next_vertex] == END_OF_PATH) path[next_vertex] = current_vertex;
		current_vertex = next_vertex;

		for (j = 0;j < vertex_num;j++)
			if (!is_in_cloud[j] && dist[j] > dist[next_vertex] + graph[next_vertex][j])
			{
				dist[j] = dist[next_vertex] + graph[next_vertex][j];
				path[j] = next_vertex;
			}
		
		printf("%d : ", next_vertex); print_dist(); printf("\n");
	}

	printf("\n");

	print_paths(start_vertex);
}

void push(item data)
{
	stack[++top] = data;
}

item pop(void)
{
	return stack[top--];
}

bool stack_empty(void)
{
	return (top == -1);
}

void print_paths(int start_vertex)
{
	printf("< Path >\n");
	int i, scaf;
	item tmp;
	for (i = 0;i < vertex_num;i++)
	{
		if (i != start_vertex)
		{
			printf("dist[%d->%d] : %2d", start_vertex, i, dist[i]);

			for (scaf = i;path[scaf] != END_OF_PATH;scaf = path[scaf])
			{
				tmp.from = path[scaf];
				tmp.to = scaf;
				push(tmp);
			}

			while (!stack_empty())
			{
				tmp = pop();
				printf(" <%d->%d> ", tmp.from, tmp.to);
			}

			printf("\n");
		}
	}
}