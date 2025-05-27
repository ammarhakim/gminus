#!/bin/sh

CP_CMD=cp
RM_CMD=rm
G0=../gkylzero

$CP_CMD $G0/count-lines.sh ./
$CP_CMD $G0/cppcheck-suppress.txt ./
$CP_CMD $G0/LICENSE ./
$CP_CMD $G0/README.md ./
$CP_CMD $G0/run-cppcheck.sh ./

$RM_CMD $G0/count-lines.sh
$RM_CMD $G0/cppcheck-suppress.txt
$RM_CMD $G0/LICENSE
$RM_CMD $G0/README.md
$RM_CMD $G0/run-cppcheck.sh


# install-deps
mkdir -p install-deps
$CP_CMD $G0/install-deps/build-cudss.sh install-deps/
$CP_CMD $G0/install-deps/build-luajit.sh install-deps/
$CP_CMD $G0/install-deps/build-openblas.sh install-deps/
$CP_CMD $G0/install-deps/build-openmpi.sh install-deps/
$CP_CMD $G0/install-deps/build-parmetis.sh install-deps/
$CP_CMD $G0/install-deps/build-superlu_dist.sh install-deps/
$CP_CMD $G0/install-deps/build-superlu.sh install-deps/
$CP_CMD $G0/install-deps/download-adas.sh install-deps/
$CP_CMD $G0/install-deps/mkdeps.sh install-deps/

$RM_CMD $G0/install-deps/build-cudss.sh
$RM_CMD $G0/install-deps/build-luajit.sh
$RM_CMD $G0/install-deps/build-openblas.sh
$RM_CMD $G0/install-deps/build-openmpi.sh
$RM_CMD $G0/install-deps/build-parmetis.sh
$RM_CMD $G0/install-deps/build-superlu_dist.sh
$RM_CMD $G0/install-deps/build-superlu.sh
$RM_CMD $G0/install-deps/download-adas.sh
$RM_CMD $G0/install-deps/mkdeps.sh

# machines
mkdir -p machines
$CP_CMD $G0/machines/configure.della-cpu.sh machines/
$CP_CMD $G0/machines/configure.della-gpu.sh machines/
$CP_CMD $G0/machines/configure.linux.cpu.sh machines/
$CP_CMD $G0/machines/configure.linux.gpu.sh machines/
$CP_CMD $G0/machines/configure.macos.sh machines/
$CP_CMD $G0/machines/configure.perlmutter.cpu.sh machines/
$CP_CMD $G0/machines/configure.perlmutter.gpu.sh machines/
$CP_CMD $G0/machines/configure.satori.cpu.sh machines/
$CP_CMD $G0/machines/configure.satori.gpu.sh machines/
$CP_CMD $G0/machines/configure.stellar-amd.sh machines/
$CP_CMD $G0/machines/configure.stellar-intel.sh machines/
$CP_CMD $G0/machines/configure.traverse.dev.sh machines/
$CP_CMD $G0/machines/configure.traverse.host.sh machines/
$CP_CMD $G0/machines/jobScript.perlmutter-gpu machines/
$CP_CMD $G0/machines/jobScript.stellar-amd machines/
$CP_CMD $G0/machines/mkdeps.della-cpu.sh machines/
$CP_CMD $G0/machines/mkdeps.della-gpu.sh machines/
$CP_CMD $G0/machines/mkdeps.linux.sh machines/
$CP_CMD $G0/machines/mkdeps.macos.sh machines/
$CP_CMD $G0/machines/mkdeps.perlmutter.cpu.sh machines/
$CP_CMD $G0/machines/mkdeps.perlmutter.gpu.sh machines/
$CP_CMD $G0/machines/mkdeps.satori.sh machines/
$CP_CMD $G0/machines/mkdeps.stellar-amd.sh machines/
$CP_CMD $G0/machines/mkdeps.stellar-intel.sh machines/
$CP_CMD $G0/machines/mkdeps.traverse.sh machines/

$RM_CMD $G0/machines/configure.della-cpu.sh
$RM_CMD $G0/machines/configure.della-gpu.sh
$RM_CMD $G0/machines/configure.linux.cpu.sh
$RM_CMD $G0/machines/configure.linux.gpu.sh
$RM_CMD $G0/machines/configure.macos.sh
$RM_CMD $G0/machines/configure.perlmutter.cpu.sh
$RM_CMD $G0/machines/configure.perlmutter.gpu.sh
$RM_CMD $G0/machines/configure.satori.cpu.sh
$RM_CMD $G0/machines/configure.satori.gpu.sh
$RM_CMD $G0/machines/configure.stellar-amd.sh
$RM_CMD $G0/machines/configure.stellar-intel.sh
$RM_CMD $G0/machines/configure.traverse.dev.sh
$RM_CMD $G0/machines/configure.traverse.host.sh
$RM_CMD $G0/machines/jobScript.perlmutter-gpu
$RM_CMD $G0/machines/jobScript.stellar-amd
$RM_CMD $G0/machines/mkdeps.della-cpu.sh
$RM_CMD $G0/machines/mkdeps.della-gpu.sh
$RM_CMD $G0/machines/mkdeps.linux.sh
$RM_CMD $G0/machines/mkdeps.macos.sh
$RM_CMD $G0/machines/mkdeps.perlmutter.cpu.sh
$RM_CMD $G0/machines/mkdeps.perlmutter.gpu.sh
$RM_CMD $G0/machines/mkdeps.satori.sh
$RM_CMD $G0/machines/mkdeps.stellar-amd.sh
$RM_CMD $G0/machines/mkdeps.stellar-intel.sh
$RM_CMD $G0/machines/mkdeps.traverse.sh
