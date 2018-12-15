# snort-tcp-socket
🐖 A SNORT&reg; version integrated with a TCP client.

Created by : Mr Dk.

@2018.12.13, Nanjing, Jiangsu, China

The National public memorial day of Nanjing Massacre 🕯️🕯️🕯️

---

### About

_Snort&reg;_ is an open-source, free and lightweight network intrusion detection system (NIDS) software for Linux and Windows to detect emerging threats, written in _C_.

https://www.snort.org/

My modification version is to integrate a TCP client into _Snort_, so that it can report the captured packets to a TCP server through _socket_.

This version is based on:

* _Snort&reg; Linux 2.9.12_ - [link](https://www.snort.org/downloads/snort/snort-2.9.12.tar.gz)
* _C Socket wrapper_ implemented by myself - [link](https://github.com/mrdrivingduck/linux-c-socket)
* _C JSON generator_ implemented by myself - [link](https://github.com/mrdrivingduck/c-json-generator)

### Installation

```bash
$ wget https://www.snort.org/downloads/snort/daq-2.0.6.tar.gz
$ tar xvzf daq-2.0.6.tar.gz
$ cd daq-2.0.6
$ ./configure && make && sudo make install
```

```bash
$ git clone https://github.com/mrdrivingduck/linux-c-socket.git
$ cd linux-c-socket
$ ./configure --enable-sourcefire && make && sudo make install
```

### Start Up

`IP Address` & `port` are added behind all parameters.

```bash
$ sudo snort 192.168.137.1 9002
```

### Modification

Modified these two files to include more `.h` & `.c` files.

```
src/Makefile.am
src/Makefile.in
```

Modified the `main` method to support `IP Addresss` & `port` input.

Modified the packets processing to output information.

```
src/snort.c
```

---

