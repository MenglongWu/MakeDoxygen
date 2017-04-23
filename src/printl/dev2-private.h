#ifndef _DEV2_PRIVATE_H_
#define _DEV2_PRIVATE_H_

#include <printl_common.h>
#include <printl.h>


#define print_m1(fmt, ... ) dbgm(LEVEL_ID(2,0),fmt, ##__VA_ARGS__)
#define print_m2(fmt, ... ) dbgm(LEVEL_ID(2,1),fmt, ##__VA_ARGS__)

#endif