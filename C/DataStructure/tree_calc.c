#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NODE_SIZE 20

/*** START 구조체 선언 ***/
typedef int element;
typedef struct TreeNode {
	element data;
	struct TreeNode* left;
	struct TreeNode* right;
}TreeNode;

//스택 구조체
typedef struct StackType{
	TreeNode* node[MAX_NODE_SIZE];
	int top;
}StackType;
/*** END 구조체 선언 ***/

/*** START 후위식 변환 스택 ***/
//스택 구조체
typedef struct stack {
    int stack[100];
    int top;
}stack;
 
void stack_init(stack *s) {
    s->top = -1;
}
 
//스택이 비어있는지 체크
int stack_empty(stack *s) {
    if (s->top == -1) {
        return 1;
    }
        return 0;
}
 
//삽입
void push_s(stack *s, int data) {
    s->top += 1;
    s->stack[s->top] = data;
}
 
//삭제
int pop_s(stack *s){
    if (stack_empty(s) == 1) {
        printf("stack is empty..");
		return 0;
    }else{
		int tmp = s->stack[s->top];
        s->top -= 1;
		return tmp;
    }
}
 
//맨위 값 출력
int peek_s(stack *s) {
	return s->stack[s->top];
}
/*** END 스택 ***/

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

void showNodeData(element data) {
	if (data >= 0 && data <= 9) printf("%d | ", data);
	else printf("%c | ", data);
}

//순환 후위 순회
void postorder(TreeNode *root) {
	if(root != NULL) {
		postorder(root->left);
		postorder(root->right);
		showNodeData(root->data);
		//printf("%d | ",root->data);
	}
}

//노드 생성
TreeNode *new_node(element item) {
	TreeNode *temp = (TreeNode *)malloc(sizeof(TreeNode));
	temp->data = item;
	temp->left = temp->right = NULL;

	return temp;
}

int precedence(char op)
{
	switch (op) {
		case '(': case ')': return 1;
		case '{': case '}': return 2;
		case '[': case ']': return 3;
		case '+': case '-': return 4;
		case '*': case '/': return 5;
	}
	return -1;
}

void resetExpression(char exp[], int len) {
	for(int i = 0; i <len; i++) {
		exp[i] = '\0';
	}
}

//중위수식을 후위수식으로 변환
/*
숫자는 후위수식 배열에 바로 담는다
여는 괄호가 나오면 무조건 push
닫는 괄호가 나오면 같은 쌍의 여는 괄호가 나올때까지 pop으로 후위수식 배열에 담기
*/
char* infix_to_postfix(char expr[])
{
	int i = 0;
	char c, op;

	//두 자리인 경우를 위해 임시 배열 생성
	char tmpExp[100] = {0,};
	int tmpCnt = 0;

	//후위수식 담을 배열 생성
	int count = 0;
	int length = strlen(expr);
	char *changeVal = (char *)malloc(sizeof(char)*length); //메모리 동적 할당
	memset(changeVal,'\0',length); //메모리 초기화

	stack s;
	stack_init(&s);
	
	for(i = 0; i < length; i++) {
		c = expr[i];
		
		//현재 문자가 숫자이면
		if ((c >= '0' && c <= '9')) {
			tmpExp[tmpCnt++] = c; //우선 임시 배열에 저장

			//현재 문자의 다음 문자가 특수문자이면.. (,),{,},[,],+,-,*,/ 임시 배열에 담긴 값을 후위수식 배열로 옮기고 임시배열 초기화.
			if(expr[i+1] == '(' || expr[i+1] == ')' || expr[i+1] == '{' || expr[i+1] == '}' || expr[i+1] == '[' || expr[i+1] == ']' || expr[i+1] == '+' || expr[i+1] == '-' || expr[i+1] == '*' || expr[i+1] == '/' || i == length-2) {
				
				//임시 배열값을 후위 수식 배열로 담기.
				for(int j = 0; j < tmpCnt; j++) {
					changeVal[count++] = tmpExp[j];
				}
				changeVal[count++] = ' '; //두자릿수 구분을 위해 띄어쓰기로 구분

				//임시 배열 초기화
				resetExpression(tmpExp,tmpCnt);
				tmpCnt = 0;
			}
		}
		else if (c == '(' || c == '{' || c == '[') //여는 괄호는 무조건 push
			push_s(&s,c);
		else if (c == ')') {
			while (stack_empty(&s) == 0) {
				op = pop_s(&s);
				if (op == '(') break;
				else changeVal[count++] = op;
			}
		}
		else if (c == '}') {
			while (stack_empty(&s) == 0) {
				op = pop_s(&s);
				if (op == '{') break;
				else changeVal[count++] = op;
			}
		}
		else if (c == ']') {
			while (stack_empty(&s) == 0) {
				op = pop_s(&s);
				if (op == '[') break;
				else changeVal[count++] = op;
			}
		}
		else if (c == '+' || c == '-' || c == '*' || c == '/') {
			while (stack_empty(&s) == 0) //스택에 값이 있으면 반복
			{
				op = peek_s(&s);
				if (precedence(c) <= precedence(op)) { //스택에 있는 문자의 우선순위가 높으면
					changeVal[count++] = op;
					pop_s(&s);
				}
				else break;
			}
			push_s(&s,c);
		}
	}
   
	//스택에 데이터가 없을때까지 스택의 데이터 전부 pop해서 후위식에 넣기
	while (stack_empty(&s) == 0)
		changeVal[count++] = pop_s(&s);

	return changeVal;
}

