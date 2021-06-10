#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_QUEUE_SIZE 10

int nodeCnt = 1;
/*** START 구조체 선언 ***/
typedef int element;
typedef struct TreeNode {
	element data;
	struct TreeNode *left;
	struct TreeNode *right;
}TreeNode;

//트리 구조체
typedef struct Tree{
	TreeNode* root;
}Tree;
/*** END 구조체 선언 ***/

void error(char str[])
{
   printf("%s\n", str);
   exit(1);
}

/*** START 트리 ***/
//트리 초기화
void init(Tree *t) {
	t->root = NULL;
}
/*** END 트리 ***/


//순환 전위 순회 - ok
void preorder(TreeNode *root) {
	if(root != NULL) {
		printf("%d | ",root->data);
		preorder(root->left);
		preorder(root->right);
	}
}

//순환 중위 순회 - ok
void inorder(TreeNode *root) {
	if(root != NULL) {
		inorder(root->left);
		printf("%d | ",root->data);
		inorder(root->right);
	}
}

//순환 후위 순회 - ok
void postorder(TreeNode *root) {
	if(root != NULL) {
		postorder(root->left);
		postorder(root->right);
		printf("%d | ",root->data);
	}
}

//순환 버전
int search(TreeNode *node, element key) {
	
	if(node != NULL) {
		if(key == node->data) {
			return 1;
		}
		else {
			if(node->left) search(node->left,key);
			if(node->right) search(node->right,key);
			
		}
	}
}

//삽입하고 루트 반환
TreeNode *addNode_left(TreeNode *root, element data) {
	
	TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
	
	newNode->data = data;
	newNode->left = NULL;
	newNode->right = NULL;
	TreeNode *curr = root;
	
	if(curr->left == NULL) {
		root->left = newNode;
		nodeCnt++;
		return root;
	} else {
		return root->left;
	}
}

TreeNode *addNode_right(TreeNode *root, element data) {
	
	TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
	
	newNode->data = data;
	newNode->left = NULL;
	newNode->right = NULL;
	TreeNode *curr = root;
	
	if(curr->right == NULL) {
		curr->right = newNode;
		nodeCnt++;
		return root;
	} else {
		return curr->right;
	}
}

int main(void) {
	int x, i, snode;
	element y;
	Tree A;
	init(&A);
	
	srand((unsigned int)time(NULL));
	
	y = rand() % 100 + 1; //1~100 난수
	TreeNode *rootNode = (TreeNode *)malloc(sizeof(TreeNode));
	
	rootNode->data = y;
	rootNode->left = NULL;
	rootNode->right = NULL;
	A.root = rootNode;
	
	printf("root : %d\n",y);
	
	TreeNode *nowRoot = rootNode;
	i = 0;
	while(1) {
		x = rand() % 2 + 1; //1~2 숫자 출력
		y = rand() % 100 + 1; //1~100 난수
		printf("[%d번째] x : %d / y : %d\n",i+2,x,y);

		snode = search(rootNode,y);
		if(snode == 1) {
			printf("y = %d 가 존재합니다. 다시 실행됩니다.\n",y);
			continue;
		}
		
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
	
	printf("\n\n[전위 순회 실행]\n");
	preorder(rootNode);
	
	printf("\n\n[중위 순회 실행]\n");
	inorder(rootNode);
		
	printf("\n\n[후위 순회 실행]\n");
	postorder(rootNode);

	return 0;
}
