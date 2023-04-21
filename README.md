# KSP_Station_Manager
Program to keep track of Space Stations in KSP/KSP2

## Basic Info
Author: Charles Haines
Language: C++
Build System: cmake
Supported Operating Systems: Linux, Windows, OSX

# Introduction
This is just a simple command line application that manages a list of Space Stations in KSP2. It stores basic information about a space station such as the name, a station ID, capacity, number and types of docking ports and communication devices. The stations can be written to and read to a json file.

This is an interactive command line application but it does support one command line option: -i <filename> which will dump a plain text listing of the station info. It will automatically pull in stations from the default filename, station.json in the same directory as the executable. The filename supplied in the -i option is the output file name. The input file is always station.json. This will be updated at some point so the input filename can be specified as well. Not supplying a filename to the -i argument will save the file as stations.txt in the directory of the executable.


