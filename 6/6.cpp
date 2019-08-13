#include<iostream>
#include<stdlib.h>
#include<string.h>
using namespace std;
#include<time.h>
void readdata(int a[],FILE *f)
{
	for(int i=0;i<20000;i++)
	fscanf(f,"%d",&a[i]);
	fclose(f);
}

void insertsort(int a[])//直接插入排序 
{
	int i,j,t;
	int choice;
	clock_t start,finish;
	double total_time;
	start=clock();
	for(i=1;i<20000;i++)
	{
		t=a[i];
		for(j=i-1;j>=0&&a[j]>t;j--)
		 a[j+1]=a[j];
		 a[j+1]=t;
	}
	finish=clock();
	total_time = (double)(finish-start) / CLOCKS_PER_SEC;
 	printf("直接插入排序 共用时：%f s\n",total_time);
 	cout<<"是否显示排序结果(输入1显示，0不显示)："<<endl;
 	cin>>choice;
 	if(choice==1)
 	{
 		for(i=0;i<20000;i++)
		 cout<<a[i]<<" ";	
	}
}

void shellinsert(int a[],int dk)
{
	int i,j,t;	
	for(i=dk;i<20000;i++)
	{
		t=a[i];
		for(j=i-dk;j>=0&&a[j]>t;j-=dk)
		 a[j+dk]=a[j];
		 a[j+dk]=t;
	}
}

void shellsort(int a[])//希尔排序 
{
	int k,i;
	int choice;
	int dlta[3]={5,3,1};
	clock_t start,finish;
	double total_time;
	start=clock();
	
	for(k=0;k<3;++k)
	shellinsert(a,dlta[k]);
	
	finish=clock();
	total_time = (double)(finish-start) / CLOCKS_PER_SEC;
 	printf("希尔排序 共用时：%f s\n",total_time);
 	cout<<"是否显示排序结果(输入1显示，0不显示)："<<endl;
 	cin>>choice;
 	if(choice==1)
 	{
 		for(i=0;i<20000;i++)
		 cout<<a[i]<<"　";	
	}
}

void bubblesort(int a[])//冒泡排序 
{
	int i,j,flag=0;
	int choice;
	int t;
	clock_t start,finish;
	double total_time;
	start=clock();
	
	for(i=0;i<19999;i++)
	{
		flag=0;
		for(j=0;j<19999-i;j++)
		if(a[j]>a[j+1])
		{
			t=a[j];
			a[j]=a[j+1];
			a[j+1]=t;
			flag=1;
		}
		if(!flag)
		break;
	}
	
	finish=clock();
	total_time = (double)(finish-start) / CLOCKS_PER_SEC;
 	printf("冒泡排序 共用时：%f s\n",total_time);
 	cout<<"是否显示排序结果(输入1显示，0不显示)："<<endl;
 	cin>>choice;
 	if(choice==1)
 	{
 		for(i=0;i<20000;i++)
		 cout<<a[i]<<"　";	
	}
}

int partition(int a[],int low,int high)
{
	int i=low,j=high;
	int pivotkey=a[low];
	while(i<j)
	{
		while(i<j&&a[j]>=pivotkey)
			j--;
		a[i]=a[j];
		while(i<j&&a[i]<=pivotkey)
			i++;
		a[j]=a[i];
	}
	a[i]=pivotkey;
	return i;
}
void qsort(int a[],int low,int high)//快速排序 
{
	int pivotloc;
	if(low<high)
	{
		pivotloc=partition(a,low,high);
		qsort(a,low,pivotloc-1);
		qsort(a,pivotloc+1,high);
	}
}

void timeqsort(int a[])
{
	int i,j;
	int choice;
	int t;
	clock_t start,finish;
	double total_time;
	start=clock();
	
	qsort(a,0,19999);
	
	finish=clock();
	total_time = (double)(finish-start) / CLOCKS_PER_SEC;
 	printf("快速排序 共用时：%f s\n",total_time);
 	cout<<"是否显示排序结果(输入1显示，0不显示)："<<endl;
 	cin>>choice;
 	if(choice==1)
 	{
 		for(i=0;i<20000;i++)
		 cout<<a[i]<<"　";	
	}
}

