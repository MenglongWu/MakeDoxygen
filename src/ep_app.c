/**
 ******************************************************************************
 * @file	ep_app.c
 * @brief	MengLong Wu\n
 	TMSxxTC 项目epollserver回调处理


*/
#include "epollserver.h"
#include <stdio.h>
#include "bipbuffer.h"
#include "malloc.h"
#include <unistd.h>
#include "./protocol/glink.h"
#include "./protocol/tmsxx.h"

#include "minishell_core.h"
#include "stdlib.h"
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>

#include <time.h>
#include "tms_app.h"
#include "ep_app.h"
#include "tmsxxdb.h"

#ifdef __cplusplus
extern "C" {
#endif

struct tms_callback tcb;
struct epapp_callback epapp_cb;
// #define BIPBUFFER_LEN 2048
#define BIPBUFFER_LEN 30000
void ep_unuse(int fd)
{
	// printf("\nep_unuse()\n\tfd = %d\n",fd);
}


int InitSocketStruct(struct tmsxx_app **pss, int fd)
{

	*pss = (struct tmsxx_app*)malloc( sizeof(struct tmsxx_app));
	if (*pss == 0) {
		perror("malloc struct tmsxx_app");
		// exit(1);
		return -1;
	}
	bzero(*pss, sizeof(struct tmsxx_app));

	// ((struct tmsxx_app*)pnode->ptr)->context.fd = pnode->sockfd;
	(**pss).context.fd = fd;
	(**pss).context.ptcb = &tcb;


	bipbuffer_Init(&(*pss)->bb);
	//bipbuffer_AllocateBuffer(&(*pss)->bb,1024*2);
	bipbuffer_AllocateBuffer(&(*pss)->bb,BIPBUFFER_LEN);
	(*pss)->morebyte = 400;
	return 0;	
}

int FreeSocketStruct(struct tmsxx_app **pss)
{
	if(*pss == 0) {
		return 0;
	}
	
	bipbuffer_FreeBuffer(&(*pss)->bb);
	free(*pss);	
	
	*pss = NULL;	
	return 0;
}


#define PINF_FLAG_ACCEPT   0
#define PINF_FLAG_CONNECT  1
#define PINF_FLAG_REMOVE   2
#define PINF_FLAG_CLOSE    4

// void PrintConnectRemoveInf(int fd, int flag)
void PrintConnectRemoveInf(struct ep_con_t *pconNode, int flag)
{
	char strout[1024]= "\0";
	char retout;
	int offset = 0;
	int empty = 1024;

	// struct sockaddr_in locateAddr,remoteAddr;
	// socklen_t 		 len;
	time_t now;
	struct tm *timenow;
	// int ret;

	// int fd;
	// fd = pconNode->sockfd;

	// len = sizeof(struct sockaddr_in);
	// getsockname(fd, (struct sockaddr*)&locateAddr, &len);
	// len = sizeof(struct sockaddr_in);
	// ret = getpeername(fd, (struct sockaddr*)&remoteAddr, &len);
	// printf("ret = %d\n",ret);
	// perror("getpeername err:");


	time(&now);
	timenow = localtime(&now);   


	// printf("%-4d%8d%16s:%-8d",
	// printf("%8d%16s:%-8d",
	// 	pconNode->sockfd,
	// 	inet_ntoa(pconNode->loc_addr.sin_addr),
	// 	htons(pconNode->loc_addr.sin_port));
	retout = snprintf(strout + offset, empty - offset, "%8d%16s:%-8d",
		pconNode->sockfd,
		inet_ntoa(pconNode->loc_addr.sin_addr),
		htons(pconNode->loc_addr.sin_port));
	offset += retout;

	if (flag == PINF_FLAG_ACCEPT) {
		// printf("<----");
		retout = snprintf(strout + offset, empty - offset,"<----");
		offset += retout;
	}
	else if (flag == PINF_FLAG_CONNECT) {
		// printf("---->");
		retout = snprintf(strout + offset, empty - offset,"---->");
		offset += retout;
	}
	else if (flag == PINF_FLAG_REMOVE) {
		// printf("---xx");
		retout = snprintf(strout + offset, empty - offset,"---xx");
		offset += retout;
	}
	else {//PINF_FLAG_CLOSE
		// printf("xx---");
		retout = snprintf(strout + offset, empty - offset,"xx---");
		offset += retout;
	}
	// printf("%16s:%-8d",
	// 	inet_ntoa(remoteAddr.sin_addr),
	// 	htons(remoteAddr.sin_port));
	retout = snprintf(strout + offset, empty - offset,"%16s:%-8d",
		inet_ntoa(pconNode->rem_addr.sin_addr),
		htons(pconNode->rem_addr.sin_port));
	offset += retout;


	retout = snprintf(strout + offset, empty - offset,"%d-%d-%d %d:%d:%d\n", 
		timenow->tm_year+1900,timenow->tm_mon+1,timenow->tm_mday,
		timenow->tm_hour,timenow->tm_min,timenow->tm_sec);
	offset += retout;
	// todo 发送 strout,长度offset+1 或empty

	// fd = tms_GetManageFd();
	printf("%s", strout);
	tms_Trace(NULL, strout, offset + 1, ID_TRACE0);
}
int epFUI_OnAccept(struct ep_t *pep, struct ep_con_t *pnode)
{
	printf("----OnAccept----\n");
//	ep_KeepAlive(pep,pnode,3,30,4,1);
    ep_KeepAlive(pep,pnode,1,30,1,1);
	InitSocketStruct((struct tmsxx_app**)&pnode->ptr, pnode->sockfd);
	// ((struct tmsxx_app*)pnode->ptr)->fd = pnode->sockfd;
	// ((struct tmsxx_app*)pnode->ptr)->context.fd = pnode->sockfd;
	
	PrintConnectRemoveInf(pnode, PINF_FLAG_ACCEPT);
	// printf("%8d%16s:%-8d",
	// 	pnode->sockfd,
	// 	inet_ntoa(pnode->loc_addr.sin_addr),
	// 	htons(pnode->loc_addr.sin_port));
	// printf("%16s:%-8d\n",
	// 	inet_ntoa(pnode->rem_addr.sin_addr),
	// 	htons(pnode->rem_addr.sin_port));

	epapp_cb.pf_Accept(pnode->sockfd);
	// sleep(3);
	// tms_GetVersion(pnode->sockfd,  0, 0,DEV_OPM);
	// printf("send over\n");
	// sleep(3);

	return 0;
	
}

int epFUI_OnConnect(struct ep_t *pep, struct ep_con_t *pnode)
{
	printf("----OnConnect----\n");
	// printf("start\n")	;
	InitSocketStruct((struct tmsxx_app**)&pnode->ptr, pnode->sockfd);
	// ((struct tmsxx_app*)pnode->ptr)->fd = pnode->sockfd;
	((struct tmsxx_app*)pnode->ptr)->context.fd = pnode->sockfd;
	// printf("connect struct ok");
	PrintConnectRemoveInf(pnode, PINF_FLAG_CONNECT);

	return 0;

	
}

void PrintfMemory(uint8_t *buf,uint32_t len);;
int epFUI_OnRecv(struct ep_t *pep, struct ep_con_t *pnode)
{
	// static int rtimes = 0;
	// printf("\r--------!!!!!! OnRecv !!!!! --------%8.8x\r",rtimes++);
	int ret;
	// char rbuf[100];
	struct tmsxx_app *pss;


	

	int32_t retRecv,retFramelen,recvTotal;
	int32_t reserved;
	char *pdata;

	// printf("epFUI_OnRecv()\n");
	if (pnode->ptr == NULL) {
		printf("wait \n");
		sleep(1);
		return 1;
	}
	pss = (struct tmsxx_app *)pnode->ptr;
	//pss->morebyte = 100;
	if (pss->enable_lbb == 0) {
		pdata = bipbuffer_Reserve(&pss->bb,pss->morebyte,&reserved);	
	}
	else {
		printf("bipbuffer_Reserve lbb  ");
		pdata = bipbuffer_Reserve(&pss->lbb,pss->lbyte,&reserved);
		int size;
		bipbuffer_GetContiguousBlock(&pss->lbb,&size);
		printf("size %d\n",size);
	}

	// printf("1-1 ");
	// sleep(1);
	if (pdata == NULL) {
		retRecv = 1;//无用，必须大于0
		// printf("2-0 ");
	}
	// 固定环形缓存
	else if (pss->enable_lbb == 0) {
		// printf("want to recv %d\n",reserved);
		retRecv = recv(pnode->sockfd, pdata, reserved, 0);	
		// printf("recv count = %d\n", retRecv);
		// printf("2-1 %d ", retRecv);
		// printf("this times recv %d\n",retRecv);
		bipbuffer_Commit(&pss->bb,retRecv);
	}
	// 大型环形缓存，只够存储一帧数据，填满缓存前不找合法帧，
	// 填满后无论是否找到合法帧均释放
	else {
		retRecv = recv(pnode->sockfd, pdata, reserved, 0);	
		// printf("recv count = %d\n", retRecv);
		// printf("2-2 %d ", retRecv);
		bipbuffer_Commit(&pss->lbb,retRecv);
		pss->lbyte -= retRecv;


		if (pss->enable_lbb == 1 && pss->lbyte > 0) {
			// printf("end 2-3\n");
			return retRecv;
		}
		else {
			// printf("e-4 ");
			struct bipbuffer tbb;
			tbb      = pss->lbb;
			pss->lbb = pss->bb;
			pss->bb  = tbb;
		}
	}
	//bipbuffer_PrintMemory(&pss->bb);

_Again:;
	// printf("_Again:");
	pdata = bipbuffer_GetContiguousBlock(&pss->bb, &recvTotal);
	if (bipbuffer_GetUsedSize(&pss->bb) >= 40 && recvTotal < 40) {
		int unuse;
		// printf("a -1 ");
		bipbuffer_GetUnContiguousBlock(&pss->bb, &unuse);
	}
	if (recvTotal >= 40) {
		// printf("a -2 ");
		ret = glink_FindFrame((int8_t*)pdata, &recvTotal, &retFramelen);	
	}
	else {
		// printf("a -3 ");
		ret = -6;
		retFramelen = 0;
	}
	
	// printf("ret %d retRecv %d %recvTotal %d retFramelen %d\n",
	// 	ret,retRecv,recvTotal,retFramelen);
	if (ret == 0) {
		// printf("a -4 ");
		bipbuffer_DecommitBlock(&pss->bb, retFramelen);
		
		// tms_Analyse(pnode->sockfd, (int8_t*)pdata, retFramelen);
		tms_Analyse(    &(((struct tmsxx_app*)(pnode->ptr))->context), 
						(int8_t*)pdata, 
						retFramelen);

		pss->morebyte = 40;
		if (pss->enable_lbb == 0) {
			goto _Again;
		}
		//if (reserved > 0) {
			
		//}
	}
	else if (ret == -2) {
		// printf("a -5 ");
		// printf("frame err Decommit %d %d\n",retFramelen,reserved);
		bipbuffer_DecommitBlock(&pss->bb, retFramelen);
		

		pss->morebyte = 40;
		//if (reserved > 0) {
			goto _Again;
		//}
	}
	else if (ret == -3) {
		// printf("a -6 ");
		// printf("recvTotal %d retFramelen %d used %d\n",recvTotal,retFramelen,bipbuffer_GetUsedSize(&pss->bb));
		if (recvTotal + retFramelen <= bipbuffer_GetUsedSize(&pss->bb)) {
			int unuse;
			bipbuffer_GetUnContiguousBlock(&pss->bb, &unuse);
		}
		pss->morebyte = 40;//retFramelen;
		bipbuffer_GetContiguousBlock(&pss->bb, &reserved);
		// printf("after copy recvTotal %d reserved %d retFramelen %d\n",
		// 	recvTotal,reserved,retFramelen);
		bipbuffer_PrintMemory(&pss->bb);
		if (reserved >=  recvTotal + retFramelen) {
			// printf("a -7 ");
			goto _Again;
		}

		if (retFramelen + recvTotal > BIPBUFFER_LEN) {
			// printf("a -8 ");
			// 初始化大块临时缓存
			printf("large bipbuffer\n");
			char *pbb_buf,*plbb_buf;
			int pbb_len,plbb_unuselen;

			pss->lbyte = recvTotal + retFramelen;
			bipbuffer_Init(&pss->lbb);
			bipbuffer_AllocateBuffer(&pss->lbb,pss->lbyte);


			pbb_buf = bipbuffer_GetContiguousBlock(&pss->bb, &pbb_len);
			//plbb_buf = bipbuffer_GetContiguousBlock(&pss->lbb, &plbb_unuselen);
			plbb_buf = bipbuffer_Reserve(&pss->lbb, pbb_len, &plbb_unuselen);
			memcpy(plbb_buf, pbb_buf, pbb_len);

			bipbuffer_Commit(&pss->lbb, pbb_len);
			bipbuffer_DecommitBlock(&pss->bb, pbb_len);
			pss->lbyte -= pbb_len;
			pss->enable_lbb = 1;
		}
	

	}
	

	if (pss->enable_lbb == 1 && pss->lbyte <= 0) {
		// printf("a -9 ");
		printf("free....\n");
		struct bipbuffer tbb;

		pss->enable_lbb = 0;
		tbb      = pss->lbb;
		pss->lbb = pss->bb;
		pss->bb  = tbb;

		bipbuffer_FreeBuffer(&pss->lbb);
		
	}
	// printf("end \n");
	return retRecv;


	// ret = recv(pnode->sockfd, rbuf, sizeof(rbuf), 0);
	// // printf("recv data %s",rbuf);
	// // 返回值必须是recv函数的返回值
	// return ret;
}

int epFUI_OnError(struct ep_t *pep, struct ep_con_t *pnode)
{
	printf("----OnError----\n");
	perror("which Err:");
	// printf("errcode %d %s\n", errno, strerror(errno));
	// printf
	return 0;
}

int epFUI_OnRemoveClose(struct ep_t *pep, struct ep_con_t *pnode)
{
	// tms_DelManage(pnode->sockfd);
	tms_DelManage(&(((struct tmsxx_app*)(pnode->ptr))->context), 
		pnode->sockfd);
	printf("----OnRemoveClose----\n");
	// printf("close addr %8.8x\n",pnode->ptr);
	FreeSocketStruct((struct tmsxx_app**)&pnode->ptr);

	PrintConnectRemoveInf(pnode, PINF_FLAG_REMOVE);

	// printf("%8d%16s:%-8d",
	// 	pnode->sockfd,
	// 	inet_ntoa(pnode->loc_addr.sin_addr),
	// 	htons(pnode->loc_addr.sin_port));
	// printf("%16s:%-8d\n",
	// 	inet_ntoa(pnode->rem_addr.sin_addr),
	// 	htons(pnode->rem_addr.sin_port));
	
	tms_RemoveDev(pnode->sockfd);


	epapp_cb.pf_RemoteClose(pnode->sockfd);
	// tms_DelManage(pnode->sockfd);
	return 0;

}
int epFUI_OnClose(struct ep_t *pep, struct ep_con_t *pnode)
{
	// tms_DelManage(pnode->sockfd);
	tms_DelManage(&(((struct tmsxx_app*)(pnode->ptr))->context), 
		pnode->sockfd);
	PrintConnectRemoveInf(pnode, PINF_FLAG_CLOSE);
	tms_RemoveDev(pnode->sockfd);
	
	return 0;
}
int epFUI_OnRelease(struct ep_t *pep)
{
	return 0;
}

void ep_Callback(struct ep_t *pep)
{
	pep->pFUI_OnAccept      = epFUI_OnAccept;
	pep->pFUI_OnConnect     = epFUI_OnConnect;
	pep->pFUI_OnRecv        = epFUI_OnRecv;
	pep->pFUI_OnError       = epFUI_OnError;
	pep->pFUI_OnRemoveClose = epFUI_OnRemoveClose;
	pep->pFUI_OnRelease     = epFUI_OnRelease;
	pep->pFUI_Close         = epFUI_OnClose;


	epapp_cb.pf_Accept      = ep_unuse;
	epapp_cb.pf_RemoteClose = ep_unuse;
}


void SetEPAppCallback(struct epapp_callback *p)
{
	if (p == NULL) {
		return;
	}
	if (p->pf_Accept) {
		epapp_cb.pf_Accept = p->pf_Accept;
	}
	if (p->pf_RemoteClose) {
		epapp_cb.pf_RemoteClose = p->pf_RemoteClose;
	}
}


int ConnectCU(struct ep_t *pep)
{
	struct ep_con_t client;

	if (0 == ep_Connect(pep,&client, "127.0.0.1", 6500) ) {    
    }
    return 0;
}

/*
 *本系统至少有4个线程
 * main主线程
 *      |-----epollserver网络线程
 *      |-----自动连接CU线程，该线程每10S执行一次
 *      |-----minishell控制台线程
 *      |
 *      |......主线开放的其他线程
 */

static pthread_t g_pthreadshell,g_pthreadconnect_cu;
void *ThreadConnectCU(void *arg);


void *ThreadShell(void *arg)
{
    int ret = 1;

    ret = -1;
    while(ret == -1) {
		ret = sh_enter();
		if (ret == 0) {
			break;
		}
		sleep(4);
    }
    
    

    // 主线程应该调用它，shell线程不能自杀
	// pthread_cancel(g_pthreadshell);
	// pthread_join(g_pthreadshell,0);

	pthread_cancel(g_pthreadconnect_cu);
    pthread_join(g_pthreadconnect_cu,0);

	    
    exit(0);
}







#include <sys/time.h> 
#include <stdio.h> 
#include <math.h>

struct timeval tpstart,tpend; 
float timeuse; 


void ResetConst()
{
#ifdef WIN32
#else
	gettimeofday(&tpstart,NULL); 
#endif
}
void PrintCost()
{
#ifdef WIN32
#else
	gettimeofday(&tpend,NULL); 
	timeuse=1000000*(tpend.tv_sec-tpstart.tv_sec)+ 
	tpend.tv_usec-tpstart.tv_usec; 
	timeuse/=10000; 
	printf("Used Time:%f\n",timeuse);
#endif
}


#include <readline/readline.h>
#include <readline/history.h>
// #include "rlprivate.h"

extern struct cmd_prompt cmd_olpposlist[2];
extern char *rl_display_prompt ;
#define PROMPT_NODE(a,b,c,d) {(char*)(a), (char*)(b), (struct cmd_prompt	*)(c), (int)(d)}

struct cmd_prompt cmd_otdrosw_pos[] = 
{
	PROMPT_NODE("'param'","<osw frame/slot/port>",NULL,NULL),
	PROMPT_NODE(NULL,NULL, NULL,NULL),
};



struct cmd_prompt cmd_otdr_test_file[] = 
{
	PROMPT_NODE("'param'","<osw frame/slot/port>",NULL, CMDP_TYPE_PASS),
	PROMPT_NODE(NULL,NULL, NULL, NULL),
};
struct cmd_prompt cmd_otdr_test[] = 
{
	PROMPT_NODE("'filename'","open otdr file",cmd_otdr_test_file,CMDP_TYPE_PASS),
	PROMPT_NODE(NULL,NULL, NULL,NULL),
};

struct cmd_prompt cmd_otdr_go_file[] = 
{
	PROMPT_NODE("'param'","<osw frame/slot/port> [lv0 lv1 lv2]",NULL, CMDP_TYPE_PASS),
	PROMPT_NODE(NULL,NULL, NULL,NULL),
};
struct cmd_prompt cmd_otdr_go[] = 
{
	PROMPT_NODE("'filename'","open otdr file",cmd_otdr_go_file,CMDP_TYPE_PASS),
	PROMPT_NODE(NULL,NULL, NULL,NULL),
};


struct cmd_prompt cmd_otdr_list[] = 
{
	PROMPT_NODE("'filename'","open otdr file",NULL,CMDP_TYPE_PASS),
	PROMPT_NODE(NULL, NULL, NULL, NULL),
};
struct cmd_prompt cmd_otdrref[] = 
{
	PROMPT_NODE("test","otdr rollcall test",cmd_otdr_test, NULL),	
	PROMPT_NODE("go","configure otdr reference",cmd_otdr_go, NULL),	
	PROMPT_NODE("list","show file event",cmd_otdr_list, NULL),
	PROMPT_NODE(NULL, NULL, NULL, NULL),
};
struct cmd_prompt cmd_otdrlist[] = 
{
	PROMPT_NODE("test","otdr rollcall test",cmd_otdrosw_pos, NULL),	
	PROMPT_NODE("cyc","otdr cycle test",cmd_otdrosw_pos, NULL),	
	PROMPT_NODE("alarmtest","otdr alarm test",cmd_otdrosw_pos, NULL),
	PROMPT_NODE("ref","otdr alarm test",cmd_otdrref, NULL),
	PROMPT_NODE(NULL, NULL, NULL, NULL),
};
struct cmd_prompt cmd_alarmolp_list[] = 
{
	PROMPT_NODE("switch","command switch",NULL, NULL),
	PROMPT_NODE("manual","manual switch",NULL, NULL),
	PROMPT_NODE("auto","protect on auto",NULL, NULL),
	PROMPT_NODE("back","protect can back",NULL, NULL),
	PROMPT_NODE(NULL, NULL, NULL, NULL),
};

struct cmd_prompt cmd_alarmoccur_list[] = 
{
	PROMPT_NODE("occur","alarm occur",NULL, NULL),
	PROMPT_NODE(NULL, NULL, NULL, NULL),
};
struct cmd_prompt cmd_alarmlevel_list[] = 
{
	PROMPT_NODE("lv0","level higher",NULL, NULL),
	PROMPT_NODE("lv1","level middle",NULL, NULL),
	PROMPT_NODE("lv2","level lower",NULL, NULL),
	PROMPT_NODE(NULL, NULL, NULL, NULL),
};
struct cmd_prompt cmd_smsatlist[] = 
{
	PROMPT_NODE("line","alarm line break",cmd_alarmlevel_list, NULL),
	PROMPT_NODE("power","alarm power down",cmd_alarmlevel_list, NULL),
	PROMPT_NODE("hw","alarm hardware",cmd_alarmoccur_list, NULL),
	PROMPT_NODE("com","alarm communication",cmd_alarmoccur_list, NULL),
	PROMPT_NODE("olp","alarm olp",cmd_alarmolp_list, NULL),
	PROMPT_NODE(NULL, NULL, NULL, NULL),
};

struct cmd_prompt cmd_smsalarm_phone[] = 
{
	PROMPT_NODE("phone","phone number",cmd_smsatlist, CMDP_TYPE_PASS),
	PROMPT_NODE(NULL, NULL, NULL, NULL),
};

struct cmd_prompt cmd_smsalarm_duty[] = 
{
	PROMPT_NODE("mon","Monday ",cmd_smsalarm_phone, NULL),
	PROMPT_NODE("tues","Tuesday ",cmd_smsalarm_phone, NULL),
	PROMPT_NODE("wed","Wednesday ",cmd_smsalarm_phone, NULL),
	PROMPT_NODE("thur","Thursday ",cmd_smsalarm_phone, NULL),
	PROMPT_NODE("fri","Friday ",cmd_smsalarm_phone, NULL),
	PROMPT_NODE("sat","Saturday ",cmd_smsalarm_phone, NULL),
	PROMPT_NODE("sun","Sunday",cmd_smsalarm_phone, NULL),
	PROMPT_NODE(NULL, NULL, NULL, NULL),
};

struct cmd_prompt cmd_smsalarmindex[] = 
{
	PROMPT_NODE("'index<0~6>'","configure alarm SMS",cmd_smsalarm_duty,CMDP_TYPE_PASS),
	PROMPT_NODE("list","in local cache", NULL, NULL),
	PROMPT_NODE("go","download configure ", NULL, NULL),
	PROMPT_NODE("clear","clear configure ", NULL, NULL),
	PROMPT_NODE(NULL, NULL, NULL, NULL),
};
struct cmd_prompt cmd_smsalarm[] = 
{
	PROMPT_NODE("alarm","configure alarm SMS",cmd_smsalarmindex, NULL),
	PROMPT_NODE(NULL, NULL, NULL, NULL),
};
struct cmd_prompt cmd_cr[] = 
{
	PROMPT_NODE("","port <0~2>", NULL, NULL),
	PROMPT_NODE(NULL, NULL, NULL, NULL),
};
struct cmd_prompt cmd_olplist_ref[] = 
{
	PROMPT_NODE("port","port <0~2>", NULL, NULL),
	PROMPT_NODE("port1","port <0~2>", NULL, NULL),
	PROMPT_NODE("port2","port <0~2>", NULL, NULL),
	PROMPT_NODE(NULL, NULL, NULL, NULL),
};


struct cmd_prompt cmd_olplist_oplevel1[] = 
{
	PROMPT_NODE("oplevel1","opm 1", NULL, NULL),
	PROMPT_NODE("oplevel1","opm 1", NULL, NULL),
	PROMPT_NODE("oplevel1","opm 1", NULL, NULL),
	PROMPT_NODE("ref","reference", NULL, NULL),
	PROMPT_NODE(NULL, NULL, NULL, NULL),
};

struct cmd_prompt cmd_olplist_op[] = 
{
	PROMPT_NODE("opm1","opm 1", cmd_olplist_oplevel1, NULL),
	PROMPT_NODE("opm2","opm 2", cmd_olplist_oplevel1, NULL),
	PROMPT_NODE("op","opm 3", NULL, NULL),
	PROMPT_NODE("auto","opm 3", NULL, NULL),
	PROMPT_NODE("<cr>","Enter", NULL, NULL),
	PROMPT_NODE(NULL, NULL, NULL, NULL),
};

struct cmd_prompt cmd_updatelist[] = 
{
	PROMPT_NODE("com","", NULL, NULL),
	PROMPT_NODE(NULL, NULL, NULL, NULL),
};

struct cmd_prompt cmd_opmref_param_list[] = 
{
	PROMPT_NODE("'param'","<opm frame/slot>", NULL, NULL),
	PROMPT_NODE(NULL, NULL, NULL, NULL),
};
struct cmd_prompt cmd_opmreflist[] = 
{
	PROMPT_NODE("'param'","<port 0~7> <ref power> [lv0] [lv1] [lv2]", NULL, NULL),
	PROMPT_NODE("list","list all reference in local cache", NULL, NULL),
	PROMPT_NODE("go","configure opm ref power from local cache", cmd_opmref_param_list, NULL),
	PROMPT_NODE("auto","auto configure local cache", cmd_opmref_param_list, NULL),
	PROMPT_NODE("clear","clear opm ref power", cmd_opmref_param_list, NULL),
	PROMPT_NODE(NULL, NULL, NULL, NULL),
};



struct cmd_prompt cmd_gwlist[] = 
{
	PROMPT_NODE("x.x.x.x","gateway address", NULL, CMDP_TYPE_PASS),
	PROMPT_NODE(NULL, NULL, NULL, NULL),
};

struct cmd_prompt cmd_masklist[] = 
{
	PROMPT_NODE("x.x.x.x","Mask", cmd_gwlist, CMDP_TYPE_PASS),
	PROMPT_NODE(NULL, NULL, NULL, NULL),
};





// ##########################  tcconnect ##########################
struct cmd_prompt cmd_tconnect_ip_list[] = 
{
	PROMPT_NODE("port","Target port", 	NULL, CMDP_TYPE_PASS),
	PROMPT_NODE(NULL, NULL, NULL, NULL),
};

struct cmd_prompt cmd_tconnectlist[] = 
{
	PROMPT_NODE("ip","Target IP address", 	cmd_tconnect_ip_list, CMDP_TYPE_PASS),
	PROMPT_NODE(NULL, NULL, NULL, NULL),
};

// ########################## sip ##########################
struct cmd_prompt cmd_siplist[] = 
{
	PROMPT_NODE("x.x.x.x","ip address", cmd_masklist, CMDP_TYPE_PASS),
	PROMPT_NODE(NULL, NULL, NULL, NULL),
};

// ##########################  gver ##########################
struct cmd_prompt cmd_gver_dev_list[] = 
{
	PROMPT_NODE("'param'","<dev frame/slot>", 	NULL, NULL),
	PROMPT_NODE(NULL, NULL, NULL, NULL),
};
struct cmd_prompt cmd_gverlist[] = 
{
	PROMPT_NODE("this","get this soft's version", 	NULL, NULL),
	PROMPT_NODE("mcu","get mcu's version", 	NULL, NULL),
	PROMPT_NODE("dev","get dev's version", 	cmd_gver_dev_list, NULL),
	{(char*)NULL,(char*)NULL, (struct cmd_prompt	*)0, 0},
};


// ##########################  disp ##########################
struct cmd_prompt cmd_displist[] = 
{
	PROMPT_NODE("frame","display dev frame", NULL, NULL),
	PROMPT_NODE("connect","display dev connect", NULL, NULL),
	PROMPT_NODE("all","display frame and connect", NULL, NULL),
	PROMPT_NODE("clear","Clear device composition cache", NULL, NULL),
	PROMPT_NODE("update","Update device composition", NULL, NULL),
	PROMPT_NODE(NULL, NULL, NULL, NULL),
};



// ##########################  olp ##########################
struct cmd_prompt cmd_olpref_param_list[] = 
{
	PROMPT_NODE("'param'","<olp frame/slot>", NULL, NULL),
	PROMPT_NODE(NULL, NULL, NULL, NULL),
};

struct cmd_prompt cmd_olpref_edisable_list[] = 
{
	PROMPT_NODE("'port...'","<portx porty portz...>", NULL, NULL),
	PROMPT_NODE(NULL, NULL, NULL, NULL),
};
struct cmd_prompt cmd_olpreflist[] = 
{
	PROMPT_NODE("'param'","<port 0~2> <ref power> [lv0] [lv1] [lv2] edit local cache", NULL, NULL),
	PROMPT_NODE("list","list all reference in local cache", NULL, NULL),
	PROMPT_NODE("go","configure olp ref power from local cache", cmd_olpref_param_list, NULL),
	PROMPT_NODE("auto","auto configure local cache", cmd_olpref_param_list, NULL),
	PROMPT_NODE("clear","clear olp ref power", cmd_olpref_param_list, NULL),
	PROMPT_NODE("enable","edit local cache enable list index", cmd_olpref_edisable_list, NULL),
	PROMPT_NODE("disable","edit local cache disable list index", cmd_olpref_edisable_list, NULL),
	PROMPT_NODE(NULL, NULL, NULL, NULL),
};

struct cmd_prompt cmd_olp_unit_clear_list[] = 
{
	PROMPT_NODE("'param'","<olp frame/slot/port> ", NULL, NULL),
	PROMPT_NODE(NULL, NULL, NULL, NULL),
};

struct cmd_prompt cmd_opm_unit_list[] = 
{
	PROMPT_NODE("'param'","<opm frame/slot/port> <osw frame/slot/port>", NULL,NULL),
	PROMPT_NODE("clear","clear opm unit osw", cmd_olp_unit_clear_list, NULL),
	PROMPT_NODE(NULL, NULL, NULL, NULL),
};

// struct cmd_prompt cmd_opmreflist[] = 
// {
// 	{"'param'","<port 0~2> <ref power> [lv0] [lv1] [lv2]", NULL},
// 	{"list","list all reference in local cache", NULL},
// 	{"go","configure olp ref power from local cache", cmd_olpref_param_list},
// 	{"clear","clear olp ref power", cmd_olpref_param_list},
// PROMPT_NODE(NULL, NULL, NULL, NULL),
// };
extern struct cmd_prompt cmd_any_op_frame_list[2];
extern struct cmd_prompt cmd_any_op_list[2];

struct cmd_prompt cmd_opmlist[] = 
{
	PROMPT_NODE("alarm","alarm list", NULL, NULL),
	PROMPT_NODE("op","get power", cmd_any_op_list, NULL),
	PROMPT_NODE("ref","set reference level", cmd_opmreflist, NULL),
	PROMPT_NODE("unit","opm unit osw", cmd_opm_unit_list, NULL),
	PROMPT_NODE(NULL, NULL, NULL, NULL),
};
struct cmd_prompt cmd_olpunitlist[] = 
{
	PROMPT_NODE("'param'","<olp frame/slot/port> <osw frame/slot/port>", NULL, NULL),
	PROMPT_NODE("clear","clear olp unit osw", cmd_olp_unit_clear_list, NULL),
	PROMPT_NODE(NULL, NULL, NULL, NULL),
};




// ##########################  olp mode ##########################
struct cmd_prompt cmd_olp_mode_backornot[] = 
{
	PROMPT_NODE("unback","protect an unback !!!warning", NULL, NULL),
	PROMPT_NODE("back","protect an back", NULL, NULL),
	PROMPT_NODE(NULL, NULL, NULL, NULL),
};


struct cmd_prompt cmd_olp_mode_line[] = 
{
	PROMPT_NODE("A","switch to A line", cmd_olp_mode_backornot, NULL),
	PROMPT_NODE("B","switch to B line", cmd_olp_mode_backornot, NULL),
	PROMPT_NODE(NULL, NULL, NULL, NULL),
};

struct cmd_prompt cmd_olp_mode_slot[] = 
{
	PROMPT_NODE("slot","<olp slot>", cmd_olp_mode_line, CMDP_TYPE_PASS),
	PROMPT_NODE(NULL, NULL, NULL, NULL),
};

struct cmd_prompt cmd_olp_mode_frame[] = 
{
	PROMPT_NODE("frame","<olp frame>", cmd_olp_mode_slot, CMDP_TYPE_PASS),
	PROMPT_NODE(NULL, NULL, NULL, NULL),
};

// ##########################  olp sw ##########################
struct cmd_prompt cmd_olp_switch_line[] = 
{
	PROMPT_NODE("master","switch to master line", NULL,NULL),
	PROMPT_NODE("slave","switch to slave line", NULL,NULL),
	PROMPT_NODE(NULL, NULL, NULL, NULL),
};

struct cmd_prompt cmd_olp_switch_slot[] = 
{
	PROMPT_NODE("slot","<olp slot>", cmd_olp_switch_line, CMDP_TYPE_PASS),
	PROMPT_NODE(NULL, NULL, NULL, NULL),
};

struct cmd_prompt cmd_olp_switch_frame[] = 
{
	PROMPT_NODE("frame","<olp frame>", cmd_olp_switch_slot, CMDP_TYPE_PASS),
	PROMPT_NODE(NULL, NULL, NULL, NULL),
};
// ##########################  olp pos ##########################
struct cmd_prompt cmd_namelist[] = 
{
	PROMPT_NODE("'name'","the port connect station name", NULL, CMDP_TYPE_PASS),
	PROMPT_NODE(NULL, NULL, NULL, NULL),
};

struct cmd_prompt cmd_slotlist[] = 
{
	PROMPT_NODE("port<0~n>","olp port", cmd_namelist, CMDP_TYPE_PASS),
	PROMPT_NODE(NULL, NULL, NULL, NULL),
};

struct cmd_prompt cmd_framelist[] = 
{
	PROMPT_NODE("slot<0~12>","olp slot", cmd_slotlist, CMDP_TYPE_PASS),
	PROMPT_NODE(NULL, NULL, NULL, NULL),
};
struct cmd_prompt cmd_olpposlist[] = 
{
	PROMPT_NODE("frame<0~16>","olp frame", cmd_framelist, CMDP_TYPE_PASS),
	PROMPT_NODE(NULL, NULL, NULL, NULL),
};
struct cmd_prompt cmd_oswlist[] = 
{
	PROMPT_NODE("pos","configure olp position name", 	cmd_olpposlist, NULL),
	PROMPT_NODE(NULL, NULL, NULL, NULL),
};

// ##########################  olp op ##########################
struct cmd_prompt cmd_any_op_frame_list[] = 
{
	PROMPT_NODE("slot","olp/opm slot", 	NULL, CMDP_TYPE_PASS),
	PROMPT_NODE(NULL, NULL, NULL, NULL),
};

struct cmd_prompt cmd_any_op_list[] = 
{
	PROMPT_NODE("frame","olp/opm frame", 	cmd_any_op_frame_list, CMDP_TYPE_PASS),
	PROMPT_NODE(NULL, NULL, NULL, NULL),
};
struct cmd_prompt cmd_olplist[] = 
{
	PROMPT_NODE("alarm","alarm list", NULL,NULL),
	PROMPT_NODE("op","get power", cmd_any_op_list,NULL),
	PROMPT_NODE("ref","set reference level", cmd_olpreflist,NULL),
	PROMPT_NODE("pos","ip address", 	cmd_olpposlist, NULL),
	PROMPT_NODE("sw","switch to line,may not success", 	cmd_olp_switch_frame, NULL),
	PROMPT_NODE("unit","olp unit osw", cmd_olpunitlist,NULL),
	PROMPT_NODE("mode","configure olp mode", cmd_olp_mode_frame,NULL),
	PROMPT_NODE(NULL,NULL, NULL,NULL),
};

struct cmd_prompt cmd_boot[] = 
{
	PROMPT_NODE("tconnect","terminal connect", cmd_tconnectlist,NULL), 
	
	PROMPT_NODE("sip","Set device IP", cmd_siplist,NULL), 
	PROMPT_NODE("display","display something", cmd_displist,NULL),
	PROMPT_NODE("gver","get target version ", cmd_gverlist,NULL),

	PROMPT_NODE("olp","Specity OLP configuration", cmd_olplist,NULL), 
	PROMPT_NODE("opm","Specity OPM configuration", cmd_opmlist,NULL), 
	PROMPT_NODE("otdr","Specity OSW configuration", cmd_otdrlist,NULL),
	PROMPT_NODE("osw","Specity OSW configuration", cmd_oswlist,NULL), 
	PROMPT_NODE("sms","sms", cmd_smsalarm,NULL), 

	PROMPT_NODE("im","Announce manager", NULL,NULL), 
	
	PROMPT_NODE("enable","Enable/Disable something", NULL,NULL), 
	PROMPT_NODE("scan","Scan and update connect state", NULL,NULL), 
	PROMPT_NODE("r","Run shell on target", NULL,NULL), 



	PROMPT_NODE("sql","call sqlite3 console", NULL,NULL), 
	PROMPT_NODE("dbselect","Datebase select tmsxxdb", NULL,NULL), 
	PROMPT_NODE("dbdelete","Datebase delete tmsxxdb", NULL,NULL), 
	PROMPT_NODE("dbinsert","Datebase insert tmsxxdb", NULL,NULL), 

	PROMPT_NODE("interface","", NULL, NULL), 
	PROMPT_NODE("inf","shell help", NULL, NULL), 
	PROMPT_NODE("connect","shell help", NULL, NULL), 
	PROMPT_NODE("close","shell help", NULL, NULL), 
	
	
	

	PROMPT_NODE("update","Update target program", NULL, NULL), 
	
	
	PROMPT_NODE("lf","shell help", NULL, NULL), 
	
	
	
	PROMPT_NODE("sudo","shell help", NULL, NULL), 
	
	
	PROMPT_NODE(NULL, NULL, NULL, NULL),
};



struct cmd_prompt cmd_boot3[] = 
{
	PROMPT_NODE("sdfa","ddd",NULL,NULL),
	PROMPT_NODE(NULL,NULL,NULL,NULL),
};



void sh_analyse_ex (char *fmt,long len, char **cmd, int *count)
{
	// char *cmd[256],
	char *token = NULL;	
	int   index = 0;
	char  seps[] = " ,\t\n";

	//step 1:提取第一个单词，并在命令列表里寻找是否存在命令
	*(fmt+len) = '\0';
	token = strtok(fmt,seps);

	while(token != NULL) {
		cmd[index] = token;
		index++;
		token = strtok(NULL,seps);	
	}
	*count = index;
}
void sh_display_prompt(struct cmd_prompt *pprompt);

int
searchboot(
		int argc, 
		char **argv, 
		struct cmd_prompt *pprompt,
		struct cmd_prompt **plist)
{
	struct cmd_prompt *pstart;
	// struct cmd_prompt *boot;
	int find = 0;
	int index = 0;
	int len;

	// boot = pprompt;

	pstart = pprompt;
	for (index = 0; index < argc; index++) {
		find = 0;
		len = strlen(argv[index]);
		while ( pstart && pstart->name ) {
			if ( pstart->type == CMDP_TYPE_STR &&   
				0 == memcmp(argv[index], pstart->name, len) ) {
				find = 1;
				pstart = pstart->next;
				break;
			}
			if (pstart->type == CMDP_TYPE_PASS) {
				find = 1;
				pstart = pstart->next;
				break;
			}
			pstart++;
		}

		if (find == 0) {
			break;
		}	
	}

	
	// printf("\nindex %d argc %d list %x    ", index, argc, pstart);
	// 当index与argc相等表示完全匹配，
	// 当pstart不为NULL表示有下一层提示

	if (index == argc && pstart) {
		*plist = pstart;
		if (pstart->next == NULL) {
			return 0;
		}
		else {
			return 1;	
		}
	}
	if (index == argc ) {
		*plist = pstart;
		return 2;
	}

	// 当index 小于argc且pstart不为NULL表示前段部分匹配
	// if (pstart) {
	// 	printf("start name %s\n", pstart->name);
	// 	*plist = pstart;
	// 	printf("c\n");
	// 	return 0;
	// }
	*plist = NULL;
	return -1;
}

// #define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)

void sh_display_prompt(struct cmd_prompt *pprompt)
{
	// int i = 0;
	struct cmd_prompt *ptprompt;

	ptprompt = pprompt;
	while( ptprompt->name ) {
		printf("\t%-12s\t%s\n", ptprompt->name, ptprompt->help);
		ptprompt++;
	}
}
void sh_list(char *text, int len, struct cmd_prompt *boot)
{

}
int funtest2(int a, int b);
int funtest(int a, int b)
{
	printf ("a = %d b = %d\n", a, b);
	printf("%s", rl_display_prompt);
	rl_bind_key('?',funtest2);
	return 0;
}	

int funtest2(int a, int b)
{
	int len    = strlen(rl_line_buffer);
#ifdef MINISHELL_USE_MALLOC
	char *pbuf = (char*)malloc(len);
#else
	char buf[1024];
	char *pbuf = buf;
#endif
	char *cmd[256];
	int count;
	memcpy(pbuf, rl_line_buffer, len);

	sh_analyse_ex(pbuf, len, cmd, &count);
	
	struct cmd_prompt *plist;
	putchar('\n');
	int ret;
	ret = searchboot(count, cmd, cmd_boot, &plist);
	// printf("ret = %d\n", ret);
	if (ret == 0 || ret == 1) {
		// sh_display_prompt(plist);
		sh_display_prompt(plist);
	}
	else if (ret == 2){
		printf("\t<cr>        Enter \n");
	}
	// else if (ret == 0) {
	// else {

	// 	printf("\t<cr> Enter %x\n", plist);
	// }
	


#ifdef MINISHELL_USE_MALLOC
	free(pbuf);
#endif
	printf("%s%s", rl_prompt, rl_line_buffer);

	return 0;
}	

// 以字母顺序排序所有命令提示
void ShortAllCommandlist()
{
	sh_sort_ex(cmd_cr, sizeof(cmd_cr) / sizeof(struct cmd_prompt));
	sh_sort_ex(cmd_olplist_ref, sizeof(cmd_olplist_ref) / sizeof(struct cmd_prompt));
	sh_sort_ex(cmd_olplist_oplevel1, sizeof(cmd_olplist_oplevel1) / sizeof(struct cmd_prompt));
	sh_sort_ex(cmd_olplist_op, sizeof(cmd_olplist_op) / sizeof(struct cmd_prompt));
	sh_sort_ex(cmd_updatelist, sizeof(cmd_updatelist) / sizeof(struct cmd_prompt));
	sh_sort_ex(cmd_displist, sizeof(cmd_displist) / sizeof(struct cmd_prompt));
	sh_sort_ex(cmd_opmreflist, sizeof(cmd_opmreflist) / sizeof(struct cmd_prompt));
	sh_sort_ex(cmd_olpreflist, sizeof(cmd_olpreflist) / sizeof(struct cmd_prompt));
	sh_sort_ex(cmd_opmlist, sizeof(cmd_opmlist) / sizeof(struct cmd_prompt));
	sh_sort_ex(cmd_olplist, sizeof(cmd_olplist) / sizeof(struct cmd_prompt));
	sh_sort_ex(cmd_boot, sizeof(cmd_boot) / sizeof(struct cmd_prompt));
}
extern void cmd_InitTmsxxEnv();
int ThreadRunServerAndShell(struct ep_t *pep)
{
	ShortAllCommandlist();
	cmd_InitTmsxxEnv();
	tmsdb_Echo(1);       	// 关闭数据库回显
	tmsdb_CheckDb();		// 创建数据库
	rl_bind_key('?',funtest2);
	tms_Init();
	tms_Callback(&tcb);
	tms_UseEpollServer(pep);
    ep_Interface(pep, 2);           // 初始化ep接口
    ep_Callback(pep);               // 设在epollserver在本工程的回掉函数

#ifdef _MANAGE
    if(ep_Listen(pep,6000)) {     // 监听TCP 0.0.0.0:6500端口
        return 0;
    }
#else
	if(ep_Listen(pep,6500)) {     // 监听TCP 0.0.0.0:6500端口
        return 0;
    }
#endif
    
    ep_RunServer(pep);             // 运行epollserver线程
    
	
    pthread_create(&g_pthreadshell,NULL,ThreadShell,pep);
    pthread_create(&g_pthreadconnect_cu,NULL,ThreadConnectCU,pep);

    return 0;
}




#ifdef __cplusplus
}
#endif
