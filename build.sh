#!/bin/sh
#

WORK_DIR=$(pwd)
TOP_DIR=$WORK_DIR
#安装到build目录下
BUILD_DIR=build
ABSOLUTE_BUILD_DIR=$TOP_DIR/$BUILD_DIR

DIST_DIR=osp_party
ABSOLUTE_DIST_DIR=$ABSOLUTE_BUILD_DIR/$DIST_DIR
DEMO_DIR=$WORK_DIR/demo
DEFAULT_VERSION=$DIST_DIR

#************ version **************
VERSION=$DEFAULT_VERSION
PKG_NAME=$VERSION.tar.gz




#************ install configure **************
index=0
#osp_libs[index++]="zookeeper-3.4.8.tar.gz"
#osp_libs[index++]="sigar-master.zip"
#osp_libs[index++]="jsoncpp-0.10.5.tar.gz"
#osp_libs[index++]="libevent-2.0.20-stable.tar.gz"
#osp_libs[index++]="Python-2.7.8.tgz"
#osp_libs[index++]="protobuf-2.5.0.tar.bz2"
#osp_libs[index++]="libunwind-0.99-beta.tar.gz"
#osp_libs[index++]="gperftools-2.1.tar.gz"
#osp_libs[index++]="bison-3.0.tar.gz"
#boost depend on  gcc-version, http://www.boost.org/users/history/version_1_54_0.html
osp_libs[index++]="boost_1_54_0.tar.gz"
#osp_libs[index++]="openssl-1.0.2.tar.gz"
osp_libs[index++]="thrift-0.9.2.tar.gz"
#osp_libs[index++]="pcre-8.37.tar.gz"
#osp_libs[index++]="memcached-1.4.25.tar.gz"
#osp_libs[index++]="libmemcache_mozilla_u3.tar.gz"
#osp_libs[index++]="apr-1.5.2.tar.gz"
#osp_libs[index++]="apr-util-1.5.4.tar.gz"
#osp_libs[index++]="httpd-2.4.18.tar.gz"
#osp_libs[index++]="demo_cpp_thrift"



function need_install() 
{
  pkg_name=$1
  array_tmp=$2
  for item in ${array_tmp[*]}; do 
    if [ $pkg_name == $item ];then
        return 0
    fi
  done;
  return 255
  
}

# *********** modules **************
MODULES_PKG_DIR=$TOP_DIR/modules
MODULES_DIST_DIR=$ABSOLUTE_DIST_DIR/modules
mkdir -p $MODULES_DIST_DIR


# pkg - 00
pkg_name="sigar-master.zip"
pkg_dir="sigar-master"
if need_install "$pkg_name" "${osp_libs[*]}";then
    echo "----- prepare install -----  $pkg_name"
    cd $MODULES_PKG_DIR
    unzip $pkg_name
    cd $pkg_dir && ./autogen.sh && ./configure --prefix=$MODULES_DIST_DIR && make && make install || exit 255
fi


# pkg - 01
pkg_name="jsoncpp-0.10.5.tar.gz"
pkg_dir="jsoncpp-0.10.5"
if need_install "$pkg_name" "${osp_libs[*]}";then
    echo "----- prepare install -----  $pkg_name"
    cd $MODULES_PKG_DIR
    tar zxvf jsoncpp-0.10.5.tar.gz
    cd $pkg_dir && mkdir -p ./build && cd ./build
    sed -i "s/unsigned int testNameIndex/unsigned int testNameIndex = 0/g" $MODULES_PKG_DIR/jsoncpp-0.10.5/src/test_lib_json/jsontest.cpp
    cmake -DCMAKE_BUILD_TYPE=release -DBUILD_STATIC_LIBS=ON -DBUILD_SHARED_LIBS=ON  -DCMAKE_INSTALL_PREFIX=$MODULES_DIST_DIR -G "Unix Makefiles" ../ && make && make install || exit 255
    cd $MODULES_PKG_DIR && rm -rf $pkg_dir
fi

# pkg - 02
pkg_name="libevent-2.0.20-stable.tar.gz"
pkg_dir="libevent-2.0.20-stable"
if need_install "$pkg_name" "${osp_libs[*]}";then
    echo "----- prepare install -----  $pkg_name"
    cd $MODULES_PKG_DIR
    tar zxvf $pkg_name 
    cd $pkg_dir
    ./configure --prefix=$MODULES_DIST_DIR && make && make install || exit 255
    #cd .. && rm -rf $pkg_dir
