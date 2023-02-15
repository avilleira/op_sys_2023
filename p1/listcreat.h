struct Creat {
    long long id;
    char *specie;
    char *color;
    int height; //mm
    int weight; //g
};

// Print all the characteristics of the creature.
void print_creat(struct Creat Creat);

//Creating an empty list.
struct Creat* create_list();

// Checking if the list is empty.
int is_empty(struct Creat* list);