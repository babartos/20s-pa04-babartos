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

set (input01 "data01.txt")
set (input02 "g1_smallGraph_lowDensity.txt")
set (input03 "g2_smallGraph_medDensity.txt")
set (input04 "g3_smallGraph_highDensity.txt")
set (input05 "g4_medGraph_lowDensity.txt")
set (input06 "g5_medGraph_medDensity.txt")
set (input07 "g6_medGraph_highDensity.txt")
set (input08 "g7_largeGraph_lowDensity.txt")
set (input09 "g8_largeGraph_medDensity.txt")
set (input10 "g9_largeGraph_highDensity.txt")
set (input11 "g10_largeGraph_vhighDensity.txt")

#
##########################################

# Copy data files to build dir
foreach(file IN LISTS input01 input02 input03 input04 input05 input06 input07 input08 input09 input10 input11)
    configure_file(${file} ${file} COPYONLY)
endforeach()

set(CMAKE_CXX_STANDARD 17)
add_executable(${EXE_NAME} main.cpp graph.h disjointSetInterface.h linkedListDisjointSet.h weightedGraph.h kruskal.h customDisjointSet.h)