//******************************************************************
//  Project	:	Banking System
//  Version	:	1.0
//******************************************************************

//******************************************************************
//  INCLUDED HEADER FILES
//******************************************************************
#include <fstream.h>
#include <string.h>
#include <conio.h>
#include <iomanip.h>
#include <stdio.h>
#include <dos.h>

const char VL=179,HL=196,TL=218,TR=191,BL=192,BR=217;

//******************************************************************
//--- MAIN CLASS USED IN THE PROGRAM ------------------
//******************************************************************

class Customer
{
  long Acno;
  char Name[20],Add[80],Mobile[15],Email[25];
  float Balance;
  float TrAmt;
  char  Type;//D:Deposit   W:Withdraw
  char  Date[12];//DD-MM-YYYY
	public:
  Customer();
  void  New(int Ano);
  void  Modify();
  void  Disp();
  void  Disp2(int);
  int   Withdraw(float Amt);
  void  Deposit(float Amt);
  long  RAcno(){return Acno;}
  int   CompareDate(char DT[]){return strcmp(Date,DT);}
  float RBal(){return Balance;}
};

//******************************************************************
//---MAIN FUNCTION PROTOTYPES-------------------------------
//******************************************************************

void help();
void NewAccount();
void DispAccount();
void SearchAccount();
void ModifyAccount();
void DepositAccount();
void WithdrawAccount();
void PassBook();
void DispTrans();

//******************************************************************
//---Screen Formatting Utility Functions---------------------
//******************************************************************

void Color(int TC,int BC);
void DispCh(int C,int R,char CH); //to display a char on a particular loc
void DispCh(int C,int R,char CH[]);//to display a string on a particular loc
void BOX(int C1,int R1,int C2,int R2);//to display a rectangular box
int  VMenu(int C,int R,char M[][20],int N);
int  HMenu(int C,int R,char M[][20],int N);
//----------------------------------------------------------

//*****************************************************************
// THIS IS MAIN FUNCTION CALLING MAIN MENU FUNCTIONS
//*****************************************************************

void main()
{ help();
  clrscr();
  char Menu[][20]  ={"Customer",
		     "Transact",
		     "Report  ",
		     "Help  ",
		     "Exit    "};
  char VMenu1[][20]={"New Account ",
		     "Display All ",
		     "Search Acc  ",
		     "Modify Acc  ",
		     "Back to Menu"};
  char VMenu2[][20]={"Deposit    ",
		     "Withdraw    ",
		     "Back to Menu"};
  char VMenu3[][20]={"Passbook    ",
		     "Statement   ",
		     "Back to Menu"};
  int MN,SMN,GetOut=0;
  do
  {
    clrscr();
    MN=HMenu(1,1,Menu,5);
    switch(MN)
    {
      case 0:SMN=VMenu(1,2,VMenu1,5);
	     switch(SMN)
	     {
	      case 0:NewAccount();   break;
	      case 1:DispAccount();  break;
	      case 2:SearchAccount();break;
	      case 3:ModifyAccount();break;
	      case 4:;
	     }
	     break;

      case 1:SMN=VMenu(11,2,VMenu2,3);
	     switch(SMN)
	     {
	      case 0:DepositAccount(); break;
	      case 1:WithdrawAccount(); break;
	      case 2:;
	     }

	     break;

      case 2:SMN=VMenu(21,2,VMenu3,3);
	     switch(SMN)
	     {
	      case 0:PassBook();  break;
	      case 1:DispTrans(); break;
	      case 2:;
	     }
	     break;

      case 3: help(); break;

      case 4:GetOut=1;
    }
  }
  while (!GetOut);
  getch();
}

//*****************************************************************
//---Main Functions of class Customer                       ---------------------
//*****************************************************************

