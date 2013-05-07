#!/usr/bin/env python

# Great problem!
# Solution:
#   * disassebmle java from apk
#   * write android app with broadcast handler that catches 5 signals and
#     writes them to disk under Pictures/ on the sdcard :)
#   * use cat to concatenate 5 binary files, using `file' to find out which has
#     a JPEG header (and is the first); concat them and extract the numers.
#   * write an android app that queries the content provider for the contest
#     with all possible keys and extract all solutions.
#   * android app written is available under android/
#
#   The solutions are in m for the purpose of submitting.

import fileinput

m = [4233, 416, 815, 158, 164]

for line in fileinput.input():
  print m[int(line)]
