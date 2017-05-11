#!/usr/bin/python
import sys
import os

# 
# Load  'script/listprj.mk'
# Build 'script/listprj.kcfg'
#
def build_kconfig(load_mk,save_kconfig):
	ro = open(load_mk)
	line = '1'

	txt=[]
	txt.append(
		'choice\n'
			'\tprompt "Select project"\n\n\n'
		);
	while line != '' and line != None:
		line = ro.readline()

		# TODO comment
		if line.startswith('#') :
			continue

		if line.find("=script") != -1:
			line=line.replace('\n','')
			line=line.replace('\t','')
			line=line.replace('\r','')
			name = line.split('=')
			# write: bool "xxxxxx\n"
			txt.append(
				'config dp_' + name[0] + '\n'
					'\tbool  \"' + line + '\"\n');
	ro.close()

	
	txt.append('\n\nendchoice\n');

	wo = open(save_kconfig,'w')
	for line in txt:
		wo.write(line)
	wo.close()

# 
# Load .config
# Check which 'CONFIG_dp_xx' be selected. The default project is that 'xx'
# Write it in './script/listprj.mk' environment 'DP'
#
def which_def_prj(search_file):
	global dp_name

	ro = open(search_file)
	line='1'

	while line != '' and line != None:
		line = ro.readline()
		if line.startswith('#') :
			continue
		if line.find("CONFIG_dp_") != -1:
			# line.split('CONFIG_dp_')[1]  ==>  ['', 'pixxxxx=y\n']
			sp_name = line.split('CONFIG_dp_')[1]
			# sp_name.split('=')[1]  ==>  ['pixxxxx', 'y\n']
			dp_name = sp_name.split('=')[0]
			break

	ro.close()
	return dp_name
	

def save_def_prj(save_file, def_prj):
	ro = open(save_file,'r')
	
	line = '1'
	txt=[]
	while line != '' and line != None:
		line = ro.readline()

		if line.find("export DP=") != -1:
			line=line.replace('\n','')
			line=line.replace('\t','')
			line=line.replace('\r','')
			name = line.split('=')[0]
			txt.append(name + '=' + def_prj)
		else:
			txt.append(line)
	ro.close()

	wo = open(save_file,'w')
	for line in txt:
		wo.write(line)
	wo.close()

def usage():
	print('kconfig\ndefprj\nedit')

if __name__ == '__main__':
	# print(len(sys.argv))
	if len(sys.argv) < 2:
		usage()
		exit(-1);


	if sys.argv[1].startswith('kconfig'):
		build_kconfig('script/listprj.mk', 'script/listprj.kcfg')
	elif sys.argv[1].startswith('defprj'):
		dp = 'unknow'
		dp = which_def_prj('.config');
		save_def_prj('./script/listprj.mk', dp)
	else:
		print('undefined command \'' + sys.argv[1] + '\'');
		usage();
