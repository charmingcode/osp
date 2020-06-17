# OSP 说明
---

> 作为各类开源项目集成party 

## docker

1. gcc8 , jdk8, python3, bazel3 
2. vimrc, dircolors 配色

## bazel

1. 全量符号表链接

```
cc_binary(
    name = "libxxxx.so",
    srcs = ["xxx.cc"],
    linkshared = True,
    linkstatic = True,  
    deps = [
      
    ],
)
```


## gflag

## glog

1. 参考kudu 实现双buffer的async_log，基于size和timeout触发flush


## gtest

## grpc


