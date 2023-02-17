
struct Creat {
    long long id;
    char *specie;
    char *color;
    int height; //mm
    int weight; //g
    struct Creat* prev;
    struct Creat* next;
};


struct List {
    int n_creatures;
    struct Creat *first;
    struct Creat *last;
};

typedef struct Creat Creat;
typedef struct List List;

// Print all the characteristics of the creature.
void print_creat(Creat *creat);

//Creating an empty list.
List *create_list(void);

// Checking if the list is empty.
int is_empty(List* list);