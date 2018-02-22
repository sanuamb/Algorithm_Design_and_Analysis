//Prim Algorithm
#include<iostream.h>
//using namespace std;

class graph
{
	int m[50][50];
	int v;
	public:
	void create_graph();
	void display();
	void prim();
};
void graph::create_graph()
{
	int w,v1,v2,i,j;
	char ans;
	cout<<"\n enter the no of vertices:";
	cin>>v;
	for(i=1;i<v;i++)
        {
                for(j=1;j<v;j++)
                {
                        m[i][j]=0;
                }
        }

	do
	{
		cout<<"\n enter the vertices for which we want an edge:";
       		 cin>>v1>>v2;
		if(m[v1][v2]==0)
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
	for(i=1;i<=v;i++)
	{
		
		for(j=1;j<=v;j++)
		{
			cout<<m[i][j]<<"\t";
		}
		cout<<"\n";
	}
}
void graph::prim()
{
	int min,count=0,i,j,wt=0;
	int visited[50],vi,vj,k;
	cout<<"\n enter the start vertex:";
	cin>>k;
	visited[k]=1;
	do
	{
		min=999;
		
		for(i=1;i<=v;i++)
		{
			if(visited[i]==1)
			{
				for(j=1;j<=v;j++)
			    {
				if(m[i][j]<min&&visited[j]!=1&&m[i][j]!=0)
				{
					min=m[i][j];
					vi=i;
					vj=j;
					
				}
				
			    }
				
			}
			
			
		}
		count++;
		cout<<"\ncount is:"<<count;
		visited[vj]=1;
		wt=wt+min;
		cout<<"\n wt is:"<<wt;
		cout<<"vetrices are:"<<vi<<vj;

	}while(count<(v-1));
}
int main()
{
	graph obj;
	char ans;
	int ch;
	do
	{
		cout<<"\n1.create_graph\n2.display\n3.prim_algo";
		cin>>ch;
		switch(ch)
		{
			case 1:obj.create_graph();
				break;
			case 2:obj.display();
				break;
			case 3:obj.prim();
				break;
		}
		cout<<"\n continue?";
		cin>>ans;
	}while(ans=='y'||ans=='Y');
	return 0;
}
