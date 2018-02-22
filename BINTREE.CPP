//Binary Tree
// Pre-order, Post Order and In-order
#include<iostream.h>
#include<conio.h>
#include<iomanip.h>
class node
{
    int data;
    node*lchild;
    node*rchild;
    friend class bintree;
    friend class stacknode;


};
class bintree
{
	node*root;
	friend class stack;
	public:
	bintree()
	{
	  root=NULL;
	}
	node*create(node*);
	void router();
	void inorder(node*);
	void preorder(node*);
	void postorder(node*);
	void nonrec_in(node*);
	void nonrec_pre(node*);
	void nonrec_post(node*);
};
class stacknode
{
	node*p1;
	stacknode*next;
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
	void push(node*);
	node*pop();
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
node*bintree::create(node*root)
{
	node*temp;
	node*ptr;
	char ans;
	int ch;
    do
    {
	temp=new node;
	temp->lchild=NULL;
	temp->rchild=NULL;
	cout<<"\nenter the data:"<<endl;
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
		cout<<"\n1.lchild\n2.rchild";
		 cin>>ch;
		if(ch==1)
	      {

		if(ptr->lchild==NULL)
		{
			ptr->lchild=temp;
			break;
		}
		else
		{
			cout<<"\n left child exist"<<endl;
			cout<<ptr->lchild->data;
			ptr=ptr->lchild;
		}
	      }
	      else
	      {

		if(ptr->rchild==NULL)
		{
			ptr->rchild=temp;
			break;
		}
		else
		{
			cout<<"\n right child exist"<<endl;
			cout<<ptr->rchild->data;
			ptr=ptr->rchild;
		}
	      }
	    }
	}
	cout<<"\n add more nodes?";
	cin>>ans;
     }while(ans=='y'||ans=='Y');
     return root;
}
void bintree::inorder(node*t)
{
	if(t!=NULL)
	{
		inorder(t->lchild);
		cout<<t->data;
		inorder(t->rchild);
	}
}
void bintree::preorder(node*p)
{
	if(p!=NULL)
	{
		cout<<p->data;
		preorder(p->lchild);
		preorder(p->rchild);
	}
}
void bintree::postorder(node*f)
{
   if(f!=NULL)
   {
	postorder(f->lchild);
	postorder(f->rchild);
	cout<<f->data;
   }
}
void stack::push(node*pt)
{
	stacknode*temp;
	temp=new stacknode;
	temp->p1=pt;
	temp->next=NULL;
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
node*stack::pop()
{
	stacknode*ptr;
	ptr=top;
	top=top->next;
	ptr->next=NULL;
	return (ptr->p1);

}
void bintree::nonrec_in(node*t)
{
	stack s1;
	node*ptr;
	ptr=t;
	while(ptr!=NULL)
	{
		s1.push(ptr);
		ptr=ptr->lchild;
	}
	while(!s1.empty())
	{
		ptr=s1.pop();
		cout<<ptr->data;
		ptr=ptr->rchild;
		while(ptr!=NULL)
		{
			s1.push(ptr);
			ptr=ptr->lchild;
		}
	}
}
void bintree::nonrec_pre(node*t)
{
	stack s1;
	node*ptr;
	ptr=t;
	while(ptr!=NULL)
	{
		cout<<ptr->data;
		s1.push(ptr);
		ptr=ptr->lchild;
	}
	while(!s1.empty())
	{
		ptr=s1.pop();
		ptr=ptr->rchild;
		while(ptr!=NULL)
		{
			cout<<ptr->data;
			s1.push(ptr);
			ptr=ptr->lchild;
		}
	}
}
void bintree::nonrec_post(node*t)
{
	stack s1,s;
	node*ptr;
	ptr=t;
	while(ptr!=NULL)
	{
		s.push(ptr);
		s1.push(NULL);
		ptr=ptr->lchild;
	}
	while(!s.empty())
	{
		ptr=s.pop();
		if(s1.pop()==NULL)
		{
			s.push(ptr);
			s1.push(ptr);
			ptr=ptr->rchild;
			while(ptr!=NULL)
			{
			 s.push(ptr);
			 s1.push(NULL);
			 ptr=ptr->lchild;
			}
		}
		else
		{
			cout<<ptr->data;
		}

	}
}
void bintree::router()
{
	int ch;
	char ans;
	node*root2;
	do
	{
		cout<<"\nmenu:";
		cout<<setw(10)<<"\n1.create\n2.rec_inorder\n3.rec_preorder\n4.rec_postorder";
		cout<<	setw(10)<<"\n5.non_recinorder\n6.non_recpreorder\n7.non_recpostorder";
		cout<<"\n enter the choice:";
		cin>>ch;
		switch(ch)
		{
			case 1:root2=create(root);
				break;
			case 2:inorder(root2);
				break;
			case 3:preorder(root2);
				break;
			case 4:postorder(root2);
				break;
			case 5:nonrec_in(root2);
				break;
			case 6:nonrec_pre(root2);
				break;
			case 7:nonrec_post(root2);
				break;
			 default:cout<<"wrong choice!!";

		}
		cout<<"\n continue?";
		cin>>ans;
	}while(ans=='y'||ans=='Y');
}
int main()
{
	clrscr();
	bintree b;
	b.router();
	getch();
	return 0;
}
