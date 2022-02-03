@REM old config: g++ app.cpp -o bin/production/"Running Lizard" -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32 -lwinmm  && bin\production\"Running Lizard"
@REM -mwindows flag hides console
@REM open the exe file after building in the root folder to work
g++ -std=c++17 -mwindows src/*.cpp -o bin/production/"Running-Lizard" -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -loleaut32 -lole32 -lwinmm && bin\production\"Running-Lizard"