#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum {
	FILE_OPEN_ERROR, MEMORY_ALLOCATION_ERROR
};

#define NAME(a) #a
#define CATCH(error) do{printf(NAME(error));exit(0);}while(false)
#define CALLOC(type, data_num, ptr) do{if(!(ptr=(type*)calloc(data_num,sizeof(type)))){CATCH(MEMORY_ALLOCATION_ERROR);}}while(false)
#define CALLOC_2D(type, row, col, ptr) do{ptr=(type**)calloc(row,sizeof(type*));int d_i;for(d_i=0;d_i<row;d_i++)CALLOC(type,col,ptr[d_i]);}while(false)

int** maze;
int** mark;

typedef struct item {
	int row;
	int col;
	int dir;
} item;

#define TOP_INIT -1
item* stack;
int top = TOP_INIT;
bool stack_empty(void);
void push(item data);
item pop(void);

typedef struct move {
	int ver_move;
	int hor_move;
} move;

move movings[8];

#define MAZE_MOVEABLE 0
#define MAZE_UNMOVEABLE 1
#define MARK_NOT_WENT 0
#define MARK_WENT 1

void print_DD_maze(int row_size, int col_size);

#define START_ROW 1
#define START_COL 1
#define START_DIR 0
#define END_DIR 7
void find_path(int row_size, int col_size);

#define FILE_NAME "input.txt"
int main(void)
{
// dir에 따른 움직임************************************
	movings[0].ver_move = -1; movings[0].hor_move =  0;
	movings[1].ver_move = -1; movings[1].hor_move =  1;
	movings[2].ver_move =  0; movings[2].hor_move =  1;
	movings[3].ver_move =  1; movings[3].hor_move =  1;
	movings[4].ver_move =  1; movings[4].hor_move =  0;
	movings[5].ver_move =  1; movings[5].hor_move = -1;
	movings[6].ver_move =  0; movings[6].hor_move = -1;
	movings[7].ver_move = -1; movings[7].hor_move = -1;
// ****************************************************

	FILE* fp;fopen_s(&fp, FILE_NAME, "r");
	int row_size, col_size;
	if (fp)
	{
		fscanf_s(fp, "%d %d", &row_size, &col_size);
		CALLOC_2D(int, row_size + 2, col_size + 2, maze);
		CALLOC_2D(int, row_size + 2, col_size + 2, mark);

		int i, j;
		for (i = 0; i <= row_size + 1; i++)
			for (j = 0;j <= col_size + 1;j++)
			{
				maze[i][j] = MAZE_UNMOVEABLE;
				mark[i][j] = MARK_NOT_WENT;
			}
		for (i = 1; i <= row_size; i++)
			for (j = 1; j <= col_size; j++)
				fscanf_s(fp, "%d", &maze[i][j]);
	}
	else CATCH(FILE_OPEN_ERROR);

//	print_DD_maze(row_size, col_size);

	CALLOC(item, row_size * col_size, stack);

	find_path(row_size, col_size);

	return 0;
}

bool stack_empty(void)
{
	return top <= TOP_INIT;
}

void push(item data)
{
	stack[++top] = data;
}

item pop(void)
{
	return stack[top--];
}

void print_DD_maze(int row_size, int col_size)
{
	printf("%3d%3d\n", row_size, col_size);
	int i, j;
	for (i = 0; i <= row_size + 1; i++)
	{
		for (j = 0; j <= col_size + 1; j++)
			printf("%3d", maze[i][j]);
		printf("\n");
	}
	printf("\n");
}

void find_path(int row_size, int col_size)
{
	const int END_ROW = row_size, END_COL = col_size;
	bool is_find = false;
	item tmp, position;

	mark[START_ROW][START_COL] = MARK_WENT;
	tmp.row = START_ROW; tmp.col = START_COL; tmp.dir = START_DIR;
	push(tmp);

	int cur_row = 0, cur_col = 0, cur_dir = 0;
	int next_row = 0, next_col = 0;
	while (!stack_empty() && !is_find)
	{
		// 스택에서 이전 위치 가져오기
		position = pop();
		cur_row = position.row; cur_col = position.col; cur_dir = position.dir;

		while (cur_dir <= END_DIR && !is_find) // 다음으로 향할 자리 탐색
		{
			next_row = cur_row + movings[cur_dir].ver_move;
			next_col = cur_col + movings[cur_dir].hor_move;

			// 다음 자리가 출구이면
			if (next_row == END_ROW && next_col == END_COL)
			{
				// 현재의 위치를
				tmp.row = cur_row; tmp.col = cur_col; tmp.dir = ++cur_dir;
				// 스택에 넣기
				push(tmp);

				// 출구를
				tmp.row = next_row; tmp.col = next_col; tmp.dir = START_DIR;
				// 스택에 넣기
				push(tmp);

				// 종료
				is_find = true;
			}
			// 갈 수 있고, 방문한 적이 없는 자리면
			else if (maze[next_row][next_col] == MAZE_MOVEABLE && mark[next_row][next_col] == MARK_NOT_WENT)
			{
				// 현재 위치를 스택에 넣고
				position.row = cur_row; position.col = cur_col; position.dir = ++cur_dir;
				push(position);

				// 다음 자리로 위치를 변경
				cur_row = next_row; cur_col = next_col; cur_dir = START_DIR;
				// 방문한 것을 표시
				mark[next_row][next_col] = MARK_WENT;
			}
			// 아니면 다음 방향의 자리 탐색
			else ++cur_dir;
		} // 한 자리에서 모든 방향의 탐색을 마치거나 출구를 찾으면 탈출
	} // 모든 길을 탐색하거나, 출구를 찾으면 탈출

	if (is_find)
	{
		printf("The path is : \n");
		printf("row col\n");
		int i;
		for (i = 0; i <= top; i++)
			printf("%2d  %2d\n", stack[i].row, stack[i].col);
		printf("\n");
	}
	else printf("The maze does not have a path\n");
}