#include <stdio.h>

int a[50][50], vis[50], n, e, c;   /* a = weights, vis = component number */

void dfs(int v) {
    int i;
    vis[v] = c;
    printf("%d ", v);
    for (i = 1; i <= n; i++)
        if (a[v][i] && !vis[i]) dfs(i);
}

void bfs(int s) {
    int q[50], f = 0, r = 0, v, i;
    vis[s] = c;
    q[r++] = s;
    while (f < r) {
        v = q[f++];
        printf("%d ", v);
        for (i = 1; i <= n; i++)
            if (a[v][i] && !vis[i]) { vis[i] = c; q[r++] = i; }
    }
}

void clear() { int i; for (i = 1; i <= n; i++) vis[i] = 0; }

int main() {
    FILE *fp = fopen("graph.txt", "r");
    int i, j, u, v, w, s, x, y;

    if (!fp) { printf("graph.txt not found\n"); return 1; }
    fscanf(fp, "%d %d", &n, &e);            /* header */
    e = 0;
    while (fscanf(fp, "%d %d %d", &u, &v, &w) == 3) {
        a[u][v] = a[v][u] = w;              /* undirected edge, weight stored */
        if (u > n) n = u;                   /* fix vertex count from data */
        if (v > n) n = v;
        e++;                                /* real edge count */
    }
    fclose(fp);

    printf("Vertices=%d  Edges=%d\nAdjacency matrix:\n", n, e);
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) printf("%3d", a[i][j]);
        printf("\n");
    }

    printf("\nEnter start vertex: ");
    scanf("%d", &s);
    c = 1;
    clear(); printf("BFS: "); bfs(s);
    clear(); printf("\nDFS: "); dfs(s);

    clear(); c = 0;                          /* ---- connectivity ---- */
    printf("\n\nConnected components:\n");
    for (i = 1; i <= n; i++)
        if (!vis[i]) { c++; printf("C%d: ", c); dfs(i); printf("\n"); }
    printf("Graph is %s (%d component/s)\n", c == 1 ? "CONNECTED" : "NOT CONNECTED", c);

    printf("\nCheck path between two vertices: ");
    scanf("%d %d", &x, &y);
    printf("%d and %d are %sconnected\n", x, y, vis[x] == vis[y] ? "" : "NOT ");
    return 0;
}