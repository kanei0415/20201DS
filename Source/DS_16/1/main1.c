#include <stdio.h>
#include <Stdlib.h>
#include <stdbool.h>

enum {
	FILE_OPEN_ERROR, MEMORY_ALLOCATION_ERROR
};

#define NAME(a) #a
#define CATCH(ERROR) do{printf(NAME(ERROR));exit(0);}while(false)
#define CALLOC(type,data_num,ptr) do{if(!(ptr=(type*)calloc(data_num,sizeof(type)))){CATCH(MEMORY_ALLOCATION_ERROR);}}while(false)

typedef struct node* link;
typedef struct node {
	link l_ch;
	int key;
	link r_ch;
} node;
link root;

#define MAX_SIZE 500
#define RAND (rand() % MAX_SIZE + 1)

int n, seed;

link modified_search(int key);
bool add_node(int key);
void  make_BST(void);

void search(int key);

void inorder(link ptr);

int main(void)
{
	printf("random number generation (1 ~ %d)\n", MAX_SIZE);
	printf("%s", "the number of nodes in BST (less than and equal to 50) : ");
	scanf_s("%d", &n);
	printf("%s", "seed : ");
	scanf_s("%u", &seed);
	printf("\ncreating a BST from random numbers\n");
	srand(seed);

	make_BST();

	int find_key;
	printf("Enter the key to search >> ");
	scanf_s("%d", &find_key);
	search(find_key);

	printf("Inorder treversal of the BST shows the sorted sequence\n");
	inorder(root);
	printf("\n");
	return 0;
}

link modified_search(int key)
{
	link location_of_parent = NULL;

	if (!root) return NULL;
	else
	{
		for (location_of_parent = root;location_of_parent;)
		{
			if (location_of_parent->key < key)
			{
				if (!location_of_parent->r_ch)
					return location_of_parent;
				else location_of_parent = location_of_parent->r_ch;
			}
			else if (location_of_parent->key == key)
				return NULL;
			else
			{
				if (!location_of_parent->l_ch)
					return location_of_parent;
				else location_of_parent = location_of_parent->l_ch;
			}
		}
	}

	return location_of_parent;
}

bool add_node(int key)
{
	link tmp; CALLOC(node, 1, tmp);
	tmp->key = key;
	if (!root)
		root = tmp;
	else
	{
		link location_of_parent = modified_search(key);

		if (!location_of_parent) return false;

		if (location_of_parent->key < key)
			location_of_parent->r_ch = tmp;
		else
			location_of_parent->l_ch = tmp;
	}
	return true;
}

void  make_BST(void)
{
	printf("< Make BST >\n");

	int i;
	int tmp;

	printf("generating numbers : ");
	for (i = 0;i < n;)
	{
		tmp = RAND;
		if (add_node(tmp))
		{
			printf("%4d", tmp);
			i++;
		}
	}
	printf("\n");
}

void search(int key)
{
	printf("The search process : ");
	link scaf; bool is_find = false;
	for (scaf = root;scaf;)
	{
		printf("%d => ", scaf->key);

		if (scaf->key == key)
		{
			is_find = true;
			break;
		}

		scaf = (scaf->key < key) ? (scaf->r_ch) : (scaf->l_ch);
	}
	printf("\n");

	if (is_find)
		printf("The element is in BST\n");
	else
		printf("The element is not in BST\n");
}

void inorder(link ptr)
{
	if (ptr)
	{
		inorder(ptr->l_ch);
		printf("%4d", ptr->key);
		inorder(ptr->r_ch);
	}
}