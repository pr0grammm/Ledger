#include<iostream>
#include<fstream>
#include<string.h>
#include<sstream>
#include<stdlib.h>
#include<iomanip>

#define SIZE 100
#define RECORD_SIZE 200

using namespace std;

class Master{

int accountNum;
char title[60];
double balances[20];

public:
void getData();
void printData();
void pack();
void unpack();

int getAcc()
{
return accountNum;
}


Master()
{
accountNum=0;
title[0] = '0';
for(int i = 0; i<12 ;i++) balances[i] = 0.005;

}
};//end of class master 

class Transaction{

private:
int accountNum;
int checkNum;
char date[30];
char desc[60];
double amount;

public:
void getData();
void printData();
void pack();
void unpack();

int getAcc()
{
return accountNum;
}

};


bool is_empty(std::fstream& pFile);
char record[RECORD_SIZE];
int month;//current month to be processed
Master list1[SIZE];
Transaction list2[SIZE];

template<class TYPE>
void insertion_sort(TYPE list[],int N)
{
TYPE temp;
int i, key, j;
   for (i = 1; i < N; i++)
   {
       temp = list[i];
       key = list[i].getAcc();
       j = i-1;
 
       /* Move elements of list[0..i-1], that are
          greater than key, to one position ahead
          of their current position */
       while (j >= 0 && key<list[j].getAcc())
       {
           list[j+1] = list[j];
           j = j-1;
       }
       list[j+1] = temp;
   }


}//end of function

int get_current_month()
{
/*
function to get current month from file
*/
cout<<"called"<<endl;
char temp[10];
fstream f;

f.open("track_month.txt" ,std::fstream::in|std::fstream::out| std::fstream::app);

//if file does not exist
if(!(f.is_open()))
{
	cout<<"creating file for the first time"<<endl;
	f.open("track_month.txt" , std::fstream::in|std::fstream::out|std::fstream::trunc);
	
}

//if file exists

//if file is empty
if(is_empty(f))
{
	//write 1 to file
	f<<"1"<<endl;
	month = 1;
	cout<<"file was empty"<<endl;
}

else // file exists and is not empty
{
	cout<<"file was not empty"<<endl;
	f>>temp;
	month = atoi(temp);
}

f.close();
return month;

}//end of function



char *  get_month_name(int no)
{
switch(no)
{
	case 1:
		return "January";
		break;

	case 2:
		return "February";
		break;
	case 3:
		return "March";
		break;
	case 4: 
		return "April";
		break;
	case 5:
		return "May";
		break;
	case 6:
		return "June";
		break;
	case 7:
		return "July";
		break;
	case 8:
		return "August";
		break;
	case 9:
		return "September";
		break;
	case 10:
		return "October";
		break;
	case 11:
		return "November";
		break;
	case 12:
		return "December";
		break;

}//end of switch

}		
double string_to_double( const std::string& s )
{
   std::istringstream i(s);
   double x;
   if (!(i >> x))
     return 0;
   return x;
}

bool is_empty(std::fstream& f)
{
f.seekg(0,ios::end);

bool ret=(f.tellg() == 0);

f.seekg(0,ios::beg);

return ret;

//    return pFile.peek() == std::fstream::traits_type::eof();
}
template<class TYPE>
int read_into_ram(char filename[],TYPE list[])//TYPE could be master or transaction
{
/*
function to read given file into buffer
return true if buffer is not empty and
false if nothing has been written to buffer
*/
fstream fin;
fin.open(filename);
int i=0;
int N=0;
bool cont =true;

if(!(fin.is_open())) return N;

if(is_empty(fin)) return N;

fin.seekg(0,ios::beg);
while(fin.getline(record , RECORD_SIZE ,'#'))
{

cout<<record;
list[i++].unpack();
//	cout<<list[i].getAcc(); 

}

fin.close();
N=i;
return N;
}//end of function

