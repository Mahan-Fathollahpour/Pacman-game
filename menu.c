#include "raylib.h"


#define MAP_WIDTH 28
#define MAP_HEIGHT 16

const int screenWidth = MAP_WIDTH * 30;

const int screenHeight = MAP_HEIGHT * 30;

void check_menu(int *mode){


InitAudioDevice();
SetTargetFPS(75);
Font font = LoadFontEx("font\\comic.ttf",96,0,0);
Vector2 startpos = {390,100}; 
Vector2 exitpos = {390,300};
Vector2 boardpos = {390,200};
Vector2 cirpos = {370,130};
Sound sound = LoadSound("audio\\lastofus.mp3");
Sound click = LoadSound("audio\\click.mp3");
Color pointer_color = YELLOW;
Texture2D menubg = LoadTexture("texture\\menubg.jpg");
PlaySound(sound);
while (!WindowShouldClose())
{

    BeginDrawing();
    ClearBackground(BLACK);
    DrawTexture(menubg,100,20,WHITE);
    DrawTextEx(font,"::Start::",startpos,50,0,YELLOW);
    DrawTextEx(font,"::Records::",boardpos,50,0,BLUE);
    DrawTextEx(font,"::Exit::",exitpos,50,0,RED);

    DrawText("Developed by Mahan Pourkami",300,450,20,SKYBLUE);

    DrawCircleV(cirpos,4,pointer_color);

    EndDrawing();
    if(IsKeyPressed(KEY_DOWN)&&cirpos.y<330) {
        PlaySound(click);
        cirpos.y+=100 ;
        }  
    if(IsKeyPressed(KEY_UP)&&cirpos.y>130){
        cirpos.y-=100; 
        PlaySound(click);
    }
    if(cirpos.y==130) pointer_color=YELLOW;
    if(cirpos.y==330) pointer_color=RED;
    if(cirpos.y==230) pointer_color=BLUE;
    
    if(IsKeyPressed(KEY_ENTER) && cirpos.y==130){
        *mode =1;
        break;
        }
    if(IsKeyPressed(KEY_ENTER)&& cirpos.y==230) {
        *mode =2 ;
         break;
    }
    if(IsKeyPressed(KEY_ENTER)&& cirpos.y==330) {
        *mode = 3 ;
         break; 
    }

}
UnloadSound(sound);
UnloadTexture(menubg);
CloseAudioDevice();

}
