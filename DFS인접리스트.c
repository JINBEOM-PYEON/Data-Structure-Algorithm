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
    int n; // 정점의 개수
    GraphNode* adj_list[MAX_VERTICES];
} GraphType;

int visited[MAX_VERTICES]; // 방문한 정점을 체크하는 용도의 배열

// 그래프 초기화
void init(GraphType* g) {
    g->n = 0;
    for (int i = 0; i < MAX_VERTICES; i++)
        g->adj_list[i] = NULL;
}

// 메모리 해제
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

// 정점 삽입 연산
void insert_vertex(GraphType* g, int v) {
    if ((g->n) + 1 > MAX_VERTICES) {
        fprintf(stderr, "그래프: 정점의 개수 초과\n");
        return;
    }
    g->n++;
}

// 간선 삽입 연산
void insert_edge(GraphType* g, int u, int v) {
    if (u >= g->n || v >= g->n) {
        fprintf(stderr, "그래프: 정점 번호 오류\n");
        return;
    }
    GraphNode* node = (GraphNode*)malloc(sizeof(GraphNode));
    node->vertex = v;
    node->link = g->adj_list[u];
    g->adj_list[u] = node;
}

// 깊이 우선 탐색
void dfs_list(GraphType* g, int v) {
    GraphNode* w;
    visited[v] = TRUE;
    printf("정점 %d -> ", v);
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

    // 방문 배열 초기화
    for (int i = 0; i < g->n; i++)
        visited[i] = FALSE;

    printf("깊이 우선 탐색\n");
    dfs_list(g, 0);
    printf("\n");

    destroy_graph(g);
    free(g);
    return 0;
}
