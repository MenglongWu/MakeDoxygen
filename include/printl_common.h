#ifndef _PRINTL_COMMON_H_
#define _PRINTL_COMMON_H_

#ifndef CONFIG_LEVEL_GROUP
#   define LEVEL_GROUP 6
#else
#   define LEVEL_GROUP CONFIG_LEVEL_GROUP
#endif

#ifndef CONFIG_SUB_GROUP
#   define SUB_GROUP 8
#else
#   define SUB_GROUP CONFIG_SUB_GROUP
#endif



#include <stdbool.h>


extern char *g_level_prefix[LEVEL_GROUP];// = {0};
// extern char (*level_prefix)[LEVEL_GROUP];
extern char g_level[LEVEL_GROUP * SUB_GROUP];

void pl_prefix(unsigned int row, char *str);
void pl_enable(unsigned int row, unsigned int col, bool en);
int pl_getstatus(unsigned int row, unsigned int col);

// #define PL_TRACE	0
// #define PL_DBG 		1	
// #define PL_WARN		2
// #define PL_ERR		3
// #define PL_MODULE1	4
// #define PL_MODULE2	5
// #define PL_MODULE3	6
// #define PL_MODULE4	7


#endif