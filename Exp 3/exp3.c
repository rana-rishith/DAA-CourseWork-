#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* ---------------- INPUT FUNCTIONS ---------------- */

void fromFile(int a[], int n, char *fname) {
    FILE *f = fopen(fname, "r");
    if (f == NULL) { printf("Cannot open %s\n", fname); exit(1); }
    for (int i = 0; i < n; i++) fscanf(f, "%d", &a[i]);
    fclose(f);
}

void fromUser(int a[], int n) {
    printf("Enter %d numbers: ", n);
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);
}

void fromRandom(int a[], int n) {
    for (int i = 0; i < n; i++) a[i] = rand() % 10000;
}

/* ---------------- SORTING FUNCTIONS ---------------- */

void insertionSort(int a[], int n) {
    for (int i = 1; i < n; i++) {
        int key = a[i], j = i - 1;
        while (j >= 0 && a[j] > key) { a[j + 1] = a[j]; j--; }
        a[j + 1] = key;
    }
}

void bubbleSort(int a[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - 1 - i; j++)
            if (a[j] > a[j + 1]) { int t = a[j]; a[j] = a[j + 1]; a[j + 1] = t; }
}

void selectionSort(int a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int m = i;
        for (int j = i + 1; j < n; j++) if (a[j] < a[m]) m = j;
        int t = a[i]; a[i] = a[m]; a[m] = t;
    }
}

/* ------ copies the array, sorts the copy, returns time taken ------ */
double timeSort(void (*sort)(int[], int), int src[], int n) {
    int *a = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) a[i] = src[i];   /* same data for every sort */
    clock_t s = clock();
    sort(a, n);
    clock_t e = clock();
    free(a);
    return (double)(e - s) / CLOCKS_PER_SEC;
}

/* ---------------- MAIN ---------------- */

int main(void) {
    int ch, n;
    srand(time(NULL));

    printf("Input from:  1.File  2.User  3.Random\nChoice: ");
    scanf("%d", &ch);
    printf("Enter size n: ");
    scanf("%d", &n);

    int *a = malloc(n * sizeof(int));
    if (ch == 1)      fromFile(a, n, "input.txt");
    else if (ch == 2) fromUser(a, n);
    else              fromRandom(a, n);

    printf("\nInsertion : %f sec\n", timeSort(insertionSort, a, n));
    printf("Bubble    : %f sec\n", timeSort(bubbleSort, a, n));
    printf("Selection : %f sec\n", timeSort(selectionSort, a, n));

    if (n <= 20) {                       /* show result for small inputs */
        insertionSort(a, n);
        printf("Sorted: ");
        for (int i = 0; i < n; i++) printf("%d ", a[i]);
        printf("\n");
    }
    free(a);

    /* ---- benchmark on random data of different sizes, for the graph ---- */
    int sizes[5] = {1000, 2000, 4000, 8000, 16000};
    FILE *f = fopen("times.csv", "w");
    fprintf(f, "n,Insertion,Bubble,Selection\n");

    printf("\nBenchmarking...\n");
    for (int k = 0; k < 5; k++) {
        int m = sizes[k];
        int *b = malloc(m * sizeof(int));
        fromRandom(b, m);
        fprintf(f, "%d,%f,%f,%f\n", m,
                timeSort(insertionSort, b, m),
                timeSort(bubbleSort, b, m),
                timeSort(selectionSort, b, m));
        printf("n = %d done\n", m);
        free(b);
    }
    fclose(f);
    printf("times.csv created. Open it in Excel and plot n vs time.\n");
    return 0;
}
