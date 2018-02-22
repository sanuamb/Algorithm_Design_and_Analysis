//Kruskal Algorithm
#include<iostream.h>
#include<conio.h>
class graph
{
	int m[50][50];
	int n;
	public:
	graph()
	{
		n=0;
	}
	void create_graph();
	void display();
	void kruskal();
};
void graph::create_graph()
{
	int w,v1,v2,i,j;
	char ans;
	cout<<"\n enter the no of vertices:";
	cin>>n;
	for(i=1;i<50;i++)
	{
		for(j=1;j<50;j++)
		{
			m[i][j]=0;
		}
	}

	do
	{
		 cout<<"\n enter the starting vertex:";
		 cin>>v1;
		 cout<<"\n enter the end vertex:";
		 cin>>v2;


		if(m[v1][v2]==0&&m[v2][v1]==0)
		{
			cout<<"\n enter the weight:";
			cin>>w;
			m[v1][v2]=w;
			m[v2][v1]=w;
		}
		else
		{
			cout<<"\n edge already exist";
		}
		cout<<"\n add more edges?";
		cin>>ans;
	}while(ans=='y'||ans=='Y');
}
void graph::display()
{
	int i,j;
	for(i=1;i<=n;i++)
	{

		for(j=1;j<=n;j++)
		{
			cout<<m[i][j]<<"\t";
		}
		cout<<"\n";
	}
}
void graph::kruskal()
{

	int count=0,i,j,p[50],wt=0;
	int u,v;
	int min;
	for(i=1;i<50;i++)
	{
		p[i]=-1;
	}
	while(count<=(n-1))
	{
		min=32645;
		for(i=1;i<=n;i++)
		{
			for(j=1;j<=n;j++)
			{
				if(min>m[i][j]&&m[i][j]!=0)
				{
					min=m[i][j];
					u=i;
					v=j;
				}
			}
		}



		i=u;
		j=v;
		while(p[i]!=(-1))

		{
			i=p[i];
		}
		while(p[j]!=(-1))
		{
			j=p[j];
		}
		if(i!=j)
		{
			p[j]=i;
			wt=wt+min;
		}
		m[u][v]=m[v][u]=32645;
		count++;
	}
	cout<<"\nweight of minimum spanning tree is:"<<wt;


}
int main()
{
	clrscr();
	graph g;
	int ch;
	char ans;
	do
	{
		cout<<"\n1.accept\n2.display\n3.kruskal";
		cout<<"\n enter the choice:";
		cin>>ch;
		switch(ch)
		{
			case 1:g.create_graph();
				break;
			case 2:g.display();
				break;
			case 3:g.kruskal();
				break;
			default:cout<<"\n invalid choice!";
		}
		cout<<"\n continue?";
		cin>>ans;
	}while(ans=='y'||ans=='Y');
	getch();
	return 0;
}
