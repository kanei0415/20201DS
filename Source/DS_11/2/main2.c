#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

enum {
	FILE_OPEN_ERROR, MEMORY_OPEN_ERROR
};

#define NAME(a) #a
#define CATCH(ERROR) do{printf(NAME(ERROR));exit(0);}while(false)
#define CALLOC(type,data_num,ptr) do{if(!(ptr=(type*)calloc(data_num,sizeof(type)))){CATCH(MEMORY_OPEN_ERROR);}}while(false)

typedef struct node* nodePointer;
typedef struct node {
	nodePointer llink;
	int data;
	nodePointer rlink;
} node;

nodePointer header = NULL;

void list_in(int data);

void print_list_forward(void);
void print_list_backward(void);

void delete_less_50(void);

#define FILE_NAME "input.txt"
int main(void)
{
	CALLOC(node, 1, header);
	header->llink = header; header->rlink = header;
	FILE* fp;fopen_s(&fp, FILE_NAME, "r");
	int data;
	if (fp)
	{
		while (fscanf_s(fp, "%d", &data) != EOF)
			list_in(data);
		fclose(fp);
	}
	else CATCH(FILE_OPEN_ERROR);

	print_list_forward();

	printf("\n");

	print_list_backward();

	delete_less_50();
	printf("\nAfter deleting datas less than and equel to 50\n\n");

	print_list_forward();

	printf("\n");

	print_list_backward();

	return 0;
}

void list_in(int data)
{
	nodePointer tmp; CALLOC(node, 1, tmp);
	tmp->data = data;
	tmp->llink = header->llink;
	tmp->rlink = header;
	header->llink->rlink = tmp;
	header->llink = tmp;
}

void print_list_forward(void)
{
	printf("< Forward Print >\n");
	nodePointer scaf;
	for (scaf = header->rlink;scaf != header;scaf = scaf->rlink)
		printf("(%p %p %d %p) ", scaf->llink, scaf, scaf->data, scaf->rlink);
	printf("\n");
}

void print_list_backward(void)
{
	printf("< Backward Print >\n");
	nodePointer scaf;
	for (scaf = header->llink;scaf != header;scaf = scaf->llink)
		printf("(%p %p %d %p) ", scaf->llink, scaf, scaf->data, scaf->rlink);
	printf("\n");
}

void delete_less_50(void)
{
	nodePointer scaf, tmp;
	for (scaf = header->rlink;scaf != header;scaf = scaf->rlink)
		if (scaf->data <= 50)
		{
			tmp = scaf;
			scaf->llink->rlink = tmp->rlink;
			scaf->rlink->llink = tmp->llink;
			scaf = tmp->rlink;
			free(tmp);
		}
}