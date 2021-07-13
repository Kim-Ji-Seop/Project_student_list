#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//20210713
#pragma warning(disable: 4996)
#define MAX_NAME 20   // 이름 길이
#define MAX_SUBJECT 4 // 최대 과목수
// 프로그래밍, 데이터 사이언스, 공업수학, 논리회로및실험
typedef struct Student
{
	char name[MAX_NAME + 1];
	int num;                 //번호
	int scores[MAX_SUBJECT]; //과목당 점수 0.프로그래밍 1.데이터 사이언스 2.공업수학 3.논리회로및실험
	struct Student* next;    //next링크
	struct Student* prev;    //prev링크
} Student;

Student* head, * tail;

char* title[MAX_SUBJECT] = { "프로그래밍", "데이터사이언스", "공업수학", "논리회로및실험" };
//포인터 배열선언 , 각 인덱스마다 하나의 문자가 아니라 문자열의 형태로 저장하기 위함.
//각 포인터들의 배열이라고 생각하면된다.

void Initialize(); //초기화
void Run();
void Exit(); //종료하기 전에 할당한 메모리 해제

int main(void)
{
	Initialize(); //초기화
	Run();
	Exit(); //종료하기 전에 할당한 메모리 해제
	return 0;
}
void Initialize()
{
	head = (Student*)malloc(sizeof(Student));//양방향연결리스트 head
	tail = (Student*)malloc(sizeof(Student));//tail
	head->next = tail;//head->tail
	head->prev = head;
	tail->next = tail;//head<-tail
	tail->prev = head;
}
void AddData();
void DeleteData();
void SearchData();
void ListData();
int SelectMenu();
void Run()
{
	int choice = 0;
	printf("<학생성적관리 프로그램>\n");

	while ((choice = SelectMenu()) != 0)
	{
		switch (choice)
		{
		case 1:
			AddData();
			break;
		case 2:
			DeleteData();
			break;
		case 3:
			SearchData();
			break;
		case 4:
			ListData();
			break;
		default:
			printf("숫자를 잘못입력하셨습니다.\n");
			break;
		}
	}
	printf("프로그램을 종료합니다..");
	return;
}
int SelectMenu()
{
	int key;
	printf("---------------------------------------메뉴 선택-----------------------------------------------\n");
	printf("1. 학생 데이터 등록  2. 학생 데이터 삭제  3. 학생 데이터 검색  4. 학생 데이터 목록 출력  (0. 종료)\n");
	printf("=>");
	scanf("%d", &key);
	return key;
}
void AddData()
{ //학생 데이터 등록
	Student* node = (Student*)malloc(sizeof(Student));
	int num; //학생번호

	printf("학생의 이름: ");
	scanf("%s", node->name);
	printf("학생 번호: ");
	scanf("%d", &num);
	node->num = num;
	printf("<학생 성적 입력>\n");
	for (int i = 0; i < MAX_SUBJECT; i++)
	{
		printf("%s 성적: ", title[i]);
		scanf("%d", node->scores + i);
	}
	Student* cur = head->next;
	while (cur != tail)
	{ //끝을 넘어가지 않도록
		cur = cur->next;
	}
	Student* prev = cur->prev;
	prev->next = node;
	node->prev = prev;
	cur->prev = node;
	node->next = cur;
}
void DeleteData()
{
	int number;
	printf("삭제할 학생의 번호를 입력하시오: ");
	scanf("%d", &number);
	Student* cur = head->next;

	for (cur; cur != tail; cur = cur->next)
	{
		if (cur->num == number)
		{
			cur->prev->next = cur->next;
			cur->next->prev = cur->prev;
			free(cur);
			printf("삭제완료\n");
			return;
		}
	}

}
void SearchData()
{
	Student* cur = head->next;
	int num;
	printf("검색할 학생의 번호를 쓰시오 : ");
	scanf("%d", &num);
	for (cur; cur != tail; cur = cur->next)
	{
		if (cur->num == num)
		{
			printf("이름: %s\n", cur->name);
			printf("학생번호: %d\n", cur->num);
			for (int i = 0; i < MAX_SUBJECT; i++)
			{
				printf("%s 성적: %d\n", title[i], cur->scores[i]);
			}
			return;
		}
	}
	printf("데이터가 없습니다.\n");
}
void ListData()
{
	int s = 0;
	Student* cur = 0;

	printf("%4s %10s ", "번호", "이름");
	for (s = 0; s < MAX_SUBJECT; s++)
	{
		printf("%4s ", title[s]);
	}
	printf("\n");
	for (cur = head->next; cur != tail; cur = cur->next)
	{
		printf("%4d ", cur->num);
		printf("%10s ", cur->name);
		for (int i = 0; i < MAX_SUBJECT; i++)
		{
			printf("%10d ", cur->scores[i]);
		}
		printf("\n");
	}
}
void Exit() {
	Student* cur = head;

	while (cur->next && cur != tail) {
		cur = cur->next;
		free(cur->prev);
	}
	free(cur);
}

