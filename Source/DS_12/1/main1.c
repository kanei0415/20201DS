#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

enum{
	FILE_OPEN_ERROR, MEMORY_ALLOCATON_ERROR
};

#define NAME(a) #a
#define CATCH(ERROR) do{printf(NAME(ERROR));exit(0);}while(false)
#define CALLOC(type,data_num,ptr) do{if(!(ptr=(type*)calloc(data_num,sizeof(type)))){CATCH(MEMORY_ALLOCATON_ERROR);}}while(false)

typedef struct node* link;
typedef struct node{
	link lch;
	char data;
	link rch;
} node;

#define MAX_STRING_SIZE 80
link queue[MAX_STRING_SIZE];
int front = 0, rear = 0;
void add_q(link data);
link delete_q(void);

char str[MAX_STRING_SIZE];
int index_str = 0;

link root = NULL;

int count_child(link this);
void tree_in(void);

void preorder(link ptr);
void inorder(link ptr);
void postorder(link ptr);

#define FILE_NAME "input.txt"
int main(void)
{
	FILE* fp; fopen_s(&fp, FILE_NAME, "r");
	if (fp)
	{
		fscanf_s(fp, "%s", str, sizeof(str));
		fclose(fp);
	}
	else CATCH(FILE_OPEN_ERROR);

	printf("input string : %s\n", str);

	tree_in();

	printf(NAME(preorder)" : ");preorder(root);printf("\n");
	printf(NAME(inorder)" : ");inorder(root);printf("\n");
	printf(NAME(postorder)" : ");postorder(root);printf("\n");

	return 0;
}

void add_q(link data)
{
	queue[rear++] = data;
}

link delete_q(void)
{
	return queue[front++];
}

int count_child(link this)
{
	int count = 0;
	if (this->lch) count++;
	if (this->rch) count++;
	return count;
}

void tree_in(void)
{
	link cur_node_ptr = NULL;
	link tmp;

	while (str[index_str])
	{
		CALLOC(node, 1, tmp); tmp->data = str[index_str++]; add_q(tmp);
		if (!cur_node_ptr)
			root = cur_node_ptr = tmp;
		else
		{
			switch (count_child(cur_node_ptr))
			{
			case 0: cur_node_ptr->lch = tmp; break;
			case 1: cur_node_ptr->rch = tmp; cur_node_ptr = delete_q(); break;
			case 2: cur_node_ptr = delete_q(); cur_node_ptr->lch = tmp; break;
			}
		}
	}
}

void preorder(link ptr)
{
	if (ptr)
	{
		printf("%c", ptr->data);
		preorder(ptr->lch);
		preorder(ptr->rch);
	}
}

void inorder(link ptr)
{
	if (ptr)
	{
		inorder(ptr->lch);
		printf("%c", ptr->data);
		inorder(ptr->rch);
	}
}

void postorder(link ptr)
{
	if (ptr)
	{
		postorder(ptr->lch);
		postorder(ptr->rch);
		printf("%c", ptr->data);
	}
}