//#include <graphics.h>
//
//#include <iostream>
//
//int screen_width = 1280;
//int screen_height = 720;
//
//int main()
//{
//    initgraph(screen_width, screen_height);
//
//    int x = 300;
//    int y = 300;
//    int r = 50;
//
//    BeginBatchDraw();
//    while (true)
//    {
//        
//        ExMessage msg;
//        while (peekmessage(&msg))
//        {   
//            if (msg.message == WM_MOUSEMOVE) 
//            {
//                x = msg.x;
//                y = msg.y;
//            }
//        }
//
//        cleardevice();
//        solidcircle(x, y, r);
//        FlushBatchDraw();
//    }
//    EndBatchDraw();
//}