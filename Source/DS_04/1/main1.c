#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef enum {
	FILE_OPEN_ERROR, MEMORY_ALLOCATION_ERROR
};

#define NAME(a) #a // 매크로 함수, "a(variable)"을 반환
// 매크로 함수에서 do{---}while(false) 을 쓰면 한덩어리로 해석함 -> 편하게 매크로 정의 가능
#define CATCH(error) do{printf(NAME(error));exit(0);}while(false) // 오류 시 작동
#define CALLOC(type, data_num, ptr) do{if(!(ptr=(type*)calloc(data_num,sizeof(type)))){CATCH(MEMORY_ALLOCATION_ERROR);}}while(false)
// 1차원 동적할당 매크로
#define CALLOC_2D(type, row, col, ptr) do{CALLOC(type*,row,ptr);int cf;for(cf=0;cf<row;cf++)CALLOC(type,col,ptr[cf]);}while(false)
// 2차원 동적할당 매크로

#define MATRIX_SIZE 20 // 행렬의 크기
#define RANGE 100 // 원소의 범위
#define RANDOM_NUM(range) rand() % range // 난수 생성

void input_matrix(int** matrix, int item_num);

#define LN putchar('\n') // New Line
void print_matrix(int** matrix);

typedef struct node {
	int row_index;
	int col_index;
	int data;
} node;

void make_sparse(node* sparse, int item_num, int** matrix);
void print_sparse(node* sparse, int item_num);

int main(void)
{
	int** matrix;
	CALLOC_2D(int, MATRIX_SIZE, MATRIX_SIZE, matrix);
	srand(time(NULL));

	int item_num;
	printf("원소의 개수를 쓰시오 >> "); scanf_s("%d", &item_num);

	printf("Random generated matrix(20,20)\n");
	input_matrix(matrix, item_num);
	print_matrix(matrix);

	node* sparse;
	CALLOC(node, item_num + 1, sparse);
	make_sparse(sparse, item_num, matrix);
	print_sparse(sparse, item_num);

	return 0;
}

void input_matrix(int** matrix, int item_num)
{
	int tmp_row, tmp_col, tmp_data;
	while (item_num) // item_num != 0 이면 반복해라
	{
		tmp_row = RANDOM_NUM(MATRIX_SIZE);
		tmp_col = RANDOM_NUM(MATRIX_SIZE);
		tmp_data = RANDOM_NUM(RANGE) + 1;

		if (!matrix[tmp_row][tmp_col]) // matrix가 비어 있으면
		{
			matrix[tmp_row][tmp_col] = tmp_data; // data를 넣고
			item_num--; // 개수 차감
		}
	}
}

void print_matrix(int** matrix)
{
	int i, j;
	for (i = 0;i < MATRIX_SIZE;i++)
	{
		for (j = 0;j < MATRIX_SIZE;j++)printf("%5d", matrix[i][j]);
		LN;
	}
	LN;
}

void make_sparse(node* sparse, int item_num, int** matrix)
{
	sparse[0].row_index = MATRIX_SIZE;
	sparse[0].col_index = MATRIX_SIZE;
	sparse[0].data = item_num;

	int scaf = 1;
	int i, j;
	for (i = 0;i < MATRIX_SIZE;i++)
	{
		for (j = 0;j < MATRIX_SIZE;j++)
			if (matrix[i][j]) // data가 있으면 정보 입력
			{
				sparse[scaf].row_index = i; 
				sparse[scaf].col_index = j;
				sparse[scaf].data = matrix[i][j];
				scaf++;
			}
	}
}

void print_sparse(node* sparse, int item_num)
{
	printf("sparse matrix\n");
	int i;
	for (i = 0;i <= item_num;i++)
		printf("%3d%3d%3d\n", sparse[i].row_index, sparse[i].col_index, sparse[i].data);
	LN;
}