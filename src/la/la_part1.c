#include <autoconfig.h>
#include "proginfo.h"
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

void lafun1()
{
	printf("%s\n", CONFIG_LA_FUN1_STR);
}


PROG_INFO(project, PRJ_NAME);
PROG_VERSION( PRJ_VERSION "." PRJ_PATCHLEVEL "." PRJ_SUBLEVEL);
PROG_BUILD(BUILD_DATE);
PROG_AUTHOR("MenglongWu");
PROG_DESCRIPTION( "MakeDoxygen demo dynamic library liba.so part1");
#ifdef __cplusplus
}
#endif
