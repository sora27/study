#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_NODE_SIZE 10

int nodeCnt = 1;

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

//순환 중위 순회
void inorder(TreeNode *root) {
	if(root != NULL) {
		inorder(root->left);
		printf("%d\n",root->data);
		inorder(root->right);
	}
}

//반복 중위 순회
void iterinorder(TreeNode *node) {
	StackType s;
	init_stack(&s);
	
	while(1) {
		while(node) {
			push(&s,node);
			node = node->left;
		}
		
		node = pop(&s);
		if(!node) break;
		printf("%d\n", node->data);
		node = node->right;
	}
}

TreeNode *addNode(TreeNode *curr, int data) {
	TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
	
	newNode->data = data;
	newNode->left = NULL;
	newNode->right = NULL;
	
	nodeCnt++;
	
	return newNode;
}

//트리 복사 - 재귀
TreeNode *copy(TreeNode *original) {
	 
	if(original == NULL)
		return NULL;

	TreeNode *newTree = (TreeNode *)malloc(sizeof(TreeNode));
	newTree->data = original->data; //현재 노드의 데이터 복사
	newTree->left = copy(original->left); //좌측 하위 트리 복사
	newTree->right = copy(original->right); //우측 하위 트리 복사
	
	return newTree;
}

//트리 복사 - 반복
TreeNode *copyWhile(TreeNode *node) {
	if(node == NULL)
		return NULL;
	
	StackType s;
	init_stack(&s);
	
	TreeNode *copyt = (TreeNode *)malloc(sizeof(TreeNode));
	copyt->data = node->data; //현재 노드의 데이터 복사
	copyt->left = NULL; //좌측 하위 트리 복사
	copyt->right = NULL; //우측 하위 트리 복사
	
	TreeNode *now = copyt;
	TreeNode *newright;
	TreeNode *parent;
	
	
	while(1) {
		while(node) {
			//if(node) {
				TreeNode *newTree = (TreeNode *)malloc(sizeof(TreeNode));
				newTree->data = node->left->data; //현재 노드의 데이터 복사
				newTree->left = NULL;
				newTree->right = NULL;
				now->left = newTree;
				
				if(node->right) {
					push(&s,now);
					push(&s,node->right);
				}

				if(node->left) {
					node = node->left;
				} else {
					break;
				}
				//node = node->left;
				now = newTree;
			//} else {
			//	break;
			//}
		}
		
		if(node->right) {
			push(&s,now);
			push(&s,node->right);
		}
		if(is_empty(&s)) break;
		newright = pop(&s);
		parent = pop(&s);
		
		node = newright;

		TreeNode *newTree = (TreeNode *)malloc(sizeof(TreeNode));
		newTree->data = newright->data; //현재 노드의 데이터 복사
		newTree->left = NULL;
		newTree->right = NULL;

		parent->right = newTree;
		node = node->left;
		
		
		
	}
	
	
	return copyt;
}

int main(void) {
	int x, y;
	int i =0;
	
	srand((unsigned int)time(NULL));
	
	y = rand() % 2 + 10; //10~11 난수
	TreeNode *rootNode = (TreeNode *)malloc(sizeof(TreeNode)); //루트 노드 생성
	
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
			if(nowRoot->left == NULL) {
				nowRoot->left = addNode(nowRoot,y);
				nowRoot = rootNode;
			} else {
				nowRoot = nowRoot->left;
				i++;
				continue;
			}
		} else { //x == 2
			//right 추가
			if(nowRoot->right == NULL) {
				nowRoot->right = addNode(nowRoot,y);
				nowRoot = rootNode;
			} else {
				nowRoot = nowRoot->right;
				i++;
				continue;
			}
		}
		
		
		i++;
		if(nodeCnt == 10) break;
	}
	
	printf("\n\n[원본 - 순환 중위]\n");
	inorder(rootNode);
	
	printf("\n\n[원본 - 반복 중위]\n");
	iterinorder(rootNode);
	
	
	printf("\n\n[순환 복사 - 순환 중위]\n");
	TreeNode *B_copy = copy(A); //원본 트리 복사1
	inorder(B_copy);
	
	printf("\n\n[순환 복사 - 반복 중위]\n");
	iterinorder(B_copy);
	
	printf("\n\n[반복 복사 - 순환 중위]\n");
	TreeNode *C_copy = copyWhile(A); //원본 트리 복사2
	inorder(C_copy);
	
	printf("\n\n[순환 복사 - 반복 중위]\n");
	iterinorder(B_copy);
	
	

	return 0;
}
