//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 1 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>	// printf, scanf를 사용하기 위한 헤더 파일
#include <stdlib.h> // malloc, free를 사용하기 위한 헤더 파일

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode
{
	int item;				// 이 노드가 저장할 정수 값
	struct _listnode *next; // 다음 노드를 가리키는 포인터
} ListNode;					// You should not change the definition of ListNode

typedef struct _linkedlist
{
	int size;		// 현재 연결 리스트에 들어 있는 노드 개수
	ListNode *head; // 첫 번째 노드를 가리키는 포인터
} LinkedList;		// You should not change the definition of LinkedList

///////////////////////// function prototypes ////////////////////////////////////

// You should not change the prototype of this function
int insertSortedLL(LinkedList *ll, int item);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode *findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);

//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	LinkedList ll; // 실제 연결 리스트 하나를 선언
	int c, i, j;   // c: 메뉴 선택, i: 입력한 값, j: 함수가 돌려준 index
	c = 1;		   // while문을 시작하기 위해 처음에는 1로 설정

	// 연결 리스트를 빈 상태로 초기화
	ll.head = NULL; // 아직 노드가 없으므로 첫 노드는 없음
	ll.size = 0;	// 노드 개수는 0개

	printf("1: Insert an integer to the sorted linked list:\n");	// 메뉴 1 출력
	printf("2: Print the index of the most recent input value:\n"); // 메뉴 2 출력
	printf("3: Print sorted linked list:\n");						// 메뉴 3 출력
	printf("0: Quit:");												// 메뉴 0 출력

	while (c != 0) // 사용자가 0을 입력하기 전까지 계속 반복
	{
		printf("\nPlease input your choice(1/2/3/0): "); // 메뉴 선택 안내
		scanf("%d", &c);								 // 사용자의 메뉴 입력을 c에 저장

		switch (c) // 사용자가 입력한 메뉴 번호에 따라 다른 작업 수행
		{
		case 1:																	  // 정수를 입력받아 정렬 상태를 유지하며 리스트에 삽입
			printf("Input an integer that you want to add to the linked list: "); // 값 입력 안내
			scanf("%d", &i);													  // 사용자가 입력한 정수를 i에 저장
			j = insertSortedLL(&ll, i);											  // i를 리스트에 넣고, 들어간 위치(index)를 j에 저장
			printf("The resulting linked list is: ");							  // 결과 리스트 출력 안내
			printList(&ll);														  // 현재 리스트 상태 출력
			break;																  // switch문 종료
		case 2:																	  // 가장 최근에 넣으려 했던 값과 그 결과 index 출력
			printf("The value %d was added at index %d\n", i, j);				  // i와 j 값 출력
			break;																  // switch문 종료
		case 3:																	  // 현재 정렬된 리스트 출력
			printf("The resulting sorted linked list is: ");					  // 출력 안내
			printList(&ll);														  // 리스트 내용 출력
			removeAllItems(&ll);												  // 출력 후 리스트의 모든 노드를 메모리에서 해제
			break;																  // switch문 종료
		case 0:																	  // 프로그램 종료 선택
			removeAllItems(&ll);												  // 종료 전에 남아 있는 모든 노드를 메모리에서 해제
			break;																  // switch문 종료
		default:																  // 정의되지 않은 메뉴 번호를 입력한 경우
			printf("Choice unknown;\n");										  // 잘못된 입력이라고 알려줌
			break;																  // switch문 종료
		}
	}
	return 0; // 프로그램을 정상 종료했다는 뜻의 값 반환
}

//////////////////////////////////////////////////////////////////////////////////

int insertSortedLL(LinkedList *ll, int item)
{
	ListNode *cur = ll->head;
	int idx = 0;
	// 리스트가 없는 경우
	if (ll == NULL)
		return -1;

	// 리스트 헤드 null인 경우
	if (cur == NULL)
	{
		insertNode(ll, 0, item);
		return 0;
	}

	while (cur != NULL)
	{
		// 이미 리스트에 값이 존재하는 경우
		if (cur->item == item)
			return -1;
		if ((cur->item) > item)
			break;
		cur = cur->next;
		idx++;
	}

	if (insertNode(ll, idx, item) < 0)
		return -1;
	return idx;
}

///////////////////////////////////////////////////////////////////////////////////

void printList(LinkedList *ll)
{
	ListNode *cur; // 현재 보고 있는 노드를 가리킬 포인터

	if (ll == NULL) // 리스트 자체가 없으면
		return;		// 함수 종료

	cur = ll->head; // 첫 번째 노드부터 보기 시작

	if (cur == NULL)	 // 첫 노드가 없으면 빈 리스트라는 뜻
		printf("Empty"); // Empty 출력

	while (cur != NULL) // 현재 노드가 존재하는 동안 반복
	{
		printf("%d ", cur->item); // 현재 노드의 값을 출력
		cur = cur->next;		  // 다음 노드로 이동
	}

	printf("\n"); // 보기 좋게 줄바꿈
}

