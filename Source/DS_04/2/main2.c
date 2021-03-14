#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum {
	FILE_OPEN_ERROR, MEMORY_ALLOCATION_ERROR
};

#define NAME(a) #a
#define CATCH(error) do{printf(NAME(error));exit(0);}while(false)
#define CALLOC(type, data_num, ptr) do{if(!(ptr=(type*)calloc(data_num,sizeof(type)))){CATCH(MEMORY_ALLOCATION_ERROR);}}while(false)

typedef struct term {
	int row_data;
	int col_data;
	int value_data;
} term;

#define LN putchar('\n')
void print_2D_matrix(term* a);
void fastTranspose1(term a[], term b[]);

#define PRINT_INT_ARY(ary, size) do{printf("DD_"NAME(ary));int i;for(i=0;i<size;i++)printf("%4d",ary[i]);LN;}while(false)
void print_sparse(term* a);

void file_input(term* b);

#define FILE_NAME "a.txt"
int main(void)
{
	FILE* fp;fopen_s(&fp, FILE_NAME, "r");

	int row_size, col_size, element_num;
	term* a;
	if (fp)
	{
		fscanf_s(fp, "%d %d %d", &row_size, &col_size, &element_num);
		CALLOC(term, element_num + 1, a);
		a[0].row_data = row_size; a[0].col_data = col_size; a[0].value_data = element_num;
		int i;
		for (i = 1;i <= element_num;i++)
			fscanf_s(fp, "%d %d %d", &a[i].row_data, &a[i].col_data, &a[i].value_data);
		fclose(fp);
	}
	else CATCH(FILE_OPEN_ERROR);

	printf("A\n");
	print_2D_matrix(a);

//	print_sparse(a);

	term* b; CALLOC(term, element_num + 1, b);
	fastTranspose1(a, b);

//	print_sparse(b);

	printf("B\n");
	print_2D_matrix(b);

	file_input(b);

	return 0;
}

void print_2D_matrix(term* a)
{
	int i, j;
	int scaf = 1;
	for (i = 0;i < a[0].row_data;i++)
	{
		for (j = 0;j < a[0].col_data;j++)
		{
			if (a[scaf].row_data == i && a[scaf].col_data == j)
				printf("%4d", a[scaf++].value_data);
			else printf("%4d", 0);
		}
		LN;
	}
	LN;
}

void fastTranspose1(term a[], term b[])
{
	b[0].row_data = a[0].col_data;
	b[0].col_data = a[0].row_data;
	b[0].value_data = a[0].value_data;
	int* col_num; CALLOC(int, a[0].col_data, col_num);
	int* start; CALLOC(int, a[0].col_data, start);

	int i;
	for (i = 1;i <= a[0].value_data;i++) col_num[a[i].col_data]++;
//	PRINT_INT_ARY(col_num, a[0].col_data);
	start[0] = 1;
	for (i = 1;i < a[0].col_data;i++) start[i] = start[i - 1] + col_num[i - 1];
//	PRINT_INT_ARY(start, a[0].col_data);
	term tmp;
	for (i = 1;i <= a[0].value_data;i++)
	{
		tmp.row_data = a[i].col_data;
		tmp.col_data = a[i].row_data;
		tmp.value_data = a[i].value_data;
		b[start[tmp.row_data]++] = tmp;
	}
}

void print_sparse(term* a)
{
	printf("DD_"NAME(print_sparse)); LN;
	int i;
	for (i = 0;i <= a[0].value_data;i++)
		printf("%4d%4d%4d\n", a[i].row_data, a[i].col_data, a[i].value_data);
	LN;
}

void file_input(term* b)
{
	FILE* fp;fopen_s(&fp, "b.txt", "w+");
	if (fp)
	{
		int i;
		for (i = 0;i <= b[0].value_data;i++)
			fprintf_s(fp, "%d %d %d\n", b[i].row_data, b[i].col_data, b[i].value_data);
		fclose(fp);
	}
	else CATCH(FILE_OPEN_ERROR);
}