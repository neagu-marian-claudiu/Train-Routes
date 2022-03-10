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

All_stations *create_station(char *station, int index)
{
    All_stations *new_node = (All_stations *)malloc(sizeof(All_stations));
    strcpy(new_node->station, station);
    new_node->train_index = index;
    new_node->next = NULL;
    return new_node;
}

All_stations *add_station(All_stations *list_head, char *station, int index)
{
    All_stations *new_node;
    new_node = create_station(station, index);
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

void print_unique(Unique_stations *head)
{
    while (head != NULL)
    {
        printf("\n%d  %s", head->index, head->station);
        head = head->next;
    }
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

int most_visited(int **a, FILE *f, Unique_stations *head, int n)
{
    int index, max = 0, sum = 0;
    for (int i = 0; i < n; i++)
    {
        if (max < sum)
        {
            max = sum;
            index = i - 1;
        }
        sum = 0;
        for (int j = 0; j < n; j++)
            sum = sum + a[i][j];
    }

    while (head != NULL)
    {
        if (head->index == index)
        {
            fputs(head->station, f);
            break;
        }
        head = head->next;
    }

    return max;
}

void second_most_visited(int **a, FILE *f, Unique_stations *head, int n, int maxim)
{
    int index, max = 0, sum = 0;
    for (int i = 0; i < n; i++)
    {
        if ((max < sum) && (sum != maxim))
        {
            max = sum;
            index = i - 1;
        }
        sum = 0;
        for (int j = 0; j < n; j++)
            sum = sum + a[i][j];
    }

    while (head != NULL)
    {
        if (head->index == index)
        {
            fputs(head->station, f);
            break;
        }
        head = head->next;
    }
}

void city_grade(Unique_stations *head, int **a, int n, FILE *f, char *oras)
{
    int index;
    int grade = 0;
    while (head != NULL)
    {
        if (strcmp(head->station, oras) == 0)
        {
            index = head->index;
            break;
        }
        head = head->next;
    }
    for (int i = 0; i < n; i++)
        grade = grade + a[index][i];

    fprintf(f, "%d", grade);
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

queue_t *queue_create()
{
    queue_t *queue = NULL;

    /* TODO: TASK 1: Alocare memorie pentru o coada vida. Initializare campuri. */

    queue = (queue_t *)malloc(sizeof(queue_t));

    queue->head = NULL;
    queue->tail = NULL;
    queue->length = 0;

    return queue;
}

queue_node_t *queue_node_create(int val)
{
    queue_node_t *node = NULL;

    /* TODO: TASK 2, a): Alocare si initializare nod. */

    node = (queue_node_t *)malloc(sizeof(queue_node_t));
    node->val = val;
    node->next = NULL;

    return node;
}

void enqueue(queue_t *queue, int val)
{
    queue_node_t *node = NULL;

    /* TODO: Creeare nod. Adaugare in coada. */

    node = queue_node_create(val);

    if (queue->head == NULL)
    {
        queue->head = node;
        queue->tail = node;
        queue->length++;
        return;
    }

    queue->tail->next = node;
    queue->tail = node;
    queue->length++;

    return;
}

int dequeue(queue_t *queue)
{
    int val = 0;

    /* TODO: Identificare nod de tipul 'queue_node_t' ce trebuie scos. */
    if (queue->head == NULL)
        return 0;
    val = queue->head->val;
    /* TODO: Copiere valoare. Stergere nod.*/

    queue_node_t *node = NULL;
    node = queue->head;
    queue->head = node->next;
    if (node->next == NULL)
        queue->tail = NULL;
    queue->length--;
    free(node);

    return val;
}

void parcurgere_bfs(Graph *g, int n, int source, queue_t *q, char **vector)
{
    char **culoare;
    int *d, *p, i;
    FILE *f;

    f = fopen("parcurgere_bfs.txt", "wt");

    q = queue_create();

    culoare = (char **)malloc(sizeof(char *) * n);
    for (i = 0; i < n; i++)
    {
        culoare[i] = (char *)malloc(10 * sizeof(char));
        strcpy(culoare[i], "alb");
    }

    d = (int *)malloc(n * sizeof(int));
    for (i = 0; i < n; i++)
        d[i] = INT_MAX;

    p = (int *)malloc(n * sizeof(int));
    for (i = 0; i < n; i++)
        p[i] = 0;

    strcpy(culoare[source], "gri");
    d[source] = 0;
    enqueue(q, source);

    while (q->head)
    {
        int v;
        v = dequeue(q);

        fprintf(f, "%s\n", vector[v]);

        if (v != -1)
        {
            for (i = 0; i < n; i++)
            {
                if (g->a[v][i] == 1)
                {
                    if (strcmp(culoare[i], "alb") == 0)
                    {
                        strcpy(culoare[i], "gri");
                        p[i] = v;
                        d[i] = d[v] + 1;
                        enqueue(q, i);
                    }
                }
            }

            strcpy(culoare[v], "negru");
        }
    }

    fclose(f);
}

void pas_dfs(int source, char **culoare, int *p, int *d, int n, Graph *g, FILE *f, char **vector)
{
    int i;

    fprintf(f, "%s\n", vector[source]);

    for (i = 0; i < n; i++)
    {
        if (g->a[source][i] == 1)
        {
            if (strcmp(culoare[i], "alb") == 0)
            {
                strcpy(culoare[i], "gri");
                p[i] = source;
                d[i] = d[source] + 1;
                pas_dfs(i, culoare, p, d, n, g, f, vector);
            }
        }

        strcpy(culoare[source], "negru");
    }
}

void parcurgere_dfs(int source, int n, char **vector, Graph *g)
{
    char **culoare;
    int *d, *p, i;
    FILE *f;

    f = fopen("parcurgere_dfs.txt", "wt");

    culoare = (char **)malloc(sizeof(char *) * n);
    for (i = 0; i < n; i++)
    {
        culoare[i] = (char *)malloc(10 * sizeof(char));
        strcpy(culoare[i], "alb");
    }

    d = (int *)malloc(n * sizeof(int));
    for (i = 0; i < n; i++)
        d[i] = INT_MAX;

    p = (int *)malloc(n * sizeof(int));
    for (i = 0; i < n; i++)
        p[i] = 0;

    strcpy(culoare[source], "gri");
    d[source] = 0;

    pas_dfs(source, culoare, p, d, n, g, f, vector);

    fclose(f);
}