#!/usr/bin/python
# This script automatically creates a list of examples by reading the header in all problem.c files.
import glob

with open("version.txt") as f:
    reboundxversion = f.readlines()[0].strip()
    print "Updating version to "+reboundxversion

with open("README.rst") as f:
    readme = f.readlines()

with open("README.rst","w") as f:
    for i in range(0,len(readme)):
        if "badge/REBOUNDx-v" in readme[i]:
            readme[i] = ".. image:: http://img.shields.io/badge/REBOUNDx-v"+reboundversion+"-green.svg?style=flat\n"
        f.write(readme[i])

with open("src/reboundx.c") as f:
    reboundxlines = f.readlines()
    for i,l in enumerate(reboundxlines):
        if "**VERSIONLINE**" in l:
            reboundxlines[i] = "const char* rebx_version_str = \""+reboundxversion+"\";			// **VERSIONLINE** This line gets updated automatically. Do not edit manually.\n"

    with open("src/reboundx.c", "w") as f:
        f.writelines(reboundxlines)

with open("setup.py") as f:
    setuplines = f.readlines()
    for i,l in enumerate(setuplines):
        if "version='" in l:
            setuplines[i] = "    version='"+reboundxversion+"',\n"

    with open("setup.py", "w") as f:
        f.writelines(setuplines)

shortversion = reboundxversion
while shortversion[-1] is not '.':
    shortversion = shortversion[:-1]
    
shortversion = shortversion[:-1]

with open("doc/conf.py") as f:
    conflines = f.readlines()
    for i,l  in enumerate(conflines):
        if "version =" in l:
            conflines[i] = "version = '"+shortversion+"'\n"
        if "release =" in l:
            conflines[i] = "release = '"+reboundxversion+"'\n"

    with open("doc/conf.py", "w") as f:
        f.writelines(conflines)
