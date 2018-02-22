//Binary Search Tree
//Operations Performed: Print tree level wise, Mirror and Copy
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
	void print_level(node*);
	node*mirror(node*);
	node*copy(node*);

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
void bst::print_level(node*t)
{
	node*ptr;
	queue q;
	ptr=t;
	q.enq(ptr);
	q.enq(NULL);
	while(q.empty()!=1)
	{
		ptr=q.dq();
		if(ptr==NULL)
		{
			cout<<"\n\n";
			if(q.empty()!=1)
			{
				q.enq(NULL);
			}
		}
		else
		{
			cout<<ptr->data<<"\t";
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
}
node*bst::mirror(node*t)
{
	node*temp;
       if(t!=NULL)
      {
	temp=new node;
	temp->data=t->data;
	temp->lchild=mirror(t->rchild);
	temp->rchild=mirror(t->lchild);
	return (temp);
     }
     else
     {
	return 0;
     }
}
node*bst::copy(node*t)
{
	node*temp;
	if(t!=NULL)
	{
		temp=new node;
		temp->data=t->data;
		temp->lchild=copy(t->lchild);
		temp->rchild=copy(t->rchild);
		return temp;
	}
	else
	{
		return 0;
	}
}
void bst::router()
{
	node*root2,*root1;
	int ch,c;
	char ans;
	do
	{
		cout<<"\n1.create\n2.printlevelwise\n3.mirror\n4.copy"<<endl;
		cout<<"\n enter the choice=";
		cin>>ch;
		switch(ch)
		{
			case 1:root2=create(root);
				break;
			case 2:print_level(root2);
				break;
			case 3:root1=mirror(root2);
				print_level(root1);
				break;
			case 4:root1=copy(root2);
				print_level(root1);
				break;
			default:cout<<"invalid choice";

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
