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

    int **orientata, **neorientata, **cost_orientata, **cost_neorientata;

    orientata = (int **)malloc(nr_of_stations * sizeof(int *));
    neorientata = (int **)malloc(nr_of_stations * sizeof(int *));
    cost_orientata = (int **)malloc(nr_of_stations * sizeof(int *));
    cost_neorientata = (int **)malloc(nr_of_stations * sizeof(int *));
    for (int i = 0; i < nr_of_stations; i++)
    {
        orientata[i] = (int *)calloc(nr_of_stations, sizeof(int));
        neorientata[i] = (int *)calloc(nr_of_stations, sizeof(int));
        cost_orientata[i] = (int *)calloc(nr_of_stations, sizeof(int));
        cost_neorientata[i] = (int *)calloc(nr_of_stations, sizeof(int));
    }

    create_matrix(Head, head, 1, orientata);
    create_matrix(Head, head, 0, neorientata);
    cost_matrix(Head, head, 1, cost_orientata);
    cost_matrix(Head, head, 0, cost_neorientata);

    //Aici am testat daca am creat corect matricea de costuri
    /*for (int i = 0; i < 5; i++)
    {
        printf("\n\n\n");
        for (int j = 0; j < 5; j++)
            printf("%d     ", cost_neorientata[i][j]);
    }*/

    Graph *g_orientat;
    Graph *g_neorientat;
    Graph *g_orientat_costuri;
    Graph *g_neorientat_costuri;

    g_orientat = (Graph *)malloc(sizeof(Graph));
    g_neorientat = (Graph *)malloc(sizeof(Graph));
    g_orientat_costuri = (Graph *)malloc(sizeof(Graph));
    g_neorientat_costuri = (Graph *)malloc(sizeof(Graph));

    //Creez graful neorientat
    g_neorientat->a = neorientata;
    g_neorientat->V = nr_of_stations;
    g_neorientat->E = nr_muchii(g_neorientat->a, g_neorientat->V, 0);
    g_neorientat_costuri->a = cost_neorientata;
    g_neorientat_costuri->V = nr_of_stations;
    g_neorientat_costuri->E = g_neorientat->E;

    //Creez graful orientat
    g_orientat->a = orientata;
    g_orientat->V = nr_of_stations;
    g_orientat->E = nr_muchii(g_orientat->a, g_orientat->V, 1);
    g_orientat_costuri->a = cost_orientata;
    g_orientat_costuri->V = nr_of_stations;
    g_orientat_costuri->E = g_orientat->E;

    char **stations;
    stations = (char **)malloc(nr_of_stations * sizeof(char *));
    for (int i = 0; i < nr_of_stations; i++)
        stations[i] = (char *)calloc(30, sizeof(char));

    create_stations_vector(head, stations);

    //Task 3
    min_max_distance(cost_neorientata, nr_of_stations, stations);

    //Task 4
    km_cale_ferata(cost_neorientata, nr_of_stations);

    //Task 5
    int parent[520];
    dijkstra(g_neorientat_costuri, get_index("Bucuresti Nord", head), stations, parent);

    char oras[40];
    printf("\nIntroduceti orasul natal: ");
    gets(oras);

    drum_minim(oras);
    ruta(get_index(oras, head), parent, stations, "ruta.txt");

    //Task 6
    departe(head, stations, parent);

    //Task 7
    f = fopen("_all_files.txt", "r");
    FILE *fis = fopen("bucuresti_oradea.txt", "w+");

    while (fscanf(f, "%s", nume_fisier) != EOF)
    {
        i = 0;
        int j = 0;
        file = fopen(nume_fisier, "r");
        if (file == NULL)
            exit(1);
        while (!feof(file))
        {
            fgets(statie, 40, file);

            char *token = strtok(statie, " ,");

            if (strcmp(token, "Oradea") == 0)
                i++;

            if (strcmp(token, "Bucuresti") == 0)
                j++;

            if ((i != 0) && (j != 0))
            {
                fclose(file);
                file = fopen(nume_fisier, "r");
                while (fgets(statie, 40, file))
                {
                    fputs(statie, fis);
                }
                fprintf(fis, "\n");
            }
        }
        fclose(file);
    }
    fclose(f);

    //Aici am incercat rularea task-ului 8 
    //Este comentat deoarece intra intr-o bucla infinita
    /*creare_fisiere(head, g_neorientat_costuri, stations);
    maximum_distance(head);*/

    return 0;
}