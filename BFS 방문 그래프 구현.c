#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 50
#define MAX_QUEUE_SIZE 100
#define TRUE 1
#define FALSE 0

typedef struct GraphType {
    int n; // ������ ����
    int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphType;

typedef int element;
typedef struct {
    element queue[MAX_QUEUE_SIZE];
    int front, rear;
} QueueType;

int visited[MAX_VERTICES]; // �湮�� ������ üũ�ϴ� �뵵�� �迭

// ť ���� �Լ���
void queue_init(QueueType* q) {
    q->front = q->rear = 0;
}

int is_empty(QueueType* q) {
    return (q->front == q->rear);
}

int is_full(QueueType* q) {
    return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

void enqueue(QueueType* q, element item) {
    if (is_full(q))
        exit(1);
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->queue[q->rear] = item;
}

element dequeue(QueueType* q) {
    if (is_empty(q))
        exit(1);
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->queue[q->front];
}

// �׷��� ���� �Լ���
void graph_init(GraphType* g) {
    int r, c;
    g->n = 0;
    for (r = 0; r < MAX_VERTICES; r++)
        for (c = 0; c < MAX_VERTICES; c++)
            g->adj_mat[r][c] = 0;
}

void insert_vertex(GraphType* g, int v) {
    if (((g->n) + 1) > MAX_VERTICES) {
        fprintf(stderr, "�׷���: ������ ���� �ʰ�\n");
        return;
    }
    g->n++;
}

void insert_edge(GraphType* g, int start, int end) {
    if (start >= g->n || end >= g->n) {
        fprintf(stderr, "�׷���: ���� ��ȣ ����\n");
        return;
    }
    g->adj_mat[start][end] = 1;
    g->adj_mat[end][start] = 1; // ����� ����
}

// BFS �Լ�
void bfs_mat(GraphType* g, int v) {
    int w;
    QueueType q;
    queue_init(&q);
    visited[v] = TRUE;
    printf("%d �湮 -> ", v);
    enqueue(&q, v);

    while (!is_empty(&q)) {
        v = dequeue(&q);
        for (w = 0; w < g->n; w++)
            if (g->adj_mat[v][w] && !visited[w]) {
                visited[w] = TRUE;
                printf("%d �湮 -> ", w);
                enqueue(&q, w);
            }
    }
}

// ���� �Լ�
int main(void) {
    GraphType* g = (GraphType*)malloc(sizeof(GraphType));
    graph_init(g);

    for (int i = 0; i < 6; i++)
        insert_vertex(g, i);

    insert_edge(g, 0, 2);
    insert_edge(g, 2, 1);
    insert_edge(g, 2, 3);
    insert_edge(g, 0, 4);
    insert_edge(g, 4, 5);
    insert_edge(g, 1, 5);

    // �湮 �迭 �ʱ�ȭ
    for (int i = 0; i < g->n; i++)
        visited[i] = FALSE;

    printf("�ʺ� �켱 Ž��\n");
    bfs_mat(g, 0);
    printf("\n");

    free(g);
    return 0;
}
