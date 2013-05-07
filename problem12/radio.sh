#!/bin/bash

# The streamed file is base64 minimodem encoded mp3
# Realized forcing the partty.contest.tuenti.net to
# encode an input with invalid characters that gave
# an error I Googled and found in the source code of
# minimodem.
#
# So, first decode from mp3 to raw wav, then pass
# to minimodem to decode the sound using rtty.
base64 -d <&0 > tmp.mp3
ffmpeg -i tmp.mp3 -ar 8000 -ac 1 tmp.wav 2>/dev/null
minimodem -r -5  rtty -q -f tmp.wav
rm tmp.wav tmp.mp3
