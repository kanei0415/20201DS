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

poly_pointer a;
poly_pointer b;
poly_pointer c;

#define DESCENDING_ORDER 'd'
#define ASCENDING_ORDER  'a'
void list_in(poly_pointer* adr_head, char sorted_type, int coef, int expo);

void print_poly(poly_pointer head);

#define COMPARE(x, y) (((x) == (y)) ? 0 : (((x) > (y)) ? 1 : -1))
void add_poly(void);

#define FILE_A_NAME "a.txt"
#define FILE_B_NAME "b.txt"
int main(void)
{
	FILE* fp_a;fopen_s(&fp_a, FILE_A_NAME, "r");
	char sorted_type_a;
	int coef_a, expo_a;
	if (fp_a)
	{
		fscanf_s(fp_a, "%c", &sorted_type_a, sizeof(sorted_type_a));
		while (fscanf_s(fp_a, "%d %d", &coef_a, &expo_a) != EOF)
			list_in(&a, sorted_type_a, coef_a, expo_a);
		fclose(fp_a);
	}
	else CATCH(FILE_OPEN_ERROR);

	FILE* fp_b;fopen_s(&fp_b, FILE_B_NAME, "r");
	char sorted_type_b;
	int coef_b, expo_b;
	if (fp_b)
	{
		fscanf_s(fp_b, "%c", &sorted_type_b, sizeof(sorted_type_b));
		while (fscanf_s(fp_b, "%d %d", &coef_b, &expo_b) != EOF)
			list_in(&b, sorted_type_b, coef_b, expo_b);
		fclose(fp_b);
	}
	else CATCH(FILE_OPEN_ERROR);

	printf("a : \n");
	print_poly(a);

	printf("b : \n");
	print_poly(b);

	add_poly();

	printf("c : \n");
	print_poly(c);

	return 0;
}

void list_in(poly_pointer* adr_head, char sorted_type, int coef, int expo)
{
	poly_pointer data; CALLOC(poly_node, 1, data);
	data->data.coef = coef; data->data.expo = expo;

	if (!(*adr_head))
		*adr_head = data;
	else
	{
		if (sorted_type == ASCENDING_ORDER)
		{
			data->link = *adr_head;
			*adr_head = data;
		}
		else
		{
			poly_pointer scaf;
			for (scaf = *adr_head; scaf->link; scaf = scaf->link);
			scaf->link = data;
		}
	}
}

void print_poly(poly_pointer head)
{
	poly_pointer tmp;
	for (tmp = head;tmp;tmp = tmp->link)
		printf("(%p %c%dx^%d %p)\n", tmp, (tmp->data.coef > 0) ? '+' : '\0', tmp->data.coef, tmp->data.expo, tmp->link);
	printf("\n");
}

void add_poly(void)
{
	poly_pointer scaf_a, scaf_b;
	
	for (scaf_a = a, scaf_b = b;scaf_a && scaf_b;)
	{
		switch (COMPARE(scaf_a->data.expo, scaf_b->data.expo))
		{
		case 1:
			list_in(&c, DESCENDING_ORDER, scaf_a->data.coef, scaf_a->data.expo);
			scaf_a = scaf_a->link;
			break;
		case 0:
			list_in(&c, DESCENDING_ORDER, scaf_a->data.coef + scaf_b->data.coef, scaf_a->data.expo);
			scaf_a = scaf_a->link;
			scaf_b = scaf_b->link;
			break;
		case -1:
			list_in(&c, DESCENDING_ORDER, scaf_b->data.coef, scaf_b->data.expo);
			scaf_b = scaf_b->link;
			break;
		}
	}

	if (scaf_a)
	{
		while (scaf_a)
		{
			list_in(&c, DESCENDING_ORDER, scaf_a->data.coef, scaf_a->data.expo);
			scaf_a = scaf_a->link;
		}
	}

	if (scaf_b)
	{
		while (scaf_b)
		{
			list_in(&c, DESCENDING_ORDER, scaf_b->data.coef, scaf_b->data.expo);
			scaf_b = scaf_b->link;
		}
	}
}