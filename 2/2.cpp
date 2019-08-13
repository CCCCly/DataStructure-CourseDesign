#include<iostream>
#include<stdlib.h>
#include<iomanip>
using namespace std;
#define initsize 100
#define increment 10
typedef struct
{
	int x;
	int y;
}position;
typedef struct
{
	int ord;
	position p;
	int di;
}selement;
typedef struct
{
	selement *base;
	selement *top;
	int stacksize;
}stack;

void initstack(stack &s)
{
	s.base=(selement *)malloc(sizeof(selement)*initsize);
	if(!s.base)
	exit(0);
	s.top=s.base;
	s.stacksize=initsize;
}

void destroystack(stack &s)
{
	if(!s.base)
	return;
	free(s.base);
}
void push(stack &s,selement e)
{
	if(s.top-s.base>=s.stacksize)
	{
		s.base=(selement *)realloc(s.base,sizeof(selement)*(increment+initsize));
		if(!s.base)
		exit(0);
		s.top=s.base+s.stacksize;
		s.stacksize+=initsize;
	}
	*s.top++=e;
}

void pop(stack &s,selement &e)
{
	if(s.top==s.base)
	exit(0);
	e=*--s.top;
}

bool stackempty(stack s)
{
	if(s.base==s.top)
	return true;
	else
	return false;
}

void gettop(stack s,selement &e)
{
	if(s.top==s.base)
	exit(0);
	e=*(s.top-1);
}

bool pass(position posi,int a[10][10])
{
									//ֻ��·������λ�õ�����Ϊ0���ǿ����ߵ� 
      if(a[posi.x][posi.y]==0)
      {
          return true;
      }

      return false; 
}

position nextposition(position now,int direction)
{
      position next;

      int x;
      int y;
	  x=now.x;
	  y=now.y;

      switch(direction)
      {
          //�� 
          case 1:
			  {
	              next.x=x;
	              next.y=y+1;
	              break;
		      }
          //�� 
         case 2:
			 {
	             next.x=x+1;
	             next.y=y; 
	             break;
             }
         //��
         case 3:
			 {
	             next.x=x;
	             next.y=y-1;
	             break;
             }
         //��
         case 4:
			 {
	             next.x=x-1;
	             next.y=y;
	             break;
             } 
         default:
			 break;
     }

     return next;
}

void footprint(position p,int step,int a[10][10])
{
    a[p.x][p.y]=step;
}

void markprint(position p,int a[10][10])
{
    a[p.x][p.y]=-1;
}

void printmaze(int a[10][10])
{
	int i;
	int j;
	for(i=0;i<10;i++)
	{
		for(j=0;j<10;j++)
		{
			if(a[i][j]!=-1)
			cout<<setw(4)<<a[i][j];
			else
			cout<<setw(4)<<"0";
		}
		cout<<endl;
	}
}

void printstep(stack path)
{
	selement *m=path.base;
	while(m!=path.top)
	{
		cout<<"��"<<m->ord<<"��:";
		cout<<"("<<m->p.x<<","<<m->p.y<<")"<<endl;
		m++;
	}
}
void escape(int a[10][10])
{
	int i;
	int j;
	int startx,starty;
	int endx,endy; 
	selement e;
	int curstep=1;//��̽���Ĳ���
    stack path;//��¼·����ջ
    initstack(path);//��ʼ��·������
    position curp;//��ǰ����λ��
					//��ʼ����ǰλ��Ϊ�������
	cout<<"������������꣺"<<endl; 
	cin>>startx>>starty;
    curp.x=startx;
    curp.y=starty;
    cout<<"������������꣺"<<endl; 
	cin>>endx>>endy;
    do
    {
        if(pass(curp,a))
        {
			footprint(curp,curstep,a);//���߾����Թ����������㼣 
            e.di=1;//��ζ����һ������·��Ϊ��һ��·�鶫��
            e.ord=curstep;
            e.p.x=curp.x;
            e.p.y=curp.y;
            push(path,e);							//��·����ջ
            if(curp.x==endx && curp.y==endy)
			{
				cout<<"�ɹ��߳��Թ�!"<<endl;
				break;
			}									//���·���鵽���Թ����յ���˳�ѭ��
            //�ҵ���һ�����Կ�
            curp=nextposition(curp,1);				//�ҵ�ǰһ�����Կ鶫���·������Ϊ���Կ�
            curstep++;						//������һ 
        }
		else//�����ǰ����·�����ܹ�ͨ���Ļ� 
        {
            if(!stackempty(path))
            {
                pop(path,e);
                curstep--;//����һ�����е���Χ·�����Ѿ������Թ���·����ջ����� 
                while(e.di==4 &&!stackempty(path))
				{
					markprint(e.p,a); //���²���ͨ���ı�� 
                    pop(path,e);
                    curstep--;
                }//�����ǰջ������δ�����Ե�·���Ͳ���ʣ�����Χ·�� 
                if(e.di<4)
                {
					e.di++;
                    curp=nextposition(e.p,e.di);
                    curstep++;
                    push(path,e);
                }
            }
       }
    }while(!stackempty(path));

	if(stackempty(path))
	{
		cout<<"���Թ�û�г�·��"<<endl;
		return;
	}
	printstep(path);
	printmaze(a);
	destroystack(path);
}
void readfile(int a[10][10])
{
	FILE *fp;
	int i,j;
	fp=fopen("maze.txt","r");
	if(!fp)
	{
		cout<<"can't open file."<<endl;
		exit(0);
	}
	for(i=0;i<10;i++)
		for(j=0;j<10;j++)
		fscanf(fp,"%d",&a[i][j]);
	fclose(fp);
	cout<<"�Թ���"<<endl;
	for(i=0;i<10;i++)
	{
		for(j=0;j<10;j++)
			cout<<setw(4)<<a[i][j];
			cout<<endl;
	}
}

int main()
{
	int a[10][10];
	readfile(a);
	escape(a);
}
