cmake_minimum_required(VERSION 3.10)
project(20S-3353-PA00)
set (EXE_NAME SampleProject)

##########################################
# Students, edit the items below.  In the quotes,
# put the names of the input files as they should appear
# in the argv param to main.
# Example:
#   set (input01 "train_data.csv")
#   set (input02 "train_target.csv")
# etc....

set (input01 "g1.txt")
set (input02 "g2.txt")

#
##########################################

# Copy data files to build dir
foreach(file IN LISTS input01 input02)
    configure_file(${file} ${file} COPYONLY)
endforeach()

set(CMAKE_CXX_STANDARD 17)
add_executable(${EXE_NAME} main.cpp directedGraph.h disjointSetInterface.h weightedGraph.h trivialSoln.cpp trivialSoln.h robustSoln.cpp robustSoln.h)