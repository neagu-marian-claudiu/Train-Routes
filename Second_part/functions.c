#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trains.h"
#include <limits.h>

int multiplu_statie(Unique_stations *head, char *statie)
{
    if (head == NULL)
        return 0;
    while (head != NULL)
    {
        if (strcmp(head->station, statie) == 0)
        {
            return 1;
        }
        head = head->next;
    }
    return 0;
}

Unique_stations *add_unique_station(Unique_stations *list_head, char *station, int index)
{
    Unique_stations *new_node;
    new_node = create_unique_station(station, index);
    if (list_head == NULL)
        return new_node;

    Unique_stations *aux = list_head;
    while (aux->next != NULL)
        aux = aux->next;
    aux->next = new_node;
    return list_head;
}

Unique_stations *create_unique_station(char *station, int index)
{
    Unique_stations *new_node = (Unique_stations *)malloc(sizeof(Unique_stations));
    strcpy(new_node->station, station);
    new_node->index = index;
    new_node->next = NULL;
    return new_node;
}

All_stations *create_station(char *station, int index, int distance)
{
    All_stations *new_node = (All_stations *)malloc(sizeof(All_stations));
    strcpy(new_node->station, station);
    new_node->train_index = index;
    new_node->distance = distance;
    new_node->next = NULL;
    return new_node;
}

All_stations *add_station(All_stations *list_head, char *station, int index, int distance)
{
    All_stations *new_node;
    new_node = create_station(station, index, distance);
    if (list_head == NULL)
        return new_node;

    All_stations *aux = list_head;
    while (aux->next != NULL)
        aux = aux->next;
    if (aux->train_index == index && strcmp(aux->station, station) == 0)
        ;
    else
        aux->next = new_node;
    return list_head;
}

void create_matrix(All_stations *Head, Unique_stations *head, int orientata, int **a)
{
    int c1;
    int c2;

    while (Head != NULL)
    {
        if (Head->next != NULL)
            if (Head->train_index == Head->next->train_index)
            {
                c1 = get_index(Head->station, head);
                c2 = get_index(Head->next->station, head);
                if (orientata == 0)
                    a[c1][c2] = a[c2][c1] = 1;
                else
                    a[c1][c2] = 1;
            }
        Head = Head->next;
    }
}

void cost_matrix(All_stations *Head, Unique_stations *head, int orientata, int **a)
{
    int c1;
    int c2;
    for (int i = 0; i < 520; i++)
        for (int j = 0; j < 520; j++)
            a[i][j] = 0;
    while (Head != NULL)
    {
        if (Head->next != NULL)
            if (Head->train_index == Head->next->train_index)
            {
                c1 = get_index(Head->station, head);
                c2 = get_index(Head->next->station, head);
                if (orientata == 0)
                    a[c1][c2] = a[c2][c1] = Head->next->distance - Head->distance;
                else
                    a[c1][c2] = Head->next->distance - Head->distance;
            }
        Head = Head->next;
    }
}

int get_index(char *station, Unique_stations *head)
{
    while (head != NULL)
    {
        if (strcmp(head->station, station) == 0)
            return head->index;
        head = head->next;
    }
}

int number_of_stations(Unique_stations *head)
{
    int i = 0;
    while (head != NULL)
    {
        if (head->next == NULL)
            i = head->index;
        head = head->next;
    }
    return (i + 1);
}

int nr_muchii(int **a, int n, int orientat)
{
    int sum = 0;
    int i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            sum = sum + a[i][j];
    if (!orientat)
        sum = sum / 2;

    return sum;
}

void min_max_distance(int **a, int nr_statii, char **stations)
{
    char b[40], c[40], d[40], e[40];
    FILE *f1, *f2;
    f1 = fopen("min.txt", "w");
    if (f1 == NULL)
        exit(1);
    f2 = fopen("max.txt", "w");
    if (f2 == NULL)
        exit(1);
    int min, max;
    min = INT_MAX;
    max = INT_MIN;
    for (int i = 0; i < nr_statii; i++)
        for (int j = 0; j < nr_statii; j++)
        {
            if (min > a[i][j] && a[i][j] != 0)
            {
                min = a[i][j];
                strcpy(b, stations[i]);
                strcpy(c, stations[j]);
            }
            if ((max < a[i][j]) && (a[i][j] != INT_MAX))
            {
                max = a[i][j];
                strcpy(d, stations[i]);
                strcpy(e, stations[j]);
            }
        }
    fprintf(f1, "%s - %s : %d km", b, c, min);
    fprintf(f2, "%s - %s : %d km", d, e, max);
    fclose(f1);
    fclose(f2);
}

void km_cale_ferata(int **a, int nr_statii)
{
    int sum = 0;
    FILE *f;
    f = fopen("total.txt", "w");
    if (f == NULL)
        exit(1);
    for (int i = 0; i < nr_statii; i++)
        for (int j = 0; j < nr_statii; j++)
        {
            if (a[i][j] != INT_MAX)
                sum = sum + a[i][j];
        }
    fprintf(f, "%d", (sum / 2));
    fclose(f);
}

void create_stations_vector(Unique_stations *head, char **stations)
{
    int i = 0;
    while (head != NULL)
    {
        strcpy(stations[i], head->station);
        i++;
        head = head->next;
    }
}

int minDistance(int dist[], int sps[], int V)
{
    int v, min = INT_MAX, min_index;
    for (v = 0; v < V; v++)
        if (sps[v] == 0 && dist[v] <= min)
        {
            min = dist[v];
            min_index = v;
        }
    return min_index;
}

