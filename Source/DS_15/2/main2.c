#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

enum {
	FILE_OPEN_ERROR
};

#define NAME(a) #a
#define CATCH(ERROR) do{printf(NAME(ERROR));exit(0);}while(false)
#define SWAP(type,x,y) do{type t=x;x=y;y=t;}while(false)

#define HEAP_SIZE 81
int min_heap[HEAP_SIZE];
int data_num = 0;

void min_heap_in(int data);
void print_min_heap(void);

int min_heap_out(void);

#define FILE_NAME "input.txt"
int main(void)
{
	FILE* fp;fopen_s(&fp, FILE_NAME, "r");
	int data;
	if (fp)
	{
		printf("< Insertion into Min Heap >\n");
		while (fscanf_s(fp, "%d", &data) != EOF)
		{
			min_heap_in(data);
			print_min_heap();
		}
		fclose(fp);
	}
	else CATCH(FILE_OPEN_ERROR);

	printf("< Deletion from a Min Heap >\n");
	while (data_num > 0)
	{
		printf("out data = %3d\n", min_heap_out());
		print_min_heap();
	}

	return 0;
}

void min_heap_in(int data)
{
	min_heap[++data_num] = data;

	int i;
	for (i = data_num; i > 1; i /= 2)
	{
		if (min_heap[i / 2] > min_heap[i])
			SWAP(int, min_heap[i / 2], min_heap[i]);
		else break;
	}
}

void print_min_heap(void)
{
	int i;
	for (i = 1; i <= data_num;i++)
		printf("%3d", min_heap[i]);
	printf("\n");
}

int min_heap_out(void)
{
	int result = min_heap[1];

	min_heap[1] = min_heap[data_num--];

	int child, parent;
	for (parent = 1; parent * 2 <= data_num;)
	{
		child = parent * 2;
		if (min_heap[child] > min_heap[child + 1]) child++;

		if (min_heap[child] < min_heap[parent])
			SWAP(int, min_heap[child], min_heap[parent]);
		else break;

		parent = child;
	}

	return result;
}