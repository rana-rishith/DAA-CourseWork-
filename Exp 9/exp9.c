#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXN 5001   // max projects
#define MAXW 1001   // max budget

int cost[MAXN], profit[MAXN], dp[MAXW];
volatile int sink;       // stops compiler skipping the timed work
char keep[MAXN][MAXW];   // keep[i][w] = 1 if project i chosen at budget w

// 0/1 Knapsack DP: best profit with budget W using projects 1..n
int knapsack(int n, int W) {
    for (int w = 0; w <= W; w++) dp[w] = 0;
    for (int i = 1; i <= n; i++)
        for (int w = W; w >= 0; w--) {          // right to left: each project used once
            keep[i][w] = 0;
            if (cost[i] <= w && dp[w - cost[i]] + profit[i] > dp[w]) {
                dp[w] = dp[w - cost[i]] + profit[i];
                keep[i][w] = 1;
            }
        }
    return dp[W];
}

int main() {
    // ---- Part 1: sample project selection ( to check the if it is working or not  like a small prototype) ----
    int c[] = {5, 4, 6, 3, 2}, p[] = {10, 40, 30, 50, 20};
    int n = 5, W = 10;
    for (int i = 1; i <= n; i++) { cost[i] = c[i - 1]; profit[i] = p[i - 1]; }

    printf("Budget = %d\nMax profit = %d\nSelected projects:", W, knapsack(n, W));
    for (int i = n, w = W; i >= 1; i--)          // backtrack
        if (keep[i][w]) { printf(" P%d", i); w -= cost[i]; }
    printf("\n\n");

    // ---- Part 2: timing (budget fixed, n varies) ----
    FILE *f = fopen("exp9timings.csv", "w");
    fprintf(f, "n,time_ms\n");
    printf("n\ttime(ms)\n");
    int R = 20;                                  // repeats for a stable average
    srand(1);
    for (n = 500; n <= 5000; n += 500) {
        for (int i = 1; i <= n; i++) { cost[i] = rand() % 100 + 1; profit[i] = rand() % 500 + 1; }
        clock_t s = clock();
        for (int r = 0; r < R; r++) sink = knapsack(n, 1000);
        double t = (double)(clock() - s) * 1000 / CLOCKS_PER_SEC / R;
        printf("%d\t%.3f\n", n, t);
        fprintf(f, "%d,%.3f\n", n, t);
    }
    fclose(f);
    return 0;
}