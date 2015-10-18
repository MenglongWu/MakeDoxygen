/**
 ******************************************************************************
 * @file	tmsxxdb.h
 * @brief	TMSxxTC 项目的数据库接口


*/

#ifndef _TMSXX_DB_H_
#define _TMSXX_DB_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <protocol/tmsxx.h>


#define DB_UNUSE    0   ///< unuse
#define DB_EQ       1	///< col=n
#define DB_MORE     2	///< col>n
#define DB_MORE_EQ  3	///< col>=n
#define DB_LEST     4	///< col<n
#define DB_LEST_EQ  5	///< col<=n



struct tdb_common
{
	int id;				///< 自增长
	int val1;			///< 用户数据
	int val2;			///< 用户数据
	int val3;			///< 用户数据
	int val4;			///< 用户数据
	int val5;			///< 用户数据
	int val6;			///< 用户数据
	int val7;			///< 用户数据
	int val8;			///< 用户数据
	int val9;			///< 用户数据
	int val10;			///< 用户数据
	int val11;			///< 用户数据
	int val12;			///< 用户数据
	int lenpdata;		///< 二进制数据长度
	const void *pdata;		///< 自定义二进制
};
typedef struct tdb_common tdb_common_t;					 ///< tdb_common 通用表数据结构

typedef struct tms_sn                  tdb_sn_t;		 ///< tb_sn 表数据结构

struct tdb_sms
{
	int id;
	int32_t time;
	int8_t  phone[TLE_LEN];
	int32_t type;
	int32_t level;
};
typedef struct tdb_sms tdb_sms_t;		 ///< tb_sms 表数据结构


struct tdb_composition 
{
	int id;					///< 随机码
	int32_t frame;			///< 机框号
	int32_t slot;			///< 槽位号
	int32_t type;			///< 设备类型
	int32_t port;			///< 端口号
};
typedef struct tdb_composition tdb_composition_t;///< tb_composition 表数据结构

struct tdb_dev_map    
{
	int id;					///< 随机码
	int32_t frame;			///< 机框号
	int32_t slot;			///< 槽位号
	int32_t type;			///< 设备类型
	int32_t port;			///< 端口号
	uint8_t dev_name[64];	///< 设备名
	uint8_t cable_name[64];	///< 光纤名
	uint8_t start_name[64];	///< 本局端名
	uint8_t end_name[64];	///< 远局端名
};
typedef struct tdb_dev_map tdb_dev_map_t;	 ///< tb_dev_map 表数据结构



struct tdb_any_unit_osw
{
	int id;				///< 随机码
	// 参考 tmsxx.h的定义 struct tms_cfg_mcu_u_any_osw
	int32_t any_frame;	///<OPM/OLP机框编号
	int32_t any_slot;	///< OPM/OLP槽位编号
	int32_t any_type;	///< OPM/OLP设备类型

	// 参考 struct tms_cfg_mcu_u_any_osw_val
	int32_t any_port;	///< OPM/OLP端口编号
	int32_t osw_frame;	///< OSW机框编号
	int32_t osw_slot;	///< OSW槽位编号
	int32_t osw_type;	///< OSW设备类型，无用函数里自动设置成DEV_OSW
	int32_t osw_port;	///< OSW端口编号
};
typedef struct tdb_any_unit_osw tdb_any_unit_osw_t;///< tb_any_unit_osw 表数据结构




/*! \page introduce_tdb_route "tb_route 表涉及的数据结构"


struct tdb_route 在数据库里记录的一条有效路由

 \code {.cpp}

	dev1 --- dev2 ---dev3
	设 dev1，代表dev1_id、dev1_ip_src、dev1_ip_dst等其他以此类推，
	-- 表示地址无用
	数据表的收尾用全0标识

	在数据库里的表示形式	
	ida | ip_src_x ip_dst_x |  0     | dev1
	idb |    --       --    |  dev1  | dev2
	idc |    --       --    |  dev2  | dev3
	idd |    --       --    |  dev3  | dev0

\endcode
	struct tdb_route_line 描述一条完整的设备级联路由，是 struct tdb_route 的压缩形式，
	如果存在一条有3个节点的路由则描述形式如下

\code {.cpp}

 	| ip_src|
 	| ip_dst|
 	| count | = 3  ---->  	| node0 |   ---> 	| find	|
 							| node1 |			| id	|
 							| ..... |			| frame	|
 							| node3 |			| slot	|
 												| type	|
 												| port	|

\endcode
	struct tdb_route_node 搜索是否能找到一条路由中的某节点，为 tmsdb_Select_route 回调函数
 			在 _cb_Select_route_listline 中被调用
 * @see	
 */


#define MAX_ROUTE_NODE 16
/**
 * @brief	在数据库里记录的一条有效路由
 * @remark	\subpage introduce_tdb_route 
 	
 * @see _cb_Select_route_listline
 * @see struct tdb_route
 * @see struct tdb_route_node
 * @see struct tdb_route_line
 */
