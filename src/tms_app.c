#include "protocol/tmsxx.h"
#include <string.h>
#include "ep_app.h"
#include "stdio.h"
#include "epollserver.h"
#include "tms_app.h"
#include "tmsxxdb.h"
// #include <strings.h>

#ifdef __cplusplus
extern "C" {
#endif

int g_en_connect_cu = 1;
extern struct tms_callback tcb;
int sg_en_save = 0;
char sg_file_path[256];
int sg_opm_auto = 0;
int sg_olp_auto = 0;
// char sg_retotdr[
// 	sizeof(struct tms_retotdr_test_hdr) +
// 	sizeof(struct tms_retotdr_test_param)+
// 	sizeof(struct tms_retotdr_data_hdr) +
// 	sizeof(struct tms_retotdr_data_val) * OTDR_SAMPLE_32000 +
// 	sizeof(struct tms_retotdr_event_hdr) +
// 	sizeof(struct tms_retotdr_event_val) * 1024 +
// 	sizeof(struct tms_retotdr_chain)] = {0};
#if 0
int unuse_copy2use(char *buf, int datalen, int msec, int fd)
{
	return 0;
	printf("\nunuse_copy2use()\t %d\n",datalen);
	uint32_t *pid;
	uint32_t *plen;

	if (datalen > 20) {
		datalen = 20;
	}
	for (int i = 0;i < datalen; i++) {
		printf("%2.2x ",buf[i]);
	}
	printf("\n");
	// pid = (uint32_t*)buf;
	// plen = (uint32_t*)(buf + sizeof(int32_t));
	// printf("\tcmdid[%8.8x] len[%d] datalen %d\n",*pid,*plen,datalen);
	return 0;	
}
#endif
int unuse_copy2use(char *buf, int datalen, int msec, void *ptr)
{
	struct tms_context *ptms = (struct tms_context *)ptr;
	struct glink_base *pgb = ptms->pgb;
	uint32_t *pid;
	uint32_t *plen;
	pid = (uint32_t*)buf;
	plen = (uint32_t*)(buf + sizeof(int32_t));

	printf("\nunuse_copy2use()\t %d\n",datalen);
	printf("\tcmdid[%8.8x] len[%d] datalen %d  src %x dst %x pkid %x\n", *pid,*plen,datalen,pgb->src, pgb->dst, pgb->pkid);
	return 0;
	printf("\nunuse_copy2use()\t %d\n",datalen);
	


	if (datalen > 20) {
		datalen = 20;
	}
	for (int i = 0;i < datalen; i++) {
		printf("%2.2x ",buf[i]);
	}
	printf("\n");
	// pid = (uint32_t*)buf;
	// plen = (uint32_t*)(buf + sizeof(int32_t));
	// printf("\tcmdid[%8.8x] len[%d] datalen %d\n",*pid,*plen,datalen);
	return 0;	
}

int32_t tms_OnGetDeviceComposition(struct tms_context *pcontext, int8_t *pdata, int32_t len)
{
	printf("OnGetDeviceComposition\n");
	struct tms_dev_composition_val devcom[16*12];

	int havedev;
	int frametotal = 0,slottotal = 0;
	int slot = 0;
	struct tms_devbase oneframe[12];

	int count = 0;

	for (int i = 0; i < 16; i++) {
		tms_GetFrame(i, &oneframe);
		for (int k = 0;k < 12;k++) {
			devcom[i*12+k].frame = oneframe[k].frame;
			devcom[i*12+k].slot  = oneframe[k].slot;
			devcom[i*12+k].type  = oneframe[k].type;
			devcom[i*12+k].port  = oneframe[k].port;
			count++;
		}
	}
	printf("count = %d\n",count);
	// tms_RetDeviceComposition(pcontext->fd, NULL, count,devcom);
	return 0;
}




struct tms_dev_composition_val sg_appdevcom[17][12] = {0};

// extern int DispFrame(struct tms_devbase *pframe,uint32_t flag);


int32_t tmsapp_GetFrame(int32_t frame, struct tms_devbase (*pdev)[12])
{
	if ((uint32_t)frame >= 16) {
		return 0;
	}
	// memcpy(&pdev[0][0],sg_devnet[frame],MAX_SLOT * sizeof(struct tms_devbase));

	for (int i = 0;i < 12;i++) {
		pdev[0][i].frame = sg_appdevcom[frame][i].frame;
		pdev[0][i].slot = sg_appdevcom[frame][i].slot;
		pdev[0][i].type = sg_appdevcom[frame][i].type;
		pdev[0][i].port = sg_appdevcom[frame][i].port;

	}


	return 0;
}

int32_t tms_OnSetIPAddress(uint8_t (*ip)[16], uint8_t (*mask)[16], uint8_t (*gw)[16])
{
	printf("ip  :%s\nmask:%s\ngate:%s\n",ip[0],mask[0],gw[0]);
	return 0;
}
int32_t tms_OnRetSerialNumber(uint8_t (*sn)[128])
{
	printf("tms_OnRetSerialNumber\n");
	printf("sn:   %s\n" ,sn[0]);

	return 0;
}
int32_t tms_OnCUNoteNet(void)
{
	return 0;
}

int32_t tms_OnCUNoteManageConnect(int32_t state)
{
	printf("\nstate %d\n", state);
	return 0;
}
void sh_analyse (char *fmt,long len);
int32_t tms_OnCommand(struct tms_context *pcontext, char *strcmd, int32_t slen)
{
	// printf("aasdf\n");
	sh_analyse(strcmd, slen);
	return 0;
}

int DispFrame(struct tms_devbase *pframe, uint32_t flag, struct trace_cache *ptc);
int32_t tms_OnRetDeviceComposition(struct tms_context *pcontext, int8_t *pdata, int32_t len,
			struct tms_dev_composition *pcfg_hr,
			struct tms_dev_composition_val *plist)
{
	printf("OnRetDeviceComposition\n");


	int havedev;
	int frametotal = 0,slottotal = 0;
	int slot = 0;
	struct tms_devbase oneframe[12];

	struct tms_dev_composition_val *ptlist;
	int frame;


	ptlist = plist;
	for (int i = 0;i < pcfg_hr->count; i++) {
		// 防止ptlist->frame溢出
		if ((uint32_t)ptlist->frame < 16 && (uint32_t)ptlist->slot < 12) {
			sg_appdevcom[ptlist->frame][ptlist->slot].frame = ptlist->frame ;
			sg_appdevcom[ptlist->frame][ptlist->slot].slot  = ptlist->slot  ;
			sg_appdevcom[ptlist->frame][ptlist->slot].type  = ptlist->type  ;
			sg_appdevcom[ptlist->frame][ptlist->slot].port  = ptlist->port  ;
		}
		ptlist++;
	}

	for (int i = 0; i < 16; i++) {

		havedev = 0;
		slot = 0;
		tmsapp_GetFrame(i, &oneframe);
		for (int k = 0;k < 12;k++) {
			if (oneframe[k].type != 0) {
				havedev = 1;
				slottotal++;
				slot++;
			}
		}
		if (havedev == 1) 
		{
			frametotal++;
			printf("\nFrame:%2.2d Slot count:%2.2d\n",i,slot);
			DispFrame(oneframe, 0, NULL);
		}
	}
	printf("                    Total Frame:%2.2d Total Slot:%2.2d\n",frametotal,slottotal);

	return 0;	
}
int32_t tms_OnAlarmLine(struct tms_context *pcontext,
			struct tms_alarm_line_hdr     *palarm,
			struct tms_retotdr_test_hdr   *ptest_hdr,
			struct tms_retotdr_test_param *ptest_param,
			struct tms_retotdr_data_hdr   *pdata_hdr,
			struct tms_retotdr_data_val   *pdata_val,
			struct tms_retotdr_event_hdr  *pevent_hdr,
			struct tms_retotdr_event_val  *pevent_val,
			struct tms_retotdr_chain      *pchain)
{
	printf("!!!!!!!!!!!!!!!!! Alarm line !!!!!!!!!!!!!!!!!\n");


	tms_SaveOTDRData(	ptest_hdr,
						ptest_param,
						pdata_hdr,
						pdata_val,
						pevent_hdr,
						pevent_val,
						pchain,
						(char*)"abc.txt",0);
	
	tms_Print_tms_retotdr_event(pevent_hdr, pevent_val);
	tms_Print_tms_retotdr_chain(pchain);
	tms_Print_tms_retotdr_test_hdr(ptest_hdr);
	tms_Print_tms_retotdr_test_param(ptest_param);
	return 0;
}


int tms_ReadySaveFile(char *path)
{
	sg_en_save = 1;
	snprintf(sg_file_path, 256, "%s",path);
	printf("will be save otdr date:%s\n",sg_file_path);
	return 0;
}

int tms_ReadOPMAuto()
{
	sg_opm_auto = 1;
	return 0;
}

int tms_ReadOLPAuto()
{
	sg_olp_auto = 1;
	return 0;
}

int32_t tms_OnRetOTDRTest(struct tms_context *pcontext,
			struct tms_retotdr_test_hdr   *ptest_hdr,
			struct tms_retotdr_test_param *ptest_param,
			struct tms_retotdr_data_hdr   *pdata_hdr,
			struct tms_retotdr_data_val   *pdata_val,
			struct tms_retotdr_event_hdr  *pevent_hdr,
			struct tms_retotdr_event_val  *pevent_val,
			struct tms_retotdr_chain      *pchain)
{
	if (sg_en_save) {
		tms_SaveOTDRBin(	ptest_hdr,
				ptest_param,
				pdata_hdr,
				pdata_val,
				pevent_hdr,
				pevent_val,
				pchain,
				(char*)sg_file_path);	
		sg_en_save = 0;
	}
	

	// tms_SaveOTDRData(	ptest_hdr,
	// 					ptest_param,
	// 					pdata_hdr,
	// 					pdata_val,
	// 					pevent_hdr,
	// 					pevent_val,
	// 					pchain,
	// 					(char*)"abc.txt",0);
	
	tms_Print_tms_retotdr_event(pevent_hdr, pevent_val);
	tms_Print_tms_retotdr_chain(pchain);
	tms_Print_tms_retotdr_test_hdr(ptest_hdr);
	tms_Print_tms_retotdr_test_param(ptest_param);


	// PrintfMemory((uint8_t*)ptest_hdr, sizeof(struct tms_retotdr_test_hdr));
	// PrintfMemory((uint8_t*)ptest_param, sizeof(struct tms_retotdr_test_param));
	// PrintfMemory((uint8_t*)pdata_hdr, sizeof(struct tms_retotdr_data_hdr));

	// struct tms_retotdr_test_hdr   *pptest_hdr;
	// struct tms_retotdr_test_param *pptest_param;
	// struct tms_retotdr_data_hdr   *ppdata_hdr;
	// struct tms_retotdr_data_val   *ppdata_val;
	// struct tms_retotdr_event_hdr  *ppevent_hdr;
	// struct tms_retotdr_event_val  *ppevent_val;
	// struct tms_retotdr_chain      *ppchain;
	// char *pbuf;

	// tms_OpenOTDRBin(	&pbuf,
	// 	// &pptest_hdr,
	// 	// &pptest_param,
	// 	// &ppdata_hdr,
	// 	// &ppdata_val,
	// 	// &ppevent_hdr,
	// 	// &ppevent_val,
	// 	// &ppchain,
	// 	(char*)"otdrbin.txt");

	// pptest_hdr   = (struct tms_retotdr_test_hdr   *)(pbuf  ); 
	// pptest_param = (struct tms_retotdr_test_param *)(((char*)pptest_hdr)   + sizeof(struct tms_retotdr_test_hdr)); 
	// ppdata_hdr   = (struct tms_retotdr_data_hdr   *)(((char*)pptest_param) + sizeof(struct tms_retotdr_test_param)); 
	// ppdata_val   = (struct tms_retotdr_data_val   *)(((char*)ppdata_hdr) + sizeof(struct tms_retotdr_data_hdr)); 
	// ppevent_hdr  = (struct tms_retotdr_event_hdr  *)(((char*)ppdata_val) + sizeof(struct tms_retotdr_data_val) * (pdata_hdr->count)); 
	// ppevent_val  = (struct tms_retotdr_event_val  *)(((char*)ppevent_hdr) + sizeof(struct tms_retotdr_event_hdr)); 
	// ppchain      = (struct tms_retotdr_chain      *)(((char*)ppevent_val) + sizeof(struct tms_retotdr_event_val) * (pevent_hdr->count));

	// PrintfMemory((uint8_t*)pptest_hdr, sizeof(struct tms_retotdr_test_hdr));
	// PrintfMemory((uint8_t*)pptest_param, sizeof(struct tms_retotdr_test_param));
	// PrintfMemory((uint8_t*)ppdata_hdr, sizeof(struct tms_retotdr_data_hdr));
	
	// printf("\n\n\n");

	
	// tms_Print_tms_retotdr_event(ppevent_hdr, ppevent_val);
	// tms_Print_tms_retotdr_chain(ppchain);
	// tms_Print_tms_retotdr_test_hdr(pptest_hdr);
	// tms_Print_tms_retotdr_test_param(ptest_param);
	// tms_Print_tms_retotdr_chain(ppchain);
	// tms_Print_tms_retotdr_test_hdr(pptest_hdr);
	// tms_Print_tms_retotdr_test_param(pptest_param);
	// 打印信息

	return 0;
}

int32_t tms_OnCfgOTDRRef(struct tms_context *pcontext,
			struct tms_retotdr_test_param *ptest_param,
			struct tms_retotdr_data_hdr   *pdata_hdr,
			struct tms_retotdr_data_val   *pdata_val,
			struct tms_retotdr_event_hdr  *pevent_hdr,
			struct tms_retotdr_event_val  *pevent_val,
			struct tms_retotdr_chain      *pchain,
			struct tms_cfg_otdr_ref_val   *pref_data)
{
	tms_Print_tms_retotdr_event(pevent_hdr, pevent_val);
	tms_Print_tms_retotdr_chain(pchain);
	tms_Print_tms_retotdr_test_param(ptest_param);
	tms_Print_tms_cfg_otdr_ref_val(pref_data);
	return 0;
}

// 调试用
int32_t tms_OnSpAnyGetOTDRTest(struct tms_context *pcontext, int8_t *pdata, int32_t len)
{
    struct tms_devbase oneframe[12];
    int fd;

    for (int i = 0; i < 16; i++) {
        tms_GetFrame(i, &oneframe);
        for (int k = 0; k < 12; k++) {
            if (oneframe[k].fd != 0 && oneframe[k].type == DEV_OTDR) {
                fd = oneframe[k].fd;
                goto _Find;
            }
		}
	}
	printf("OTDR unconnect\n");
	return -1;
_Find:;
	return glink_SendSerial(fd, (uint8_t*)pdata, len);
}

int32_t tms_OnSpSendSMS(struct tms_context *pcontext, int8_t *pdata, int32_t len)
{
	struct tms_devbase oneframe[12];
	int fd;

	for (int i = 0; i < 16; i++) {
		tms_GetFrame(i, &oneframe);
		for (int k = 0; k < 12; k++) {
			if (oneframe[k].fd != 0 && oneframe[k].type == DEV_SMS) {
				fd = oneframe[k].fd;
				goto _Find;
			}
		}
	}
	printf("SMS unconnect\n");
	return -1;
_Find:;
	return glink_SendSerial(fd, (uint8_t*)pdata, len);

}


int32_t tms_OnSpAck(struct tms_context *pcontext, int8_t *pdata, int32_t len)
{
	struct tms_ack *pval;
	int cmdid;
	pval = (struct tms_ack *)(pdata + GLINK_OFFSET_DATA);
	cmdid   = htonl(pval->cmdid);

	if (ID_GET_OTDR_TEST == cmdid) {
		tms_Transmit2Manager(pcontext, pdata, len);
	}
	return 0;
}

int32_t tms_OnRetDevType(struct tms_context *pcontext, struct tms_dev_port *pval)
{
	struct pro_list typelist[] = {
		{"Dev Undefine"}, 
		{"DEV_PWU"}, 
		{"DEV_MCU"}, 
		{"DEV_OPM"}, 
		{"DEV_OSW"}, 
		{"DEV_OTDR"}, 
		{"DEV_OLS"}, 
		{"DEV_OLP"}, 
		{"DEV_SMS"}, 
	};
	char strout[128];
	int ret;
	struct trace_cache tc;

	tc.strout = strout;
	tc.empty = 128;
	tc.offset = 0;
	tc.limit = 100;

	// printf("tms_AnalyseRetDevType\n");
	// ret = snprintf(tc.strout, tc.empty,
	// 	"", 
	// 	);
	// tc.offset += ret;

	if ((uint32_t)(pval->type) >= sizeof(typelist) / sizeof(struct pro_list)) {
		ret = snprintf(tc.strout + tc.offset, tc.empty - tc.offset,
			"fd %d val:f%d/s%x/t%x/%x\n\ttype code [%d] out of typelist!!!\n", 
			pcontext->fd, pval->frame, pval->slot, pval->type, pval->port,
			pval->type);
		tc.offset += ret;
	}
	else {
		ret = snprintf(tc.strout + tc.offset, tc.empty - tc.offset,
				"fd %d val:f%d/s%x/t%x/%x\n\ttype %s port %d\n", 
				pcontext->fd, pval->frame, pval->slot, pval->type, pval->port,
				typelist[pval->type].name, pval->port);
		tc.offset += ret;
	}
	
	printf("%s",tc.strout);
	tms_Trace(NULL, tc.strout, tc.offset + 1, LEVEL_TC);
	return 0;
}

int32_t tms_OnRetVersion(struct tms_context *pcontext, struct tms_dev_version *pval)
{
	char strout[128];
	int ret;
	struct trace_cache tc;

	tc.strout = strout;
	tc.empty = 128;
	tc.offset = 0;
	tc.limit = 100;
	ret = snprintf(tc.strout, tc.empty,
			"val:f%d/s%x/t%d\n\tversion:%s\n", 
			pval->frame, pval->slot, pval->type,pval->vsersion);
	tc.offset += ret;

	printf("%s",tc.strout);
	tms_Trace(NULL, tc.strout, tc.offset + 1, LEVEL_TC);
	return 0;
}

extern struct tms_cfg_opm_ref_val sg_opmref[8];
extern struct tms_cfg_opm_ref_val sg_opmref_def;
extern struct tms_cfg_olp_ref_val sg_olpref[6];
extern struct tms_cfg_olp_ref_val sg_olpref_def;
int32_t tms_OnRetAnyOP(struct tms_context *pcontext, struct tms_any_op *phdr, struct tms_any_op_val  *plist)
{
	int max;

	if (sg_opm_auto && phdr->type == DEV_OPM) {
		printf("auto input\n");
		max = phdr->count > 8 ? 8 : phdr->count;
		for (int i = 0; i < max; i++) {
			sg_opmref[i].port      = plist[i].port;
			sg_opmref[i].ref_power = plist[i].power;
			sg_opmref[i].leve0     = sg_opmref_def.leve0;
			sg_opmref[i].leve1     = sg_opmref_def.leve1;
			sg_opmref[i].leve2     = sg_opmref_def.leve2;
			if (plist[i].power < -600) {
				sg_opmref[i].isminitor = 0;
			}
		}
		sg_opm_auto = 0;
	}

	if (sg_olp_auto && phdr->type == DEV_OLP) {
		printf("auto input\n");
		max = phdr->count > 3 ? 3 : phdr->count;
		for (int i = 0; i < max; i++) {
			sg_olpref[i].port      = plist[i].port;
			sg_olpref[i].ref_power = plist[i].power;

			sg_olpref[i].leve0     = sg_olpref_def.leve0;
			sg_olpref[i].leve1     = sg_olpref_def.leve1;
			sg_olpref[i].leve2     = sg_olpref_def.leve2;
			if (plist[i].power < -600) {
				sg_olpref[i].isminitor = 0;
			}
		}
		sg_olp_auto = 0;
	}
	return 0;
}

int32_t tms_OnGetSerialNumber(struct tms_context *pcontext)
{
    return 0;
	tdb_sn_t input, mask;
	tdb_sn_t *ppout;
	int row;
	char strout[1024];
	int ret;
	bzero(&mask,  sizeof(tdb_common_t));

	
	// mask.sn[0] = 1;
	row = tmsdb_Select_sn(&input, &mask, &ppout);
	printf("row = %d\n",row);

	if (row == 0) {
		return 0;
	}
	for (int r = 0; r < row; r++) {
		// ID_TRACE 发送
		ret = snprintf(strout, 64,"sn reply %s",ppout[r].sn);
		// tms_Trace(NULL, strout, ret + 1, LEVEL_R_CMD);

		// TMSxx标准协议发送
		struct glink_addr gl;
		gl.src = GLINK_4412_ADDR;
		gl.dst = GLINK_MANAGE_ADDR;
        gl.pkid = pcontext->pgb->pkid;
		ret = snprintf(strout, 64,"%s",ppout[r].sn);
        tms_RetSerialNumber(tms_GetCUFd(), &gl, (uint8_t (*)[128])strout);
		printf("cu fd %d\n", tms_GetCUFd());
		break;
	}
	
	// 注意，用完后必须释放
	free(ppout);
	return 0;
}

extern int DispRoute_V2(struct tdb_route *prl, int count, struct trace_cache *ptc);
int32_t tms_OnInsertTbRoute(struct tms_context *pcontext,int count ,struct tms_route *plist)
{
	struct tdb_route route[MAX_ROUTE_NODE];

	if (count > MAX_ROUTE_NODE) {
		printf("out of range MAX_ROUTE_NODE\n");
		return -1;
	}

	for (int i = 0; i < count; i++) {
		route[i].frame_a	= plist->frame_a;
		route[i].slot_a	= plist->slot_a;
		route[i].type_a	= plist->type_a;
		route[i].port_a	= plist->port_a;
		route[i].frame_b	= plist->frame_b;
		route[i].slot_b	= plist->slot_b;
		route[i].type_b	= plist->type_b;
		route[i].port_b	= plist->port_b;
		plist++;
	}

	struct trace_cache tc;
	char strout[1024];

	tc.strout = strout;
	tc.empty = 1024;
	tc.offset = 0;
	tc.limit = 180;
	DispRoute_V2(route, count, &tc);
	printf("%s", tc.strout);

	// tmsdb_Insert_route(route,NULL,count);	
	return 0;
}

void tms_Callback(struct tms_callback *ptcb)
{
	bzero(ptcb, sizeof(struct tms_callback));
	
	ptcb->pf_OnCopy2Use             = unuse_copy2use;
	ptcb->pf_OnGetDeviceComposition = tms_OnGetDeviceComposition;
	ptcb->pf_OnRetDeviceComposition = tms_OnRetDeviceComposition;
	ptcb->pf_OnCommand              = tms_OnCommand;
	ptcb->pf_OnCUNoteNet            = tms_OnCUNoteNet;
	ptcb->pf_OnCUNoteManageConnect  = tms_OnCUNoteManageConnect;
	ptcb->pf_OnRetSerialNumber      = tms_OnRetSerialNumber;
	ptcb->pf_OnSetIPAddress         = tms_OnSetIPAddress;
	ptcb->pf_OnRetOTDRTest          = tms_OnRetOTDRTest;
	ptcb->pf_OnAlarmLine            = tms_OnAlarmLine;
	ptcb->pf_OnCfgOTDRRef           = tms_OnCfgOTDRRef;
	ptcb->pf_OnSpAnyGetOTDRTest     = tms_OnSpAnyGetOTDRTest;
	ptcb->pf_OnSpSendSMS            = tms_OnSpSendSMS;
	ptcb->pf_OnSpAck                = tms_OnSpAck;
	ptcb->pf_OnRetDevType           = tms_OnRetDevType;
	ptcb->pf_OnRetVersion           = tms_OnRetVersion;
	ptcb->pf_OnRetAnyOP             = tms_OnRetAnyOP;
	ptcb->pf_OnGetSerialNumber      = tms_OnGetSerialNumber;
	ptcb->pf_OnInsertTbRoute		= tms_OnInsertTbRoute;
#ifdef _MANAGE

	// 重定向tms_Analysexxx函数处理方式，如果不执行任何tms_SetDoWhat，则默认表示
	// 协议处于MCU工作方式，回调函数的dowhat设置为0表示不做任何转发，收到的数据一律
	// 传递给应用层
	// 1.作为网管和板卡来说都是传递给应用层
	// 2.作为CU和MCU就要仔细修改dowhat的处理方式
	int cmd_0xx000xxxx[100];

	bzero(cmd_0xx000xxxx, sizeof(cmd_0xx000xxxx) / sizeof(int));
	tms_SetDoWhat(0x10000000, sizeof(cmd_0xx000xxxx) / sizeof(int),cmd_0xx000xxxx);
	tms_SetDoWhat(0x60000000, sizeof(cmd_0xx000xxxx) / sizeof(int),cmd_0xx000xxxx);
	tms_SetDoWhat(0x80000000, sizeof(cmd_0xx000xxxx) / sizeof(int),cmd_0xx000xxxx);
#endif
	
}


void tms_SetCB(void *fun)
{
#if 0
	if (fun) {
		tcb.pf_OnCopy2Use =  (int32_t (*)(char *, int32_t , int, int))fun;
	}
#endif
	if (fun) {
		tcb.pf_OnCopy2Use =  (int32_t (*)(char *, int32_t , int, void*))fun;
	}
}


void *ThreadConnectCU(void *arg)
{
	struct tmsxx_app *ptmsapp;
	struct tms_context *pcontext;
	struct ep_t *pep = (struct ep_t*)arg;
	struct ep_con_t client;
	
	bzero(&client, sizeof(struct ep_con_t));
	// return 0;
#ifdef _MANAGE
	return 0;
#endif
	usleep(3000000);//延时3s，防止x86下efence奔溃
	while(1) {
		if (g_en_connect_cu == 1 && 0 == tms_ManageCount()) {
			if (0 == ep_Connect(pep,&client, "192.168.0.253", 6000) ) {
			// if (0 == ep_Connect(pep,&client, "192.168.1.251", 6000) ) {
		    	printf("connect CU success :  %s:%d\n", 
							inet_ntoa(client.loc_addr.sin_addr),
							htons(client.loc_addr.sin_port));

		    	// ptmsapp = (struct tmsxx_app*)client.ptr;
		    	// pcontext = &ptmsapp->context;
		    	// printf("pcontext %d\n", pcontext->fd);
		    	// pcontext = (struct tms_context*) ((struct tmsxx_app*)client.ptr->context);
		    	tms_AddManage(NULL,client.sockfd, 0);
		    	tms_SetCUFd(client.sockfd);
		    	sleep(5);
		    }
		    else {
		    	sleep(5);
		    	continue;
		    }
	    }
	    // if (g_en_connect_cu == 1 && 0 != tms_ManageCount()) {
	    if (g_en_connect_cu == 1 && 0 != client.sockfd) {
	    	struct tmsxx_app *ptapp = (struct tmsxx_app*)client.ptr;
			
			for (int i = 0;i < 10; i++) {
				tms_Tick(client.sockfd, NULL);
				sleep(3);

				if (ptapp->context.tick == 0) {
					if (i < 6) {
						printf("continue send TICK to cu %d\n",i);
						continue;
					}
					else {
						tms_SetCUFd(0);
						tms_DelManage(NULL,client.sockfd); // 解决bug
						ep_Close(pep, NULL, client.sockfd);
						client.sockfd = 0;
						break;
					}
				}
				else {
					break;
				}
			}
			ptapp->context.tick = 0;
	    }
	    sleep(5);
	}
    

}

#ifdef __cplusplus
}
#endif
