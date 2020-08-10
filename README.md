# numa_machine_tests
source c code to debug numa machines

# install the qemu
qemu is a emulator for different machines. You install qemu like this:
```
sudo apt-get install qemu-kvm qemu virt-manager virt-viewer libvirt libvirt0
```
after this, you can star a machine direct, but no have a operational system. To start a machine with numa configuration, do you need creat a disk to not install operational system all time to start the machine.
in qemu you can creat a disk with this command
```
qemu-img create -f qcow2 disk.qcow 5G
```
Yes. you creat a 5 gigabytes disk to use for install operational system
Now, we start a numa machine with two nodes and two processor with 2Gigabytes of RAM (1G per node)
```
sudo qemu-system-x86_64 -M pc -m 2G,slots=2,maxmem=4G -object memory-backend-ram,size=1G,id=m0 -object memory-backend-ram,size=1G,id=m1 -numa node,nodeid=0,memdev=m0 -numa node,nodeid=1,memdev=m1 -smp 2,sockets=2,maxcpus=2 -numa cpu,node-id=0,socket-id=0 -numa cpu,node-id=1,socket-id=1 -enable-kvm -drive file=disk.qcow,format=qcow2 -cdrom http://archive.ubuntu.com/ubuntu/dists/bionic-updates/main/installer-amd64/current/images/netboot/mini.iso
```
In this example, we start a machine with a iso image of ubuntu from internet, but you can dowload the iso image before to start the machine and use this, is more fast. Case you prefer this, change the last information in the command line above
```
-cdrom mini.iso
```
Install the ubuntu minimal linux and have fun.
