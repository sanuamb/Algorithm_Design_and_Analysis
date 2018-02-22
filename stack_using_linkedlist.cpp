//Stack using linked list
#include<iostream>
using namespace std;
class Node
{
	int data;
	Node *link;
	friend class Stack;
};
class Stack
{
        Node *top;
        public:
        Stack();
        void push();
        void pop();
        void displayTop();
};
Stack::Stack()
{
        top=NULL;
}
void Stack::push()
{
	int m;
	Node *temp=new Node;
        cout<<"\n Enter element: ";
	cin>>m;
	temp->data=m;
	if(top==NULL)
		temp->link=NULL;
        else
              	temp->link=top;
	top=temp;
}
void Stack::pop()
{
	Node *temp=new Node;
	temp=top;
        if(top==NULL)
                cout<<"\n Stack Empty!!";
        else
        {
                top=top->link;
                cout<<"\n Element popped: "<<temp->data;
		temp->link=NULL;
		delete temp;
        }
}
void Stack::displayTop()
{
	cout<<"\n Top: "<<top->data;
}
int main()
{
        Stack obj;
        int ch;
        do
        {
                cout<<"\n Menu:\n\t1.Push\n\t2.Pop\n\t3.Display Top";
                cout<<"\n\t4.Exit\n Enter your choice: ";
                cin>>ch;
                switch(ch)
                {
                        case 1:obj.push();
                               break;
                        case 2:obj.pop();
                               break;
                        case 3:obj.displayTop();
                               break;
                        case 4:cout<<"\n Quitting Program!!!\n\tThanking You";
                               break;
                        default:cout<<"\n Wrong Choice!!";
                }
        }while(ch!=4);
        return 1;
}                                                                                    
