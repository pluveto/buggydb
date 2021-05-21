#!/bin/bash

exit_with_error() {
    echo -e "\033[31m[ERROR]\033[0m $1"
}

rm test/primary_test -rf
cd build
make
if [ $? -ne 0 ]; then
    exit_with_error "Failed to build."
    exit 1
fi
cp ./primary_test ../test/
cd ../test/
rm db/* -rf
./primary_test