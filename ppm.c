#include "ppm.h"
#include <stdio.h>
#include <assert.h>

int read_header (FILE* fichier, int* hauteur, int* largeur){
    char* s;
    fscanf(fichier, "%s", s);
    printf("%s", s);
    char poubelle;
    char c = '0';
    int width = 0;
    fscanf(fichier, "%c", &poubelle);
    while (c != 32 && c != 13 && c != 10 && c != 9){
        printf("%d\n", c - '0');
        width = 10*width + c - '0';
        fscanf(fichier, "%c", &c);
    }
    printf("%d", width);
    return 1;
}

int main(){
    char* f_n = "sample_1920×1280.ppm";
    FILE* f = fopen(f_n,"r");
    int hauteur;
    int largeur;
    read_header(f, &hauteur, &largeur);
}
