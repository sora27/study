#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTEX 10

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

// 오류 출력 문구
void error(char str[]) {
   printf("%s\n", str);
   exit(1);
}

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
	if(is_full_queue(q)) {
		error("큐가 포화상태입니다.");
	}
	q->rear = (q->rear + 1) % MAX_VERTEX;
	q->queue[q->rear] = data;
}

// 큐 삭제
int dequeue(QueueType *q) {
	if(is_empty_queue(q)) {
		error("큐가 공백상태입니다");
	}
	q->front = (q->front + 1) % MAX_VERTEX;
	return q->queue[q->front];
}

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
void Add_Vertex(Graph* g){

    g->adj_list[g->n] = (List*)malloc(sizeof(List));

    g->adj_list[g->n]->vx = -1;

    g->adj_list[g->n]->link = NULL;

    

    g->n++;

}
*/

// 간선 삽입
void insert_edgeList(GraphTypeList *g, int s, int e) {
	//if(s-1 >= g->vertex || s-1 >= g->vertex || s == e) {
	if(s == e) {
		printf("\n!! 그래프 정점 번호 오류 (start:%d, end:%d) !!\n",s,e);
		return;
	}
	
	int arrN = s / 10;
	GraphNode *node = (GraphNode *)malloc(sizeof(GraphNode));
	node->n = e;
	node->link = g->adj_list[arrN];
	g->adj_list[arrN] = node;
	
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
		printf("정점 %d의 인접 리스트", i*10);
		
		while (p != NULL) {
			printf("-> %d", p->n);
			p = p->link;
		}
		printf("\n");
	}
}

// dfs 인접리스트 - 재귀
void dfs_list(GraphTypeList *g, int v) {
	int arrN = v / 10;
	int arrN2;
	GraphNode *w;
	g->visited[arrN] = 1;
	printf("방문 : %d\n",v);
	for(w = g->adj_list[arrN]; w; w = w->link) {
		arrN2 = w->n / 10;
		if(g->visited[arrN2] == 0) dfs_list(g,w->n);
	}
}

// bfs 인접리스트
// void bfs_list(GraphTypeList *g, int v) {
// 	GraphNode *w;
	
// 	QueueType q;
// 	init_queue(&q);
	
// 	g->visited[v-1] = 1;
// 	printf("방문1 : %d\n",v);
// 	enqueue(&q,v);
	
// 	while(!is_empty_queue(&q)) {
// 		v = dequeue(&q);
// 		for(w = g->adj_list[v-1]; w; w = w->link) {
// 			if(g->visited[(w->n)-1] == 0) {
// 				g->visited[(w->n)-1] = 1;
// 				printf("방문2 : %d\n",w->n);
// 				enqueue(&q,w->n);
// 			}
// 		}
// 	}
// }

/********** END 그래프 - 인접리스트 **********/
int main(void) {
	
	//인접리스트
	GraphTypeList *gl;
	gl = (GraphTypeList *)malloc(sizeof(GraphTypeList));
	init_graphList(gl,MAX_VERTEX);
	
	insert_edgeList(gl,30,40);
	insert_edgeList(gl,40,30);
	
	insert_edgeList(gl,40,70);
	insert_edgeList(gl,70,40);
	
	insert_edgeList(gl,70,50);
	insert_edgeList(gl,50,70);
	
	insert_edgeList(gl,50,60);
	insert_edgeList(gl,60,50);
	
	insert_edgeList(gl,10,20);
	insert_edgeList(gl,20,10);
	
	insert_edgeList(gl,10,90);
	insert_edgeList(gl,90,10);
	
	insert_edgeList(gl,90,0);
	insert_edgeList(gl,0,90);
	
	insert_edgeList(gl,0,80);
	insert_edgeList(gl,80,0);
	
	insert_edgeList(gl,80,20);
	insert_edgeList(gl,20,80);
	
	printf("\n======== 인접리스트 =======\n");
	printfGraphList(gl);
	
	int conn = 0;
	for(int i = 0; i < MAX_VERTEX; i++) {
		if(gl->visited[i] == 0) {
			printf("\n\n== %d번째 연결요소 정점값 출력 ==\n\n",conn+1);
			dfs_list(gl,i * 10);
			conn++;
		}
	}
	
	
	printf("\n총 연결 요소 개수 : %d\n",conn);
	
	// printf("\n======== 인접리스트 - DFS - 재귀 =======\n");
	// resetList_visited(gl);
	// dfs_list(gl,40);
	
	// printf("\n======== 인접리스트 - BFS =======\n");
	// resetList_visited(gl);
	// bfs_list(gl,30);
	
	return 0;
}
