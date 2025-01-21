#include "raylib.h"

#define MAP_WIDTH 28
#define MAP_HEIGHT 16


void difficultymode (int *hardness) {


InitAudioDevice();
SetTargetFPS(75);

Font font = LoadFontEx("font\\comic.ttf",96,0,0);
Vector2 Titlepos = {250,5};
Vector2 easypos = {390,100};
Vector2 mediumpos = {390,200};
Vector2 hardpos = {390,300};
Vector2 cirpos = {370,130};

Sound click =LoadSound("audio\\click.mp3");
Color pointer_color = GREEN;
Texture2D menubg = LoadTexture("texture\\menubg.jpg");


while (!WindowShouldClose())
{
   BeginDrawing();
   ClearBackground(BLACK);
   DrawTexture(menubg,100,20,WHITE);
   DrawTextEx(font,"::Select the difficulty of your game::",Titlepos,30,0,SKYBLUE);
   DrawTextEx(font,"::Easy::",easypos,50,0,GREEN);
   DrawTextEx(font ,"::Medium::",mediumpos,50,0,YELLOW);
   DrawTextEx(font,"::Hard::",hardpos,50,0,RED);

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
   
   if(cirpos.y==130) pointer_color = GREEN;
   if(cirpos.y==230) pointer_color = YELLOW ;
   if(cirpos.y==330) pointer_color = RED ;

   if((IsKeyPressed(KEY_ENTER) ||IsKeyPressed(KEY_KP_ENTER)) && cirpos.y==130) {
    *hardness=1 ;
    break;
   }
   if((IsKeyPressed(KEY_ENTER) ||IsKeyPressed(KEY_KP_ENTER)) && cirpos.y==230){ 
    *hardness=2 ;
    break;
   }
   if((IsKeyPressed(KEY_ENTER) ||IsKeyPressed(KEY_KP_ENTER)) && cirpos.y==330){
     *hardness=3 ;
     break;
   } 
}
UnloadSound(click);
UnloadTexture(menubg);
CloseAudioDevice();

}