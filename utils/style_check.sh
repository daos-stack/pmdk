#!/usr/bin/env bash
# SPDX-License-Identifier: BSD-3-Clause
# Copyright 2016-2023, Intel Corporation
# Copyright 2025-2026, Hewlett Packard Enterprise Development LP
#
# utils/style_check.sh -- common style checking script
#
set -e

ARGS=("$@")
CSTYLE_ARGS=()
CLANG_ARGS=()
FLAKE8_ARGS=()
CHECK_TYPE=$1

# When updating, please search for all references to "clang-format" and update
# them as well; at this time these are CONTRIBUTING.md src/common.inc and
# docker images.
[ -z "$clang_format_bin" ] && which clang-format-14 >/dev/null &&
	clang_format_bin=clang-format-14
[ -z "$clang_format_bin" ] && which clang-format >/dev/null &&
	clang_format_bin=clang-format
[ -z "$clang_format_bin" ] && clang_format_bin=clang-format

#
# print script usage
#
function usage() {
	echo "$0 <check|format> [C/C++ files]"
}

#
# run old cstyle check
#
function run_cstyle() {
	if [ $# -eq 0 ]; then
		return
	fi

	${cstyle_bin} -pP $@
}

#
# generate diff with clang-format rules
#
function run_clang_check() {
	if [ $# -eq 0 ]; then
		return
	fi

	for file in $@
	do
		LINES=$(${clang_format_bin} -style=file $file |\
				git diff --no-index $file - | wc -l)
		if [ $LINES -ne 0 ]; then
			${clang_format_bin} -style=file $file | git diff --no-index $file -
		fi
	done
}

#
# in-place format according to clang-format rules
#
function run_clang_format() {
	if [ $# -eq 0 ]; then
		return
	fi

	${clang_format_bin} -style=file -i $@
}

function run_flake8() {
	if [ $# -eq 0 ]; then
		return
	fi
	${flake8_bin} --exclude=testconfig.py,envconfig.py $@
}

for ((i=1; i<$#; i++)) {

	IGNORE="$(dirname ${ARGS[$i]})/.cstyleignore"
	if [ -e $IGNORE ]; then
		if grep -q ${ARGS[$i]} $IGNORE ; then
			echo "SKIP ${ARGS[$i]}"
			continue
		fi
	fi
	case ${ARGS[$i]} in
		*.[ch]pp)
			CLANG_ARGS+="${ARGS[$i]} "
			;;

		*.[ch])
			CSTYLE_ARGS+="${ARGS[$i]} "
			;;

		*.py)
			FLAKE8_ARGS+="${ARGS[$i]} "
			;;

		*)
			echo "Unknown argument"
			exit 1
			;;
	esac
}

case $CHECK_TYPE in
	check)
		run_cstyle ${CSTYLE_ARGS}
		run_clang_check ${CLANG_ARGS}
		run_flake8 ${FLAKE8_ARGS}
		;;

	format)
		run_clang_format ${CLANG_ARGS}
		;;

	*)
		echo "Invalid parameters"
		usage
		exit 1
		;;
esac
