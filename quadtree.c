#include "quadtree.h"

pix_t* read_pix (int red, int green, int blue, int maxval){
    pix_t* res = malloc(sizeof (pix_t));
    res -> r = red*255/maxval;
    res -> g = green*255/maxval;
    res -> b = blue*255/maxval; 
    return res;
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


int respect_incertitude(image_t* image, int u){
    int max_r = image->pixels[0][0]->r;
    int min_r = image->pixels[0][0]->r;
    int max_g = image->pixels[0][0]->g;
    int min_g = image->pixels[0][0]->g;
    int max_b = image->pixels[0][0]->b;
    int min_b = image->pixels[0][0]->b;

    for(int i = 0; i < image->hauteur; i++){
        for(int j = 0; j < image->largeur; j++){
            if(image->pixels[i][j]->r > max_r){
                max_r = image->pixels[i][j]->r;
            }
            if(image->pixels[i][j]->r < min_r){
                min_r = image->pixels[i][j]->r;
            }
            if(image->pixels[i][j]->g > max_g){
                max_g = image->pixels[i][j]->g;
            }
            if(image->pixels[i][j]->g < min_g){
                max_g = image->pixels[i][j]->g;
            }
            if(image->pixels[i][j]->b > max_b){
                max_b = image->pixels[i][j]->b;
            }
            if(image->pixels[i][j]->b < min_b){
                min_b = image->pixels[i][j]->b;
            }
        }
    }
    if ((max_r - min_r)>u || (max_r - min_r)>u || (max_r - min_r)>u){
        return 0;
    }
    return 1;
}


pix_t* average_pixel(image_t* image){
    float nb_pixels = (float) (image->hauteur * image->largeur);
    float moy_r = 0;
    float moy_g = 0;
    float moy_b = 0;
    for(int i = 0; i < image->hauteur; i++){
        for(int j = 0; j < image->largeur; j++){
            moy_r += ((float) image->pixels[i][j]->r)/nb_pixels;
            moy_g += ((float) image->pixels[i][j]->g)/nb_pixels;
            moy_b += ((float) image->pixels[i][j]->b)/nb_pixels;
        }
    }
    pix_t* pixel = malloc(sizeof(pix_t));
    pixel->b = (int) moy_b;
    pixel->r = (int) moy_r;
    pixel->g = (int) moy_g;
    return pixel;
}



tree_t* make_tree(image_t* image, int u){
    if(respect_incertitude(image, u) == 0){
        image_t** quad_images = split_list(image);
        tree_t* arbre = malloc(sizeof(tree_t));
        arbre->enfants = malloc(4*sizeof(tree_t*));
        arbre->pixel = NULL;
        for(int i = 0; i <4; i++){
            arbre->enfants[i] = make_tree(quad_images[i],u);
        }
        return arbre;
    }else{
        pix_t* avrg_pixel = average_pixel(image);
        tree_t* arbre  = malloc(sizeof(tree_t));
        arbre->pixel = avrg_pixel;
        arbre->enfants = NULL;
        return arbre;
    }
}

dim_tree_t* make_tree_dim(image_t* image, int u){
    dim_tree_t* dim_tree = malloc(sizeof(dim_tree_t));
    dim_tree->arbre = make_tree(image, u);
    dim_tree->largeur = image->largeur;
    dim_tree->hauteur = image->hauteur;
    return dim_tree;
}


int main(){
    char* f_n = "sample_1920×1280.ppm";
    int* p_hauteur = malloc(sizeof(int));
    int* p_largeur = malloc(sizeof(int));
    int* p_taille_max = malloc(sizeof(int));
    image_t* test = read_ppm (f_n, p_hauteur, p_largeur, p_taille_max);
    tree_t* test2 = make_tree(test,5);
}
