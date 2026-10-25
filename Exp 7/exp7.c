/* 
     Q] Implement three versions of greedy algos for Fractional Knapsack Problem.
       Input should be either given through file or should be randomly generated.
       Plot the time taken and value provided by various strategy to show the comparison.
*/ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct { double w, p; } Item;

int mode; // 0 = max weight, 1 = max profit, 2 = max p/w

double key(Item *t) {
    if (mode == 0) return t->w;
    if (mode == 1) return t->p;
    return t->p / t->w;
}

// sort in descending order of key
int cmp(const void *a, const void *b) {
    double x = key((Item *)a), y = key((Item *)b);
    return (x < y) - (x > y);
}

// greedy fractional knapsack, returns total profit
double knapsack(Item *a, int n, double cap) {
    qsort(a, n, sizeof(Item), cmp);
    double val = 0;
    for (int i = 0; i < n && cap > 0; i++) {
        double take = a[i].w < cap ? a[i].w : cap;  // whole item or a fraction
        val += take * a[i].p / a[i].w;
        cap -= take;
    }
    return val;
}

int main() {
    srand(time(0));
    FILE *f = fopen("knapsack.csv", "w");
    fprintf(f, "n,time_maxW,time_maxP,time_maxPW,val_maxW,val_maxP,val_maxPW\n");
    printf("%8s %10s %10s %10s %12s %12s %12s\n",
           "n", "t_W(ms)", "t_P(ms)", "t_PW(ms)", "val_W", "val_P", "val_PW");

    for (int n = 100000; n <= 1000000; n += 100000) {
        Item *a = malloc(n * sizeof(Item)), *b = malloc(n * sizeof(Item));
        double cap = 0, t[3], v[3];

        for (int i = 0; i < n; i++) {        // random weights and profits 1..100
            a[i].w = rand() % 100 + 1;
            a[i].p = rand() % 100 + 1;
            cap += a[i].w;
        }
        cap /= 2;                            // bag holds half the total weight

        for (mode = 0; mode < 3; mode++) {
            memcpy(b, a, n * sizeof(Item)); // same input for every strategy (makes a new copy each for the algos)
            clock_t s = clock();
            v[mode] = knapsack(b, n, cap);
            t[mode] = (double)(clock() - s) * 1000 / CLOCKS_PER_SEC;
        }

        fprintf(f, "%d,%.2f,%.2f,%.2f,%.0f,%.0f,%.0f\n", n, t[0], t[1], t[2], v[0], v[1], v[2]);
        printf("%8d %10.2f %10.2f %10.2f %12.0f %12.0f %12.0f\n", n, t[0], t[1], t[2], v[0], v[1], v[2]);
        free(a); free(b);
    }
    fclose(f);
    printf("\nSaved to knapsack.csv\n");
    return 0;
}
