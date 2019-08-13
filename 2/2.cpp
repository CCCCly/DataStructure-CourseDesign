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
									//只有路径所在位置的数字为0的是可以走的 
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
          //东 
          case 1:
			  {
	              next.x=x;
	              next.y=y+1;
	              break;
		      }
          //南 
         case 2:
			 {
	             next.x=x+1;
	             next.y=y; 
	             break;
             }
         //西
         case 3:
			 {
	             next.x=x;
	             next.y=y-1;
	             break;
             }
         //北
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
		cout<<"第"<<m->ord<<"步:";
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
	int curstep=1;//被探索的步数
    stack path;//记录路径的栈
    initstack(path);//初始化路径数组
    position curp;//当前被试位置
					//初始化当前位置为矩阵入口
	cout<<"请输入入口坐标："<<endl; 
	cin>>startx>>starty;
    curp.x=startx;
    curp.y=starty;
    cout<<"请输入出口坐标："<<endl; 
	cin>>endx>>endy;
    do
    {
        if(pass(curp,a))
        {
			footprint(curp,curstep,a);//可走就在迷宫里面留下足迹 
            e.di=1;//意味着下一个被试路块为这一个路块东面
            e.ord=curstep;
            e.p.x=curp.x;
            e.p.y=curp.y;
            push(path,e);							//将路径入栈
            if(curp.x==endx && curp.y==endy)
			{
				cout<<"成功走出迷宫!"<<endl;
				break;
			}									//如果路径块到了迷宫的终点就退出循环
            //找到下一个被试块
            curp=nextposition(curp,1);				//找到前一个被试块东面的路径块作为被试块
            curstep++;						//步数加一 
        }
		else//如果当前被试路径不能够通过的话 
        {
            if(!stackempty(path))
            {
                pop(path,e);
                curstep--;//将这一段所有的周围路径都已经被测试过的路径从栈中清除 
                while(e.di==4 &&!stackempty(path))
				{
					markprint(e.p,a); //留下不能通过的标记 
                    pop(path,e);
                    curstep--;
                }//如果当前栈顶还有未被测试的路径就测试剩余的周围路径 
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
		cout<<"此迷宫没有出路！"<<endl;
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
	cout<<"迷宫："<<endl;
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
