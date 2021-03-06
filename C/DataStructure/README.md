<h1>[C언어 자료구조]</h1>


<h3>check_matching_and_calc.c</h3>
<h5>스택을 활용하여 연산식의 괄호 검사 체크 후 연산 결과까지 출력(정적스택)</h5>
<h6>1. 4칙연산과 괄호(),{},[]를 포함하는 중위식 문자열 수식을 입력받아 괄호의 유혀성 검사 및 수식 계산 프로그램을 정적 스택으로 작성</h6>
<h6>2. 괄호의 우선순위는 [] > {} > ()</h6>
<h6>3. 피연산자는 2자리 수 이하</h6>
<h6>ex) 유효 : [3*(14+6)] = 60, [3*{6+10/(2+3)}] = 24 / 비유효 : (33*[4+65]), [13*{42+6)]: 종료(계산불필요)</h6>

<hr/>

<h3>queue_circle.c</h3>
<h5>원형 큐를 사용하여 연산 후 출력</h5>
<h6>1. 무작위로 1 혹은 2를 생성한 후 다시 생성한 하나의 무작위수(1~100)에 대해 해당 연산을(1:enqueue, 2:dequeue) 원형큐에 적용한다.</h6>
<h6>2. 큐에 적용할 연산은 30번, 큐 크기는 20으로 한다</h6>
<h6>3. 모든 연산 적용 후에 큐에 있는 데이터를 앞(front) 및 뒤(rear)부터 차례로 각각 출력하는 프로그램을 작성</h6>
<h6>4. 원형큐는 배열로 구현한다.</h6>

<hr/>

<h3>polynomial_addition.c</h3>
<h5>연결리스트를 사용하여 다항식의 덧셈</h5>
<h6>1. 계수가 0이 아닌 항을 표현한 식</h6>
<h6>2. 2개의 다항식을 입력받는다</h6>
<h6>3. 입력 다항식과 결과 다항식을 출력한다</h6>

<hr/>

<h3>polynomial_multiplication.c</h3>
<h5>연결리스트를 사용하여 다항식의 곱셈</h5>
<h6>1. 계수가 0이 아닌 항을 표현한 식</h6>
<h6>2. 2개의 다항식을 입력받는다</h6>
<h6>3. 입력 다항식과 결과 다항식을 출력한다</h6>

<hr/>

<h3>Linkedlist_queue.c</h3>
<h5>원형큐를 연결리스트로 구현하기</h5>
<h6>1. 무작위로 1 또는 2를 생성하고, 1~100 사이의 수를 랜덤으로 생성한다.</h6>
<h6>2. 1이 나오면 enqueue, 2가 나오면 dequeue를 실행하여 원형큐에 적용한다.</h6>
<h6>3. 원형큐에 적용할 연산은 10번으로 한다.</h6>
<h6>4. 생성한 모든 연산명과 무작위 수를 한 번에 출력하고 원형큐에 있는 데이터를 앞에서부터 차례로 출력한다.</h6>
<h6>5. 원형큐는 연결리스트로 구현한다.</h6>

<hr/>

<h3>LinkedList_calc.c(전역변수) / LinkedList_struct_calc.c(구조체)</h3>
<h5>4칙연산(+, -, *, /)과 괄호([], {}, ())를 포함하는 중위식 문자열 수식을 입력받아 괄호의 유효성 검사 및 수식 계산 프로그램을 작성</h5>
<h6>1. 괄호의 우선순위는 [] > {} > () 이다.</h6>
<h6>2. 피연산자는 2자리 수 이하로 한다.</h6>
<h6>3. (예) 유효: [3*(14+6)] = 60,  [3*{6+10/(2+3)}] = 24 / 비유효: (33*[4+65]), [13*{42+6)]: 종료(계산불필요)</h6>
<h6>4. 연결 리스트로 구현한다.</h6>

<hr/>

<h3>LinkedList_book.c</h3>
<h5>10권의 도서에 대한 도서정보를 (도서명, 저자명 (각 20자 미만), 가격, 출판년월(예: 2020/12)) 무작위로 1권씩 구조체를 사용하여 입력 받아 최근 출판년월순으로 모든 도서정보를 올림차순 및 내림차순으로 출력하되, 아래 기능을 수행하는 함수를 반드시 포함하는 프로그램을 작성</h5>
<h6>1. classify_book(): 입력받은 1권의 도서에 대해 2000년 미만의 그룹인지 이상의 그룹인지를 결정한다. (예: A 혹은 B)</h6>
<h6>2. store_book(): 그룹이 결정된 1권의 도서를 해당 그룹(예: A, B)에 추가하되, 추가된 각 그룹의 도서는 항상 출판년월 순으로(최근의 도서가 앞(처음)에) 유지한다.</h6>
<h6>3. merge_group(): 2그룹을 하나의 그룹으로 통합하되 각 그룹이 출판년월순으로 정렬되어 있다는 사실을 이용(merge 방식)한다.</h6>
<h6>4. 전역변수는 사용하지 않는다.</h6>
<h6>5. 모든 입출력은 main()에서만 한다.</h6>
<h6>6. 입력 받은 1권의 도서에 대해 ①과 ②를 호출한 후 다음 도서를 입력 받는다.</h6>

