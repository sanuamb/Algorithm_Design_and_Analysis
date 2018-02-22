//BFS and DFS
#include<iostream.h>
//using namespace std;
// class declarations
class node
{
	int data;
	node*link;
	friend class graph;
};
class graph
{
	friend class queue;
	node*head[20];
	int n;
	public:
	void init();
	void create();
	void insert(int ,int);
	node*getnode();
	void router();
	void bfs();
	void dfs();
};
class qnode
{
	qnode*next;
	int data;
	friend class queue;
};
class queue
{
	qnode* rear;
	qnode* front;
	public:
	queue()
	{
		front=NULL;
		rear=NULL;
	}
	void enq(int k)
	{
		qnode*temp;
		temp=new qnode;
		temp->data=k;
		temp->next=NULL;

		if(front==NULL)
		{
			front=rear=temp;

		}
		else
		{
			rear->next=temp;
			rear=temp;

		}


	}
	int dq()
	{
		int p;
		qnode*ptr;
		if(front==NULL)
		{
			return 0;
		}
		else
		{
			ptr=front;
			p=front->data;
			front=front->next;
			ptr->next=NULL;
			return(p);
			delete ptr;

		}
	}
	int empty()
	{
		if(front==NULL)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	
};
class stacknode
{
	
	stacknode*next;
	int data;
	friend class stack;
};
class stack
{
	stacknode*top;
	public:
	stack()
	{
		top=NULL;
	}
	void push(int d)
	{
		stacknode*temp;
		temp=new stacknode;
		temp->data=d;
		if(top==NULL)
		{
			top=temp;
		}
		else
		{
			temp->next=top;
			top=temp;
		}
	}
	int pop()
	{
		stacknode*ptr;
		int p;
			ptr=top;
			p=ptr->data;
			top=top->next;
			ptr->next=NULL;
			return(p);
			delete ptr;
		
	}
	int empty()
	{
		if(top==NULL)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
};
void graph::init()
{
	int i;
	for(i=0;i<20;i++)
	{
		head[i]=NULL;
	}
}
void graph::create()
{
	int i,k,u,v;
	init();
	cout<<"\n enter the no of vertices:";
	cin>>n;
	cout<<"\n enter the no of edges:";
	cin>>k;
	for(i=0;i<k;i++)
	{
		cout<<"\n enter the vertices to join the edge:";
		cin>>u>>v;
		insert(u,v);
		insert(v,u);
	
	}
}
void graph::insert(int u,int v)
{
	node*temp,*p;
	temp=getnode();
	temp->data=v;
	if(head[u]==NULL)
	{
		head[u]=temp;
		
	}
	else
	{
		p=head[u];
		while(p->link!=NULL)
		{
			p=p->link;
		}
		p->link=temp;
	}
	
}
void graph::bfs()
{
	int visited[20],l,i,v1;
	queue q;
	node*ptr;
	cout<<"\n enter the vertex:";
	cin>>l;
	for(i=0;i<20;i++)
	{
		visited[i]=0;
	}
	q.enq(l);
	while(q.empty()!=1)
	{
		v1=q.dq();
		if(visited[v1]==0)
		{
			cout<<"\n vertex visited";
			cout<<v1;
			visited[v1]=1;	
		}
		ptr=head[v1];
		while(ptr!=NULL)
		{
			if(visited[ptr->data]==0)
			{
				q.enq(ptr->data);
			}
			ptr=ptr->link;
		}
	}
	
	
	
}
void graph::dfs()
{
	int visited[20],l,i,v1;
        stack s;
        node*ptr;
        cout<<"\n enter the vertex:";
        cin>>l;
        for(i=0;i<20;i++)
        {
                visited[i]=0;
        }
        s.push(l);
        while(s.empty()!=1)
        {
                v1=s.pop();
		cout<<"popped value is:"<<v1;
                if(visited[v1]==0)
                {
                        cout<<"\n vertex visited";
                        cout<<v1;
                        visited[v1]=1;
                }
                ptr=head[v1];
                while(ptr!=NULL)
                {
                        if(visited[ptr->data]==0)
                        {
                                s.push(ptr->data);
                        }
                        ptr=ptr->link;
		}
	}                    
}
node*graph::getnode()
{
	node*temp;
	temp=new node;
	temp->link=NULL;
	return temp;
}
void graph::router()
{
	int ch;
	char ans;
	do
	{
		cout<<"\n1.create\n2.BFS\n3.DFS";
		cout<<"\n enter the choice:";
		cin>>ch;
		switch(ch)
		{
			case 1:create();
				break;
			case 2:bfs();
				break;
			case 3:dfs();
				break;
		}
		cout<<"\n continue?";
		cin>>ans;
	}while(ans=='y'||ans=='Y');
}
int main()
{
	graph g;
	g.router();
	return 0;
}
