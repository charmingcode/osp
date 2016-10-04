#!/bin/sh 

###################################################
#                  环境变量                       #
###################################################
WORKER_HOME=$(pwd)
cd ../../ && OSP_HOME=$(pwd) && cd -
MODULES_HOME=$OSP_HOME/build/osp_party/modules
_LD_LIBRARY_PATH+=:$MODULES_HOME/lib
_LD_LIBRARY_PATH+=:$LD_LIBRARY_PATH
LD_LIBRARY_PATH=$_LD_LIBRARY_PATH
export LD_LIBRARY_PATH

app=pcre_test
debug=0
while getopts "g" arg #选项后面的冒号表示该选项需要参数
do
    case $arg in
        g)
            debug=1
            ;;
        ?)
            ;;
    esac
done

REG="^/"
URL="/abcd"

if [ $debug -eq 1 ];then
  gdb $app $REG $URL;
else
  ./$app $REG $URL;
fi
