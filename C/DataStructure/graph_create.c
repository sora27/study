#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTEX 10

// 그래프 구조체 - 인접행렬
typedef struct GraphType {
	int vertex; //정점의 개수
	int edge[MAX_VERTEX][MAX_VERTEX];
	int visited[MAX_VERTEX]; //방문 여부
}GraphType;

// 그래프 노드
typedef struct GraphNode {
	int n;
	struct GraphNode *link;
}GraphNode;

// 그래프 구조체 - 인접리스트
typedef struct GraphTypeList {
	int vertex; //정점의 개수
	GraphNode *adj_list[MAX_VERTEX];
	int visited[MAX_VERTEX]; //방문 여부
}GraphTypeList;

// 스택 구조체
typedef struct stack {
	int stack[MAX_VERTEX];
	int top;
}StackType;

// 큐 구조체
typedef struct queue {
	int queue[MAX_VERTEX];
	int front;
	int rear;
}QueueType;

// 스택 초기화
void init_stack(StackType *s) {
	for(int i = 0; i < MAX_VERTEX; i++) {
		s->stack[i] = 0;
	}
	s->top = -1;
}

// 스택 비어있는지 확인
int is_empty(StackType *s) {
	return (s->top == -1);
}

// 스택 팝
int pop(StackType *s) {
	int re = s->stack[s->top];
	s->top--;
	return re;
}

// 스택 삽입
void push(StackType *s,int data) {
	s->stack[++(s->top)] = data;
}

// 큐 초기화
void init_queue(QueueType *q) {
	for(int i = 0; i < MAX_VERTEX; i++) {
		q->queue[i] = 0;
	}
	q->front = q->rear = 0;
}

// 큐 공백 상태 검출
int is_empty_queue(QueueType *q) {
	return (q->front == q->rear);
}

// 큐 포화 상태 검출
int is_full_queue(QueueType *q) {
	return ((q->rear + 1) % MAX_VERTEX == q->front);
}

// 큐 삽입
void enqueue(QueueType *q, int data) {
	//if(is_full_queue(q)) {
		//error("큐가 포화상태입니다.");
	//}
	q->rear = (q->rear + 1) % MAX_VERTEX;
	q->queue[q->rear] = data;
}

// 큐 삭제
int dequeue(QueueType *q) {
	//if(is_empty_queue(q)) {
		//error("큐가 공백상태입니다");
	//}
	q->front = (q->front + 1) % MAX_VERTEX;
	return q->queue[q->front];
}

/********** START 그래프 - 인접행렬 **********/
// 그래프 초기화
void init_graph(GraphType *g, int maxVertex) {
	int row, col;
	g->vertex = maxVertex;
	for(row = 0; row < MAX_VERTEX; row++) {
		g->visited[row] = 0;
		for(col = 0; col < MAX_VERTEX; col++) {
			g->edge[row][col] = 0;
		}
	}
}

// 그래프 방문 체크 리셋
void reset_visited(GraphType *g) {
	int i;
	for(i = 0; i < MAX_VERTEX; i ++) {
		g->visited[i] = 0;
	}
}

/*
// 정점 삽입
void insert_vertex(GraphType *g, int v) {
	if(((g->vertex) + 1) > MAX_VERTEX) {
		printf("\n!! 정점의 개수 초과 !!\n");
		return;
	}
	
	g->vertex++;
}
*/

// 간선 삽입
void insert_edge(GraphType *g, int s, int e) {
	if(s-1 >= g->vertex || e-1 >= g->vertex || s == e) {
		printf("\n!! 그래프 정점 번호 오류 (start:%d, end:%d) !!\n",s,e);
		return;
	}
	
	g->edge[s-1][e-1] = 1;
	g->edge[e-1][s-1] = 1;
}

// dfs 인접행렬 - 재귀
void dfs(GraphType *g, int v) {
	int i;
    g->visited[v-1] = 1;
    printf("방문 : %d\n", v);
    for (i = 0; i < g->vertex; i++) {
        if (g->edge[v-1][i] == 1 && g->visited[i] == 0 ) {
			//printf("i :%d, %d...\n",v-1,i);
			dfs(g,i+1);
		}
        
    }
}

