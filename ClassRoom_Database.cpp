/*
Project Title: Classroom Database Management System
Version: 1.0
Developed By: M.Harine, Osho Sharma
School : Delhi Public School, RK Puram
*/
#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<iomanip.h>
#include<string.h>
#include<ctype.h>

//==================================================================
//                       FUNCTION PROTOTYPES
//==================================================================
void CreateClass();
void DelClass();
void ChooseClass();
int menu();
//==================================================================
//                           DATA OBJECTS
struct Student
{
  char Name[20], email[100], admno[10];
  int S1, S2, S3, S4, S5;
  float Agg;
};
//------------------------------------------------------------------
//                               CLASS
//------------------------------------------------------------------

class Class
{
   int ID, Total;
   Student S[30];
  public:
   Class() { Total=0; }
   Class(int I) { ID=I; Total=0; }
   int retID() { return ID; }
   void AddS();
   void viewS();
   void delS();
};
//------------------------------------------------------------------//                       class member insertion
//------------------------------------------------------------------
void Class::AddS()
{
  int i=Total;
  char ch;
  do{
  cout<<"Enter student details: \n";
  cout<<"Name: "; gets(S[i].Name);
  cout<<"Roll number: "<<i+1<<endl;
  cout<<"Admission number: "; gets(S[i].admno);
  cout<<"E-mail id: "; gets(S[i].email);
  cout<<"Enter marks [out of 100] for: "<<endl;
  cout<<"\tEnglish: "; cin>>S[i].S1;
  cout<<"\tMath: "; cin>>S[i].S2;
  cout<<"\tScience: "; cin>>S[i].S3;
  cout<<"\tSocial Science: "; cin>>S[i].S4;
  cout<<"\tComputer Science: "; cin>>S[i].S5;
  cout<<endl;
  S[i].Agg=(S[i].S1+S[i].S2+S[i].S3+S[i].S4+S[i].S5)/5;
  cout<<endl<<"Create more entries? [y/n] ";
  cin>>ch; ch=toupper(ch);
  i++;
  }while(ch=='Y');
  Total=i;
}
//------------------------------------------------------------------
//                        class member display
//------------------------------------------------------------------
void Class::viewS()
{
  int i=0;
  do{
  cout<<"Student details: \n";
  cout<<"Name: "; puts(S[i].Name);
  cout<<"Admission number: "; puts(S[i].admno);
  cout<<"E-mail id: "; puts(S[i].email);
  cout<<"Subject-wise marks [out of 100]: "<<endl;
  cout<<"\tEnglish: "<<S[i].S1<<endl;
  cout<<"\tMath: "<<S[i].S2<<endl;
  cout<<"\tScience: "<<S[i].S3<<endl;
  cout<<"\tSocial Science: "<<S[i].S4<<endl;
  cout<<"\tComputer Science: "<<S[i].S5<<"\n";
  cout<<"Overall % "<<S[i].Agg<<endl;
  cout<<endl;
  i++;
  }while(i<Total);
}
//------------------------------------------------------------------
//                     class member deletion
//------------------------------------------------------------------
void Class::delS()
{
  cout<<"Enter student roll number to delete: ";
  int i;
  cin>>i;
  for(int a=i-1; a<=Total; a++)
  {
    strcpy(S[a].Name, S[a+1].Name);
    strcpy(S[a].email, S[a+1].email);
    strcpy(S[a].admno, S[a+1].admno);
    S[a].S1=S[a+1].S1;
    S[a].S2=S[a+1].S2;
    S[a].S3=S[a+1].S3;
    S[a].S4=S[a+1].S4;
    S[a].S5=S[a+1].S5;
    S[a].Agg=S[a+1].Agg;
  }
  Total--;
  cout<<"Deleted~"<<endl;
}


//==================================================================
//                             CLASS CREATION
//==================================================================
//------------------------------------------------------------------
//                   temporary file creation/deletion
//------------------------------------------------------------------void Dummy(char key)
{
	fstream F1("Users.dat", ios::binary|ios::in);
	fstream F2("Dummy.dat", ios::binary|ios::out);
	Class C;
	if(key=='A')
	{
	  while(F1.read((char *)&C, sizeof(C)))
	    { F2.write((char *)&C, sizeof(C)); }
	}
	else if(key=='D')
	{
	  remove("Dummy.dat");
	}
	F1.close();
	F2.close();
}

