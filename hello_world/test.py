import os
import subprocess

# run the program and capture the output
result = subprocess.run("./a.out", stdout=subprocess.PIPE)

# test that the output is what we want.
# travis-ci will capture raised exceptions
if(result.stdout == b"Hello World!\n"):
    print("SUCCESS")
else:
    raise Exception("FAILURE")