void sort(char list[][RECORD_SIZE])
{
//to sort list in ascending order of item


}//end of function


void Master :: getData()
{
cout<<"enter the account number: ";
cin>>accountNum;
cin.ignore();
cout<<"enter the title for this account: ";
cin.getline(title,60); 


//balances are initialised through post transaction
}

void Master::printData()
{
cout<<left<<setw(20)<<setfill(' ')<<accountNum;
cout<<left<<setw(20)<<setfill(' ')<<title;

for(int i =0 ;i<12 ; i++)
{
	if(balances[i] == 0.005)//account has been added later (or) current month balance not yet posted
	cout<<left<<setw(20)<<setfill(' ')<<' ';

	else
	cout<<left<<setw(20)<<setfill(' ')<<balances[i];
}
cout<<endl;
/*
cout.setf(ios::right , ios::adjustfield);
cout<<accountNum<<'\t';
cout.setf(ios::left , ios::adjustfield);
cout<<setw(20)<<title;
cout.setf(ios::right , ios::adjustfield);
cout.setf(ios::right|ios::fixed , ios::floatfield);
cout.precision(2);

for(int i =0 ;i<=month; i++)
{
	cout<<'\t'<<setw(8)<<balances[i];
}

cout<<endl;
*/
}

void Master:: pack()
{

char a[10];
char b[10];
sprintf(a, "%d", accountNum);
strcpy(record , a);
strcat(record , "|");
strcat(record , title);

for(int i = 0;i<12 ; i++)
{
	strcat(record , "|");
	sprintf(b, "%.3f", balances[i]);
	strcat(record , b);
	
}
strcat(record , "#");
}


void Master::unpack()
{
char temp[RECORD_SIZE];
strcpy(temp , record);
this->accountNum =atoi(strtok(temp , "|"));
cout<<"unpacked"<<endl;
cout<<accountNum<<endl;
strcpy(this->title , strtok(NULL , "|"));
cout<<title<<endl;
int i;
for( i =0 ; i <11;i++)
{
this->balances[i] =string_to_double(strtok(NULL , "|"));
}

this->balances[11] = string_to_double(strtok(NULL,"#"));
for(int i=0 ; i<12;i++) cout<<balances[i]<<" ";
cout<<endl;
}


void addNewVendor()
{
char filename[SIZE];
strcpy(filename , "Master.txt");
ofstream f;
f.open(filename , ios::app);
f.close();
int N=read_into_ram(filename , list1);
cout<<N;
N++;
list1[N-1].getData();
cout<<list1[N-1].getAcc();
//do insertion sort
insertion_sort(list1,N);
for(int i =0 ;i<N;i++) cout<<list1[i].getAcc()<<endl;
//write list back to file
ofstream fout;
fout.open("Master.txt");

for(int i = 0; i < N;i++)
{
	list1[i].pack();
	fout<<record;
}
fout.close();
}

void displayVendors()
{
fstream f;
f.open("Master.txt");

if(!(f.is_open())) 
{
	cout<<"Ledger empty. Nothing posted yet"<<endl;
	return;
}


if(is_empty(f)) 
{
	cout<<"Master file is empty"<<endl;
	f.close();
	return;

}

cout<<"****************************************************************************************************"<<endl;
Master m;
while(true)
{
	f.getline(record,RECORD_SIZE,'#');

	if(f.eof()) break;
	m.unpack();
	m.printData(); 

}
cout<<"****************************************************************************************************"<<endl;
f.close();
}
void Transaction::pack()
{
char a[30];
char b[30];
char c[30];

sprintf(a, "%d", accountNum);
strcpy(record , a);
strcat(record , "|");

sprintf(b, "%d", checkNum);
strcat(record , b);
strcat(record , "|");

strcat(record , date);
strcat(record , "|");

strcat(record , desc);
strcat(record , "|");

sprintf(c, "%.3f", amount);

strcat(record, c);
strcat(record , "#");

}

