//구조체를 이용한 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef int element;
typedef struct StackNode {
	element data;
	struct StackNode *link;
}StackNode;

typedef struct {
	StackNode *top;
}LinkedStackType;

void error(char *message) {
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void init(LinkedStackType *s) {
	s->top = NULL;
}

int is_empty(LinkedStackType *s) {
	return (s->top == NULL);
	// if(s->top == NULL) {
	// 	//error("Error : Stack is Empty.");
	// 	return 1;
	// }
	// return 0;
}

void push(LinkedStackType *s, element item) {
	StackNode *temp = (StackNode *)malloc(sizeof(StackNode));

	if(temp == NULL) error("메모리 할당 에러");
	temp->data = item;
	temp->link = s->top;
	s->top = temp;
}

void print_stack(LinkedStackType *s) {
	for(StackNode *p = s->top; p!=NULL; p = p->link)
		printf("%d->",p->data);
	printf("NULL \n");
}

element pop(LinkedStackType *s) {
	if(is_empty(s)) {
		error("스택이 비어있음");
	} else {
		StackNode *temp = s->top;
		int data = temp->data;
		s->top = temp->link;
		free(temp);
		return data;
	}
}

element peek(LinkedStackType *s) {
	if(!is_empty(s)) {
		return s->top->data;
	}
}

int precedence(char op)
{
	switch (op) {
		case '(': case ')': return 0;
		case '{': case '}': return 0;
		case '[': case ']': return 0;
		case '+': case '-': return 3;
		case '*': case '/': return 4;
	}
	return -1;
}


//괄호 검사
int testPair(char expr[]) {
	int i = 0;
	char ch, open_ch, pre_ch;
	int length = strlen(expr);

	LinkedStackType s;
	init(&s);

	for(i=0; i < length; i++) {
		ch = expr[i];
		switch (ch) {
			case '(':
				push(&s,ch);
				break;
			case '{':
				if(is_empty(&s) == 0) { //스택이 비어있지 않으면
					pre_ch = peek(&s);
					if(pre_ch == '(') { //중괄호 앞에 소괄호가 있으면 에러
						error("괄호 우선 순위 오류! => [] > {} > ()");
						break;
					}
				}
				push(&s,ch);
				break;
			case '[':
				if(is_empty(&s) == 0) { //스택이 비어있지 않으면
					pre_ch = peek(&s);
					if(pre_ch == '(' || pre_ch == '{') { //대괄호 앞에 중괄호나 소괄호가 있으면 에러
						error("괄호 우선 순위 오류! => [] > {} > ()");
						break;
					}
				}
				push(&s,ch);
				break;
			case ')':
			case '}':
			case ']':
				if(s.top == NULL) {
					return 0;
				} else {
					open_ch = pop(&s);

					if((open_ch == '(' && ch != ')') || (open_ch == '[' && ch != ']') || (open_ch == '{' && ch != '}')) {
						return 0;
					} else {
						break;
					}
				}
		}
	}

	if(s.top == NULL) return 1;
	else return 0;
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

	LinkedStackType itps;
	init(&itps);

	for(i = 0; i < length; i++) {
		c = expr[i];

		//현재 문자가 숫자이면
		if ((c >= '0' && c <= '9')) {
			tmpExp[tmpCnt++] = c; //우선 임시 배열에 저장

			//현재 문자의 다음 문자가 특수문자이면.. (,),{,},[,],+,-,*,/ 임시 배열에 담긴 값을 후위수식 배열로 옮기고 임시배열 초기화.
			if(expr[i+1] == '(' || expr[i+1] == ')' || expr[i+1] == '{' || expr[i+1] == '}' || expr[i+1] == '[' || expr[i+1] == ']' || expr[i+1] == '+' || expr[i+1] == '-' || expr[i+1] == '*' || expr[i+1] == '/') {

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
			push(&itps,c);
		else if (c == ')') {
			while (is_empty(&itps) == 0) {
				op = pop(&itps);
				if (op == '(') break;
				else changeVal[count++] = op;
			}
		}
		else if (c == '}') {
			while (is_empty(&itps) == 0) {
				op = pop(&itps);
				if (op == '{') break;
				else changeVal[count++] = op;
			}
		}
		else if (c == ']') {
			while (is_empty(&itps) == 0) {
				op = pop(&itps);
				if (op == '[') break;
				else changeVal[count++] = op;
			}
		}
		else if (c == '+' || c == '-' || c == '*' || c == '/') {
			while (is_empty(&itps) == 0) //스택에 값이 있으면 반복
			{
				op = peek(&itps);
				if (precedence(c) <= precedence(op)) { //스택에 있는 문자의 우선순위가 높으면
					changeVal[count++] = op;
					pop(&itps);
				}
				else break;
			}
			push(&itps,c);
		}
	}
   
	//스택에 데이터가 없을때까지 스택의 데이터 전부 pop해서 후위식에 넣기
	while (is_empty(&itps) == 0)
		changeVal[count++] = pop(&itps);

	return changeVal;
}


//후위수식 계산
element calc_postfix(char expr[]) {
	char c;
	int i = 0;
	int val, val1, val2;

	//두 자릿수를 위해 임시 배열 생성
	char tmpExp[100] = {0,};
	int tmpCnt = 0;

	LinkedStackType cp;
	init(&cp);
   
	//while (expr[i] != '\0') {
	for (i=0;expr[i] != '\0';i++) {
		c = expr[i];

		//현재 문자가 숫자이면
		if (c >= '0' && c <= '9') {

			tmpExp[tmpCnt++] = c; //임시 배열에 저장

			if(expr[i+1] == ' ') { //다음 문자열이 공백이면


				push(&cp,atoi(tmpExp)); //임시 배열을 숫자로 변환 후 스택에 push
				//printf("%d",atoi(tmpExp));

				//임시 배열 초기화
				resetExpression(tmpExp,tmpCnt);
				tmpCnt = 0;

			}
		}
		else if (c == '+' || c == '-' || c == '*' || c == '/') {
			val2 = pop(&cp);
			val1 = pop(&cp);
			switch (c) {
				case '+':
				push(&cp,val1 + val2);
				break;
				case '-':
				push(&cp,val1 - val2);
				break;
				case '*':
				push(&cp,val1 * val2);
				break;
				case '/':
				push(&cp,val1 / val2);
				break;
			}
		}
	}
   
	return pop(&cp);
}

void main()
{
	char expr[100];
	printf("수식을 입력하세요 : ");
	//scanf("%s", expr); //scanf의 %s는 공백 전까지의 문자열만 입력받는다. 따라서 띄어쓰기가 있으면 그전까지만 받게됨.
	fgets(expr,100,stdin);

	printf("\n\n");

	//1. 괄호 검사 시작
	if(testPair(expr) == 1) {
		printf("ㄴ괄호 검사 : 성공!\n");

		//2. 중위식을 후위식으로 변환
		char* s1 = infix_to_postfix(expr);
		printf("ㄴ중위수식: %s ==> 후위수식: %s\n", expr,s1);

		//3. 후위식 계산
		printf("ㄴ값 = %d\n", calc_postfix(s1));
	}
	else {
		printf("ㄴ괄호 검사 : 실패!.. 계산이 종료됩니다.\n");
	}
}
