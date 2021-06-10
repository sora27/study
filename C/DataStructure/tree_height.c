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

//노드 생성
TreeNode *addNode(TreeNode *curr, int data) {
	TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
	
	newNode->data = data;
	newNode->left = NULL;
	newNode->right = NULL;
	
	return newNode;
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

//트리의 높이
int get_height(TreeNode *root) {
  if (!root)
    return 0;
  else {
    int left_h = get_height(root->left); // 왼쪽 서브트리의 높이를 순환호출을 통해 얻는다.
    int right_h = get_height(root->right); // 같은 방법으로 오른쪽 서브트리의 높이를 얻는다.
    return 1 + (left_h > right_h ? left_h : right_h); // 둘 중 큰 값에 1을 더해 반환한다.
  }
}

/*
void gs(TreeNode *n) {
	root = gs(n->left);
}


//각 레벨의 노드 개수
int cnt_perLevel(TreeNode *root, int h) {
	while(1) {
		for(int i = 0; i < h-2; i++) {
			root = cnt_perLevel(root->left);
		}
	}
	int cnt = 0;
	TreeNode *now = NULL;
	while(1) {
		for(int i = 0; i < h-2; i++) {
			if(root->left) {
				root = root->left;
				continue;
			}
			if(root->right) {
				root = root->right;
				continue;
			}
		}
		
		if(root->left) cnt++;
		if(root->right) cnt++;
	}
	for(int i = 0; i < h-1; i++) {
		if(root->left) {
			cnt++;
		}
		if(root->right) {
			cnt++;
		}
		if(root->left) {
			root = root->left;
		}
		if(root->right) {
			root = root->right;
		}
	}
	return cnt;
}
*/

int main(void) {
	
	srand(time(NULL));
	TreeNode *A = create_tree();

	int height = get_height(A);
	printf("이진트리 높이 : %d\n",height);
	
	/*
	int cnt;
	for(int i = 1; i < height; i++) {
		cnt = cnt_perLevel(A,i);
		printf("레벨 %d의 노드 개수 : %d\n",i,cnt);
	}
	*/
	
	
	return 0;
}
