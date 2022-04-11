#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 4

typedef char element;
typedef struct {
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;

QueueType *createQueue();
int freeQueue(QueueType *cQ);
int isEmpty(QueueType *cQ);
int isFull(QueueType *cQ);
void enQueue(QueueType *cQ, element item);
void deQueue(QueueType *cQ, element* item);
void printQ(QueueType *cQ);
void debugQ(QueueType *cQ);
element getElement();

int main(void)
{
	QueueType *cQ = createQueue();
	element data;

	char command;
	do{
        printf("[------------ [Cho Daehyeon] [2016039075] ------------]\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'i': case 'I':
			data = getElement();
			enQueue(cQ, data);
			break;
		case 'd': case 'D':
			deQueue(cQ,&data);
			break;
		case 'p': case 'P':
			printQ(cQ);
			break;
		case 'b': case 'B':
			debugQ(cQ);
			break;
		case 'q': case 'Q':
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

QueueType *createQueue()
{
	QueueType *cQ;
	cQ = (QueueType *)malloc(sizeof(QueueType));    // 원형 큐 생성하고 메모리 할당
	cQ->front = 0;      // 큐의 front 0으로 초기화
	cQ->rear = 0;       // 큐의 rear 0으로 초기화
	return cQ;
}

int freeQueue(QueueType *cQ)
{
    if(cQ == NULL) return 1;    
    free(cQ);       // 큐에 할당된 메모리 해제
    return 1;
}

element getElement()
{
	element item;
	printf("Input element = ");
	scanf(" %c", &item);        // 큐에 아이템 삽입
	return item;
}

int isEmpty(QueueType *cQ)
{
	if (cQ->front == cQ->rear){     // 큐의 front와 rear가 같은지 확인
		printf("Circular Queue is empty!");     // 같으면 빈 큐
		return 1;
	}
	else return 0;
}

int isFull(QueueType *cQ)
{
	if (((cQ->rear+1)%MAX_QUEUE_SIZE) == cQ->front) {   // 큐의 front가 rear의 한 자리 앞에 있는지 확인
		printf(" Circular Queue is full!");     // 한 자리 앞에 있으면 꽉 찬 큐
		return 1;
	}
	else return 0;
}

void enQueue(QueueType *cQ, element item)
{
	if(isFull(cQ)) return;      // 큐가 꽉 차 있으면 종료
	else {
		cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE;     // 큐의 rear를 한 자리 뒤로 옮김
		cQ->queue[cQ->rear] = item;     // 한 자리 뒤로 옮긴 rear에 새 아이템 삽입
	}
}

void deQueue(QueueType *cQ, element *item)
{
	if(isEmpty(cQ)) return;     // 큐가 비어 있으면 종료
	else {
		cQ->front = (cQ->front + 1)%MAX_QUEUE_SIZE;     // 큐의 front를 한 자리 뒤로 옮김
		*item = cQ->queue[cQ->front];       // 한 자리 뒤로 옮긴 front의 주소값을 *item에 저장
		return;
	}
}


void printQ(QueueType *cQ)
{
	int i, first, last;

	first = (cQ->front + 1)%MAX_QUEUE_SIZE; // 큐에서 어디서부터 출력할지 지정
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE;   // 어디까지 출력할지 지정

	printf("Circular Queue : [");

	i = first;
	while(i != last){
		printf("%3c", cQ->queue[i]);    // first부터 큐에 저장된 값 출력
		i = (i+1)%MAX_QUEUE_SIZE;       // i가 last가 될때까지 하나씩 증가
	}
	printf(" ]\n");
}


void debugQ(QueueType *cQ)
{

	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++)
	{
		if(i == cQ->front) {
			printf("  [%d] = front\n", i);  // front 위치 출력
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]);   // 큐의 인덱스와 값 출력
	}
	//printQ(cQ);
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);     // front와 rear의 위치 출력
}