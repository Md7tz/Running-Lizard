// Deprecated
// #include <graphics.h>
// #include <iostream>
// using namespace std;
// class menu
// {
// private:
// 	int x, y, x2, y2, xW, yW;
// public:
// 	void start(int,int,int,int);

// };
// void menu::start(int _x,int _y, int _x2, int _y2)
// {
//     x=_x;
//     y=_y;
//     x2=_x2;
//     y2=_y2;
//     rectangle(x, y, x2, y2);
//     settextstyle(BOLD_FONT, HORIZ_DIR, 3);
//     outtextxy(348, 315, "start");
//     while (!ismouseclick(WM_LBUTTONDOWN))
//     {
//         delay(1000);
//     }
//     int xMouse, yMouse;
//     bool start = true;
//     while (start)
//     {
//         if (ismouseclick(WM_LBUTTONDOWN))
//         {
//             getmouseclick(WM_LBUTTONDOWN, xMouse, yMouse);
//             cout << xMouse << " " << yMouse<<endl;
//             cout<<x<<" "<<y<<endl;
//             if ((xMouse >= x && xMouse <= x2) && (yMouse >= y && yMouse <= y2))
//             {
//                 cout<<"hi";
//                 settextstyle(BOLD_FONT, HORIZ_DIR, 3);
//                 outtextxy(270, 250, "ok");
//                 start = false;
//                 break;
//             }
//         }
//     }
// }
