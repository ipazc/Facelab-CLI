# Description

The FaceLab is the CLI facade for the Face+Age+Gender service. It is written in C++ optimized for the best performance.

# Requirements

The following packages are needed:
 - libboost-program-options-dev   (1.54+) 
 - libzmq3-dev

# Compilation

```
sudo apt-get update && sudo apt-get install build-essential libzmq3-dev libboost-program-options-dev
cd /tmp && git clone https://gitlab.com/varpsec/FaceLab.git && cd FaceLab
mkdir build && cd build
cmake ..
make -j $(nproc)
```

# Notes
It comes with a config file located in the folder `config/` that must be configured and copied in the folder `/etc/varpcore/` in
order for the CLI to work.