// dfs 인접행렬 - 비재귀
void dfs_nonrecur(GraphType *g, int v) {
	
	int i, p;
	
    StackType s;
	init_stack(&s);
	
	push(&s,v);
	
	while(!is_empty(&s)) {
		
		p = pop(&s);
		if(g->visited[p-1] == 0) {
			g->visited[p-1] = 1;
			printf("방문 : %d\n",p);
			
			for(i = MAX_VERTEX-1; i >= 0; i--) {
				if(g->edge[p-1][i] == 1 && g->visited[i] == 0) push(&s,i+1);
			}
		}
	}
}

// bfs 인접행렬
void bfs(GraphType *g, int v) {
	int i;
	
	QueueType q;
	init_queue(&q);
	
    g->visited[v-1] = 1;
    printf("방문 : %d\n", v);
	
	enqueue(&q, v);
	
	while(!is_empty_queue(&q)) {
		v = dequeue(&q);
		for(i = 0; i < g->vertex; i++) {
			if(g->edge[v-1][i] == 1 && g->visited[i] == 0) {
				g->visited[i] = 1;
				printf("방문 : %d\n", i+1);
				enqueue(&q,i+1);
			}
		}
	}
}

void printfGraph(GraphType *g) {
	int i, j;
	for(i = 0; i < g->vertex; i++) {
		printf("start %d -> ",i+1);
		for(j = 0; j < g->vertex; j++) {
			printf("%d ", g->edge[i][j]);
		}
		printf("\n");
	}
}
/********** END 그래프 - 인접행렬 **********/

/********** START 그래프 - 인접리스트 **********/
// 그래프 초기화
void init_graphList(GraphTypeList *g, int maxVertex) {
	int i;
	g->vertex = maxVertex;
	for(i = 0; i < MAX_VERTEX; i++) {
		g->adj_list[i] = NULL;
		g->visited[i] = 0;
	}
}

// 그래프 방문 체크 리셋
void resetList_visited(GraphTypeList *g) {
	int i;
	for(i = 0; i < MAX_VERTEX; i ++) {
		g->visited[i] = 0;
	}
}

/*
// 정점 삽입
void insert_vertexList(GraphTypeList *g, int v) {
	if(((g->vertex) + 1) > MAX_VERTEX) {
		printf("\n!! 그래프 정점 개수 초과 !!\n");
		return;
	}
	g->vertex++;
}
*/

// 간선 삽입
void insert_edgeList(GraphTypeList *g, int s, int e) {
	if(s-1 >= g->vertex || s-1 >= g->vertex || s == e) {
		printf("\n!! 그래프 정점 번호 오류 (start:%d, end:%d) !!\n",s,e);
		return;
	}
	
	
	GraphNode *node = (GraphNode *)malloc(sizeof(GraphNode));
	node->n = e;
	node->link = g->adj_list[s-1];
	g->adj_list[s-1] = node;
	
	/*
	GraphNode *node = (GraphNode *)malloc(sizeof(GraphNode));
	node->n = e;
	if(g->adj_list[s-1] == NULL || g->adj_list[s-1]->n > e) {
		node->link = g->adj_list[s-1];
		g->adj_list[s-1] = node;
		return;
	}
	
	//printf("%d",g->adj_list[s-1]->n);
	
	//기존에 있던 값이 더 작으면..
	GraphNode *p = g->adj_list[s-1];
	while(p->n < e) {
		if(p->link == NULL) {
			node->link = NULL;
			p->link = node;
			return;
		} else if(p->link->n > e) {
			node->link = p->link;
			p->link = node;
		}
		p = p->link;
	}
	*/
	
}

// 그래프 출력
void printfGraphList(GraphTypeList *g) {
	int i;
	GraphNode *p;
	for (i = 0; i < g->vertex; i++) {
		p = g->adj_list[i];
		printf("정점 %d의 인접 리스트", i+1);
		
		while (p != NULL) {
			printf("-> %d", p->n);
			p = p->link;
		}
		printf("\n");
	}
}

// dfs 인접리스트 - 재귀
void dfs_list(GraphTypeList *g, int v) {
	GraphNode *w;
	g->visited[v-1] = 1;
	printf("방문 : %d\n",v);
	for(w = g->adj_list[v-1]; w; w = w->link) {
		if(g->visited[(w->n)-1] == 0) dfs_list(g,w->n);
	}
}

