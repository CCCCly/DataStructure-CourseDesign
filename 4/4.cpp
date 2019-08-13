#include<iostream>
#include<string.h>
#include<stdlib.h>
#define increment 10
#include<iomanip> 
using namespace std;
#define initsize 100
#define increment 10
typedef struct
{
	int weight;
	int lchild;
	int rchild;
	int parent;
	bool flag;
	char name;
}hfmnode,*hfmtree;

typedef char** hfmcode;

typedef struct
{
	char *base;
	char *top;
	int stacksize;
}stack;

void initstack(stack &s)
{
	s.base=(char *)malloc(sizeof(char)*initsize);
	if(!s.base)
	exit(0);
	s.top=s.base;
	s.stacksize=initsize;
}

void push(stack &s,char e)
{
	if(s.top-s.base>=s.stacksize)
	{
		s.base=(char *)realloc(s.base,sizeof(char)*(increment+initsize));
		if(!s.base)
		exit(0);
		s.top=s.base+s.stacksize;
		s.stacksize+=initsize;
	}
	*s.top++=e;
	*s.top='\0';
}

void pop(stack &s,char &e)
{
	if(s.top==s.base)
	exit(0);
	e=*--s.top;
	*s.top='\0';
}

bool stackempty(stack s)
{
	if(s.base==s.top)
	return true;
	else
	return false;
}

void clearstack(stack &s)
{
	s.top=s.base;
	*s.top='\0';
}
void gettop(stack s,char &e)
{
	if(s.top==s.base)
	exit(0);
	e=*(s.top-1);
}
void readdata(hfmtree &t,int &n,int &size)
{
	FILE *fp;
	char ch;
	int i,flag;
	fp=fopen("novel.txt","r");
	if(!fp)
	{
		cout<<"can't open novel.txt!"<<endl;
		exit(0);
	}
	while(!feof(fp))
	{
		flag=0;
		fscanf(fp,"%c",&ch);
		for(i=1;i<=n;i++)
		if(t[i].name==ch)
		{
			t[i].weight++;
			flag=1;	
			break;
		}
		if(!flag)
		{
			if(n>=size-1)
			{
				t=(hfmnode *)realloc(t,sizeof(hfmnode)*(size+increment));
				if(!t)
					exit(0);
				size+=increment;
			}
			n++;
			t[n].name=ch;
			t[n].weight=1;
			t[n].lchild=0;
			t[n].rchild=0;
			t[n].parent=0;
			t[n].flag=0;
		}
	}
	t[0].weight=9999999;
	for(i=0;i<=n;i++)
		{
			t[n].lchild=0;
			t[n].rchild=0;
			t[n].parent=0;
			t[n].flag=0;
		}
	fclose(fp);
}

void show(hfmtree t,int n)
{
	int i;
	for(i=1;i<=2*n-1;i++)
	{
		cout<<i<<" ";
		cout<<t[i].name<<" ";
		cout<<t[i].weight<<" ";
		cout<<t[i].parent<<" ";
		cout<<t[i].lchild<<" ";
		cout<<t[i].rchild<<" ";
		cout<<t[i].flag<<endl;
	}
}

void createhfm(hfmtree &t,int n,int &size)
{
		int i,j;
		int min=0;
		while(2*n-1>=size-1)
			{
				t=(hfmnode *)realloc(t,sizeof(hfmnode)*(size+increment));
				if(!t)
					exit(0);
				size+=increment;
			}
		for(i=n+1;i<=2*n-1;i++)
		{
				t[i].name='\0';
				t[i].weight=0;
				t[i].lchild=0;
				t[i].rchild=0;
				t[i].parent=0;
				t[i].flag=0;
		}
		
		for(i=n+1;i<=2*n-1;i++)
		{
			min=0;
			t[i].weight=0;
			for(j=1;j<i;j++)
			if(!t[j].flag&&t[j].weight<t[min].weight)
				min=j;
			t[i].lchild=min;
			t[i].weight+=t[min].weight;
			t[min].parent=i;
			t[min].flag=1;
			min=0;
			for(j=1;j<i;j++)
			if(!t[j].flag&&t[j].weight<t[min].weight)
				min=j;
			t[i].rchild=min;
			t[i].weight+=t[min].weight;
			t[min].parent=i;
			t[min].flag=1;
		}
}

void hfmcoding(hfmcode &hc,hfmtree t,int n)
{
	int i,start;
	char *cd;
	hc=(hfmcode)malloc(sizeof(char *)*(n+1));
	if(!hc)
	exit(0);
	cd=(char *)malloc(sizeof(char)*(n));
	cd[n-1]='\0';
	
	for(i=1;i<=n;i++)
	{
		start=n-1;
		cd[start]='\0';
		for(int c=i,f=t[i].parent;f!=0;c=f,f=t[f].parent)
		if(t[f].lchild==c)
		cd[--start]='0';
		else
		cd[--start]='1';
		hc[i]=(char *)malloc(sizeof(char)*(n-start));
		strcpy(hc[i],&cd[start]);
	}
	free(cd);
}
void showcode(hfmcode hc,hfmtree t,int n)
{
	int i;
	for(i=1;i<=n;i++)
	{
		cout<<"字符："<<setw(2)<<t[i].name;
		cout<<" 出现次数："<<setw(5)<<t[i].weight<<"　";
		cout<<"编码："<<hc[i]<<endl;
	}
}

