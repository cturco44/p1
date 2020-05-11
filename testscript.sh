#!/bin/bash

#  testscript.sh
#  p1
#
#  Created by Connor Turco on 5/10/20.
#  Copyright © 2020 Connor Turco. All rights reserved.

for test in ./test-*.txt; do
    str1="${test#*-}"
    str2="${str1#*-}"
    str3="${str2%.*}"
    #str3 has just the arguments
    
    
done
