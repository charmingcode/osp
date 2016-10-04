#!/bin/sh 

cd ../../../ 
TOP_DIR=$(pwd)
cd -
WORK_DIR=$(pwd)
BUILD_DIR=build
ABSOLUTE_BUILD_DIR=$TOP_DIR/$BUILD_DIR
DIST_DIR=osp_party
ABSOLUTE_DIST_DIR=$ABSOLUTE_BUILD_DIR/$DIST_DIR
MODULES_DIST_DIR=$ABSOLUTE_DIST_DIR/modules

_PATH=$MODULES_DIST_DIR/bin
_LD_LIBRARY_PATH=$MODULES_DIST_DIR/lib

export PATH=$_PATH:$PATH
export LD_LIBRARY_PATH=$_LD_LIBRARY_PATH:$LD_LIBRARY_PATH

#  编译  xxx.thrift  idl
#thrift --gen cpp:cob_style httpapi.thrift
thrift -debug --gen py -o ./ httpapi.thrift ||exit 255


