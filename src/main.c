/**
 ******************************************************************************
 * @file	main.c
 * @brief	TMSxxTC 主程序
 *			
*/
/*--------------------------------------------------
 * version    |    author    |    date    |    content
 * V1.0			Menglong Wu		2015-1-5	
 ******************************************************************************
*/

#include "ar.h"
#include "stdio.h"
#include "string.h"
#include <errno.h>

#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>

#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "minishell_core.h"

#include "ossocket.h"





volatile int __wcmd_end2   __attribute__ ((section (".w_boot_end"))) = 0;

// void server()
// {
// 	int listenfd;
// 	int clientfd;
// 	short port = 6000;
// 	struct sockaddr_in listen_addr;
// 	struct sockaddr_in client_addr;
// 	socklen_t len;
// 	int ret;
// 	char rbuf[100];

// 	listenfd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	


// 	listen_addr.sin_family = AF_INET;     // Address family
// 	listen_addr.sin_port = htons (port);
// 	listen_addr.sin_addr.s_addr = inet_addr("192.168.1.252");

// 	ret = bind(listenfd,(struct sockaddr*)&listen_addr, sizeof(struct sockaddr_in));
// 	printf("ret %d bind %d %s\n",ret,os_error(),strerror(errno));


// 	listen(listenfd,5);
// 	//printf("listen %s\n", strerror(errno)); 
// 	len = sizeof(struct sockaddr_in);
// 	clientfd = accept(listenfd,(struct sockaddr*)&client_addr,&len);
// 	//printf("accept %s\n", strerror(errno)); 
// 	while(1) {
// 		ret = recv(clientfd,rbuf,10,0);
// 		printf("recv return\n");
// 		if(ret != -1) 
// 		{
// 			rbuf[ret] = '\0';
// 			printf("%s\n",rbuf);
// 		}
// 		//sleep(1);

// 	}


// }

// void client()
// {
// 	int clientfd;
// 	struct sockaddr_in client_addr;



// 	clientfd = socket(AF_INET,SOCK_STREAM,0);
// 	printf("socket %s\n", strerror(errno));
// 	bzero(&client_addr, sizeof(client_addr));
// 	client_addr.sin_family 		= AF_INET;
// 	client_addr.sin_port 		= htons (6000);
// 	client_addr.sin_addr.s_addr = inet_addr("192.168.1.52");
// 	printf("client %x\n",client_addr.sin_addr.s_addr );

// 	int ret = connect(clientfd,(struct sockaddr*)&client_addr,sizeof(struct sockaddr));
// 	printf("ret = %d\n",ret);
// 	printf("%s\n", strerror(errno));  
// 	while(1) {
// 		sleep(1);
		
// 	}

// }



#include "epollserver.h"
#include "pthread.h"
#include "malloc.h"
#include "ossocket.h"

#include "ep_app.h"
#include "tms_app.h"
#include "protocol/tmsxx.h"
#include <readline/readline.h>
#include <readline/history.h>

void TestList(struct ep_t *ep)
{

	// struct ep_node_t *node1,*node2,*node3,*pnode;
	// struct list_head *pos,*n;
	// //ep_Interface(&ep, 2);
	// node1 = (struct ep_node_t *)malloc(sizeof(struct ep_node_t));
	// node2 = (struct ep_node_t *)malloc(sizeof(struct ep_node_t));
	// node3 = (struct ep_node_t *)malloc(sizeof(struct ep_node_t));

	// // node1->fd = 1;
	// // node2->fd = 2;
	// // node3->fd = 3;

	// ep_AddClient(ep,node1);
	// ep_AddClient(ep,node2);
	
	// ep_AddClient(ep,node3);
	// printf("node bef cnt %d\n",ep->node_cnt);
	// ep_DelClient(ep,node2);

	
	// list_for_each_safe(pos, n, &ep->node_head) {
	// 	pnode = (struct ep_node_t*)list_entry(pos,struct ep_node_t,list);
	// 	printf("node %d\n",pnode->fd);
	// }
	
	// printf("node aft cnt %d\n",ep->node_cnt);

	

}

#include "signal.h"