// 수식 트리 생성
TreeNode *makeTree(char exp[]) {
	
	StackType stack;
	init_stack(&stack);

	int expLen = strlen(exp);
	int i;
	
	TreeNode* pnode;
	
	//두 자리인 경우를 위해 임시 배열 생성
	char tmpExp[100] = {0,};
	int tmpCnt = 0;
	
	for (i = 0; i < expLen; i++) {
		if (exp[i] >= '0' && exp[i] <= '9') { //피연산자(숫자)
			
			tmpExp[tmpCnt++] = exp[i]; //우선 임시 배열에 저장
			
			if(exp[i+1] == ' ') {
				pnode = new_node(atoi(tmpExp)); // 노드 생성 (문자를 정수로 바꿔서 저장)
				push(&stack, pnode); //스택에 삽입
				
				//임시 배열 초기화
				resetExpression(tmpExp,tmpCnt);
				tmpCnt = 0;
			}
			
			
		} else if(exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/') { //연산자
			
			pnode = new_node(exp[i]); // 노드 생성 
			pnode->right = pop(&stack);
			pnode->left = pop(&stack);
			
			push(&stack, pnode); //스택에 삽입
		}
	}

	return pop(&stack);
}

// 수식 트리 계산
int calc(TreeNode* t) {
	int op1, op2;

	if (t->left == NULL && t->right == NULL)
		return t->data;
	op1 = calc(t->left);
	op2 = calc(t->right);
	switch (t->data)
	{
		case '+': return op1 + op2;
		case '-': return op1 - op2;
		case '*': return op1 * op2;
		case '/': return op1 / op2;
	}

}

int main(void) {
	char expr[100];
	printf("수식을 입력하세요 : ");
	//scanf("%s", expr); //scanf의 %s는 공백 전까지의 문자열만 입력받는다. 따라서 띄어쓰기가 있으면 그전까지만 받게됨.
	fgets(expr,100,stdin);
	
	// 중위식을 후위식으로 변환
	char* s = infix_to_postfix(expr);
	printf("ㄴ후위수식 : %s\n",s);
    
	// 후위식으로 수식 트리 생성
	TreeNode *result = makeTree(s);
	
	// 수식 트리 후위 순회 출력
	printf("ㄴ트리 후위 순회 : ");
	postorder(result);
	
	// 수식 트리 연산
	printf("\nㄴ연산의 결과 : %d\n", calc(result));
	
	return 0;
}
