#include "stdio.h"
#include "math.h"

int main()
{
	printf("Macro:\n"
		"\tPRJ_NAME      %s\n"
		"\tPRJ_VERSION   %s\n"
		"\tBUILD_DATE    %s\n",
		PRJ_NAME,PRJ_VERSION,BUILD_DATE);

	printf("sin(pi/2) = %f\n", sin(M_PI/2));
	return 0;
}