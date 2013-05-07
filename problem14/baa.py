# Solution: #  played with xoring each cipher with all others, looking for letters.
#  xorring letter with a space(32) will invert the case of that letter
#  but will keep the same letter.
#
#  Played in bash with all combinations and reconstructed parts of the
#  phrases (where spaces existed in cartesian product), and managed
#  to google the phrases (see quotes file).
#
#  Then, using the longest quote to calculate the full key xoring it with
#  it's cipher, now can calclate anything. Baaad sheep.

# longest combination exposing the whole key
a = "Some humans would do anything to see if it was possible to do it. If you put a large switch in some cave somewhere, with a sign on it saying 'End-of-the-World Switch. PLEASE DO NOT TOUCH', the paint wouldn't even have time to dry."
b = "46fb200144df180dba5c8f52481c0ef515d9e963d0008b859c121b51ee8d0ca8e98b01d89a841257a1559174765d8ea95b9e69aaf014624eb5be51c415cfc5854aaa6c18b929b496e71a721303846856ae31c6d24529f4a9c19ef46a75819ea156598893e644f2c7f7ae39381b0184b5c937f8473a3800842e822014c4e8a94cc36373e81a6ee94632678625f2a5ff2eeb4eeae42d4190791cfd8fcc5f8dec2c2c5547fd63ebcb8a3c56303b4976dff9502d30e85955ed128114eb094b1667bb7da282be7ed7f1873d8e8c31d18ef24a48e990db46f5a591ecbc33704380a1b9b8babcdb4fe3"

from itertools import cycle, izip

def xor(ss, key):
    key = cycle(key)
    return ''.join(chr(ord(x) ^ ord(y)) for (x,y) in izip(ss, key))

binary_a = a
binary_b = b.decode("hex")

key = xor(a, binary_b)

import sys
for line in sys.stdin:
    line = line.strip('\r').strip('\n')
    key1 = key[0:len(line.decode("hex"))]
    print xor(key1, line.decode("hex"))
