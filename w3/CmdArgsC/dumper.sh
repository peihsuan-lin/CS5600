#!/bin/bash

# Compile the C program
make

# check if run file exists
if [ ! -f ./arger-lin ]; then
    echo "Error: arger-lin not found"
    exit 1
fi

# test cases

./arger-lin "$@"

./arger-lin -cap help is on the WAY
test $? -eq 0 || echo "The -cap test has failed!!"

./arger-lin -u help is on
test $? -eq 0 || echo "The -u test has failed!!"

./arger-lin -l help is on
test $? -eq 0 || echo "The -l test has failed!!"

./arger-lin -cad help is on the WAY
test $? -eq 255 || echo "The invalid flag test has failed!!"

./arger-lin -cap
test $? -eq 255 || echo "The argument length test has failed!!"