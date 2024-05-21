#include "ppm.h"
#include <stdio.h>
#include <assert.h>

int read_header (FILE* fichier, int* hauteur, int* largeur){
    assert(fichier != NULL);
    char* s = malloc(3*sizeof(char));
    fscanf(fichier, "%s", s);
    printf("%s\n", s);
    char poubelle;
    char c = '0';
    int width=0;
    int height=0;
    int maxval=0;
    fscanf(fichier, "%c", &poubelle);
    while (c != 32 && c != 13 && c != 10 && c != 9){
        width = 10*width + c - '0';
        fscanf(fichier, "%c", &c);
    }
    c = '0';
    while (c != 32 && c != 13 && c != 10 && c != 9){
        height = 10*height + c - '0';
        fscanf(fichier, "%c", &c);
    }
    c = '0';
    while (c != 32 && c != 13 && c != 10 && c != 9){
        maxval = 10*maxval + c - '0';
        fscanf(fichier, "%c", &c);
    }

    *hauteur = height;
    *largeur = width;
    // printf("hauteur : %d\n", height);
    // printf("largeur : %d\n", width);
    // printf("maxval : %d\n", maxval);
    return maxval;
}

int read_int(FILE* fichier){
    assert(fichier!=NULL);
    unsigned int res=0;
    unsigned char entier;
    fscanf(fichier, "%c", &entier);
    res = entier;
    // printf("%u\n", res);
    return res;
}

pix_t*** read_body (FILE* fichier, int hauteur, int largeur){
    pix_t*** res = malloc(hauteur*sizeof(pix_t**));
    for (int i=0; i<hauteur; i++){
        res[i] = malloc(largeur*sizeof(pix_t*));
        for (int j=0; j<largeur; j++){
            res[i][j] = malloc(sizeof(pix_t));
            res[i][j]->r = read_int(fichier);
            res[i][j]->g = read_int(fichier);
            res[i][j]->b = read_int(fichier);
        }
    }
    return res;
}

image_t* read_ppm (char* name, int* p_hauteur, int* p_largeur, int* p_taille_max){
    FILE* f = fopen(name, "r");
    int maxval = read_header (f, p_hauteur, p_largeur);
    image_t* res = malloc(sizeof(image_t));
    res -> hauteur = *p_hauteur;
    res -> largeur = *p_largeur;
    res -> pixels = read_body(f,*p_hauteur,*p_largeur);
    return res;
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
