#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//책에 대한 구조체 선언
typedef struct _BOOK {
	char name[20];
	char author[20];
	int price;
	int year;
	int month;
}BOOK;

typedef struct _BookNode {
	BOOK bookinfo;
	struct _BookNode *link;
}BookNode;

typedef struct _ListType {
	BookNode *head;
}ListType;

void error(char *message) {
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void init(ListType *s) {
	s->head = NULL;
}

int is_empty(ListType *s) {
	return (s->head == NULL);
}

ListType* classify_book(BOOK *b, ListType *A, ListType *B) {
	//printf("A : %d\n",A);
	//printf("B : %d\n",B);
	if(b->year < 2000) {
		return A;
	} else {
		return B;
	}
}

void store_book(BOOK *b, ListType *g) {
	//printf("%d\n",g);
	BookNode *temp = (BookNode *)malloc(sizeof(BookNode));
	
	if(g->head == NULL) {
		temp->bookinfo = *b;
		temp->link = NULL;
		g->head = temp;
	} else {
		BookNode* p = g->head;
		BookNode* before = NULL;
		for(; p; p = p->link) {
			//printf("%s\n",p->bookinfo.name);
			if((p->bookinfo.year > b->year) || (p->bookinfo.year == b->year && p->bookinfo.month > b->month)) { //기존 책의 연도가 더 최근이거나, 연도가 같고 기존 책의 월이 더 최근이면
				if(p->link == NULL) {
					//마지막에 추가
					temp->bookinfo = *b;
					temp->link = NULL;
					p->link = temp;
					break;
				} else {
					//패스
					before = p;
					continue;
				}
			} else if((p->bookinfo.year < b->year) || (p->bookinfo.year == b->year && p->bookinfo.month < b->month)) { //신규 책의 연도가 더 최근이거나, 연도가 같고 신규 책의 월이 더 최근이면
				//앞에 추가
				temp->bookinfo = *b;
				temp->link = p;
				if(before != NULL) before->link = temp;
				if(g->head == p) g->head = temp;
				break;
			} else { //두 책의 월 비교
				//앞에 추가
				temp->bookinfo = *b;
				temp->link = p;
				if(before != NULL) before->link = temp;
				if(g->head == p) g->head = temp;
				break;
			}
		}
		
	}
}

BookNode* reverse(ListType *b) {
	BookNode *p, *q, *r;
	
	p = b->head;
	q = NULL;
	while(p != NULL) {
		r = q;
		q = p;
		p = p->link;
		q->link = r;
	}
	return q;
}

ListType* merge_group(ListType *a, ListType *b) {
	
	if(a->head == NULL) return b;
	else if (b->head == NULL) return a;
	else {
		//내림차순으로 출력 (b리스트 먼저)
		BookNode *p = b->head;
		while(p->link != NULL)
			p = p->link;
		p->link = a->head;
		return b;
	}
}

// void pr(ListType *a) {
// 	BookNode *p = a->head;
// 	for(; p; p = p->link) {
// 		printf("도서명 : %s\n",p->bookinfo.name);
		
// 		// printf("저자명 : %s\n",p->bookinfo.author);
		
// 		// printf("가격 : %d\n",p->bookinfo.price);
		
// 		printf("출판년월(예:2020/12) : %d/%d\n",p->bookinfo.year,p->bookinfo.month);
// 		printf("\n");
// 	}
// }


int main(void)
{
	BOOK book[10];
	ListType A; //2000년 미만 그룹
	ListType B; //2000년 이상 그룹
	
	init(&A);
	init(&B);
	
	int i;
	
	printf("[도서 정보 입력을 시작합니다.]\n\n");
	for(i = 0; i < 10; i++) {
		printf("[%d번째] 도서 정보 입력\n",i+1);
		
		printf("ㄴ도서명 : ");
		scanf("%s",book[i].name);
		
		printf("ㄴ저자명 : ");
		scanf("%s",book[i].author);
		
		printf("ㄴ가격 : ");
		scanf("%d",&book[i].price);
		
		printf("ㄴ출판년월(예:2020/12) : ");
		scanf("%d/%d",&book[i].year,&book[i].month);
		
		printf("\n");
		
		ListType* group = classify_book(&book[i],&A,&B);
		store_book(&book[i],group);
		
	}
	
	/*
	pr(&A);
	*/
	
	ListType* mg = merge_group(&A,&B);
	
	printf("\n\n== 내림차순 출력 ==\n\n");
	BookNode* p = mg->head;
	for(; p; p = p->link) {
		printf("도서명 : %s\n",p->bookinfo.name);
		
		printf("저자명 : %s\n",p->bookinfo.author);
		
		printf("가격 : %d\n",p->bookinfo.price);
		
		printf("출판년월(예:2020/12) : %d/%d\n",p->bookinfo.year,p->bookinfo.month);
		printf("\n");
	}
	
	
	printf("\n\n== 올림차순 출력 ==\n\n");
	BookNode* reverse_mg = reverse(mg);
	
	BookNode* rp = reverse_mg;
	for(; rp; rp = rp->link) {
		printf("도서명 : %s\n",rp->bookinfo.name);
		
		printf("저자명 : %s\n",rp->bookinfo.author);
		
		printf("가격 : %d\n",rp->bookinfo.price);
		
		printf("출판년월(예:2020/12) : %d/%d\n",rp->bookinfo.year,rp->bookinfo.month);
		printf("\n");
	}
	
	
	
	return 0;
}
