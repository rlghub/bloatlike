#!/bin/bash
cd src;
g++ actor.cc frame.cc main.cc -lncurses -o ../rl;
cd ..
