Open the graveler folder in VSCode and run the build task by holding Ctrl+Shift+P then entering 'tasks: run task' and selecting the build task 'C/C++: g++.exe build graveler.cpp'

(note: you must have the g++ compilier, or change the selected compiler for C++ in the tasks.json file)

After building, just run graveler.exe in Command Prompt from the graveler folder

The program doesn't have any dependencies so you can just use whatever C++ compiler from the command line instead, just be sure to enable the -O3 flag or equivalent
