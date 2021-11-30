to compile any cpp file present in root, 
from root => 

g++ <filename.cpp> -o <name in which exe file will be saved>

to run the compiled exe file, from the root folder:
start <name of exe file>

to make sure command prompt doesnt shut down as soon as program is executed,
add this line just before return in main:

system("pause");
