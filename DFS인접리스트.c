#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 50
#define TRUE 1
#define FALSE 0

typedef struct GraphNode {
    int vertex;
    struct GraphNode* link;
} GraphNode;

typedef struct GraphType {
    int n; // ������ ����
    GraphNode* adj_list[MAX_VERTICES];
} GraphType;

int visited[MAX_VERTICES]; // �湮�� ������ üũ�ϴ� �뵵�� �迭

// �׷��� �ʱ�ȭ
void init(GraphType* g) {
    g->n = 0;
    for (int i = 0; i < MAX_VERTICES; i++)
        g->adj_list[i] = NULL;
}

// �޸� ����
void destroy_graph(GraphType* g) {
    for (int i = 0; i < g->n; i++) {
        GraphNode* node = g->adj_list[i];
        while (node != NULL) {
            GraphNode* temp = node;
            node = node->link;
            free(temp);
        }
    }
}

// ���� ���� ����
void insert_vertex(GraphType* g, int v) {
    if ((g->n) + 1 > MAX_VERTICES) {
        fprintf(stderr, "�׷���: ������ ���� �ʰ�\n");
        return;
    }
    g->n++;
}

// ���� ���� ����
void insert_edge(GraphType* g, int u, int v) {
    if (u >= g->n || v >= g->n) {
        fprintf(stderr, "�׷���: ���� ��ȣ ����\n");
        return;
    }
    GraphNode* node = (GraphNode*)malloc(sizeof(GraphNode));
    node->vertex = v;
    node->link = g->adj_list[u];
    g->adj_list[u] = node;
}

// ���� �켱 Ž��
void dfs_list(GraphType* g, int v) {
    GraphNode* w;
    visited[v] = TRUE;
    printf("���� %d -> ", v);
    for (w = g->adj_list[v]; w; w = w->link)
        if (!visited[w->vertex])
            dfs_list(g, w->vertex);
}

int main(void) {
    GraphType* g = (GraphType*)malloc(sizeof(GraphType));
    init(g);

    for (int i = 0; i < 4; i++) {
        insert_vertex(g, i);
    }

    insert_edge(g, 0, 1);
    insert_edge(g, 0, 2);
    insert_edge(g, 0, 3);
    insert_edge(g, 1, 2);
    insert_edge(g, 2, 3);

    // �湮 �迭 �ʱ�ȭ
    for (int i = 0; i < g->n; i++)
        visited[i] = FALSE;

    printf("���� �켱 Ž��\n");
    dfs_list(g, 0);
    printf("\n");

    destroy_graph(g);
    free(g);
    return 0;
}
