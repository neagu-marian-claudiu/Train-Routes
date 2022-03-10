#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Trains.h"

int main()
{
    setbuf(stdout, NULL);
    FILE *f, *file;

    //Creez lista cu statii unice
    Unique_stations *head = NULL;
    f = fopen("_all_files.txt", "r");

    char nume_fisier[30];
    char statie[40];
    int i = 0;
    while (fscanf(f, "%s", nume_fisier) != EOF)
    {
        file = fopen(nume_fisier, "r");
        if (file == NULL)
            exit(1);
        while (!feof(file))
        {
            fgets(statie, 40, file);

            for (int j = 0; j < strlen(statie); j++)
                if (statie[j] == ',')
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

    /* while (head != NULL)
    {
        printf("\n %s  index:%d", head->station, head->index);
        head = head->next;
    }*/

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
        while (fgets(statie, 40, file))
        {
            for (int j = 0; j < strlen(statie); j++)
            {
                if (statie[j] == 13)
                    statie[j] = '\0';
            }

            string = strtok(statie, ",");
            string = strtok(NULL, ",");
            string = string + 1;
            int distance = atoi(string);

            for (int j = 0; j < strlen(statie); j++)
                if (statie[j] == ',')
                    statie[j] = '\0';
            Head = add_station(Head, statie, index, distance);
        }
        fclose(file);
    }
    fclose(f);

    //Aici am testat lista cu toate rutele
    /*while (Head != NULL)
    {
        printf("\n %s  index:%d  km: %d", Head->station, Head->train_index, Head->distance);
        Head = Head->next;
    }*/

    int nr_of_stations;

    nr_of_stations = number_of_stations(head);

    int **cost_neorientata;

    cost_neorientata = (int **)malloc(nr_of_stations * sizeof(int *));
    for (int i = 0; i < nr_of_stations; i++)
        cost_neorientata[i] = (int *)calloc(nr_of_stations, sizeof(int));

    cost_matrix(Head, head, 0, cost_neorientata);
    GRAPH *g;
    g = (GRAPH *)malloc(sizeof(GRAPH));
    g->V = nr_of_stations;
    g->E = nr_muchii(cost_neorientata, nr_of_stations);
    g->e = vector_muchii(cost_neorientata, g->E, nr_of_stations);

    char **stations;
    stations = (char **)malloc(nr_of_stations * sizeof(char *));
    for (int i = 0; i < nr_of_stations; i++)
        stations[i] = (char *)calloc(40, sizeof(char));
    create_stations_vector(head, stations);
    printf("Cost minim km cale ferata = %d km\n", Kruskal(g, stations));

    return 0;
}