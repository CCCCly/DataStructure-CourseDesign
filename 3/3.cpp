#include<iostream>
#include<stdlib.h>
using namespace std;
#define initsize 100
#define increment 20
typedef struct bitnode//��������� 
{
	int data;
	struct bitnode *lchild,*rchild;
}bitnode,*bitree;

typedef struct qnode//���� 
{
	bitree data;
	struct qnode *next;
}qnode,*queueptr;

typedef struct
{
	queueptr front;
	queueptr rear;
}linkqueue;

typedef struct//ջ 
{
	bitree *base;
	bitree *top;
	int stacksize;
}sqstack;

//��ʼ��ջ 
void initstack(sqstack &S)
{
	S.base=(bitree *)malloc(sizeof(bitree)*initsize);
	if(!S.base)
	exit(0);
	S.top=S.base;
	S.stacksize=initsize;
}

//��ջ 
void pop(sqstack &S,bitree &e)
{
	if(S.top-S.base==0)
	exit(0);
	S.top--;
	e = *S.top;
}

//��ջ 
void push(sqstack &S,bitree e)
{
	if(S.top-S.base>=S.stacksize)
	{
		S.base=(bitree *)realloc(S.base,sizeof(bitree)*(S.stacksize+increment));
		if(!S.base)
		exit(0);
		S.top=S.base+S.stacksize;
		S.stacksize+=increment;
	}
	*S.top=e;
	S.top++;
}

//�п�
bool emptystack(sqstack S)
{
	if(S.top-S.base)
	return false;
	else
	return true;
}

//����ջ
void destroystack(sqstack &S)
{
	if(S.base)
	free(S.base);	
} 

//��ʼ������ 
void initqueue(linkqueue &Q)
{
	Q.front=(qnode *)malloc(sizeof(qnode));
	if(!Q.front)
	exit(0);
	Q.rear=Q.front;
	Q.front->next=NULL;
}

//������ 
void enqueue(linkqueue &Q,bitree e)
{
	queueptr p;
	p=(qnode *)malloc(sizeof(qnode));
	if(!p)
	exit(0);
	p->data=e;
	p->next=NULL;
	Q.rear->next=p;
	Q.rear=p;
}

//������ 
void dequeue(linkqueue &Q,bitree &e)
{
	queueptr p;
	if(Q.front==Q.rear)
		return;
	p=Q.front->next;
	e=p->data;
	Q.front->next=p->next;
	if(p==Q.rear)
	Q.rear=Q.front;
	free(p);
}

//�пն��� 
bool emptyqueue(linkqueue Q)
{
	if(Q.front==Q.rear)
	return true;
	else
	return false;
}

//������������ 
void Createbitree(bitree &T,FILE *fp)
{
	int ch;
	fscanf(fp,"%d",&ch);
	if(ch==-1)
		T=NULL;
	else
	{
		T=(bitree)malloc(sizeof(bitnode));
		if(!T)
		exit(0);
		T->data=ch;
		Createbitree(T->lchild,fp);
		Createbitree(T->rchild,fp);	
	} 

}

//����ݹ���������� 
void preordertraverse(bitree T)
{
	if(T)
	{
		cout<<T->data<<" ";
		preordertraverse(T->lchild);
		preordertraverse(T->rchild);
	}
}

//����ݹ���������� 
void inordertraverse(bitree T)
{
	if(T)
	{
		inordertraverse(T->lchild);
		cout<<T->data<<" ";
		inordertraverse(T->rchild);
	}	
}

//�����ݹ���������� 
void postordertraverse(bitree T)
{
	if(T)
	{
		postordertraverse(T->lchild);
		postordertraverse(T->rchild);
		cout<<T->data<<" "; 
	}
}

//������������� 
void levelordertraverse(bitree T)
{
	linkqueue Q;
	bitree p;
	initqueue(Q);
	if(T)
	enqueue(Q,T);
	while(!emptyqueue(Q))
	{
		dequeue(Q,p);
		cout<<p->data<<" ";
		if(p->lchild)
		enqueue(Q,p->lchild);
		if(p->rchild)
		enqueue(Q,p->rchild);
	}
}

//����ǵݹ���������� 
void _preordertraverse(bitree T)
{
	sqstack S;
	bitree p;
	initstack(S);
	
	if(T)
	push(S,T);
	
	while(!emptystack(S))
	{
		pop(S,p);
		cout<<p->data<<" ";
		if(p->rchild)
		push(S,p->rchild);
		if(p->lchild)
		push(S,p->lchild);
	}
	
	destroystack(S);
}

//����ǵݹ���������� 
void _inordertraverse(bitree T)
{
	sqstack S;
	bitree p;
	initstack(S);
	
	if(T)
	p=T;
	
	while(p||!emptystack(S))
	{
		if(p)
		{
			push(S,p);
			p=p->lchild;
		}
		else
		{
			pop(S,p);
			cout<<p->data<<" ";
			p=p->rchild;
		}
	}
	
	destroystack(S);
}

//����ǵݹ���������� 
void _postordertraverse(bitree T)
{
	bitree p,prev;
	sqstack S;
	initstack(S);
	if(T)
	p=T; 
	while(p||!emptystack(S))
	{
		while(p)
		{
			push(S,p);
			p=p->lchild;
		}
		if(!emptystack(S))
		{
			p=*(S.top-1);
			if(p->rchild)
			{
				p=p->rchild;
				continue;
			}
			while(!p->rchild||p->rchild==prev)
			{
				cout<<p->data<<" ";
				prev=p;
				pop(S,p);
				
				if(emptystack(S))
					return;
				p=*(S.top-1);
			}
			if(p->lchild==prev)
				p=p->rchild;
		
		}
	}
	
	destroystack(S);
		
}

