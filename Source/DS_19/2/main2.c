#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

enum {
	FILE_OPEN_ERROR, MEMORY_ALLOCATION_ERROR
};

#define NAME(a) #a
#define CATCH(ERROR) do{printf(NAME(ERROR));exit(0);}while(false)
#define CALLOC(type,data_num,ptr) do{if(!(ptr=(type*)calloc(data_num,sizeof(type)))){CATCH(MEMORY_ALLOCATION_ERROR);}}while(false)
#define CALLOC_2D(type,row,col,ptr) do{CALLOC(type*,row,ptr);int i_2d;for(i_2d=0;i_2d<row;i_2d++)CALLOC(type,col,ptr[i_2d]);}while(false)

int vertex_size, edge_size;
int** graph;
int* weights;
bool* is_printed;
#define INF 123456789
void init_graph(void);

#define PRINT_OF(num) do{if(num==INF)printf(" INF");else printf("%4d",num);}while(false)

void graph_in(int from, int to, int weight);
void print_graph(void);

int find_next_vertex(void);
void print_weights(void);

int cost = 0;
void find_MST(int start_vertex);

#define FILE_NAME "input.txt"
int main(void)
{
	FILE* fp;fopen_s(&fp, FILE_NAME, "r");
	int tmp_from, tmp_to, tmp_weight;
	if (fp)
	{
		fscanf_s(fp, "%d %d", &vertex_size, &edge_size);

		CALLOC_2D(int, vertex_size, vertex_size, graph);
		init_graph();

		CALLOC(int, vertex_size, weights);

		int i;
		for (i = 0;i < edge_size;i++)
		{
			fscanf_s(fp, "%d %d %d", &tmp_from, &tmp_to, &tmp_weight);
			graph_in(tmp_from, tmp_to, tmp_weight);
		}

		fclose(fp);
	}
	else CATCH(FILE_OPEN_ERROR);

	print_graph();

	CALLOC(bool, vertex_size, is_printed);

	find_MST(0);

	return 0;
}

void init_graph(void)
{
	int i, j;
	for (i = 0;i < vertex_size;i++)
		for (j = 0;j < vertex_size;j++)
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
	for (i = 0;i < vertex_size;i++)
	{
		for (j = 0;j < vertex_size;j++)
			PRINT_OF(graph[i][j]);
		printf("\n");
	}
	printf("\n");
}

int find_next_vertex(void)
{
	int min_vertex = -1, min_weight = INF;

	int i;
	for (i = 0;i < vertex_size;i++)
		if (!is_printed[i])
		{
			min_vertex = i;
			min_weight = weights[i];
			break;
		}

	for (;i < vertex_size;i++)
	{
		if (!is_printed[i] && min_weight > weights[i])
		{
			min_vertex = i;
			min_weight = weights[i];
		}
	}

	return min_vertex;
}

void print_weights(void)
{
	printf("weights : ");
	int i;
	for (i = 0;i < vertex_size;i++) PRINT_OF(weights[i]);
}

void find_MST(int start_vertex)
{
	int i;

	int next_vertex = start_vertex;
	for (i = 0;i < vertex_size;i++)
		weights[i] = graph[next_vertex][i];

	printf("Select : %d ", next_vertex); print_weights();
	is_printed[next_vertex] = true;

	printf("\n");

	int current_vertex;
	int j;
	for (i = 0;i < vertex_size - 1;i++)
	{
		current_vertex = next_vertex;
		next_vertex = find_next_vertex();is_printed[next_vertex] = true;
		for (j = 0;j < vertex_size; j++)
			if (!is_printed[j] && weights[j] > graph[next_vertex][j])
				weights[j] = graph[next_vertex][j];
		cost += graph[current_vertex][next_vertex];

		printf("Select : %d ", next_vertex); print_weights();
		printf(" Edge : (%d %d) ", current_vertex, next_vertex); PRINT_OF(graph[next_vertex][current_vertex]); printf("\n");
	}

	printf("\nMinimum Cost : %d\n", cost);
}