void ValidDate(char DT[])
{
  int Invalid;
  do
  {
    Invalid=0;
    DispCh(7,15,"Date [DD-MM-YYYY] :                   ");
    DispCh(7,15,"Date [DD-MM-YYYY] :");gets(DT);
    if (strlen(DT)!=10)
      Invalid=1;
    if (DT[2]!='-' || DT[5]!='-')
      Invalid=1;
    if (DT[0]>'3' && DT[0]<'0')
      Invalid=1;
    if (DT[1]>'9' && DT[1]<'0')
      Invalid=1;
    if (DT[3]>'1' && DT[3]<'0')
      Invalid=1;
    if (DT[4]>'9' && DT[4]<'0')
      Invalid=1;
    if (DT[6]!='2' || DT[7]!='0')
      Invalid=1;
  }
  while (Invalid);
}

Customer::Customer()
{
  Acno=1000;
  Name[0]='\0';
  Add[0]='\0';
  Mobile[0]='\0';
  Email[0]='\0';
  Balance=0;
  TrAmt=0;
  Type='*';
  strcpy(Date,"DD-MM-YYYY");
}

void  Customer::New(int Ano)
{
  BOX(5,5,75,20);
  Acno=Ano+1;
  DispCh(7,7 ,"Account Number    :");cout<<Acno;
  DispCh(7,8 ,"Name              :");gets(Name);
  DispCh(7,9 ,"Address           :");gets(Add);
  DispCh(7,10,"Mobile            :");gets(Mobile);
  DispCh(7,11,"Email             :");gets(Email);
  DispCh(7,12,"Amount to Deposit:");cin>>TrAmt;
  Balance=TrAmt;
  DispCh(7,13,"Balance           :");cout<<Balance;
  Type='D';
  DispCh(7,14,"Transaction Type  :");cout<<"Deposit";
  ValidDate(Date);
}

void  Customer::Modify()
{
  BOX(5,5,75,20); char Q;
  DispCh(7,7 ,"Account Number    :");cout<<Acno;
  DispCh(7,8 ,"Name              :");cout<<Name;
  DispCh(7,9 ,"Address           :");cout<<Add;
  DispCh(60,9,"Modify(Y/N)");cin>>Q;
  if(Q=='Y')
  {
    DispCh(7,9 ,"Address           :                                 ");
    DispCh(7,9 ,"Address           :");gets(Add);
  }
  DispCh(7,10,"Mobile            :");cout<<Mobile;
  DispCh(60,10,"Modify(Y/N)");cin>>Q;
  if(Q=='Y')
  {
    DispCh(7,10,"Mobile            :                                 ");
    DispCh(7,10,"Mobile            :");gets(Mobile);
  }
  DispCh(7,11,"Email             :");cout<<Email;
  DispCh(60,11,"Modify(Y/N)");cin>>Q;
  if(Q=='Y')
  {
    DispCh(7,11,"Email             :                                 ");
    DispCh(7,11,"Email             :");gets(Email);
  }
}

void  Customer::Disp()
{
  BOX(5,5,75,20);
  DispCh(7,7 ,"Account Number    :");cout<<Acno;
  DispCh(7,8 ,"Name              :");cout<<Name;
  DispCh(7,9 ,"Address           :");cout<<Add;
  DispCh(7,10,"Mobile            :");cout<<Mobile;
  DispCh(7,11,"Email             :");cout<<Email;
  DispCh(7,12,"Amount to Deposit:");cout<<TrAmt;
  DispCh(7,13,"Balance           :");cout<<Balance;
  DispCh(7,14,"Transaction Type  :");
				 cout<<(Type=='D')?"Deposit":"Withdrawal";
  DispCh(7,14,"Transaction Date  :");cout<<Date;
}

void  Customer::Disp2(int Row)
{
  DispCh(1,Row,">>");
  cout<<setw(7)<<Acno<<setw(22)<<Name
	     <<setw(8)<<TrAmt<<"   "<<Type<<"   "<<setw(12)<<Balance
	     <<setw(12)<<Date;
}

int   Customer::Withdraw(float Amt)
{
  if((Balance-Amt)>5000)
  {
    DispCh(7,7 ,"Account Number    :");cout<<Acno;
    DispCh(7,8 ,"Name              :");cout<<Name;
    DispCh(7,9 ,"Address           :");cout<<Add;
    DispCh(7,10,"Mobile            :");cout<<Mobile;
    DispCh(7,11,"Email             :");cout<<Email;
    ValidDate(Date);
    Balance-=Amt;
    TrAmt=Amt;
    Type='W';
    DispCh(7,12,"Amount Withdrawn  :");cout<<TrAmt;
    DispCh(7,13,"Balance           :");cout<<Balance;
    DispCh(7,14,"Transaction Type  :");cout<<"Withdrawl";
    return 1;
  }
  else
    return 0;
}

