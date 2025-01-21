#include "raylib.h"
#include <stdlib.h>
#include <time.h>

#define MAP_WIDTH 28
#define MAP_HEIGHT 16

char map[MAP_HEIGHT][MAP_WIDTH + 1] = {

    "############################",
    "#  #                    #  #",
    "# ##  ## # #    # # ##  ## #",
    "# #   ^#   #    #   #^  ^# #",
    "# # #### ########## #### # #",
    "#            ##            #",
    "#^## ### # ###### # ### ## #",
    "#^## ### # ###### # ### ##^#",
    "#^##   #     ##     #   ## #",
    "#^## #^# ### ## ### # # ## #",
    "# ##   #            #   ## #",
    "#    # ############## # ^^ #",
    "# ## #    #      #    # ## #",
    "# #  # #### ^    #### #  # #",
    "# #         ####         # #",
    "@@@@@@@@@@@@@@@@@@@@@@@@@@@@"};
    
char temp[MAP_HEIGHT][MAP_WIDTH+1] =
{

    "############################",
    "#  #                    #  #",
    "# ##  ## # #    # # ##  ## #",
    "# #   ^#   #    #   #^  ^# #",
    "# # #### ########## #### # #",
    "#            ##            #",
    "#^## ### # ###### # ### ##^#",
    "#^## ### # ###### # ### ##^#",
    "#^##  ^#     ##     #   ##^#",
    "#^## #^# ### ## ### # # ##^#",
    "# ##  ^#            #   ##^#",
    "#    #^############## # ^^^#",
    "# ## #    #      #    # ##^#",
    "# #  # #### ^    #### #  #^#",
    "# #         ####         #^#",
    "@@@@@@@@@@@@@@@@@@@@@@@@@@@@"};

char map2[MAP_HEIGHT][MAP_WIDTH + 1] = {

    "############################",
    "#  #                    #  #",
    "# ### ## # #    # # ## ### #",
    "# #    #   #    #   #    # #",
    "# # #### ########## #### # #",
    "#            ##            #",
    "# ## ### # ###### # ### ## #",
    "# ## ### # ###### # ### ## #",
    "# ##   #     ##     #   ## #",
    "# ## # # ### ## ### # # ## #",
    "# ##   #            #   ## #",
    "#    # ############## #    #",
    "# ## #    #      #    # ## #",
    "# #  # ####      #### #  # #",
    "# #         ####         # #",
    "@@@@@@@@@@@@@@@@@@@@@@@@@@@@"};

Color veryDarkBlue = (Color){ 0, 0, 70, 255};
Color DARKPINK = (Color){252,3,119,255};
Color random [5]= {GOLD,WHITE,BLUE,RED,GREEN};
void DrawMap(char board[MAP_HEIGHT][MAP_WIDTH+1],int index)
{   
    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            if (board[y][x] == '#')
            {
                DrawRectangle(x * 30, y * 30, 30, 30,veryDarkBlue);
                DrawRectangleLines(x*30,y*30,30,30,BLUE);
            }
            else if (board[y][x] == '.')
            {
                
                DrawCircle(x * 30 + 10, y * 30 + 10, 3.5, random[index]);
            }
            else if (board[y][x] == '@')
                DrawRectangle(x * 30, y * 30, 30, 30,DARKPINK);
            else if (board[y][x] == '0')
                DrawRectangle(x * 30, y * 30, 30, 30, ORANGE);
        }
    }
}


int dot_cnt(){

int result = 0;

    for (int i = 0; i <MAP_HEIGHT; i++)
    {
        for (int j = 0; j < MAP_WIDTH; j++)
        {
            if(map[i][j]=='.') result++;
        }
        
    }
  return result ;   
}


void put_randomdots(int dot_number){

srand(time(NULL));

int dot_added = 0;

while (dot_added<dot_number)
{
    int x = rand() % MAP_WIDTH  ;
    int y = rand() % MAP_HEIGHT ;

    if(map[y][x]==' ' && map[y][x]!='#' && map[y][x]!='^' ){

        map[y][x] = '.';
        dot_added++;
    }
}
}
