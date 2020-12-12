// BFS algorithm in C

#include <stdio.h>
#include <stdlib.h>

#define QUEUE_MAX_SIZE 150

struct queue {
    int items[QUEUE_MAX_SIZE];
    int front;
    int rear;
};

struct queue* createQueue();
void enqueue(struct queue* q, int);
int dequeue(struct queue* q);
void display(struct queue* q);
int isEmpty(struct queue* q);

struct node {
    int vertex;
    struct node* next;
};

struct node* createNode(int);

struct Graph {
    int numVertices;
    struct node** adjLists;
    int* visited;
};

int* bfs(struct Graph* graph, int startVertex) {

    int* dist = (int*)malloc(graph->numVertices * sizeof(int));
    for (int i = 0; i < graph->numVertices; i++) {
        dist[i] = -1;
    }
    dist[startVertex] = -1;

    struct queue* q = createQueue();

    graph->visited[startVertex] = 1;
    enqueue(q, startVertex);

    int prevVertex = startVertex; //initial value doesn't matter
    while (!isEmpty(q)) {
        int currentVertex = dequeue(q);
        dist[currentVertex] = dist[prevVertex] + 1;
        prevVertex = currentVertex;

        struct node* temp = graph->adjLists[currentVertex];

        while (temp) {
            int adjVertex = temp->vertex;

            if (graph->visited[adjVertex] == 0) {
                graph->visited[adjVertex] = 1;
                enqueue(q, adjVertex);
            }
            temp = temp->next;
        }
    }

    return dist;
}

struct node* createNode(int v) {
    struct node* newNode = malloc(sizeof(struct node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

struct Graph* makeGraph(int vertices) {
    struct Graph* graph = malloc(sizeof(struct Graph));
    graph->numVertices = vertices;

    graph->adjLists = malloc(vertices * sizeof(struct node*));
    graph->visited = malloc(vertices * sizeof(int));

    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = 0;
    }

    return graph;
}

void addEdge(struct Graph* graph, int src, int dest) {
    struct node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

struct queue* createQueue() {
    struct queue* q = malloc(sizeof(struct queue));
    q->front = -1;
    q->rear = -1;
    return q;
}

int isEmpty(struct queue* q) {
    if (q->rear == -1)
        return 1;
    else
        return 0;
}

void enqueue(struct queue* q, int value) {
    if (q->rear == QUEUE_MAX_SIZE - 1)
        exit(1);
    else {
        if (q->front == -1)
            q->front = 0;
        q->rear++;
        q->items[q->rear] = value;
    }
}

int dequeue(struct queue* q) {
    int item;
    if (isEmpty(q)) {
        item = -1;
    } else {
        item = q->items[q->front];
        q->front++;
        if (q->front > q->rear) {
            q->front = q->rear = -1;
        }
    }
    return item;
}

int main(int argc, char* argv[]) {

    if (argc < 3) {
        printf("provide 2 file names\n");
        return 1;
    }

	freopen(argv[1], "r", stdin);
	freopen(argv[2], "w", stdout);

    int graphSize;
    scanf("%d", &graphSize);

    struct Graph* graph = makeGraph(graphSize);

    int edgeCnt;
    scanf("%d", &edgeCnt);

    for (int i = 0; i < edgeCnt; i++) {
        int from, to;
        scanf("%d %d", &from, &to);
        addEdge(graph, from, to);
    }

    int start, dest;
    scanf("%d %d", &start, &dest);

    int* dist = bfs(graph, start);

    printf("%d", dist[dest]); // -1 means "can't get"
    free(dist);
    

    return 0;
}