void  Customer::Deposit(float Amt)
{
  DispCh(7,7 ,"Account Number    :");cout<<Acno;
  DispCh(7,8 ,"Name              :");cout<<Name;
  DispCh(7,9 ,"Address           :");cout<<Add;
  DispCh(7,10,"Mobile            :");cout<<Mobile;
  DispCh(7,11,"Email             :");cout<<Email;
  ValidDate(Date);
  Balance+=Amt;
  TrAmt=Amt;
  Type='D';
  DispCh(7,12,"Amount Deposited  :");cout<<TrAmt;
  DispCh(7,13,"Balance           :");cout<<Balance;
  DispCh(7,14,"Transaction Type  :");cout<<"Deposit";
}

//*****************************************************************
//---Main Function Definitions          ---------------------
//*****************************************************************

void help()
{
clrscr() ;
   textcolor(LIGHTGRAY);
   delay(10) ;
   gotoxy(10,6); cout <<"In this Project you can keep record of daily banking" ;
   delay(10) ;
   gotoxy(10,7); cout<<"transactions." ;
   delay(10) ;
   gotoxy(10,9); cout <<"   This program is capable of holding any no. of accounts." ;
   delay(10) ;
   gotoxy(10,11); cout <<"- In first option you can open new accounts, display all" ;
   delay(10) ;
   gotoxy(10,12); cout <<"  accounts, search and also modify accounts." ;
   delay(10) ;
   gotoxy(10,14); cout <<"- Through the second option you can do banking transactions" ;
   delay(10) ;
   gotoxy(10,16); cout <<"- The third option allows you to view passbooks and" ;
   delay(10) ;
   gotoxy(10,17); cout <<"- statements" ;
   delay(10) ;
   gotoxy(10,19); cout <<"- Through the fourth option you can view help." ;
   delay(10) ;
   gotoxy(10,21); cout <<"- And last option is Quit (Exit to Dos)." ;
   delay(10) ;
   gotoxy(10,23); cout <<"Press any key to continue...............";
   getch() ;
   for (int i=27; i>=1; i--)
   {
	 delay(20) ;
	 gotoxy(1,i) ; clreol() ;
   }
}

long LastAcno()
{
  fstream F;
  F.open("BANK.DAT",ios::binary|ios::in);
  Customer C;
  long Ano=1000;
  while(F.read((char*)&C,sizeof(C)))
  { Ano=C.RAcno();}
  F.close();
  return Ano;
}

void NewAccount()
{
  clrscr();
  long Lano=LastAcno();
  fstream F1,F2;
  F1.open("BANK.DAT",ios::binary|ios::app);
  F2.open("TRAN.DAT",ios::binary|ios::app);
  Customer C;
  C.New(Lano);
  F1.write((char*)&C,sizeof(C));
  F2.write((char*)&C,sizeof(C));
  F1.close();
  F2.close();
}

void DispAccount()
{
  clrscr();
  fstream F;
  F.open("BANK.DAT",ios::binary|ios::in);
  Customer C;
  int RecNo=1;
  while(F.read((char*)&C,sizeof(C)))
  {
    clrscr();
    DispCh(62,6,"RecNo [");cout<<RecNo++<<"]";
    C.Disp();
    DispCh(7,16,"Press Any Key To Continue....");
    getch();
  }
  F.close();
}