void selectsort(int a[]) //选择排序 
{
	int i,j,k;
	int choice;
	int t;
	clock_t start,finish;
	double total_time;
	start=clock();
	
	for(i=0;i<19999;i++)
	{
		k=i;
		for(j=k+1;j<20000;j++)
		if(a[j]<a[k])
			k=j;
		if(k!=i)
		{
			t=a[k];
			a[k]=a[i];
			a[i]=t;
		}
	}
	
	finish=clock();
	total_time = (double)(finish-start) / CLOCKS_PER_SEC;
 	printf("选择排序 共用时：%f s\n",total_time);
 	cout<<"是否显示排序结果(输入1显示，0不显示)："<<endl;
 	cin>>choice;
 	if(choice==1)
 	{
 		for(i=0;i<20000;i++)
		 cout<<a[i]<<"　";	
	}
}
void heapadjust(int a[],int s,int m)
{
	int i,j,t;
	i=s;
	t=a[i];
	j=i*2+1;
	while(j<=m)
	{
		if(j+1<=m&&a[j+1]>a[j])
		 j++;
		if(t>a[j])
			break;
		else
		{
			a[i]=a[j];
			i=j;
			j=2*i+1;
		}
	}
	a[i]=t;
}

void heapsort(int a[])//堆排序 
{
	int i,j,t;
	int choice;
	clock_t start,finish;
	double total_time;
	start=clock();
	
	for(i=9999;i>=0;i--)
	heapadjust(a,i,19999);
	
	for(i=19999;i>0;i--)
	{
		t=a[0];
		a[0]=a[i];
		a[i]=t;
		heapadjust(a,0,i-1);
	}
	finish=clock();
	total_time = (double)(finish-start) / CLOCKS_PER_SEC;
 	printf("堆排序 共用时：%f s\n",total_time);
 	cout<<"是否显示排序结果(输入1显示，0不显示)："<<endl;
 	cin>>choice;
 	if(choice==1)
 	{
 		for(i=0;i<20000;i++)
		 cout<<a[i]<<"　";	
	}
} 

void merge(int a[],int temp[],int i,int m,int n)
{
	int j,k;
	int l=i;
	for(j=m+1,k=l;l<=m&&j<=n;k++)
	{
		if(a[l]>a[j])
		{
			temp[k]=a[j];
			j++;
		}
		else
		{
			temp[k]=a[l];
			l++;
		}
	}
	while(l<=m)
	{
		temp[k]=a[l];
		l++;
		k++;
	}
	while(j<=n)
	{
		temp[k]=a[j];
		j++;
		k++;
	}
	
	for(l=i;l<=n;l++)
	a[l]=temp[l];
}
void msort(int a[],int temp[],int s,int t)
{
	int m;
	if(s==t)
	temp[s]=a[s];
	else
	{
		m=(s+t)/2;
		msort(a,temp,s,m);
		msort(a,temp,m+1,t);
		merge(a,temp,s,m,t); 
	}
}
void mergesort(int a[])//归并排序 
{
	int temp[20000];
	int choice,i;
	clock_t start,finish;
	double total_time;
	start=clock();
	
	msort(a,temp,0,19999);

	finish=clock();
	total_time = (double)(finish-start) / CLOCKS_PER_SEC;
 	printf("归并排序 共用时：%f s\n",total_time);
 	cout<<"是否显示排序结果(输入1显示，0不显示)："<<endl;
 	cin>>choice;
 	if(choice==1)
 	{
 		for(i=0;i<20000;i++)
		 cout<<a[i]<<"　";	
	}
	
}

