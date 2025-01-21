#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
    int score;
    int year ;
    int month ;
    int day ;
} Points;

void show_point() {
    
    Points list[10]; 
    char msgbuff[500] = ""; 
    FILE *fptr = fopen("save\\new.txt", "r");
    Font font = LoadFont("font\\comic.ttf");
    Texture2D menubg = LoadTexture("texture\\menubg.jpg");
    SetTargetFPS(75);
      

    int count = 0; 
    while (count < 10 && fscanf(fptr, "%49s %d %d %d %d", list[count].name, &list[count].score,&list[count].year , &list[count].month , &list[count].day)  > 0) {
        count++;
    }
    fclose(fptr);

    for (int i = 0; i < count; i++) {
        char buffer[100];
        sprintf(buffer, "%10s   %d :: %.4d / %.2d /%.2d \n", list[i].name, list[i].score,list[i].year,list[i].month,list[i].day);
        strcat(msgbuff, buffer);
    }


        ClearBackground(BLACK);
        DrawTexture(menubg,100,20,WHITE);
        DrawTextEx(font,msgbuff,(Vector2){300,100},25,0,WHITE);
        DrawTextEx(font,"Press Enter to return to The Menu",(Vector2){300,400},25,0,WHITE);

}