void PassBook()
{
  clrscr();
  fstream F;
  F.open("TRAN.DAT",ios::binary|ios::in);
  Customer C;
  int Acnos;
  int RowNo=2;
  cout<<"Account No:";cin>>Acnos;
  clrscr();
  cout<<"  "<<setw(7)<<"Acno"<<setw(22)<<"Name"
      <<setw(8)<<"TrAmt"<<setw(7)<<"Type"<<setw(12)<<"Balance"
      <<setw(12)<<"Date";

  while(F.read((char*)&C,sizeof(C)))
  {
    if (Acnos==C.RAcno())
    {
      C.Disp2(RowNo++);
      if (RowNo>=22)
      {
	 DispCh(7,23,"Press Any Key To Continue....");
	 getch();
	 RowNo=2;
	 clrscr();
	 cout<<"  "<<setw(7)<<"Acno"<<setw(22)<<"Name"
	     <<setw(8)<<"TrAmt"<<setw(7)<<"Type"<<setw(12)<<"Balance"
	     <<setw(12)<<"Date";
      }
    }
  }
  F.close();
  DispCh(7,23,"Press Any Key To Continue....");
  getch();
}

void DispTrans()
{
  clrscr();
  fstream F;
  F.open("TRAN.DAT",ios::binary|ios::in);
  Customer C;
  int RowNo=1;
  char DT[12];
  cout<<"Date of Transactions:";gets(DT);
  while(F.read((char*)&C,sizeof(C)))
  {
    if (C.CompareDate(DT)==0)
    {
      C.Disp2(RowNo++);
      if (RowNo>=22)
      {
	DispCh(7,23,"Press Any Key To Continue....");
	getch();
	RowNo=1;
	clrscr();
      }
    }
  }
  F.close();
  DispCh(7,23,"Press Any Key To Continue....");
  getch();
}

void SearchAccount()
{
  clrscr();
  fstream F;
  F.open("BANK.DAT",ios::binary|ios::in);
  Customer C;
  long found=0,Anos;
  DispCh(7,7 ,"Acno to search    :");cin>>Anos;
  while(F.read((char*)&C,sizeof(C)))
  {
    if(Anos==C.RAcno())
    {
      C.Disp();
      found++;
      DispCh(7,16,"Press Any Key To Continue....");
      getch();
    }
  }
  F.close();
  if(found==0)
  {
    DispCh(7,16,"Sorry account does not exist in our bank....");
    getch();
  }
}

void ModifyAccount()
{
  clrscr();
  fstream F;
  F.open("BANK.DAT",ios::binary|ios::in|ios::out);
  Customer C;
  long found=0,Anos;
  DispCh(7,7 ,"Acno to modify    :");cin>>Anos;
  while(F.read((char*)&C,sizeof(C)))
  {
    if(Anos==C.RAcno())
    {
      C.Modify();
      int POS=F.tellg()-sizeof(C);
      F.seekp(POS);
      F.write((char*)&C,sizeof(C));
      found++;
      DispCh(7,16,"Press Any Key To Continue....");
      getch();
    }
  }
  F.close();
  if(found==0)
  {
    DispCh(7,16,"Sorry account does not exist in our bank....");
    getch();
  }
}

void DepositAccount()
{
  clrscr();
  fstream F1,F2;
  F1.open("BANK.DAT",ios::binary|ios::in|ios::out);
  F2.open("TRAN.DAT",ios::binary|ios::app);
  Customer C;
  long found=0,Anos; float Amtd;
  DispCh(7,7 ,"Acno[Deposit]    :");cin>>Anos;
  DispCh(7,8 ,"Amt [Deposit]    :");cin>>Amtd;
  while(F1.read((char*)&C,sizeof(C)))
  {
    if(Anos==C.RAcno())
    {
      C.Deposit(Amtd);
      int POS=F1.tellg()-sizeof(C);
      F1.seekp(POS);
      F1.write((char*)&C,sizeof(C));
      F2.write((char*)&C,sizeof(C));
      found++;
      DispCh(7,16,"Press Any Key To Continue....");
      getch();
    }
  }
  F1.close();
  F2.close();
  if(found==0)
  {
    DispCh(7,16,"Sorry accout does not exist in our bank....");
    getch();
  }
}

