#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

enum {
	FILE_OPEN_ERROR, MEMORY_ALLOCATION_ERROR
};

#define NAME(a) #a
#define CATCH(ERROR) do{printf(NAME(ERROR));exit(0);}while(false)
#define CALLOC(type,data_num,ptr) do{if(!(ptr=(type*)calloc(data_num,sizeof(type)))){CATCH(MEMORY_ALLOCATION_ERROR);}}while(false) 

#define STR_SIZE 80
char str[STR_SIZE];

typedef enum {
	plus, minus, times, divide, mod, operand, EOS
} input_type;

typedef struct item {
	char data;
	input_type type;
} item;

typedef struct node* link;
typedef struct node{
	link l_ch;
	char data;
	link r_ch;
}node;

link root;

char symbol;
int scaf_str = 0;
input_type token;
input_type get_token(void);

link stack[STR_SIZE];
int top = -1;
void push(link data);
link pop(void);

void bi_tree_in(void);

void preorder(link ptr);
void inorder(link ptr);
void postorder(link ptr);

#define FILE_NAME "input.txt"
int main(void)
{
	FILE* fp;fopen_s(&fp, FILE_NAME, "r");
	if (fp)
	{
		fscanf_s(fp,"%s",str,sizeof(str));
		fclose(fp);
	}
	else CATCH(FILE_OPEN_ERROR);

	printf("the length of input string should be less than %d\n", STR_SIZE);
	printf("input string : %s\n", str);

	bi_tree_in();

	printf(NAME(preorder)" : "); preorder(root); printf("\n");
	printf(NAME(inorder)" : "); inorder(root); printf("\n");
	printf(NAME(postorder)" : "); postorder(root); printf("\n");

	return 0;
}

input_type get_token(void)
{
	symbol = str[scaf_str++];
	switch (symbol)
	{
	case'+': return plus;
	case'-': return minus;
	case'*': return times;
	case'/': return divide;
	case'%': return mod;
	case'\0': return EOS;
	default: return operand;
	}
}

void push(link data)
{
	stack[++top] = data;
}

link pop(void)
{
	return stack[top--];
}

void bi_tree_in(void)
{
	link tmp;CALLOC(node, 1, tmp);
	token = get_token(); tmp->data = symbol;

	while (token != EOS)
	{
		switch (token)
		{
		case plus:case minus: case times: case divide: case mod:
			tmp->r_ch = pop(); tmp->l_ch = pop(); push(tmp); break;
		case operand: push(tmp); break;
		case EOS: break;
		}
		token = get_token();
		CALLOC(node, 1, tmp);
		tmp->data = symbol;
	}
	root = pop();
}

void preorder(link ptr)
{
	if (ptr)
	{
		printf("%c", ptr->data);
		preorder(ptr->l_ch);
		preorder(ptr->r_ch);
	}
}

void inorder(link ptr)
{
	if (ptr)
	{
		inorder(ptr->l_ch);
		printf("%c", ptr->data);
		inorder(ptr->r_ch);
	}
}

void postorder(link ptr)
{
	if (ptr)
	{
		postorder(ptr->l_ch);
		postorder(ptr->r_ch);
		printf("%c", ptr->data);
	}
}