#!/usr/bin/pythonimport mathimport sysfor line in sys.stdin:    line = int(line.strip('\r').strip('\n'))    print sum(int(digit) for digit in str(math.factorial(line)))