#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 50
#define TRUE 1
#define FALSE 0

typedef struct GraphType {
    int n; // 정점의 개수
    int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int visited[MAX_VERTICES]; // 방문한 정점을 체크하는 용도의 배열

// 그래프 초기화
void init(GraphType* g) {
    int r, c;
    g->n = 0;
    for (r = 0; r < MAX_VERTICES; r++)
        for (c = 0; c < MAX_VERTICES; c++)
            g->adj_mat[r][c] = 0;
}

// 정점 삽입 연산
void insert_vertex(GraphType* g, int v) {
    if (((g->n) + 1) > MAX_VERTICES) {
        fprintf(stderr, "그래프: 정점의 개수 초과\n");
        return;
    }
    g->n++;
}

// 간선 삽입 연산
void insert_edge(GraphType* g, int start, int end) {
    if (start >= g->n || end >= g->n) {
        fprintf(stderr, "그래프: 정점 번호 오류\n");
        return;
    }
    g->adj_mat[start][end] = 1;
    g->adj_mat[end][start] = 1; // 양방향 연결
}

// 깊이 우선 탐색
void dfs_mat(GraphType* g, int v) {
    int w;
    visited[v] = TRUE; // 정점 v의 방문 표시
    printf("정점 %d -> ", v); // 방문한 정점 출력
    for (w = 0; w < g->n; w++) // 인접 정점 탐색
        if (g->adj_mat[v][w] && !visited[w])
            dfs_mat(g, w); // 정점 w에서 DFS 새로 시작
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

    // 방문 배열 초기화
    for (int i = 0; i < MAX_VERTICES; i++)
        visited[i] = FALSE;

    printf("깊이 우선 탐색\n");
    dfs_mat(g, 0);
    printf("\n");
    free(g);
    return 0;
}
//visited 배열 선언 추가, 깊이 우선 탐색(DFS)에서 각 정점의 방문 여부를 추적하기 위함
//각 정점에 대한 방문 상태를 TRUE 또는 FALSE로 저장합니다.
//main 함수에서 visited 배열 초기화 : main 함수에서 visited 배열의 모든 요소를 FALSE로 초기화하는 부분을 추가