#ifndef TRAINS_H
#define TRAINS_H

typedef struct unique_stations
{
    struct unique_stations *next;
    char station[30];
    int index;
} Unique_stations;

typedef struct all_stations
{
    int train_index;
    char station[30];
    struct all_stations *next;
} All_stations;

typedef struct graph
{
    int V;
    int E;
    int **a;
} Graph;

typedef struct queue_node_t queue_node_t;
struct queue_node_t
{
    /* Valoarea retinuta de catre nod. */
    int val;

    /* Pointer catre urmatorul element de tip nod. */
    struct queue_node_t *next;
};

typedef struct queue_t queue_t;
struct queue_t
{
    /* Capul listei inlantuite. */
    struct queue_node_t *head;
    /* Coada listei inlantuite. */
    struct queue_node_t *tail;

    /* Dimensiunea cozii. */
    unsigned int length;
};

int multiplu_statie(Unique_stations *head, char *statie);

Unique_stations *add_unique_station(Unique_stations *list_head, char *station, int index);

Unique_stations *create_unique_station(char *station, int index);

All_stations *create_station(char *station, int index);

All_stations *add_station(All_stations *list_head, char *station, int index);

void print_unique(Unique_stations *head);

void create_matrix(All_stations *Head, Unique_stations *head, int orientata, int **a);

int number_of_stations(Unique_stations *head);

int nr_muchii(int **a, int n, int orientat);

int most_visited(int **a, FILE *f, Unique_stations *head, int n);

void second_most_visited(int **a, FILE *f, Unique_stations *head, int n, int maxim);

void city_grade(Unique_stations *head, int **a, int n, FILE *f, char *oras);

int get_index(char *station, Unique_stations *head);

queue_t *queue_create();

queue_node_t *queue_node_create(int val);

void enqueue(queue_t *queue, int val);

int dequeue(queue_t *queue);

void parcurgere_bfs(Graph *g, int n, int source, queue_t *q, char **vector);

void pas_dfs(int source, char **culoare, int *p, int *d, int n, Graph *g, FILE *f, char **vector);

void parcurgere_dfs(int source, int n, char **vector, Graph *g);

void create_stations_vector(Unique_stations *head, char **stations);

#endif