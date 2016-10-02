#!/bin/bash
cd src;
g++ actor.cc frame.cc nscreen.cc main.cc -lncurses -o ../rl;
cd ..
