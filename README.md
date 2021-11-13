# Running-Lizard 

This game is built with WinBGIm (Windows BGI - with mouse) graphics.h library v6.0
[Documentation](https://home.cs.colorado.edu/~main/cs1300/doc/bgi/ "WinBGIm Doc")

```
 # build the exe file (example)
 g++ -g app.cpp -o bin/Debug/"Running Lizard" -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32
 
 # run the exe file
 cd ./bin/Debug
 .\'Running Lizard.exe'
 ```

## Screenshots
> Stage 1
![stage_1](https://github.com/Md7tz/Running-Lizard/blob/master/Screenshots/stage_1/sc1.PNG)
![stage_1](https://github.com/Md7tz/Running-Lizard/blob/master/Screenshots/stage_1/sc2.PNG)

> Stage 2
![stage_2](https://github.com/Md7tz/Running-Lizard/blob/master/Screenshots/stage_2/sc1.PNG)
![stage_2](https://github.com/Md7tz/Running-Lizard/blob/master/Screenshots/stage_2/sc2.PNG)

### TODO
```
1.  [DONE] fix left wall to right transition border (make the lizard appear on the right side when position of head is on X is 0) 
2.  Add a life counter with a 3 image sprite 
3.  Create a poison class inherited from food class through polymorphism
4.  [Done] Add a popup message upon winning/losing with a retry prompt with the keystroke R (Keystroke Added without popup)
5.  instantiate more than one fruit(red apple) as an array of objects with randomized position
6.  instatiate one poisonous apple at a time (no array of objects needed)
7.  Fix First couple of tiles that has color filling issue
8.  [DONE] Change lizard color to blend
9.  [DONE] Add controls UI for the player
10. [DONE] Set max score to be 300 when the lizard reaches length of 32
11. [DONE] Add progressive speed
```

### Contribution
1. Create a branch with your name from master branch
2. Clone the repo to your local machine `git clone https://github.com/Md7tz/Running-Lizard.git`
3. Pull the latest changes `git pull`
4. Switch to your branch with `git branch BranchName` (your branch should have a *)
6. Add changes to your local repo with `git add .`
7. Commit your changes with a message declaring the changes `git commit -m "message"`
8. push changes to the remote repo on your branch `git push`
9. Create a pull request to the master branch and issue a review without merging


> Download [Github Desktop](https://desktop.github.com/ "Github Desktop") for easier workflow
<!-- > If you have any issues request a tutorial in a google meeting through my email [medhatusama@gmail.com](mailto:medhatusama@gmail.com) -->


**Important Notes** 
* run the same configuration provided in *.vscode* folder for vscode to avoid debugging issues
* Add [DONE] for every achievement in the todo list
* Do not merge with the master branch, only issue a pull request with revision
