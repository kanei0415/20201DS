#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

enum {
	FILE_OPEN_ERROR, MEMORY_ALLOCATION_ERROR
};

#define NAME(a) #a
#define CATCH(ERROR) do{printf(NAME(ERROR));exit(0);}while(false)
#define CALLOC(type,data_num,ptr) do{if(!(ptr=(type*)calloc(data_num,sizeof(type)))){CATCH(MEMORY_ALLOCATION_ERROR);}}while(false)

typedef struct node* link;
typedef struct node{
	link l_ch;
	char data;
	bool value;
	link r_ch;
} node;
link root;

#define MAX_STR 80
link stack[MAX_STR];
int top = -1;
void push(link data);
link pop(void);

typedef enum {
	and, or, not, operand, end_of_str
} input_type;

char str[MAX_STR];
int index_str = 0;
char symbol;
input_type token;

input_type get_token(void);

void bi_tree_in(void);

bool int_to_bool(int data);
void eval(link ptr, int a, int b, int c);

#define FILE_NAME "input.txt"
int main(void)
{
	FILE* fp;fopen_s(&fp, FILE_NAME, "r");
	if (fp)
	{
		fscanf_s(fp, "%s", str, sizeof(str));
		fclose(fp);
	}
	else CATCH(FILE_OPEN_ERROR);

	printf("input string : %s\n", str);

	bi_tree_in();

	int a, b, c;
	printf("find true condition\n");
	for (a = 0;a <= 1;a++)
		for (b = 0;b <= 1;b++)
			for (c = 0;c <= 1;c++)
			{
				eval(root, a, b, c);
				if (root->value)
					printf("a = %s b = %s c = %s\n", a ? "true" : "false", b ? "true" : "false", c ? "true" : "false");
			}
	printf("\n");

	return 0;
}

void push(link data)
{
	stack[++top] = data;
}

link pop(void)
{
	return stack[top--];
}

input_type get_token(void)
{
	symbol = str[index_str++];

	switch (symbol)
	{
	case '&': return and;
	case '|': return or;
	case '~': return not;
	case'\0': return end_of_str;
	default: return operand;
	}
}

void bi_tree_in(void)
{
	link tmp;
	token = get_token(); CALLOC(node, 1, tmp);
	tmp->data = symbol; tmp->value = false;

	while (token != end_of_str)
	{
		switch (token)
		{
		case and: case or : tmp->r_ch = pop(); tmp->l_ch = pop(); push(tmp); break;
		case not: tmp->r_ch = pop(); push(tmp); break;
		default: push(tmp); break;
		}
		token = get_token(); CALLOC(node, 1, tmp);
		tmp->data = symbol; tmp->value = false;
	}

	root = pop();
}

bool int_to_bool(int data)
{
	return data ? true : false;
}

void eval(link ptr, int a, int b, int c)
{
	if (ptr)
	{
		eval(ptr->l_ch, a, b, c);
		eval(ptr->r_ch, a, b, c);

		switch (ptr->data)
		{
		case'a': ptr->value = int_to_bool(a); break;
		case'b': ptr->value = int_to_bool(b); break;
		case'c': ptr->value = int_to_bool(c); break;
		case'&': ptr->value = ptr->l_ch->value && ptr->r_ch->value; break;
		case'|': ptr->value = ptr->l_ch->value || ptr->r_ch->value; break;
		case'~': ptr->value = !ptr->r_ch->value; break;
		}
	}
}