// dfs 인접리스트 - 비재귀
void dfs_list_nonrecur(GraphTypeList *g, int v) {
	
	int i, p;
	GraphNode *node;
	
    StackType s;
	init_stack(&s);
	
	push(&s,v);
	
	while(!is_empty(&s)) {
		
		p = pop(&s);
		if(g->visited[p-1] == 0) {
			g->visited[p-1] = 1;
			printf("방문 : %d\n",p);
			
			for(node = g->adj_list[p-1]; node; node = node->link) {
				if(g->visited[(node->n)-1] == 0) push(&s,node->n);
			}
		}
	}
	
}

// bfs 인접리스트
void bfs_list(GraphTypeList *g, int v) {
	GraphNode *w;
	
	QueueType q;
	init_queue(&q);
	
	g->visited[v-1] = 1;
	printf("방문1 : %d\n",v);
	enqueue(&q,v);
	
	while(!is_empty_queue(&q)) {
		v = dequeue(&q);
		for(w = g->adj_list[v-1]; w; w = w->link) {
			if(g->visited[(w->n)-1] == 0) {
				g->visited[(w->n)-1] = 1;
				printf("방문2 : %d\n",w->n);
				enqueue(&q,w->n);
			}
		}
	}
}

/********** END 그래프 - 인접리스트 **********/
int main(void) {
	//인접행렬
	GraphType *g;
	g = (GraphType *)malloc(sizeof(GraphType));
	init_graph(g,MAX_VERTEX);
	
	insert_edge(g,1,2);
	insert_edge(g,1,3);
	insert_edge(g,2,4);
	insert_edge(g,3,6);
	insert_edge(g,4,5);
	insert_edge(g,4,6);
	insert_edge(g,4,7);
	insert_edge(g,6,8);
	insert_edge(g,9,4);
	insert_edge(g,10,5);
	
	printf("\n======== 인접행렬 =======\n");
	printfGraph(g);
	
	printf("\n======== 인접행렬 - DFS - 재귀 =======\n");
	reset_visited(g);
	dfs(g,4);
	
	printf("\n======== 인접행렬 - DFS - 비재귀 =======\n");
	reset_visited(g);
	dfs_nonrecur(g,4);
	
	printf("\n======== 인접행렬 - BFS =======\n");
	reset_visited(g);
	bfs(g,4);
	
	
	//인접리스트
	GraphTypeList *gl;
	gl = (GraphTypeList *)malloc(sizeof(GraphTypeList));
	init_graphList(gl,MAX_VERTEX);
	
	insert_edgeList(gl,1,2);
	insert_edgeList(gl,2,1);
	
	insert_edgeList(gl,1,3);
	insert_edgeList(gl,3,1);
	
	insert_edgeList(gl,2,4);
	insert_edgeList(gl,4,2);
	
	insert_edgeList(gl,3,6);
	insert_edgeList(gl,6,3);
	
	insert_edgeList(gl,4,5);
	insert_edgeList(gl,5,4);
	
	insert_edgeList(gl,4,6);
	insert_edgeList(gl,6,4);
	
	insert_edgeList(gl,4,7);
	insert_edgeList(gl,7,4);
	
	insert_edgeList(gl,6,8);
	insert_edgeList(gl,8,6);
	
	insert_edgeList(gl,9,4);
	insert_edgeList(gl,4,9);
	
	insert_edgeList(gl,10,5);
	insert_edgeList(gl,5,10);
	
	printf("\n======== 인접리스트 =======\n");
	printfGraphList(gl);
	
	printf("\n======== 인접리스트 - DFS - 재귀 =======\n");
	resetList_visited(gl);
	dfs_list(gl,4);
	// dfs_list(gl,8);
	
	printf("\n======== 인접리스트 - DFS - 비재귀 =======\n");
	resetList_visited(gl);
	dfs_list_nonrecur(gl,4);
	
	printf("\n======== 인접리스트 - BFS =======\n");
	resetList_visited(gl);
	bfs_list(gl,4);
	
	return 0;
}
