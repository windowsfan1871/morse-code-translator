#!/bin/bash

gcc encode.c -o morse_code_encoder
gcc decode.c -o morse_code_decoder

sudo mv morse_code_encoder /usr/bin
sudo mv morse_code_decoder /usr/bin