struct tdb_route
{
	int id;					///< 随机码
	int32_t ip_src;			///< 远方 IP 地址
	int32_t ip_dst;			///< 本地 IP 地址

	int32_t  frame_a;		///< 机框编号a
	int32_t  slot_a;		///< 槽位编号a
	int32_t  type_a;		///< 设备类型a
	int32_t  port_a;		///< 端口编号a

	int32_t  frame_b;		///< 机框编号b
	int32_t  slot_b;		///< 槽位编号b
	int32_t  type_b;		///< 设备类型b
	int32_t  port_b;		///< 端口编号b
};
typedef struct tdb_route tdb_route_t;

/**
 * @brief	搜索是否能找到一条路由中的某节点，为 tmsdb_Select_route 回调函数
 			在 _cb_Select_route_listline 中被调用
 * @see _cb_Select_route_listline
 * @see struct tdb_route
 * @see struct tdb_route_node
 * @see struct tdb_route_line
 */
struct tdb_route_node
{
	int find;			///< 是否找到路由节点标志
	int id;				///< 随机码
	int32_t  frame;		///< 机框编号
	int32_t  slot;		///< 槽位编号
	int32_t  type;		///< 设备类型
	int32_t  port;		///< 端口编号
};

/**
 * @brief	描述一条完整的设备级联路由
 * @remark	\subpage introduce_tdb_route 		
 * @see _cb_Select_route_listline
 * @see struct tdb_route
 * @see struct tdb_route_node
 * @see struct tdb_route_line
 */
struct tdb_route_line
{
	int32_t ip_src;					///< 远方 IP 地址
	int32_t ip_dst;					///< 本地 IP 地址
	int     count;					///< 节点数
	struct tdb_route_node *node;	///< 节点数组
};




struct tdb_a_trigger_b
{
	int id;

	int32_t  frame_a;		///< 触发条件：机框编号a
	int32_t  slot_a;		///< 触发条件：槽位编号a
	int32_t  type_a;		///< 触发条件：设备类型a
	int32_t  port_a;		///< 触发条件：端口编号a

	int32_t  frame_b;		///< 被触发：机框编号b
	int32_t  slot_b;		///< 被触发：槽位编号b
	int32_t  type_b;		///< 被触发：设备类型b
	int32_t  port_b;		///< 被触发：端口编号b
};
typedef struct tdb_a_trigger_b tdb_a_trigger_b_t;

struct tdb_osw_cyc
{
	int id;
	// 参考 tmsxx.h的定义 struct tms_cfg_mcu_osw_cycle
	int32_t  frame;		///< OSW机框编号
	int32_t  slot;		///< OSW槽位编号
	int32_t  type;		///< OSW设备类型

	// 参考 tmsxx.h的定义 struct tms_cfg_mcu_osw_cycle_val
	int32_t port;		///< OSW端口编号
	int32_t iscyc;		///< 是否周期测试
	int32_t interval;	///< 周期测试间隔
};
typedef struct tdb_osw_cyc tdb_osw_cyc_t;		///< tb_osw_cyc 表数据结构


struct tdb_osw_cyc_bak
{
	int id;
	// 参考 tmsxx.h的定义 struct tms_cfg_mcu_osw_cycle
	int32_t  frame;		///< OSW机框编号
	int32_t  slot;		///< OSW槽位编号
	int32_t  type;		///< OSW设备类型

	// 参考 tmsxx.h的定义 struct tms_cfg_mcu_osw_cycle_val
	int32_t port;		///< OSW端口编号
	int32_t iscyc;		///< 是否周期测试
	int32_t interval;	///< 周期测试间隔
	int32_t nexttest;	///< 下次测量
};
typedef struct tdb_osw_cyc_bak tdb_osw_cyc_bak_t;		///< tb_osw_cyc 表数据结构

struct tdb_otdr_rollcall
{
	int id;
	struct tms_getotdr_test_hdr    *ptest_hdr;
	struct tms_getotdr_test_param *ptest_param;
};
typedef struct tdb_otdr_rollcall tdb_otdr_rollcall_t;


struct tdb_otdr_ref
{
	int id;
	struct tms_otdr_ref_hdr       *pref_hdr; 		
	struct tms_retotdr_test_param *ptest_param; 

	struct tms_retotdr_data_hdr   *pdata_hdr; 
	struct tms_retotdr_data_val   *pdata_val; 

	struct tms_retotdr_event_hdr  *pevent_hdr; 
	struct tms_retotdr_event_val  *pevent_val; 

	struct tms_retotdr_chain      *pchain; 
	struct tms_cfg_otdr_ref_val   *pref_data;
};
typedef struct tdb_otdr_ref tdb_otdr_ref_t;		///< tb_otdr_ref 表数据结构

