/*
Experiment No. 8B :  Direct Access File ,Collision handling throgh linear
		    probing with chaining and without replacement
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
		       cout<<"\n"<<i<<") "<<rec.rollno<<"  "<<rec.name<<"  "<<setprecision(2)<<rec.marks;
		       cout<<" "<<rec.link;
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
	int n,i,j,start,k;
	rec1.status=0;
	rec1.link=-1;
	start=h(rec1.rollno);/*hashed location*/
   //locate the begining of the chain
	for(i=0;i<SIZE;i++)
	  {
		j=(start+i)%SIZE;
		read(j);
		if(rec.status==0 && h(rec.rollno)==start)
		   break;
	  }
	if(i<10)
	  {
	    //chain found,goto the end of chain
	    while(rec.link!=-1)
	      {
		j=rec.link;
		read(j);
	      }
	    //find an empty location
	    for(i=0;i<SIZE;i++)
	       {
		  k=(start+i)%SIZE;
		  read(k);
		 if(rec.status==1)  //Empty location is found
		    {
			rec=rec1;
			write(k);
			read(j);
			rec.link=k;
			write(j);
			return;
		    }
	       }
	    cout<<"\nTable is full ";
	}
     else
       {  //first element of the chain
	  for(i=0;i<SIZE;i++)//find an empty location
	       {
		  k=(start+i)%SIZE;
		  read(k);
		 if(rec.status==1)
		    {
			rec=rec1;
			write(k);
			return;
		    }
	       }
	    cout<<"\nTable is full ";
	}

}


void lin_probe::Delete(int rollno)
{
	student rec1;
	int recno;
	int i,j,start,k;
	start=h(rollno); //Hashed location for the given rollno
	//locate the beginnning of the chain
	for(i=0;i<SIZE;i++)
	  {
		j=(start+i)%SIZE;
		read(j);
		if(rec.status==0 && h(rec.rollno)==start)//synonim found
		   break;
	  }
	if(i<10)//chain exist
	 {
	     if(rec.rollno==rollno )//found at the beginning of the chain
		{
			rec.status=1;
			write(j);
		}
	     else
		{
			//locate the predecessor
			while(rec.rollno !=rollno && rec.link!=-1)
			   {
				k=j;
				j=rec.link;
				read(j);
			   }

			if(rec.rollno==rollno)
			   {   rec.status=1;
			       write(j);
			       int nextlink=rec.link;
			       read(k);
			       rec.link=nextlink;
			       write(k);
			   }
			else
				cout<<"\nElement not found";
	       }
	 }
       else
		cout<<"\nRecord Not Found ";
}
int lin_probe::search(int rollno)
{
	int start,i,j;
	start=h(rollno);
	for(i=0;i<SIZE;i++)
	  {
		j=(start+i)%SIZE;
		read(j);
		if(rec.status==0 && h(rec.rollno)==start)//synonim found
		   break;
	  }
	if(i<10)//chain exist
	 {
			while(rec.rollno !=rollno && rec.link!=-1)
			   {
				j=rec.link;
				read(j);
			   }

			if(rec.rollno==rollno)
				return(j);

			else
				return -1;
	 }
       else
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

Enter a record to be inserted(roll no,name,marks) : 155 Nilesh 76


1)Print
2)Insert
3)Delete
4)Search
5)Quit
Enter Your Choice:2

Enter a record to be inserted(roll no,name,marks) : 45 Komal 88


1)Print
2)Insert
3)Delete
4)Search
5)Quit
Enter Your Choice:2

Enter a record to be inserted(roll no,name,marks) : 90 Ashish 70


1)Print
2)Insert
3)Delete
4)Search
5)Quit
Enter Your Choice:4

Enter a roll no. : 45

 Record No.:  6
6) 45  Komal  88 -1

1)Print
2)Insert
3)Delete
4)Search
5)Quit
Enter Your Choice:1
*********Data File*********

0) 90  Ashish  70 -1
1) ***** Empty  ********
2) ***** Empty  ********
3) ***** Empty  ********
4) ***** Empty  ********
5) 155  Nilesh  76 6
6) 45  Komal  88 -1
7) ***** Empty  ********
8) ***** Empty  ********
9) ***** Empty  ********

1)Print
2)Insert
3)Delete
4)Search
5)Quit
Enter Your Choice:3

Enter the roll no.:45


1)Print
2)Insert
3)Delete
4)Search
5)Quit
Enter Your Choice:1

*********Data File*********

0) 90  Ashish  70 -1
1) ***** Empty  ********
2) ***** Empty  ********
3) ***** Empty  ********
4) ***** Empty  ********
5) 155  Nilesh  76 -1
6) ***** Empty  ********
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