#include "quadtree.h"

pix_t* read_pix (int red, int green, int blue, int maxval){
    pix_t* res = malloc(sizeof (pix_t));
    res -> r = red*255/maxval;
    res -> g = green*255/maxval;
    res -> b = blue*255/maxval; 
    return res 
}

image_t** split_list (image_t* img){
    int h1 = img->hauteur/2;
    int h2 = img->hauteur - h1;
    int l1 = img->largeur / 2;
    int l2 = img->largeur - l1;
    int taille1 = h1*img->largeur;
    int taille2 = h2*img->largeur;
    int taille = taille1+taille2;
    pix_t*** liste1 = malloc(h1*sizeof(pix_t**));
    for (int i = 0; i<h1; i++){
        liste1[i] = malloc(l1*sizeof(pix_t));
    }

    pix_t*** liste2 = malloc(h1*sizeof(pix_t**));
    for (int i = 0; i<h1; i++){
        liste2[i] = malloc(l2*sizeof(pix_t*));
    }    

    pix_t*** liste3 = malloc(h2*sizeof(pix_t**));
    for (int i = 0; i<h2; i++){
        liste3[i] = malloc(l1*sizeof(pix_t*));
    }    

    pix_t*** liste4 = malloc(h2*sizeof(pix_t**));
    for (int i = 0; i<h2; i++){
        liste4[i] = malloc(l2*sizeof(pix_t*));
    }   

    for (int i = 0; i<h1; i++) {
        for (int j = 0; j<l1; j++){
            liste1[i][j] = img->pixels[i][j];
        }
    }

    for (int i = 0; i<h1; i++){
        for (int j = 0; j<l2; j++){
            liste2[i][j] = img->pixels[i][l1+j];
        }
    }

    for (int i = 0; i<h2; i++){
        for (int j = 0; j<l1; j++){
            liste3[i][j] = img->pixels[h1+i][j];
        }
    }

    for (int i = 0; i<h2; i++){
        for (int j = 0; j<l2; j++){
            liste4[i][j] = img->pixels[h1+i][l1+j];
        }
    }

    image_t** res = malloc(4*sizeof(image_t*));
    image_t* img1 = malloc(sizeof(image_t));
    img1 -> hauteur = h1;
    img1 -> largeur = l1;
    img1 -> pixels = liste1;
    image_t* img2 = malloc(sizeof(image_t));
    img2 -> hauteur = h1;
    img2 -> largeur = l1;
    img2 -> pixels = liste2;
    image_t* img3 = malloc(sizeof(image_t));
    img3 -> hauteur = h1;
    img3 -> largeur = l1;
    img3 -> pixels = liste3;
    image_t* img4 = malloc(sizeof(image_t));
    img4 -> hauteur = h1;
    img4 -> largeur = l1;
    img4 -> pixels = liste4;
    res[0] = img1; res[1] = img2; res[2] = img3; res[3] = img4;
    
    return res;
}

