#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

// Function prototypes
void bubbleSort_Serial_NonOptimized(int *, int);
void bubbleSort_Serial_Optimized(int *, int);
void bubbleSort_Parallel_Optimized(int *, int);
void printTimeGraph(double, double, double);

int main() {
    int size;
    printf("Enter the size of the array: ");
    scanf("%d", &size);

    // Allocate memory for the arrays
    int *array_serial_non_optimized = (int *)malloc(size * sizeof(int));
    int *array_serial_optimized = (int *)malloc(size * sizeof(int));
    int *array_parallel_optimized = (int *)malloc(size * sizeof(int));
    if (array_serial_non_optimized == NULL || array_serial_optimized == NULL || array_parallel_optimized == NULL) {
        printf("Memory allocation failed.");
        return 1;
    }

    // Fill the arrays with random values
    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        array_serial_non_optimized[i] = rand() % 1000; // Generating random numbers between 0 and 999
        array_serial_optimized[i] = array_serial_non_optimized[i]; // Copy the same data to the optimized array
        array_parallel_optimized[i] = array_serial_non_optimized[i]; // Copy the same data to the parallel optimized array
    }

    // Perform serial non-optimized bubble sort
    printf("\nPerforming Serial Non-Optimized Bubble Sort...\n");
    clock_t start = clock();
    bubbleSort_Serial_NonOptimized(array_serial_non_optimized, size);
    clock_t end = clock();
    double time_taken_serial_non_optimized = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Perform serial optimized bubble sort
    printf("\nPerforming Serial Optimized Bubble Sort...\n");
    start = clock();
    bubbleSort_Serial_Optimized(array_serial_optimized, size);
    end = clock();
    double time_taken_serial_optimized = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Perform parallel optimized bubble sort
    printf("\nPerforming Parallel Optimized Bubble Sort...\n");
    start = clock();
    bubbleSort_Parallel_Optimized(array_parallel_optimized, size);
    end = clock();
    double time_taken_parallel_optimized = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Print time complexity graph
    printTimeGraph(time_taken_serial_non_optimized, time_taken_serial_optimized, time_taken_parallel_optimized);

    // Free dynamically allocated memory
    free(array_serial_non_optimized);
    free(array_serial_optimized);
    free(array_parallel_optimized);

    return 0;
}

// Serial Non-Optimized Bubble Sort Algorithm
void bubbleSort_Serial_NonOptimized(int *a, int size) {
    int i, j;
    for (i = 0; i < size - 1; i++) {
        for (j = 0; j < size - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                // Swap elements
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}

// Serial Optimized Bubble Sort Algorithm
void bubbleSort_Serial_Optimized(int *a, int size) {
    int i, j;
    int swapped;
    for (i = 0; i < size - 1; i++) {
        swapped = 0; // Flag to check if any swaps were made in this pass
        for (j = 0; j < size - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                // Swap elements
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
                swapped = 1; // Set swapped flag
            }
        }
        // If no swaps were made in the pass, array is already sorted
        if (!swapped) {
            break;
        }
    }
}

// Parallel Optimized Bubble Sort Algorithm
void bubbleSort_Parallel_Optimized(int *a, int size) {
    int i, j;
    //int swapped;
    for (i = 0; i < size - 1; i++) {
        //swapped = 0; // Flag to check if any swaps were made in this pass
        #pragma omp parallel for private(j) shared(a, swapped)
        for (j = 0; j < size - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                // Swap elements
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
                //swapped = 1; // Set swapped flag
            }
        }
        // If no swaps were made in the pass, array is already sorted
        //if (!swapped) {
            //break;
        //}
    }
}

// Function to print time complexity graph
void printTimeGraph(double time_taken_serial_non_optimized, double time_taken_serial_optimized, double time_taken_parallel_optimized) {
    // Find the maximum time taken among the three functions
    double max_time = time_taken_serial_non_optimized;
    if (time_taken_serial_optimized > max_time) {
        max_time = time_taken_serial_optimized;
    }
    if (time_taken_parallel_optimized > max_time) {
        max_time = time_taken_parallel_optimized;
    }

    // Calculate the bar lengths based on the maximum time
    int bar_length_non_optimized = (int)(time_taken_serial_non_optimized / max_time * 50);
    int bar_length_optimized = (int)(time_taken_serial_optimized / max_time * 50);
    int bar_length_parallel = (int)(time_taken_parallel_optimized / max_time * 50);

    // Print the time graph
    printf("\nTime Complexity Graph:\n");
    printf("Serial Non-Optimized Bubble Sort: ");
    for (int i = 0; i < bar_length_non_optimized; i++) {
        printf("*");
    }
    printf(" %.6f seconds\n", time_taken_serial_non_optimized);

    printf("Serial Optimized Bubble Sort:     ");
    for (int i = 0; i < bar_length_optimized; i++) {
        printf("*");
    }
    printf(" %.6f seconds\n", time_taken_serial_optimized);

    printf("Parallel Optimized Bubble Sort:   ");
    for (int i = 0; i < bar_length_parallel; i++) {
        printf("*");
    }
    printf(" %.6f seconds\n", time_taken_parallel_optimized);
}
