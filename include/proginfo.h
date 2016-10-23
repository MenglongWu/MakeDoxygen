#ifndef _PROGRAM_INFO_

#define __stringify(x...)        #x

#define ___module_cat(a,b) __mod_ ## a ## b
#define __module_cat(a,b) ___module_cat(a,b)
#define __MODULE_INFO(tag, name, info)					  \
static const char __module_cat(name,__LINE__)[]				  \
  __attribute__((section(".modinfo"),unused)) = __stringify(tag) "=" info


#define MODULE_PARM_DESC(_parm, desc) \
	__MODULE_INFO(parm, _parm, #_parm ":" desc)

#define MODULE_DESCRIPTION(_description) MODULE_INFO(description, _description)

#define MODULE_INFO(tag, info) __MODULE_INFO(tag, tag, info)





#define MODULE_GENERIC_TABLE(gtype,name)			\
extern const struct gtype##_id __mod_##gtype##_table		\
  __attribute__ ((unused, alias(__stringify(name))))

#define PROG_INFO(tag, info) __MODULE_INFO(tag, tag, info)
#define PROG_ALIAS(_alias) PROG_INFO(alias, _alias)
#define PROG_LICENSE(_license) PROG_INFO(license, _license)
#define PROG_AUTHOR(_author) PROG_INFO(author, _author)
#define PROG_DESCRIPTION(_description) PROG_INFO(description, _description)
#define PROG_PARM_DESC(_parm, desc) \
  __MODULE_INFO(parm, _parm, #_parm ":" desc)
#define PROG_DEVICE_TABLE(type,name)		\
  PROG_GENERIC_TABLE(type##_device,name)
#define PROG_VERSION(_version) PROG_INFO(version, _version)
#define PROG_FIRMWARE(_firmware) PROG_INFO(firmware, _firmware)
#define PROG_BUILD(_time) PROG_INFO(build, _time)
#define PROG_DEPEND(_depend) PROG_INFO(build, _depend)



#endif