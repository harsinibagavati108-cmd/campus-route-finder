#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 6

char *places[N] = {
    "Main Gate", "Library", "Canteen", "Lab", "Hostel", "Auditorium"
};

/* Linked list node for adjacency list */
typedef struct Node {
    int dest;
    struct Node *next;
} Node;

Node *graph[N];

void addEdge(int u, int v) {
    Node *n = (Node *)malloc(sizeof(Node));
    n->dest = v;
    n->next = graph[u];
    graph[u] = n;
}

void connect(int u, int v) {
    addEdge(u, v);
    addEdge(v, u);
}

void buildCampus() {
    int i;
    for (i = 0; i < N; i++)
        graph[i] = NULL;

    /* Predefined campus connections (undirected) */
    connect(0, 1); /* Main Gate - Library */
    connect(0, 2); /* Main Gate - Canteen */
    connect(1, 3); /* Library - Lab */
    connect(1, 5); /* Library - Auditorium */
    connect(2, 4); /* Canteen - Hostel */
    connect(3, 4); /* Lab - Hostel */
}

int findPlace(char name[]) {
    int i;
    for (i = 0; i < N; i++) {
        if (strcmp(places[i], name) == 0)
            return i;
    }
    return -1;
}

void displayConnections() {
    int i;
    Node *p;
    printf("\n--- Campus Connections (Adjacency List) ---\n");
    for (i = 0; i < N; i++) {
        printf("%s -> ", places[i]);
        p = graph[i];
        if (p == NULL)
            printf("None");
        while (p != NULL) {
            printf("%s", places[p->dest]);
            if (p->next != NULL)
                printf(", ");
            p = p->next;
        }
        printf("\n");
    }
}

void findRoute() {
    char srcName[50], destName[50];
    int src, dest, i, front = 0, rear = 0;
    int visited[N], parent[N], queue[N];
    int path[N], len = 0, cur;
    Node *p;

    printf("\nLocations: Main Gate, Library, Canteen, Lab, Hostel, Auditorium\n");
    printf("Enter start location: ");
    fgets(srcName, sizeof(srcName), stdin);
    srcName[strcspn(srcName, "\n")] = '\0';
    printf("Enter destination: ");
    fgets(destName, sizeof(destName), stdin);
    destName[strcspn(destName, "\n")] = '\0';

    src = findPlace(srcName);
    dest = findPlace(destName);
    if (src == -1 || dest == -1) {
        printf("Invalid location name.\n");
        return;
    }
    if (src == dest) {
        printf("BFS Route: %s\n", places[src]);
        return;
    }

    for (i = 0; i < N; i++) {
        visited[i] = 0;
        parent[i] = -1;
    }

    /* BFS using a queue */
    visited[src] = 1;
    queue[rear++] = src;

    while (front < rear) {
        int u = queue[front++];
        if (u == dest)
            break;
        p = graph[u];
        while (p != NULL) {
            if (!visited[p->dest]) {
                visited[p->dest] = 1;
                parent[p->dest] = u;
                queue[rear++] = p->dest;
            }
            p = p->next;
        }
    }

    if (!visited[dest]) {
        printf("No route found.\n");
        return;
    }

    for (cur = dest; cur != -1; cur = parent[cur])
        path[len++] = cur;

    printf("BFS Route: ");
    for (i = len - 1; i >= 0; i--) {
        printf("%s", places[path[i]]);
        if (i > 0)
            printf(" -> ");
    }
    printf("\n");
}

int main() {
    int choice;
    char line[20];

    buildCampus();
    printf("===== Campus Route Finder =====\n");

    while (1) {
        printf("\n1. Display Campus Connections\n");
        printf("2. Find Route using BFS\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        if (fgets(line, sizeof(line), stdin) == NULL)
            break;
        choice = atoi(line);

        if (choice == 1)
            displayConnections();
        else if (choice == 2)
            findRoute();
        else if (choice == 3) {
            printf("Thank you!\n");
            break;
        } else
            printf("Invalid choice.\n");
    }
    return 0;
}
