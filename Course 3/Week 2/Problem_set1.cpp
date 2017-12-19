#include <stdio.h>
#include <stdlib.h>

typedef struct node tnode;
typedef struct nodelist tnodelist;
typedef struct edge edge_t;

struct node {
    int label;
    int rank;
    tnode *leader;
};

struct nodelist {
    tnode *node;
    tnodelist *next;
};

struct edge {
    tnode *n1;
    tnode *n2;
    int cost;
};

typedef unsigned int unionfind_t;

static int
compar(const void *p1, const void *p2) {
    edge_t *e1 = (edge_t *)p1;
    edge_t *e2 = (edge_t *)p2;

    return (e1->cost - e2->cost);
}

static tnode *
uf_find(tnode *n) {
    if (n == n->leader)
        return n;
    return (uf_find(n->leader));
}

static int
uf_union(tnode *n1, tnode *n2) {
    tnode *l1 = uf_find(n1);
    tnode *l2 = uf_find(n2);

    if (l1 == l2)
        return 0;
    else {
        if (l1->rank > l2->rank) {
            l2->leader = l1;
        } else if (l2->rank > l1->rank) {
            l1->leader = l2;
        } else {
            l1->leader = l2;
            l2->rank++;
        }

        return 1;
    }
}

int main(void) {
    FILE *fp = fopen("clustering1.txt", "r");
#define GOAL 4
    char *line = NULL;
    size_t len;
    ssize_t read;

    int N, M;

    read = getline(&line, &len, fp);
    sscanf(line, "%d\n", &N);
    M = (N*(N-1))/2;
    printf("Number of Nodes: %d\n", N);
    printf("Number of Edges: %d\n", M);

    tnode *nodes = calloc(N+1, sizeof(tnode));
    unionfind_t *uf = calloc(N+1, sizeof(unionfind_t));
    edge_t *edges = calloc(M, sizeof(edge_t));

    for (int i = 1; i <= N; i++) {
        nodes[i].label = i;
        nodes[i].rank = 0;
        nodes[i].leader = &nodes[i];
    }

    int count = 0;
    while ((read = getline(&line, &len, fp)) != -1) {
        int n1, n2, cost;
        sscanf(line, "%d %d %d\n", &n1, &n2, &cost);
        printf("%d -- %d (%d)\n", n1, n2, cost);
        edges[count].n1 = &nodes[n1];
        edges[count].n2 = &nodes[n2];
        edges[count].cost = cost;
        count++;
    }
    printf("Counted edges: %d\n", count);
    M = count;
    qsort(edges, M, sizeof(edge_t), compar);

    for (int i = 0; i < M; i++) {
        printf("%d %d %d\n", edges[i].n1->label, edges[i].n2->label, edges[i].cost);
    }

    int k = N;
    int i = 0;
    int cost;
    while ((k >= GOAL) && (i < M)) {
        if (uf_union(edges[i].n1, edges[i].n2)) {
            k--;
            cost = edges[i].cost;
        }
        i++;
    }
    for (int x = 1; x <= N; x++) {
        printf("Node: %d(%d) - Leader: %d (%d)\n", nodes[x].label, nodes[x].rank, nodes[x].leader->label, nodes[x].leader->rank);
    }
    printf("Answer: %d\n", cost);

    free(edges);
    free(uf);
    free(nodes);
    fclose(fp);
}
