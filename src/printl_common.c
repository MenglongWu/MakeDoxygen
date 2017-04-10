#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include "printl_common.h"

char *g_level_prefix[LEVEL_GROUP];// = {0};// = {0};
char g_level[LEVEL_GROUP * SUB_GROUP] = {0};


// __attribute__((constructor))
// void _pl_init()
// {
// 	// bzero(level_prefix, LEVEL_GROUP);
// 	// bzero(level, LEVEL_GROUP*SUB_GROUP);
// 	// printf("%s %s\n", level_prefix[0], level_prefix[1]);
// }
void pl_prefix(unsigned int row, char *str)
{
	if (row >= LEVEL_GROUP) {
		printf("out of range\n");
		return ;
	}


	char **oldstr = &g_level_prefix[row];

	free(*oldstr);
	*oldstr = NULL;

	*oldstr = (char *)malloc(strlen(str) + 1);

	if ( NULL == *oldstr ) {
		exit(1);
	}
	strcpy(*oldstr, str);
}

void pl_enable(unsigned int row, unsigned int col, bool en)
{
	if (row * LEVEL_GROUP + col >= LEVEL_GROUP * SUB_GROUP) {
		printf("out of range\n");
		return ;
	}
	g_level[ row * LEVEL_GROUP  + col] = en;
}


int pl_getstatus(unsigned int row, unsigned int col)
{
	if (row * LEVEL_GROUP + col >= LEVEL_GROUP * SUB_GROUP) {
		printf("out of range\n");
		return -1;
	}
	return g_level[ row * LEVEL_GROUP  + col];
}