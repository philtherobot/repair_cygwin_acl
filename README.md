# Repair file ACLs broken by Cygwin

This tool repairs the access control lists on files.  ACLs
then be broken by an incorrect cygwin configuration.

This tool must be executed as Windows program (not as a
program of the cygwin platform) to ensure its successful
execution.

# Dependencies

Microsoft Visual Studio 2017

# Build

- Launch MSVC environment shell.
- cl /std:c++latest /EHsc /W4 rcygacl.cpp
