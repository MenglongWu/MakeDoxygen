/**
 ******************************************************************************
 * @file	main.c
 * @brief	mheader/main.c

read config.mk analyse and make autoconfig.h, look like Linux Kernel
make menuconfig

- 2015-8-23, Menglong Woo,  MenglongWoo@163.com
 	- first version
- 2015-11-21, Menglong Woo,  MenglongWoo@aliyun.com
	- bugfix-2015-11-21-1


*/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

volatile int __wcmd_end3 __attribute__ ((section (".w_boot_end"))) = 0;
volatile char __str_ver[] __attribute__ ((section (".w_boot_end"))) = "ver 2.3";
volatile char __str_ff[] __attribute__ ((section (".w_boot_end"))) = "todo: -------------";
volatile char __str_mo[] __attribute__ ((section (".w_boot_end"))) = "what: -------------";
volatile char __str_data[] __attribute__ ((section (".w_boot_end"))) = "hello:-----------``";

static char str_in_file[256] = "config.mk";
static char str_out_file[256] = "autoconfig.h";
static char str_prj_name[256] = "<Input Project Name>";

static char stroption[64] = "";
static char strval[2048] = "";
static char strnull[64] = "                                                              ";
FILE *fp;

void part_configx(const char *str)
{	
	// 正则表达式分离配置信息字符串
	stroption[0] = '\0';
	strval[0]  = '\0';
	sscanf(str, "CONFIG_%[^= , +]",  stroption);
	sscanf(str, "%*[^=]= %[^@]",     strval);



	switch (strval[0]) {
	case 'y':
		strval[0] = '1';
		strval[1] = '\n';
		strval[2] = '\0';
		break;
	case 'n':
		strval[0] = '\0';
		break;
	default:
		break;
	}
	
}


void write_autoconfig()
{
	int ret;

	if (stroption[0] == '\0' || strval[0] == '\0' || fp == NULL) {
		return ;
	}

	ret = fprintf(fp, "#define CONFIG_%s ", stroption);
	
	fwrite(strnull, (size_t) 1, (size_t) ((64-ret) & 0x3f), fp);
	fprintf(fp, "%s", strval);
}


int read_rawconfig()
{
	FILE *fin = NULL;
	char *pret = (char*)1;
	char strinput[2048];

	// 读取打开配置文件
	fin = fopen( str_in_file, "r");
	if (NULL == fin) {
		printf("Error: can't open config file :%s.\nCheck path\n", str_in_file);
		return -1;
	}

	fprintf(fp,
		"/*\n"
		" * Automatically generated C config: don't edit\n"
		" * Project \"%s\" Configuration\n"
		" * Depand on %s\n"
		" */\n",
		str_prj_name,
		str_in_file);
	/*                                                                                                                              
	 * Automatically generated C config: don't edit
	 * Linux/arm 3.0.15Hello-KuGo Kernel Configuration
	 */
	fprintf(fp, 
		"#ifndef _AUTO_CONFIG_H_\n" 
		"#define _AUTO_CONFIG_H_\n\n");

	// 逐行读取配置信息
	strinput[0] = '\0';
	while(NULL != pret) {
		pret = fgets(strinput, 2048, fin);
		if (pret) {
			part_configx(strinput);
			write_autoconfig();	
		}
		
	}

	fprintf(fp, "\n#endif\n");
	fclose(fin);

	return 0;
}

void usage()
{
	printf(
		"Usage:\n"
		"\tmheader <config file> [header file] [project name]\n"
		"\tconfig file: input config file such as config.mk\n"
		"\theader file: default autoconfig.h\n"
		);
}
int main(int argc, char const *argv[])
{
	switch (argc) {
	case 4:
		snprintf(str_prj_name, 256, "%s", argv[3]);
	case 3:
		snprintf(str_out_file, 256, "%s", argv[2]);
	case 2:
		snprintf(str_in_file, 256, "%s", argv[1]);
		if (0 == strcmp(argv[1], "--help")) {
			goto _Help;
		}
		break;
	case 1:
	default:
_Help:;
		usage();
		return -1;
	}

	printf("read config file :%s\n", str_in_file);
	printf("make header file :%s\n", str_out_file);
	fp = fopen((const char*) str_out_file, (const char*) "wb");
	if (NULL == fp) {
		printf("Error: can't create header file :%s.\nCheck path\n", str_out_file);
		return -1;
	}
	read_rawconfig();
	fclose(fp);
	return 0;
}
