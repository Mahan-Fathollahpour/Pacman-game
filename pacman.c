/*-------------------------------------------------------Pacman Project--------------------------------------------------*/
/*Author : Mahan Fathollahpourkami------------E_mail : Mahanpourkami@aut.ac.ir-------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------------------------------------------*/
/*Date : 10/01/2025------1:27 A.M---------------------------------------------------------------------------------------------------------*/

/*Include libraries - start*/

/*Standard libraries*/

#include <time.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

/*Custome libraries*/

#include "menu.h"
#include "raylib.h"
#include "getname.h"
#include "savescore.h"
#include "sortwrite.h"
#include "mapdrawer.h"
#include "difficulty.h"
#include "showrecords.h"
#include "deathscreen.h"

/*Include libraries - end */

/*Define Macros - start*/

#define MAP_WIDTH 28
#define MAP_HEIGHT 16

/*Define Macros - end  */

/*Define the structor of pacman*/
typedef struct Player
{
    Vector2 position;
    float radius;
    Color color;
} Player;

/*Define the structor of Ghosts*/
typedef struct Ghost
{
    Vector2 position;  // The position of ghosts that it includes x axis and y axis of that in float format
    Vector2 direction; // The Direction of ghosts movement includes up , down , left & right
    Color color;       // We simulate the ghosts as an cicle for checking the collisions of ghosts with walls and pacmnan and the color of that is constant and it's blank

} Ghost;

/*Define custome colors in the game Start*/
Color veryDarkOrange = (Color){255, 140, 0, 255};
/*Define custome colors in the game end */

/*Functions decelaration Start*/
Vector2 spawnfruitesrandom(); // None used
Vector2 distance_calculator(Ghost ghost , Player player);


bool CheckCollisionWithWalls(Vector2 position, float radius); // a function that check the collisions of pacman and ghosts with walls
void follower_ghost (Ghost *ghost , Player player , int speed);
void MoveGhost(Ghost *ghost, int speed);
void spawnghostrandom(Ghost *ghost); // ghost movements management

void death_animation(Texture2D result, Vector2 position, Player player, float angle); // this animation plays when the pacman lose the game

/*Functions decelration End */

typedef enum
{
    MAINMENU,
    GAME,
    GAME_OVER,
    RECORD
} GameState;

typedef enum
{
    CHER,
    NONE
} fruite;

