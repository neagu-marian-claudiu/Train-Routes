#ifndef TRAINS_H
#define TRAINS_H

typedef struct
{
    int v1, v2, cost;
} MUCHIE;

typedef struct
{
    int V;
    int E;
    MUCHIE *e;
} GRAPH;

typedef struct unique_stations
{
    struct unique_stations *next;
    char station[30];
    int index;
} Unique_stations;

typedef struct all_stations
{
    int train_index;
    int distance;
    char station[30];
    struct all_stations *next;
} All_stations;

void swap(MUCHIE *a, MUCHIE *b);

int partition(MUCHIE *arr, int low, int high);

void quickSort(MUCHIE *arr, int low, int high);

int Kruskal(GRAPH *g, char **stations);

void cost_matrix(All_stations *Head, Unique_stations *head, int orientata, int **a);

int multiplu_statie(Unique_stations *head, char *statie);

int get_index(char *station, Unique_stations *head);

int number_of_stations(Unique_stations *head);

Unique_stations *add_unique_station(Unique_stations *list_head, char *station, int index);

Unique_stations *create_unique_station(char *station, int index);

All_stations *create_station(char *station, int index, int distance);

All_stations *add_station(All_stations *list_head, char *station, int index, int distance);

int nr_muchii(int **a, int n);

MUCHIE *vector_muchii(int **a, int muchii, int n);

void create_stations_vector(Unique_stations *head, char **stations);

#endif