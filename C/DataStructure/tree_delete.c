#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_NODE_SIZE 20

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
TreeNode *insert_node(TreeNode *node, int data) {
	if(node == NULL) return new_node(data);

	if(data < node->data) {
		node->left = insert_node(node->left, data);
	} else if(data > node->data) {
		node->right = insert_node(node->right, data);
	}

	return node;
}

//탐색 - 순환
TreeNode *search(TreeNode *node, int data) {
	if(node == NULL) return NULL;
	if(data == node->data) return node;
	else if(data < node->data)
		return search(node->left, data);
	else
		return search(node->right, data);
}

//왼쪽에서 가장 큰 수
TreeNode *left_maxNode(TreeNode *node) {
	 // 커서 노드
    TreeNode *cur = node;
 
    while(cur && cur->right){
        cur = cur->right;
    }
	
    return cur;
}

//오른쪽에서 가장 작은 수
TreeNode *right_minNode(TreeNode * node) {   
    // 커서 노드
    TreeNode *cur = node;
 
    while(cur && cur->left != NULL ){
        cur = cur->left;
    }
	
    return cur;
}

//노드 삭제 - 순환
TreeNode *delete_node(TreeNode *root, int key) {
	if(root == NULL) return NULL;
	
	if(key < root->data) {
		root->left = delete_node(root->left, key);
	} else if (key > root->data) {
		root->right = delete_node(root->right, key);
	} else { //같으면 삭제
		
		//왼쪽이나 오른쪽이 있는 경우 or 모두 없는 경우
		if(root->left == NULL) {
			TreeNode *tmp = root->right;
			free(root);
			return tmp;
		} else if(root->right == NULL) {
			TreeNode *tmp = root->left;
			free(root);
			return tmp;
		}
		
		//양쪽 모두 있는 경우
		//# 왼쪽에서 가장 큰 수
		TreeNode *temp = left_maxNode(root->left);
 
        root->data = temp->data;
        root->left = delete_node(root->left, temp->data);
		
		//# 오른쪽에서 가장 작은 수
		/*
        TreeNode *temp = right_minNode(root->right);
 
        root->data = temp->data;
        root->right = delete_node(root->right, temp->data);*/
		
	}
	return root;
}

//노드 삭제 - 반복
int delete_node_iter(TreeNode *node, int key) {
	
	TreeNode *delNode = NULL; //삭제할 노드
	TreeNode *parentNode = NULL; //삭제할 노드의 부모 노드
	
	//삭제 노드 찾기
	while(node && node->data != key) {
		parentNode = node;
		if(key < node->data) {
			node = node->left;
		} else {
			node = node->right;
		}
	}
	
	if(node == NULL) {
		printf("존재하지 않음.\n");
		return 0;
	}
	
	delNode = node;
	
	//삭제 노드의 서브 트리 확인
	if(delNode->left == NULL && delNode->right == NULL) { //서브가 모두 없는 경우
		printf("모두 없음\n");
		if(parentNode->left) {
			if(parentNode->left->data == delNode->data) {
				parentNode->left = NULL;
				return 1;
			}
		}
		parentNode->right = NULL;
		free(delNode);
		return 1;
	} else if(delNode->left && delNode->right) { //서브가 모두 있는 경우
		printf("모두 있음\n");
		TreeNode *tmp = NULL;
		/*
		//# 왼쪽 서브트리에서 가장 큰 데이터의 노드 찾기(가장 큰 노드는 서브 노드가 왼쪽에만 있거나 없다)
		tmp = delNode->left;
		if(tmp->right == NULL) {
			delNode->data = tmp->data;
			delNode->left = tmp->left;
			
			free(tmp);
			return 1;
		}
		
		while(tmp->right) {
			parentNode = tmp;
			tmp = tmp->right;
		}
		delNode->data = tmp->data;
		parentNode->right = tmp->left;
		
		free(tmp);
		return 1;
		*/
		
		//# 오른쪽 서브트리에서 가장 작은 데이터의 노드 찾기(가장 작은 노드는 서브 노드가 오른쪽에만 있거나 없다)
		tmp = delNode->right;
		if(tmp->left == NULL) {
			delNode->data = tmp->data;
			delNode->right = tmp->right;
			
			free(tmp);
			return 1;
		}
		
		while(tmp->left) {
			parentNode = tmp;
			tmp = tmp->left;
		}
		delNode->data = tmp->data;
		parentNode->left = tmp->right;
		
		free(tmp);
		return 1;
		
		
	} else { //서브가 왼쪽이나 오른쪽 중 하나만 있는 경우
		printf("한쪽만 있음\n");
		if(parentNode->left && (parentNode->left->data == key)) {
			if(delNode->left) parentNode->left = delNode->left;
			else parentNode->left = delNode->right;
		} else {
			if(delNode->left) parentNode->right = delNode->left;
			else parentNode->right = delNode->right;
		}
		//free(delNode);
		return 1;
	}
	
	return 1;
}

int main(void) {
	
	srand(time(NULL));

	printf("[순환 생성]\n");
	
	int y;
	int i=1;
	
	TreeNode *tree = (TreeNode *)malloc(sizeof(TreeNode)); //루트 노드 생성
	
	y = rand() % 30 + 1; //1~30 난수
	tree->data = y;
	tree->left = tree->right = NULL;
	
	printf("root : %d\n",y);
  
    while(1) {
    	y = rand() % 30 + 1; //1~30 난수
		printf("(%d) y : %d\n",i,y);

        if(search(tree, y) == NULL) {
          insert_node(tree,y);
        } else {
          printf("중복 값 발생!! 다시 실행됩니다.\n");
          continue;
        }
		
		i++;
		if(nodeCnt == MAX_NODE_SIZE) break;
	}

    printf("\n\n[순환 중위]\n");
	inorder(tree);
	
	printf("\n\n[노드 삭제]\n");
	while(1) {
		//#1. 삭제 할 노드의 데이터 뽑기
		y = rand() % 30 + 1; //1~30 난수
		printf("삭제할 노드 데이터 : %d\n",y);
		
		
		/*
		//#3. 삭제 진행(반복)
		delete_node_iter(tree, y);
		*/
		
		
		//#2. 노드 여부 확인
		if(search(tree,y) == NULL) {
			printf("트리에 삭제할 노드가 없습니다.\n\n");
			continue;
		}
		
		//#3. 삭제 진행(재귀)
		delete_node(tree,y);
		
		
		break;
	}
	
	printf("\n\n[삭제 후 - 순환 중위]\n");
	inorder(tree);
	
	return 0;
}
