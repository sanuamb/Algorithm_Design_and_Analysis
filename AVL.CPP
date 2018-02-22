//AVL trees
#include<iostream.h>
class node
{
	int data;
	int height;
	node*lchild;
	node*rchild;
	friend class avl;
	friend class qnode;
};
class avl
{
	node*root;
	public:
	avl()
	{
		root=NULL;
	}
	node* insert1(int,node*);
	node* insert(node*);
	void router();
	void inorder(node*);
	int hei(node*);
	int bf(node*);
	node* ll(node*);
	node*lr(node*);
	node*rr(node*);
	node*rl(node*);
	void preorder(node*);
	void postorder(node*);
	void display(node*);
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
	qnode*ptr;
	ptr=front;
	if(front==NULL)
	{
		return 0;
	}
	front=front->next;
	return (ptr->p1);
}
void avl::display(node*t)
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
		
			cout<<"\n";
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
node* avl::insert(node*root)
{
	int data1;
	char ans;
     do
     {
	cout<<"\n enter the data:";
	cin>>data1;
	root=insert1(data1,root);
	cout<<"\n add more nodes?";
	cin>>ans;
     }while(ans=='y'||ans=='Y');
   return root;
}
node*avl::insert1(int data1,node*root)
{
	int h,b;
	node*ptr,*temp;
	temp=new node;
	temp->lchild=NULL;
	temp->rchild=NULL;
	if(root==NULL)
	{
		root=temp;
		root->data=data1;
	}
	else
	{
		
		if(data1<root->data)
		{
			root->lchild=insert1(data1,root->lchild);
			b=bf(root);
			if(b==2)
			{
				if(data1<root->lchild->data)
				{

				 root=ll(root);
				}
				else
				{
					root=lr(root);
				}

			}
		}
		else
		{
			if(data1>root->data)
		       {
			 root->rchild=insert1(data1,root->rchild);
			 b=bf(root);
			 if(b==(-2))
			 {
				if(data1>root->rchild->data)
				{
					root=rr(root);
				}
				else
				{
					root=rl(root);
				}
			 }
		       }
		}
		}
	root->height=hei(root);



   return root;


}
node*avl::rl(node*temp1)
{
	temp1->rchild=ll(temp1->rchild);
	temp1=rr(temp1);
	return temp1;
}
node*avl::rr(node*temp1)
{
	node*temp2;
	int h1,h2;
	temp2=temp1->rchild;
	temp1->rchild=temp2->lchild;
	temp2->lchild=temp1;
	temp1->height=hei(temp1);
	temp2->height=hei(temp2);
	return temp2;
}
node*avl::lr(node*temp1)
{
	temp1->lchild=rr(temp1->lchild);
	temp1=ll(temp1);
	return temp1;
}
node* avl::ll(node*temp1)
{
	node*temp2;
	int h1,h2;
	temp2=temp1->lchild;
	temp1->lchild=temp2->rchild;
	temp2->rchild=temp1;
	temp1->height=hei(temp1);
	temp2->height=hei(temp2);
	return temp2;
}
int avl::bf(node*root)
{

	int lh,rh,bf;
	if(root==NULL)
	{
		return 0;
	}


		if(root->lchild==NULL)
		{
			lh=0;
		}
		else
		{
			lh=root->lchild->height+1;
		}
		if(root->rchild==NULL)
		{
			rh=0;
		}
		else
		{
			rh=root->rchild->height+1;
		}
        
	bf=(lh-rh);
	return bf;
}

int avl::hei(node*root)
{
	int lh,rh;
	if(root==NULL)
	{
		return 0;
	}
		if(root->lchild==NULL)
		{
			lh=0;
		}
		else
		{
			lh=root->lchild->height+1;
		}
		if(root->rchild==NULL)
		{
			rh=0;
		}
		else
		{
			rh=root->rchild->height+1;
		}
	
	if(lh>rh)
	{
		return lh;
	}
	else
	{
		return rh;
	}
}
void avl::inorder(node*t)
{
	if(t!=NULL)
	{
		inorder(t->lchild);
		cout<<t->data<<"\t";
		inorder(t->rchild);
	}
}
void avl::preorder(node*t)
{
	if(t!=NULL)
	{
		cout<<t->data<<"\t";
		preorder(t->lchild);
		preorder(t->rchild);
	}
}
void avl::postorder(node*t)
{
	if(t!=NULL)
	{
		postorder(t->lchild);
		postorder(t->rchild);
		cout<<t->data<<"\t";
	}
}
void avl::router()
{
	int ch;
	node*root2;
	char ans;
	do
	{
		cout<<"\n1.insert\n2.display_levelwise\n3.inorder\n4.preorder\n5.postorder";
		cout<<"\nenter the choice:";
		cin>>ch;
		switch(ch)
		{
			case 1:root2=insert(root);
				break;
			case 2:display(root2);
				break;
			case 3:inorder(root2);
				break;
			case 4:preorder(root2);
				break;
			case 5:postorder(root2);
				break;
			default:cout<<"invalid entry!";

		}
	 cout<<"\n continue?";
	cin>>ans;
	}while(ans=='y'||ans=='Y');
}
int main()
{
	avl a1;
	a1.router();
	return 0;
}
