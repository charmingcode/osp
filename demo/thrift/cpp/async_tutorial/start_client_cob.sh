#!/bin/sh 

###################################################
#                  环境变量                       #
###################################################
WORKER_HOME=$(pwd)
cd ../../../../ && OSP_HOME=$(pwd) && cd -
MODULES_HOME=$OSP_HOME/build/osp_party/modules
export MODULES_HOME
_LD_LIBRARY_PATH+=:$MODULES_HOME/lib
_LD_LIBRARY_PATH+=:$LD_LIBRARY_PATH
LD_LIBRARY_PATH=$_LD_LIBRARY_PATH
export LD_LIBRARY_PATH

./CppCobClient
