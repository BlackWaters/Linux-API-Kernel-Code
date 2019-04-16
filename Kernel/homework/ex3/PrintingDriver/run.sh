#!/bin/bash

make

sudo rmmod PrintModule 

sudo insmod ./PrintModule.ko

sudo ./a.out 





