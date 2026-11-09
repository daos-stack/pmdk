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

if [ "$CHECK_TYPE" = "check" ]; then
    run_cstyle ${CSTYLE_ARGS}
    run_flake8 ${FLAKE8_ARGS}
else
    echo "Invalid parameters"
    usage
    exit 1
fi
