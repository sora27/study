#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#define MAX_QUEUE_SIZE 20

//원형 큐
typedef int element;
typedef struct {
	element data[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;

//오류 함수
void error(char *message) {
	fprintf(stderr, "%s\n", message);
	exit(1);
}

//초기화 함수
void init_queue(QueueType *q) {
	q->front = q->rear = 0;
}

//공백 상태 검출 함수
int is_empty(QueueType *q) {
	return (q->front == q->rear);
}

//포화 상태 검출 함수
int is_full(QueueType *q) {
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

//원형큐 출력 함수
void queue_print(QueueType *q) {
	printf("QUEUE(front=%d rear=%d) = ",q->front,q->rear);
	if(!is_empty(q)) {
		int i = q->front;
		do {
			i = (i + 1) % (MAX_QUEUE_SIZE);
			printf("%d | ",q->data[i]);
			if(i == q->rear) break;
		} while(i != q->front);
	}
	printf("\n");
}

//삽입 함수
void enqueue(QueueType *q, element item) {
	//if(is_full(q)) {
		//error("큐가 포화상태입니다.");
	//}
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}

//삭제 함수
element dequeue(QueueType *q) {
	//if(is_empty(q)) {
		//error("큐가 공백상태입니다");
	//}
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

//뒤(rear)에서부터 앞(front)으로 출력
void rear_to_front_print(QueueType *q) {
	
	if(q->rear > 0) {
		int now = q->rear;
		do {
			printf("%d\n",q->data[now]);
			now -= 1;
		}while(now > q->front);
	}
	
	if(q->rear == 0) {
		//0이니까 최초 한번 실행
		printf("%d\n",q->data[q->rear]);
		
		int now = MAX_QUEUE_SIZE - 1;
		while(now > q->front) {
			printf("%d\n",q->data[now]);
			now -= 1;
		}
	}
	
}

int main(int argc, char* argv[]) {
	QueueType queue;
	int element;
	int gubun;
	
	init_queue(&queue);
	
	
	srand((unsigned int)time(NULL));
	for(int i = 0; i < 30; i++) {
		gubun = rand() % 2 + 1; //1 또는 2 숫자 출력
		element = rand() % 100 + 1; //1~100 난수
		printf("[%d번째] 구분 : %d / 숫자 : %d\n",i+1,gubun,element);
		
		if(gubun == 1) {
			//enqueue 실행
			if(is_full(&queue)) {
				dequeue(&queue);
			} else {
				enqueue(&queue,element);
			}
		} else {
			//dequeue 실행
			if(is_empty(&queue)) {
				enqueue(&queue,element);
			} else {
				dequeue(&queue);
			}
		}
	}
	
	/*
	//..테스트 코드
	// gubun:1, ele:10 / gubun:1, ele:11 / gubun:1, ele:12 / gubun:1, ele:13 ..차례로 입력
	// gubun:1, ele:10 / gubun:1, ele:11 / gubun:2, ele:12 / gubun:2, ele:13 / gubun:1, ele:14 / gubun:2, ele:15 / gubun:1, ele:16 ..차례로 입력
	for(int i = 0; i < 7; i++) {
		printf("%d : 구분 입력하세요 : ",i+1);
		scanf("%d",&gubun);
		printf("%d : 데이터 입력하세요 : ",i+1);
		scanf("%d",&element);
		
		if(gubun == 1) { //enqueue 실행
			if(is_full(&queue)) {
				dequeue(&queue);
			} else {
				enqueue(&queue,element);
			}
		} else { //dequeue 실행
			if(is_empty(&queue)) {
				enqueue(&queue,element);
			} else {
				dequeue(&queue);
			}
		}
	}
	*/
	
	printf("\n\n[rear에서 front로 출력합니다..]\n");
	//2. 뒤에서 앞으로 출력..
	if(!is_empty(&queue)) {
		rear_to_front_print(&queue);
	}
	
	printf("\n\n[front에서 rear로 출력합니다..]\n");
	//3. 앞에서 뒤로 출력.. 삭제하면서..
	while(!is_empty(&queue)) {
		queue_print(&queue);
		element = dequeue(&queue);
		printf("꺼내진 정수 : %d \n",element);
	}
	
	return 0;
}
