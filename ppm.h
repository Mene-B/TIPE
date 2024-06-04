#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "quadtree.h"

//renvoie la liste des pixels du fichier de nom name et stocke la hauteur, largeur et taille maximum. 
image_t* read_ppm (char* name, int* hauteur, int* largeur);

//renvoie la valeur max et stocke la hauteur et la largeur de l'image.
void read_header (FILE* fichier, int* hauteur, int* largeur);

//renvoie la liste des pixels de fichier 
pix_t*** read_body (FILE* fichier, int hauteur, int largeur);

//renvoie un entier lu dans fichier 
int read_int (FILE* fichier);

// Créer l'imafe au format ppm à partir de l'arbre avec les données compressées 
image_t* tree_to_image(dim_tree_t* arbre);

// Transforme un arbre en une matrice qui met les pixels aux bons endroits dans la matrice
void tree_to_matrice(tree_t* arbre, pix_t*** mat, int i, int j, int largeur, int hauteur);;

//crée un fichier ppm appelé filename avec les données de image
void img_to_ppm (char* filename, image_t* image);

//ecrit le header du fichier f de taille largeur*longuer de valeur max maxval
void write_header(FILE* f, int largeur, int hauteur);

//ecrit le corps du fichier ppm
void write_body(FILE* f, int largeur, int hauteur, pix_t*** pixels);
