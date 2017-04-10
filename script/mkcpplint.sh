#!/bin/bash



function param_less() {
	if [ "${2}" -lt "${3}" ]; then
		echo "${1} param less ${3}"
		exit;
	fi
}



function build_filter() {							
	param_less $FUNCNAME $# 2

	if [ ! ${1} ]
	then
		return 0;
	fi

	if [ "${2}" == "y" ]
	then
		echo 'filter=-'${3}
	else
		echo 'filter=+'${3}
	fi

}


. .cpplint_config

build_filter "$CONFIG_whitespace_semicolon"				"$CONFIG_no_whitespace_semicolon" 		'whitespace/semicolon'
build_filter "$CONFIG_whitespace_blank_line"			"$CONFIG_no_whitespace_blank_line" 		'whitespace/blank_line'
build_filter "$CONFIG_whitespace_tab"					"$CONFIG_no_whitespace_tab" 			'whitespace/tab'

build_filter "$CONFIG_build_class"						"$CONFIG_build_class" 					'build/class'
build_filter "$CONFIG_build_c11"						"$CONFIG_build_c11" 					'build/c++11'
build_filter "$CONFIG_build_c14"						"$CONFIG_build_c14" 					'build/c++14'
build_filter "$CONFIG_build_ctr1"						"$CONFIG_build_ctr1" 					'build/c++tr1'
build_filter "$CONFIG_build_deprecated"					"$CONFIG_build_deprecated" 				'build/deprecated'
build_filter "$CONFIG_build_endif_comment"				"$CONFIG_build_endif_comment" 			'build/endif_comment'
build_filter "$CONFIG_build_explicit_make_pair"			"$CONFIG_build_explicit_make_pair" 		'build/explicit_make_pair'
build_filter "$CONFIG_build_forward_decl"				"$CONFIG_build_forward_decl" 			'build/forward_decl'
build_filter "$CONFIG_build_header_guard"				"$CONFIG_build_header_guard" 			'build/header_guard'
build_filter "$CONFIG_build_include"					"$CONFIG_build_include" 				'build/include'
build_filter "$CONFIG_build_include_subdir"				"$CONFIG_build_include_subdir" 			'build/include_subdir'
build_filter "$CONFIG_build_include_alpha"				"$CONFIG_build_include_alpha" 			'build/include_alpha'
build_filter "$CONFIG_build_include_order"				"$CONFIG_build_include_order" 			'build/include_order'
build_filter "$CONFIG_build_include_what_you_use"		"$CONFIG_build_include_what_you_use" 	'build/include_what_you_use'
build_filter "$CONFIG_build_namespaces_literals"		"$CONFIG_build_namespaces_literals" 	'build/namespaces_literals'
build_filter "$CONFIG_build_namespaces"					"$CONFIG_build_namespaces" 				'build/namespaces'
build_filter "$CONFIG_build_printf_format"				"$CONFIG_build_printf_format" 			'build/printf_format'
build_filter "$CONFIG_build_storage_class"				"$CONFIG_build_storage_class" 			'build/storage_class'



build_filter "$CONFIG_legal_copyright"					"$CONFIG_no_legal_copyright" 			'legal/copyright'


build_filter "$CONFIG_readability_alt_tokens"			"$CONFIG_no_readability_alt_tokens" 		'readability/alt_tokens'
build_filter "$CONFIG_readability_braces"				"$CONFIG_no_readability_braces" 			'readability/braces'
build_filter "$CONFIG_readability_casting"				"$CONFIG_no_readability_casting" 			'readability/casting'
build_filter "$CONFIG_readability_check"				"$CONFIG_no_readability_check" 				'readability/check'
build_filter "$CONFIG_readability_constructors"			"$CONFIG_no_readability_constructors" 		'readability/constructors'
build_filter "$CONFIG_readability_fn_size"				"$CONFIG_no_readability_fn_size" 			'readability/fn_size'
build_filter "$CONFIG_readability_inheritance"			"$CONFIG_no_readability_inheritance" 		'readability/inheritance'
build_filter "$CONFIG_readability_multiline_comment"	"$CONFIG_no_readability_multiline_comment" 	'readability/multiline_comment'
build_filter "$CONFIG_readability_multiline_string"		"$CONFIG_no_readability_multiline_string" 	'readability/multiline_string'
build_filter "$CONFIG_readability_namespace"			"$CONFIG_no_readability_namespace" 			'readability/namespace'
build_filter "$CONFIG_readability_nolint"				"$CONFIG_no_readability_nolint" 			'readability/nolint'
build_filter "$CONFIG_readability_nul"					"$CONFIG_no_readability_nul" 				'readability/nul'
build_filter "$CONFIG_readability_strings"				"$CONFIG_no_readability_strings" 			'readability/strings'
build_filter "$CONFIG_readability_todo"					"$CONFIG_no_readability_todo" 				'readability/todo'
build_filter "$CONFIG_readability_utf8"					"$CONFIG_no_readability_utf8" 				'readability/utf8'


