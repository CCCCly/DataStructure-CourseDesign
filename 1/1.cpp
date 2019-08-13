#include<iostream>
#include<iomanip>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
using namespace std;

typedef struct object //商品 
{
	char oname[20];//商品名称 
	float price;//价格 
	int sale;//销量 
}object;


typedef struct shop //商铺 
{
	int data;//编号
	char name[20];//商铺名称 
	int credit;//信誉
	int num;//商品数量
	object shangpin[50];//商品
	shop *next;
}shop,*sptr;


typedef struct node//所查找商品信息 
{
	int data;//编号 
	char name[20];//商铺名称 
	int credit;//信誉 
	char oname[20];//商品名称 
	float price;//价格 
	int sale;//销量 
	node *prior;
	node *next;
}node,*linklist;


void destroyshop(sptr &s)//销毁链表 
{
	sptr p=s->next;
	while(p)
	{
		s->next=p->next;
		free(p);
		p=s->next;
	}
	free(s);
} 


void initshop(sptr &s)
{
	s=(shop *)malloc(sizeof(shop));
	if(!s)
	{
		cout<<"error!"<<endl;
		exit(0);
	}
	s->next=NULL;
}


void createshop(sptr &s)//建立一个单向链表存储所有商铺信息
{
	FILE *fp;
	sptr p,q;
	p=s;
	fp=fopen("shangpu.txt","r");
	if(!fp)
	cout<<"打开文件失败。"<<endl;
	
	while(!feof(fp))
	{
		q=(shop *)malloc(sizeof(shop));
		if(!q)
		{
			cout<<"error!"<<endl;
			exit(0);
		}
		fscanf(fp,"%d",&q->data);
		fscanf(fp,"%s",&q->name);
		fscanf(fp,"%d",&q->credit);
		fscanf(fp,"%d",&q->num);
	
		for(int i=0;i<q->num;i++)
		{
			fscanf(fp,"%s",&q->shangpin[i].oname);
			fscanf(fp,"%f",&q->shangpin[i].price);
			fscanf(fp,"%d",&q->shangpin[i].sale);
		}
		q->next=NULL;
		p->next=q;
		p=q;
	}
	fclose(fp); 
}


void show(sptr s)//显示所有商品 
{
	cout<<endl<<"*                     欢迎来到商品显示功能~                     *"<<endl;
	sptr p;
	p=s->next;
	while(p)
	{
		cout<<"商铺编号："<<setw(5)<<p->data<<" ";
		cout<<"商铺名："<<setw(10)<<p->name<<" ";
		cout<<"信誉："<<p->credit<<endl;
		cout<<"共有商品"<<p->num<<"件:"<<endl;
		for(int i=0;i<p->num;i++)
		{
			cout<<"名称："<<setw(10)<<p->shangpin[i].oname<<" ";
			cout<<"价格："<<setw(10)<<p->shangpin[i].price<<" ";
			cout<<"销量："<<p->shangpin[i].sale<<endl;
		}
		cout<<endl;
		p=p->next;
	}
	
	cout<<endl<<"*                     已显示所有商品！                     *"<<endl; 
}


void rewrite(sptr s)//将更改信息写入文件 
{
	FILE *fp;
	fp=fopen("shangpu.txt","w");
	sptr p;
	p=s->next;
	fprintf(fp,"%d ",p->data);
	fprintf(fp,"%s ",p->name); 
	fprintf(fp,"%d ",p->credit);
	fprintf(fp,"%d ",p->num);
		for(int i=0;i<p->num;i++)
			{
				fprintf(fp,"%s ",p->shangpin[i].oname);
				fprintf(fp,"%f ",p->shangpin[i].price);
				fprintf(fp,"%d",p->shangpin[i].sale);			
			}
	p=p->next;
	while(p)
	{
		fprintf(fp,"\n");
		fprintf(fp,"%d ",p->data);
		fprintf(fp,"%s ",p->name); 
		fprintf(fp,"%d ",p->credit);
		fprintf(fp,"%d ",p->num);
		for(int i=0;i<p->num;i++)
			{
				fprintf(fp,"%s ",p->shangpin[i].oname);
				fprintf(fp,"%f ",p->shangpin[i].price);
				fprintf(fp,"%d",p->shangpin[i].sale);			
			}
		p=p->next;
	}
	fclose(fp);
}


void addshop(sptr &s)//增加商铺，编号自动加一，插入链表尾部
{
	cout<<endl<<"*                     欢迎来到增加商铺功能~                     *"<<endl; 
	sptr p,q;
	p=s;
	while(p->next)
	p=p->next;
	q=(shop *)malloc(sizeof(shop));
	if(!q)
	{
		cout<<"error!"<<endl;
		exit(0);
	}
	q->data=p->data+1;
	cout<<"商铺名称：";
	cin>>q->name; 
	cout<<"信誉：";
	cin>>q->credit;
	cout<<"商品件数：";
	cin>>q->num;
	 for(int i=0;i<q->num;i++)
		{
			cout<<"名称：";
			cin>>q->shangpin[i].oname;
			cout<<"价格：";
			cin>>q->shangpin[i].price;
			cout<<"销量：";
			cin>>q->shangpin[i].sale;
		}
	q->next=NULL;
	p->next=q;
	rewrite(s);
	cout<<endl<<"*                     已成功添加该商铺！                     *"<<endl;
}


