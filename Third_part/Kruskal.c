#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Trains.h"

void swap(MUCHIE *a, MUCHIE *b)
{

    MUCHIE aux;
    aux = *a;
    *a = *b;
    *b = aux;
}

int partition(MUCHIE *arr, int low, int high)
{
    int j;
    MUCHIE pivot = arr[high];
    int i = (low - 1);
    for (j = low; j <= high - 1; j++)
        if (arr[j].cost <= pivot.cost)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(MUCHIE *arr, int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int Kruskal(GRAPH *g, char **stations)
{
    FILE *f = fopen("Kruskal_trains.txt", "w");
    if (f == NULL)
        exit(1);
    int i, j, min, max, nrMuchiiSelectate = -1, sum = 0;
    int c[g->V];
    for (i = 0; i < g->V; i++)
        c[i] = i;
    MUCHIE a[g->V - 1];

    quickSort(g->e, 0, (g->E) - 1);
    for (i = 0; nrMuchiiSelectate < g->V - 2; i++)
    {
        if (c[g->e[i].v1] != c[g->e[i].v2])
            a[++nrMuchiiSelectate] = g->e[i];

        if (c[g->e[i].v1] < c[g->e[i].v2])
        {
            min = c[g->e[i].v1];
            max = c[g->e[i].v2];
        }
        else
        {
            max = c[g->e[i].v1];
            min = c[g->e[i].v2];
        }
        for (j = 0; j < g->V; j++)
            if (c[j] == max)
                c[j] = min;
    }

    fprintf(f, "Linii utilizate:\n");
    for (i = 0; i < g->V - 1; i++)
    {
        fprintf(f, "%s --- %s   cost: %d km\n", stations[a[i].v1], stations[a[i].v2], a[i].cost);
        sum = sum + a[i].cost;
    }
    fclose(f);
    return sum;
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

int get_index(char *station, Unique_stations *head)
{
    while (head != NULL)
    {
        if (strcmp(head->station, station) == 0)
            return head->index;
        head = head->next;
    }
    return -1;
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

int nr_muchii(int **a, int n)
{
    int sum = 0;
    int i, j;
    for (i = 0; i < n; i++)
        for (j = i + 1; j < n; j++)
            if (a[i][j] > 0)
                sum = sum + 1;

    return sum;
}

MUCHIE *vector_muchii(int **a, int muchii, int n)
{
    int i, j, k = 0;
    MUCHIE *vector = (MUCHIE *)malloc(muchii * sizeof(MUCHIE));
    for (i = 0; i < n; i++)
        for (j = i + 1; j < n; j++)
            if (a[i][j] > 0)
            {
                vector[k].v1 = i;
                vector[k].v2 = j;
                vector[k].cost = a[i][j];
                k++;
            }
    return vector;
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