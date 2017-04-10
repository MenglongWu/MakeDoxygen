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


static int level_status()
{
	printf("               0   1   2   3   4   5   6   7\r\n");
	for (int r = 0; r < LEVEL_GROUP; r++) {
		printf("%d [%08s] : ", r, g_level_prefix[r]);
		for (int c = 0 ; c < SUB_GROUP; c++) {
			if (LEVEL_ID(r, c)) {
				printf(C_YELLOW "%d   " C_NORMAL, LEVEL_ID(r, c));
			} else {
				printf("%d   ", LEVEL_ID(r, c));
			}
		}
		printf("\n");
	}
	return 0;
}
int main(int argc, char **argv)
{
	// 演示各种打印级别
	LEVEL_ID(0, 0) = 1;
	PRINTL(LEVEL_ID(0, 0), "PRINTL_I\r\n");
	LEVEL_ID(0, 0) = 0;

	PRINTT("PRINTL_T");
	PRINTD("PRINTL_D");
	PRINTW("PRINTL_W");
	PRINTA("PRINTL_A");
	PRINTE("PRINTL_E");

	// 命名
	pl_prefix(1, "dev1");
	pl_prefix(2, "dev2");
	level_status();




	// TODO 载入配置文件
	int select = 0;

	printf("select which device information will display (1/2) ? ");
	scanf("%d", &select);
	switch(select) {
	case 1:
		// 只打开研发员1的打印
		LEVEL_ID(1, 0) = 1; // 打印 dev1_mod1 的输出内容
		LEVEL_ID(1, 1) = 1;
		break;
	case 2:
		LEVEL_ID(2, 0) = 1;
		LEVEL_ID(2, 1) = 1;
		break;
	default:
		break;
	}
	level_status();



	// 研发员1 开发的项目模块
	printf("------------------------\n");
	dev1_mod1();
	dev1_mod2();

	// 研发员2 开发的项目模块
	printf("\n------------------------\n");
	dev2_mod1();
	dev2_mod2();

	return 0;
}