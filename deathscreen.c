#include "raylib.h"


void deathscreen(){

Vector2 textpos = {300 , 100};
Texture2D menubg = LoadTexture("texture\\menubg.jpg");
Font font = LoadFontEx("font\\comic.ttf", 96, 0, 0);
DrawTexture(menubg,100,20,WHITE);
DrawTextEx(font,"You Lose the Game !",textpos,50,0,YELLOW);
DrawTextEx(font,"Press Enter to return to The Menu",(Vector2){300,400},25,0,WHITE);



}