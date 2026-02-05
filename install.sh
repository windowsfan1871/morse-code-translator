#!/bin/bash

gcc encode.c -o morse_code_encoder
gcc decode.c -o morse_code_decoder

cp morse_code_encoder /usr/bin
cp morse_code_decoder /usr/bin
