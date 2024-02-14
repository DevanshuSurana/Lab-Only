#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

// Function prototypes
void bubbleSort_Optimized(int *, int);
void bubbleSort_NonOptimized(int *, int);
void printArray(int *, int);

int main() {
    int size;
    printf("Enter the size of the array: ");
    scanf("%d", &size);

    // Allocate memory for the array
    int *array_optimized = (int *)malloc(size * sizeof(int));
    int *array_non_optimized = (int *)malloc(size * sizeof(int));
    if (array_optimized == NULL || array_non_optimized == NULL) {
        printf("Memory allocation failed.");
        return 1;
    }

    // Fill the arrays with random values
    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        array_optimized[i] = rand() % 1000; // Generating random numbers between 0 and 999
        array_non_optimized[i] = array_optimized[i]; // Copy the same data to the non-optimized array
    }

    // Print unsorted arrays
    printf("\nUnsorted Arrays:\n");
    printf("Optimized Bubble Sort:\n");
    printArray(array_optimized, size);
    printf("Non-Optimized Bubble Sort:\n");
    printArray(array_non_optimized, size);

    // Perform optimized bubble sort
    printf("\nPerforming Optimized Bubble Sort...\n");
    clock_t start = clock();
    bubbleSort_Optimized(array_optimized, size);
    clock_t end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Optimized Bubble Sort took %f seconds.\n", time_taken);

    // Perform non-optimized bubble sort
    printf("\nPerforming Non-Optimized Bubble Sort...\n");
    start = clock();
    bubbleSort_NonOptimized(array_non_optimized, size);
    end = clock();
    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Non-Optimized Bubble Sort took %f seconds.\n", time_taken);

    // Print sorted arrays
    printf("\nSorted Arrays:\n");
    printf("Optimized Bubble Sort:\n");
    printArray(array_optimized, size);
    printf("Non-Optimized Bubble Sort:\n");
    printArray(array_non_optimized, size);

    // Free dynamically allocated memory
    free(array_optimized);
    free(array_non_optimized);

    return 0;
}

// Optimized Bubble Sort Algorithm
void bubbleSort_Optimized(int *a, int size) {
    int i, j;
    int swapped;
    for (i = 0; i < size - 1; i++) {
        swapped = 0; // Flag to check if any swaps were made in this pass
        #pragma omp parallel for private(j)
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

// Non-Optimized Bubble Sort Algorithm
void bubbleSort_NonOptimized(int *a, int size) {
    int i, j;
    #pragma omp parallel for private(i, j)
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

// Function to print an array
void printArray(int *a, int size) {
    printf("[");
    for (int i = 0; i < size; i++) {
        printf(" %d", a[i]);
        if (i != size - 1) {
            printf(",");
        }
    }
    printf(" ]\n");
}