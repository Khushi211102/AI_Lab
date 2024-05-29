#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Structure to represent a point in 2D space
typedef struct {
    int x;
    int y;
} Point;

// Function to calculate Euclidean distance between two points
double euclidean_distance(Point point1, Point point2) {
    return sqrt(pow(point1.x - point2.x, 2) + pow(point1.y - point2.y, 2));
}

// Nearest Neighbor Algorithm for TSP
void nearest_neighbor_tsp(Point points[], int num_points) {
    int unvisited[num_points];
    for (int i = 0; i < num_points; i++) {
        unvisited[i] = 1;  // Set all points as unvisited
    }
    int tour[num_points + 1];  // The tour to store the order of visited points
    int current_point = 0;  // Start from the first point
    unvisited[current_point] = 0;  // Mark the current point as visited
    int tour_index = 0;

    while (1) {
        tour[tour_index] = current_point;
        tour_index++;

        int nearest_point = -1;
        double min_distance = -1;

        // Find the nearest unvisited point
        for (int i = 0; i < num_points; i++) {
            if (unvisited[i]) {
                double distance = euclidean_distance(points[current_point], points[i]);
                if (min_distance < 0 || distance < min_distance) {
                    min_distance = distance;
                    nearest_point = i;
                }
            }
        }

        if (nearest_point == -1) {
            break;  // No unvisited point found, end the loop
        }

        unvisited[nearest_point] = 0;  // Mark the nearest point as visited
        current_point = nearest_point;  // Move to the nearest point
    }

    tour[tour_index] = 0;  // Return to the starting point to complete the tour

    // Print the tour
    //printf("TSP Solution Using Nearest Neighbor Algorithm:\n");
    printf("Tour order: ");
    for (int i = 0; i <= num_points; i++) {
        printf("%d ", tour[i]);
    }
}

int main() {
    int num_points;
    
    // Prompt user for the number of points
    printf("Enter the number of points: ");
    scanf("%d", &num_points);
    
    // Allocate memory for the points
    Point *points = malloc(num_points * sizeof(Point));
    
    // Input coordinates for each point
    printf("Enter the coordinates for each point (x y):\n");
    for (int i = 0; i < num_points; i++) {
        printf("Point %d: ", i );
        scanf("%d %d", &points[i].x, &points[i].y);
    }

    // Solve TSP using nearest neighbor algorithm
    nearest_neighbor_tsp(points, num_points);

    // Free dynamically allocated memory
    free(points);

    return 0;
}
