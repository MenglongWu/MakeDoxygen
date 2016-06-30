#################################################################
# list all souce file while be compiled
# file select or not please edit script/config.mk


SRCS-y += 	script/kconfig/mconf.c \
                script/kconfig/zconf.tab.c \
                script/kconfig/lxdialog/checklist.c \
                script/kconfig/lxdialog/util.c \
                script/kconfig/lxdialog/inputbox.c \
                script/kconfig/lxdialog/textbox.c \
                script/kconfig/lxdialog/yesno.c \
                script/kconfig/lxdialog/menubox.c 

SRCS-y += 	script/kconfig/lxdialog/util.c
	
# SRCS-y += shell/minishell_core.c
# SRCS-y += shell/minishell_core_ex.c