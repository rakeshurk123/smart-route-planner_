#include <stdio.h>
#include <limits.h>

#define MAX 10

// Function to print header line
void line() {
    printf("==========================================\n");
}

// Function to find minimum distance node
int minDistance(int dist[], int visited[], int n) {
    int min = INT_MAX, index = -1;

    for (int i = 0; i < n; i++) {
        if (!visited[i] && dist[i] < min) {
            min = dist[i];
            index = i;
        }
    }
    return index;
}

// Function to print path
void printPath(int parent[], int j) {
    if (j == -1)
        return;

    printPath(parent, parent[j]);
    printf("%d ", j);
}

// Dijkstra Algorithm
void dijkstra(int graph[MAX][MAX], int n, int src) {
    int dist[MAX], visited[MAX], parent[MAX];

    for (int i = 0; i < n; i++) {
        dist[i] = INT_MAX;
        visited[i] = 0;
        parent[i] = -1;
    }

    dist[src] = 0;

    for (int count = 0; count < n - 1; count++) {
        int u = minDistance(dist, visited, n);
        if (u == -1) break;

        visited[u] = 1;

        for (int v = 0; v < n; v++) {
            if (!visited[v] && graph[u][v] > 0 &&
                dist[u] + graph[u][v] < dist[v]) {

                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }

    // OUTPUT
    line();
    printf("        SMART ROUTE PLANNER SYSTEM\n");
    line();

    printf("\nSource City : %d\n", src);

    printf("\n------------------------------------------\n");
    printf("Shortest Paths (Dijkstra Algorithm)\n");
    printf("------------------------------------------\n");

    printf("\nDestination\tDistance\tPath\n");
    printf("------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t", i, dist[i]);
        printPath(parent, i);
        printf("\n");
    }

    printf("------------------------------------------\n");
    line();
}

// Function to input graph
void inputGraph(int graph[MAX][MAX], int n) {
    printf("\nEnter Distance Matrix (0 = No path)\n\n");

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("Distance from %d to %d: ", i, j);
            scanf("%d", &graph[i][j]);
        }
        printf("\n");
    }
}

// Main Menu
int main() {
    int graph[MAX][MAX];
    int n, choice, src;

    line();
    printf("     SMART ROUTE PLANNER - MAIN MENU\n");
    line();

    printf("\nEnter number of cities (max %d): ", MAX);
    scanf("%d", &n);

    if (n <= 0 || n > MAX) {
        printf("Invalid number of cities!\n");
        return 0;
    }

    inputGraph(graph, n);

    do {
        line();
        printf("1. Find Shortest Route (Dijkstra)\n");
        printf("2. Exit\n");
        line();

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\nEnter source city (0 to %d): ", n - 1);
                scanf("%d", &src);

                if (src < 0 || src >= n) {
                    printf("Invalid source!\n");
                } else {
                    dijkstra(graph, n, src);
                }
                break;

            case 2:
                printf("\nExiting system...\n");
                break;

            default:
                printf("Invalid choice! Try again.\n");
        }

    } while (choice != 2);

    return 0;
}