void delshop(sptr &s)//删除商铺以编号为准，并修改后续结点的编号，保持编号连续性。 
{
	int k;
	int flag=0;
	sptr p,q;
	p=s;
	q=s->next;
	cout<<endl<<"*                     欢迎来到删除商铺功能~                     *"<<endl;
	cout<<"请输入要删除的商铺编号："<<endl;
	cin>>k;
	while(q)
	{
		if(flag)
			q->data--;
		if(!flag&&q->data==k)
		{
			flag=1;
			p->next=q->next;
			free(q);
			q=p->next;
		}
		else
		{
			p=q;
			q=q->next;
		}		
	}
	rewrite(s);
	cout<<endl<<"*                     已成功删除该商铺！                     *"<<endl;
}

void addobj(sptr &s) //增加选定商铺中的商品
{
	int k;
	int add; 
	sptr p;
	cout<<endl<<"*                     欢迎来到增加商品功能~                     *"<<endl;
	cout<<"请输入商铺编号："<<endl;
	cin>>k;
	p=s->next;
	while(p)
	{
		if(p->data==k)
		{
			cout<<"请输入要增加的商品个数："<<endl;
			cin>>add;
			for(int i=0;i<add;i++)
			{
				cout<<"商品名称："<<endl;
				cin>>p->shangpin[p->num+i].oname;
				cout<<"价格："<<endl;
				cin>>p->shangpin[p->num+i].price;
				cout<<"销量："<<endl;
				cin>>p->shangpin[p->num+i].sale;
			}
			cout<<endl<<"*                     已成功增加商品！                     *"<<endl;
			p->num+=add;
			break;
		}	
		p=p->next;
	}
	rewrite(s);
}
void delobj(sptr &s)//删除选定商铺中的商品
{
	int k;
	int del; 
	sptr p;
	cout<<endl<<"*                     欢迎来到删除商品功能~                     *"<<endl;
	cout<<"请输入商铺编号："<<endl;
	cin>>k;
	p=s->next;
	while(p)
	{
		if(p->data==k)
		{
			for(int i=0;i<p->num;i++)
			{
				cout<<"编号："<<i+1<<endl;
				cout<<"名称："<<setw(10)<<p->shangpin[i].oname<<" ";
				cout<<"价格："<<setw(10)<<p->shangpin[i].price<<" ";
				cout<<"销量："<<p->shangpin[i].sale<<endl;
			}
			cout<<"请输入要删除的商品编号："<<endl;
			cin>>del;
			if(del>=1&&del<=p->num)
			{
				for(int i=del-1;i<p->num-1;i++)
					p->shangpin[i]=p->shangpin[i+1];			
				p->num--;
			}
			else
			{
				cout<<"输入编号无效！"<<endl;
				exit(0); 
			} 
			break;
		}
		p=p->next;	
	}
	cout<<endl<<"*                     已成功删除该商品！                     *"<<endl;
	rewrite(s);
} 

void changeprice(sptr &s)//修改商品价格
{
	int k; 
	int change; 
	sptr p;
	cout<<endl<<"*                     欢迎来到修改价格功能~                     *"<<endl;
	cout<<"请输入商铺编号："<<endl;
	cin>>k;
	p=s->next;
	while(p)
	{
		if(p->data==k)
		{
			for(int i=0;i<p->num;i++)
			{
				cout<<"编号："<<i+1<<endl;
				cout<<"名称："<<setw(10)<<p->shangpin[i].oname<<" ";
				cout<<"价格："<<setw(10)<<p->shangpin[i].price<<" ";
				cout<<"销量："<<p->shangpin[i].sale<<endl;
			}
			cout<<"请输入要修改的商品编号："<<endl;
			cin>>change;
			if(change>=1&&change<=p->num)
			{ 
				cout<<"请输入新的价格："<<endl;
				cin>>p->shangpin[change-1].price;
			}
			else
			{
				cout<<"输入编号无效！"<<endl;
				exit(0);
			}
			break;
		}
		p=p->next;	
	}
	cout<<endl<<"*                     已更改商品价格！                     *"<<endl;
	rewrite(s);
} 

