/*
Experiment No. 8C :  Direct Access File ,Collision handling throgh linear
		    probing with chaining and with replacement
*/
#include <iomanip.h>
#include <iostream.h>
#include <fstream.h>
#include <conio.h>
#include <string.h>
#define SIZE 10
#define h(x) x%SIZE
struct student
{
	int rollno;
	char name[20];
	float marks;
	int status; /* 0-record is active, 1-record is deleted */
	int link;  /*address of the next record */
};

class lin_probe
 {
   char table[30];
   fstream tab;
   student rec;//for reading/writing current record
   public:
	 lin_probe(char *a);//a[] gives the name of the data file
	 /* a bucket holds a single record */
	 void displayall();/*for displaying of records */
	 void insert(student rec1);
	 void  Delete(int rollno);
	 int  search(int rollno);
	 void display(int recno) // display a particular record
	   {
	       int i=recno;
	       tab.open(table,ios::binary  | ios::in | ios::nocreate);
	       tab.seekg(recno*sizeof(student),ios::beg);
	       tab.read((char*)&rec,sizeof(student));
	       if(rec.status==0)
		  {
		       cout<<"\n"<<i<<") "<<rec.rollno<<"   "<<rec.name<<"   "<<setprecision(2)<<rec.marks;
		       cout<<"   "<<rec.link;
		  }
	       else
		       cout<<"\n"<<i<<") ***** Empty  ********";
	       tab.close();
	   }
	 void read(int recno)
	   {
	       tab.open(table,ios::binary | ios::in  );
	       tab.seekg(recno*sizeof(student),ios::beg);
	       tab.read((char*) &rec,sizeof(student));
	       tab.close();
	   }
	  void write(int recno)
	   {
	       tab.open(table,ios::binary | ios::nocreate | ios::out | ios::in);
	       tab.seekp(recno*sizeof(student),ios::beg);
	       tab.write((char*)&rec,sizeof(student));
	       tab.close();
	   }

};
void lin_probe::lin_probe(char *a)//Create an empty table in the file
 {
	int i;
	strcpy(table,a);
	rec.status=1;rec.link=-1;
	tab.open(table,ios::binary | ios::out);
	tab.close();
	for(i=0;i<SIZE;i++)
		 write(i);

}
void lin_probe::displayall()
 {
	int i=1,n;
	cout<<"\n*********Data File*********\n";
	for(i=0;i<SIZE;i++)
		display(i);
 }

void lin_probe::insert(student rec1)
{
	int n,i,j,start,k,empty;
	rec1.status=0;
	rec1.link=-1;
	student rec2;
	start=h(rec1.rollno);/*hashed location*/
	read(start);
	//if the mapped location is empty store the record and finsh
	if(rec.status==1)
	   {    rec=rec1;
		write(start);
		return;
	   }
	//locate an empty location
	for(i=0;i<SIZE;i++)
	  {
		empty=(start+i)%SIZE;
		read(empty);
		if(rec.status==1)
		   break;
	  }
	if(i==SIZE)
	   {
		cout<<"\nTable is full...";
		return;
	   }

       //if the mapped location contains a synonym
	   j=start;
	   read(j);
       if(h(rec.rollno)==start)
	 {
		while(rec.link != -1)//go to the end of the chain
		   {
			j=rec.link;
			read(j);
		   }
		 rec.link=empty;
		 write(j);
		 rec=rec1;
		 write(empty);
		 return;
	 }
       //if the mapped location does not contain a synonym
       //  save the record
	rec2=rec;
       //locate its predecessor and modify the link
	j=h(rec2.rollno);
	read(j);
	while(rec.link != start)
	   {
		j=rec.link;
		read(j);
	   }
	rec.link=rec2.link;
	write(j);//predecessor modified to point to successor
	//locate the end of the link
	while(rec.link != -1)
	    {
		j=rec.link;
		read(j);
	    }
	rec.link=empty;
	write(j);
	rec=rec2;
	rec.link=-1;
	write(empty);
	rec=rec1;
	write(start);
  }




