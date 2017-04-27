#!/bin/sh

bin=`dirname "${BASH_SOURCE-$0}"`
bin=`cd "$bin">/dev/null; pwd`

. "$bin"/hbase-config.sh

# start hbase daemons
errCode=$?
if [ $errCode -ne 0 ]
then
  exit $errCode
fi

#echo ${HBASE_CONF_DIR}
master=""
rest_port=""
thrift_port=""
hostname=`hostname -s`
while getopts "m:r:t:" arg #选项后面的冒号表示该选项需要参数
do
        case $arg in
             m)
                master=$OPTARG
                ;;
             r)
		rest_port=$OPTARG
                ;;
             t)
		thrift_port=$OPTARG
                ;;
             ?)  #当有不认识的选项的时候arg为?
                echo "unkonw argument"
                exit 1
                ;;
        esac
done
if [[ $rest_port -gt 0 ]] && [[ $thrift_port -gt 0 ]] && [[ $master ]];
then
  echo "master-hostname=$master" #参数存在$OPTARG中
  echo "port=$rest_port"
else
  echo "error, must match pattern:  $0 -m master-hostname -r rest_port -t thrift_port"
  echo "eg:  ./check-hbase.sh -m hadoop-master -r 38888 -t 37777 "
  exit -1
fi

#--1  HMaster
if [ "$master" = "$hostname" ];
then
  check_hmaster=`ps -ef|grep -i hmaster|grep -v grep|grep "org.apache.hadoop.hbase.master.HMaster"|wc -l`
  if [ $check_hmaster -eq 1 ];
  then
    echo "HMaster run ok"
  else
    echo "HMaster need restart"
    ./hbase-daemon.sh start master
  fi
else 
  echo "this host has no master"
fi
#--2  backup HMaster
n=`cat ${HBASE_CONF_DIR}/backup-masters|grep $hostname|wc -l`
if [ 1 -eq $n ];
then
  ./hbase-daemon.sh start master --backup
else 
  echo "this host has no master-backup"
fi
#--3  HQuorumPeer
check_HQuorumPeer=`ps -ef|grep -v grep|grep "org.apache.hadoop.hbase.zookeeper.HQuorumPeer"|wc -l`
if [ $check_HQuorumPeer -eq 1 ];
then
    echo "HQuorumPeer run ok"
else
    echo "HQuorumPeer need restart"
  ./hbase-daemon.sh --config ${HBASE_CONF_DIR} start zookeeper
fi

#--4  RESTServer
check_rest=`ps -ef|grep -v grep|grep "org.apache.hadoop.hbase.rest.RESTServer"|wc -l`
if [ $check_rest -eq 1 ];
then
  echo "RESTServer run ok"
else
  echo "RESTServer need restart"
  ./hbase-daemon.sh start rest -p $rest_port 
fi

#--5  ThriftServer
check_thrift=`ps -ef|grep -v grep|grep "org.apache.hadoop.hbase.thrift2.ThriftServer"|wc -l`
if [ $check_thrift -eq 1 ];
then
  echo "ThriftServer run ok"
else
  echo "ThriftServer need restart"
   ./hbase-daemon.sh start thrift2 -p $thrift_port
fi
#--5  HRegionServer
n=`cat ${HBASE_CONF_DIR}/regionservers|grep $hostname|wc -l`
if [ 1 -eq $n ];
then
  check_rest=`ps -ef|grep -v grep|grep "org.apache.hadoop.hbase.regionserver.HRegionServer"|wc -l `
  if [ $check_rest -eq 1 ];
  then
    echo "HRegionServer run ok"
  else
    echo "HRegionServer need restart"
    ./hbase-daemon.sh start regionserver
  fi
else 
  echo "this host has no regionserver"
fi
