#include<iostream>
#include<stdlib.h>
#include<iomanip>
#include<math.h>
using namespace std;
#define MAX_VERTEX_NUM 20
#define MAXQSIZE  100
#define max_weight 1000
typedef struct 
{
	int num;//��� 
	int x;
	int y;//���� 
	int linked;//���۵��Ƿ��ͨ 
}point;

typedef  struct
{
	point vexs[MAX_VERTEX_NUM];//��һ�����ǻ�۵� 
	int arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];//1ͨ0��ͨ 
	float weight1[MAX_VERTEX_NUM][MAX_VERTEX_NUM];//���룬-1��ͨ
	int weight2[MAX_VERTEX_NUM][MAX_VERTEX_NUM];//�����ƽ����-1��ͨ
	int vexnum;
}MGraph;

void  creategraph(MGraph  &G)
{
	int   n,i,j;
	FILE *fp;
	fp=fopen("dian.txt","r");
	if(!fp)
	{
		cout<<"can't open file"<<endl;
		exit(0);
	} 
	cout<<"��������ĸ�����"<<endl;
	cin>>n; 
	G.vexnum=n+1;
	G.vexs[0].num=0;//��ʼ����۵� 
	G.vexs[0].x=0;
	G.vexs[0].y=0;
	for(i=1;i<=n;i++)
	{
		fscanf(fp,"%d",&G.vexs[i].num);
		fscanf(fp,"%d",&G.vexs[i].x);
		fscanf(fp,"%d",&G.vexs[i].y); 
	} 
	
	for(i=0;i<G.vexnum;i++)
		G.vexs[i].linked=0;
		
	for(i=0;i<G.vexnum;i++)
		for(j=0;j<G.vexnum;j++)
			G.arcs[i][j]=0;
			
	for(i=0;i<G.vexnum;i++)
		for(j=0;j<G.vexnum;j++)
		G.weight1[i][j]=-1;
		
	for(i=0;i<G.vexnum;i++)
		for(j=0;j<G.vexnum;j++)
		G.weight2[i][j]=-1;
	fclose(fp);
}

int firstadjvex(MGraph G1,int v)
{
	for(int i=0;i<G1.vexnum;i++)
	if(G1.arcs[v][i]==1)
	return i;
	return -1;
}

int nextadjvex(MGraph G1,int v,int w)
{
	for(int i=w+1;i<G1.vexnum;i++)
	if(G1.arcs[v][i]==1)
	return i;
	return -1;
}

void DFSjudge(MGraph &G1,int v,bool visited[])
{
	int w;
	visited[v]=1;
	G1.vexs[v].linked=1;
	for(w=firstadjvex(G1,v);w>=0;w=nextadjvex(G1,v,w))
	if(!visited[w])
		DFSjudge(G1,w,visited);
}

