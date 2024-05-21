//renvoie la liste des pixels du fichier de nom name et stocke la hauteur, largeur et taille maximum. 
pix_t* read_ppm (char name, int* hauteur, int* largeur, int* taille_max);

//renvoie les informations du header de fichier.
int read_header (FILE* fichier, int* hauteur, int* largeur);

//renvoie la liste des pixels de fichier 
pix_t* read_body (FILE* fichier, int hauteur, int largeur, int valmax);

// Créer l'imafe au format ppm à partir de l'arbre avec les données compressées 
image_t* tree_to_image(dim_tree_t* arbre);

// Ecrit le header du fichier ppm 
void write_header(FILE* f, int largeur, int longueur);

// Transforme un arbre en une matrice qui met les pixels aux bons endroits dans la matrice
void tree_to_matrice(tree_t* arbre, pix_t*** mat, int i, int j, int largeur, int hauteur);;
