#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100000
#define REP 2000            /* repeat each search, for stable timing */

int a[MAX], n;
volatile int sink;          /* stops the compiler deleting timed loops */

/* ---------- the two searches ---------- */
int linear(int a[], int n, int key)
{
    int i;
    for (i = 0; i < n; i++)
        if (a[i] == key) return i;
    return -1;
}

int binary(int a[], int n, int key)   /* array must be sorted */
{
    int lo = 0, hi = n - 1, mid;
    while (lo <= hi) {
        mid = (lo + hi) / 2;
        if (a[mid] == key) return mid;
        if (a[mid] < key)  lo = mid + 1;
        else               hi = mid - 1;
    }
    return -1;
}

int cmp(const void *x, const void *y) { return *(int *)x - *(int *)y; }

/* ---------- 3 ways of taking input ---------- */
int fromFile(int a[])
{
    FILE *f = fopen("input.txt", "r");
    int n = 0;
    if (!f) { printf("input.txt not found\n"); return 0; }
    while (n < MAX && fscanf(f, "%d", &a[n]) == 1) n++;
    fclose(f);
    return n;
}

int fromUser(int a[])
{
    int i, n;
    printf("How many numbers? ");  scanf("%d", &n);
    printf("Enter %d numbers: ", n);
    for (i = 0; i < n; i++) scanf("%d", &a[i]);
    return n;
}

int fromRandom(int a[])
{
    int i, n;
    printf("How many numbers? ");  scanf("%d", &n);
    srand(time(NULL));
    for (i = 0; i < n; i++) a[i] = rand() % 1000;
    return n;
}

/* ---------- timing -> timing.csv (open in Excel) ---------- */
void benchmark(void)
{
    int sizes[] = {1000, 5000, 10000, 20000, 50000, 100000};
    int s, r, i, key;
    clock_t t;
    double tl, tb;
    FILE *f = fopen("timing.csv", "w");

    fprintf(f, "Size,Linear (ns),Binary (ns)\n");
    for (s = 0; s < 6; s++) {
        n = sizes[s];
        for (i = 0; i < n; i++) a[i] = i;   /* already sorted */
        key = -1;                           /* worst case: absent */

        t = clock();
        for (r = 0; r < REP; r++) sink = linear(a, n, key);
        tl = (double)(clock() - t) * 1e9 / CLOCKS_PER_SEC / REP;

        t = clock();
        for (r = 0; r < REP; r++) sink = binary(a, n, key);
        tb = (double)(clock() - t) * 1e9 / CLOCKS_PER_SEC / REP;

        fprintf(f, "%d,%.0f,%.0f\n", n, tl, tb);
        printf("n=%-7d linear=%9.0f ns   binary=%5.0f ns\n", n, tl, tb);
    }
    fclose(f);
    printf("Saved timing.csv\n");
}

/* ---------- main ---------- */
int main(void)
{
    int ch, key, i;

    printf("1.File  2.User  3.Random  4.Benchmark\nChoice: ");
    scanf("%d", &ch);

    if (ch == 4) { benchmark(); return 0; }

    if (ch == 1) n = fromFile(a);
    else if (ch == 2) n = fromUser(a);
    else if (ch == 3) n = fromRandom(a);
    else { printf("Wrong choice\n"); return 1; }
    if (n == 0) return 1;

    printf("Key to search: ");  scanf("%d", &key);
    printf("Linear search: index %d\n", linear(a, n, key));

    qsort(a, n, sizeof(int), cmp);          /* binary needs sorted data */
    printf("Sorted array: ");
    for (i = 0; i < n && i < 20; i++) printf("%d ", a[i]);
    printf("\nBinary search: index %d\n", binary(a, n, key));
    return 0;
}