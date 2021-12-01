to compile any cpp file present in root, 
from root => 

g++ <filename.cpp> -o ./build/<name in which exe file will be saved>


adding ./build/ will create the exe file in build folder, which is git ingored

to run the compiled exe file, from the root folder:
start ./build/<name of exe file>

to make sure command prompt doesnt shut down as soon as program is executed,
add this line just before return in main:

system("pause");


if not compiling, make sure command prompt is not already open