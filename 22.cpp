#include<iostream>
#include<string>
#include<cstring>
#include<stdlib.h> 
#include<ctype.h>
#include<fstream>
#define N 20
using namespace std;
/*����ṹ��*/
typedef struct wenjian{
	char data[N];
	int shu;
	struct wenjian *zuo;
	struct wenjian *you;
}wenjian,*bwenjian;
class Word{//����һ���ʻ���� 
public:
	Word();
	int get_word(int start, int end, char* p, char* word);
	void create_wenjian(char* m, bwenjian& b);
	void Order(bwenjian b, FILE* q);
	int sum;
	int j;
	int i;
	char liang[N];
	char liang1[N];
	char word[N];
	char fwen[20];
	
};
/*��ʼ��*/
Word::Word()
{
	sum = 0;
	j = 0;
	i = 0;
}
/*�����ȡ�������ĺ���*/
int Word::get_word(int start, int end, char* p, char* word)
{
	memset(word, 0, sizeof(char));
	for (  i = start; i<end; i++)//ʹ��ѭ����ȡ�ļ� 
	{
		if (isalpha(p[i]))
		{
			word[j] = p[i];
			j++;
		}
		else if (j == 0)
		{
			continue;
		}
		else
		{
			word[j] = '\0';
			j = 0;
			sum++;
			break;
		}
	}
	return i;
}
/*���Һ���*/
void Word::create_wenjian(char* m, bwenjian& b)
{
	strcpy(liang, m);
	liang[0] = tolower(m[0]);
	if (b == NULL)
	{
		b = (bwenjian)malloc(sizeof(wenjian));//������ջ
		strcpy(b->data, m);
		b->shu = 1;
		b->zuo = NULL;
		b->you = NULL;
	}
	else
	{
		strcpy(liang1, b->data);
		liang1[0] = tolower(b->data[0]);
		if (strcmp(liang, liang1) == -1)
		{
			create_wenjian(m, b->zuo);
		}
		else if (strcmp(liang, liang1) == 1)
		{
			create_wenjian(m, b->you);
		}
		else
		{
			b->shu++;
		}
	}
}
/*д���ļ�*/
void Word::Order(bwenjian b, FILE* q)
{
	if (b != NULL)
	{
		Order(b->zuo, q);
		fprintf(q, "world��%-10s ����:%-9d\n", b->data, b->shu);
		printf("world��%-10s ����:%-9d\n", b->data, b->shu);
		Order(b->you, q);
	}
}
int main()
{
	Word w;//����Word����
	while (true)
	{
		memset(w.fwen, 0, sizeof(w.fwen));
		cout << "����������򿪵ĺ���" << endl;
		cin >> w.fwen;
		FILE *q;  
		q=fopen(w.fwen,"rb");
		if (q==NULL)
		{
			cout << "���ļ�ʧ�ܣ�" << endl;
			return false;
		}
		cout << "�Ѵ򿪣�" << w.fwen << endl;
		//��ʼ�����ļ�ͳ�� 
		fseek(q, 0, SEEK_END);
		int len = ftell(q);
		rewind(q);
		char *p = new char[len + 1];
		p[len] = 0;
		fread(p, 1, len, q);
		fclose(q);
		cout << p << endl;
		bwenjian b = NULL;
		while (w.i<len)
		{
			w.i = w.get_word(w.i, len, p, w.word);
			if (strlen(w.word) == 0)
			{
				break;
			}
			w.create_wenjian(w.word, b);
		}
		memset(w.fwen, 0, sizeof(w.fwen));
	   cout<<"\n"<<"������д����洢���ļ�: "<<endl;
		cin >> w.fwen;
		q=fopen(w.fwen,"w");
		if (q == NULL)
		{
			cout << "����д���ļ�" << endl;
			return false;
		}
		fprintf(q, "��Ƶͳ�ƽ��: \n");
		cout<<"��Ƶͳ�ƽ��:\n"<<endl;
		fprintf(q, "\n");
		w.Order(b,q);
		fprintf(q, "\n");
		fprintf(q, "world����: %d\n", w.sum);
		printf("world������%d\n", w.sum);
		fclose(q);
		cout<<"\n" << "��д���ļ�:" << w.fwen << endl;
	}
	return 0;
}

