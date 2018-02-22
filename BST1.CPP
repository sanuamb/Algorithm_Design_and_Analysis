//Binary Search Tree
//Performing Search, Findind Height, Printing Leafnodes
#include<iostream.h>
#include<conio.h>
class node
{
	int data;
	node*lchild;
	node*rchild;
	friend class bst;
	friend class qnode;
};
class bst
{
	node*root;
	friend class queue;
	public:
	bst()
	{
		root=NULL;
	}
	node*create(node*);
	void router();
	void display(node*);
	void print_leaf(node*);
	node* search(node*);
	void height(node*);
};
class qnode
{
	node*p1;
	qnode*next;
	friend class queue;
};
class queue
{
	qnode*rear;
	qnode*front;
	public:
	queue()
	{
		rear=NULL;
		front=NULL;
	}
	void enq(node*);
	node*dq();
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
void queue::enq(node*ptr)
{
	qnode*temp;
	temp=new qnode;
	temp->p1=ptr;
	temp->next=NULL;
	if(front==NULL)
	{
		rear=temp;
		front=temp;
	}
	else
	{
		rear->next=temp;
		rear=temp;
	}
}
node*queue::dq()
{
	qnode*pt;
	pt=front;
	if(front==NULL)
	{
		return 0;
	}
	else
	{
		front=front->next;
		return(pt->p1);
	}
}
node*bst::create(node*root)
{
	node*ptr,*temp;
	char ans;
	do
	{
		temp=new node;
		temp->lchild=NULL;
		temp->rchild=NULL;
		cout<<"\nenter the data=";
		cin>>temp->data;
		if(root==NULL)
		{
			root=temp;
		}
		else
		{
			ptr=root;
		   while(ptr!=NULL)
		   {
			if(temp->data<ptr->data)
			{
				if(ptr->lchild==NULL)
				{
				      ptr->lchild=temp;
				      break;
				}
				else
				{
					ptr=ptr->lchild;
				}
			}
			else
			{
				if(temp->data>ptr->data)
				{
					if(ptr->rchild==NULL)
					{
						ptr->rchild=temp;
						break;
					}
					else
					{
						ptr=ptr->rchild;
					}

				}
			}
		    }
		}
		cout<<"\n add more nodes?"<<endl;
		cin>>ans;
	}while(ans=='y'||ans=='Y');
	return root;
}
void bst::display(node*t)
{
	node*ptr;
	queue q;
	ptr=t;
	q.enq(ptr);
	while(q.empty()!=1)
	{
		ptr=q.dq();
		cout<<ptr->data;
		if(ptr->lchild!=NULL)
		{
			q.enq(ptr->lchild);
		}
		if(ptr->rchild!=NULL)
		{
			q.enq(ptr->rchild);
		}
	}

}
void bst::print_leaf(node*t)
{
	queue q;
	node*ptr;
	ptr=t;
	q.enq(ptr);

	while(ptr!=NULL)
	{
		ptr=q.dq();
		if(ptr->lchild==NULL&&ptr->rchild==NULL)
		{
			cout<<ptr->data;
		}
		if(ptr->lchild!=NULL)
		{
			q.enq(ptr->lchild);
		}
		if(ptr->rchild!=NULL)
		{
			q.enq(ptr->rchild);
		}
	}

}
node* bst::search(node*t)
{
	node*ptr;
	int k;
	ptr=t;
	cout<<"\n enter the key to be searched=";
	cin>>k;
	while(ptr!=NULL)
      {
	if(k==ptr->data)
	{
		return (ptr);
	}
	else
	{
		if(k>ptr->data)
		{
			ptr=ptr->rchild;
		}
		else
		{
			if(k<ptr->data)
			{
				ptr=ptr->lchild;
			}
		}
	}
     }

}
void bst::height(node*t)
{
	node*ptr;
	queue q;
	int count=0;
	ptr=t;
	q.enq(ptr);
	q.enq(NULL);
	while(q.empty()!=1)
	{
		ptr=q.dq();
		if(ptr==NULL)
		{
			count++;

			if(q.empty()!=1)
			{
			q.enq(NULL);
			}
		}
		else
		{
			if(ptr->lchild!=NULL)
			{
			q.enq(ptr->lchild);
			}
			if(ptr->rchild!=NULL)
			{
				q.enq(ptr->rchild);
			}
		 }
	}
	cout<<"the height is:"<<count;
}

void bst::router()
{
	node*root2,*r1=NULL;
	int ch,c;
	char ans;
	do
	{
		cout<<"\n1.create\n2.display\n3.print leafnodes\n4.search\n5.height"<<endl;
		cout<<"\n enter the choice=";
		cin>>ch;
		switch(ch)
		{
			case 1:root2=create(root);
				break;
			case 2:display(root2);
				break;
			case 3:print_leaf(root2);
				break;
			case 4:r1=search(root2);
				cout<<"search found:";
				cout<<r1->data;
				break;
			case 5:height(root2);
				break;
		}
		cout<<"\n continue?"<<endl;
		cin>>ans;
	}while(ans=='y'||ans=='Y');
}
int main()
{
	clrscr();
	bst b1;
	b1.router();
	getch();
	return 0;
}