void dijkstra(Graph *g, int s, char **stations, int *parent)
{
    FILE *f = fopen("ruta.txt", "w");
    int i, j, u;
    int dist[g->V];
    int sps[g->V];
    for (i = 0; i < g->V; i++)
    {
        dist[i] = INT_MAX;
        sps[i] = 0;
        parent[i] = -1;
    }
    dist[s] = 0;
    for (j = 0; j < g->V - 1; j++)
    {
        u = minDistance(dist, sps, g->V);
        //fprintf(f, "%s\n", stations[u]);
        sps[u] = 1;
        for (i = 0; i < g->V; i++)
        {
            if (sps[i] == 0 && g->a[u][i] != 0 &&
                dist[u] != INT_MAX && dist[u] + g->a[u][i] < dist[i])
            {
                dist[i] = dist[u] + g->a[u][i];
                parent[i] = u;
            }
        }
    }
    parent[s] = -1;
    printSolution(dist, g->V, stations);
    fclose(f);
}

void printSolution(int dist[], int n, char **stations)
{
    FILE *f;
    f = fopen("dijkstra.txt", "w");
    if (f == NULL)
        exit(1);
    for (int i = 0; i < n; i++)
        fprintf(f, "%s,%d\n", stations[i], dist[i]);
    fclose(f);
}

void drum_minim(char *oras)
{
    FILE *f;
    char *token, city[40];
    f = fopen("dijkstra.txt", "r");
    fgets(city, 40, f);
    token = strtok(city, ",");
    while (strcmp(token, oras) != 0)
    {
        fgets(city, 40, f);
        token = strtok(city, ",");
    }
    token = strtok(NULL, ",");
    fclose(f);
    f = fopen("ruta.txt", "w");
    fprintf(f, "Drumul cel mai scurt de la Bucuresti la %s este de %d km", oras, atoi(token));
    fclose(f);
}

void ruta(int oras, int *parent, char **stations, char *fisier)
{
    FILE *f = fopen(fisier, "a");
    if (parent[oras] != -1)
        ruta(parent[oras], parent, stations, fisier);
    fprintf(f, "\n%s", stations[oras]);
    fclose(f);
}

void departe(Unique_stations *head, char **stations, int *parent)
{
    int max;
    FILE *f;
    char *token, *token2, city[40], aux[40];
    f = fopen("dijkstra.txt", "r");
    fgets(city, 40, f);
    token = strtok(city, ",");
    token2 = strtok(NULL, ",");
    max = atoi(token2);
    while (fgets(city, 40, f))
    {
        token = strtok(city, ",");
        token2 = strtok(NULL, ",");
        if (max < atoi(token2))
        {
            max = atoi(token2);
            strcpy(aux, token);
        }
    }
    fclose(f);
    f = fopen("departe.txt", "a");
    fprintf(f, "\nStatia cea mai indepartata de Bucuresti nord este %s aflata la %d km\n", aux, max);
    ruta(get_index(aux, head), parent, stations, "departe.txt");
}

void dijkstra2(Graph *g, int s, char **stations, int *parent, char *file)
{
    FILE *f = fopen("ruta.txt", "w");
    int i, j, u;
    int dist[g->V];
    int sps[g->V];
    for (i = 0; i < g->V; i++)
    {
        dist[i] = INT_MAX;
        sps[i] = 0;
        parent[i] = -1;
    }
    dist[s] = 0;
    for (j = 0; j < g->V - 1; j++)
    {
        u = minDistance(dist, sps, g->V);
        //fprintf(f, "%s\n", stations[u]);
        sps[u] = 1;
        for (i = 0; i < g->V; i++)
        {
            if (sps[i] == 0 && g->a[u][i] != 0 &&
                dist[u] != INT_MAX && dist[u] + g->a[u][i] < dist[i])
            {
                dist[i] = dist[u] + g->a[u][i];
                parent[i] = u;
            }
        }
    }
    parent[s] = -1;
    printSolution2(dist, g->V, stations, file);
    fclose(f);
}

void printSolution2(int dist[], int n, char **stations, char *file)
{
    FILE *f;
    f = fopen("dijkstra.txt", "w");
    if (f == NULL)
        exit(1);
    for (int i = 0; i < n; i++)
        fprintf(f, "%s,%d\n", stations[i], dist[i]);
    fclose(f);
}

void creare_fisiere(Unique_stations *head, Graph *g, char **stations)
{
    int parent[520];
    while (head != NULL)
    {
        char aux[40];
        strcat(aux, head->station);
        strcat(aux, ".txt");
        dijkstra2(g, head->index, stations, parent, aux);
    }
}

void maximum_distance(Unique_stations *head)
{
    FILE *f;
    char a[40], b[40];
    int max = 0;
    char statie[40];
    while (head != NULL)
    {
        char aux[40];
        strcat(aux, head->station);
        strcat(aux, ".txt");
        f = fopen(aux, "r");
        while (fgets(statie, 40, f))
        {
            char *token = strtok(statie, ",");
            token = strtok(NULL, ",");
            token = token + 1;
            if (atoi(token) > max)
            {
                max = atoi(token);
                strcpy(a, head->station);
                strcpy(b, statie);
            }
        }
        fclose(f);
        head = head->next;
    }
    f = fopen("drum_lung.txt", "w");
    fprintf(f, "Drumul cel mai lung este intre %s si %s si este de lungime %d km", a, b, max);
}