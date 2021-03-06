// ConsoleApplication10.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>
typedef struct node1
{
	char m;
	struct node1 *next;
}Optr;
typedef struct node2
{
	int n;
	struct node2 *next;
}Opnd;
typedef struct node3
{
	Optr OPTR;
	Opnd OPND;
}OperandType;
Optr *InitStack()
{
	Optr *h;
	h = (Optr*)malloc(sizeof(Optr));
	h->next = NULL;
	return h;
}
Opnd *initStack()
{
	Opnd *h;
	h = (Opnd*)malloc(sizeof(Opnd));
	h->next = NULL;
	return h;
}
void Push1(Optr *h,char c)
{
	Optr *p;
	p = (Optr *)malloc(sizeof(Optr));
	p->m = c;
	p->next = h->next;
	h->next = p;
}
char GetTop1(Optr *p)
{
	return p->next->m;
}
int GetTop2(Opnd *p)
{
	if (p->next != NULL)
		return p->next->n;
	else
		return 0;
}
 int  In(char c,Optr *m)
{
	 if (c == '+' || c == '-' || c == '*' || c == '/'||c=='('||c==')')
		 return 1;
	 else
		 return 0;
}
 char Precede(char m, char n)
 {
	 if ((m == '+' || m == '-') && (n == '*' || n == '/' || n == '('))
		 return '<';
	 if ((m == '+' || m == '-') && (n == '+' || n == '-' || n == ')' || n == '#'))
		 return '>';
	 if ((m == '*' || m == '/') && n == '(')
		 return '<';
	 if ((m == '*' || m == '/') && (n == '+' || n == '-' || n == '*' || n == '/' || n == ')' || n == '#'))
		 return '>';
	 if ((m == '(') && (n == '*' || n == '/'||n=='+'||n=='-'||n=='('))
		 return '<';
	 if (m == ')' && (n == '+' || n == '-' || n == '*' || n == '/'))
		 return '>';
	 if (m == '#' && (n == '+' || n == '-' || n == '*' || n == '/'))
		 return '<';
	 if ((m == '#'&&n == '#')||m=='('&&n==')')
		 return '=';
 }
 void Pop1(Optr *h, char *m)
 {
	 Optr *p;
	 p = h->next;
	 if (p == NULL)
		 return;
	 else
	 {
		 if (h->next->m == ')'&&p->next->m == '(')
		 {
			 h->next = p->next->next;
			 free(p);
			 free(p->next);
		 }
		 else
		 {
			 h->next = p->next;
			 *m = p->m;
			 free(p);
			 return;
		 }
	 }
 }
 int Pop2(Opnd *h)
 {
	 Opnd *p;
	 int m;
	 p = h->next;
	 if (p== NULL)
		 return 0;
	 else
	 {
		 h->next = p->next;
		 m = p->n;
		 free(p);
	 }
	 return m;
 }
int Operate(int a, char theta, int b)
{
	switch (theta)
	{
	case'-':return a-b;
	case'+':return a+b;
	case'*':return a*b;
	case '/':
		if (b == 0)
			return 0;
		else
			return a/ b;
	}
}
void Push2(Opnd *p, int m)
{
	Opnd *q;
	q = (Opnd*)malloc(sizeof(Opnd));
	q->n = m;
	q->next = p->next;
	p->next = q;
}
int EvaluateExpression() {
	char c,theta,x;
	int a, b,k;
	Opnd *OPND;
	Optr *OPTR ;
	Optr *OP;
	OP=OPTR=InitStack();
	Push1(OPTR, '#');
	OPND=initStack();
	fflush(stdin);
	theta=c = getchar();
	while (c!='#')
	{
		if (!In(c, OP))
		{
			x = c - '0';
			Push2(OPND, x);
			c = getchar();
		}
		else
			switch (Precede(GetTop1(OPTR), c))
			{
			case'<':Push1(OPTR, c);
				theta=c = getchar();
				break;
			case'=':Pop1(OPTR, &x);
				c = getchar();
				break;
			case'>':
				x = c;
				Pop1(OPTR,&theta);
				if (c != ')')
				{
					c = getchar();
					k = c - '0';
					a = Pop2(OPND);
					b = Pop2(OPND);
					Push2(OPND, Operate(a, theta, b));
					Push1(OPTR, x);
					Push2(OPND, k);
					c = getchar();
				}
				else {
					a = Pop2(OPND);
					b = Pop2(OPND);
					Push2(OPND, Operate(a, theta, b));
				}
			}
	}
	if (c== '#')
	{
		while (OPTR ->next->m!='#')
		{
			Pop1(OPTR, &theta);
			b = Pop2(OPND);
			a = Pop2(OPND);
			Push2(OPND, Operate(a, theta, b));
		}
	}
	return GetTop2(OPND);
}
int main()
{
	int m;
	m=EvaluateExpression();
	printf("%d", m);
	system("pause");
    return 0;
}

