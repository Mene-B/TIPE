//renvoie la liste des pixels du fichier de nom name et stocke la hauteur, largeur et taille maximum. 
pix_t* read_ppm (char name, int* hauteur, int* largeur, int* taille_max);

//renvoie les informations du header de fichier.
int read_header (FILE* fichier, int* hauteur, int* largeur);

//renvoie la liste des pixels de fichier 
pix_t* read_body (FILE* fichier, int hauteur, int largeur, int maxval);
