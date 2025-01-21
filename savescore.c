#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


void save_score(char *name , int point) {

FILE *score ;
score= fopen("save\\score.txt","a+");
char buffer[100];
time_t now ;
struct tm *local_time ;
time(&now);
local_time = localtime(&now);
int year = local_time->tm_year+1900;
int month = local_time->tm_mon+1;
int day = local_time->tm_mday;


sprintf(buffer,"%s %d %d %d %d\n",name,point,year,month,day);
fprintf(score,buffer);
fclose(score);


}

