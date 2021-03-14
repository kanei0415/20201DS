#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

enum {
	FILE_OPEN_ERROR, MEMORY_ALLOCAION_ERROR
};

#define NAME(a) #a
#define CATCH(ERROR) do{printf(NAME(ERROR));exit(0);}while(false)
#define CALLOC(type,data_type,ptr) do{if(!(ptr=(type*)calloc(data_num,sizeof(type)))){CATCH(MEMORY_ALLOCAION_ERROR);}}while(false)

int ary_size;
int* ary;

#define FILE_NAME "input.txt"
int main(void)
{
	FILE* fp; fopen_s(&fp, FILE_NAME, "r");
	if (fp)
	{
		fscanf_s(fp,)
		fclose(fp);
	}
	else CATCH(FILE_OPEN_ERROR);

	return 0;
}