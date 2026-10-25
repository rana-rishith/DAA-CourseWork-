#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define W 1000     // knapsack capacity
#define MAXN 10000
#define REPS 10    // repeat each run, then average

int wt[MAXN], val[MAXN], idx[MAXN], mode;

// sort order for greedy: 0 = lightest first, 1 = highest profit first, 2 = best P/W first
int cmp(const void *a, const void *b) {
    int i = *(int *)a, j = *(int *)b;
    if (mode == 0) return wt[i] - wt[j];
    if (mode == 1) return val[j] - val[i];
    return val[j] * wt[i] - val[i] * wt[j];
}

// greedy: sort items, take each one if it still fits
int greedy(int n, int m) {
    mode = m;
    for (int i = 0; i < n; i++) idx[i] = i;
    qsort(idx, n, sizeof(int), cmp);
    int cap = W, p = 0;
    for (int k = 0; k < n; k++)
        if (wt[idx[k]] <= cap) { cap -= wt[idx[k]]; p += val[idx[k]]; }
    return p;
}

int big(int a, int b) { return a > b ? a : b; }

// DP: K[i][w] = best profit using first i items with capacity w (always optimal)
int dp(int n) {
    int (*K)[W + 1] = malloc((n + 1) * sizeof *K);
    for (int i = 0; i <= n; i++)
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0)  K[i][w] = 0;
            else if (wt[i-1] <= w) K[i][w] = big(val[i-1] + K[i-1][w - wt[i-1]], K[i-1][w]);
            else                   K[i][w] = K[i-1][w];
        }
    int ans = K[n][W];
    free(K);
    return ans;
}

// average time (ms) of method m: 0,1,2 = greedy by W, P, P/W   3 = DP
double timeit(int n, int m, int *p) {
    clock_t s = clock();
    for (int r = 0; r < REPS; r++) *p = (m < 3) ? greedy(n, m) : dp(n);
    return (double)(clock() - s) * 1000 / CLOCKS_PER_SEC / REPS;
}

int main() {
    srand(time(NULL));
    FILE *f = fopen("ZEROknapsack.csv", "w");
    fprintf(f, "n,t_W(ms),t_P(ms),t_PW(ms),t_DP(ms),P_W,P_P,P_PW,P_DP\n");
    printf("    n |  t_W   t_P   t_PW   t_DP (ms) | profit: W    P    PW    DP\n");

    for (int n = 1000; n <= MAXN; n += 1000) {
        for (int i = 0; i < n; i++) {          // random input
            wt[i]  = rand() % 100 + 1;
            val[i] = rand() % 100 + 1;
        }
        double t[4]; int p[4];
        for (int m = 0; m < 4; m++) t[m] = timeit(n, m, &p[m]);

        printf("%5d | %5.2f %5.2f %5.2f %6.2f | %5d %5d %5d %5d\n",
               n, t[0], t[1], t[2], t[3], p[0], p[1], p[2], p[3]);
        fprintf(f, "%d,%.3f,%.3f,%.3f,%.3f,%d,%d,%d,%d\n",
                n, t[0], t[1], t[2], t[3], p[0], p[1], p[2], p[3]);
    }
    fclose(f);
    printf("Saved to ZEROknapsack.csv\n");
    return 0;
}