pix_t* read_pix (int red, int green, int blue, int maxval){
    pix_t* res = malloc(sizeof (pix_t));
    res -> r = red*255/maxval;
    res -> g = green*255/maxval;
    res -> b = blue*255/maxval; 
    return res 
}

pix_t** split_list (pix_t* pixels, int hauteur, int largeur){
    int h1 = hauteur/2;
    int h2 = hauteur - h1;
    int l1 = largeur / 2;
    int l2 = largeur - l1;
    int taille1 = h1*largeur;
    int taille2 = h2*largeur;
    int taille = taille1+taille2
    pix_t* liste1 = malloc(h1*l1*sizeof(pix_t));
    pix_t* liste2 = malloc(h1*l2*sizeof(pix_t));
    pix_t* liste3 = malloc(h2*l1*sizeof(pix_t));
    pix_t* liste4 = malloc(h2*l2*sizeof(pix_t));

    int i = 0 ;
    int j = 0; 
    while (i<h1) {
        j = 0;
        while (j<l1){
            liste1[l1*i+j] = pixels[largeur*i+j];
        j++;
        }
    }
}

