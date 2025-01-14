#!/usr/bin/groovy
// SPDX-License-Identifier: BSD-2-Clause-Patent
// Copyright (c) 2019-2024 Intel Corporation

// To use a test branch (i.e. PR) until it lands to master
// I.e. for testing library changes
//@Library(value="pipeline-lib@your_branch") _
@Library(value="pipeline-lib@grom72/SRE-2736") _
packageBuildingPipelineDAOSTest(['distros': ['el8', 'el9', 'leap15', 'ubuntu20.04'],
				 'test-tag': 'pr daosio'])
