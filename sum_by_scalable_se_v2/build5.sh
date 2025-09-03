#!/bin/sh
#

c7x_root=c:/ti/ccs1250/ccs/tools/compiler/ti-cgt-c7000_5.0.0.LTS

g++ -c --std=c++14 -fno-strict-aliasing -I${c7x_root}/host_emulation/include/C7100 sum_by_scalable_se_v2.c
g++ -o sum_by_scalable_se_v2 sum_by_scalable_se_v2.o -L${c7x_root}/host_emulation -lC7100-host-emulation
