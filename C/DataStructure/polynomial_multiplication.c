#include<stdio.h>
#include<stdlib.h>

typedef struct ListNode {
   int coef;
   int expon;
   struct ListNode *link;
}ListNode;

typedef struct ListType {
   int size;
   ListNode *head;
   ListNode *tail;
}ListType;

void error(char *message) {
   fprintf(stderr, "%s\n", message);
   exit(1);
}

ListType* create() {
   ListType *plist = (ListType*)malloc(sizeof(ListType));
   plist->size = 0;
   plist->head = plist->tail = NULL;
   return plist;
}

void insert_last(ListType* plist, int coef, int expon) {
   ListNode *temp = (ListNode*)malloc(sizeof(ListNode));
   
   if(temp == NULL) error("메모리 할당 에러");
   temp->coef = coef;
   temp->expon = expon;
   temp->link = NULL;
   
   if(plist->tail == NULL) {
      plist->head = plist->tail = temp;
   } else {
      plist->tail->link = temp;
      plist->tail = temp;
   }
   
   plist->size++;
}

void poly_multiple(ListType* plist1, ListType* plist2, ListType* plist3)
{
   ListNode* a = plist1->head;
   while(a != NULL) {
      ListNode* b = plist2->head;
      while(b != NULL) {
         int c = a->coef * b->coef;
         int e = a->expon + b->expon;
         insert_last(plist3,c,e);
         b = b->link;
      }
      a = a->link;
   }
}

void poly_print(ListType* plist) {
   ListNode* p = plist->head;
   
   //printf("polynomial = ");
   for(; p; p = p->link) {
      printf("%d^%d + ", p->coef, p->expon);
   }
   
   printf("\n");
}

int main(void) {
   int en_coef, en_expon;
   ListType *list1,*list2,*list3;
 
   list1 = create(); //첫번째 다항식
   list2 = create(); //두번째 다항식
   list3 = create(); //결과
   
   printf("==다항식의 곱셈==\n\n");
   
   //첫번째 다항식
   printf("[첫번째 다항식 입력]..(최고차항부터 내림차순으로 입력, 계수는 0이 아닌 항만 입력, 계수에 0입력시 종료)\n");
   while(1) {
      printf("계수입력/차수입력 : ");
      scanf("%d/%d",&en_coef,&en_expon);

      if(en_coef == 0) {
         printf("계수에 0입력! 첫번째 다항식 입력이 종료됩니다...\n\n");
         break;
      }


      insert_last(list1,en_coef,en_expon);
   }
   
   //두번째 다항식
   printf("[두번째 다항식 입력]..(최고차항부터 내림차순으로 입력, 계수는 0이 아닌 항만 입력, 계수에 0입력시 종료)\n");
   while(1) {
      printf("계수입력/차수입력 : ");
      scanf("%d/%d",&en_coef,&en_expon);

      if(en_coef == 0) {
         printf("계수에 0입력! 첫번째 다항식 입력이 종료됩니다...\n\n");
         break;
      }


      insert_last(list2,en_coef,en_expon);
   }
 
   printf("다항식1 : ");
   poly_print(list1);
   printf("다항식2 : ");
   poly_print(list2);
   
   poly_multiple(list1,list2,list3);
   printf("다항식 곱 : ");
   poly_print(list3);
 
   free(list1); free(list2); free(list3);
   
   
    return 0;
}
