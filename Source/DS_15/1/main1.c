#include <Stdio.h>
#include <stdlib.h>
#include <stdbool.h>

enum {
	FILE_OPEN_ERROR
};

#define NAME(a) #a
#define CATCH(ERROR) do{printf(NAME(ERROR));exit(0);}while(false)
#define SWAP(type,x,y) do{type t=x;x=y;y=t;}while(false)

#define HEAP_SIZE 81
int max_heap[HEAP_SIZE];
int data_num = 0;

void max_heap_in(int data);
void print_max_heap(void);

int max_heap_out(void);

#define FILE_NAME "input.txt"
int main(void)
{
	FILE* fp;fopen_s(&fp, FILE_NAME, "r");
	int data;
	if (fp)
	{
		printf("< Insertion into Max Heap >\n");
		while (fscanf_s(fp, "%d", &data) != EOF)
		{
			max_heap_in(data);
			print_max_heap();
		}
		fclose(fp);
	}
	else CATCH(FILE_OPEN_ERROR);

	printf("< Deletion from a Max Heap >\n");
	while (data_num>0)
	{
		printf("out data = %3d\n", max_heap_out());
		print_max_heap();
	}

	return 0;
}

void max_heap_in(int data)
{
	max_heap[++data_num] = data;

	int i;
	for (i = data_num; i > 1; i /= 2)
	{
		if (max_heap[i / 2] < max_heap[i])
			SWAP(int, max_heap[i / 2], max_heap[i]);
		else break;
	}
}

void print_max_heap(void)
{
	int i;
	for (i = 1; i <= data_num;i++)
		printf("%3d", max_heap[i]);
	printf("\n");
}

int max_heap_out(void)
{
	int result = max_heap[1];

	max_heap[1] = max_heap[data_num--];

	int child, parent;
	for (parent = 1; parent * 2 <= data_num;)
	{
		child = parent * 2;
		if (max_heap[child] < max_heap[child + 1]) child++;

		if (max_heap[child] > max_heap[parent])
			SWAP(int, max_heap[child], max_heap[parent]);
		else break;

		parent = child;
	}

	return result;
}