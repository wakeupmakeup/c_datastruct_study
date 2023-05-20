#include <stdio.h>

// 이진 탐색 트리 특징.
// 왼쪽 자식 노드 < 부모 노드 < 오른쪽 자식 노드

// 탐색과정은 다음과 같다.
// 부모노드의 값이 30일때 37을 탐색한다고 하면. 부모노드 보다 더 크기 때문에 오른쪽으로 간다.
// 오른쪽 자식노드로 갔을때 48이라고 한다면 37이 48보다 작으므로 왼쪽 자식으로 간다.
// 짜잔 37을 찾았다.

/* 트리의 순회 방법은 세가지.
    1. 전위 순회(pre-order)
    2. 중위 순회(in-order)
    3. 후위 순회(post-order)

순회라는 것은 트리에 포함된 모든 노드를 한 번씩 방문 하는 방법이다.

전위 순회 : 루트를 먼저 방문한다.
중위 순회 : 맨 왼쪽 자식을 방문한 후 루트를 방문한다. -> 가장 아래의 왼쪽 자식까지 쭉 가고나서 위로 올라온다.
후위 순회 : 루트 노드 기준으로 왼쪽 갔다가 오른쪽으로 간다.-> 루트 기준으로 왼쪽으로 가고. 또 거기서 왼쪽 오른쪽 방문 후에 해당하는 부모노드를 출력한다.

여기서 방문은 출력을 의미한다.
*/

// 트리 순회에 대한 예시.
// 먼저 완전 이진 트리라고 가정하고 진행했다.

int number = 15;

// 하나의 노드 정보를 선언하자!
// node라는 구조체를 treePointer라는 이름으로 포인터 형식으로 사용하겠다는 의미.
typedef struct node *treePointer;
typedef struct node
{
    int data;
    treePointer leftChild, rightChild;
} node;

// 전위 순회를 구현하자.
void preorder(treePointer ptr)
{ // 특정한 포인터 위치에서 전위 순회를 하도록 만든다.
    if (ptr != NULL)
    {                              // 해당 포인터가 NULL값이 아니라면. -> 어떤 데이터를 가지고 있다면.
        printf("%d ", ptr->data);  // 자신의 데이터를 먼저 출력한 후에
        preorder(ptr->leftChild);  // 왼쪽 노드를 기준으로 해서 전위순회를 시행. (이때 실행되는 건 printf())
        preorder(ptr->rightChild); // 왼쪽을 했다면 재귀적으로 오른쪽도 해준다.
    }
}

// 중위 순회
// 왼쪽 부터 방문하고 출력후에 오른쪽
void inorder(treePointer ptr)
{
    if (ptr != NULL)
    {
        inorder(ptr->leftChild);
        printf("%d ", ptr->data);
        inorder(ptr->rightChild);
    }
}

// 후위 순회
void postorder(treePointer ptr)
{
    if (ptr != NULL)
    {
        postorder(ptr->leftChild);
        postorder(ptr->rightChild);
        printf("%d ", ptr->data);
    }
}

// 바로 만든 위의 함수를 실행시켜보자.
int main()
{
    node nodes[number + 1]; // 총 15개의 노드가 담길 수 있는 데이터배열만들기.
    for (int i = 1; i <= number; i++)
    {
        nodes[i].data = i; // 1~15까지 데이터들이 들어 갈 수 있게 만들었다.
        nodes[i].leftChild = NULL;
        nodes[i].rightChild = NULL;
        // 일단 왼, 오른쪽 자식 노드들을 NULL이라고 하고 아직 연결 작업은 하지 않았음.
        // 일단 노드들을 만들어주고 각각 데이터가 들어 갈 수 있게만 만들어 줬다.
    }

    // 이제 연결해 주자.
    for (int i = 1; i <= number; i++)
    {

        // 여기서 i가 2의 배수라면 이라는 말은 위 조건일 경우 왼쪽 노드라고 하는 것이다.
        /* 트리에서 자식읜 인덱스는 다음과 같이 표현할 수 있다.
        왼쪽 자식 -> 2*i (2의 배수) 다시 말하면 짝수는 왼쪽
        오른쪽 자식 -> 2*i+1 (2의배수에 +1) 홀수는 오른쪽이다.

        부모 노드의 인덱스는 이렇게 표현 가능하다.
        부모 노드 -> i/2

        그리고 c에선 배열 인덱스에 대한 연산에서 정수 내림 처리한다.
        nodes[i/2]에서 i가 1이라면 0.5가 아니라 0이 된다. 즉,
        nodes[0] = 0번째 배열 -> 부모노드가 되는것이다.

        nodes[i/2] 에서 i가 3이라면? i가 2일때랑 값이 똑같다. 왜냐면 내림처리 하니까 그렇다.
        똑같이 1을 가르키는데 이를 구분하기 위해서 아래 if문을 사용한 것이다.
        */
        if (i % 2 == 0)
        {
            nodes[i / 2].leftChild = &nodes[i];
            // 짝수번째 인덱스 자기 자신이 leftChild가 된다.
        }
        else
        {
            nodes[i / 2].rightChild = &nodes[i];
            // 그게 아니고 홀수라면 오른쪽 자식노드가 된다.
        }
    }

    preorder(&nodes[1]);
    // inorder(&nodes[1]);
    // postorder(&nodes[1]);

    return 0;
}