<hr/>

<h3>Tree_while.c</h3>
<h5>트리 반복 전위/중위/후위 순회</h5>
<h6>1. 무작위 수 X(1 혹은 2)를 생성한 후 다시 생성한 하나의 무작위수 Y(1~100)에 대해 항상 루트 노드부터 아래와 같은 규칙에 따라 Y를 노드값으로 하는 노드를 추가하면서 이진 트리를 구성한다. (전체 노드 개수는 10개로 하며 첫 노드는 루트 노드가 된다)</h6>
<h6>2. X 값에 따라 루트의 왼쪽(X=1) 혹은 오른쪽(X=2) 자식 노드로 한 개의 노드를 추가하되, 루트의 해당(1:왼쪽, 2:오른쪽) 서브트리가 공백이 아니면 새로운 무작위 수 X (1 혹은 2) 및 하나의 무작위수 Y(1~100)를 생성하여 해당 서브트리의 루트 노드부터 동일한 규칙을 적용하여 노드 한 개를 추가한다.</h6>
<h6>3. 이진 트리를 반복 방식으로 구성한 후, 반복 방식으로 각각 중위, 후위, 전위순회한 결과를 출력하는 프로그램 작성</h6>


<hr/>

<h3>Tree_recursion.c</h3>
<h5>트리 순회(재귀) 전위/중위/후위 순회</h5>
<h6>1. 무작위 수 X(1 혹은 2)를 생성한 후 다시 생성한 하나의 무작위수 Y(1~100)에 대해 항상 루트 노드부터 아래와 같은 규칙에 따라 Y를 노드값으로 하는 노드를 추가하면서 이진 트리를 구성한다. (전체 노드 개수는 10개로 하며 첫 노드는 루트 노드가 된다)</h6>
<h6>2. X 값에 따라 루트의 왼쪽(X=1) 혹은 오른쪽(X=2) 자식 노드로 한 개의 노드를 추가하되, 루트의 해당(1:왼쪽, 2:오른쪽) 서브트리가 공백이 아니면 새로운 무작위 수 X (1 혹은 2) 및 하나의 무작위수 Y(1~100)를 생성하여 해당 서브트리의 루트 노드부터 동일한 규칙을 적용하여 노드 한 개를 추가한다.</h6>
<h6>3. 이진 트리를 반복 방식으로 구성한 후, 재귀 방식으로 각각 중위, 후위, 전위순회한 결과를 출력하는 프로그램 작성</h6>

<hr/>

<h3>tree_equal.c</h3>
<h5>아래의 규칙으로 2개의 이진트리를 각각 생성하여 각 트리를 후위 순회한 결과를 출력한 후, 두 개의 이진 트리가 동일한(구조와 노드값이 동일) 트리인지 결정하는 프로그램을 순환과 반복 방식으로 확인</h5>
<h6>무작위 수 X(1 혹은 2)를 생성한 후 다시 생성한 하나의 무작위수 Y(10 혹은 11)에 대해 항상 루트 노드부터 아래와 같은 규칙에 따라 Y를 노드값으로 하는 노드를 추가하면서 이진 트리를 구성한다. (전체 노드 개수는 10개로 하며 첫 노드는 루트 노드가 된다)</h6>
<h6>(규칙) X 값에 따라 루트의 왼쪽(X=1) 혹은 오른쪽(X=2) 자식 노드로 한 개의 노드를 추가하되, 루트의 해당(1:왼쪽, 2:오른쪽) 서브트리가 공백이 아니면 새로운 무작위 수 X (1 혹은 2) 및 하나의 무작위수 Y(10 혹은 11)를 생성하여 해당 서브트리의 루트 노드부터 동일한 규칙을 적용하여 노드 한 개를 추가한다.</h6>

<hr/>

