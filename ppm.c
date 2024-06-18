
#include "ppm.h"
#include "quadtree.h"
#include <assert.h>
#include <stdio.h>
#include <assert.h>

void read_header (FILE* fichier, int* hauteur, int* largeur){
    assert(fichier != NULL);
    char* s = malloc(3*sizeof(char));
    fscanf(fichier, "%s", s);
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
}

int read_int(FILE* fichier){
    assert(fichier!=NULL);
    unsigned char entier;
    fscanf(fichier,"%c", &entier);
    return entier;
}

pix_t*** read_body_P6 (FILE* fichier, int hauteur, int largeur){
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

image_t* read_ppm (char* name, int* p_hauteur, int* p_largeur){
    FILE* f = fopen(name, "r");
    read_header (f, p_hauteur, p_largeur);
    image_t* res = malloc(sizeof(image_t));
    res -> hauteur = *p_hauteur;
    res -> largeur = *p_largeur;
    res -> pixels = read_body(f,*p_hauteur,*p_largeur);
    printf("%d et %d\n", *p_hauteur, *p_largeur);
    printf("coucou c'est bon pour le read_ppm !\n");
    return res;
}

void tree_to_matrice(tree_t* arbre, pix_t*** mat, int i, int j, int largeur, int hauteur){
    int new_largeur = (int) (largeur/2);
    int new_hauteur = (int) (hauteur/2);
    if(arbre->enfants != NULL){
        tree_to_matrice(arbre->enfants[0], mat, i, j, new_largeur, new_hauteur);
        tree_to_matrice(arbre->enfants[1], mat, i, j + new_largeur, largeur - new_largeur, hauteur);
        tree_to_matrice(arbre->enfants[2], mat, i + new_hauteur, j, new_largeur, hauteur -new_hauteur);
        tree_to_matrice(arbre->enfants[3], mat, i + new_hauteur, j + new_largeur, largeur -  new_largeur, hauteur -  new_hauteur);
    }else {
        for (int k = i; k < i + hauteur; k++){
            for (int p = j; p < j + largeur; p++){
                pix_t* pixel = malloc(sizeof(pix_t));
                pixel -> r = arbre->pixels->r;
                pixel -> g = arbre->pixels->g;
                pixel -> b = arbre->pixels->b;
                mat[k][p] = pixel;
            }
        }
    }
}


image_t* tree_to_image(dim_tree_t* dim_arbre){
    int largeur = dim_arbre->largeur;
    int hauteur = dim_arbre->hauteur;

    tree_t* arbre = dim_arbre->arbre;
    pix_t*** mat = malloc(hauteur*sizeof(pix_t**));
    for(int i = 0; i < hauteur ; i++){
        mat[i] = malloc(largeur*sizeof(pix_t*));
    }
    tree_to_matrice(arbre, mat, 0, 0, largeur, hauteur);
    image_t* image = malloc(sizeof(image_t));
    image->hauteur = hauteur;
    image->largeur = largeur;
    image->pixels = mat;
    return image;
}


void write_header(FILE* f,int largeur, int hauteur){
    assert(f!=NULL);
    fprintf(f, "P3\n");
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
    fprintf(f, " ");
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

void print_int_char(int n, FILE* f){
    int cent = (int) n/100;
    //printf("%d\n",n);
    int diz = ((int) n/10)%10;
    int unit = n%10;
    char* string = malloc(3*sizeof(char));
    if (cent == 0){
        fprintf(f," ");
        string[0] = ' ';
    }else{
        fprintf(f,"%c", '0'+cent);
        string[0] = '0'+cent;
    }
    if (diz == 0 && cent == 0){
        fprintf(f," ");
        string[1] = ' ';
    }else{
        fprintf(f,"%c", '0'+diz);
        string[1] = '0'+diz;
    }
    fprintf(f,"%c",'0'+unit);    
    string[2] = '0'+unit;
    //printf("%s\n",string);
}

void write_body(FILE* f, int largeur, int hauteur, pix_t*** pixels){
    int acc = 0;
    for (int i=0; i<hauteur; i++){
        for (int j=0; j<largeur; j++){
            print_int_char(pixels[i][j]->r,f);
            fprintf(f," ");
            print_int_char(pixels[i][j]->g,f);
            fprintf(f," ");
            print_int_char(pixels[i][j]->b,f);
            fprintf(f," ");
        }
        fprintf(f,"\n");
        acc++;
    }
    printf("On a fini d'écrire le body du fichier !!\n Et il y a %d lignes\nun pixel vers la fin : %d %d %d\n", acc, pixels[0][0]->r, pixels[0][0]->g, pixels[0][0]->b);
}

void img_to_ppm (char* filename, image_t* image){
    FILE* f  = fopen(filename, "w");
    int largeur = image->largeur;
    int hauteur = image->hauteur;
    printf("%s\n", filename);
    write_header(f, largeur, hauteur);
    write_body (f, largeur, hauteur, image->pixels);
    fclose(f);
}
