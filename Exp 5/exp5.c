#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* ---------- Merge Sort ---------- */
void merge(int a[], int l, int m, int r) {
    int n = r - l + 1, i = l, j = m + 1, k = 0;
    int *t = malloc(n * sizeof(int));
    while (i <= m && j <= r) t[k++] = (a[i] <= a[j]) ? a[i++] : a[j++];
    while (i <= m) t[k++] = a[i++];
    while (j <= r) t[k++] = a[j++];
    for (k = 0; k < n; k++) a[l + k] = t[k];
    free(t);
}

void mergeSort(int a[], int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        mergeSort(a, l, m);
        mergeSort(a, m + 1, r);
        merge(a, l, m, r);
    }
}

/* ---------- Quick Sort ---------- */
int partition(int a[], int l, int r) {
    int p = a[r], i = l - 1, j, tmp;
    for (j = l; j < r; j++)
        if (a[j] < p) { i++; tmp = a[i]; a[i] = a[j]; a[j] = tmp; }
    tmp = a[i + 1]; a[i + 1] = a[r]; a[r] = tmp;
    return i + 1;
}

void quickSort(int a[], int l, int r) {
    if (l < r) {
        int p = partition(a, l, r);
        quickSort(a, l, p - 1);
        quickSort(a, p + 1, r);
    }
}

/* ---------- Benchmark ---------- */
int main() {
    int sizes[] = {10000, 50000, 100000, 500000, 1000000};
    int cases = 5, c, i;
    clock_t s;
    double tq, tm;

    printf("n,QuickSort(s),MergeSort(s)\n");

    for (c = 0; c < cases; c++) {
        int n = sizes[c];
        int *base = malloc(n * sizeof(int));
        int *a = malloc(n * sizeof(int));

        srand(1);                                  /* same data every run */
        for (i = 0; i < n; i++) base[i] = rand();

        for (i = 0; i < n; i++) a[i] = base[i];    /* fresh copy */
        s = clock();
        quickSort(a, 0, n - 1);
        tq = (double)(clock() - s) / CLOCKS_PER_SEC;

        for (i = 0; i < n; i++) a[i] = base[i];    /* fresh copy */
        s = clock();
        mergeSort(a, 0, n - 1);
        tm = (double)(clock() - s) / CLOCKS_PER_SEC;

        printf("%d,%.4f,%.4f\n", n, tq, tm);
        free(base); free(a);
    }
    return 0;
}