build_filter "$CONFIG_runtime_arrays"					"$CONFIG_no_runtime_arrays"						'runtime/arrays'
build_filter "$CONFIG_runtime_casting"					"$CONFIG_no_runtime_casting"					'runtime/casting'
build_filter "$CONFIG_runtime_explicit"					"$CONFIG_no_runtime_explicit"					'runtime/explicit'
build_filter "$CONFIG_runtime_int"						"$CONFIG_no_runtime_int"						'runtime/int'
build_filter "$CONFIG_runtime_init"						"$CONFIG_no_runtime_init"						'runtime/init'
build_filter "$CONFIG_runtime_invalid_increment"		"$CONFIG_no_runtime_invalid_increment"			'runtime/invalid_increment'
build_filter "$CONFIG_runtime_member_string_references"	"$CONFIG_no_runtime_member_string_references"	'runtime/member_string_references'
build_filter "$CONFIG_runtime_memset"					"$CONFIG_no_runtime_memset"						'runtime/memset'
build_filter "$CONFIG_runtime_indentation_namespace"	"$CONFIG_no_runtime_indentation_namespace"		'runtime/indentation_namespace'
build_filter "$CONFIG_runtime_operator"					"$CONFIG_no_runtime_operator"					'runtime/operator'
build_filter "$CONFIG_runtime_printf"					"$CONFIG_no_runtime_printf"						'runtime/printf'
build_filter "$CONFIG_runtime_printf_format"			"$CONFIG_no_runtime_printf_format"				'runtime/printf_format'
build_filter "$CONFIG_runtime_references"				"$CONFIG_no_runtime_references"					'runtime/references'
build_filter "$CONFIG_runtime_string"					"$CONFIG_no_runtime_string"						'runtime/string'
build_filter "$CONFIG_runtime_threadsafe_fn"			"$CONFIG_no_runtime_threadsafe_fn"				'runtime/threadsafe_fn'
build_filter "$CONFIG_runtime_vlog"						"$CONFIG_no_runtime_vlog"						'runtime/vlog'


build_filter "$CONFIG_whitespace_braces"				"$CONFIG_no_whitespace_braces"					"whitespace/braces"
build_filter "$CONFIG_whitespace_comma"					"$CONFIG_no_whitespace_comma"					"whitespace/comma"
build_filter "$CONFIG_whitespace_comments"				"$CONFIG_no_whitespace_comments"				"whitespace/comments"
build_filter "$CONFIG_whitespace_empty_if_body"			"$CONFIG_no_whitespace_empty_if_body"			"whitespace/empty_if_body"
build_filter "$CONFIG_whitespace_empty_loop_body"		"$CONFIG_no_whitespace_empty_loop_body"			"whitespace/empty_loop_body"
build_filter "$CONFIG_whitespace_end_of_line"			"$CONFIG_no_whitespace_end_of_line"				"whitespace/end_of_line"
build_filter "$CONFIG_whitespace_ending_newline"		"$CONFIG_no_whitespace_ending_newline"			"whitespace/ending_newline"
build_filter "$CONFIG_whitespace_forcolon"				"$CONFIG_no_whitespace_forcolon"				"whitespace/forcolon"
build_filter "$CONFIG_whitespace_indent"				"$CONFIG_no_whitespace_indent"					"whitespace/indent"
build_filter "$CONFIG_whitespace_line_length"			"$CONFIG_no_whitespace_line_length"				"whitespace/line_length"
build_filter "$CONFIG_whitespace_newline"				"$CONFIG_no_whitespace_newline"					"whitespace/newline"
build_filter "$CONFIG_whitespace_operators"				"$CONFIG_no_whitespace_operators"				"whitespace/operators"
build_filter "$CONFIG_whitespace_todo"					"$CONFIG_no_whitespace_todo"					"whitespace/todo"






