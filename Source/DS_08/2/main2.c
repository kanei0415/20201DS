#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef enum {
	MEMORY_ALLOCATION_ERROR, FILE_OPEN_ERROR
};

#define NAME(a) #a
#define CATCH(error) do{printf(NAME(error));exit(0);}while(false)
#define CALLOC(type, data_num,ptr) do{if(!(ptr=(type*)calloc(data_num,sizeof(type)))){CATCH(MEMORY_ALLOCATION_ERROR);}}while(false)

#define STRING_SIZE 20
typedef struct {
	char name[STRING_SIZE];
	char background[STRING_SIZE];
	char sex[STRING_SIZE];
} item;

typedef struct listNode* listPointer;
typedef struct listNode {
	item data;
	listPointer link;
} listNode;
listPointer head = NULL;
listPointer tail = NULL;

void list_in(listPointer* adr_head, listPointer* adr_tail, char name[STRING_SIZE], char background[STRING_SIZE], char sex[STRING_SIZE]);
void print_list(listPointer head);

listPointer male = NULL;
listPointer tail_male = NULL;

listPointer female = NULL;
listPointer tail_female = NULL;
void divide(void);

#define FILE_NAME "input.txt"
int main(void)
{
	FILE* fp;fopen_s(&fp, FILE_NAME, "r");
	char name[STRING_SIZE];
	char background[STRING_SIZE];
	char sex[STRING_SIZE];
	if (fp)
	{
		while (fscanf_s(fp, "%s %s %s", name, sizeof(name), background, sizeof(background), sex, sizeof(sex)) != EOF)
			list_in(&head, &tail, name, background, sex);
		fclose(fp);
	}
	else CATCH(FILE_OPEN_ERROR);

	printf("전체리스트\n");
	print_list(head);

	divide();

	printf("남자리스트\n");
	print_list(male);

	printf("여자리스트\n");
	print_list(female);

	return 0;
}

void list_in(listPointer* adr_head, listPointer* adr_tail, char name[STRING_SIZE], char background[STRING_SIZE], char sex[STRING_SIZE])
{
	listPointer tmp; CALLOC(listNode, 1, tmp);
	strcpy_s(tmp->data.name, sizeof(tmp->data.name), name);
	strcpy_s(tmp->data.background, sizeof(tmp->data.background), background);
	strcpy_s(tmp->data.sex, sizeof(tmp->data.sex), sex);

	if (!(*adr_head))
		*adr_head = *adr_tail = tmp;
	else
	{
		(*adr_tail)->link = tmp;
		*adr_tail = tmp;
	}
}

void print_list(listPointer head)
{
	listPointer tmp;
	for (tmp = head; tmp;tmp = tmp->link)
		printf("(%p, %s, %s, %s, %p)\n", tmp, tmp->data.name, tmp->data.background, tmp->data.sex, tmp->link);
	printf("\n");
}

void divide(void)
{
	listPointer tmp = head;
	while (tmp)
	{
		if (strcmp(tmp->data.sex, "남자") == 0)
			list_in(&male, &tail_male, tmp->data.name, tmp->data.background, tmp->data.sex);
		else
			list_in(&female, &tail_female, tmp->data.name, tmp->data.background, tmp->data.sex);

		tmp = tmp->link;
	}
}