void bianmabiao(hfmcode hc,hfmtree t,int n)
{
	int i;
	FILE *fp;
	fp=fopen("bianmabiao.txt","w");
	if(!fp)
	{
		cout<<"can't open file."<<endl;
		exit(0);
	}
	for(i=1;i<=n;i++)
	{
		fprintf(fp,"%c ",t[i].name);
		fprintf(fp,"%s",hc[i]);
		fprintf(fp,"\n");
	}
	fclose(fp);
}
void translate(hfmcode hc,hfmtree t,int n)
{
	FILE *fp;
	stack s;
	char ch;
	int i;
	fp=fopen("code.txt","r");
	if(!fp)
	{
		cout<<"can't open file."<<endl;
		exit(0);
	}
	initstack(s);
	while(!feof(fp))
	{
		fscanf(fp,"%c",&ch);
		push(s,ch);
		for(i=1;i<=n;i++)
		if(!strcmp(s.base,hc[i]))
		{
			cout<<t[i].name;
			clearstack(s);
			break;
		}
	}
	fclose(fp);
	
}

void translatebit(hfmcode hc,hfmtree t,int n)
{
	FILE *fp;
	char m[8];
	stack s;
	int x;
	int i,j;
	int count;
	initstack(s);
	fp=fopen("bit.txt","r");
	if(!fp)
	{
		cout<<"can't open file."<<endl;
		exit(0);
	}
	cout<<"以下为文章内容："<<endl;
	while(!feof(fp))
	{
		fscanf(fp,"%d",&x);
		count=7;
		while(x)
		{
			m[count]=x%2+'0';
			count--;
			x/=2;
		}
		for(i=1;i<=count;i++)
			m[i]='0';
		for(i=1;i<=7;i++)
		{
			push(s,m[i]);
			for(j=1;j<=n;j++)
			{
				if(!strcmp(s.base,hc[j]))
				{
					cout<<t[j].name;
					clearstack(s);
					break;
				}
			}
		}
	}
}

void storebit(hfmcode hc,hfmtree t,int n)
{
	FILE *fp,*fs;
	int count;
	int num;
	char ch;
	char s[8];
	fp=fopen("bit.txt","w");
	if(!fp)
	{
		cout<<"can't open file."<<endl;
		exit(0);
	}
	fs=fopen("code.txt","r");
	if(!fs)
	{
		cout<<"can't open file."<<endl;
		exit(0);
	}
	
	count=0;
	while(!feof(fs))
	{
		fscanf(fs,"%c",&ch);
		s[count]=ch;
		count++;
		if(count>6)
		{
			count=0;
			num=(s[0]-'0')*64+(s[1]-'0')*32+(s[2]-'0')*16+(s[3]-'0')*8
			+(s[4]-'0')*4+(s[5]-'0')*2+(s[6]-'0')*1;
			fprintf(fp,"%d ",num);
		}
	}
	num=0;
	count--;
	if(count!=0&&count<=6)
	{
		int m=1;
		for(int i=0;i<count;i++)
		{
			num+=(s[count-i-1]-'0')*m;
			m*=2;
		}
		fprintf(fp,"%d",num);
	}
	fclose(fp);
	fclose(fs);
}

void storecode(hfmcode hc,hfmtree t,int n)
{
	int i,j;
	int num;
	int length;
	int k;
	char ch;
	FILE *fp,*fs;
	fp=fopen("code.txt","w");
	if(!fp)
	{
		cout<<"can't open file."<<endl;
		exit(0);
	}
	fs=fopen("novel.txt","r");
	if(!fs)
	{
		cout<<"can't open file."<<endl;
		exit(0);
	}
	while(!feof(fs))
	{
		fscanf(fs,"%c",&ch);
		for(i=1;i<=n;i++)
		if(t[i].name==ch)
		{
			fprintf(fp,"%s",hc[i]);
			break;
		}
	}
	fclose(fs);
	fclose(fp);
}

int main()
{
	int n=0;
	int size=100;
	hfmcode hc;
	hfmtree t;
	hfmcode wei;
	t=(hfmnode *)malloc(sizeof(hfmnode)*size);
	if(!t)
	exit(0);
	readdata(t,n,size);//读取数据 
	createhfm(t,n,size);//建立hfm树 
	//show(t,n); 
	hfmcoding(hc,t,n);
	showcode(hc,t,n);
	bianmabiao(hc,t,n);
	storecode(hc,t,n);
	//translate(hc,t,n);
	storebit(hc,t,n);
	translatebit(hc,t,n);
	free(t);
	for(int i=1;i<=n;i++)
	free(hc[i]);
}