/*Main Function Start*/
int main(void)
{

    /*Variables Declaration Start 1 */

    const int screenWidth = MAP_WIDTH * 30;
    const int screenHeight = MAP_HEIGHT * 30;
    char name[50];
    char msg[20];
    char name_buffer[50];
    int diff = 0;
    int x = 0;
    int counter = 0;
    int starnums = 0 ;
    double pacman_animation_timer = 0.0;
    int index = 0;
    double color_time = 0 ;

    /*Variables Declaration end  1 */






    InitWindow(screenWidth, screenHeight, "Mahan Pourkami PacMan"); // Initialazing the window of our game size : 840 * 500 || Title : Mahan Pourkami Pacman


    GameState gameState = MAINMENU; // define the defaul game state :: MAINMENU

    check_menu(&x); // Run the menu screen (Included from menu.h library)

    while (!WindowShouldClose()) // while we don't close the window or press the ESC key
    {
            Image wini = LoadImage("winicon.png");
            SetWindowIcon(wini);

        if (gameState == MAINMENU)
        {

            if (x == 1) // x==1 means that operator had choosed the start
            {

              /*Variables Declaration Start 2 */
                double estimated_time = 0.0; // the time value for time measuring for cherry fruite
                float speed_pacman = 2;      // the default pacman speed ( it increases if the pacman eat the pepper)
                int speed = 2;               // the default speed of ghosts (it can be decreased or increased by changing the difficulty of game)
                int hearts = 3;              // define the number of hearts 
                int score = 0;               // define the score of pacman 
                float angle = 0;             // define the angle of pacman's textures 
              /*Variables Declaration End   2 */

                get_name(name); // run the get name screen & save the name in name's string 

                difficultymode(&diff); // run the choose-difficulty-screen to define the difficulty mode (using call by reference)

                switch (diff)
                {
                case 1: // 1 : Easy

                    speed = 1;
                    estimated_time = 15.0;
                    starnums  = 15 ;
                    break;

                case 2: // 2 : Medium

                    speed = 2;
                    estimated_time = 10.0;
                    starnums = 10 ;
                    break;
                case 3: // 3: Hard

                    speed = 3;
                    estimated_time = 5.0;
                    starnums = 5 ;
                    break;

                default:

                    break;
                }

                // The game loop starts 

                gameState = GAME;
                fruite fru_state = NONE;


                InitAudioDevice(); // initialazing the Audio of device 

                Player player = {{400, 315}, 10, BLANK}; // define the pacman player 

                /*define Ghosts Start */
                Ghost ghost = {{400, 100}, {1, 1}, BLANK}; 
                Ghost blue = {{40, 100}, {1, 1}, BLANK};
                Ghost green = {{300, 260}, {1, 1}, BLANK};
                Ghost pink = {{360, 385}, {1, 1}, BLANK};
                Ghost wild = {{495, 420}, {1, 1}, BLANK};
                /*define Ghosts End */

                /*Define the Colors of textures*/
                Color h1 = WHITE, h2 = WHITE, h3 = WHITE, cherrycolor1 = WHITE, cherrycolor2 = WHITE, cherrycolor3 = WHITE, applecolor1 = GREEN, applecolor2 = GREEN, mashcolor1 = WHITE, mashcolor2 = WHITE, pepcolor1 = WHITE, pepcolor2 = WHITE;
                
                /*Loading fonts Start*/
                Font font = LoadFontEx("font\\comic.ttf", 96, 0, 0);
                 /*Loading fonts End*/

                /*Loading Textures Start*/

                Texture2D pac[4]; // An arraye of textures for pacman's animation

                pac[1] = LoadTexture("texture\\pacWide1.png");
                pac[2] = LoadTexture("texture\\pacNarrow1.png");
                pac[0] = LoadTexture("texture\\death2.png");
                pac[3] = LoadTexture("texture\\pacman4.png");

                Texture2D mons[2];

                mons[0] = LoadTexture("texture\\monster.png");
                mons[1] = LoadTexture("texture\\monster2.png");

              
                Texture2D gh = LoadTexture("texture\\blinky1.png");
                Texture2D bl = LoadTexture("texture\\orange.png");
                Texture2D gr = LoadTexture("texture\\inky1.png");
                Texture2D pi = LoadTexture("texture\\pink.png");
                Texture2D wi = LoadTexture("texture\\wild.png");
                Texture2D gh2 = LoadTexture("texture\\blinky1.png");
                Texture2D bl2 = LoadTexture("texture\\orange.png");
                Texture2D gr2 = LoadTexture("texture\\inky1.png");
                Texture2D pi2 = LoadTexture("texture\\pink.png");
                Texture2D wi2 = LoadTexture("texture\\wild.png");
                Texture2D cherry = LoadTexture("texture\\cherry.png");
                Texture2D heart = LoadTexture("texture\\heart.png");
                Texture2D apple = LoadTexture("texture\\apple.png");
                Texture2D mashroom = LoadTexture("texture\\mashroom.png");
                Texture2D pepper = LoadTexture("texture\\pepper.png");
                Texture2D person = LoadTexture("texture\\Person.png");


                /*Loading Textures End*/

                /*Define Position Start*/

                Vector2 socrpos = {16, 455};
                Vector2 datepos = {650, 460};

                /*Define Position End */


                /*Loading Sounds Start*/
                Sound start = LoadSound("audio\\pacman_beginning.wav");
                Sound eat = LoadSound("audio\\pacman_eatfruit.wav");
                Sound chomp = LoadSound("audio\\pacman_chomp.wav");
                Sound eatapple = LoadSound("audio\\apple_eat.mp3");
                Sound eatmash = LoadSound("audio\\mashroom.mp3");
                Sound gameover = LoadSound("audio\\gameover.mp3");
                Sound endtime = LoadSound("audio\\timeend.mp3");
                /*Loading Sounds End*/

                SetTargetFPS(75); //Refresh rate : 75 Hz

                Vector2 last_position; // the position of pacman befor collision with walls 

                PlaySound(start); // play the start-up sound of pacman game 

                for (int i = 0; i < MAP_HEIGHT; i++)  // get a backup from map 
                    strcpy(map[i], temp[i]);

              /*Variables Declaration Start 3 */
              
                double cherry_time = -20.0;
                double monster_time = 0.0 ;
                int mons_cnt = 0; 
                bool eat_cherry_1  =  false;
                bool eat_cherry_2  =  false;
                bool eat_cherry_3  =  false;
                bool eat_apple_1   =  false;
                bool eat_apple_2   =  false;
                bool eat_mashroom1 =  false;
                bool eat_mashroom2 =  false;
                bool eat_pepper_1  =  false;
                bool eat_pepper_2  =  false;


                 /*Variables Declaration End 3 */

                 /*Game loop start*/

                while (gameState == GAME && !WindowShouldClose())
                {

                    int remaining_dot = dot_cnt(); //count the number of stars of the map (at first it's zero)

                    if (!remaining_dot)   // if the number of stars was zero it draw 10 stars randomly in map 
                    {
                        put_randomdots(starnums);  
                        remaining_dot = dot_cnt(); // update the number of stars
                    }
                
                /*Setup the ghosts Movement Start*/
                  

                    MoveGhost(&ghost,speed);
                    MoveGhost(&blue, speed);
                    MoveGhost(&pink, speed);
                    MoveGhost(&wild, speed);

                    if(diff==1)MoveGhost(&green,speed);
                    else if (diff == 2)follower_ghost(&green,player,1);
                    else follower_ghost(&green,player,2);
                /*Setup the ghosts Movement End*/

                /*Check the collision of pacman with fruites and ghosts  Start*/

                    if (eat_cherry_1 == false && (int)(player.position.x / 30) == 13 && (int)(player.position.y / 30) == 13)
                    {

                        PlaySound(chomp);
                        fru_state = CHER;
                        cherrycolor1 = BLANK;
                        cherry_time = GetTime();
                        eat_cherry_1 = true;
                    }

                    if (eat_cherry_2 == false && (int)(player.position.x / 30) == 26 && (int)(player.position.y / 30) == 6)
                    {

                        PlaySound(chomp);
                        fru_state = CHER;
                        cherrycolor2 = BLANK;
                        cherry_time = GetTime();
                        eat_cherry_2 = true;
                    }

                    if (eat_cherry_3 == false && (int)(player.position.x / 30) == 1 && (int)(player.position.y / 30) == 9)
                    {

                        PlaySound(chomp);
                        fru_state = CHER;
                        cherrycolor3 = BLANK;
                        cherry_time = GetTime();
                        eat_cherry_3 = true;
                    }

                    if (eat_apple_1 == false && (int)(player.position.x / 30) == 24 && (int)(player.position.y / 30) == 3 && hearts != 3)
                    {

                        hearts++;
                        PlaySound(eatapple);
                        applecolor1 = BLANK;
                        eat_apple_1 = true;
                    }

                    if (eat_apple_2 == false && (int)(player.position.x / 30) == 6 && (int)(player.position.y / 30) == 3 && hearts != 3)
                    {

                        hearts++;
                        PlaySound(eatapple);
                        applecolor2 = BLANK;
                        eat_apple_2 = true;
                    }

                    if (eat_mashroom1 == false && (int)(player.position.x / 30) == 6 && (int)(player.position.y / 30) == 9)
                    {

                        hearts--;
                        PlaySound(eatmash);
                        mashcolor1 = BLANK;
                        eat_mashroom1 = true;
                    }

                    if (eat_mashroom2 == false && (int)(player.position.x / 30) == 21 && (int)(player.position.y / 30) == 3)
                    {

                        hearts--;
                        PlaySound(eatmash);
                        mashcolor2 = BLANK;
                        eat_mashroom2 = true;
                    }

                    if (eat_pepper_1 == false && (int)(player.position.x / 30) == 12 && (int)(player.position.y / 30) == 5)
                    {

                        speed_pacman += 1.0f;
                        eat_pepper_1 = true;
                        pepcolor1 = BLANK;
                    }

                    if (eat_pepper_2 == false && (int)(player.position.x / 30) == 25 && (int)(player.position.y / 30) == 11)
                    {

                        speed_pacman += 1.0f;
                        eat_pepper_2 = true;
                        pepcolor2 = BLANK;
                    }

                     /*Check the collision of pacman with fruites and ghosts  End*/

                    /*Timer's measuring start*/
                    if (GetTime() - cherry_time > estimated_time + 2.0)
                    {
                        fru_state = NONE;
                        gh = gh2;
                        bl = bl2;
                        gr = gr2;
                        pi = pi2;
                        wi = wi2;
                    }
                    else if (GetTime() - cherry_time >= estimated_time && GetTime() - cherry_time <= estimated_time + 2.0)
                        PlaySound(endtime);
                                                                            
                    else if (GetTime() - cherry_time < estimated_time)
                    {
                        if(GetTime()-monster_time >= 0.3){
                         
                        // for blinking animation of monsters 
                        mons_cnt++;
                        gh = bl = gr = pi = wi = mons[counter%2];
                        monster_time = GetTime();
                        }
                    }

                
                     if(GetTime()-color_time >=1.0){
                        // for changing the color of stars
                         index++;
                         color_time = GetTime();
                     }

                      /*Timer's measuring start*/
                    if (CheckCollisionWithWalls(player.position, player.radius) == false)
                    {
                        last_position = player.position;
                        if (IsKeyDown(KEY_RIGHT))
                        {
                            player.position.x += speed_pacman;
                            angle = 0.0;
                        }
                        if (IsKeyDown(KEY_LEFT))
                        {
                            player.position.x -= speed_pacman;
                            angle = 180;
                        }
                        if (IsKeyDown(KEY_UP))
                        {
                            player.position.y -= speed_pacman;
                            angle = -90;
                        }
                        if (IsKeyDown(KEY_DOWN))
                        {
                            player.position.y += speed_pacman;
                            angle = 90;
                        }
                        if (map[(int)player.position.y / 30][(int)player.position.x / 30] == '.')
                        {
                            score += 10;
                            map[(int)player.position.y / 30][(int)player.position.x / 30] = ' ';
                            PlaySound(eat);
                        }
                    }

                    else player.position = last_position;

                    char time_buf[30];
                    time_t current;
                    time(&current);
                    Texture2D result;
                    
                   /* Check the collision with ghosts start :*/
                    if ((int)(player.position.x / 25) == (int)(ghost.position.x / 25) && (int)(player.position.y / 25) == (int)(ghost.position.y /25))
                    {

                        if (fru_state != CHER)
                        {

                            PlaySound(gameover);
                            death_animation(result, player.position, player, angle);
                            hearts--;
                            player.position = (Vector2){400, 315};
                        }
                        else
                        {
                            PlaySound(chomp);
                            score += 200;
                        }
                        spawnghostrandom(&ghost);
                    }

                    if ((int)(player.position.x / 25) == (int)(blue.position.x / 25) && (int)(player.position.y / 25) == (int)(blue.position.y / 25))
                    {

                        if (fru_state != CHER)
                        {

                            hearts--;
                            PlaySound(gameover);
                            death_animation(result, player.position, player, angle);
                            player.position = (Vector2){400, 315};
                        }
                        else
                        {
                            PlaySound(chomp);
                            score += 200;
                        }
                        spawnghostrandom(&blue);
                    }

                    if ((int)(player.position.x / 25) == (int)(pink.position.x / 25) && (int)(player.position.y / 25) == (int)(pink.position.y / 25))
                    {

                        if (fru_state != CHER)
                        {
                            hearts--;
                            PlaySound(gameover);
                            death_animation(result, player.position, player, angle);
                            player.position = (Vector2){400, 315};
                        }

                        else
                        {
                            PlaySound(chomp);
                            score += 200;
                        }
                        spawnghostrandom(&pink);
                    }

                    if ((int)(player.position.x / 25) == (int)(green.position.x / 25) && (int)(player.position.y / 25) == (int)(green.position.y / 25))
                    {

                        if (fru_state != CHER)
                        {
                            hearts--;
                            PlaySound(gameover);
                            death_animation(result, player.position, player, angle);
                            player.position = (Vector2){400, 315};
                        }

                        else
                        {
                            PlaySound(chomp);
                            score += 200;
                        }
                        spawnghostrandom(&green);
                    }

                    if ((int)(player.position.x / 25) == (int)(wild.position.x / 25) && (int)(player.position.y / 25) == (int)(wild.position.y / 25))
                    {

                        if (fru_state != CHER)
                        {

                            PlaySound(gameover);
                            death_animation(result, player.position, player, angle);
                            hearts--;
                            player.position = (Vector2){400, 315};
                        }

                        else
                        {
                            PlaySound(chomp);
                            score += 200;
                        }
                        spawnghostrandom(&wild);
                    }

                    /* Check the collision with ghosts end */

                    if (GetTime() - pacman_animation_timer >= 0.1)
                    {
                        counter++;
                        result = pac[counter % 4];
                        pacman_animation_timer = GetTime();
                    }

                    ClearBackground(BLACK);
                    sprintf(time_buf, "Time : %s", ctime(&current));
                    sprintf(msg, "Your score : %.3d", score);
                    sprintf(name_buffer, "Player : %s", name);
                    BeginDrawing();
                    DrawMap(map,index%5);
                    DrawTextEx(font, msg, socrpos, 20, 0, WHITE);
                    DrawTextEx(font, name_buffer, datepos, 20, 0, WHITE);
                    DrawTexture(gh, ghost.position.x - 10, ghost.position.y - 10, WHITE);
                    DrawTexture(bl, blue.position.x - 10, blue.position.y - 10, WHITE);
                    DrawTexture(gr, green.position.x - 10, green.position.y - 10, WHITE);
                    DrawTexture(pi, pink.position.x - 10, pink.position.y - 10, WHITE);
                    DrawTexture(wi, wild.position.x - 10, wild.position.y - 10, WHITE);

                    DrawTexture(cherry, 360, 385, cherrycolor1);
                    DrawTexture(cherry, 780, 180, cherrycolor2);
                    DrawTexture(cherry, 30, 270, cherrycolor3);

                    DrawTexture(apple, 720, 92, applecolor1);
                    DrawTexture(apple, 180, 92, applecolor2);

                    DrawTexture(mashroom, 185, 270, mashcolor1);
                    DrawTexture(mashroom, 630, 92, mashcolor2);

                    DrawTexture(pepper, 360, 150, pepcolor1);
                    DrawTexture(pepper, 750, 330, pepcolor2);

                    DrawTexture(heart, 360, 445, h1);
                    DrawTexture(heart, 400, 445, h2);
                    DrawTexture(heart, 440, 445, h3);

                    DrawTexture(person, 600, 460, BLUE);

                    DrawCircleV(player.position, player.radius, player.color);
                    DrawCircleV(ghost.position, 10, ghost.color);
                    DrawCircleV(blue.position, 10, blue.color);

                    Rectangle sourceRec = {0.0f, 0.0f, (float)result.width, result.height};
                    Rectangle destRec = {player.position.x, player.position.y, result.width, result.height};

                    Vector2 origin = {result.width / 2.0f, result.height / 2.0f};

                    DrawTexturePro(result, sourceRec, destRec, origin, angle, WHITE);

                    

                    

                    switch (hearts)
                    {
                    case 3:
                        h1 = WHITE;
                        h2 = WHITE;
                        h3 = WHITE;
                        break;

                    case 2:
                        h1 = WHITE;
                        h2 = WHITE;
                        h3 = BLANK;
                        break;
                    case 1:

                        h1 = WHITE;
                        h2 = BLANK;
                        h3 = BLANK;
                        break;

                    case 0:
                        
                        save_score(name, score);
                        getsocres();
                        gameState = GAME_OVER;
                        break;
                    }

                    EndDrawing();
                }
                UnloadTexture(pac[0]);
                UnloadTexture(pac[1]);
                UnloadTexture(pac[2]);
                UnloadTexture(gh);
                UnloadTexture(bl);
                UnloadTexture(gr);
                UnloadTexture(pi);
                UnloadTexture(cherry);
                UnloadTexture(heart);
                UnloadFont(font);
                UnloadSound(start);
                UnloadSound(eat);

                CloseAudioDevice();
            }
            else if (x == 2)
                gameState = RECORD;

            else if (x == 3)
                break;
        }

        else if (gameState == GAME_OVER)
        {

            BeginDrawing();
            ClearBackground(BLACK);
            deathscreen();
            Font font = LoadFontEx("font\\comic.ttf", 96, 0, 0);
            DrawTextEx(font, msg, (Vector2){350, 200}, 30, 0, SKYBLUE);
            DrawTextEx(font, name_buffer, (Vector2){350, 300}, 30, 0, SKYBLUE);

            EndDrawing();

            if (IsKeyPressed(KEY_ENTER))
            {
                gameState = MAINMENU;
                check_menu(&x);
            }
        }

        else if (gameState == RECORD)
        {
            BeginDrawing();
            show_point();
            EndDrawing();
            if (IsKeyPressed(KEY_ENTER))
            {
                gameState = MAINMENU;
                check_menu(&x);
            }
        }
    }
    CloseWindow();
    return 0;
}

