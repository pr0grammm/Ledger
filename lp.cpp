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

void processEndMaster(ofstream &);
void processCurrentMaster(float);
void processStartMaster(ofstream &);

void printHeader(ofstream & stream)//to printout
{
stream<<accountNum<<'\t'<<title<<endl;
}

void printBalances(ofstream & stream, double prev_bal , double cur_bal)//balance line for print outs
{
stream<<"\t\t\t\tPrev. bal: "<<setw(8)<<fixed<<showpoint<<setprecision(2)<<prev_bal\
<<"\tNew bal:\t"<<setw(8)<<fixed<<showpoint<<setprecision(2)<<cur_bal<<endl;
}

int getAcc()
{
return accountNum;
}


Master()
{
accountNum=0;
title[0] = '0';
for(int i = 0; i<12 ;i++) balances[i] = 0.000005;

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

void printLine(ofstream & stream)//to print out
{
stream.setf(ios::right , ios::adjustfield);
stream<<'\t'<<setw(6)<<checkNum<<'\t';
stream.setf(ios::left,ios::adjustfield);
stream<<date<<'\t'<<setw(30)<<desc;
stream.setf(ios::right , ios::adjustfield);
stream.setf(ios::right|ios::fixed,ios::floatfield);
stream.precision(2);
stream<<'\t'<<setw(8)<<amount<<endl;
}


int getAcc()
{
return accountNum;
}

float getAmount()
{
return amount;
}

};


bool is_empty(std::fstream& pFile);
char record[RECORD_SIZE];
int month;//current month to be processed
Master list1[SIZE];
Transaction list2[SIZE];
char outputList[1000][50000];
int N1=0;
int N2=0;

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

list[i++].unpack();

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
	if(balances[i] == 0.000005)//account has been added later (or) current month balance not yet posted
	cout<<left<<setw(12)<<setfill(' ')<<' ';

	else
	cout<<left<<setw(12)<<setfill(' ')<<balances[i];
}
cout<<endl;
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
	sprintf(b, "%.6f", balances[i]);
	strcat(record , b);
	
}
strcat(record , "#");
}


void Master::unpack()
{
char temp[RECORD_SIZE];
strcpy(temp , record);
accountNum =atoi(strtok(temp , "|"));
strcpy(title , strtok(NULL , "|"));

int i;
for( i =0 ; i <11;i++)
{
balances[i] =string_to_double(strtok(NULL , "|"));
}

balances[11] = string_to_double(strtok(NULL,"#"));
}


void addNewVendor()
{
char filename[SIZE];
strcpy(filename , "Master.txt");
ofstream f;
f.open(filename , ios::app);
f.close();
int N=read_into_ram(filename , list1);
N++;
list1[N-1].getData();

//do insertion sort
insertion_sort(list1,N);

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

sprintf(c, "%.6f", amount);

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

void Master::processEndMaster(ofstream & fprint)
{
float prev_bal,cur_bal;
cur_bal = balances[month-1];

prev_bal=( (month == 1)?balances[11]:balances[month-2] );
printBalances(fprint, prev_bal , cur_bal);

}

void Master::processStartMaster(ofstream & fprint)
{
//print header
printHeader(fprint);

//initialise new balance
if(month == 1)
{
balances[0] = balances[11];
}

else
balances[month-1] = balances[month-2];

}

void Master::processCurrentMaster(float amt)
{

balances[month-1] += amt;

}

void cosequential(Master list1[] ,Transaction list2[])
{
int i =0;//master
int j= 0;//transaction
int item1=0;
int item2 = 0;
int lowValue = -1;
int highValue = 32767;

ofstream fprint;
char printFileName[30];
sprintf(printFileName, "%s_report_print",get_month_name(month));
fprint.open(printFileName);
item1= list1[i].getAcc();
item2 = list2[j].getAcc();

list1[i].processStartMaster(fprint);

while(i < N1 || j <N2)
{

if(item1<item2 && item1 != -1)//finish this master record and start next
{

	if(i==N1) //all records processed
	{
		item1 = lowValue;
		
	}

	else//process this master record and read next if any
	{
		list1[i].processEndMaster(fprint);
		i++;

		if(i<N1)//more records present
		{
			item1 = list1[i].getAcc();
			list1[i].processStartMaster(fprint);
		}
		
		else item1 = lowValue;//no more records

	}
}

else if(item1==item2)//transaction matches master
{

	if(j == N2)//no more transaction records to be processed
	{
		item2 = highValue;
	}

	else//process this record and read in next record if present
	{
	
		list1[i].processCurrentMaster(list2[j].getAmount());
		list2[j].printLine(fprint);
		j++;


		if(j<N2)//next record exists 
		{
			item2 = list2[j].getAcc();
		}

		else//all records exhausted
		{
		item2 = highValue;
		}
	}
}

else // transaction with no master
{

	if(j == N2) item2 = highValue; // all transcation records over
	else//skip transaction
	{
		//print some message

		j++;
		if(j < N2) item2 = list2[j].getAcc();

		else item2 = highValue;
	}

}
}//end of while
fprint.close();
}//end of func

void finishUp()
{
/*
to be called after post transaction
*/

//write back to master from index
fstream fout;
fout.open("Master.txt");
cout<<N1;

for(int i =0; i < N1 ;i ++)
{
list1[i].pack();
fout<<record;

}
fout.close();
//change month
//month = (month+1)%12;
}//end of func 

void menu()
{
int opt;
bool cont;
char filename[SIZE];
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
	
	//read both files into list
	month = get_current_month();
	N1=read_into_ram("Master.txt" , list1);
	sprintf(filename , "%s.txt" , get_month_name(month));
	N2=read_into_ram(filename , list2);

	//sort lists in memory- list1 already sorted
	insertion_sort(list2 , N2);

	//	
	cosequential(list1 ,list2);
	finishUp();		
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


