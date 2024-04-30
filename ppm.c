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


void tree_to_image(dim_tree_t* dim_arbre, char* file_name){
    FILE* f  = fopen(file_name, "w");
    int largeur = dim_arbre->largeur;
    int hauteur = dim_arbre->hauteur;
    write_header(f, largeur, hauteur);

}


void write_header(FILE* f,int largeur, int hauteur ){
    fprintf(f, "P6");
    fprintf(f, "\n");
    char* chiffres = malloc(10*sizeof(char));
    int i = 0;
    while(largeur != 0){
        chiffres[i] = '0'+ largeur%10;
        largeur = largeur / 10;
        i++;
    }
    while(i > 0){
        fprintf(f, "%c", chiffres[i-1]);
        i--;
    }
    fprintf(f, "\n");
    while(hauteur != 0){
        chiffres[i] = '0'+ hauteur%10;
        hauteur = hauteur / 10;
        i++;
    }
    while(i > 0){
        fprintf(f, "%c", chiffres[i-1]);
        i--;
    }
    fprintf(f, "\n");
    int maxval = 255;
    while(maxval != 0){
        chiffres[i] = '0'+ maxval%10;
        maxval = maxval / 10;
        i++;
    }
    while(i > 0){
        fprintf(f, "%c", chiffres[i-1]);
        i--;
    }
    fprintf(f, "\n");

}




int main(){
    char* f_n = "sample_1920×1280.ppm";
    FILE* f = fopen(f_n,"r");
    int hauteur;
    int largeur;
    read_header(f, &hauteur, &largeur);
}
