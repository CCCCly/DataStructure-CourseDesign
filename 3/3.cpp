#include<iostream>
#include<stdlib.h>
using namespace std;
#define initsize 100
#define increment 20
typedef struct bitnode//二叉树结点 
{
	int data;
	struct bitnode *lchild,*rchild;
}bitnode,*bitree;

typedef struct qnode//队列 
{
	bitree data;
	struct qnode *next;
}qnode,*queueptr;

typedef struct
{
	queueptr front;
	queueptr rear;
}linkqueue;

typedef struct//栈 
{
	bitree *base;
	bitree *top;
	int stacksize;
}sqstack;

//初始化栈 
void initstack(sqstack &S)
{
	S.base=(bitree *)malloc(sizeof(bitree)*initsize);
	if(!S.base)
	exit(0);
	S.top=S.base;
	S.stacksize=initsize;
}

//退栈 
void pop(sqstack &S,bitree &e)
{
	if(S.top-S.base==0)
	exit(0);
	S.top--;
	e = *S.top;
}

//进栈 
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

//判空
bool emptystack(sqstack S)
{
	if(S.top-S.base)
	return false;
	else
	return true;
}

//销毁栈
void destroystack(sqstack &S)
{
	if(S.base)
	free(S.base);	
} 

//初始化队列 
void initqueue(linkqueue &Q)
{
	Q.front=(qnode *)malloc(sizeof(qnode));
	if(!Q.front)
	exit(0);
	Q.rear=Q.front;
	Q.front->next=NULL;
}

//进队列 
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

//出队列 
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

//判空队列 
bool emptyqueue(linkqueue Q)
{
	if(Q.front==Q.rear)
	return true;
	else
	return false;
}

//先序建立二叉树 
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

//先序递归遍历二叉树 
void preordertraverse(bitree T)
{
	if(T)
	{
		cout<<T->data<<" ";
		preordertraverse(T->lchild);
		preordertraverse(T->rchild);
	}
}

//中序递归遍历二叉树 
void inordertraverse(bitree T)
{
	if(T)
	{
		inordertraverse(T->lchild);
		cout<<T->data<<" ";
		inordertraverse(T->rchild);
	}	
}

//后续递归遍历二叉树 
void postordertraverse(bitree T)
{
	if(T)
	{
		postordertraverse(T->lchild);
		postordertraverse(T->rchild);
		cout<<T->data<<" "; 
	}
}

//层序遍历二叉树 
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

//先序非递归遍历二叉树 
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

//中序非递归遍历二叉树 
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

//后序非递归遍历二叉树 
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

//求深度 
int deepbitree(bitree T)
{
	if(!T)
		return 0;
	else
		return (max(deepbitree(T->lchild),deepbitree(T->rchild))+1);
} 


//求宽度 
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

//求结点数
int nodenum(bitree T)
{
	if(!T)
	return 0;
	else
	return nodenum(T->lchild)+nodenum(T->rchild)+1;
}


//销毁二叉树
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


//判断排序二叉树 
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
		cout<<"打开文件失败！"<<endl;
		exit(0); 
	}
	cout<<"二叉树1："<<endl;
	Createbitree(T,fp);
	fclose(fp);
	cout<<"先序递归遍历："<<endl;
	preordertraverse(T);
	cout<<endl<<endl;
	
	cout<<"先序非递归遍历："<<endl;
	_preordertraverse(T);
	cout<<endl<<endl;
	
	cout<<"中序递归遍历："<<endl;
	inordertraverse(T);
	cout<<endl<<endl;
	
	cout<<"中序非递归遍历："<<endl;
	_inordertraverse(T);
	cout<<endl<<endl;
	
	cout<<"后序递归遍历："<<endl;
	postordertraverse(T);
	cout<<endl<<endl;
	
	cout<<"后序非递归遍历："<<endl;
	_postordertraverse(T);
	cout<<endl<<endl;
	
	cout<<"层序遍历："<<endl;
	levelordertraverse(T);
	cout<<endl<<endl;
	
	cout<<"二叉树深度："<<endl;
	cout<<deepbitree(T)<<endl<<endl;
	
	cout<<"二叉树宽度："<<endl;
	cout<<widthbitree(T)<<endl<<endl;
	
	cout<<"二叉树结点数："<<endl;
	cout<<nodenum(T)<<endl<<endl;
	
	cout<<"是否为二叉排序树："<<endl;
	if(is_bstree(T))
	cout<<"是"<<endl<<endl;
	else
	cout<<"否"<<endl<<endl;
	
	 
	
	cout<<endl<<endl<<endl;
	fp=fopen("bitree1.txt","r");
	if(!fp)
	{
		cout<<"打开文件失败！"<<endl;
		exit(0); 
	}
	cout<<"二叉树2："<<endl;
	Createbitree(M,fp);
	fclose(fp);
	cout<<"先序递归遍历："<<endl;
	preordertraverse(M);
	cout<<endl<<endl;
	
	cout<<"先序非递归遍历："<<endl;
	_preordertraverse(M);
	cout<<endl<<endl;
	
	cout<<"中序递归遍历："<<endl;
	inordertraverse(M);
	cout<<endl<<endl;
	
	cout<<"中序非递归遍历："<<endl;
	_inordertraverse(M);
	cout<<endl<<endl;
	
	cout<<"后序递归遍历："<<endl;
	postordertraverse(M);
	cout<<endl<<endl;
	
	cout<<"后序非递归遍历："<<endl;
	_postordertraverse(M);
	cout<<endl<<endl;
	
	cout<<"层序遍历："<<endl;
	levelordertraverse(M);
	cout<<endl<<endl;
	
	cout<<"二叉树深度："<<endl;
	cout<<deepbitree(M)<<endl<<endl;
	
	cout<<"二叉树宽度："<<endl;
	cout<<widthbitree(M)<<endl<<endl;
	
	cout<<"二叉树结点数："<<endl;
	cout<<nodenum(M)<<endl<<endl;
	
	cout<<"是否为二叉排序树："<<endl;
	if(is_bstree(M))
	cout<<"是"<<endl<<endl;
	else
	cout<<"否"<<endl<<endl;
	
	destroybitree(T);
	destroybitree(M); 
}