struct tdb_otdr_his_data
{
	int id;
	struct tms_retotdr_test_hdr   *ptest_hdr; 		
	struct tms_retotdr_test_param *ptest_param; 

	struct tms_retotdr_data_hdr   *pdata_hdr; 
	struct tms_retotdr_data_val   *pdata_val; 

	struct tms_retotdr_event_hdr  *pevent_hdr; 
	struct tms_retotdr_event_val  *pevent_val; 

	struct tms_retotdr_chain      *pchain;
};

typedef struct tdb_otdr_his_data tdb_otdr_his_data_t;		///< tb_otdr_his_data 表数据结构


struct tdb_otdr_alarm_data
{
	int id;
	struct tms_retotdr_test_hdr   *ptest_hdr; 		
	struct tms_retotdr_test_param *ptest_param; 

	struct tms_retotdr_data_hdr   *pdata_hdr; 
	struct tms_retotdr_data_val   *pdata_val; 

	struct tms_retotdr_event_hdr  *pevent_hdr; 
	struct tms_retotdr_event_val  *pevent_val; 

	struct tms_retotdr_chain      *pchain;
	struct tms_alarm_line_hdr     *palarm;
};
typedef struct tdb_otdr_alarm_data tdb_otdr_alarm_data_t;		///< tdb_otdr_alarm_data 表数据结构


void tmsdb_Echo(int echo);
int tmsdb_CheckDb();
int tmsdb_Insert_common(
		tdb_common_t *pcondition, 
		tdb_common_t *pmask,
		int count);
int tmsdb_Insert_sn(
		tdb_sn_t *pcondition, 
		tdb_sn_t *pmask,
		int count);
int tmsdb_Insert_sms(
		tdb_sms_t *pcondition, 
		tdb_sms_t *pmask,
		int count);
int tmsdb_Insert_composition(
		tdb_composition_t *pcondition, 
		tdb_composition_t *pmask,
		int count);
int tmsdb_Insert_dev_map(
		tdb_dev_map_t *pcondition, 
		tdb_dev_map_t *pmask,
		int count);
int tmsdb_Insert_any_unit_osw(
		tdb_any_unit_osw_t *pcondition, 
		tdb_any_unit_osw_t *pmask,
		int count);
int tmsdb_Insert_osw_cyc(
		tdb_osw_cyc_t *pcondition, 
		tdb_osw_cyc_t *pmask,
		int count);
int tmsdb_Insert_osw_cyc_bak(
		tdb_osw_cyc_bak_t *pcondition, 
		tdb_osw_cyc_bak_t *pmask,
		int count);
int tmsdb_Insert_otdr_rollcall(
		tdb_otdr_rollcall_t *pcondition, 
		tdb_otdr_rollcall_t *pmask,
		int count);
int tmsdb_Insert_otdr_ref(
		tdb_otdr_ref_t *pcondition, 
		tdb_otdr_ref_t *pmask,
		int count);
int tmsdb_Insert_otdr_his_data(
		tdb_otdr_his_data_t *pcondition, 
		tdb_otdr_his_data_t *pmask,
		int count);
int tmsdb_Insert_otdr_alarm_data(
		tdb_otdr_alarm_data_t *pcondition, 
		tdb_otdr_alarm_data_t *pmask,
		int count);



int tmsdb_Delete_common(
		tdb_common_t *pcondition, 
		tdb_common_t *pmask);
int tmsdb_Delete_sn(
		tdb_sn_t *pcondition, 
		tdb_sn_t *pmask);
int tmsdb_Delete_sms(
		tdb_sms_t *pcondition, 
		tdb_sms_t *pmask);

int tmsdb_Delete_composition(
		tdb_composition_t *pcondition, 
		tdb_composition_t *pmask);
int tmsdb_Delete_dev_map(
		tdb_dev_map_t *pcondition, 
		tdb_dev_map_t *pmask);
int tmsdb_Delete_any_unit_osw(
		tdb_any_unit_osw_t *pcondition, 
		tdb_any_unit_osw_t *pmask);
int tmsdb_Delete_osw_cyc(
		tdb_osw_cyc_t *pcondition, 
		tdb_osw_cyc_t *pmask);
int tmsdb_Delete_osw_cyc_bak(
		tdb_osw_cyc_bak_t *pcondition, 
		tdb_osw_cyc_bak_t *pmask);
int tmsdb_Delete_otdr_ref(
		tdb_otdr_ref_t *pcondition, 
		tdb_otdr_ref_t *pmask);
int tmsdb_Delete_otdr_rollcall(
		struct tdb_otdr_rollcall *pcondition, 
		struct tdb_otdr_rollcall *pmask);
