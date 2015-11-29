#include "stdio.h"
#include "math.h"

#include "la/liba.h"
#include "lb/libb.h"

// #ifdef __cplusplus
// extern "C" {

// #endif

int main()
{
	printf("Macro:\n"
		"\tPRJ_NAME      %s\n"
		"\tPRJ_VERSION   %s\n"
		"\tBUILD_DATE    %s\n",
		PRJ_NAME,PRJ_VERSION,BUILD_DATE);

	printf("asin(1) = %f\n", asin(1));

	lafun1();
	lafun2();
	lbfun1();
	lbfun2();
	lbfun2();
	lbfun1();
	lbfun1();
	lbfun1();
	lbfun2();
	lbfun2();
	lbfun1();
	lbfun1();
	return 0;
}
// #ifdef __cplusplus
// }
// #endif
