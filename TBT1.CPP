//Threaded Binary Trees
#include<iostream.h>
//using namespace std;
class node
{
	int data;
	int lt;
	int rt;
	node*rchild;
	node*lchild;
	friend class tbt;
};
class tbt
{
	node*root;
	node*head;
	public:
	void create();
	void inorder();
	void router();
	void preorder();
	void postorder();

};
void tbt::create()
{	node*ptr;
	node*temp;
	char ans;
		head=new node;
		head->rt=0;
		head->rchild=head;
		head->lt=0;
		head->lchild=root;
		root=new node;
		cout<<"\n enter the data for the root:";
		cin>>root->data;
		root->lt=1;
		root->rt=1;
		root->rchild=head;
		root->lchild=head;

	ptr=root;
	do
	{
		temp=new node;
		cout<<"\n enter the data for children:";
		cin>>temp->data;
		temp->rt=1;
		temp->lt=1;
		temp->rchild=head;
		temp->lchild=head;
		while(ptr!=head)
            {
		if(temp->data<ptr->data)
		{
			if(ptr->lt==1)
			{
				temp->lchild=ptr->lchild;
				ptr->lt=0;
				ptr->lchild=temp;
				temp->rchild=ptr;
				break;
			}
			else
			{
				ptr=ptr->lchild;
			}
			
		}
		if(temp->data>ptr->data)
		{
			if(ptr->rt==1)
			{
				temp->rchild=ptr->rchild;
				ptr->rt=0;
				ptr->rchild=temp;
				temp->lchild=ptr;
				break;
			}
			else
			{
				ptr=ptr->rchild;
			}
		}
	   }
		cout<<"\n add more nodes?";
		cin>>ans;
	
	}while(ans=='y'||ans=='Y');

	
}
void tbt::inorder()
{
	node*ptr;
	int count=0;
	ptr=root;
    while(ptr!=head)
   {
	while(ptr->lt==0)
	{
		ptr=ptr->lchild;
	}
	if(ptr!=head)
	{
		//cout<<ptr->data<<"\t";
		count++;
	}
	while(ptr->rt==1)
	{
	       //	cout<<ptr->data;
		ptr=ptr->rchild;
	}

	ptr=ptr->rchild;
   }
   cout<<count;
}
void tbt::preorder()
{
	node*ptr;
	ptr=root;
	while(ptr!=head)
	{
		
		while(ptr->lt==0)
		{
			cout<<ptr->data<<"\t";
			ptr=ptr->lchild;
		}
		if(ptr!=head)
                {
                        cout<<ptr->data<<"\t";
                }
		while(ptr->rt==1)
		{
			ptr=ptr->rchild;
		}
	
		ptr=ptr->rchild;
	}
}
void tbt::postorder()
{
	node*ptr;
	int arr[10];
	int i=0,count=0;
	ptr=root;
	while(ptr!=head)
	{
		while(ptr->rt==0)
		{
			arr[i]=ptr->data;
			ptr=ptr->rchild;
			i++;
			count++;
		}
		arr[i]=ptr->data;
		i++;
		count++;
		while(ptr->lt==1)
		{
			ptr=ptr->lchild;
		}
		if(ptr!=head)
		{
			ptr=ptr->lchild;
		}
		
	}
	for(i=count-1;i>=0;i--)
	{
		cout<<arr[i]<<"\t";
	}

	
}

void tbt::router()
{
	node*root1;
	int ch;
	char ans;
	do
	{
		cout<<"\n1.create\n2.inorder\n3.preorder\n4.postorder";
		cout<<"\n enter the choice=";
		cin>>ch;
		switch(ch)
		{
			case 1:create();
				break;
			case 2:inorder();
				break;
			case 3:preorder();
				break;
			case 4:postorder();
				break;
			default:cout<<"\ninvalid choice";

		}
		cout<<"\n continue?";
		cin>>ans;
	}while(ans=='y'||ans=='Y');
}
int main()
{
	tbt t1;
	t1.router();
	return 0;
}
