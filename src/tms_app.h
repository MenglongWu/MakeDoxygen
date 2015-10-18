#ifndef _TMS_APP_H_
#define _TMS_APP_H_

#ifdef __cplusplus
extern "C" {
#endif



//目标程序名
#ifdef _MANAGE
#define TARGET_NAME     "TMSxxTC Manager"
#else
#define TARGET_NAME     "TMSxxTC MCU"
#endif


#define THIS_VERSION	"	V1.0.0-Bate"    		     //目标板名称
#define RELEASE_DATE	"Release Date	2015-06-29"	 //修改发布时间

// 在 makefile 里编写自动生成 BUILD_DATE脚本
#ifndef BUILD_DATE 
#define BUILD_DATE "unknow"
#endif



/**
 * @brief	跟踪输出缓存
 
 只有 offset < limit 时才能对缓存添加内容，填充函数必须保证每次填充的长度不得大于
 empty - limit，
 */

struct trace_cache
{
	char *strout;	///< 输出执法车
	int offset;		///< 输出字符串偏移
	int empty;		///< 最大空余
	int limit;		///< 填充极限
};


void tms_SetCB(void *fun);
void tms_Callback(struct tms_callback *ptcb);


int tms_ReadySaveFile(char *path);
int tms_ReadOPMAuto();
int tms_ReadOLPAuto();
#ifdef __cplusplus
}
#endif

#endif