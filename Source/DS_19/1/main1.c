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
	int from;
	int to;
	int weight;
} edge_data;

edge_data* edges;

#define ROOT_OF_SET -1
int* set;

void init_set(void);

int vertex_size, edge_size;

#define SWAP(type,x,y) do{type t=x;x=y;y=t;}while(false)
void sort_edges(void);

int find_root_of(int a);
bool is_same_set(int a, int b);

int cost = 0;
void find_MST(void);

#define FILE_NAME "input.txt"
int main(void)
{
	FILE* fp; fopen_s(&fp, FILE_NAME, "r");
	int tmp_from, tmp_to, tmp_weight;
	if (fp)
	{
		fscanf_s(fp, "%d %d", &vertex_size, &edge_size);

		CALLOC(edge_data, edge_size, edges);
		CALLOC(int, vertex_size, set);
		init_set();

		int i;
		for (i = 0;i < edge_size;i++)
		{
			fscanf_s(fp, "%d %d %d", &tmp_from, &tmp_to, &tmp_weight);
			edges[i].from = tmp_from;
			edges[i].to = tmp_to;
			edges[i].weight = tmp_weight;
		}
		fclose(fp);
	}
	else CATCH(FILE_OPEN_ERROR);

	sort_edges();

	find_MST();

	return 0;
}

void init_set(void)
{
	int i;
	for (i = 0;i < vertex_size;i++)
		set[i] = ROOT_OF_SET;
}

void sort_edges(void)
{
	int i, j;
	for (i = 0;i < edge_size;i++)
	{
		for (j = 0;j < edge_size - 1;j++)
			if (edges[j].weight > edges[j + 1].weight)
				SWAP(edge_data, edges[j], edges[j + 1]);
	}
}

int find_root_of(int a)
{
	for (;set[a] != ROOT_OF_SET;a = set[a]);
	return a;
}

bool is_same_set(int a, int b)
{
	return (find_root_of(a) == find_root_of(b));
}

void find_MST(void)
{
	int i;
	printf("< MST >\n");
	for (i = 0;i < edge_size;i++)
	{
		if (!is_same_set(edges[i].from, edges[i].to))
		{
			printf("(%d %d) : %d\n", edges[i].from, edges[i].to, edges[i].weight);
			cost += edges[i].weight;

			set[find_root_of(edges[i].to)] = find_root_of(edges[i].from);
		}
	}

	printf("\nMinimum Cost : %d\n", cost);
}