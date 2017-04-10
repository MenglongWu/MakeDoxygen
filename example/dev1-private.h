#ifndef _DEV1_PRIVATE_H_
#define _DEV1_PRIVATE_H_

#include <printl_common.h>
#include <printl.h>


#define print_m1(fmt, ... ) PRINTL(LEVEL_ID(1,0),fmt, ##__VA_ARGS__)
#define print_m2(fmt, ... ) PRINTL(LEVEL_ID(1,1),fmt, ##__VA_ARGS__)

#endif