void search(sptr s)//查询某一种商品名称，建立一个双向循环链表，按销量高至低排序，并可逐一显示。
{
	char obj[20];
	sptr p;
	linklist l;
	node *q,*m;
	l=(node *)malloc(sizeof(node));
	if(!l)
	{
		cout<<"error!"<<endl;
		exit(0);
	}
	l->next=NULL;
	l->prior=NULL;
	cout<<endl<<"*                     欢迎来到查找商品功能~                     *"<<endl;
	cout<<"请输入要查找的商品名称："<<endl;
	cin>>obj;
	p=s->next;
	while(p)
	{
		for(int i=0;i<p->num;i++)
		{
			if(!strcmp(obj,p->shangpin[i].oname))
			{
				q=(node *)malloc(sizeof(node));
				if(!q)
				{
					cout<<"error!"<<endl;
					exit(0);
				}
				q->data=p->data;
				strcpy(q->name,p->name);
				q->credit=p->credit;
				strcpy(q->oname,p->shangpin[i].oname);
				q->price=p->shangpin[i].price;
				q->sale=p->shangpin[i].sale;
				q->next=NULL;
				q->prior=NULL; 
				
				m=l;
				
					while(m->next&&m->next->sale >= q->sale)
						m=m->next;
					if(m->next)
					{
						q->next=m->next;
						q->prior=m;
						m->next=q;
						q->next->prior=q; 
					}
					else
					{
						m->next=q;
						q->prior=m;
						q->next=NULL;
					}
			}		
		}
		p=p->next;
	}
	q=l->next;
		while(q->next) //循环链表 
			q=q->next;
		q->next=l->next;
		l->next->prior=q;
		
		q=l->next;
		cout<<"商铺编号："<<setw(5)<<q->data<<" ";
		cout<<"商铺名："<<setw(10)<<q->name<<" ";
			cout<<"信誉："<<q->credit<<endl;

			cout<<"名称："<<setw(10)<<q->oname<<" ";
			cout<<"价格："<<setw(10)<<q->price<<" ";
			cout<<"销量："<<q->sale<<endl;
		cout<<endl;		
		q=q->next;
	while(q!=l->next)
	{
		cout<<"商铺编号："<<setw(5)<<q->data<<" ";
		cout<<"商铺名："<<setw(10)<<q->name<<" ";
		cout<<"信誉："<<q->credit<<endl;

			cout<<"名称："<<setw(10)<<q->oname<<" ";
			cout<<"价格："<<setw(10)<<q->price<<" ";
			cout<<"销量："<<q->sale<<endl;
		cout<<endl;		
		q=q->next;
	}
	
	q=l->next;
	q->prior->next=NULL;
	while(q)
	{
		l->next=q->next;
		free(q);
		q=l->next;
	}
	free(l);
	cout<<endl<<"*                     已查找所有该商品信息！                     *"<<endl;
}

void buyobj(sptr &s)//购买某一商铺的商品，修改单向链表中商品的信息的销量。
{
	int k;
	int buy;
	sptr p;
	cout<<endl<<"*                     欢迎来到购买商品功能~                     *"<<endl;
	cout<<"请输入要购买商品的商铺编号："<<endl;
	cin>>k;
	p=s->next;
	while(p)
	{
		if(k==p->data)
		{
			for(int i=0;i<p->num;i++)
			{
				cout<<"编号："<<i+1<<endl;
				cout<<"名称："<<setw(10)<<p->shangpin[i].oname<<" ";
				cout<<"价格："<<setw(10)<<p->shangpin[i].price<<" ";
				cout<<"销量："<<p->shangpin[i].sale<<endl;
			}
			cout<<"请输入要购买的商品编号："<<endl;
			cin>>buy;
			if(buy<=p->num&&buy>=1)
				p->shangpin[buy-1].sale++;
			else
			{
				cout<<"输入编号无效！"<<endl;
				exit(0);
			}
			break;
		}
		p=p->next;
	}
	cout<<endl<<"*                     已成功购买该商品！                     *"<<endl;
}
int main()
{
	sptr s;
	initshop(s);
	createshop(s);
	char ch='1';
	while(ch!='#')
	 {
		printf("********************************************************************\n");
		printf("*                                                                  *\n");
		printf("*                       欢迎来到淘啊淘                             *\n");
		printf("*                                                                  *\n");
		printf("*                                                                  *\n");
		printf("*             1 商品显示                                           *\n");
		printf("*                                                                  *\n");
		printf("*             2 增加商铺                                           *\n");
		printf("*                                                                  *\n");
		printf("*             3 删除商铺                                           *\n");
		printf("*                                                                  *\n");
		printf("*             4 增加商品                                           *\n");
		printf("*                                                                  *\n");
		printf("*             5 删除商品                                           *\n");
		printf("*                                                                  *\n");
		printf("*             6 修改价格                                           *\n");
		printf("*                                                                  *\n");
		printf("*             7 销量排序                                           *\n");
		printf("*                                                                  *\n");
		printf("*             8 购买商品                                           *\n");
		printf("*                                                                  *\n");
		printf("*                                                                  *\n");
		printf("***************输入选择(按#退出喔，谢谢来到淘啊淘)******************\n"); 	
	 	cin>>ch;
	 	if(ch=='1')
	 	show(s);
	 	else if(ch=='2')
	 	addshop(s);
	 	else if(ch=='3')
	 	delshop(s);
	 	else if(ch=='4')
	 	addobj(s);
	 	else if(ch=='5')
	 	delobj(s);
	 	else if(ch=='6')
	 	changeprice(s);
	 	else if(ch=='7')
	 	search(s);
	 	else if(ch=='8')
	 	buyobj(s);
	 	system("pause");
	}
} 