<h3>tree_copy.c (미완성 - 반복 복사)</h3>
<h5>구성한 이진 트리와 동일한 이진 트리를 순환, 반복 2가지 방식으로 각각 생성한 후(즉, 복사본) 각 방식별로 생성한 복사본과 원본 이진 트리를 중위 순회한 결과를 출력하는 프로그램을 작성</h5>
<h6>무작위 수 X(1 혹은 2)를 생성한 후 다시 생성한 하나의 무작위수 Y(10 혹은 11)에 대해 항상 루트 노드부터 아래와 같은 규칙에 따라 Y를 노드값으로 하는 노드를 추가하면서 이진 트리를 구성한다. (전체 노드 개수는 10개로 하며 첫 노드는 루트 노드가 된다)</h6>
<h6>(규칙) X 값에 따라 루트의 왼쪽(X=1) 혹은 오른쪽(X=2) 자식 노드로 한 개의 노드를 추가하되, 루트의 해당(1:왼쪽, 2:오른쪽) 서브트리가 공백이 아니면 새로운 무작위 수 X (1 혹은 2) 및 하나의 무작위수 Y(10 혹은 11)를 생성하여 해당 서브트리의 루트 노드부터 동일한 규칙을 적용하여 노드 한 개를 추가한다.</h6>

<hr/>

<h3>tree_height.c (미완성 - 반복 높이 구하기, 각 레벨의 노드 수 출력)</h3>
<h5>구성한 이진 트리의 높이를 순환, 반복 2가지 방식으로 각각 구하여 출력한 후,  각 레벨의 노드 수를 출력하는 프로그램을 작성</h5>
<h6>무작위 수 X(1 혹은 2)를 생성한 후 다시 생성한 하나의 무작위수 Y(10 혹은 11)에 대해 항상 루트 노드부터 아래와 같은 규칙에 따라 Y를 노드값으로 하는 노드를 추가하면서 이진 트리를 구성한다. (전체 노드 개수는 10개로 하며 첫 노드는 루트 노드가 된다)</h6>
<h6>(규칙) X 값에 따라 루트의 왼쪽(X=1) 혹은 오른쪽(X=2) 자식 노드로 한 개의 노드를 추가하되, 루트의 해당(1:왼쪽, 2:오른쪽) 서브트리가 공백이 아니면 새로운 무작위 수 X (1 혹은 2) 및 하나의 무작위수 Y(10 혹은 11)를 생성하여 해당 서브트리의 루트 노드부터 동일한 규칙을 적용하여 노드 한 개를 추가한다.</h6>

<hr/>

<h3>tree_create.c</h3>
<h5>순환, 반복 2가지 방식으로 구성한 이진 탐색 트리 각각에 대해 중위 순회한 결과를 출력하는 프로그램을 작성</h5>
<h6>(구성 규칙) 하나의 무작위수 Y(1~30)를 생성한 후 이진 탐색 트리를 순환, 반복 2가지 방식으로 각각 구성한다. (전체 노드 개수는 20개로(Y 중복값 배제) 하며 첫 노드는 루트 노드가 된다)</h6>

<hr/>

<h3>tree_delete.c</h3>
<h5>하나의 무작위수 Y(1~30)를 생성한 후 구성한 이진 탐색 트리에서 해당 값을 갖는 노드를 삭제한 후 이진 탐색 트리를 중위 순회한 결과를 출력하는 프로그램을 작성</h5>
<h6>(구성 규칙) 하나의 무작위수 Y(1~30)를 생성한 후 이진 탐색 트리를 순환, 반복 2가지 방식으로 각각 구성한다. (전체 노드 개수는 20개로(Y 중복값 배제) 하며 첫 노드는 루트 노드가 된다)</h6>

<hr/>

<h3>tree_calc.c</h3>
<h5>수식 트리는 단말 노드가 피연산자이며 비단말 노드가 연산자로 구성된다. 4칙 연산자를 포함하는 임의의 중위 수식(예: A*B+C/2)을 입력받아 올바르게 수식 트리를 구성한 후에 후위순회 결과를 출력하는 프로그램을 작성 (후위순회 결과가 후위 표기식이면 수식 트리를 올바르게 구성한 것임)</h5>

<hr/>

<h3>graph_create.c</h3>
<h5>임의의 그래프(정점 10개)를 인정행렬 방식, 인접리스트 방식 두 가지로 구성한 후 각각 DFS(recursion 및 nonrecurson) 및 BFS로 순회한 결과(정점번호:1~10)를 출력하는 프로그램 작성</h5>

<hr/>

<h3>graph_connected-component.c</h3>
<h5>아래 그림(picture.JPG)을 보고 그래프 G를 인접리스트로 구성한 후 G의 각 연결요소(connected component)의 정점값을 출력하는 프로그램을 작성</h5>
<img src="./picture.JPG">


