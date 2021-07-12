#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <string.h>
//20210712
#pragma warning(disable: 4996)
#define MAX_NAME 20   // �̸� ����
#define MAX_SUBJECT 4 // �ִ� �����
// ���α׷���, ������ ���̾�, ��������, ��ȸ�ι׽���
typedef struct Student
{
	char name[MAX_NAME + 1];
	int num;                 //��ȣ
	int scores[MAX_SUBJECT]; //����� ���� 0.���α׷��� 1.������ ���̾� 2.�������� 3.��ȸ�ι׽���
	struct Student* next;    //next��ũ
	struct Student* prev;    //prev��ũ
} Student;

Student* head, * tail;

char* title[MAX_SUBJECT] = { "���α׷���", "�����ͻ��̾�", "��������", "��ȸ�ι׽���" };

void Initialize(); //�ʱ�ȭ
void Run();
void Exit(); //�����ϱ� ���� �Ҵ��� �޸� ����

int main(void)
{
	Initialize(); //�ʱ�ȭ
	Run();
	Exit(); //�����ϱ� ���� �Ҵ��� �޸� ����
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
	printf("<�л��������� ���α׷�>\n");

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
			printf("���ڸ� �߸��Է��ϼ̽��ϴ�.\n");
			break;
		}
	}
	printf("���α׷��� �����մϴ�..");
	return;
}
int SelectMenu()
{
	int key = 0;
	printf("---------------------------------------�޴� ����-----------------------------------------------\n");
	printf("1. �л� ������ ���  2. �л� ������ ����  3. �л� ������ �˻�  4. �л� ������ ��� ���  (0. ����)\n");
	printf("=>");
	scanf("%d", &key);
	return key;
}
void AddData()
{ //�л� ������ ���
	Student* node = (Student*)malloc(sizeof(Student));
	int num; //�л���ȣ

	printf("�л��� �̸�: ");
	scanf("%s", node->name);
	printf("�л� ��ȣ: ");
	scanf("%d", &num);
	node->num = num;
	printf("<�л� ���� �Է�>\n");
	for (int i = 0; i < MAX_SUBJECT; i++)
	{
		printf("%s ����: ", title[i]);
		scanf("%d", node->scores + i);
	}
	Student* cur = head->next;
	while (cur != tail)
	{ //�������� , ���� �Ѿ�� �ʵ���
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
			printf("�����Ϸ�\n");
		}
	}
	printf("�ش� �����Ͱ� �����ϴ�.\n");
}
void SearchData()
{
	Student* cur = head->next;
	int num;
	printf("�˻��� �л��� ��ȣ�� ���ÿ� : ");
	scanf("%d", &num);
	for (cur; cur != tail; cur = cur->next)
	{
		if (cur->num == num)
		{
			printf("�̸�: %s\n", cur->name);
			printf("�л���ȣ: %d\n", cur->num);
			for (int i = 0; i < MAX_SUBJECT; i++)
			{
				printf("%s ����: %d\n", title[i], cur->scores[i]);
			}
			return;
		}
	}
	printf("�����Ͱ� �����ϴ�.\n");
}
void ListData()
{
	int s = 0;
	Student* cur = 0;

	printf("%4s %10s ", "��ȣ", "�̸�");
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

