struct Creat {
	long long id;
	char *specie;
	char *color;
	int height;		//mm
	int weight;		//g
	struct Creat *prev;
	struct Creat *next;
};
typedef struct Creat Creat;

struct List {
	int n_creatures;
	struct Creat *first;
	struct Creat *last;
};

typedef struct List List;

// Print all the characteristics of the creature.
void
print_creat(Creat *creat);

//Creating an empty list.
List 
*create_list(void);

// Checking if the list is empty.
int
is_empty(List *list);

// Adding elements at the top of the list.
void
add_creature_top(Creat *creat, List *list);

// Adding elements at the end of the list.
void
add_creature_end(Creat *creat, List *list);

// Determining first creature
void
print_first(List *list);

// Determining last creature
void
print_last(List *list);

// Asking if the animal is in the list
Creat
*is_creature(List *list, long long id);

// Delete a creature
void
del_creature (List *list, Creat* creat);

// Asking n creatures of the list
int
count_creature(List *list);

// Delete List
void 
del_list (List *list);