//����� 
int deepbitree(bitree T)
{
	if(!T)
		return 0;
	else
		return (max(deepbitree(T->lchild),deepbitree(T->rchild))+1);
} 


//���� 
int widthbitree(bitree T)
{
	int count=0,max=0;
	linkqueue Q;
	bitree e;
	bitree mark;
	initqueue(Q);
	
	if(T)
	{
		enqueue(Q,T);
		mark=Q.front->next->data;
	}
	while(!emptyqueue(Q))
	{
		dequeue(Q,e);
		count++;
		
		if(e->lchild)
		enqueue(Q,e->lchild);
		if(e->rchild)
		enqueue(Q,e->rchild);	
			
		if(e==mark)
			{
				if(max<count)
				max=count;
				count=0;
				mark=Q.rear->data;
			}
		
	}
	return max;
}

//������
int nodenum(bitree T)
{
	if(!T)
	return 0;
	else
	return nodenum(T->lchild)+nodenum(T->rchild)+1;
}


//���ٶ�����
void destroybitree(bitree &T)
{
	if(T)
	{
		if(T->lchild)
		destroybitree(T->lchild);
		if(T->rchild)
		destroybitree(T->rchild);
		free(T);
		T=NULL;
	}
}


//�ж���������� 
bool is_bstree(bitree T)
{
	sqstack S;
	bitree p;
	int last=-1;
	initstack(S);
	
	if(T)
	p=T;
	
	while(p||!emptystack(S))
	{
		if(p)
		{
			push(S,p);
			p=p->lchild;
		}
		else
		{
			pop(S,p);
			if(last>p->data)
			{
				destroystack(S);
				return false;
			}
			last=p->data;
			p=p->rchild;
		}
	}
	
	destroystack(S);
	return true;
	
/*	int last=0,flag=1;

if(T->lchild&&flag)
		is_bstree(T->lchild);
		
	if(T->data<last)
		flag=0;
		
	last=T->data;
	
	if(T->rchild&&flag)
		is_bstree(T->rchild);
		
	return flag;
*/
}
int main()
{
	FILE *fp;
	bitree T,M;
	fp=fopen("bitree.txt","r");
	if(!fp)
	{
		cout<<"���ļ�ʧ�ܣ�"<<endl;
		exit(0); 
	}
	cout<<"������1��"<<endl;
	Createbitree(T,fp);
	fclose(fp);
	cout<<"����ݹ������"<<endl;
	preordertraverse(T);
	cout<<endl<<endl;
	
	cout<<"����ǵݹ������"<<endl;
	_preordertraverse(T);
	cout<<endl<<endl;
	
	cout<<"����ݹ������"<<endl;
	inordertraverse(T);
	cout<<endl<<endl;
	
	cout<<"����ǵݹ������"<<endl;
	_inordertraverse(T);
	cout<<endl<<endl;
	
	cout<<"����ݹ������"<<endl;
	postordertraverse(T);
	cout<<endl<<endl;
	
	cout<<"����ǵݹ������"<<endl;
	_postordertraverse(T);
	cout<<endl<<endl;
	
	cout<<"���������"<<endl;
	levelordertraverse(T);
	cout<<endl<<endl;
	
	cout<<"��������ȣ�"<<endl;
	cout<<deepbitree(T)<<endl<<endl;
	
	cout<<"��������ȣ�"<<endl;
	cout<<widthbitree(T)<<endl<<endl;
	
	cout<<"�������������"<<endl;
	cout<<nodenum(T)<<endl<<endl;
	
	cout<<"�Ƿ�Ϊ������������"<<endl;
	if(is_bstree(T))
	cout<<"��"<<endl<<endl;
	else
	cout<<"��"<<endl<<endl;
	
	 
	
	cout<<endl<<endl<<endl;
	fp=fopen("bitree1.txt","r");
	if(!fp)
	{
		cout<<"���ļ�ʧ�ܣ�"<<endl;
		exit(0); 
	}
	cout<<"������2��"<<endl;
	Createbitree(M,fp);
	fclose(fp);
	cout<<"����ݹ������"<<endl;
	preordertraverse(M);
	cout<<endl<<endl;
	
	cout<<"����ǵݹ������"<<endl;
	_preordertraverse(M);
	cout<<endl<<endl;
	
	cout<<"����ݹ������"<<endl;
	inordertraverse(M);
	cout<<endl<<endl;
	
	cout<<"����ǵݹ������"<<endl;
	_inordertraverse(M);
	cout<<endl<<endl;
	
	cout<<"����ݹ������"<<endl;
	postordertraverse(M);
	cout<<endl<<endl;
	
	cout<<"����ǵݹ������"<<endl;
	_postordertraverse(M);
	cout<<endl<<endl;
	
	cout<<"���������"<<endl;
	levelordertraverse(M);
	cout<<endl<<endl;
	
	cout<<"��������ȣ�"<<endl;
	cout<<deepbitree(M)<<endl<<endl;
	
	cout<<"��������ȣ�"<<endl;
	cout<<widthbitree(M)<<endl<<endl;
	
	cout<<"�������������"<<endl;
	cout<<nodenum(M)<<endl<<endl;
	
	cout<<"�Ƿ�Ϊ������������"<<endl;
	if(is_bstree(M))
	cout<<"��"<<endl<<endl;
	else
	cout<<"��"<<endl<<endl;
	
	destroybitree(T);
	destroybitree(M); 
}
