#!/bin/bash
cd src;
g++ actor.cc main.cc nscreen.cc -lncurses -o ../rl;
cd ..
