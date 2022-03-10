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
    int distance;
    char station[30];
    struct all_stations *next;
} All_stations;

typedef struct graph
{
    int V;
    int E;
    int **a;
} Graph;

int multiplu_statie(Unique_stations *head, char *statie);

Unique_stations *add_unique_station(Unique_stations *list_head, char *station, int index);

Unique_stations *create_unique_station(char *station, int index);

All_stations *create_station(char *station, int index, int distance);

All_stations *add_station(All_stations *list_head, char *station, int index, int distance);

int get_index(char *station, Unique_stations *head);

void create_matrix(All_stations *Head, Unique_stations *head, int orientata, int **a);

void cost_matrix(All_stations *Head, Unique_stations *head, int orientata, int **a);

int number_of_stations(Unique_stations *head);

int nr_muchii(int **a, int n, int orientat);

void min_max_distance(int **a, int nr_statii, char **stations);

void km_cale_ferata(int **a, int nr_statii);

void create_stations_vector(Unique_stations *head, char **stations);

void printSolution(int dist[], int n, char **stations);

int minDistance(int dist[], int sps[], int V);

void dijkstra(Graph *g, int s, char **stations, int *parent);

void drum_minim(char *oras);

void ruta(int oras, int *parent, char **stations, char *fisier);

void departe(Unique_stations *head, char **stations, int *parent);

void creare_fisiere(Unique_stations *head, Graph *g, char **stations);

void printSolution2(int dist[], int n, char **stations, char *file);

void dijkstra2(Graph *g, int s, char **stations, int *parent, char *file);

void maximum_distance(Unique_stations *head);

#endif