import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/home/dorson/Documents/github/Doe/src/doe_teleop/install/doe_teleop'
