#!/bin/sh

CP_CMD=cp
G0=/home/gandalf/research/gkyl-project/g0-branches/dir-reorg-fixes/gkylzero

# zero
mkdir -p zero

# app
mkdir -p apps

$CP_CMD $G0/apps/gkyl_moment.h apps/
$CP_CMD $G0/apps/gkyl_moment_lw.h apps/
$CP_CMD $G0/apps/gkyl_moment_multib.h apps/
$CP_CMD $G0/apps/gkyl_moment_multib_priv.h apps/
$CP_CMD $G0/apps/gkyl_moment_priv.h apps/
$CP_CMD $G0/apps/mom_coupling.c apps/
$CP_CMD $G0/apps/mom_field.c apps/
$CP_CMD $G0/apps/mom_priv.c apps/
$CP_CMD $G0/apps/mom_species.c apps/
$CP_CMD $G0/apps/mom_update_one_step.c apps/
$CP_CMD $G0/apps/mom_update_ssp_rk.c apps/
$CP_CMD $G0/apps/moment.c apps/
$CP_CMD $G0/apps/moment_lw.c apps/
$CP_CMD $G0/apps/moment_multib.c apps/


# unit
mkdir -p unit

# regression
mkdir -p unit