int locatevex(MGraph G,int num)
{
	int i;
	for(i=0;i<G.vexnum;i++)
	if(G.vexs[i].num==num)
		return i;
}
void initgraph(MGraph &G)
{
	int i,j;
	G.vexnum=1;
	for(i=0;i<G.vexnum;i++)
		G.vexs[i].linked=0;
		
	for(i=0;i<G.vexnum;i++)
		for(j=0;j<G.vexnum;j++)
			G.arcs[i][j]=0;
			
	for(i=0;i<G.vexnum;i++)
		for(j=0;j<G.vexnum;j++)
		G.weight1[i][j]=-1;
		
	for(i=0;i<G.vexnum;i++)
		for(j=0;j<G.vexnum;j++)
		G.weight2[i][j]=-1;
}
void eliminate(MGraph &G1,MGraph &G2)
{
	bool visited[MAX_VERTEX_NUM];
	int m;
	int x,y;
	int i,j,k; 
	bool flag=0;
	G2.vexnum=1;
	G2.vexs[0].num=0;//��ʼ����۵� 
	G2.vexs[0].x=0;
	G2.vexs[0].y=0;
	G2.vexs[0].linked=1;
	for(i=0;i<=G1.vexnum-1;i++)//�ж�������Ƿ��ͨ 
		for(j=i+1;j<=G1.vexnum-1;j++)
		{
			m=(G1.vexs[i].x-G1.vexs[j].x)*(G1.vexs[i].x-G1.vexs[j].x)
			+(G1.vexs[i].y-G1.vexs[j].y)*(G1.vexs[i].y-G1.vexs[j].y);
			if(m<=100)
			{
				G1.arcs[i][j]=1;
				G1.arcs[j][i]=1;
				G1.weight1[i][j]=sqrt(m);
				G1.weight1[j][i]=sqrt(m);
				G1.weight2[i][j]=m;
				G1.weight2[j][i]=m;
			}
		}
	for(i=0;i<=G1.vexnum-1;i++)
	visited[i]=0;
	DFSjudge(G1,0,visited);
	
	k=1;
	for(i=1;i<=G1.vexnum-1;i++)
	{
		if(G1.vexs[i].linked==1)
		{
			G2.vexs[k].num=G1.vexs[i].num;
			G2.vexs[k].x=G1.vexs[i].x;
			G2.vexs[k].y=G1.vexs[i].y;
			G2.vexs[k].linked=G1.vexs[i].linked;
			k++;
		}
		else
		cout<<"�ų��㣺"<<G1.vexs[i].num<<" ";
	}
	cout<<endl; 
	G2.vexnum=k;
	
	for(i=0;i<G2.vexnum;i++)
		for(j=0;j<G2.vexnum;j++)
			G2.arcs[i][j]=0;
			
	for(i=0;i<G2.vexnum;i++)
		for(j=0;j<G2.vexnum;j++)
		G2.weight1[i][j]=-1;
		
	for(i=0;i<G2.vexnum;i++)
		for(j=0;j<G2.vexnum;j++)
		G2.weight2[i][j]=-1;
		
	for(i=0;i<G2.vexnum;i++)
		{
			x=locatevex(G1,G2.vexs[i].num);
			for(j=i+1;j<G2.vexnum;j++)
			{
				y=locatevex(G1,G2.vexs[j].num);
				G2.arcs[i][j]=G1.arcs[x][y];
				G2.arcs[j][i]=G2.arcs[i][j];
				G2.weight1[i][j]=G1.weight1[x][y];
				G2.weight1[j][i]=G2.weight1[i][j];
				G2.weight2[i][j]=G1.weight2[x][y];
				G2.weight2[j][i]=G2.weight2[i][j];
			}
		}
		
}

void show(MGraph G)
{
	int  i,j;
	for(i=0;i<=G.vexnum-1;i++)
	{
		cout<<"��ţ�"<<setw(2)<<G.vexs[i].num<<" λ�ã�";
		cout<<"("<<G.vexs[i].x<<","<<G.vexs[i].y<<") ";
		cout<<setw(20)<<"�Ƿ����۵���ͨ��"<<setw(2)<<G.vexs[i].linked<<endl;
	}
	cout<<endl;
	cout<<"�ڽӾ���"<<endl;
	for(i=0;i<G.vexnum;i++)
	{
		for(j=0;j<G.vexnum;j++)
	    cout<<setw(3)<<G.arcs[i][j];
	    cout<<endl;
	}
	cout<<endl;
	cout<<"�ķ�ʱ�䣺"<<endl;
	for(i=0;i<G.vexnum;i++)
	{
		for(j=0;j<G.vexnum;j++)
	    printf("%10f ",G.weight1[i][j]);
	    cout<<endl;
	}
	cout<<endl;
	cout<<"�ܺģ�"<<endl;
	for(i=0;i<G.vexnum;i++)
	{
		for(j=0;j<G.vexnum;j++)
	    cout<<setw(4)<<G.weight2[i][j];
	    cout<<endl;
	}	
	cout<<endl;
}

