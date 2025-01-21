# Pacman-game
a simple pacman game , created with c and raylib

![pacman-readme](https://github.com/user-attachments/assets/4db22f4b-978f-48ac-99d1-7b99e4b03088)

<h2>Ghosts movement modes :</h2>

<h3> 1 . Moving randomly</h3>

```
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



<h3> 2 . Following the pacman</h3>


