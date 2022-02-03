# Running-Lizard

This game is built with WinBGIm (Windows BGI - with mouse) graphics.h library v6.0 [Documentation](https://home.cs.colorado.edu/~main/cs1300/doc/bgi/ "WinBGIm Doc")

> Development/Debugging

```
 # build the exe file
 g++ -g -std=c++17 src/*.cpp -o bin/Debug/Running-Lizard.exe -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32 -lwinmm
 
 # run the exe file
 cd ./bin/Debug
 .\'Running Lizard.exe'
```

> Production

```
 # build the exe file
 ./Build.bat
 ```

![Menu](https://github.com/Md7tz/Running-Lizard/blob/master/Screenshots/Game.PNG)
![Game](https://github.com/Md7tz/Running-Lizard/blob/master/Screenshots/Menu.PNG)