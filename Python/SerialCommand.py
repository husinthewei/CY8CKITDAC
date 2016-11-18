import SerialHandler 
import sys

a = sys.argv
if len(a) == 3:
    SH = SerialHandler.SerialHandler()
    msg = "0" * (3-len(str(a[2]))) + str(a[2]) + str(a[1])
    SH.writeLine(msg)
    print msg
else:
    print "argument must be which DAC (0-3) and new value (in mV)"