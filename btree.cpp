//BTrees
//Search Operation
#include<iostream>
#define max 20
using namespace std;

class node;

class pair1
{
	int key;
	node*next;
	public:
	pair1()
	{
		key=0;
		next=NULL;
	}
	friend class node;
	friend class btree;
};
class node
{
	int no_of_keys;
	pair1 data[20];
	node*father;
	node*start;
	public:
	node()
	{
		no_of_keys=0;
		father=start=NULL;
	}
	friend class btree;
	friend class pair1;
	void insertnode(pair1 p);
	int leaf_node();
	node*next_index(int);
	pair1 split_node();
	void display();
};
class btree
{
	node*root;
	int mkeys;
	friend class pair1;
	public:
	btree(int order)
	{
		mkeys=order-1;
		root=NULL;
	}
	void insert(int x);
	void display_tree();
	node*search(int x);
};
class queue
{
	node*data[100];
	int f,r;
	public:
	queue()
	{
		f=(-1);
		r=(-1);
	}
	int empty()
	{
		if((f==-1&&r==-1)||f>r)
			return(-1);
		else
		return 0;
	}
	int full()
	{
		if(r==max-1)
		  return -1;
		else
		  return 0;
	}
	node*del();
	void add(node*);
	void makeempty()
	{
		f=-1;
		r=-1;
	}
};
void queue::add(node*x)
{
	if(empty())
	{
		f=f+1;
		r=r+1;
		data[f]=x;
	}
	  else
	   { 
		if(!full())
		r=r+1;
		data[r]=x;
	  }
	
}
node*queue::del()
{
	node*x;
	if(!empty())
	{
		x=data[f];
		f=f+1;
		
	}
	return(x);
}
void btree::insert(int x)
{
	node*ptr,*newroot;
	pair1 p1,temp;
	p1.key=x;
	p1.next=NULL;
	if(root==NULL)
	{
		root=new node;
		root->insertnode(p1);
	}
	else
	{
		ptr=root;
		while(!(ptr->leaf_node()))
		{
			ptr=ptr->next_index(x);
		}
			ptr->insertnode(p1);
			if(ptr->no_of_keys>mkeys)
			{
				temp=ptr->split_node();
				while(1)
				{
					if(ptr==root)
					{
						newroot=new node;
						newroot->data[0]=temp;
						newroot->father=NULL;
						newroot->no_of_keys=1;
						root=newroot;
						newroot->start=ptr;
						newroot->start->father=newroot;
						newroot->data[0].next->father=newroot;
						return;
					}
					else
					{
						ptr=ptr->father;
						ptr->insertnode(temp);
						if(ptr->no_of_keys<=mkeys)
						return;
						else
						 temp=ptr->split_node();
					}
				}
				
			}
		
	}
}
void btree::display_tree()
{
	queue q1,q2;
	node*p;
	q1.add(root);
	while(!q1.empty())
	{
		q2.makeempty();
		cout<<endl<<endl;
		while(!(q1.empty()))
		{
			p=q1.del();
			p->display();
			if(!(p->leaf_node()))
			{
				q2.add(p->start);
				for(int i=0;i<p->no_of_keys;i++)
					q2.add(p->data[i].next);
			}
		}
		q1=q2;
	}
}
node*btree::search(int x)
{
	node*p;
	int i=0;
	p=root;
	while(p!=NULL)
	{
		for(i=0;i<p->no_of_keys;i++)
		{
			if(x==p->data[i-1].key)
				return p;
		}
		p=p->next_index(x);

	}
	return NULL;
}
void node::insertnode(pair1 p)
{
	int i=0;
	i=no_of_keys-1;
	while(i>=0&&(data[i].key>p.key))
	{
		data[i+1]=data[i];
		i--;
	}
	data[i+1]=p;
	no_of_keys++;
}
int node::leaf_node()
{
	if(data[0].next==NULL)
	    return 1;
	return 0;
}
node*node::next_index(int x)
{
	int i;
	i=0;
	if(x<data[0].key)
	return start;
	while(i<no_of_keys)
	{
		if(x<=data[i].key)
		return(data[i-1].next);
		i++;
	}
	return (data[i-1].next);
}
pair1 node::split_node()
{
	node*temp_split;
	node*temp;
	pair1 split_pair1;
	int middle_node,i,j=0;
	middle_node=(no_of_keys-1)/2;
	temp_split=new node;
	for(i=middle_node+1;i<no_of_keys;i++)
	{
		temp_split->data[j]=data[i];
		j++;
	}
	temp_split->no_of_keys=no_of_keys-middle_node-1;
	no_of_keys=middle_node;
	
	temp_split->start=data[middle_node].next;
	temp_split->father=father;
	if(temp_split->start!=NULL)
	{
		temp_split->start->father=father;
	}
	split_pair1.key=data[middle_node].key;
	split_pair1.next=temp_split;
	return (split_pair1);
}

void node::display()
{
	int i=0;
	while(i<no_of_keys)
	{
		cout<<data[i].key<<"\t";
		i++;
	}
}
int main()
{

	int ch,x;
	node*temp;
	char ans;
	btree t(5);
	do
	{
		cout<<"\nMENU:";
		cout<<"\n1.create\n2.display\n3.search";
		cout<<"\n enter the choice:";
		cin>>ch;
		switch(ch)
		{
			case 1:cout<<"\n enter data:";
				cin>>x;
				t.insert(x);
				break;
			case 2:t.display_tree();
				break;
			case 3:cout<<"\n enter the data to be searched:";
				cin>>x;
				temp=t.search(x);
				if(temp==NULL)
				{
					cout<<"\n\n data not found";
				}
				else
				{
					cout<<"\n data present in the tree";
				}
				break;
			default:
			   cout<<"\n invalid choice!";
		}
		cout<<"\n continue?";
		cin>>ans;
	}while(ans=='y'||ans=='Y');
}