bool CheckCollisionWithWalls(Vector2 position, float radius)
{
    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            if (map[y][x] == '#' || map[y][x] == '@')
            {
                Rectangle wall = {x * 30, y * 30, 30, 30};
                if (CheckCollisionCircleRec(position, radius, wall))
                {
                    return true;
                }
            }
        }
    }
    return false;
}

void UpdateGhostDirection(Ghost *ghost)
{
    int random = GetRandomValue(0, 3);

    switch (random)
    {
    case 0:
        ghost->direction = (Vector2){1, 0};
        break;
    case 1:
        ghost->direction = (Vector2){-1, 0};
        break;
    case 2:
        ghost->direction = (Vector2){0, 1};
        break;
    case 3:
        ghost->direction = (Vector2){0, -1};
        break;
    }
}

void MoveGhost(Ghost *ghost, int speed)
{
    Vector2 nextPosition = (Vector2){ghost->position.x + ghost->direction.x * speed, ghost->position.y + ghost->direction.y * speed};

    if (CheckCollisionWithWalls(nextPosition, 10)==true)
    {
        UpdateGhostDirection(ghost);
    }
    else
    {
        ghost->position = nextPosition;
    }
}

void spawnghostrandom(Ghost *ghost)
{

    srand(time(NULL));

    int x, y;

    do
    {

        x = rand() % MAP_WIDTH;
        y = rand() % MAP_HEIGHT;
    } while (map[y][x] != ' ');

    ghost->position = (Vector2){x * 30 + 10.2, y * 30 + 10.2};
}

