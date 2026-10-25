#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int arr[10], i, max, min;

    srand(time(0));   // makes numbers different each run

    for (i = 0; i < 10; i++) {
        arr[i] = rand() % 100 + 1;   // random number from 1 to 100
        printf("%d ", arr[i]);
    }
    printf("\n");

    max = arr[0];
    min = arr[0];

    for (i = 1; i < 10; i++) {
        if (arr[i] > max) max = arr[i];
        if (arr[i] < min) min = arr[i];
    }

    printf("Largest  = %d\n", max);
    printf("Smallest = %d\n", min);

    return 0;
}