void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head; // 현재 지우고 있는 노드를 가리킴
	ListNode *tmp;			  // 다음 노드를 잠깐 저장해둘 포인터

	while (cur != NULL) // 지울 노드가 남아 있는 동안 반복
	{
		tmp = cur->next; // 현재 노드를 free 하기 전에 다음 노드 주소를 저장
		free(cur);		 // 현재 노드가 차지한 메모리 해제
		cur = tmp;		 // 다음 노드로 이동
	}

	ll->head = NULL; // 이제 리스트가 비었으므로 head를 NULL로 설정
	ll->size = 0;	 // 노드 개수도 0으로 초기화
}

ListNode *findNode(LinkedList *ll, int index)
{
	ListNode *temp; // 원하는 위치까지 이동할 때 사용할 포인터

	if (ll == NULL || index < 0 || index >= ll->size) // 리스트가 없거나 index가 범위를 벗어나면
		return NULL;								  // 찾을 수 없으므로 NULL 반환

	temp = ll->head; // 첫 번째 노드부터 시작

	if (temp == NULL || index < 0) // 리스트가 비어 있거나 index가 잘못되면
		return NULL;			   // 찾을 수 없으므로 NULL 반환

	while (index > 0) // 원하는 위치까지 아직 더 가야 하면 반복
	{
		temp = temp->next; // 다음 노드로 이동
		if (temp == NULL)  // 이동했는데 노드가 없으면
			return NULL;   // 찾을 수 없으므로 NULL 반환
		index--;		   // 한 칸 이동했으니 남은 거리 1 감소
	}

	return temp; // 원하는 index의 노드 주소 반환
}

int insertNode(LinkedList *ll, int index, int value)
{
	ListNode *pre, *cur; // pre: 삽입 위치 바로 앞 노드, cur: 현재 또는 다음 노드

	if (ll == NULL || index < 0 || index > ll->size + 1) // 리스트가 없거나 index가 이상하면
		return -1;										 // 삽입 실패

	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0) // 빈 리스트이거나 맨 앞에 삽입하는 경우
	{
		cur = ll->head;						 // 기존 첫 노드를 cur에 저장
		ll->head = malloc(sizeof(ListNode)); // 새 노드 메모리 할당
		ll->head->item = value;				 // 새 노드에 값 저장
		ll->head->next = cur;				 // 새 노드의 next가 기존 첫 노드를 가리키게 연결
		ll->size++;							 // 노드 개수 1 증가
		return 0;							 // 삽입 성공
	}

	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL) // 삽입 위치 바로 앞 노드를 찾았다면
	{
		cur = pre->next;					  // 원래 그 뒤에 있던 노드를 cur에 저장
		pre->next = malloc(sizeof(ListNode)); // 새 노드 메모리 할당
		pre->next->item = value;			  // 새 노드에 값 저장
		pre->next->next = cur;				  // 새 노드 다음을 원래 노드와 연결
		ll->size++;							  // 노드 개수 1 증가
		return 0;							  // 삽입 성공
	}

	return -1; // 앞 노드를 찾지 못했으므로 삽입 실패
}

int removeNode(LinkedList *ll, int index)
{
	ListNode *pre, *cur; // pre: 삭제할 노드의 앞 노드, cur: 삭제할 노드

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size) // 리스트가 없거나 index가 범위를 벗어나면
		return -1;									  // 삭제 실패

	// If removing first node, need to update head pointer
	if (index == 0) // 첫 번째 노드를 지우는 경우
	{
		cur = ll->head->next; // 두 번째 노드를 잠깐 저장
		free(ll->head);		  // 첫 번째 노드 메모리 해제
		ll->head = cur;		  // head를 두 번째 노드로 변경
		ll->size--;			  // 노드 개수 1 감소

		return 0; // 삭제 성공
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL) // 삭제할 노드 바로 앞 노드를 찾았다면
	{
		if (pre->next == NULL) // 그런데 실제 삭제할 노드가 없으면
			return -1;		   // 삭제 실패

		cur = pre->next;	   // 삭제할 노드를 cur에 저장
		pre->next = cur->next; // 앞 노드가 삭제할 노드의 다음 노드를 가리키게 연결
		free(cur);			   // 삭제할 노드 메모리 해제
		ll->size--;			   // 노드 개수 1 감소
		return 0;			   // 삭제 성공
	}

	return -1; // 앞 노드를 찾지 못했으므로 삭제 실패
}
