#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_WORD_LENGTH 30
int main(int argc, char *argv[])
{
	if(argc == 1)
	{
		printf("The name of the file is missing!\n");
		return 1;
	}

	int count=0;
	FILE *fp;
	char ch[MAX_WORD_LENGTH];/*define the maximum length that will be scaned */
	fp=fopen(argv[1],"r");
	while(fscanf(fp,"%s",ch)!=EOF)
	{
		count++;
	}/*if a character is scaned, count will be incremented by 1 */
	printf("Number of characters is %d\n",count);
	fclose(fp);
	return 0;
}