//------------------------------------------------------------------
void CreateClass()
{
  fstream F("Users.dat", ios::binary|ios::app);
  Dummy('A');
  int id, ch; Class x;
  fstream D("Dummy.dat", ios::binary|ios::in);
  do{
    ch=0;
    cout<<"Enter class id: "; cin>>id;
    D.seekp(0*sizeof(x));
    while(D.read((char *)&x, sizeof(x))&&(ch==0))
    {
      if(x.retID()==id)
      {
	cout<<"ID taken! Choose another or delete previous"<<endl;
	ch++;
      }
    }
  }while(ch==1);
  Class C(id);
  C.AddS();
  F.write((char *)&C, sizeof(C));
  D.close();
  Dummy('D');
  F.close();
}
//==================================================================
//                         CLASS MODIFICATION
//==================================================================
void ChooseClass()
{
  fstream F1("Users.dat", ios::binary|ios::in);
  fstream F2("Temp.dat", ios::binary|ios::out);
  cout<<"Enter class id: ";
  int id, ch, Found=0; cin>>id;
  Class C;
  while((F1.read((char *)&C, sizeof(C))))
  {
    if(C.retID()==id)
    {
	Found++;
	cout<<"Select an option: "<<endl;
	cout<<"\t[1] Add student details"<<endl;
	cout<<"\t[2] Delete student details"<<endl;
	cout<<"\t[3] View class details:"<<endl;
	cin>>ch;
	switch (ch)
	{
	  case 1: clrscr();
		C.AddS();
		F2.write((char*)&C, sizeof(C));
		getch();
		break;
	  case 2: C.delS();
		F2.write((char *)&C, sizeof(C));
		getch();
		break;
	  case 3: C.viewS();
		F2.write((char*)&C, sizeof(C));
		getch();
	}
    }
    else { F2.write((char*)&C, sizeof(C)); }
  }
  if(Found==0)
  { cout<<"class not found!"; }
  F1.close();
  F2.close();
  remove("Users.dat");
  rename("Temp.dat", "Users.dat");
}
//==================================================================
//                            CLASS DELETION
//==================================================================
void DelClass()
{
  fstream F1("Users.dat", ios::binary|ios::in);
  fstream F2("Temp.dat", ios::binary|ios::out);
  Class C;
  int c;
  cout<<"Enter class ID to be deleted: "; cin>>c;
  while(F1.read((char*)&C, sizeof(C)))
  {
    if(C.retID()!=c)
    {
      F2.write((char*)&C, sizeof(C));
    }
  }
  F1.close();
  F2.close();
  remove("Users.dat");
  rename("Temp.dat", "Users.dat");
}
//==================================================================
//                             MAIN MENU
//==================================================================int menu()
{
  clrscr();
  int ch;
  cout<<"\n\n\n";
  cout<<setw(5)<<" "<<char(201);
  for(int i=0; i<58; i++)
  { cout<<char(205); }
  cout<<char(187);
  cout<<endl;
  cout<<setw(5)<<" "<<char(186);
  cout<<setw(2)<<" "<<char(4);
  cout<<"   Welcome to student database management system "<<char(4);
  cout<<setw(5)<<" "<<char(186);
  cout<<setw(20)<<" "<<char(186);
  cout<<setw(58)<<" "<<char(186);
  cout<<"\n";
  cout<<setw(5)<<" "<<char(186);
  cout<<setw(19)<<"[1] Select class";
  cout<<setw(39)<<" "<<char(186)<<"\n";
  cout<<setw(5)<<" "<<char(186);
  cout<<setw(19)<<"[2] Create class";
  cout<<setw(39)<<" "<<char(186);
  cout<<"\n";
  cout<<setw(5)<<" "<<char(186);
  cout<<setw(19)<<"[3] Delete class";
  cout<<setw(39)<<" "<<char(186);
  cout<<"\n";
  cout<<setw(5)<<" "<<char(186);
  cout<<setw(11)<<"[4] Exit";
  cout<<setw(47)<<" "<<char(186);
  cout<<"\n";
  cout<<setw(5)<<" "<<char(200);
  for(i=0; i<58; i++)
  {
    cout<<char(205);
  }
  cout<<char(188);
  cout<<endl<<endl<<endl;
  cout<<"Enter your choice: ";
  cin>>ch;
  switch (ch)
  {
    case 1: clrscr();
	ChooseClass();
	getch();
	break;
    case 2: clrscr();
	CreateClass();
	getch();
	break;
    case 3: clrscr();
	DelClass();
	getch();
	break;
    case 4: return 0;
  }
}
//==================================================================
//                                MAIN
//==================================================================
void main()
{
  clrscr();
  int a;
  do{
  a=menu();
  }while(a!=0);
}
