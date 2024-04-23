typedef struct pixel {
    int r;
    int g;
    int b;
} pix_t;

typedef struct tree {
    pix_t* pixel;
    struct tree** enfants;
} tree_t;

typedef struct img {
    pix_t*** pixels;
    int hauteur;
    int largeur;
} image_t;

//renvoie le pixel représenté par les couleurs r,g,b
pix_t* read_pix* (int r, int g, int b, int maxval);

//sépare pixels en 4 listes en fonction de leur position dans l'image. 
image_t** split_list (image_t* img);

// Renvoie 1 si l'incertitude est respectée dans une certaine image, 0 sinon
int respect_incertitude(image_t* image, int incertitude);
