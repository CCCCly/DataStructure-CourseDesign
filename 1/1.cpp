#include<iostream>
#include<iomanip>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
using namespace std;

typedef struct object //��Ʒ 
{
	char oname[20];//��Ʒ���� 
	float price;//�۸� 
	int sale;//���� 
}object;


typedef struct shop //���� 
{
	int data;//���
	char name[20];//�������� 
	int credit;//����
	int num;//��Ʒ����
	object shangpin[50];//��Ʒ
	shop *next;
}shop,*sptr;


typedef struct node//��������Ʒ��Ϣ 
{
	int data;//��� 
	char name[20];//�������� 
	int credit;//���� 
	char oname[20];//��Ʒ���� 
	float price;//�۸� 
	int sale;//���� 
	node *prior;
	node *next;
}node,*linklist;


void destroyshop(sptr &s)//�������� 
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


void createshop(sptr &s)//����һ����������洢����������Ϣ
{
	FILE *fp;
	sptr p,q;
	p=s;
	fp=fopen("shangpu.txt","r");
	if(!fp)
	cout<<"���ļ�ʧ�ܡ�"<<endl;
	
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


void show(sptr s)//��ʾ������Ʒ 
{
	cout<<endl<<"*                     ��ӭ������Ʒ��ʾ����~                     *"<<endl;
	sptr p;
	p=s->next;
	while(p)
	{
		cout<<"���̱�ţ�"<<setw(5)<<p->data<<" ";
		cout<<"��������"<<setw(10)<<p->name<<" ";
		cout<<"������"<<p->credit<<endl;
		cout<<"������Ʒ"<<p->num<<"��:"<<endl;
		for(int i=0;i<p->num;i++)
		{
			cout<<"���ƣ�"<<setw(10)<<p->shangpin[i].oname<<" ";
			cout<<"�۸�"<<setw(10)<<p->shangpin[i].price<<" ";
			cout<<"������"<<p->shangpin[i].sale<<endl;
		}
		cout<<endl;
		p=p->next;
	}
	
	cout<<endl<<"*                     ����ʾ������Ʒ��                     *"<<endl; 
}


void rewrite(sptr s)//��������Ϣд���ļ� 
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


void addshop(sptr &s)//�������̣�����Զ���һ����������β��
{
	cout<<endl<<"*                     ��ӭ�����������̹���~                     *"<<endl; 
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
	cout<<"�������ƣ�";
	cin>>q->name; 
	cout<<"������";
	cin>>q->credit;
	cout<<"��Ʒ������";
	cin>>q->num;
	 for(int i=0;i<q->num;i++)
		{
			cout<<"���ƣ�";
			cin>>q->shangpin[i].oname;
			cout<<"�۸�";
			cin>>q->shangpin[i].price;
			cout<<"������";
			cin>>q->shangpin[i].sale;
		}
	q->next=NULL;
	p->next=q;
	rewrite(s);
	cout<<endl<<"*                     �ѳɹ���Ӹ����̣�                     *"<<endl;
}


void delshop(sptr &s)//ɾ�������Ա��Ϊ׼�����޸ĺ������ı�ţ����ֱ�������ԡ� 
{
	int k;
	int flag=0;
	sptr p,q;
	p=s;
	q=s->next;
	cout<<endl<<"*                     ��ӭ����ɾ�����̹���~                     *"<<endl;
	cout<<"������Ҫɾ�������̱�ţ�"<<endl;
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
	cout<<endl<<"*                     �ѳɹ�ɾ�������̣�                     *"<<endl;
}

void addobj(sptr &s) //����ѡ�������е���Ʒ
{
	int k;
	int add; 
	sptr p;
	cout<<endl<<"*                     ��ӭ����������Ʒ����~                     *"<<endl;
	cout<<"���������̱�ţ�"<<endl;
	cin>>k;
	p=s->next;
	while(p)
	{
		if(p->data==k)
		{
			cout<<"������Ҫ���ӵ���Ʒ������"<<endl;
			cin>>add;
			for(int i=0;i<add;i++)
			{
				cout<<"��Ʒ���ƣ�"<<endl;
				cin>>p->shangpin[p->num+i].oname;
				cout<<"�۸�"<<endl;
				cin>>p->shangpin[p->num+i].price;
				cout<<"������"<<endl;
				cin>>p->shangpin[p->num+i].sale;
			}
			cout<<endl<<"*                     �ѳɹ�������Ʒ��                     *"<<endl;
			p->num+=add;
			break;
		}	
		p=p->next;
	}
	rewrite(s);
}
void delobj(sptr &s)//ɾ��ѡ�������е���Ʒ
{
	int k;
	int del; 
	sptr p;
	cout<<endl<<"*                     ��ӭ����ɾ����Ʒ����~                     *"<<endl;
	cout<<"���������̱�ţ�"<<endl;
	cin>>k;
	p=s->next;
	while(p)
	{
		if(p->data==k)
		{
			for(int i=0;i<p->num;i++)
			{
				cout<<"��ţ�"<<i+1<<endl;
				cout<<"���ƣ�"<<setw(10)<<p->shangpin[i].oname<<" ";
				cout<<"�۸�"<<setw(10)<<p->shangpin[i].price<<" ";
				cout<<"������"<<p->shangpin[i].sale<<endl;
			}
			cout<<"������Ҫɾ������Ʒ��ţ�"<<endl;
			cin>>del;
			if(del>=1&&del<=p->num)
			{
				for(int i=del-1;i<p->num-1;i++)
					p->shangpin[i]=p->shangpin[i+1];			
				p->num--;
			}
			else
			{
				cout<<"��������Ч��"<<endl;
				exit(0); 
			} 
			break;
		}
		p=p->next;	
	}
	cout<<endl<<"*                     �ѳɹ�ɾ������Ʒ��                     *"<<endl;
	rewrite(s);
} 

void changeprice(sptr &s)//�޸���Ʒ�۸�
{
	int k; 
	int change; 
	sptr p;
	cout<<endl<<"*                     ��ӭ�����޸ļ۸���~                     *"<<endl;
	cout<<"���������̱�ţ�"<<endl;
	cin>>k;
	p=s->next;
	while(p)
	{
		if(p->data==k)
		{
			for(int i=0;i<p->num;i++)
			{
				cout<<"��ţ�"<<i+1<<endl;
				cout<<"���ƣ�"<<setw(10)<<p->shangpin[i].oname<<" ";
				cout<<"�۸�"<<setw(10)<<p->shangpin[i].price<<" ";
				cout<<"������"<<p->shangpin[i].sale<<endl;
			}
			cout<<"������Ҫ�޸ĵ���Ʒ��ţ�"<<endl;
			cin>>change;
			if(change>=1&&change<=p->num)
			{ 
				cout<<"�������µļ۸�"<<endl;
				cin>>p->shangpin[change-1].price;
			}
			else
			{
				cout<<"��������Ч��"<<endl;
				exit(0);
			}
			break;
		}
		p=p->next;	
	}
	cout<<endl<<"*                     �Ѹ�����Ʒ�۸�                     *"<<endl;
	rewrite(s);
} 

void search(sptr s)//��ѯĳһ����Ʒ���ƣ�����һ��˫��ѭ���������������������򣬲�����һ��ʾ��
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
	cout<<endl<<"*                     ��ӭ����������Ʒ����~                     *"<<endl;
	cout<<"������Ҫ���ҵ���Ʒ���ƣ�"<<endl;
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
		while(q->next) //ѭ������ 
			q=q->next;
		q->next=l->next;
		l->next->prior=q;
		
		q=l->next;
		cout<<"���̱�ţ�"<<setw(5)<<q->data<<" ";
		cout<<"��������"<<setw(10)<<q->name<<" ";
			cout<<"������"<<q->credit<<endl;

			cout<<"���ƣ�"<<setw(10)<<q->oname<<" ";
			cout<<"�۸�"<<setw(10)<<q->price<<" ";
			cout<<"������"<<q->sale<<endl;
		cout<<endl;		
		q=q->next;
	while(q!=l->next)
	{
		cout<<"���̱�ţ�"<<setw(5)<<q->data<<" ";
		cout<<"��������"<<setw(10)<<q->name<<" ";
		cout<<"������"<<q->credit<<endl;

			cout<<"���ƣ�"<<setw(10)<<q->oname<<" ";
			cout<<"�۸�"<<setw(10)<<q->price<<" ";
			cout<<"������"<<q->sale<<endl;
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
	cout<<endl<<"*                     �Ѳ������и���Ʒ��Ϣ��                     *"<<endl;
}

void buyobj(sptr &s)//����ĳһ���̵���Ʒ���޸ĵ�����������Ʒ����Ϣ��������
{
	int k;
	int buy;
	sptr p;
	cout<<endl<<"*                     ��ӭ����������Ʒ����~                     *"<<endl;
	cout<<"������Ҫ������Ʒ�����̱�ţ�"<<endl;
	cin>>k;
	p=s->next;
	while(p)
	{
		if(k==p->data)
		{
			for(int i=0;i<p->num;i++)
			{
				cout<<"��ţ�"<<i+1<<endl;
				cout<<"���ƣ�"<<setw(10)<<p->shangpin[i].oname<<" ";
				cout<<"�۸�"<<setw(10)<<p->shangpin[i].price<<" ";
				cout<<"������"<<p->shangpin[i].sale<<endl;
			}
			cout<<"������Ҫ�������Ʒ��ţ�"<<endl;
			cin>>buy;
			if(buy<=p->num&&buy>=1)
				p->shangpin[buy-1].sale++;
			else
			{
				cout<<"��������Ч��"<<endl;
				exit(0);
			}
			break;
		}
		p=p->next;
	}
	cout<<endl<<"*                     �ѳɹ��������Ʒ��                     *"<<endl;
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
		printf("*                       ��ӭ�����԰���                             *\n");
		printf("*                                                                  *\n");
		printf("*                                                                  *\n");
		printf("*             1 ��Ʒ��ʾ                                           *\n");
		printf("*                                                                  *\n");
		printf("*             2 ��������                                           *\n");
		printf("*                                                                  *\n");
		printf("*             3 ɾ������                                           *\n");
		printf("*                                                                  *\n");
		printf("*             4 ������Ʒ                                           *\n");
		printf("*                                                                  *\n");
		printf("*             5 ɾ����Ʒ                                           *\n");
		printf("*                                                                  *\n");
		printf("*             6 �޸ļ۸�                                           *\n");
		printf("*                                                                  *\n");
		printf("*             7 ��������                                           *\n");
		printf("*                                                                  *\n");
		printf("*             8 ������Ʒ                                           *\n");
		printf("*                                                                  *\n");
		printf("*                                                                  *\n");
		printf("***************����ѡ��(��#�˳�ร�лл�����԰���)******************\n"); 	
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
