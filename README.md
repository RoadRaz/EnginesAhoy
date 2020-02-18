# EnginesAhoy
Repository to track Game Engine Development

Steps to download and setup SDL using Visual Studio:
(I don't think you guys have to do this because I would be including the downloaded SDL package in the repo and also have things in place as needed. But I'll still leave this here.)
1) Go to http://libsdl.org/
2) Under 'Download' Tab on the left, select 'SDL 2.0'
3) Select 'SDL2-devel-2.0.10-VC.zip (Visual C++ 32/64-bit)' under 'Development Libraries'
4) Save the downloaded folder somewhere safe
5) Create a new Visual Studio C++ Console Application/Empty Project
6) Right click the project name and go to 'Properties'
	a) Under C/C++, General -> Additional Include Directories : Specify the path to the include folder in the SDL folder downloaded from http://libsdl.org/
	b) Under Linker, General -> Additional Library Directories : Specify the path to the x86 folder in the SDL folder downloaded from http://libsdl.org/
	c) Under Linker, Input -> Additional Dependencies : Add 'SDL2.lib' and 'SDL2main.lib' to the list separated with semi-colons
7) Finally go to /lib/x86 in the downloaded folder and copy 'SDL2.dll' file, and paste in the same folder that has your 'Main.cpp' file
8) Try running the existing code. EZ!