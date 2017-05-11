#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include "printl.h"
#include "printl_common.h"

char *g_level_prefix[LEVEL_GROUP];// = {0};// = {0};
char g_level[LEVEL_GROUP * SUB_GROUP] = {0};


int level_status()
{
	printf("               0   1   2   3   4   5   6   7\r\n");
	for (int r = 0; r < LEVEL_GROUP; r++) {
		if (NULL == g_level_prefix[r]) {
			printf("%d [%8s] : ", r, g_level_prefix[r]);
		} else {
			printf("%d [" C_RED BC_YELLOW  "%8s" C_NORMAL "] : ", r, g_level_prefix[r]);
		}

		for (int c = 0 ; c < SUB_GROUP; c++) {
			if (LEVEL_ID(r, c)) {
				printf(C_RED BC_YELLOW "%d   " C_NORMAL, LEVEL_ID(r, c));
			} else {
				printf("%d   ", LEVEL_ID(r, c));
			}
		}
		printf("\n");
	}
	return 0;
}

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