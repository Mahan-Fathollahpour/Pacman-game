#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char name[50];
    int score; 
    int year;
    int month;
    int day;
} record; 

void swap(record *a, record *b) {
    record temp = *a;
    *a = *b;
    *b = temp;
}

void sort(record list[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {  
            if(list[i].score < list[j].score) {
                swap(&list[i], &list[j]);
            }
        }   
    }
}

int readlines(char *filename) {
    FILE *fptr = fopen(filename, "r");
    if (fptr == NULL) {
        perror("Failed to open file");
        return 0; 
    }

    int counter = 0;
    char c; 

    while ((c = fgetc(fptr)) != EOF) {
        if(c == '\n') counter++;
    }
    fclose(fptr);
    return counter + 1;
}

void getsocres() {
    FILE *input = fopen("save\\score.txt", "r");
    if (input == NULL) {
        perror("Failed to open file");
        return;  
    }
    int index = readlines("save\\score.txt");
    record list[index];

    for (int i = 0; i < index; i++) {
        fscanf(input, " %49s %d %d %d %d", list[i].name, &list[i].score, &list[i].year, &list[i].month, &list[i].day);
    }

    sort(list, index);

    FILE *output = fopen("save\\new.txt", "w");
    if (output == NULL) {
        perror("Failed to open file");
        return; 
    }

    for (int i = 1; i < index; i++) {  
        fprintf(output, "%s %d %d %d %d\n", list[i].name, list[i].score, list[i].year, list[i].month, list[i].day);
    }

    fclose(output);
    fclose(input);  
}
