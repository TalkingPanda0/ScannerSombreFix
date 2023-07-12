#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define OFFSET  10088835

uint8_t fixed_bytes[4] = {144,144,144,144};
void writefixed_bytes(FILE *fp)
{
	printf("fwrit %lu\n",fwrite(fixed_bytes,sizeof(uint8_t),4,fp));
}


void iexit()
{
	printf("Press enter to exit");
	getchar();
	exit(0);
}

int main(int argc,char **argv){
	uint8_t broken_bytes[4] = {72,141,70,64};
	if(argc != 2)
	{
		printf("Please give file name\n");
		iexit();
	}
	FILE *fp = fopen(argv[1],"rb+");
	if(!fp)
	{
		printf("Can't open file \n");
		iexit();
	}

	printf("sek cur: %d\n",SEEK_CUR);
	fseek(fp,OFFSET,SEEK_SET);
	uint8_t fileNumbers[4];

	fseek(fp,OFFSET,SEEK_SET);
	fread(fileNumbers,sizeof(uint8_t),4,fp);
	if(memcmp(broken_bytes,fileNumbers,sizeof(broken_bytes)) != 0)
	{
			printf("Couldn't find the right bytes\n");
			iexit();
	}
	for(int i=0;i<4;i++)
	{
		printf("%X\n",fileNumbers[i]);
	}
	printf("sek cur: %d\n",SEEK_CUR);
	fseek(fp, -sizeof(fileNumbers), SEEK_CUR);
	writefixed_bytes(fp);
	printf("sek cur: %d\n",SEEK_CUR);

	printf("sek cur: %d\n",SEEK_CUR);
	fseek(fp, -sizeof(fileNumbers), SEEK_CUR);
	fread(fileNumbers,sizeof(uint8_t),4,fp);
	printf("%d\n",memcmp(fixed_bytes,fileNumbers,sizeof(fixed_bytes)));
	for(int i=0;i<4;i++)
	{
		printf("%X\n",fileNumbers[i]);
	}
	printf("Succescuflty fixed game!\n");
	iexit();



	return 0;
}
