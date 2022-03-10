#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trains.h"

int main()
{
    setbuf(stdout, NULL);
    FILE *f, *file;

    //Creez lista cu statii unice
    Unique_stations *head = NULL;
    f = fopen("_all_files.txt", "r");

    char nume_fisier[30];
    char statie[30];
    int i = 0;
    while (fscanf(f, "%s", nume_fisier) != EOF)
    {
        file = fopen(nume_fisier, "r");
        if (file == NULL)
            exit(1);
        while (!feof(file))
        {
            fgets(statie, 30, file);

            for (int j = 0; j < strlen(statie); j++)
                if (statie[j] == 13)
                    statie[j] = '\0';

            if (multiplu_statie(head, statie) == 0)
            {
                head = add_unique_station(head, statie, i);
                i++;
            }
        }
        fclose(file);
    }
    fclose(f);

    //Creez lista cu toate rutele trenurilor
    All_stations *Head = NULL;
    f = fopen("_all_files.txt", "r");
    while (fscanf(f, "%s", nume_fisier) != EOF)
    {
        file = fopen(nume_fisier, "r");
        if (file == NULL)
            exit(1);
        char *string = strtok(nume_fisier, ".");
        int index = atoi(string);
        while (!feof(file))
        {
            fgets(statie, 30, file);

            for (int j = 0; j < strlen(statie); j++)
                if (statie[j] == 13)
                    statie[j] = '\0';

            Head = add_station(Head, statie, index);
        }
        fclose(file);
    }
    fclose(f);

    //print_unique(head);

    int nr_of_stations;

    nr_of_stations = number_of_stations(head);

    int **orientata, **neorientata;

    orientata = (int **)malloc(nr_of_stations * sizeof(int *));
    neorientata = (int **)malloc(nr_of_stations * sizeof(int *));
    for (int i = 0; i < nr_of_stations; i++)
    {
        orientata[i] = (int *)calloc(nr_of_stations, sizeof(int));
        neorientata[i] = (int *)calloc(nr_of_stations, sizeof(int));
    }

    create_matrix(Head, head, 1, orientata);
    create_matrix(Head, head, 0, neorientata);

    Graph *g_orientat;
    Graph *g_neorientat;

    g_orientat = (Graph *)malloc(sizeof(Graph));
    g_neorientat = (Graph *)malloc(sizeof(Graph));

    //Creez graful neorientat
    g_neorientat->a = neorientata;
    g_neorientat->V = nr_of_stations;
    g_neorientat->E = nr_muchii(g_neorientat->a, g_neorientat->V, 0);

    //Creez graful orientat
    g_orientat->a = orientata;
    g_orientat->V = nr_of_stations;
    g_orientat->E = nr_muchii(g_orientat->a, g_orientat->V, 1);

    //Pun nr de noduri in fisierul noduri.txt
    f = fopen("noduri.txt", "w");
    if (f == NULL)
        exit(1);
    fprintf(f, "%d\n", g_orientat->V);
    fprintf(f, "%d\n", g_neorientat->V);
    fclose(f);

    //Pun nr de muchii in fisierul muchii.txt
    f = fopen("muchii.txt", "w");
    if (f == NULL)
        exit(1);
    fprintf(f, "%d\n", g_orientat->E);
    fprintf(f, "%d\n", g_neorientat->E);
    fclose(f);

    /*for (int l = 0; l < 5; l++)
    {
        printf("\n\n");
        for (int c = 0; c < 5; c++)
            printf("%d   ", g_orientat->a[l][c]);
    }*/

    f = fopen("primul.txt", "w");
    if (f == NULL)
        exit(1);
    int max = most_visited(g_neorientat->a, f, head, nr_of_stations);
    fclose(f);

    f = fopen("doilea.txt", "w");
    if (f == NULL)
        exit(1);
    second_most_visited(g_neorientat->a, f, head, nr_of_stations, max);
    fclose(f);

    char oras[20];
    printf("Introduceti orasul dumneavostra pentru a gasi gradul acestuia:");
    f = fopen("orasul_meu.txt", "w");
    if (f == NULL)
        exit(1);
    gets(oras);
    city_grade(head, g_neorientat->a, nr_of_stations, f, oras);
    fclose(f);

    char **stations;
    stations = (char **)malloc(nr_of_stations * sizeof(char *));
    for (int i = 0; i < nr_of_stations; i++)
        stations[i] = (char *)calloc(30, sizeof(char));

    create_stations_vector(head, stations);

    queue_t *q;
    q = (queue_t *)malloc(sizeof(queue_t));

    parcurgere_bfs(g_neorientat, nr_of_stations, 0, q, stations);
    parcurgere_dfs(0, nr_of_stations, stations, g_neorientat);

    return 0;
}