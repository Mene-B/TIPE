typedef struct pixel {
    int r;
    int g;
    int b;
} pix_t;

typedef struct tree {
    pix_t* pixel;
    struct tree** enfants;
} tree_t;

