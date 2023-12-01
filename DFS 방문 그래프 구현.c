#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 50
#define TRUE 1
#define FALSE 0

typedef struct GraphType {
    int n; // ������ ����
    int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int visited[MAX_VERTICES]; // �湮�� ������ üũ�ϴ� �뵵�� �迭

// �׷��� �ʱ�ȭ
void init(GraphType* g) {
    int r, c;
    g->n = 0;
    for (r = 0; r < MAX_VERTICES; r++)
        for (c = 0; c < MAX_VERTICES; c++)
            g->adj_mat[r][c] = 0;
}

// ���� ���� ����
void insert_vertex(GraphType* g, int v) {
    if (((g->n) + 1) > MAX_VERTICES) {
        fprintf(stderr, "�׷���: ������ ���� �ʰ�\n");
        return;
    }
    g->n++;
}

// ���� ���� ����
void insert_edge(GraphType* g, int start, int end) {
    if (start >= g->n || end >= g->n) {
        fprintf(stderr, "�׷���: ���� ��ȣ ����\n");
        return;
    }
    g->adj_mat[start][end] = 1;
    g->adj_mat[end][start] = 1; // ����� ����
}

// ���� �켱 Ž��
void dfs_mat(GraphType* g, int v) {
    int w;
    visited[v] = TRUE; // ���� v�� �湮 ǥ��
    printf("���� %d -> ", v); // �湮�� ���� ���
    for (w = 0; w < g->n; w++) // ���� ���� Ž��
        if (g->adj_mat[v][w] && !visited[w])
            dfs_mat(g, w); // ���� w���� DFS ���� ����
}

int main(void) {
    GraphType* g;
    g = (GraphType*)malloc(sizeof(GraphType));
    init(g);
    for (int i = 0; i < 4; i++)
        insert_vertex(g, i);
    insert_edge(g, 0, 1);
    insert_edge(g, 0, 2);
    insert_edge(g, 0, 3);
    insert_edge(g, 1, 2);
    insert_edge(g, 2, 3);

    // �湮 �迭 �ʱ�ȭ
    for (int i = 0; i < MAX_VERTICES; i++)
        visited[i] = FALSE;

    printf("���� �켱 Ž��\n");
    dfs_mat(g, 0);
    printf("\n");
    free(g);
    return 0;
}
//visited �迭 ���� �߰�, ���� �켱 Ž��(DFS)���� �� ������ �湮 ���θ� �����ϱ� ����
//�� ������ ���� �湮 ���¸� TRUE �Ǵ� FALSE�� �����մϴ�.
//main �Լ����� visited �迭 �ʱ�ȭ : main �Լ����� visited �迭�� ��� ��Ҹ� FALSE�� �ʱ�ȭ�ϴ� �κ��� �߰