void WithdrawAccount()
{
  clrscr();
  fstream F1,F2;
  F1.open("BANK.DAT",ios::binary|ios::in|ios::out);
  F2.open("TRAN.DAT",ios::binary|ios::app);
  Customer C;
  long found=0,Anos; float Amtw;
  DispCh(7,7 ,"Acno[Withdraw]    :");cin>>Anos;
  DispCh(7,8 ,"Amt [Withdraw]    :");cin>>Amtw;
  while(F1.read((char*)&C,sizeof(C)))
  {
    if(Anos==C.RAcno())
    {
      if (C.Withdraw(Amtw))
      {
	int POS=F1.tellg()-sizeof(C);
	F1.seekp(POS);
	F1.write((char*)&C,sizeof(C));
	F2.write((char*)&C,sizeof(C));
	DispCh(7,16,"Amount Withdrawn..Press Any Key To Continue");
	getch();
      }
      else
      {
	DispCh(7,16,"Insufficient Fund....");
	getch();
      }
      found++;
    }
  }
  F1.close();
  F2.close();
  if(found==0)
  {
    DispCh(7,16,"Sorry account does not exist in our bank....");
    getch();
  }
}

//*****************************************************************
//---Screen Formatting Utility Functions---------------------
//*****************************************************************

void Color(int TC,int BC)
{
  textcolor(TC);
  textbackground(BC);
}

void DispCh(int C,int R,char CH) //to display a char on a particular loc
{
  gotoxy(C,R);
  cprintf("%c",CH); //to display char var with current color settings
}

void DispCh(int C,int R,char CH[])//to display a string on a particular loc
{
  gotoxy(C,R);
  cprintf("%s",CH);
}

void BOX(int C1,int R1,int C2,int R2)//to display a rectangular box
{
  DispCh(C1,R1,TL);  //displaying corners
  DispCh(C2,R1,TR);
  DispCh(C1,R2,BL);
  DispCh(C2,R2,BR);
  for (int i=C1+1;i<C2;i++) //displaying horizontal lines
  {
    DispCh(i,R1,HL);
    DispCh(i,R2,HL);
  }
  for (i=R1+1;i<R2;i++)
  {
    DispCh(C1,i,VL);
    DispCh(C2,i,VL);
  }
}

int VMenu(int C,int R,char M[][20],int N)
{
  Color(BLACK,WHITE);
  BOX(C,R,C+strlen(M[0])+1,R+N+1);
  for (int I=0;I<N;I++)
    DispCh(C+1,R+I+1,M[I]);

  int Sel=0,Exit=0;
  char Ch;
  do
  {
    int Tsel=Sel;
    Color(BLACK,GREEN);
    DispCh(C+1,R+Sel+1,M[Sel]);
    Color(BLACK,WHITE);
    Ch=getch();
    switch(Ch)
    {
     case 71:Sel=0;break;                 //Home
     case 79:Sel=N-1;break;               //End
     case 72:Sel=(Sel==0)?N-1:Sel-1;break;//Up
     case 80:Sel=(Sel==N-1)?0:Sel+1;break;//Down
     case 27:Sel=-1;                      //Escape
     case 13:Exit=1;                      //enter
    }
    DispCh(C+1,R+Tsel+1,M[Tsel]);
  }
  while (!Exit);
  return Sel;
}

int HMenu(int C,int R,char M[][20],int N)
{
  Color(WHITE,RED);
  for (int I=0;I<N;I++)
    DispCh(C+1+10*I,R,M[I]);

  int Sel=0,Exit=0;
  char Ch;
  do
  {
    int Tsel=Sel;
    Color(RED,WHITE);
    DispCh(C+1+10*Sel,R,M[Sel]);
    Color(WHITE,RED);
    Ch=getch();
    switch(Ch)
    {
     case 71:Sel=0;break;                 //Home
     case 79:Sel=N-1;break;               //End
     case 75:Sel=(Sel==0)?N-1:Sel-1;break;//Up
     case 77:Sel=(Sel==N-1)?0:Sel+1;break;//Down
     case 27:Sel=-1;                      //Escape
     case 13:Exit=1;                      //enter
    }
    DispCh(C+1+10*Tsel,R,M[Tsel]);
  }
  while (!Exit);
  return Sel;
}

//*****************************************************************
// END OF PROJECT
//*****************************************************************