void death_animation(Texture2D result, Vector2 position, Player player, float angle)
{

    Texture2D death[11];

    death[0] = LoadTexture("texture\\death 1.png");
    death[1] = LoadTexture("texture\\death 2.png");
    death[2] = LoadTexture("texture\\death 3.png");
    death[3] = LoadTexture("texture\\death 4.png");
    death[4] = LoadTexture("texture\\death 5.png");
    death[5] = LoadTexture("texture\\death 6.png");
    death[6] = LoadTexture("texture\\death 7.png");
    death[7] = LoadTexture("texture\\death 8.png");
    death[8] = LoadTexture("texture\\death 9.png");
    death[9] = LoadTexture("texture\\death 10.png");
    death[10] = LoadTexture("texture\\death 11.png");

    for (int i = 0; i < 11; i++)
    {
        BeginDrawing();
        result = death[i];
        Rectangle sourceRec = {0.0f, 0.0f, (float)result.width, result.height};
        Rectangle destRec = {player.position.x, player.position.y, result.width, result.height};
        Vector2 origin = {result.width / 2.0f, result.height / 2.0f};
        DrawTexturePro(result, sourceRec, destRec, origin, angle, WHITE);
        WaitTime(0.15);
        EndDrawing();
    }
}

Vector2 distance_calculator(Ghost ghost , Player player){

double distance_x = player.position.x - ghost.position.x  ;
double distance_y = player.position.y - ghost.position.y  ;

double dx = distance_x / fabs(distance_x);
double dy = distance_y / fabs(distance_y);

return (Vector2){dx,dy};

}

void follower_ghost (Ghost *ghost , Player player , int speed){

Vector2 newdir = distance_calculator(*ghost,player);

Vector2 newposx ={ghost->position.x + newdir.x * speed ,ghost->position.y};
Vector2 newposy ={ghost->position.x , ghost->position.y + newdir.y * speed};



if(((newdir.x<=newdir.y || CheckCollisionWithWalls(newposy,10)==true) && CheckCollisionWithWalls(newposx,8)==false ) || (newdir.y<=newdir.x && CheckCollisionWithWalls(newposy,10)==false )){

        ghost->position = newposx;
}

if(((newdir.y<newdir.x || CheckCollisionWithWalls(newposx,10)==true) && CheckCollisionWithWalls(newposy,8)==false )|| (newdir.x<newdir.y && CheckCollisionWithWalls(newposx,10)==false )){

        ghost->position = newposy;
}


}
