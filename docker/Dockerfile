#Note:
# cd osp/docker && docker build -t osp:test .
# docker run -it --rm -h debug     -v $HOME/work/ant/osp/osp:/v -v $HOME/.cache:/root/.cache -w /v/osp   osp:test

FROM centos:latest

#RUN yum install -y yum-plugin-ovl

# Install system tools
RUN yum install -y which

# Install gcc
RUN yum install -y glibc glibc-devel
RUN yum install -y gcc gcc-c++ libstdc++-devel binutils gdb

# Install clang
RUN yum install -y -b llvm clang compiler-rt

# Install jdk and python 
RUN yum install -y java-1.8.0-openjdk* python36
RUN yum install -y -b git automake libtool make.x86_64 cmake.x86_64 patch

# Install tools for integration test (aovid net timeout)
#RUN pip3 install pytest py4j pyyaml

# Install bazel
RUN curl https://copr.fedorainfracloud.org/coprs/vbatts/bazel/repo/epel-7/vbatts-bazel-epel-7.repo -o /etc/yum.repos.d/CentOS-Bazek.repo && yum install -y bazel3

ENTRYPOINT [ "/bin/bash" ]