void radixsort(int a[])//基数排序 
{
	int count[10]={0};
	int i,x=1,j,t,k;
	int buck[10][20000];//五位数循环五次
	int choice;
	clock_t start,finish;
	double total_time;
	start=clock();
	
	for(j=0;j<5;j++)
	{
		for(i=0;i<10;i++)
		count[i]=0;
		
		for(i=0;i<20000;i++)
		{
			t=(a[i]/x)%10;
			buck[t][count[t]]=a[i];
			count[t]++;
		}		

		t=0;
		for(i=0;i<10;i++)
		{
			for(k=0;k<count[i];k++)
			{
				a[t]=buck[i][k];
				t++;
			}
		} 
		x*=10;
	}
	
	finish=clock();
	total_time = (double)(finish-start) / CLOCKS_PER_SEC;
 	printf("基数排序 共用时：%f s\n",total_time);
 	cout<<"是否显示排序结果(输入1显示，0不显示)："<<endl;
 	cin>>choice;
 	if(choice==1)
 	{
 		for(i=0;i<20000;i++)
		 cout<<a[i]<<"　";	
	}
}
void writetxt(int a[],FILE *f)
{
	int i;
	for(i=0;i<19999;i++)
	fprintf(f,"%d ",a[i]);
	fprintf(f,"%d",a[i]);
	fclose(f);
}
int main()
{
	int a[20000]={0};
	FILE *fp,*fs;
/*	fp=fopen("data10.txt","w");
	if(!fp)
	{
		cout<<"打开文件失败！"<<endl;
		exit(0);
	}
	srand((int)time(0));
	for(int i=1;i<20000;i++)
	{
		
		fprintf(fp,"%d ",rand());
	}
	fprintf(fp,"%d",rand());
	fclose(fp);
*/
	cout<<"测试data1.txt中数据！"<<endl;
	fs=fopen("data1.txt","r");
	if(!fs)
	{
		cout<<"打开文件失败！"<<endl;
		exit(0);
	}
	readdata(a,fs);
	insertsort(a);
	
	fs=fopen("data1.txt","r");
	if(!fs)
	{
		cout<<"打开文件失败！"<<endl;
		exit(0);
	}
	readdata(a,fs);
	shellsort(a);
	
	fs=fopen("data1.txt","r");
	if(!fs)
	{
		cout<<"打开文件失败！"<<endl;
		exit(0);
	}
	readdata(a,fs);
	bubblesort(a);
	
	fs=fopen("data1.txt","r");
	if(!fs)
	{
		cout<<"打开文件失败！"<<endl;
		exit(0);
	}
	readdata(a,fs);
	timeqsort(a);
	
	fs=fopen("data1.txt","r");
	if(!fs)
	{
		cout<<"打开文件失败！"<<endl;
		exit(0);
	}
	readdata(a,fs);
	selectsort(a);
	
	fs=fopen("data1.txt","r");
	if(!fs)
	{
		cout<<"打开文件失败！"<<endl;
		exit(0);
	}
	readdata(a,fs);
	heapsort(a);
	
	fs=fopen("data1.txt","r");
	if(!fs)
	{
		cout<<"打开文件失败！"<<endl;
		exit(0);
	}
	readdata(a,fs);
	mergesort(a);
		
	fs=fopen("data1.txt","r");
	if(!fs)
	{
		cout<<"打开文件失败！"<<endl;
		exit(0);
	}
	readdata(a,fs);
	radixsort(a);
	
	
	cout<<endl<<"测试data2.txt中数据！"<<endl;
	fs=fopen("data2.txt","r");
	if(!fs)
	{
		cout<<"打开文件失败！"<<endl;
		exit(0);
	}
	readdata(a,fs);
	insertsort(a);
	
	fs=fopen("data2.txt","r");
	if(!fs)
	{
		cout<<"打开文件失败！"<<endl;
		exit(0);
	}
	readdata(a,fs);
	shellsort(a);
	
	fs=fopen("data2.txt","r");
	if(!fs)
	{
		cout<<"打开文件失败！"<<endl;
		exit(0);
	}
	readdata(a,fs);
	bubblesort(a);
	
	fs=fopen("data2.txt","r");
	if(!fs)
	{
		cout<<"打开文件失败！"<<endl;
		exit(0);
	}
	readdata(a,fs);
	timeqsort(a);
	
	fs=fopen("data2.txt","r");
	if(!fs)
	{
		cout<<"打开文件失败！"<<endl;
		exit(0);
	}
	readdata(a,fs);
	selectsort(a);
	
	fs=fopen("data2.txt","r");
	if(!fs)
	{
		cout<<"打开文件失败！"<<endl;
		exit(0);
	}
	readdata(a,fs);
	heapsort(a);
	
	fs=fopen("data2.txt","r");
	if(!fs)
	{
		cout<<"打开文件失败！"<<endl;
		exit(0);
	}
	readdata(a,fs);
	mergesort(a);
		
	fs=fopen("data2.txt","r");
	if(!fs)
	{
		cout<<"打开文件失败！"<<endl;
		exit(0);
	}
	readdata(a,fs);
	radixsort(a);

	cout<<endl<<"测试data3.txt中数据！"<<endl;
	fs=fopen("data3.txt","r");
	if(!fs)
	{
		cout<<"打开文件失败！"<<endl;
		exit(0);
	}
	readdata(a,fs);
	insertsort(a);
	
	fs=fopen("data3.txt","r");
	if(!fs)
	{
		cout<<"打开文件失败！"<<endl;
		exit(0);
	}
	readdata(a,fs);
	shellsort(a);
	
	fs=fopen("data3.txt","r");
	if(!fs)
	{
		cout<<"打开文件失败！"<<endl;
		exit(0);
	}
	readdata(a,fs);
	bubblesort(a);
	
	fs=fopen("data3.txt","r");
	if(!fs)
	{
		cout<<"打开文件失败！"<<endl;
		exit(0);
	}
	readdata(a,fs);
	timeqsort(a);
	
	fs=fopen("data3.txt","r");
	if(!fs)
	{
		cout<<"打开文件失败！"<<endl;
		exit(0);
	}
	readdata(a,fs);
	selectsort(a);
	
	fs=fopen("data3.txt","r");
	if(!fs)
	{
		cout<<"打开文件失败！"<<endl;
		exit(0);
	}
	readdata(a,fs);
	heapsort(a);
	
	fs=fopen("data3.txt","r");
	if(!fs)
	{
		cout<<"打开文件失败！"<<endl;
		exit(0);
	}
	readdata(a,fs);
	mergesort(a);
		
	fs=fopen("data3.txt","r");
	if(!fs)
	{
		cout<<"打开文件失败！"<<endl;
		exit(0);
	}
	readdata(a,fs);
	radixsort(a);
	
	cout<<endl<<"测试data4.txt中数据！"<<endl;
	fs=fopen("data4.txt","r");
	if(!fs)
	{
		cout<<"打开文件失败！"<<endl;
		exit(0);
	}
	readdata(a,fs);
	insertsort(a);
	
	fs=fopen("data4.txt","r");
	if(!fs)
	{
		cout<<"打开文件失败！"<<endl;
		exit(0);
	}
	readdata(a,fs);
	shellsort(a);
	
	fs=fopen("data4.txt","r");
	if(!fs)
	{
		cout<<"打开文件失败！"<<endl;
		exit(0);
	}
	readdata(a,fs);
	bubblesort(a);
	
	fs=fopen("data4.txt","r");
	if(!fs)
	{
		cout<<"打开文件失败！"<<endl;
		exit(0);
	}
	readdata(a,fs);
	timeqsort(a);
	
	fs=fopen("data4.txt","r");
	if(!fs)
	{
		cout<<"打开文件失败！"<<endl;
		exit(0);
	}
	readdata(a,fs);
	selectsort(a);
	
	fs=fopen("data4.txt","r");
	if(!fs)
	{
		cout<<"打开文件失败！"<<endl;
		exit(0);
	}
	readdata(a,fs);
	heapsort(a);
	
	fs=fopen("data4.txt","r");
	if(!fs)
	{
		cout<<"打开文件失败！"<<endl;
		exit(0);
	}
	readdata(a,fs);
	mergesort(a);
		
	fs=fopen("data4.txt","r");
	if(!fs)
	{
		cout<<"打开文件失败！"<<endl;
		exit(0);
	}
	readdata(a,fs);
	radixsort(a);
	
	cout<<endl<<"测试data5.txt中数据！"<<endl;
	fs=fopen("data5.txt","r");
	if(!fs)
	{
		cout<<"打开文件失败！"<<endl;
		exit(0);
	}
	readdata(a,fs);
	insertsort(a);
	
	fs=fopen("data5.txt","r");
	if(!fs)
	{
		cout<<"打开文件失败！"<<endl;
		exit(0);
	}
	readdata(a,fs);
	shellsort(a);
	
	fs=fopen("data5.txt","r");
	if(!fs)
	{
		cout<<"打开文件失败！"<<endl;
		exit(0);
	}
	readdata(a,fs);
	bubblesort(a);
	
	fs=fopen("data5.txt","r");
	if(!fs)
	{
		cout<<"打开文件失败！"<<endl;
		exit(0);
	}
	readdata(a,fs);
	timeqsort(a);
	
	fs=fopen("data5.txt","r");
	if(!fs)
	{
		cout<<"打开文件失败！"<<endl;
		exit(0);
	}
	readdata(a,fs);
	selectsort(a);
	
	fs=fopen("data5.txt","r");
	if(!fs)
	{
		cout<<"打开文件失败！"<<endl;
		exit(0);
	}
	readdata(a,fs);
	heapsort(a);
	
	fs=fopen("data5.txt","r");
	if(!fs)
	{
		cout<<"打开文件失败！"<<endl;
		exit(0);
	}
	readdata(a,fs);
	mergesort(a);
		
	fs=fopen("data5.txt","r");
	if(!fs)
	{
		cout<<"打开文件失败！"<<endl;
		exit(0);
	}
	readdata(a,fs);
	radixsort(a);
	
	cout<<endl<<"测试data6.txt中数据！"<<endl;
	fs=fopen("data6.txt","r");
	if(!fs)
	{
		cout<<"打开文件失败！"<<endl;
		exit(0);
	}
	readdata(a,fs);
	insertsort(a);
	
	fs=fopen("data6.txt","r");
	if(!fs)
	{
		cout<<"打开文件失败！"<<endl;
		exit(0);
	}
	readdata(a,fs);
	shellsort(a);
	
	fs=fopen("data6.txt","r");
	if(!fs)
	{
		cout<<"打开文件失败！"<<endl;
		exit(0);
	}
	readdata(a,fs);
	bubblesort(a);
	
	fs=fopen("data6.txt","r");
	if(!fs)
	{
		cout<<"打开文件失败！"<<endl;
		exit(0);
	}
	readdata(a,fs);
	timeqsort(a);
	
	fs=fopen("data6.txt","r");
	if(!fs)
	{
		cout<<"打开文件失败！"<<endl;
		exit(0);
	}
	readdata(a,fs);
	selectsort(a);
	
	fs=fopen("data6.txt","r");
	if(!fs)
	{
		cout<<"打开文件失败！"<<endl;
		exit(0);
	}
	readdata(a,fs);
	heapsort(a);
	
	fs=fopen("data6.txt","r");
	if(!fs)
	{
		cout<<"打开文件失败！"<<endl;
		exit(0);
	}
	readdata(a,fs);
	mergesort(a);
		
	fs=fopen("data6.txt","r");
	if(!fs)
	{
		cout<<"打开文件失败！"<<endl;
		exit(0);
	}
	readdata(a,fs);
	radixsort(a);
	
	cout<<endl<<"测试data7.txt中数据！"<<endl;
	fs=fopen("data7.txt","r");
	if(!fs)
	{
		cout<<"打开文件失败！"<<endl;
		exit(0);
	}
	readdata(a,fs);
	insertsort(a);
	
	fs=fopen("data7.txt","r");
	if(!fs)
	{
		cout<<"打开文件失败！"<<endl;
		exit(0);
	}
	readdata(a,fs);
	shellsort(a);
	
	fs=fopen("data7.txt","r");
	if(!fs)
	{
		cout<<"打开文件失败！"<<endl;
		exit(0);
	}
	readdata(a,fs);
	bubblesort(a);
	
	fs=fopen("data7.txt","r");
	if(!fs)
	{
		cout<<"打开文件失败！"<<endl;
		exit(0);
	}
	readdata(a,fs);
	timeqsort(a);
	
	fs=fopen("data7.txt","r");
	if(!fs)
	{
		cout<<"打开文件失败！"<<endl;
		exit(0);
	}
	readdata(a,fs);
	selectsort(a);
	
	fs=fopen("data7.txt","r");
	if(!fs)
	{
		cout<<"打开文件失败！"<<endl;
		exit(0);
	}
	readdata(a,fs);
	heapsort(a);
	
	fs=fopen("data7.txt","r");
	if(!fs)
	{
		cout<<"打开文件失败！"<<endl;
		exit(0);
	}
	readdata(a,fs);
	mergesort(a);
		
	fs=fopen("data7.txt","r");
	if(!fs)
	{
		cout<<"打开文件失败！"<<endl;
		exit(0);
	}
	readdata(a,fs);
	radixsort(a);
	
	cout<<endl<<"测试data8.txt中数据！"<<endl;
	fs=fopen("data8.txt","r");
	if(!fs)
	{
		cout<<"打开文件失败！"<<endl;
		exit(0);
	}
	readdata(a,fs);
	insertsort(a);
	
	fs=fopen("data8.txt","r");
	if(!fs)
	{
		cout<<"打开文件失败！"<<endl;
		exit(0);
	}
	readdata(a,fs);
	shellsort(a);
	
	fs=fopen("data8.txt","r");
	if(!fs)
	{
		cout<<"打开文件失败！"<<endl;
		exit(0);
	}
	readdata(a,fs);
	bubblesort(a);
	
	fs=fopen("data8.txt","r");
	if(!fs)
	{
		cout<<"打开文件失败！"<<endl;
		exit(0);
	}
	readdata(a,fs);
	timeqsort(a);
	
	fs=fopen("data8.txt","r");
	if(!fs)
	{
		cout<<"打开文件失败！"<<endl;
		exit(0);
	}
	readdata(a,fs);
	selectsort(a);
	
	fs=fopen("data8.txt","r");
	if(!fs)
	{
		cout<<"打开文件失败！"<<endl;
		exit(0);
	}
	readdata(a,fs);
	heapsort(a);
	
	fs=fopen("data8.txt","r");
	if(!fs)
	{
		cout<<"打开文件失败！"<<endl;
		exit(0);
	}
	readdata(a,fs);
	mergesort(a);
		
	fs=fopen("data8.txt","r");
	if(!fs)
	{
		cout<<"打开文件失败！"<<endl;
		exit(0);
	}
	readdata(a,fs);
	radixsort(a);
	
	cout<<endl<<"测试data9.txt中数据！"<<endl;
	fs=fopen("data9.txt","r");
	if(!fs)
	{
		cout<<"打开文件失败！"<<endl;
		exit(0);
	}
	readdata(a,fs);
	insertsort(a);
	
	fs=fopen("data9.txt","r");
	if(!fs)
	{
		cout<<"打开文件失败！"<<endl;
		exit(0);
	}
	readdata(a,fs);
	shellsort(a);
	
	fs=fopen("data9.txt","r");
	if(!fs)
	{
		cout<<"打开文件失败！"<<endl;
		exit(0);
	}
	readdata(a,fs);
	bubblesort(a);
	
	fs=fopen("data9.txt","r");
	if(!fs)
	{
		cout<<"打开文件失败！"<<endl;
		exit(0);
	}
	readdata(a,fs);
	timeqsort(a);
	
	fs=fopen("data9.txt","r");
	if(!fs)
	{
		cout<<"打开文件失败！"<<endl;
		exit(0);
	}
	readdata(a,fs);
	selectsort(a);
	
	fs=fopen("data9.txt","r");
	if(!fs)
	{
		cout<<"打开文件失败！"<<endl;
		exit(0);
	}
	readdata(a,fs);
	heapsort(a);
	
	fs=fopen("data9.txt","r");
	if(!fs)
	{
		cout<<"打开文件失败！"<<endl;
		exit(0);
	}
	readdata(a,fs);
	mergesort(a);
		
	fs=fopen("data9.txt","r");
	if(!fs)
	{
		cout<<"打开文件失败！"<<endl;
		exit(0);
	}
	readdata(a,fs);
	radixsort(a);
	
		cout<<endl<<"测试data10.txt中数据！"<<endl;
	fs=fopen("data10.txt","r");
	if(!fs)
	{
		cout<<"打开文件失败！"<<endl;
		exit(0);
	}
	readdata(a,fs);
	insertsort(a);
	
	fs=fopen("data10.txt","r");
	if(!fs)
	{
		cout<<"打开文件失败！"<<endl;
		exit(0);
	}
	readdata(a,fs);
	shellsort(a);
	
	fs=fopen("data10.txt","r");
	if(!fs)
	{
		cout<<"打开文件失败！"<<endl;
		exit(0);
	}
	readdata(a,fs);
	bubblesort(a);
	
	fs=fopen("data10.txt","r");
	if(!fs)
	{
		cout<<"打开文件失败！"<<endl;
		exit(0);
	}
	readdata(a,fs);
	timeqsort(a);
	
	fs=fopen("data10.txt","r");
	if(!fs)
	{
		cout<<"打开文件失败！"<<endl;
		exit(0);
	}
	readdata(a,fs);
	selectsort(a);
	
	fs=fopen("data10.txt","r");
	if(!fs)
	{
		cout<<"打开文件失败！"<<endl;
		exit(0);
	}
	readdata(a,fs);
	heapsort(a);
	
	fs=fopen("data10.txt","r");
	if(!fs)
	{
		cout<<"打开文件失败！"<<endl;
		exit(0);
	}
	readdata(a,fs);
	mergesort(a);
		
	fs=fopen("data10.txt","r");
	if(!fs)
	{
		cout<<"打开文件失败！"<<endl;
		exit(0);
	}
	readdata(a,fs);
	radixsort(a);
/*	fp=fopen("data1.txt","w");
	if(!fp)
	{
		cout<<"打开文件失败！"<<endl;
		exit(0);
	}
	writetxt(a,fp);*/
}
