export TOP_DIR = $(realpath ./)
include $(TOP_DIR)/script/rules.mk

# include config_app_file_list.mk
# export SRCS


all: 
	# @$(MAKE) -C ./
	@$(MAKE) -C ./src/
clean: 
	$(MAKE) -C ./
# clean:
# 	echo $(TOP_DIR)
# 	rm 	$(OBJS) \
# 		$(OUTPUT_DIR)/$(NAME_DIS) \
# 		$(OUTPUT_DIR)/$(NAME_ELF) \
# 		core