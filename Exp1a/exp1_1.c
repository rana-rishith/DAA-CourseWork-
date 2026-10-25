#include <stdio.h>

int main() {
    FILE *in, *out;
    int num, max, min, count = 0;

    in = fopen("input.txt", "r");
    if (in == NULL) {
        printf("Cannot open input.txt\n");
        return 1;
    }

    while (fscanf(in, "%d", &num) == 1) {
        if (count == 0) {          // first number
            max = num;
            min = num;
        }
        if (num > max) max = num;
        if (num < min) min = num;
        count++;
    }
    fclose(in);

    if (count == 0) {
        printf("File is empty\n");
        return 1;
    }

    out = fopen("output.txt", "w");
    fprintf(out, "Largest  = %d\n", max);
    fprintf(out, "Smallest = %d\n", min);
    fclose(out);

    printf("Done. Check output.txt\n");
    return 0;
}