void shortpath(MGraph G)
{
	int adjvex[MAX_VERTEX_NUM];
	int lowcost[MAX_VERTEX_NUM];
	int min; 
	bool finish[MAX_VERTEX_NUM];
	int i,j,k;
	int m;
	for(i=0;i<G.vexnum;i++)
	{
		adjvex[i]=0;
		lowcost[i]=G.weight1[i][0];
		finish[i]=0;
	}
	finish[0]=1;
/*	for(i=0;i<G.vexnum;i++)
	{
		min=99999999;//����С��
		
		for(j=0;j<G.vexnum;j++)
		if(!finish[j])
		{
			minnum=j;
			break;
		}
		for(j=0;j<G.vexnum;j++)
			if(!finish[j]&&distance[j]>0&&distance[j]<min)
			{
				
			}
	}*/
    for(int w=0;w<G.vexnum;w++)
        cout<<adjvex[w]<<" ";
    cout<<endl;
    for(int w=0;w<G.vexnum;w++)
        cout<<lowcost[w]<<" ";
    cout<<endl;
    for(int w=0;w<G.vexnum;w++)
        cout<<finish[w]<<" ";
    cout<<endl;
    
    for(i=1;i<G.vexnum;i++)
    {
        for(min=0;min<G.vexnum;min++)
            if(!finish[min])
                break;
        for(k=0;k<G.vexnum;k++)
            if(!finish[k]&&lowcost[k]>=0&&(lowcost[min]==-1||lowcost[k]<lowcost[min]))
                min=k;
        finish[min]=true;
        
        for(j=0;j<G.vexnum;j++)
            if(!finish[j]&&lowcost[min]>=0&&G.arcs[min][j]>0
			&&(lowcost[j]>(lowcost[min]+G.weight1[min][j])||lowcost[j]==-1))
            {
                lowcost[j]=lowcost[min]+G.weight1[min][j];
                adjvex[j]=min;
            }
        
        for(int w=0;w<G.vexnum;w++)
            cout<<adjvex[w]<<" ";
        cout<<endl;
        for(int w=0;w<G.vexnum;w++)
            cout<<lowcost[w]<<" ";
        cout<<endl;
        for(int w=0;w<G.vexnum;w++)
            cout<<finish[w]<<" ";
        cout<<endl;
    }
    for(i=1;i<G.vexnum;i++)
    {
    	m=adjvex[i];
    	cout<<"��ţ�"<<G.vexs[i].num<<" "<<"·����";
    	cout<<G.vexs[i].num;
    	while(m)
    	{
    		cout<<"->"<<G.vexs[m].num;
    		m=adjvex[m];
		}
		cout<<"->0  ";
		cout<<"ʱ�䣺"<<lowcost[i]<<endl;
	}
}

void shortenergy(MGraph G)
{
	int adjvex[MAX_VERTEX_NUM];
	int lowcost[MAX_VERTEX_NUM];
	int lowenergy[MAX_VERTEX_NUM];
	float allenergy;
	int min; 
	bool finish[MAX_VERTEX_NUM];
	int i,j,k;
	int m;
	for(i=0;i<G.vexnum;i++)
	{
		adjvex[i]=0;
		lowcost[i]=G.weight2[i][0];
		finish[i]=0;
	}
	finish[0]=1;
	
	for(int w=0;w<G.vexnum;w++)
        cout<<adjvex[w]<<" ";
    cout<<endl;
    for(int w=0;w<G.vexnum;w++)
        cout<<lowcost[w]<<" ";
    cout<<endl;
    for(int w=0;w<G.vexnum;w++)
        cout<<finish[w]<<" ";
    cout<<endl;
    
    for(i=1;i<G.vexnum;i++)
    {
        for(min=0;min<G.vexnum;min++)
            if(!finish[min])
                break;
        for(k=0;k<G.vexnum;k++)
            if(!finish[k]&&lowcost[k]>=0&&(lowcost[min]==-1||lowcost[k]<lowcost[min]))
                min=k;
        finish[min]=true;//�ҵ���С�� 
        
        for(j=0;j<G.vexnum;j++)
            if(!finish[j]&&lowcost[min]>=0&&G.arcs[min][j]>0
			&&(lowcost[j]>G.weight2[min][j]||lowcost[j]==-1))
            {
                lowcost[j]=G.weight2[min][j];
                adjvex[j]=min;
            }
        
        for(int w=0;w<G.vexnum;w++)
            cout<<adjvex[w]<<" ";
        cout<<endl;
        for(int w=0;w<G.vexnum;w++)
            cout<<lowcost[w]<<" ";
        cout<<endl;
        for(int w=0;w<G.vexnum;w++)
            cout<<finish[w]<<" ";
        cout<<endl;
    }
    for(i=0;i<G.vexnum;i++)
    lowenergy[i]=0;
    for(i=1;i<G.vexnum;i++)
    {
    	cout<<"��ţ�"<<G.vexs[i].num<<" "<<"���ӷ�ʽ��";
    	m=i;
    	while(m)
    	{
    		cout<<G.vexs[m].num<<"->";
    		lowenergy[i]+=lowcost[m];
    		m=adjvex[m];
		}
		cout<<"0  ";
		cout<<"�ܺģ�"<<lowenergy[i]<<endl;
	}
	allenergy=0;
	for(i=1;i<G.vexnum;i++)
	{
		allenergy+=lowenergy[i];
	}
	cout<<"ƽ����С�ܺģ�";
	printf("%.6f",allenergy/G.vexnum);
	cout<<endl;
}
int main()
{
	MGraph G1;
	MGraph G2;
	MGraph G3;
	creategraph(G1);
	initgraph(G2);
	eliminate(G1,G2);
	cout<<"��ʼ��Ϣ��"<<endl;
	show(G1);
	cout<<"�Ƴ������Ϣ��"<<endl;
	show(G2);
	shortpath(G2);
	shortenergy(G2); 
} 
