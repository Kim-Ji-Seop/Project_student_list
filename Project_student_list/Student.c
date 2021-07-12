#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <string.h>
//20210712
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
	head = (Student*)malloc(sizeof(Student));
	tail = (Student*)malloc(sizeof(Student));
	head->next = tail;
	head->prev = head;
	tail->next = tail;
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
	int key = 0;
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
	{ //오름차순 , 끝을 넘어가지 않도록
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
	int num;
	scanf("%d", &num);
	Student* cur = head->next;

	for (cur; cur != tail; cur = cur->next)
	{
		if (cur->num == num)
		{
			cur->prev->next = cur->next;
			cur->next->prev = cur->prev;
			free(cur);
			printf("삭제완료\n");
		}
	}
	printf("해당 데이터가 없습니다.\n");
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
			printf("%8d ", cur->scores[i]);
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

