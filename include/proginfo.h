#ifndef _PROGRAM_INFO_

#define __stringify(x...)        #x

#define PROG_INFO(name,desc) \
	char   __pi_##name ## __LINE__ [] \
	__attribute__ ((unused,section (".modinfo"))) = __stringify(name) "=" desc;

#endif