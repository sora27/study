#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_QUEUE_SIZE 10

int nodeCnt = 1;

/*** START 구조체 선언 ***/
typedef struct TreeNode {
	int data;
	struct TreeNode* left;
	struct TreeNode* right;
}TreeNode;

//트리 구조체
typedef struct Tree{
	TreeNode* root;
}Tree;

//스택 구조체
typedef struct StackType{
	TreeNode* node[10];
	int top;
}StackType;
/*** END 구조체 선언 ***/

/*** START 트리 ***/
//트리 생성
Tree *init_tree() {
	Tree *t = (Tree *)malloc(sizeof(Tree));
	t->root = NULL;
	return t;
}
/*** END 트리 ***/

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
	return (s->top + 1) == MAX_QUEUE_SIZE;
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

//반복 전위 순회 - ok
void iterpreorder(TreeNode *node) {
	StackType s;
	init_stack(&s);
	
	push(&s,node);
	
	while(1) {
		node = pop(&s);
		while(node) {
			printf("%d\n", node->data);
			if(node->right) {
				//printf("오른쪽 삽입 : %d\n", node->right->data);
				push(&s,node->right);
			}
			node = node->left;
		}
		
		if(is_empty(&s)) break;
	}
}

//반복 중위 순회 - ok
void iterinorder(TreeNode *node) {
	StackType s;
	init_stack(&s);
	
	while(1) {
		while(node) {
			push(&s,node);
			node = node->left;
		}
		
		node = pop(&s);
		if(!node) break; //스택이 비어있는 상태에서 (윗줄에서) 팝하면 node 데이터는 없기 때문에 바로 아랫줄의 node->data 출력이 세그먼트오류가 발생한다. 그래서 스택이 비어있으면 break로 마무리.
		// if(is_empty(&s)) break; //is_empty를 쓰지 않은 이유 : 스택의 마지막 데이터를 팝했다고해서 순환이 모두 끝난게 아니기 때문에.
		printf("%d\n", node->data);
		node = node->right;
	}
}

//반복 후위 순회 - ok
void iterpostorder(TreeNode *node) {
	StackType s;
	init_stack(&s);
	
	TreeNode *prev = NULL; //이전 노드 비교
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


//삽입하고 루트 반환
TreeNode *addNode_left(TreeNode *curr, int data) {
	
	TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
	
	newNode->data = data;
	newNode->left = NULL;
	newNode->right = NULL;
	
	if(curr->left == NULL) {
		curr->left = newNode;
		nodeCnt++;
		return curr;
	} else {
		return curr->left;
	}
}

TreeNode *addNode_right(TreeNode *curr, int data) {
	
	TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
	
	newNode->data = data;
	newNode->left = NULL;
	newNode->right = NULL;
	
	if(curr->right == NULL) {
		curr->right = newNode;
		nodeCnt++;
		return curr;
	} else {
		return curr->right;
	}
}

int main(void) {
	int x, y;
	int i = 0;

	Tree *A = init_tree(); //A트리 생성
	
	srand((unsigned int)time(NULL));
	
	// y = rand() % ((end - start) + 1) + start; //start ~ end 사이 정수 출력
	y = rand() % 2 + 10; //10~11 난수
	TreeNode *rootNode = (TreeNode *)malloc(sizeof(TreeNode)); //루트 노드 생성
	
	rootNode->data = y;
	rootNode->left = NULL;
	rootNode->right = NULL;
	A->root = rootNode; //A트리의 루트 설정
	
	printf("root : %d\n",y);
	
	TreeNode *nowRoot = rootNode;
	while(1) {
	//for(i = 0; i < 10; i++) {
		x = rand() % 2 + 1; //1~2 숫자 출력
		y = rand() % 100 + 10; //10~11 난수
		printf("[%d번째] x : %d / y : %d\n",i,x,y);
		
		if(x == 1) {
			//left 추가
			nowRoot = addNode_left(nowRoot,y);
		} else { //x == 2
			//right 추가
			nowRoot = addNode_right(nowRoot,y);
		}
		
		i++;
		if(nodeCnt == 10) break;
	}
	
	printf("\n\n[전위 반복 순회]\n");
	iterpreorder(rootNode);
		
	printf("\n\n[후위 반복 실행]\n");
	iterpostorder(rootNode);
	
	printf("\n\n[중위 반복 실행]\n");
	iterinorder(rootNode);

	return 0;
}
