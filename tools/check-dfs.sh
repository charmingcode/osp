#!/bin/sh

bin=`dirname "${BASH_SOURCE-$0}"`
bin=`cd "$bin"; pwd`

DEFAULT_LIBEXEC_DIR="$bin"/../libexec
HADOOP_LIBEXEC_DIR=${HADOOP_LIBEXEC_DIR:-$DEFAULT_LIBEXEC_DIR}

. $HADOOP_LIBEXEC_DIR/hdfs-config.sh

HOSTNAME=`hostname -s`
NAMENODE=`$HADOOP_PREFIX/bin/hdfs getconf -namenodes|grep $HOSTNAME`
DATANODE=`cat $HADOOP_CONF_DIR/slaves|grep $HOSTNAME`

#echo $HADOOP_PREFIX
#echo $HADOOP_CONF_DIR

if [ $NAMENODE ];
then
  echo "There is one NAMENODE, NAMENODE=$NAMENODE"
  #--1
  check_namenode=`ps -ef|grep -v grep|grep "hdfs.server.namenode.NameNode"|wc -l`
  if [ $check_namenode -eq 1 ];
  then
    echo "namenode run ok"
  else 
    echo "namenode need restart"
    "$HADOOP_PREFIX/sbin/hadoop-daemons.sh" \
      --config "$HADOOP_CONF_DIR" \
      --hostnames "$NAMENODE" \
      --script "$bin/hdfs" start namenode 
  fi
  #--2
  check_secondary_namenode=`ps -ef|grep -v grep|grep "hdfs.server.namenode.SecondaryNameNode"|wc -l`
  if [ $check_secondary_namenode -eq 1 ];
  then
    echo "secondary_namenode run ok"
  else 
    echo "secondary_namenode need restart"
    "$HADOOP_PREFIX/sbin/hadoop-daemons.sh" \
      --config "$HADOOP_CONF_DIR" \
      --hostnames "$NAMENODE" \
      --script "$bin/hdfs" start secondarynamenode 
  fi
fi

if [ $DATANODE ];
then
  echo "There is one DATANODE, DATANODE=$DATANODE"
  #--3
  check_datanode=`ps -ef|grep -v grep|grep DataNode|wc -l`
  if [ $check_datanode -eq 1 ];
  then
    echo "datanode run ok"
  else 
    echo "datanode need restart"
    "$HADOOP_PREFIX/sbin/hadoop-daemons.sh" \
      --config "$HADOOP_CONF_DIR" \
      --hostnames "$DATANODE" \
      --script "$bin/hdfs" start datanode 
  fi
fi