fi

# pkg - 16
pkg_name="Python-2.7.8.tgz"
pkg_dir="Python-2.7.8"
if need_install "$pkg_name" "${osp_libs[*]}";then
    cd $MODULES_PKG_DIR
    tar zxvf $pkg_name
    cd $pkg_dir
    ./configure --prefix=$MODULES_DIST_DIR -enable-shared && make && make install || exit 255
    cd $MODULES_PKG_DIR && rm -rf $pkg_dir
fi

# pkg - 03
pkg_name="protobuf-2.5.0.tar.bz2"
pkg_dir="protobuf-2.5.0"
if need_install "$pkg_name" "${osp_libs[*]}";then
    echo "----- prepare install -----  $pkg_name"
    cd $MODULES_PKG_DIR
    tar xjvf $pkg_name 
    cd $pkg_dir 
    ./configure --prefix=$MODULES_DIST_DIR && make && make install || exit 255
    cd python && export PYTHONPATH=$MODULES_DIST_DIR/lib/python2.7/site-packages/:$PYTHONPATH && python setup.py build && python setup.py install --prefix=$MODULES_DIST_DIR || exit 255
    cd ../.. && rm -rf $pkg_dir
fi

# pkg - 04
pkg_name="libunwind-0.99-beta.tar.gz"
pkg_dir="libunwind-0.99-beta"
if need_install "$pkg_name" "${osp_libs[*]}";then
    echo "----- prepare install -----  $pkg_name"
    cd $MODULES_PKG_DIR
    tar xzvf $pkg_name 
    cd $pkg_dir 
    ./configure --prefix=$MODULES_DIST_DIR && make && make install || exit 255
    cd .. && rm -rf $pkg_dir
fi

# pkg - 05
pkg_name="gperftools-2.1.tar.gz"
pkg_dir="gperftools-2.1"
if need_install "$pkg_name" "${osp_libs[*]}";then
    echo "----- prepare install -----  $pkg_name"
    cd $MODULES_PKG_DIR
    tar xzvf $pkg_name 
    cd $pkg_dir 
    ./configure --prefix=$MODULES_DIST_DIR LDFLAGS="-L$MODULES_DIST_DIR/lib" --enable-frame-pointers && make && make install || exit 255
    cd .. && rm -rf $pkg_dir
fi

# pkg - 06
pkg_name="bison-3.0.tar.gz"
pkg_dir="bison-3.0"
if need_install "$pkg_name" "${osp_libs[*]}";then
    echo "----- prepare install -----  $pkg_name"
    cd $MODULES_PKG_DIR
    tar zxvf $pkg_name 
    cd $pkg_dir 
    ./configure --prefix=$MODULES_DIST_DIR && make && make install || exit 255
    cd .. && rm -rf $pkg_dir
fi

# pkg - 07
pkg_name="boost_1_54_0.tar.gz"
pkg_dir="boost_1_54_0"
if need_install "$pkg_name" "${osp_libs[*]}";then
    echo "----- prepare install -----  $pkg_name"
    cd $MODULES_PKG_DIR
    tar zxvf $pkg_name 
    cd $pkg_dir 
    ./bootstrap.sh && ./b2 install --prefix=$MODULES_DIST_DIR || exit 255
    cd .. && rm -rf $pkg_dir
fi

# pkg - 08
pkg_name="openssl-1.0.2.tar.gz"
pkg_dir="openssl-1.0.2"
if need_install "$pkg_name" "${osp_libs[*]}";then
    echo "----- prepare install -----  $pkg_name"
    cd $MODULES_PKG_DIR
    tar zxvf $pkg_name 
    cd $pkg_dir 
    ./config --prefix=$MODULES_DIST_DIR --libdir=lib shared && make -j1 && make install || exit 255
    cd .. && rm -rf $pkg_dir
fi

# pkg - 09
pkg_name="thrift-0.9.2.tar.gz"
pkg_dir="thrift-0.9.2"
if need_install "$pkg_name" "${osp_libs[*]}";then
    echo "----- prepare install -----  $pkg_name"
    cd $MODULES_PKG_DIR
    export PATH=$MODULES_DIST_DIR/bin:$PATH
    tar zxvf $pkg_name 
    cd $pkg_dir 
    ./configure --prefix=$MODULES_DIST_DIR --with-boost=$MODULES_DIST_DIR --with-libevent=$MODULES_DIST_DIR --with-openssl=$MODULES_DIST_DIR --disable-tests --without-lua --without-c_glib --without-python --without-php --without-qt4 && make && make install || exit 255
    cd .. && rm -rf $pkg_dir
