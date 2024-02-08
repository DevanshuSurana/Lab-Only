#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <string.h>
#include <omp.h>
#include <time.h> // Include for time management

#define max 12

void displayMenu(void);
void reset();
void red();
void init_array(int[]);
void display_array(int[]);
void bubbleSort_Serial(int[]);
void bubbleSort_parallel(int[]);
void bubbleSort_parallel_with_explanation(int[]);
void display_array_colored(int[], int, int);
void startTimer(); // Function to start the timer
void stopTimer(); // Function to stop the timer
double elapsedTime(); // Function to get elapsed time

clock_t startTime, endTime; // Variables to hold start and end times

int main(void)
{
    int count = 0;
    char line[256]; /* or other suitable maximum line size */
    int Array[max];
    int choice = -9;
    int alreadyInitialized = 0;
    FILE *file = fopen("Bubble.c", "r");

    while (1)
    {
        displayMenu();
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            init_array(Array);
            alreadyInitialized = 1;
            break;
        case 2:
            if (alreadyInitialized)
                display_array(Array);
            else
                printf("\n Array is not initialized.\n");
            break;
        case 3:
            if (!alreadyInitialized)
            {
                printf("\n Array is not initialized. Please initialize the array first.\n");
                break;
            }
            startTimer(); // Start the timer
            bubbleSort_Serial(Array);
            stopTimer(); // Stop the timer
            printf("\n|The sorted array is:");
            display_array(Array);
            printf("\nElapsed time: %f seconds\n", elapsedTime()); // Display elapsed time
            break;
        case 4:
            if (!alreadyInitialized)
            {
                printf("\n Array is not initialized. Please initialize the array first.\n");
                break;
            }
            startTimer(); // Start the timer
            bubbleSort_parallel(Array);
            stopTimer(); // Stop the timer
            printf("\n|The sorted array is:");
            display_array(Array);
            printf("\nElapsed time: %f seconds\n", elapsedTime()); // Display elapsed time
            break;
        case 5:
            if (!alreadyInitialized)
            {
                printf("\n Array is not initialized. Please initialize the array first.\n");
                break;
            }
            startTimer(); // Start the timer
            bubbleSort_parallel_with_explanation(Array);
            stopTimer(); // Stop the timer
            printf("\nElapsed time: %f seconds\n", elapsedTime()); // Display elapsed time
            break;

        case 6:

            if (file != NULL)
            {
                count = 0;
                while (fgets(line, sizeof line, file) != NULL) /* read a line */
                {
                    count++;
                    if (count > 120 && count < 153)
                        printf(" %s ", line);
                }
                fclose(file);
            }

            break;

        case 7:
            return 1;
            break;

        default:
            printf("\n enter valid option !!");
            break;
        } //end_switch

    } //end_while

    return 1;
} //end_main

void displayMenu(void)
{
    printf("\n\n\n\n\n\n");
    printf("\n_-_-_-_-_-_-_-_ Bubble Sort Assignment 2 of High Performance Computing_-_-_-_-_-_-_-_");
    printf("\n1. Initialize Array");
    printf("\n2. Display Array");
    printf("\n3. Serial Bubble Sort");
    printf("\n4. Parallel Bubble Sort");
    printf("\n5. Parallel Bubble sort with explanation");
    printf("\n6. print the parallel bubble sort code");
    printf("\n7. exit");
} //end_display_Menu

void bubbleSort_parallel(int *a)
{
    int z, i, j, k;
    for (z = 0; z < ceil(max / 2.0); z++) //total iterations needed = max = (even_phase + odd_phase)
    {

#pragma omp parallel for private(j)
        for (j = 0; j < max; j += 2) //even phase of transposition sort
        {
            int temp1;
            if (a[j + 1] < a[j]) //swap logic
            {
                temp1 = a[j + 1];
                a[j + 1] = a[j];
                a[j] = temp1;
            }
        } //end_even_phase of transposition sort

#pragma omp parallel for private(k)
        for (k = 1; k < max - 1; k += 2) //odd phase of transposition sort
        {
            int temp2;
            if (a[k + 1] < a[k]) //swap logic
            {
                temp2 = a[k + 1];
                a[k + 1] = a[k];
                a[k] = temp2;
            }
        } //end_odd_Phase_for_Loop
    }     //end_for_loop_z
} //end bubble parallel

void bubbleSort_parallel_with_explanation(int *a)
{
    int z, i, j, k;
    int even_counter = 0;
    int odd_counter = 0;
    display_array(a);

    printf("\n To sort the given array we are going to use even phase and odd phases.");
    printf("\n Each of theses phases compares element pair which does not have any common element.");

    for (z = 0; z < ceil(max / 2.0); z++) //total iterations needed = max = (even_phase + odd_phase)
    {
        sleep(1);
        printf("\n\n Even phase %d 'th iteration. All the below comparisons are executed in parallel manner .. ", even_counter++);
        for (j = 0; j < max - 1; j += 2) //even phase of transposition sort
        {

            int temp1;
            if (a[j + 1] < a[j]) //swap logic
            {
                temp1 = a[j + 1];
                a[j + 1] = a[j];
                a[j] = temp1;
            }
            display_array_colored(a, j, j + 1);
            sleep(1);
        } //end_even_phase of transposition sort

        sleep(1);

        printf("\n\n Odd phase %d 'th iteration. All the below comparisons are executed in parallel manner .. ", odd_counter++);
        for (k = 1; k < max - 1; k += 2) //odd phase of transposition sort
        {

            int temp2;
            if (a[k + 1] < a[k]) //swap logic
            {
                temp2 = a[k + 1];
                a[k + 1] = a[k];
                a[k] = temp2;
            }
            display_array_colored(a, k, k + 1);
            sleep(1);
        } //end_odd_Phase_for_Loop
    }     //end_for_loop_z
} //bubbleSort_parallel_with_explanation

void bubbleSort_Serial(int *a)
{
    int i, j = 0;
    for (i = 0; i < max; i++)
    {
        for (j = 0; j < max - i - 1; j++)
        {
            int temp;
            if (a[j + 1] < a[j])
            {
                temp = a[j + 1];
                a[j + 1] = a[j];
                a[j] = temp;
            }
        } //end_inner_for
    }     //end_outer_for
} //end_bubbleSort_Serial

void init_array(int *a)
{
    int i = 0;
    printf("\nEnter %d elements for the array:\n", max);
    for (i = 0; i < max; i++)
    {
        printf("Enter element %d: ", i + 1);
        scanf("%d", &a[i]);
    }
} //end_init_array

void display_array(int *a)
{
    int i = 0;
    printf("\n Array = [");
    for (i = 0; i < max; i++)
    {
        printf(" %d ,", a[i]);
    }
    printf("\b]");
} //end_display_array

void display_array_colored(int *a, int x, int y)
{
    int i = 0;
    printf("\n Array = [");
    for (i = 0; i < max; i++)
    {
        if (i == x || i == y)
        {
            red();
            printf(" %d ,", a[i]);
            reset();
        }
        else
            printf(" %d ,", a[i]);
    }
    printf("\b]");
} //end_display_array

void red()
{
    printf("\033[1;31m");
}

void reset()
{
    printf("\033[0m");
}

void startTimer()
{
    startTime = clock(); // Start the timer
}

void stopTimer()
{
    endTime = clock(); // Stop the timer
}

double elapsedTime()
{
    return ((double)(endTime - startTime)) / CLOCKS_PER_SEC; // Calculate the elapsed time
}