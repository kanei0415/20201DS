#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum {
	FILE_OPEN_ERROR
};

#define NAME(a) #a
#define CATCH(error) do{printf(NAME(error)); exit(0);}while(false)

#define MAX_EXPR_SIZE 80
char expr[80];

typedef enum {
	plus, minus, muliple, divide, operand, eos
} token_type;

char symbol;
int index_expr = 0;
token_type token_expr;
token_type get_token(void);

token_type token;
int eval(void);

int stack[MAX_EXPR_SIZE];
int top = -1;
void push(int data);
int pop(void);

#define FILE_NAME "input.txt"
int main(void)
{
	FILE* fp;fopen_s(&fp, FILE_NAME, "r");
	if (fp)
	{
		fscanf_s(fp, "%s", expr, sizeof(expr));
		fclose(fp);
	}
	else CATCH(FILE_OPEN_ERROR);

	printf("postfix expression : %s\n", expr);
	printf("result : %d\n", eval());
	return 0;
}

token_type get_token(void)
{
	symbol = expr[index_expr++];
	switch (symbol)
	{
	case '+': return plus;
	case '-': return minus;
	case '*': return muliple;
	case '/': return divide;
	case '\0': return eos;
	default: return operand;
	}
}

void push(int data)
{
	stack[++top] = data;
}

int pop(void)
{
	return stack[top--];
}

int eval(void)
{
	token = get_token();
	int op1, op2;
	while (token != eos)
	{
		switch (token)
		{
		case plus: op2 = pop(); op1 = pop(); push(op1 + op2); break;
		case minus: op2 = pop(); op1 = pop(); push(op1 - op2);break;
		case muliple: op2 = pop(); op1 = pop(); push(op1 * op2);break;
		case divide: op2 = pop(); op1 = pop(); push(op1 / op2);break;
		case operand: push(symbol - '0'); break;
		}
		token = get_token();
	}
	return pop();
}