fi

# pkg - 10
pkg_name="pcre-8.37.tar.gz"
pkg_dir="pcre-8.37"
if need_install "$pkg_name" "${osp_libs[*]}";then
    cd $MODULES_PKG_DIR
    tar zxvf $pkg_name
    cd $pkg_dir
    ./configure --prefix=$MODULES_DIST_DIR && make && make install || exit 255
    cd .. && rm -rf $pkg_dir
fi

# pkg - 11
pkg_name="libmemcache_mozilla_u3.tar.gz"
pkg_dir="libmemcache"
if need_install "$pkg_name" "${osp_libs[*]}";then
    cd $MODULES_PKG_DIR
    tar zxvf $pkg_name
    cd $pkg_dir 
    ./configure --prefix=$MODULES_DIST_DIR && make && make install || exit 255
    cd .. && rm -rf $pkg_dir
fi

# pkg - 12
pkg_name="memcached-1.4.25.tar.gz"
pkg_dir="memcached-1.4.25"
if need_install "$pkg_name" "${osp_libs[*]}";then
    cd $MODULES_PKG_DIR
    tar xvf $pkg_name
    cd $pkg_dir
    ./configure --prefix=$MODULES_DIST_DIR && make && make install || exit 255
    cd .. && rm -rf $pkg_dir
fi

# pkg - 13
pkg_name="apr-1.5.2.tar.gz"
pkg_dir="apr-1.5.2"
if need_install "$pkg_name" "${osp_libs[*]}";then
    cd $MODULES_PKG_DIR
    tar zxvf $pkg_name
    cd $pkg_dir
    ./configure --prefix=$MODULES_DIST_DIR && make && make install || exit 255
    cd $MODULES_PKG_DIR && rm -rf $pkg_dir
fi

# pkg - 14
pkg_name="apr-util-1.5.4.tar.gz"
pkg_dir="apr-util-1.5.4"
if need_install "$pkg_name" "${osp_libs[*]}";then
    cd $MODULES_PKG_DIR
    tar zxvf $pkg_name
    cd $pkg_dir
    ./configure --prefix=$MODULES_DIST_DIR --with-apr=$MODULES_DIST_DIR && make && make install || exit 255
    cd $MODULES_PKG_DIR && rm -rf $pkg_dir
fi

# pkg - 15
pkg_name="httpd-2.4.18.tar.gz"
pkg_dir="httpd-2.4.18"
if need_install "$pkg_name" "${osp_libs[*]}";then
    cd $MODULES_PKG_DIR
    tar zxvf $pkg_name
    cd $pkg_dir
    ./configure --prefix=$MODULES_DIST_DIR --with-apr=$MODULES_DIST_DIR --with-apr-util=$MODULES_DIST_DIR --with-pcre=$MODULES_DIST_DIR && make && make install || exit 255
    #cd $MODULES_PKG_DIR && rm -rf $pkg_dir
fi

# pkg - 16 
pkg_name="zookeeper-3.4.8.tar.gz"
pkg_dir="zookeeper-3.4.8/src/c"
if need_install "$pkg_name" "${osp_libs[*]}";then
    cd $MODULES_PKG_DIR
    tar zxvf $pkg_name
    cd $pkg_dir
    ./configure --prefix=$MODULES_DIST_DIR && make && make install || exit 255
    #cd $MODULES_PKG_DIR && rm -rf $pkg_dir
fi



# ******** 生成 demo ********
pkg_name="demo_cpp_thrift"
if need_install "$pkg_name" "${osp_libs[*]}";then
    echo "----- prepare install -----  $pkg_name"
    cd $DEMO_DIR/cpp_thrift
    ./build.sh
fi

# ******** 生成version信息 ********
cd $ABSOLUTE_DIST_DIR
echo "$VERSION" > version
echo "build date:" >> version
echo `date` >> version
cat version

# ************* 打包 **************
#cd $ABSOLUTE_BUILD_DIR
#echo `pwd`
#tar -czvf $PKG_NAME $DIST_DIR

#--end
