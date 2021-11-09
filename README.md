# Running-Lizard 

This game is built with WinBGIm (Windows BGI - with mouse) graphics.h library v6.0

```
 # build the exe file
 g++ -g app.cpp -o bin/Debug/"Running Lizard" -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32
 # run the exe file
 cd ./bin/Debug
 .\'Running Lizard.exe'
 ```

## Screenshots
![ScreenShot_1](https://github.com/Md7tz/Running-Lizard/blob/master/Screenshots/sc1.PNG)

### TODO
```
1. fix left wall to right transition border (make the lizard appear on the right side when position of head is on X is 0)
2. Add a life counter with a 3 image sprite 
3. Create a poison class inherited from food class through polymorphism
4. Add a popup message upon winning/losing with a retry prompt with the keystroke R (Keystroke Added without popup)
```

**Note** run the same configuration provided in *.vscode* folder for vscode to avoid debugging issues
