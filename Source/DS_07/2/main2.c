#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum {
	FILE_OPEN_ERROR
};

#define NAME(a) #a
#define CATCH(error) do{printf(NAME(error)); exit(0);}while(false)

#define MAX_EXPR_SIZE 80
char expr[MAX_EXPR_SIZE];

typedef enum {
	lparen, rparen, plus, minus, multiple, divide, mod, eos, operand
} token_type;
static int isp[] = { 0, 19, 12, 12, 13, 13, 13, 0 };
static int icp[] = { 20, 19, 12, 12, 13, 13, 13, 0 };

char symbol;
int index_expr = 0;
token_type get_token(void);

typedef struct {
	token_type token_data;
	char symbol_data;
} item;

item stack[MAX_EXPR_SIZE];
int top = -1;
void push(item data);
item pop(void);

token_type token;
char expr_trans[MAX_EXPR_SIZE];
int index_expr_trans = 0;
void postfix(void);


#define FILE_NAME "input.txt"
int main(void)
{
	printf("<<<<<<<<<<< infix to postfix >>>>>>>>>>>\n");
	FILE* fp; fopen_s(&fp, FILE_NAME, "r");
	if (fp)
	{
		fscanf_s(fp, "%s", expr, sizeof(expr));
		fclose(fp);
	}
	else CATCH(FILE_OPEN_ERROR);

	printf("infix expression : %s\n", expr);

	postfix();

	printf("postfix expression : %s\n", expr_trans);

	return 0;
}

token_type get_token(void)
{
	symbol = expr[index_expr++];

	switch (symbol)
	{
	case'(': return lparen;
	case')': return rparen;
	case'+': return plus;
	case'-': return minus;
	case'*': return multiple;
	case'%': return mod;
	case'/': return divide;
	case'\0': return eos;
	default: return operand;
	}
}

void push(item data)
{
	stack[++top] = data;
}

item pop(void)
{
	return stack[top--];
}

void postfix(void)
{
	item tmp;
	tmp.symbol_data = '\0'; tmp.token_data = eos;
	push(tmp);

	for (token = get_token(); token != eos; token = get_token())
	{
		tmp.token_data = token; tmp.symbol_data = symbol;

		if (tmp.token_data == operand)
			expr_trans[index_expr_trans++] = tmp.symbol_data;
		else if (tmp.token_data == rparen)
		{
			while (stack[top].token_data != lparen)
				expr_trans[index_expr_trans++] = pop().symbol_data;
			pop();
		}
		else
		{
			while (isp[stack[top].token_data] >= icp[token])
				expr_trans[index_expr_trans++] = pop().symbol_data;
			push(tmp);
		}
	}

	while (tmp.token_data != eos)
	{
		tmp = pop();
		expr_trans[index_expr_trans++] = tmp.symbol_data;
	}
}