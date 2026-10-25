#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* LCS length using DP with only two rows (memory O(n), time O(n*n)) */
int lcs(char *a, char *b, int n) {
    int *prev = calloc(n + 1, sizeof(int));
    int *cur  = calloc(n + 1, sizeof(int));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (a[i-1] == b[j-1]) cur[j] = prev[j-1] + 1;           /* match: extend */
            else cur[j] = prev[j] > cur[j-1] ? prev[j] : cur[j-1];  /* skip one char */
        }
        int *t = prev; prev = cur; cur = t;                         /* next row */
    }
    int r = prev[n];
    free(prev); free(cur);
    return r;
}

int main() {
    srand(time(NULL));
    FILE *f = fopen("lcs.csv", "w");
    fprintf(f, "n,time_ms,lcs_length\n");

    for (int n = 1000; n <= 15000; n += 1000) {
        char *a = malloc(n), *b = malloc(n);
        for (int i = 0; i < n; i++) {           /* random DNA-like sequences (used by real life bioscientists)*/
            a[i] = "ACGT"[rand() % 4];
            b[i] = "ACGT"[rand() % 4];
        }
        clock_t s = clock();
        int len = lcs(a, b, n);
        double ms = (double)(clock() - s) * 1000 / CLOCKS_PER_SEC;

        printf("n=%5d  time=%8.2f ms  LCS=%d\n", n, ms, len);
        fprintf(f, "%d,%.2f,%d\n", n, ms, len);
        free(a); free(b);
    }
    fclose(f);
    printf("Saved to lcs.csv\n");
    return 0;
}