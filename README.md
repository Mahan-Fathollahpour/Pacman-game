# Pacman-game
a simple pacman game , created with c and raylib

![pacman-readme](https://github.com/user-attachments/assets/4db22f4b-978f-48ac-99d1-7b99e4b03088)

Download Raylib via this link : <a href="https://raysan5.itch.io/raylib/purchase?popup=1">download</a>

<h2>Ghosts movement modes :</h2>

<h3> 1 . Following the pacman</h3>

```C
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
```

<h3> 2 . Moving randomly</h3>

```C
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
```
pacman.c is the main file

<h1>Developer :</h1>

<h3>Mahan Fathollahpour</h3>



