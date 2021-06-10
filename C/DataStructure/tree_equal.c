#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_NODE_SIZE 10

/*** START 구조체 선언 ***/
typedef struct TreeNode {
	int data;
	struct TreeNode* left;
	struct TreeNode* right;
}TreeNode;

//스택 구조체
typedef struct StackType{
	TreeNode* node[MAX_NODE_SIZE];
	int top;
}StackType;
/*** END 구조체 선언 ***/

/*** START 스택 ***/
//스택 초기화
void init_stack(StackType *s) {
	s->top = -1;
}

//스택 공백 상태 체크
int is_empty(StackType *s) {
	return (s->top == -1);
}

//스택 포화 상태 체크
int is_full(StackType *s) {
	return (s->top + 1) == MAX_NODE_SIZE;
}

//스택 삽입
void push(StackType *s, TreeNode *node) {
	if(is_full(s)) {
		printf("스택이 꽉 찼습니다.\n");
		return;
	}
	s->top++;
	s->node[s->top] = node;
}

//스택 팝
TreeNode *pop(StackType *s) {
	TreeNode *res = NULL;
	if(is_empty(s)) {
		printf("스택이 비어있습니다.\n");
		return res;
	}
	res = s->node[s->top];
	s->top--;
	return res;
}
/*** END 스택 ***/

void error(char str[])
{
   printf("%s\n", str);
   exit(1);
}

//재귀 후위 순회
void postorder(TreeNode *root) {
	if(root != NULL) {
		postorder(root->left);
		postorder(root->right);
		printf("%d\n",root->data);
	}
}

//반복 후위 순회
void iterpostorder(TreeNode *node) {
	StackType s;
	init_stack(&s);
	
	TreeNode *prev = NULL;
	while(1) {
		do{
			if(prev != node && node != NULL) {
				push(&s,node);
				node = node->left;
			}
			else {break;}
		}while(node != NULL);
		node = pop(&s);
		if(!node) break;
		
		if(node->right != NULL) {
			if(node->right == prev) {
				printf("%d\n",node->data);
				prev = node;
			} else {
				push(&s,node);
				node = node->right;
			}
			
		} else {
			printf("%d\n", node->data);
			prev = node;
		}
		
	}
	
}

//노드 생성
TreeNode *addNode(TreeNode *curr, int data) {
	TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
	
	newNode->data = data;
	newNode->left = NULL;
	newNode->right = NULL;
	
	return newNode;
}

//동일성 검사 - 재귀
int equal(TreeNode *first, TreeNode *second) {
	return ((!first && !second) || (first && second && (first->data == second->data) && equal(first->left, second->left) && equal(first->right, second->right)));
}

//동일성 검사 - 반복
int equal_iter(TreeNode *first, TreeNode *second) {
	StackType s;
	init_stack(&s);
	
	push(&s,first);
	push(&s,second);
	
	TreeNode *A1 = NULL;
	TreeNode *B1 = NULL;
	
	while(1) {
		A1 = pop(&s);
		B1 = pop(&s);
		if(A1->data != B1->data) return 0;
		while(A1 != NULL && B1 != NULL) {
			
			if(!A1->left && !B1->left) {
				if(!A1->right && !B1->right) break;
				
				if(A1->right && B1->right && (A1->right->data == B1->right->data)) {
					push(&s,A1->right);
					push(&s,B1->right);
					
					break;
				} else {
					return 0;
				}
			}
			
			if(A1->left && B1->left && (A1->left->data == B1->left->data)) {
				if(!A1->right && !B1->right) {
					A1 = A1->left;
					B1 = B1->left;
					continue;
				}
				if(A1->right && B1->right && (A1->right->data == B1->right->data)) {
					push(&s,A1->right);
					push(&s,B1->right);
					
					A1 = A1->left;
					B1 = B1->left;
				} else {
					return 0;
				}
				
			} else {
				return 0;
			}
		}
		
		if(is_empty(&s)) break;
	}
	return 1;
}

//트리 생성
TreeNode *create_tree() {

	int nodeCnt = 1;
	
	int x, y;
	int i = 0;
	
	TreeNode *rootNode = (TreeNode *)malloc(sizeof(TreeNode)); //루트 노드 생성
	
	y = rand() % 2 + 10; //10~11 난수
	rootNode->data = y;
	rootNode->left = NULL;
	rootNode->right = NULL;
	TreeNode *A = rootNode; //A트리의 루트 설정
	
	printf("root : %d\n",y);
	
	TreeNode *nowRoot = rootNode;
	
	while(1) {
		x = rand() % 2 + 1; //1~2 숫자 출력
		y = rand() % 2 + 10; //10~11 난수
		printf("[%d번째] x : %d / y : %d\n",i,x,y);
		
		if(x == 1) {
			//left 추가
			if(nowRoot->left) {
				nowRoot = nowRoot->left;
				i++;
				continue;
			} else {
				nowRoot->left = addNode(nowRoot,y);
				nowRoot = rootNode;
				nodeCnt++;
			}
		} else {
			//right 추가
			if(nowRoot->right) {
				nowRoot = nowRoot->right;
				i++;
				continue;
			} else {
				nowRoot->right = addNode(nowRoot,y);
				nowRoot = rootNode;
				nodeCnt++;
			}
		}
		
		i++;
		if(nodeCnt == MAX_NODE_SIZE) break;
	}
	
	return rootNode;
}

int main(void) {
	
	srand(time(NULL));
	TreeNode *A = create_tree();
	TreeNode *B = create_tree();
		
	printf("\n\n[A - 재귀 후위 실행]\n");
	postorder(A);
	
	printf("\n\n[A - 반복 후위 실행]\n");
	iterpostorder(A);
	
	printf("\n\n[B - 재귀 후위 실행]\n");
	postorder(B);
	
	printf("\n\n[B - 반복 후위 실행]\n");
	iterpostorder(B);
	
	
	
	int result = equal(A,B);
	if(result == 1) {
		printf("\n\n재귀 방식 : 동일\n");
	} else {
		printf("\n\n재귀 방식 : 비동일\n");
	}
	
	int result_iter = equal_iter(A,B);
	if(result_iter == 1) {
		printf("\n\n반복 방식 : 동일\n");
	} else {
		printf("\n\n반복 방식 : 비동일\n");
	}

	return 0;
}
