/**
 ******************************************************************************
 * @file	example/t-printl.c
 * @brief	可屏蔽打印

用于多人开发项目整合后多人的打印内容造成终端凌乱
工程结构
	t-printl.c 	子模块合并
	printl_common.c	打印级别控制

	dev1.c		开发者1 编写的所有
	dev1-private.h  开发者1 私有
	dev1.h		开发者1 对外

	dev2.c		开发者2 编写的所有
	dev2-private.h  开发者1 私有
	dev1.h		开发者1 对外



PRINTL
用于来屏蔽那些可以随时关闭的内容

如下打印内容不能屏蔽
PRINTT PRINTD PRINTW PRINTA PRINTE


如下表示使能 开发者2 的 模块1、模块2 的打印内容
               0   1   2   3   4   5   6   7
0 [  (null)] : 0   0   0   0   0   0   0   0
1 [    dev1] : 0   0   0   0   0   0   0   0
2 [    dev2] : 1   1   0   0   0   0   0   0
3 [  (null)] : 0   0   0   0   0   0   0   0
4 [  (null)] : 0   0   0   0   0   0   0   0
5 [  (null)] : 0   0   0   0   0   0   0   0

 *
 @section Platform
	-#
 @section Library
	-#
- 20xx-xx-xx,author,email
 	- brief

 * @attention
 *
 * ATTENTION
 *
 * <h2><center>&copy; COPYRIGHT </center></h2>
*/

#include <stdio.h>
#include <printl.h>

#include "dev1.h"
#include "dev2.h"

void Pause()
{
	printf("\nPress 'Enter' continue.");
	getchar();
}

int main(int argc, char **argv)
{
	printf("\nPrint effect for:\ndbg() dbgm() PRINTW() PRINTE() \n");
	printf("============================================\n");
	printf("\n\t1. ");
	dbg("dbg(\"\");\n");
	printf("\n\t2. ");
	dbgm(1, "dbgm(1, \"\");\n");
	printf("\n\t3. ");
	PRINTW("PRINTW(\"\");");
	printf("\n\t4. ");
	PRINTE("PRINTE(\"\");");



	printf("\nRename developer group\n");
	printf("============================================\n");
	printf("\nBefore rename:\n");
	level_status();
	pl_prefix(1, "dev1");
	pl_prefix(2, "dev2");
	printf("\nAfter rename:\n");
	level_status();
	Pause();



	printf("\nOnly enalbe developer 1 module 1 \n");
	printf("============================================\n");
	LEVEL_ID(1, 0) = 0, LEVEL_ID(1, 1) = 0, LEVEL_ID(2, 0) = 0, LEVEL_ID(2, 1) = 0;
	LEVEL_ID(1, 0) = 1;
	level_status();
	dev1_mod1();
	dev1_mod2();
	dev2_mod1();
	dev2_mod2();
	Pause();



	printf("\nOnly enalbe developer 1 module 2 \n");
	printf("============================================\n");
	LEVEL_ID(1, 0) = 0, LEVEL_ID(1, 1) = 0, LEVEL_ID(2, 0) = 0, LEVEL_ID(2, 1) = 0;
	LEVEL_ID(1, 1) = 1;
	level_status();
	dev1_mod1();
	dev1_mod2();
	dev2_mod1();
	dev2_mod2();
	Pause();



	printf("\nOnly enalbe developer 2 module 1 \n");
	printf("============================================\n");
	LEVEL_ID(1, 0) = 0, LEVEL_ID(1, 1) = 0, LEVEL_ID(2, 0) = 0, LEVEL_ID(2, 1) = 0;
	LEVEL_ID(2, 0) = 1;
	level_status();
	dev1_mod1();
	dev1_mod2();
	dev2_mod1();
	dev2_mod2();
	Pause();



	printf("\nOnly enalbe developer 2 module 2 \n");
	printf("============================================\n");
	LEVEL_ID(1, 0) = 0, LEVEL_ID(1, 1) = 0, LEVEL_ID(2, 0) = 0, LEVEL_ID(2, 1) = 0;
	LEVEL_ID(2, 1) = 1;
	level_status();
	dev1_mod1();
	dev1_mod2();
	dev2_mod1();
	dev2_mod2();
	Pause();





	printf("\nWhen condition can use PRINTW() and PRINTE()\n");
	printf("============================================\n");
	printf("string \"1234\" is digit?\n");
	printf("\t\t\t%s\n", dev1_is_digit("1234") ? "True" : "False");

	printf("string \"abcd\" is digit?\n");
	printf("\t\t\t%s\n", dev1_is_digit("abcd") ? "True" : "False");

	printf("1 / 2 = %f\n", dev1_div(1, 2));

	printf("1 / 0 = %f\n", dev1_div(1, 0));
	Pause();
	return 0;
}