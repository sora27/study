#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_NODE_SIZE 20

int nodeCnt;

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
		printf("%d | ",root->data);
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
		if(!node) break; //스택이 비어있는 상태에서 (윗줄에서) 팝하면 node 데이터는 없기 때문에 바로 아랫줄의 node->data 출력이 세그먼트오류가 발생한다. 그래서 스택이 비어있으면 break로 마무리.
		// if(is_empty(&s)) break; //is_empty를 쓰지 않은 이유 : 스택의 마지막 데이터를 팝했다고해서 순환이 모두 끝난게 아니기 때문에.
		printf("%d\n", node->data);
		node = node->right;
	}
}

//노드 생성
TreeNode *new_node(int item) {
	TreeNode *temp = (TreeNode *)malloc(sizeof(TreeNode));
	temp->data = item;
	temp->left = temp->right = NULL;

	nodeCnt++;
	return temp;
}

//노드 추가 - 순환
TreeNode *insert_node(TreeNode *node, int key) {
	if(node == NULL) return new_node(key);

	if(key < node->data) {
		node->left = insert_node(node->left, key);
	} else if(key > node->data) {
		node->right = insert_node(node->right, key);
	}

	return node;
}

//탐색 - 순환
TreeNode *search(TreeNode *node, int key) {
	if(node == NULL) return NULL;
	if(key == node->data) return node;
	else if(key < node->data)
		return search(node->left, key);
	else
		return search(node->right, key);
}

//트리 생성 - 순환
TreeNode *create() {
	int y;
	int i=1;
	
	TreeNode *rootNode = (TreeNode *)malloc(sizeof(TreeNode)); //루트 노드 생성
	
	y = rand() % 30 + 1; //1~30 난수
	rootNode->data = y;
	rootNode->left = rootNode->right = NULL;
	
	printf("root : %d\n",y);
  
    while(1) {
    	y = rand() % 30 + 1; //1~30 난수
		printf("[%d번째] y : %d\n",i,y);

        if(search(rootNode, y) == NULL) {
          insert_node(rootNode,y);
        } else {
          printf("중복 값 발생!! 다시 실행됩니다.\n");
          continue;
        }
		
		i++;
		if(nodeCnt == MAX_NODE_SIZE) break;
	}
	
	return rootNode;
}

//노드 추가 - 반복
TreeNode *insert_node_iter(TreeNode *node, int key) {
	
	while(1) {
		if(key < node->data) {
			if(node->left == NULL) {
				node->left = new_node(key);
				return node->left;
			}
			node = node->left;
		} else if(key > node->data) {
			if(node->right == NULL) {
				node->right = new_node(key);
				return node->right;
			}
			node = node->right;
		}
	}
}

//탐색 - 반복
TreeNode *search_iter(TreeNode *node, int key) {
	
	while(1) {
		if(node == NULL) return NULL;
		if(key == node->data) {
			return node;
		} else if(key < node->data) {
			node = node->left;
		} else {
			node = node->right;
		}
	}
}

//트리 생성 - 반복 (#2. 탐색 진행 후 없으면 노드 추가)
TreeNode *create_iter2() {	
	int y;
	int i=1;
	
	TreeNode *rootNode = (TreeNode *)malloc(sizeof(TreeNode)); //루트 노드 생성
	
	y = rand() % 30 + 1; //1~30 난수
	rootNode->data = y;
	rootNode->left = rootNode->right = NULL;
	
	printf("root : %d\n",y);
	
	while(1) {
		y = rand() % 30 + 1; //1~30 난수
		printf("[%d번째] y : %d\n",i,y);
		
		if(search_iter(rootNode, y) == NULL) {
          insert_node_iter(rootNode,y);
        } else {
          printf("중복 값 발생!! 다시 실행됩니다.\n");
          continue;
		}        
		
		i++;
		if(nodeCnt == MAX_NODE_SIZE) break;
	}
	
	return rootNode;
}

//트리 생성 - 반복 (#1. 탐색과 노드 추가 동시에 진행)
TreeNode *create_iter() {	
	int y;
	int i=1;
	
	TreeNode *rootNode = (TreeNode *)malloc(sizeof(TreeNode)); //루트 노드 생성
	
	y = rand() % 30 + 1; //1~30 난수
	rootNode->data = y;
	rootNode->left = rootNode->right = NULL;
	
	printf("root : %d\n",y);
	
	TreeNode *nowNode;
	
	while(1) {
		y = rand() % 30 + 1; //1~30 난수
		printf("[%d번째] y : %d\n",i,y);
		
		nowNode = rootNode;
		
		while(nowNode) {
			if(y == nowNode->data) {
				printf("중복 값 발생!! 다시 실행됩니다.\n");
				break;
			} else if(y < nowNode->data) {
				if(nowNode->left == NULL) {
					nowNode->left = new_node(y);
					break;
				} else {
					nowNode = nowNode->left;
				}

			} else if(y > nowNode->data) {
				if(nowNode->right == NULL) {
					nowNode->right = new_node(y);
					break;
				} else {
					nowNode = nowNode->right;
				}
			}
		}
        
		
		i++;
		if(nodeCnt == MAX_NODE_SIZE) break;
	}
	
	return rootNode;
}

int main(void) {
	
	srand(time(NULL));

	printf("\n\n[순환 생성]\n\n");
    nodeCnt = 1;
    TreeNode *tree = create();
	
	printf("\n\n[반복 생성 - 탐색과 추가 동시 진행]\n\n");
	nodeCnt = 1;
	TreeNode *tree_iter = create_iter();

	printf("\n\n[반복 생성 - 탐색 후 없으면 추가]\n\n");
	nodeCnt = 1;
	TreeNode *tree_iter2 = create_iter2();


    printf("\n\n[순환 생성 - 순환 중위]\n");
	inorder(tree);
	
	printf("\n\n[순환 생성 - 반복 중위]\n");
	iterinorder(tree);

	printf("\n\n[반복 생성 - 순환 중위]\n");
	inorder(tree_iter);
	
	printf("\n\n[반복 생성 - 반복 중위]\n");
	iterinorder(tree_iter);
	
	printf("\n\n[반복 생성 - 순환 중위]\n");
	inorder(tree_iter2);
	
	printf("\n\n[반복 생성 - 반복 중위]\n");
	iterinorder(tree_iter2);

	return 0;
}
