#include <stdio.h>

void maxmin(int a[], int i, int j, int *max, int *min) {
    int mx1, mn1, mid;

    if (i == j)                 /* one element */
        *max = *min = a[i];
    else if (i == j - 1) {      /* two elements */
        *max = (a[i] > a[j]) ? a[i] : a[j];
        *min = (a[i] < a[j]) ? a[i] : a[j];
    } else {                    /* divide */
        mid = (i + j) / 2;
        maxmin(a, i, mid, max, min);          /* left half  */
        maxmin(a, mid + 1, j, &mx1, &mn1);  /* right half */
        if (mx1 > *max) *max = mx1;           /* combine */
        if (mn1 < *min) *min = mn1;
    }
}

int main(void) {
    int a[100], n, i, max, min;

    printf("Enter n: ");
    scanf("%d", &n);
    printf("Enter %d numbers: ", n);
    for (i = 0; i < n; i++)
        scanf("%d", &a[i]);

    maxmin(a, 0, n - 1, &max, &min);
    printf("Max = %d\nMin = %d\n", max, min);
    return 0;
}