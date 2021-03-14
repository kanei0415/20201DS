#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

enum {
	FILE_OPEN_ERROR, MEMORY_ALLOCATION_ERROR
};

#define NAME(a) #a
#define CATCH(ERROR) do{printf(NAME(ERROR));exit(0);}while(false)
#define CALLOC(type,data_num,ptr) do{if(!(ptr=(type*)calloc(data_num,sizeof(type)))){CATCH(MEMORY_ALLOCATION_ERROR);}}while(false)

typedef struct {
	int coef;
	int expo;
} item;

typedef struct poly_node* poly_pointer;
typedef struct poly_node {
	item data;
	poly_pointer link;
}poly_node;

#define VALUE_EMPTY -1

poly_pointer a, tail_a;
poly_pointer b, tail_b;
poly_pointer c, tail_c;
poly_pointer avail = NULL;

void init_node(poly_pointer ptr);

poly_pointer get_node(void);

#define DESCENDING_ORDER 'd'
#define ASCENDING_ORDER  'a'
void list_in(poly_pointer head, poly_pointer* adr_tail, char sorted_type, int coef, int expo);

void print_poly(poly_pointer head, poly_pointer tail);

#define COMPARE(x, y) (((x) == (y)) ? 0 : (((x) > (y)) ? 1 : -1))
void add_poly(void);

void return_poly(poly_pointer head, poly_pointer tail);

#define FILE_A_NAME "a.txt"
#define FILE_B_NAME "b.txt"
int main(void)
{
	CALLOC(poly_node, 1, a); tail_a = a;
	init_node(a); a->link = a;
	FILE* fp_a;fopen_s(&fp_a, FILE_A_NAME, "r");
	char sorted_type_a;
	int coef_a, expo_a;
	if (fp_a)
	{
		fscanf_s(fp_a, "%c", &sorted_type_a, sizeof(sorted_type_a));
		while (fscanf_s(fp_a, "%d %d", &coef_a, &expo_a) != EOF)
			list_in(a, &tail_a,sorted_type_a, coef_a, expo_a);
		fclose(fp_a);
	}
	else CATCH(FILE_OPEN_ERROR);

	CALLOC(poly_node, 1, b); tail_b = b;
	init_node(b); b->link = b;
	FILE* fp_b;fopen_s(&fp_b, FILE_B_NAME, "r");
	char sorted_type_b;
	int coef_b, expo_b;
	if (fp_b)
	{
		fscanf_s(fp_b, "%c", &sorted_type_b, sizeof(sorted_type_b));
		while (fscanf_s(fp_b, "%d %d", &coef_b, &expo_b) != EOF)
			list_in(b, &tail_b, sorted_type_b, coef_b, expo_b);
		fclose(fp_b);
	}
	else CATCH(FILE_OPEN_ERROR);

	printf("a : \n");
	print_poly(a, tail_a);

	printf("b : \n");
	print_poly(b, tail_b);

	CALLOC(poly_node, 1, c); tail_c = c;
	init_node(c); c->link = c;
	add_poly();

	printf("c : \n");
	print_poly(c, tail_c);

	return_poly(a, tail_a);
	return_poly(b, tail_b);
	return_poly(c, tail_c);

	printf("avail : \n");
	poly_pointer tmp;
	for (tmp = avail; tmp; tmp = tmp->link)
		printf("(%p %c%dx^%d %p)\n", tmp, (tmp->data.coef > 0) ? '+' : '\0', tmp->data.coef, tmp->data.expo, tmp->link);
	printf("\n");

	return 0;
}

void init_node(poly_pointer ptr)
{
	ptr->data.coef = VALUE_EMPTY; ptr->data.expo = VALUE_EMPTY;
	ptr->link = NULL;
}

poly_pointer get_node(void)
{
	poly_pointer tmp = avail;

	if (avail)
	{
		avail = avail->link;
		init_node(tmp);
	}
	else
		CALLOC(poly_node, 1, tmp);

	return tmp;
}

void list_in(poly_pointer head, poly_pointer* adr_tail, char sorted_type, int coef, int expo)
{
	poly_pointer data = get_node();
	data->data.coef = coef; data->data.expo = expo;

	if (sorted_type == DESCENDING_ORDER)
	{
		data->link = head;
		(*adr_tail)->link = data;
		*adr_tail = data;
	}
	else
	{
		if (*adr_tail == head)
			*adr_tail = data;
		data->link = head->link;
		head->link = data;
	}
}

void print_poly(poly_pointer head, poly_pointer tail)
{
	poly_pointer tmp = head;
	for (tmp = head; tmp != tail ; tmp = tmp->link)
		printf("(%p %c%dx^%d %p)\n", tmp, (tmp->data.coef > 0) ? '+' : '\0', tmp->data.coef, tmp->data.expo, tmp->link);
	printf("(%p %c%dx^%d %p)\n", tmp, (tmp->data.coef > 0) ? '+' : '\0', tmp->data.coef, tmp->data.expo, tmp->link);
	printf("\n");
}

void add_poly(void)
{
	poly_pointer scaf_a, scaf_b;

	for (scaf_a = a->link, scaf_b = b->link;scaf_a != a && scaf_b != b;)
	{
		switch (COMPARE(scaf_a->data.expo, scaf_b->data.expo))
		{
		case 1:
			list_in(c, &tail_c, DESCENDING_ORDER, scaf_a->data.coef, scaf_a->data.expo);
			scaf_a = scaf_a->link;
			break;
		case 0:
			list_in(c, &tail_c, DESCENDING_ORDER, scaf_a->data.coef + scaf_b->data.coef, scaf_a->data.expo);
			scaf_a = scaf_a->link;
			scaf_b = scaf_b->link;
			break;
		case -1:
			list_in(c, &tail_c, DESCENDING_ORDER, scaf_b->data.coef, scaf_b->data.expo);
			scaf_b = scaf_b->link;
			break;
		}
	}

	if (scaf_a != a)
	{
		while (scaf_a != a)
		{
			list_in(c, &tail_c, DESCENDING_ORDER, scaf_a->data.coef, scaf_a->data.expo);
			scaf_a = scaf_a->link;
		}
	}

	if (scaf_b != b)
	{
		while (scaf_b != b)
		{
			list_in(c, &tail_c, DESCENDING_ORDER, scaf_b->data.coef, scaf_b->data.expo);
			scaf_b = scaf_b->link;
		}
	}
}

void return_poly(poly_pointer head, poly_pointer tail)
{
	tail->link = avail;
	avail = head;
}