void sig_handle(int sig)
{
	printf("\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
	printf("             capture SIG_xxxx %d\n",sig);
	printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
	perror("what:");
}

void sig_int(int sig)
{
	printf("!!!!!!!!!!!!!!!!!!!!!!!capture SIGINT %d\n",sig);
	perror("what:");
}

struct ep_t ep;
extern struct tms_callback tcb;
extern void ep_Callback(struct ep_t *pep);

/*
-------------------------------------------------------------------------------------------------
|   struct unknow1   |<- struct_A -> | <- struct_B->|<- struct_B->|<- struct_B->|   struct unknow2|
-------------------------------------------------------------------------------------------------
                     ^ptrA           |              B_count                                       ^ptrEnd

*/

#define CHECK_PTR(ptrA, struct_A, struct_B, B_Count, PtrEnd) 	\
 				( ((uint8_t*)(ptrA)) + sizeof(struct_A) + \
				   sizeof(struct_B) * (int32_t)(B_Count-1) <= ((uint8_t*)(PtrEnd)-sizeof(struct_B)) )
#define CHECK_PTRH(ptrA,struct_A,struct_B,B_Count) 	\
 				( ((uint8_t*)(ptrA)) + sizeof(struct_A) + \
				   sizeof(struct_B) * (int32_t)(B_Count-1)  \
				)
#define CHECK_PTRT(struct_B,PtrEnd) 	\
 				((uint8_t*)(PtrEnd)-sizeof(struct_B)) 

#include "locale.h"
#include <stdio.h>
#include <wchar.h>		
#include <stdlib.h>	
#include <iconv.h>
//代码转换:从一种编码转为另一种编码
int code_convert(char *from_charset,char *to_charset,char *inbuf,int inlen,char *outbuf,int outlen)
{
	iconv_t cd;
	int rc;
	char **pin = &inbuf;
	char **pout = &outbuf;

	cd = iconv_open(to_charset,from_charset);
	if (cd==0) return -1;

	memset(outbuf,0,outlen);
	if (iconv(cd,pin,(size_t*)&inlen,pout,(size_t*)(outlen))==-1) return -1;
	// iconv(iconv_t __cd, char **__inbuf, size_t *__inbytesleft, char **__outbuf, size_t *__outbytesleft)
	iconv_close(cd);
	return 0;
}
//UNICODE码转为GB2312码
int u2g(char *inbuf,int inlen,char *outbuf,int outlen)
{
	return code_convert("utf-8","gb2312",inbuf,inlen,outbuf,outlen);
}
//GB2312码转为UNICODE码
int g2u(char *inbuf,size_t inlen,char *outbuf,size_t outlen)
{
	return code_convert("gb2312","utf-8",inbuf,inlen,outbuf,outlen);
}
#define OUTLEN 600
void fun3()
{
	char in_utf8[100] = "姝ｅ?ㄥ??瑁?";
	char in_gb2312[100] = "正在安装";
	char out[OUTLEN] = {0};
	int rc;
	char **pin = (char**)&in_utf8;
	char **pout= (char**)&out;
	size_t inlen = 100, outlen = OUTLEN;

	iconv_t cd;
	//unicode码转为gb2312码
	// rc = u2g(in_utf8,strlen(in_utf8)/2,out,OUTLEN);
	rc = code_convert("gb2312","utf-8",in_utf8,strlen(in_utf8),out,OUTLEN);
	// cd = iconv_open("gb2312","utf-8");
	// iconv(cd, pin, &inlen, pout, &outlen);
	// iconv_close(cd);
	printf("unicode-->gb2312 out=%sn",out);
	//gb2312码转为unicode码
	// rc = g2u(in_gb2312,strlen(in_gb2312),out,OUTLEN);
	// printf("gb2312-->unicode out=%sn",out);
}



void fun()
{
	// setlocale(LC_ALL,"chs"); 
	setlocale(LC_ALL,"zh_CN.utf-8");
	wchar_t wstr[30] = L"中国abcd";
	char cstr[30] = "中国";
	wchar_t wcstr[90]= {0};
	char strinput[90]= {0};

	printf("wchar_t:\n");
	PrintfMemory((uint8_t*)wstr,30);
	printf("char:\n");
	PrintfMemory((uint8_t*)cstr,30);

	// wscanf(L"%s",wcstr);
	// printf("wchar:\n");
	// PrintfMemory((uint8_t*)wcstr,30);	
	
	// scanf("%s", strinput);
	// printf("char:\n");
	// PrintfMemory((uint8_t*)strinput,30);	


	// printf((char*)L"str %s\n",str);
	// printf("cstr %s\n",cstr);
	// wprintf(L"cstr %s\n\n",wstr);
	// wsprintf wcstr
	size_t len, ls;


	// setlocale(LC_ALL,"zh_CN");
	
	len = mbstowcs(wcstr, cstr, 90);
	perror("wcstombs ");

	printf("conv:\n");
	PrintfMemory((uint8_t*)wcstr,30);	
	return ;
	setlocale(LC_ALL,"POSIX");
	
	len = mbstowcs(wcstr, cstr, 90);
	perror("wcstombs ");

	setlocale(LC_ALL,"C");
	
	len = mbstowcs(wcstr, cstr, 90);
	perror("wcstombs ");

	setlocale(LC_ALL,"en_AG.utf8");
	
	len = mbstowcs(wcstr, cstr, 90);
	perror("wcstombs ");

	setlocale(LC_ALL,"zh_HK.gb2312");
	
	len = mbstowcs(wcstr, cstr, 90);
	perror("wcstombs ");

	setlocale(LC_ALL,"zh_HK.utf8");
	
	len = mbstowcs(wcstr, cstr, 90);
	perror("wcstombs ");

	setlocale(LC_ALL,"zh_HK.utf8");
	
	len = mbstowcs(wcstr, cstr, 90);
	perror("wcstombs ");

	setlocale(LC_ALL,"zh_HK.utf8");
	
	len = mbstowcs(wcstr, cstr, 90);
	perror("wcstombs ");

	setlocale(LC_ALL,"zh_HK.utf8");
	ls = mbstowcs(NULL,cstr,0)+1;
	len = mbstowcs(wcstr, cstr, 90);




	printf("len = %d %d\n", len,ls);
	perror("wcstombs ");
	
	len = wcslen(wcstr);
	printf("len = %d %d\n", len,ls);
	PrintfMemory((uint8_t*)wcstr,60);	
	
}

int fun2()
{
	setlocale(LC_ALL,"zh_CN.GB18030");
    wchar_t wcstr[50] = L"字符测试123abc";

    for (int i = 0; i < 50; i++) {
    	printf("%4.4x\n ",wcstr[i]);
    }
    int len = wcslen(wcstr)+1;
    printf("len = %d \n",len);
    for(int i = 0; i < len; i++)
        printf("0x%08x ",wcstr[i]);
    printf("\n");

    char str[55] = {0};    
    int n = wcstombs(str,wcstr,55);
    if(-1 == n)
    {
    perror("wcstombs ");
    exit(-1);
    }    
    printf("n = %d\n",n);
    for(int i = 0; i < n+1; i++)
        printf("0x%08x ",str[i]);
    printf("\n");    
    wchar_t wch[50]={0};
    int m = mbstowcs(wch,str,n);    
    if(m == -1)
    {
    perror("Converting");
    exit(-1);
    }
    printf("m = %d\n",m);
    for(int i =0; i<m+1;i++)
    printf("0x%08x ",wch[i]);
    printf("\n");
    return 0;



}
#include <netdb.h> 
// #include <sockets.h>
#include <stdio.h>


#define SERVER_NAME     "api.yeelink.net"  //服务器域名地址

#ifndef PRJ_VERSION
#define PRJ_VERSION "unknow"
#endif
#ifndef PRJ_NAME
#define PRJ_NAME "unknow"
#endif

void dns()
{



	struct hostent *host;
	struct in_addr addr;
	//DNS地址解析   
	host = gethostbyname(SERVER_NAME);
	addr.s_addr = *(unsigned long *)host->h_addr;
	printf("Server IP Address:%s\r\n" , inet_ntoa(addr));  
}

int main(int argc, char const *argv[])
{	
	printf("%s  %s %s\n",BUILD_DATE,PRJ_NAME, PRJ_VERSION);
	// dns();
	// setlocale(LC_ALL,"zh_CN.utf-8");
	// char str[100];
	// int len;
	// scanf("%s",str);
	// len = strlen(str);

	// PrintfMemory( (uint8_t*)str, 30);
	// len = wcslen((wchar_t*)str);
	// printf("len   %d\n", len);
	// fun2();
	// fun();
	// fun3();
	signal(SIGINT, sig_handle);
	signal(SIGPIPE, sig_handle);
	// signal(SIGSEGV, sig_handle);

	signal(SIGHUP, sig_handle);

	signal(SIGALRM, sig_handle);
	signal(SIGILL, sig_handle);
	signal(SIGABRT, sig_handle);
	// signal(SIGSEGV, sig_handle);
	
	// return 0;
	ThreadRunServerAndShell(&ep);
	while(1) {
		sleep(2);
	}

	tms_Init();
	tms_Callback(&tcb);

	// 创建epoll server对象，版本号目前随意
	ep_Interface(&ep, 2);


	// 定义回调函数，各种回调函数在ep_app.c里定义
	ep_Callback(&ep);
	
	// signal(SIGINT, sig_handler);
	// 开放监听端口，需要关闭套接字调用ep_StopServer
	// 如果不做服务器可以去除ep_Listen

#ifdef TARGET_ARMV7
	if(ep_Listen(&ep,6500)) {
		return 0;
	}
#else
	if(ep_Listen(&ep,6500)) {
		return 0;
	}
#endif
	


	// 创建若干后台线程运行epoll server服务，管理所有套接字，
	// 包括新连接的建立、接收数据，函数回调
	// ep_CreateThread(&ep,0);
	ep_RunServer(&ep);
	// sleep(1);
	// ep_StopServer(&ep);


	// if(ep_Listen(&ep,6000)) {
	// 	return 0;
	// }
	// ep_RunServer(&ep);
	//ep_Listen(&ep,6000);


	// 跳转到控制台接受用户命令，QT用GUI代替控制台
	while(1) {
		
		sh_enter();	

		sleep(1);
		printf("again\n");
	}
	

	
	// 停止服务
	ep_StopServer(&ep);


	// 释放epoll server对象，与ep_Interface相对应
	ep_Release(&ep);

	
	return 0;
}

volatile int __soft_version_1_2_3  __attribute__ ((section (".soft"))) = 0;