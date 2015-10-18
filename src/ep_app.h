#ifndef _EP_APP_H_
#define _EP_APP_H_



#ifdef __cplusplus
extern "C" {
#endif

struct epapp_callback
{
	void (*pf_Accept)(int fd);
	void (*pf_RemoteClose)(int fd);
};


extern void ep_Callback(struct ep_t *pep);
extern int ThreadRunServerAndShell(struct ep_t *pep);
#ifdef __cplusplus
}
#endif
#endif
