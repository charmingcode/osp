#!/bin/sh


#echo $# 
#echo $@
#echo $0
if [ $# -lt 3 ];
then
  echo "must set base_dir1  base_dir2, and vimdiff file"
  exit -1
fi

base_dir1=$1
base_dir2=$2
dst_file=$3

if [ ! -d $1 -o ! -d $2 ];
then
  echo "$1 and $2 must be dir and exits"
  exit -1
fi

dst_file1=`readlink -f $base_dir1`"/$dst_file"
dst_file2=`readlink -f $base_dir2`"/$dst_file"
echo $dst_file1
echo $dst_file2
if [ $dst_file1 = $dst_file2 ];
then
  echo "two file must be not the same"
  exit -1;
fi

if [ ! -f $dst_file1 -o ! -f $dst_file2 ];
then
  echo "two file must exists"
  exit -1
fi

vimdiff $dst_file1 $dst_file2


