#include <stdio.h>
#include <stdlib.h>
#include<time.h>

//노드 구조체
typedef struct ListNode {
	int data;
	struct ListNode *link;
}ListNode;

//원형큐
typedef struct QueueType {
	int size;
	ListNode *front;
	ListNode *rear;
}QueueType;

//오류 함수
void error(char *message) {
	fprintf(stderr, "%s\n", message);
	exit(1);
}

//초기화 함수
void init_queue(QueueType *q) {
	q->front = q->rear = NULL;
	q->size = 0;
}

//공백 상태 검출 함수
int is_empty(QueueType *q) {
	return (q->size == 0);
}

//삽입 함수
void enqueue(QueueType *q, int data) {
	ListNode *plist = (ListNode*)malloc(sizeof(ListNode));

	plist->data = data;
	plist->link = NULL;
	
	if(is_empty(q)) {
		q->front = plist;
	} else {
		q->rear->link = plist;
	}
	
	q->rear = plist;
	q->size++;
}

//삭제 함수
int dequeue(QueueType *q) {
	int re = 0;
	ListNode *temp;
	if(is_empty(q)) return re;
	
	temp = q->front;
	re = temp->data;
	q->front = temp->link;
	free(temp);
	q->size--;
	return re;
}

//원형큐 출력 함수
void queue_print(QueueType *q) {
	ListNode* p = q->front;
	
	for(; p; p = p->link) {
		printf("%d\n", p->data);
	}
	printf("\n");
}

int main(void) {
	QueueType queue;
	int number;
	int gubun;
	
	init_queue(&queue);
	
	
	srand((unsigned int)time(NULL));
	for(int i = 0; i < 10; i++) {
		gubun = rand() % 2 + 1; //1 또는 2 숫자 출력
		number = rand() % 100 + 1; //1~100 난수
		
		printf("[%d번째] 연산명 : ",i+1);
		if(gubun == 1) {
			printf("enqueue");
		} else {
			printf("dequeue");
		}
		printf(" / 숫자 : %d\n",number);
		
		if(gubun == 1) {
			//enqueue 실행
			enqueue(&queue,number);
		} else {
			//dequeue 실행
			if(is_empty(&queue)) {
				continue;
			} else {
				dequeue(&queue);
			}
		}
	}
	
	//앞부터 차례로 데이터 출력
	printf("\n\n[front에서 rear로 출력합니다..]\n");
	
	if(is_empty(&queue)) {
		printf("출력할 데이터가 없습니다.\n");
	} else {
		queue_print(&queue);
	}
	
	return 0;
}
