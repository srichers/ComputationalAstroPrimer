import os
import subprocess

# run the program and capture the output
result = subprocess.check_output("./a.out")

# test that the output is what we want.
# travis-ci will capture raised exceptions
if(result == b"Hello World!\n"):
    print("SUCCESS")
else:
    raise Exception("FAILURE")