void Transaction::unpack()
{
char temp[RECORD_SIZE];

strcpy(temp , record);

accountNum =atoi(strtok(temp , "|"));
checkNum=atoi( strtok(NULL , "|"));
strcpy(date , strtok(NULL , "|"));
strcpy(desc , strtok(NULL , "|"));

amount=string_to_double(strtok(NULL , "#"));

}

void Transaction::getData()
{
cout<<"enter account number: ";
cin>>accountNum;
cout<<"enter check number: ";
cin>>checkNum;
cout<<"enter date(dd/mm/yyyy)";
cin>>date;
cout<<"enter a brief description";
cin.ignore();
cin.getline(desc,60);
cout<<"enter amount(credit/debit)";
cin>>amount;
}

void Transaction::printData()
{
cout<<left<<setw(20)<<setfill(' ')<<accountNum;
cout<<left<<setw(20)<<setfill(' ')<<checkNum;
cout<<left<<setw(20)<<setfill(' ')<<date;
cout<<left<<setw(20)<<setfill(' ')<<desc;
cout<<left<<setw(20)<<setfill(' ')<<amount;
cout<<endl;
}

void addNewTransaction()
{
/*to add record to transaction file*/
char filename[30];
sprintf(filename , "%s.txt" , get_month_name(month));

fstream ft;
ft.open(filename , ios::app);

//check if open is successful
if(!(ft.is_open())) 
{
	cout<<"problem opening file"<<endl;
	exit(0);
}


Transaction t;
t.getData();
t.pack();

ft << record;

ft.close();
}

void displayTransactions()
{

Transaction t;
char filename[30];
sprintf(filename , "%s.txt" , get_month_name(month));

fstream ft;
ft.open(filename);

//check if open is successful
if(!(ft.is_open())) 
{
	cout<<"file could not be opened. This month's transaction file has probably not been created yet.\n\
Please add some transactions and try again"<<endl;
	return;
}


if(is_empty(ft))
{
	cout<<"no transactions for this month yet"<<endl;
	return;
}
cout<<"****************************************************************************************************"<<endl;
while(true)
{
	ft.getline(record,50,'#');

	if(ft.eof()) break;
	t.unpack();
	t.printData(); 
}
cout<<"****************************************************************************************************"<<endl;

ft.close();
}//end of function


void menu()
{
int opt;
bool cont;

while(1)
{
cout<<"\n1. edit journal file\t2. post transactions to ledger\t3. edit master file\t4. exit"<<endl;
cin>>opt;

switch(opt)
{
case 1: 
	month = get_current_month();
	cont = true;
	while(cont)
	{
		
	cout<<"Editing transaction file for the month of "<<get_month_name(month)<<endl;
	cout<<"\n1. add new transaction for current month\t2. view transactions for current month\t3. back to main menu\t4.exit"<<endl;
	cin>>opt;
	switch(opt)
	{
		case 1:
			addNewTransaction();
			break;

		case 2:
			displayTransactions();
			break;

		case 3:
			cont = false;
			break;

		case 4:
			exit(0);
		
		default :
			exit(0);
			
			

	}
	}//end of inner while
	break;

case 2:
	//post transactions to ledger	
	
	break;

case 3://edit master file
	month = get_current_month();
	cont = true;
	while(cont)
	{
		cout<<"\n1. add new vendor account\t2. view master file\t3. back to main menu\t4.exit"<<endl;
		cin>>opt;
		switch(opt)
		{
			case 1:
				addNewVendor();
				break;

			case 2:
				displayVendors();
				break;

			case 3:	
				cont = false;
				break;

			case 4:
				exit(0);
		
			default :
				exit(0);
			
			

		}
	}//end of inner while

	break;

case 4:
	exit(0);
	break;

default : exit(0);
}

}//end of while
}

int main()
{
menu();
return 0;
}


