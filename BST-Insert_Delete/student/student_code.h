typedef struct node {
    char* enWord;
    char* frWord;
    struct node* left;
    struct node* right;
} node_t;

typedef struct bt {
    struct node* root;
} bt_t;

int insert(bt_t* bt, char* enWord, char* frWord);

node_t* rightSubtreesLeftMostChild(node_t* node);

void delete(bt_t* bt, char* enWord);
