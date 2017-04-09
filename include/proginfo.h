#ifndef _PROGRAM_INFO_

#define __stringify(x...)        #x

#define ___module_cat(a,b) __mod_ ## a ## b
#define __module_cat(a,b) ___module_cat(a,b)


#define __MODULE_INFO(tag, name, info)					  \
static const char __module_cat(name,__LINE__)[]				  \
  __attribute__((section(".modinfo"),used)) = __stringify(tag) "=" info

#define MODULE_PARM_DESC(_parm, desc) \
	__MODULE_INFO(parm, _parm, #_parm ":" desc)

#define MODULE_DESCRIPTION(_description) MODULE_INFO(description, _description)

#define MODULE_INFO(tag, info) __MODULE_INFO(tag, tag, info)





#define MODULE_GENERIC_TABLE(gtype,name)			\
extern const struct gtype##_id __mod_##gtype##_table		\
  __attribute__ ((unused, alias(__stringify(name))))

#define MODULE_INFO(tag, info) __MODULE_INFO(tag, tag, info)
#define MODULE_ALIAS(_alias) MODULE_INFO(alias, _alias)
#define MODULE_LICENSE(_license) MODULE_INFO(license, _license)
#define MODULE_AUTHOR(_author) MODULE_INFO(author, _author)
#define MODULE_DESCRIPTION(_description) MODULE_INFO(description, _description)
#define MODULE_PARM_DESC(_parm, desc) \
  __MODULE_INFO(parm, _parm, #_parm ":" desc)
#define MODULE_DEVICE_TABLE(type,name)		\
  MODULE_GENERIC_TABLE(type##_device,name)
#define MODULE_VERSION(_version) MODULE_INFO(version, _version)
#define MODULE_FIRMWARE(_firmware) MODULE_INFO(firmware, _firmware)
#define MODULE_BUILD(_time) MODULE_INFO(build, _time)
#define MODULE_DEPEND(_depend) MODULE_INFO(depend, _depend)
#define MODULE_PROJECT(_project) MODULE_INFO(project, _project)

#define PROG_INFO MODULE_INFO
#define PROG_ALIAS MODULE_ALIAS
#define PROG_LICENSE MODULE_LICENSE
#define PROG_AUTHOR MODULE_AUTHOR
#define PROG_DESCRIPTION MODULE_DESCRIPTION
#define PROG_PARM_DESC MODULE_PARM_DESC
#define PROG_DEVICE_TABLE MODULE_DEVICE_TABLE
#define PROG_VERSION MODULE_VERSION
#define PROG_FIRMWARE MODULE_FIRMWARE
#define PROG_BUILD MODULE_BUILD
#define PROG_DEPEND MODULE_DEPEND
#define PROG_PROJECT MODULE_PROJECT
#define PROG_GITSHA1(_git_sha1) MODULE_INFO(git,_git_sha1)
#endif