int tmsdb_Delete_otdr_his_data(
		tdb_otdr_his_data_t *pcondition, 
		tdb_otdr_his_data_t *pmask);
int tmsdb_Delete_otdr_alarm_data(
		tdb_otdr_alarm_data_t *pcondition, 
		tdb_otdr_alarm_data_t *pmask);







int tmsdb_Select_common(
		tdb_common_t *pcondition, 
		tdb_common_t *pmask,
		// tdb_common_t **ppout,
		int (*pcallback)(tdb_common_t *cbptr, void *ptr, int len),
		void *ptr);
int tmsdb_Select_sn(
		tdb_sn_t *pcondition, 
		tdb_sn_t *pmask,
		tdb_sn_t **ppout);
int tmsdb_Select_sms(
		tdb_sms_t *pcondition, 
		tdb_sms_t *pmask,
		tdb_sms_t **ppout);
int tmsdb_Select_composition(
		tdb_composition_t *pcondition, 
		tdb_composition_t *pmask,
		tdb_composition_t **ppout);
int tmsdb_Select_dev_map(
		tdb_dev_map_t *pcondition, 
		tdb_dev_map_t *pmask,
		tdb_dev_map_t **ppout);
int tmsdb_Select_any_unit_osw(
		tdb_any_unit_osw_t *pcondition, 
		tdb_any_unit_osw_t *pmask,
		tdb_any_unit_osw_t **ppout);
int tmsdb_Select_osw_cyc(
		tdb_osw_cyc_t *pcondition, 
		tdb_osw_cyc_t *pmask,
		tdb_osw_cyc_t **ppout);
int tmsdb_Select_osw_cyc_bak(
		tdb_osw_cyc_bak_t *pcondition, 
		tdb_osw_cyc_bak_t *pmask,
		tdb_osw_cyc_bak_t **ppout);
int tmsdb_Select_otdr_rollcall(
		tdb_otdr_rollcall_t *pcondition, 
		tdb_otdr_rollcall_t *pmask,
		int (*pcallback)(tdb_otdr_rollcall_t *output, void *ptr), 
		void *ptr);
int tmsdb_Select_otdr_ref(
		tdb_otdr_ref_t *pcondition, 
		tdb_otdr_ref_t *pmask,
		int (*pcallback)(tdb_otdr_ref_t *output, void *ptr), 
		void *ptr);
int tmsdb_Select_otdr_his_data(
		tdb_otdr_his_data_t *pcondition, 
		tdb_otdr_his_data_t *pmask,
		int (*pcallback)(tdb_otdr_his_data_t *cbptr, void *ptr),
		void *ptr);
int tmsdb_Select_otdr_alarm_data(
		tdb_otdr_alarm_data_t *pcondition, 
		tdb_otdr_alarm_data_t *pmask,
		int (*pcallback)(tdb_otdr_alarm_data_t *cbptr, void *ptr),
		void *ptr);

int tmsdb_Select_Page_route(
		tdb_route_t *pcondition, 
		tdb_route_t *pmask,
		int from,
		int limit,
		int (*pcallback)(tdb_route_t *output, void *ptr), 
		void *ptr);
int tmsdb_Select_route(
		tdb_route_t *pcondition, 
		tdb_route_t *pmask,
		int (*pcallback)(tdb_route_t *output, void *ptr), 
		void *ptr);




int tmsdb_Select_a_trigger_b(
		tdb_a_trigger_b_t *pcondition, 
		tdb_a_trigger_b_t *pmask,
		int (*pcallback)(tdb_a_trigger_b_t *output, void *ptr), 
		void *ptr);
int tmsdb_Delete_route(
		tdb_route_t *pcondition, 
		tdb_route_t *pmask,
		int count);
int tmsdb_Delete_a_trigger_b(
		tdb_a_trigger_b_t *pcondition, 
		tdb_a_trigger_b_t *pmask);
int tmsdb_Insert_route(
		tdb_route_t *pcondition, 
		tdb_route_t *pmask,
		int count);
int tmsdb_Insert_a_trigger_b(
		tdb_a_trigger_b_t *pcondition, 
		tdb_a_trigger_b_t *pmask,
		int count);

int tmsdb_Select_oneline(
		tdb_route_t *pcondition,
		tdb_route_t *poutput,
		int *plen);

int tmsdb_Select_Page_a_trigger_b(
		tdb_a_trigger_b_t *pcondition,
		tdb_a_trigger_b_t *pmask,
		int from,
		int limit,
		int (*pcallback)(tdb_a_trigger_b_t *output, void *ptr),
		void *ptr);

struct tdb_route * tmsdb_Check_route_getoneline(struct tdb_route *pval, int *len);
int tmsdb_Check_route_oneline(struct tdb_route *pval, int count);
int tmsdb_Check_route_multiline(struct tdb_route *pval, int count);


#ifdef __cplusplus
}
#endif

#endif