#!/bin/bash

for i in 1 2 3 4 5; do
    echo
    echo i = $i
    for j in 1 2 3 4 5; do
        echo j = $j
        if [ $j -eq 2 ]; then break; fi
        if [ $j -eq 3 ] && [ $i -eq 4 ]; then break 2; fi
    done
done
