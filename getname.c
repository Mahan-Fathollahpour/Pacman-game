#include "raylib.h"
#include <stdbool.h>
#include <string.h>


void get_name(char *input ){

char name[50] = ""; 
int letterCount = 0; 
bool enterPressed = false;


 SetTargetFPS(75); 

Texture2D menubg = LoadTexture("texture\\menubg.jpg");
Font font = LoadFontEx("font\\comic.ttf",96,0,0);

 while (!WindowShouldClose()) {

    if (!enterPressed) { 
    int key = GetCharPressed();

    while (key > 0) { 
      if ((key >= 48) && (key <= 122) && (letterCount < 50))
       { 

        name[letterCount] = (char)key; 
        name[letterCount + 1] = '\0'; 
        letterCount++;
        
        }
        
        key = GetCharPressed(); 
     }

if (IsKeyPressed(KEY_BACKSPACE)) {
      if (letterCount > 0) {
     letterCount--; 
     name[letterCount] = '\0';
    }
    }

if (IsKeyPressed(KEY_SPACE)) {
    enterPressed = true; 
    } 
    }  

    BeginDrawing(); 
    ClearBackground(BLACK); 
    DrawTexture(menubg,100,20,WHITE);
    DrawRectangle(300,200,300,40,DARKGRAY);

    if (enterPressed) {
      break;
      }
      else {

      DrawTextEx(font,"Please Enter Your Name (only Alphabats)",(Vector2){190,100},30,0,WHITE);
      DrawTextEx(font,"Press Space to confirm",(Vector2){330,400},25,0,WHITE);
      DrawTextEx(font,name,(Vector2){400,200},30,0,SKYBLUE);

   } 
         EndDrawing();
      } 
    strcpy(input,name);
 }