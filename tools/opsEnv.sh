#!/bin/sh  
cpus=`cat /proc/cpuinfo |grep "physical id"|sort|uniq| wc -l`
real_cores_cpu_per=`cat /proc/cpuinfo |grep "cpu cores"|uniq|grep -oP "[0-9]+"`
total_cores=`cat /proc/cpuinfo |grep "processor"|wc -l`
cpuinfo=`cat /proc/cpuinfo |grep "model name"|uniq`

meminfo=`free -g`
netinfo=`ethtool eth0`
diskinfo=`df -h`
echo -e "\n---==== cpu ====---"
echo "cpus_num=$cpus"
echo "real_cores_cpu_per=$real_cores_cpu_per"
echo "total_real_cores="$real_cores_cpu_per*$cpus
echo "total_cores=$total_cores"
echo "cpuinfo=$cpuinfo"

echo -e "\n---==== mem ====---"
echo "meminfo=$meminfo"

echo -e "\n---==== net ====---"
echo "netinfo=$netinfo"

echo -e "\n---==== disk ====---"
echo "diskinfo=$diskinfo"