void lin_probe::Delete(int rollno)
{
	student rec1;
	int recno;
	int i,j,start,k;
	start=h(rollno); //Hashed location for the given rollno
	read(start);
	if(rec.status==1)
	    {
		cout<<"\nRecord does not exist";
		return;
	    }
	if(rec.rollno==rollno )//found at the beginning of the chain
		{
		     if(rec.link==-1)//only record in the chain
			{
				rec.status=1;
				write(start);
				return;
			}
		     else
			{  //move the second record to the beginning
				j=rec.link;
				read(j);
			       //	display(j);
				write(start);
			     //	cout<<"start="<<start<<" j="<<j;
			     //	getch();
				rec.status=1;
				write(j);
				return;
			 }
		  }
	else
	   {   //locate the predecessor
		 j=start;
		 read(j);
		 while(rec.rollno != rollno && rec.link !=-1)
		    {
		       k=j;  //k is the predecessor
		       j=rec.link;
		       read(j);
		    }
		 if(rec.rollno==rollno)
		    {   int nextlink=rec.link;
			rec.status=1;
			write(j);
			read(k);
			rec.link=nextlink;
			write(k);
		    }
		  else
			cout<<"\nNot found";
	  }
}
int lin_probe::search(int rollno)
{
	int start,i,j;
	start=h(rollno);
	read(start);
	if(h(rec.rollno)!=start) //first element is not a synonym
		return(-1);  //Not found
	j=start;
	while( j!=-1)
	  {
	    read(j);
	    if(rec.rollno==rollno)
		 return j;
	    j=rec.link;
	  }
       return -1;
}
void main()
 { lin_probe object("table.txt");
   int rollno,op,recno;
   student rec1;
   clrscr();
   do
     { cout<<"\n\n1)Print\n2)Insert\n3)Delete";
       cout<<"\n4)Search\n5)Quit";
       cout<<"\nEnter Your Choice:";
       cin>>op;
       switch(op)
	{ case 1: object.displayall();break;
	  case 2: cout<<"\nEnter a record to be inserted(roll no,name,marks) : ";
		  cin>>rec1.rollno>>rec1.name>>rec1.marks;
		  object.insert(rec1);
		  break;
	  case 3: cout<<"\nEnter the roll no.:";
		  cin>>rollno;
		  object.Delete(rollno);
		  break;
	 case 4: cout<<"\nEnter a roll no. : ";
		 cin>>rollno;
		 recno=object.search(rollno);
		 if(recno>=0)
		  { cout<<"\n Record No.:  "<<recno;
		    object.display(recno);
		  }
		else
		  cout<<"\nRecord Not Found ";
		break;
       }
     }while(op!=5);
 }

/*

OUTPUT:

1)Print
2)Insert
3)Delete
4)Search
5)Quit
Enter Your Choice:2

Enter a record to be inserted(roll no,name,marks) : 101 Nisha 98


1)Print
2)Insert
3)Delete
4)Search
5)Quit
Enter Your Choice:2

Enter a record to be inserted(roll no,name,marks) : 155 Amit 67


1)Print
2)Insert
3)Delete
4)Search
5)Quit
Enter Your Choice:2

Enter a record to be inserted(roll no,name,marks) : 145 Sonal 87


1)Print
2)Insert
3)Delete
4)Search
5)Quit
Enter Your Choice:1
*********Data File*********

0) ***** Empty  ********
1) 101   Nisha   98   -1
2) ***** Empty  ********
3) ***** Empty  ********
4) ***** Empty  ********
5) 155   Amit   67   6
6) 145   Sonal   87   -1
7) ***** Empty  ********
8) ***** Empty  ********
9) ***** Empty  ********

1)Print
2)Insert
3)Delete
4)Search
5)Quit
Enter Your Choice:4

Enter a roll no. : 155

 Record No.:  5
5) 155   Amit   67   6

1)Print
2)Insert
3)Delete
4)Search
5)Quit
Enter Your Choice:3

Enter the roll no.:101


1)Print
2)Insert
3)Delete
4)Search
5)Quit
Enter Your Choice:1
*********Data File*********

0) ***** Empty  ********
1) ***** Empty  ********
2) ***** Empty  ********
3) ***** Empty  ********
4) ***** Empty  ********
5) 155   Amit   67   6
6) 145   Sonal   87   -1
7) ***** Empty  ********
8) ***** Empty  ********
9) ***** Empty  ********

1)Print
2)Insert
3)Delete
4)Search
5)Quit
Enter Your Choice:5

*/