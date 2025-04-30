#!/bin/sh

CP_CMD=cp
RM_CMD=rm
G0=$HOME/research/gkyl-project/g0-branches/dir-reorg-fixes/gkylzero

# lua
mkdir -p lua
$CP_CMD -r $G0/lua .
