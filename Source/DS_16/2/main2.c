#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

enum {
	MEMORY_OPEN_ERROR
};

#define NAME(a) #a
#define CATCH(ERROR) do{printf(NAME(ERROR));exit(0);}while(false)
#define CALLOC(type,data_num,ptr) do{if(!(ptr=(type*)calloc(data_num,sizeof(type)))){CATCH(MEMORY_OPEN_ERROR);}}while(false)
#define CALLOC_2D(type,row,col,ptr)do{CALLOC(type*,row,ptr);int iter;for(iter = 0; iter < row; iter++)CALLOC(type,col,ptr[iter]);}while(false)

#define RUN_SIZE 10
int* winner_tree;
int* index_ary_of_each_run;
int** run_table;

#define INF 123456789
#define RAND_RANGE 500
#define RAND_NUM (rand()%RAND_RANGE+1)

void make_run_table(void);

#define SWAP(type,x,y) do{type t=x;x=y;y=t;}while(false)
void sorting_run_table(void);

#define PRINT_NUM(num) (num==INF) ? (printf(" INF")) : (printf("%4d",num))
void print_run_table(void);

void init_winner_tree(void);

int* result;
int iter_result = 0;
void sort_with_winner_tree(void);

void print_result(void);

int run_number;
int seed_value;
int main(void)
{
	printf("< Sorting with winner tree >\n");

	printf("Enter the number of runs (4, 8, 16, 32 as a power of 2) >> ");
	scanf_s("%d", &run_number);

	CALLOC_2D(int, RUN_SIZE + 1, run_number, run_table);
	CALLOC(int, run_number, index_ary_of_each_run);
	CALLOC(int, run_number * 2, winner_tree);

	CALLOC(int, (run_number * RUN_SIZE), result);

	printf("Enter the seed value >> ");
	scanf_s("%d", &seed_value);

	srand(seed_value);

	printf("\n< Initialize Run Table >\n");
	make_run_table();
	sorting_run_table();
	print_run_table();

	printf("\n< Sorting >\n");
	init_winner_tree();

	sort_with_winner_tree();

	print_result();
	return 0;
}

void make_run_table(void)
{
	int i, j;
	for (j = 0;j < run_number;j++)
	{
		for (i = 0;i < RUN_SIZE;i++)
			run_table[i][j] = RAND_NUM;
		run_table[i][j] = INF;
	}
}

void sorting_run_table(void)
{
	int i, j, k;
	for (j = 0;j < run_number;j++)
	{
		for (k = 0;k < RUN_SIZE;k++)
			for (i = 0;i < RUN_SIZE - 1;i++)
				if (run_table[i][j] > run_table[i + 1][j])
					SWAP(int, run_table[i][j], run_table[i + 1][j]);
	}
}

void print_run_table(void)
{
	printf("initial_records\n");
	int i, j;
	for (j = 0;j < run_number;j++)
	{
		printf("%d-th run\n", j + 1);
		for (i = 0;i < RUN_SIZE;i++)
			PRINT_NUM(run_table[i][j]);
		printf("\n");
	}
	printf("\n");
}

void init_winner_tree(void)
{
	int i;
	for (i = run_number;i < (2 * run_number);i++)
	{
		winner_tree[i] = i - run_number;
		index_ary_of_each_run[i - run_number] = 0;
	}

	int l_ch_winner_tree_value, r_ch_winner_tree_value;
	int l_ch_run_table_value, r_ch_run_table_value;

	for (i = run_number / 2;i >= 1;)
	{
		l_ch_winner_tree_value = winner_tree[i * 2];
		r_ch_winner_tree_value = winner_tree[i * 2 + 1];

		l_ch_run_table_value = run_table[index_ary_of_each_run[l_ch_winner_tree_value]][l_ch_winner_tree_value];
		r_ch_run_table_value = run_table[index_ary_of_each_run[r_ch_winner_tree_value]][r_ch_winner_tree_value];

		winner_tree[i] = (l_ch_run_table_value > r_ch_run_table_value) ? (r_ch_winner_tree_value) : (l_ch_winner_tree_value);

		if (((++i) % 4) == 0) i /= 4;
		else if (i == 2)break;
	}
}

void sort_with_winner_tree(void)
{
	int l_ch_winner_tree_value, r_ch_winner_tree_value;
	int l_ch_run_table_value, r_ch_run_table_value;

	int i;
	for (iter_result = 0;iter_result < (run_number * RUN_SIZE);iter_result++)
	{
		result[iter_result] = run_table[index_ary_of_each_run[winner_tree[1]]++][winner_tree[1]];

		for (i = run_number / 2;i >= 1;)
		{
			l_ch_winner_tree_value = winner_tree[i * 2];
			r_ch_winner_tree_value = winner_tree[i * 2 + 1];

			l_ch_run_table_value = run_table[index_ary_of_each_run[l_ch_winner_tree_value]][l_ch_winner_tree_value];
			r_ch_run_table_value = run_table[index_ary_of_each_run[r_ch_winner_tree_value]][r_ch_winner_tree_value];

			winner_tree[i] = (l_ch_run_table_value > r_ch_run_table_value) ? (r_ch_winner_tree_value) : (l_ch_winner_tree_value);

			if (((++i) % 4) == 0) i /= 4;
			else if (i == 2) break;
		}
	}
}

void print_result(void)
{
	int i;
	for (i = 0;i < iter_result;i++)
	{
		PRINT_NUM(result[i]);
		if ((i + 1) % RUN_SIZE == 0)printf("\n");
	}
	printf("\n");
}