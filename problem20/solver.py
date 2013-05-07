#!/usr/bin/env python

# Another great and challenging problem :)
#
# Solution: go step by step through the instructions
# 1 by 1 and realize 2 things:
#
#  * binary was getting stuck afer return from ptrace
#      .text:080480C7 mov     [ebp+var_10], eax
#      .text:080480CA xor     edx, edx                   ; addr
#      .text:080480CC mov     eax, 1Ah
#      .text:080480D1 mov     ebx, edx                   ; ptrace_request
#      .text:080480D3 mov     ecx, edx                   ; pid
#      .text:080480D5 mov     esi, edx                   ; data
#      .text:080480D7 int     80h                        ; LINUX - sys_ptrace
#      .text:080480D9 test    eax, eax
#      .text:080480DB jnz     short loc_804813C          ; exit 255 essentially
#
# Problem was that the sys_ptrace would leave eax = 255 when the trap would end
# so there was nothing to be done, so I replace the test instruction with a
# xor instruction, so it was
#
#      .text:080480D9 xor    eax, eax
#
# which in turn set eax to 0, and the next line did not take it to exit. This
# Was the 1st step.
#
#
# Second step was to realize by playing around and observing how the program
# looked into the stack that it was essentially doing something like this:
#
#         for (char c : argv[1]) {
#           if (c ^ buffer1[i] != buffer2[i]) {
#             exit(255);
#           }
#           ++i;
#         }

#         .text:08048112 and     edx, 0FFh
#         .text:08048118 xor     ecx, edx
#         .text:0804811A movzx   eax, byte_8048148[esi]
#         .text:08048121 cmp     ecx, eax
#         .text:08048123 jnz     short loc_8048127
#         .text:08048125 jmp     short loc_804812A
#
# After noticing that I went letter by letter, and inverse calculating what
# my char should be, namely c[i] = buffer1[i] xor buffer2[i].
#
# The rest is history.

print "We're not hit! We're not hit!"
