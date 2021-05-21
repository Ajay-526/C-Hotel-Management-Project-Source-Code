#include<iostream>
#include<conio.h>
#include<fstream>
#include<string.h>
using namespace std;
char user_name[20]="admin";
char password[10]="1234";
char d[3][10]={"Date","Month","Year"};
class booking
{
public:
	int room_no;
	char name[30];
	char address[50];
	char phone[10];
	int nod;
	int nogts;
	int date[3];
	int cost;
	int tot_amt;
public:
	int payment(int,int,int,int);
};
class admin: public booking
{
public:
	void main_menu();		
	void admin_add();			
	void display_admin_bookings(); 		
	void display_user_bookings();
	void admin_tot_rooms();		
	void edit_admin_bookings();			
	int check_admin(int);			
	void modify_admin(int);		
	void delete_rec_admin(int);
};
class user: public booking
{
public:	
	void menu();
	void user_add();			
	void display_booked_room();
	void all_rooms();
	int check_user(int);
	void edit_user_bookings();
	void modify_user(int);	
	void delete_rec_user(int);
};
class food: public user
{
public:
	int fr;
	char food_name[30];
	int qty;
	int price;
	int tot_food_cost;
public:
	void main_menu_food();
	void order_food();
	int food_payment(char*,int,int);
	void food_ordering_details();	
};
void food::main_menu_food()
{
	int choice;
	while(choice!=3)
	{
		cout<<"\n\t\t\t\t-------------";
		cout<<"\n\t\t\t\t* MAIN MENU *";
		cout<<"\n\t\t\t\t--------------";
		cout<<"\n\t\t\t1.Order Food";
		cout<<"\n\t\t\t2.Food_ordering_details";
		cout<<"\n\t\t\t3.go back to the menu";
		cout<<"\n\t\t\t4.Exit";
		cout<<"\n\n\t\t\tEnter Your Choice: ";
		cin>>choice;
		switch(choice)
		{
			case 1: order_food();
					break;
			case 2: food_ordering_details();
					break;
			case 3: return;
					break;
			case 4: exit(0);
					break;
			default:
			{
				cout<<"\n\n\t\t\tWrong choice.....!!!";
				cout<<"\n\t\t\tPress any key to continue....!!";
				getch();
			}
		}
	}
}
void food::order_food()
{
	int f,pr;
	int room_no, name;
	char foodd[4][30]={"Chicken Biryani","Mutton Biryani","Noodles","Fried Rice"};
	
	ofstream foo("food.dat",ios::app);
	
//	ifstream fin("admin_bookings.dat",ios::in);
//	ifstream user_fin("user_bookings.dat",ios::in);
//	fin.seekg(0);
//	user_fin.close();
	int room,flag=0,ct=0,ct1=0;
	cout<<"\n Enter room no: ";
	cin>>room;
	
//	fin.close();
//	user_fin.close();
	admin a;
	//ct=a.check_admin(room);
	ct1=check_user(room);
	
	if(ct1)
	{
		fr=room;
		for(int i=0;i<4;i++)
		{
			cout<<"\n"<<i+1<<". "<<foodd[i];
		}
		cout<<"\nEnnter the food item: ";
		cin>>f;
		switch(f)
		{
			case 1: strcpy(food_name,"Chicken Biryani");
					cout<<"\nThe cost is Rs. 120 per each Quantity";
					price=120;
					break;
			case 2: strcpy(food_name,"Mutton Biryani");
					cout<<"\nThe cost is Rs. 170 per each Quantity";
					price=170;
					break;
			case 3: strcpy(food_name,"Noodles");
					cout<<"\nThe cost is Rs. 70 per each Quantity";
					price=70;
					break;
			case 4: strcpy(food_name,"Fried Rice");
					cout<<"\nThe cost is Rs. 100 per each Quantity";
					price=100;
					break;
			default: cout<<"\nSelect a valid one";
						break;
		}
		cout<<"\nNow Enter the Quantity of the food-item";
		cin>>qty;
		pr=food_payment(food_name,qty,price);
		tot_food_cost=pr;
		flag=1;
		foo.write((char*)this,sizeof(food));
	}
	if(flag==0)
		cout<<"\n Sorry Room no. not found or vacant....!!";
	cout<<"\n\n Press any key to continue....!!";
	getch();
	//fin.close();
}
void food::food_ordering_details()
{
	ifstream food_fin("food.dat",ios::in);
	while(!food_fin.eof() && food_fin.read((char*)this,sizeof(food)))
	{
		//food_fin.read((char*)this,sizeof(*this));
		cout<<"\nroom_no: "<<fr;
		cout<<"\nfood-item: "<<food_name;
		cout<<"\nQuantity: "<<qty;
		cout<<"\nPrice per qty: "<<price;
		cout<<"\nThe final food cost: "<<tot_food_cost;
		cout<<"\n-----------------------------------------------";
	}
	food_fin.close();
}
int food::food_payment(char food_name[30],int qty,int price)
{
	cout<<"\nYou Have selected "<<food_name<<"of Quantity"<<qty;
	int t=qty*price;
	cout<<"\nNow the total amount for the food-item is: "<<t;
	return t;
}
void user::menu()
{
	food f;
	int choice;
	while(choice!=4)
	{
		cout<<"\n\t\t\t\t-------------";
		cout<<"\n\t\t\t\t* MAIN MENU *";
		cout<<"\n\t\t\t\t--------------";
		cout<<"\n\n\n\t\t\t1.Book A Room";
		cout<<"\n\t\t\t2.See your booked room";
		cout<<"\n\t\t\t3.Edit your booked rooms";
		cout<<"\n\t\t\t4.Order Food";
		cout<<"\n\t\t\t5.Go back to menu";
		cout<<"\n\t\t\t6.Exit";
		cout<<"\n\n\t\t\tEnter Your Choice: ";
		cin>>choice;
		switch(choice)
		{
			case 1:	user_add();
					break;
			case 2: display_booked_room();
					break;
			case 3: edit_user_bookings();
					break;
			case 4: f.main_menu_food();
					break;
			case 5: return;
					break;
			case 6: exit(0);
			        break;
			default:
			{
				cout<<"\n\n\t\t\tWrong choice.....!!!";
				cout<<"\n\t\t\tPress any key to continue....!!";
				getch();
			}
		}
	}
}
void user::user_add()
{
	int r,flag;
    char ch;
    int c,t;
	ofstream user("user_bookings.dat",ios::app);
	cout<<"\n Enter Customer Detalis:\n";
	cout<<"**********\n";
	cout<<"\n\t\tchoose the room type";
	cout<<"\n**********";
    cout<<"\nRo ROYAL ROOMS\t\t\t\troom number from 1-50";
    cout<<"\n**********";
    cout<<"\nS DELUX ROOMS\t\t\t\troom number from 51-100";
    cout<<"\n**********";
    cout<<"\nRR REGULAR ROOMS\t\t\t room number from 101-150";
    cout<<"\n**********";
    cout<<"\nSS: single suite\t\t\t room number from 151-200";
    cout<<"\n**********";
    cout<<"\nPS: presidental suite\t\t\t room number from 201-250";
	cout<<"\n**********";
	cout<<"\n ----------------------";
	cout<<"\n\n Room no: ";
	cin>>r;
	cout<<"\n-----------------------------------";
	flag=check_user(r);
	if(flag)
		cout<<"\n Sorry..!!!Room is already booked";
	else
	{
		room_no=r;
		cout<<" Name: ";
		cin>>name;
		cout<<"Address: ";
		cin>>address;
		cout<<"Phone No: ";
		while(1)
		{
			gets(phone);
			if(strlen(phone)==10)
			break;
			else
			cout<<"Enter a 10-digit phone number";
		}
		cout<<"Number of days you want to stay: ";
		cin>>nod;
		cout<<"How many no. of guests";
		cin>>nogts;
		cout<<"Today's Date: ";
		while(1)
		{
			for(int i=0;i<3;i++)
			{
				cout<<d[i]<<":";
				cin>>date[i];
			}
			if((date[0]>=1&&date[0]<=31)&&(date[1]>=1 && date[1]<=12) && (date[2]>=2021))
			break;
			else
			cout<<"Please enter valid date:)";
		}
		if(room_no>=1 && room_no<=50)
			{
				cout<<"\nIt's a ROYAL ROOM";
				cout<<"\nYou need to pay Rs:1000 per head";
				cost=1000;
			}
			else if(room_no>=51 && room_no<=100)
			{
				cout<<"\nIt's a DELUX ROOM";
				cout<<"\nYou need to pay Rs:750 per head";
				cost=750;
			}
			else if(room_no>=101 && room_no<=150)
			{
				cout<<"\nIt's a REGULAR ROOM";
				cout<<"\nYou need to pay Rs:550 per head";
				cost=550;
			}
			else if(room_no>=151 && room_no<=200)
			{
				cout<<"\nIt's a SINGLE SUITE ROOM";	
				cout<<"\nYou need to pay Rs:450 per head";
				cost=450;
			}
			else
			{
				cout<<"\nIt's a PRESENDTIAL SUITE ROOM";
				cout<<"\nYou need to pay Rs:350 per head";
				cost=350;
			}
		cout<<"Do you want to go to the Billing? (y/n)";
		cin>>ch;
		if(ch=='y')
		{
			cout<<"\nChoose a ppayment method:";
			cout<<"\n1. Credit/Debit Card Payment";
			cout<<"\n2. NetBanking Payment";
			cout<<"\n3. UPI pin";
			cout<<"\nEnter your choice:";
			cin>>c;
			t=payment(c,nod,nogts,cost);
		}
		else
		{
			cout<<"\nSorry Request Timed-Out";
			exit(0);
		}
		tot_amt=t;
		user.write((char*)this,sizeof(user));
		user.close();
	}
}
void user::all_rooms()
{
	ifstream user_fin("user_bookings.dat",ios::in);
	user_fin.seekg(0);
	cout<<"\n---------------------USER BOOKINGS--------------------------:";
	cout<<"\nRoom_no \tName \t\t Address \t\t No. of Guests \t\t cost_per_head \t Tot_no_Guests \t Total_amout\n";
	cout<<"\n";
	while(!user_fin.eof())
	{
		user_fin.read((char*)this,sizeof(user));
		cout<<room_no<<"\t\t"<<name<<"\t\t"<<address<<"\t\t"<<nogts<<"\t\t\t"<<cost<<"\t\t\t"<<nogts<<"\t"<<tot_amt<<"\n";
		cout<<"\n";
	}
	user_fin.close();
}
void user::display_booked_room()
{
	ifstream user_fin("user_bookings.dat",ios::in);
	int r,flag=0,ct=0;
	cout<<"\n Enter room no: ";
	cin>>r;
	while(!user_fin.eof())
	{
		user_fin.read((char*)this,sizeof(user));
		if(r==room_no)
		{
			cout<<"\n Cusromer Details";
			cout<<"\n ----------------";
			cout<<"\n\n Room no: "<<room_no;
			cout<<"\n Name of the customer: "<<name;
			cout<<"\n Customer Address: "<<address;
			cout<<"\n Phone: "<<phone;
			cout<<"\n No. of days to be stayed: "<<nod;
			cout<<"\n No. of Guests: "<<nogts;
			cout<<"\n Date of alloted :";
			for(int i=0;i<3;i++)
			{
				cout<<date[i]<<"-";
			}
			flag=1;
		}
		if(flag==1)
		break;
	}
	if(flag==0)
		cout<<"\n Sorry Room no. not found or vacant....!!";
	cout<<"\n\n Press any key to continue....!!";
	getch();
	user_fin.close();
}
int user::check_user(int r)
{
	int flag=0,flag1=0,temp=0;
	ifstream user_fin("user_bookings.dat",ios::in);
	ifstream fin("admin_bookings.dat",ios::in);
	while(!user_fin.eof() && user_fin.read((char*)this,sizeof(user)))
	{
		//user_fin.read((char*)this,sizeof(user));
		if(room_no==r)
		{
			flag=1;
			break;
		}
	}
	while(!fin.eof() && fin.read((char*)this,sizeof(admin)))
	{
		//fin.read((char*)this,sizeof(admin));
		if(room_no==r)
		{
			flag1=1;
			break;
		}
	}
	if(flag==1 || flag1==1)
		temp=1;
	return temp;;
	user_fin.close();
	fin.close();
}
void user::edit_user_bookings()
{
	int choice,r;
	cout<<"\n EDIT MENU";
	cout<<"\n ---------";
	cout<<"\n\n 1.Modify Customer Record";
	cout<<"\n 2.Delete Customer Record";
	cout<<"\n Enter your choice: ";
	cin>>choice;
	cout<<"\n Enter room no: " ;
	cin>>r;
	switch(choice)
	{
		case 1:	modify_user(r);
				break;
		case 2:	delete_rec_user(r);
				break;
		default: cout<<"\n Wrong Choice.....!!";
	}
	cout<<"\n Press any key to continue....!!!";
	getch();
}
void user::modify_user(int r)
{
	long pos,flag=0;
	fstream user_file("user_bookings.dat",ios::in|ios::out);
	while(!user_file.eof())
	{
		pos=user_file.tellg();
		user_file.read((char*)this,sizeof(user));
		if(room_no==r)
		{
			cout<<"\n Enter New Details";
			cout<<"\n -----------------";
			cout<<"\n : ";
			cout<<" Name:";
			cin>>name;
			cout<<" Address: ";
			cin>>address;
			cout<<" Phone no: ";
			while(1)
			{
				gets(phone);
				if(strlen(phone)==10)
				break;
				else 
				cout<<"Enter exactly 10-digit phone number"<<endl;
			}
			cout<<"Number of days you want to stay: ";
			cin>>nod;
			cout<<"How many no. of guests";
			cin>>nogts;
			cout<<"Today's Date: ";
			while(1)
			{
				for(int i=0;i<3;i++)
				{
					cout<<d[i]<<":";
					cin>>date[i];
				}
				if((date[0]>=1&&date[0]<=31)&&(date[1]>=1 && date[1]<=12) && (date[2]>=2021))
				break;
				else
				cout<<"Please enter valid date:)";
			}
			user_file.seekg(pos);
			user_file.write((char*)this,sizeof(user));
			cout<<"\n Record is modified....!!";
			flag=1;
			break;
		}
	}
	if(flag==0)
	cout<<"\n Sorry Room no. not found or vacant...!!";
	user_file.close();
}
void user::delete_rec_user(int r)
{
	int flag=0;
	char ch;
	int ct=0;
	ifstream user_fin("user_bookings.dat",ios::in);
	
	ofstream fout1("temp1.dat",ios::out);
	
	while(!user_fin.eof())
	{
		user_fin.read((char*)this,sizeof(user));
		if(room_no==r)
		{
		   cout<<"\n Name: "<<name;
		   cout<<"\n Address: "<<address;
		   cout<<"\n Pone No: "<<phone;
		   cout<<"\n Number of days are: "<<nod;
		   cout<<"\n Number of guests are: "<<nogts;
		   cout<<"\n Date of alloted: ";
			for(int i=0;i<3;i++)
			{
				
				cout<<date[i]<<"-";
			}
		   cout<<"\n\n Do you want to delete this record(y/n): ";
		   cin>>ch;
			if(ch=='n')
		  		fout1.write((char*)this,sizeof(user));
			flag=1;
		}
		else
		fout1.write((char*)this,sizeof(user));
		if(flag==1)
		break;
	}
	user_fin.close();
	fout1.close();
	if(flag==0)
		cout<<"\n Sorry room no. not found or vacant...!!";
	else
	{
		remove("user_bookings.dat");
	    rename("temp1.dat","user_bookings_dat");
	}

/******/
}
class regis{	
public:
	int id;
	int pass;
public:	
	void menu();
	void reg();
	void login();
	int check_reg(int,int);
	void all_registrations();
};
void regis::menu()
{
	admin a;
	int ch;
	do
	{
		cout<<"\nHello!!";
		cout<<"\n1.Adim Login:";
		cout<<"\n2.User Registration";
		cout<<"\n3.User Login";
		cout<<"\n4.Exit";
		cout<<"\nEnter choice";
		cin>>ch;
		switch(ch)
		{
			case 1: a.main_menu();
					break;
			case 2: reg();
					break;
			case 3: login();
					break;
			case 4: exit(0);
					break;
			default: cout<<"Sorry! Choose a right one";
						break;
		}
	}while(1);
}
void regis::reg()
{
	int i,ps,flag=0;
	ofstream reg("registrations.dat",ios::app);
	cout<<"Enter id: in numbers:";
	cin>>i;
	cout<<"Choose Password in numbers:";
	cin>>ps;
	flag=check_reg(i,ps);
	if(flag)
	{
		cout<<"Sorry!! Registration details are already taken";
	}
	else
	{
		id=i;
		pass=ps;
		reg.write((char*)this,sizeof(*this));
		cout<<"-------------------Registration Successfull--------------------------";
	}
	reg.close();
}
int regis::check_reg(int i,int ps)
{
	int flag=0;
	ifstream check("registrations.dat",ios::in);
	check.seekg(0);
	while(!check.eof() && check.read((char*)this,sizeof(*this)))
	{
		if(i==id || ps==pass)
		{
			flag=1;
			break;
		}
	}
	check.close();
	return flag;
}
void regis::all_registrations()
{
	ifstream check("registrations.dat",ios::in);
	while(!check.eof() && check.read((char*)this,sizeof(*this)))
	{
		cout<<"\nId: "<<id;
		cout<<"\nPassword:"<<pass;
	}
	check.close();
}
void regis::login()
{
	user u;
	int i,ps,flag=0;
	cout<<"Enter id: in numbers:";
	cin>>i;
	cout<<"Choose Password in numbers:";
	cin>>ps;
	flag=check_reg(i,ps);
	ifstream check("registrations.dat",ios::in);
	check.seekg(0);
	while(!check.eof() && check.read((char*)this,sizeof(*this)))
	{
		if(i==id && ps==pass)
		{
			cout<<"\n--------------Login Successfull-----------------";
			u.menu();
		    break;
		}
		else
		{
			cout<<"Invalid Entries:";
		}
	}
	check.close();
}
void admin::main_menu()
{
	food f1;
	char user[20];
	char ps[10];
	int ch;
	cout<<"Enter Login Credentials:";
	cout<<"\nEnter User_Name:";
	cin>>user;
	cin.sync();
	cout<<"\nEnter Password:";
	cin>>ps;
	int choice;
	if(strcmp(user,user_name)==0 && strcmp(password,ps)==0)
	{
    	while(choice!=7)
	    {
			cout<<"\n\t\t\t\t-------------";
			cout<<"\n\t\t\t\t* MAIN MENU *";
			cout<<"\n\t\t\t\t--------------";
			cout<<"\n\n\n\t\t\t1.Book A Room";
			cout<<"\n\t\t\t2.Admin booking Record";
			cout<<"\n\t\t\t3.Admin total Rooms Allotted";
			cout<<"\n\t\t\t4.Overall Rooms Alloted";
			cout<<"\n\t\t\t5.Edit Admin alloted rooms";
			cout<<"\n\t\t\t6.Food Ordering";
			cout<<"\n\t\t\t7.Go back to the menu";
			cout<<"\n\t\t\t8.Exit";
			cout<<"\n\n\t\t\tEnter Your Choice: ";
			cin>>choice;
			switch(choice)
			{
				case 1:	admin_add();
						break;
				case 2: display_admin_bookings();
						break;
				case 3: admin_tot_rooms();
						break;
				case 4: display_user_bookings();
						break;
				case 5: edit_admin_bookings();
						break;
				case 6: f1.main_menu_food();
						break;
				case 7: return;
						break;
				case 8: exit(0);
				        break;
				default:
				{
					cout<<"\n\n\t\t\tWrong choice.....!!!";
					cout<<"\n\t\t\tPress any key to continue....!!";
					getch();
				}
			}
		}
    }
}

void admin::admin_add()
{
	int r,flag;
    char ch;
    int c,t;
	ofstream fout("admin_bookings.dat",ios::app);
	cout<<"\n Enter Customer Detalis:\n";
	cout<<"**********\n";
	cout<<"\n\t\tchoose the room type";
	cout<<"\n**********";
    cout<<"\nRo ROYAL ROOMS\t\t\t\troom number from 1-50";
    cout<<"\n**********";
    cout<<"\nS DELUX ROOMS\t\t\t\troom number from 51-100";
    cout<<"\n**********";
    cout<<"\nRR REGULAR ROOMS\t\t\t room number from 101-150";
    cout<<"\n**********";
    cout<<"\nSS: single suite\t\t\t room number from 151-200";
    cout<<"\n**********";
    cout<<"\nPS: presidental suite\t\t\t room number from 201-250";
	cout<<"\n**********";
	cout<<"\n ----------------------";
	cout<<"\n\n Room no: ";
	cin>>r;
	flag=check_admin(r);
	if(flag)
		cout<<"\n Sorry..!!!Room is already booked";
	else
	{
		room_no=r;
		cout<<" Name: ";
		cin>>name;
		cout<<"Address: ";
		cin>>address;
		cout<<"Phone No: ";
		while(1)
		{
			gets(phone);
			if(strlen(phone)==10)
			break;
			else
			cout<<"Enter a 10-digit phone number";
		}
		cout<<"Number of days you want to stay: ";
		cin>>nod;
		cout<<"How many no. of guests";
		cin>>nogts;
		cout<<"Today's Date: ";
		while(1)
		{
			for(int i=0;i<3;i++)
			{
				cout<<d[i]<<":";
				cin>>date[i];
			}
			if((date[0]>=1&&date[0]<=31)&&(date[1]>=1 && date[1]<=12) && (date[2]>=2021))
			break;
			else
			cout<<"Please enter valid date:)";
		}
		if(room_no>=1 && room_no<=50)
			{
				cout<<"\nIt's a ROYAL ROOM";
				cout<<"\nYou need to pay Rs:1000 per head";
				cost=1000;
			}
			else if(room_no>=51 && room_no<=100)
			{
				cout<<"\nIt's a DELUX ROOM";
				cout<<"\nYou need to pay Rs:750 per head";
				cost=750;
			}
			else if(room_no>=101 && room_no<=150)
			{
				cout<<"\nIt's a REGULAR ROOM";
				cout<<"\nYou need to pay Rs:550 per head";
				cost=550;
			}
			else if(room_no>=151 && room_no<=200)
			{
				cout<<"\nIt's a SINGLE SUITE ROOM";	
				cout<<"\nYou need to pay Rs:450 per head";
				cost=450;
			}
			else
			{
				cout<<"\nIt's a PRESENDTIAL SUITE ROOM";
				cout<<"\nYou need to pay Rs:350 per head";
				cost=350;
			}
		cout<<"Do you want to go to the Billing? (y/n)";
		cin>>ch;
		if(ch=='y')
		{
			cout<<"\nChoose a ppayment method:";
			cout<<"\n1. Credit/Debit Card Payment";
			cout<<"\n2. NetBanking Payment";
			cout<<"\n3. UPI pin";
			cout<<"\nEnter your choice:";
			cin>>c;
			t=payment(c,nod,nogts,cost);
		}
		else
		{
			cout<<"\nSorry Request Timed-Out";
			exit(0);
		}
		tot_amt=t;
		fout.write((char*)this,sizeof(admin));
		fout.close();
	}
}
int admin::check_admin(int r)
{
	int flag=0,flag1=0,temp=0;
	
	ifstream fin("admin_bookings.dat",ios::in);
	ifstream user_fin("user_bookings.dat",ios::in);
	while(!fin.eof())
	{
		fin.read((char*)this,sizeof(admin));
		if(room_no==r)
		{
			flag=1;
			break;
		}
	}
	while(!user_fin.eof())
	{
		user_fin.read((char*)this,sizeof(user));
		if(room_no==r)
		{
			flag1=1;
			break;
		}
	}
	fin.close();
	user_fin.close();
	if(flag==1 || flag1==1)
	     temp=1;
	cout<<"*********"<<temp;
	return(temp);
}
int booking::payment(int c,int nod,int nogts,int cost)
{
	string card;
	char cc;
	int tot;
	
	if(c==1)
	{
		cout<<"\nYou Have Choosen Cedit/Debit Card Payment:";
		cout<<"\nEnter The 12-Digit CARD Number";
		while(1)
		{
			getline(cin,card);
			if(card.length()==12)
			break;
			else
			{
				cout<<"\nEnter the correct Card Number:";
			}
		}
		cout<<"\nDo you want the confirm the payment (y/n):";
		cin>>cc;
		if(cc=='y')
		{
			tot=nod*nogts*cost;
			cout<<"\n(((CONGRATULATIONS)))";
			cout<<"\nTo the given information as follows: \n"<<nogts<<" guests are statying for "<<nod<<" days ";
			cout<<"\nNo of Guests "<<nogts<<" Times to the No. of Days "<<nod<<" with per day cost is :"<<cost;
			cout<<"\nThe Total Amount is "<<tot;
			cout<<"\nYour Payment has been successfully done Through the card number: "<<card;
			return tot;
		}
		else
		{
			cout<<"\nYour are not allowed for the payment";
			exit(0);
		}
	}
	else if(c==2)
	{
		cout<<"\nYou Have Choosen NetBanking Payment:";
		cout<<"\nEnter The 12-Digit NetBanking Number";
		while(1)
		{
			getline(cin,card);
			if(card.length()==12)
			break;
			else
			{
				cout<<"\nEnter the correct Card Number:";
			}
		}
		cout<<"\nDo you want the confirm the payment (y/n):";
		cin>>cc;
		if(cc=='y')
		{
			tot=nod*nogts*cost;
			cout<<"\n(((CONGRATULATIONS)))";
			cout<<"\nTo the given information as follows: \n"<<nogts<<" guests are statying for "<<nod<<" days ";
			cout<<"\nNo of Guests "<<nogts<<" Times to the No. of Days "<<nod<<" with per day cost is :"<<cost;
			cout<<"\nThe Total Amount is "<<tot;
			cout<<"\nYour Payment has been successfully done Through the card number: "<<card;
			return tot;
		}
		else
		{
			cout<<"\nYour are not allowed for the payment";
			exit(0);
		}
	}
	else if(c==3)
	{
		cout<<"\nYou Have Choosen UPI Pin Payment:";
		cout<<"\nEnter The 12-Digit UPI PIN Number";
		while(1)
		{
			getline(cin,card);
			if(card.length()==12)
			break;
			else
			{
				cout<<"\nEnter the correct Card Number:";
			}
		}
		cout<<"\nDo you want the confirm the payment (y/n):";
		cin>>cc;
		if(cc=='y')
		{
			tot=nod*nogts*cost;
			cout<<"\n(((CONGRATULATIONS)))";
			cout<<"\nTo the given information as follows: \n"<<nogts<<" guests are statying for "<<nod<<" days ";
			cout<<"\nNo of Guests "<<nogts<<" Times to the No. of Days "<<nod<<" with per day cost is :"<<cost;
			cout<<"\nThe Total Amount is "<<tot;
			cout<<"\nYour Payment has been successfully done Through the card number: "<<card;
			return tot;
		}
		else
		{
			cout<<"\nYour are not allowed for the payment";
			exit(0);
		}
	}
	else 
	{
		cout<<"\nSelect a valid Method from the above";
		cout<<"\nSorry You are not allowed for the payment:";
		exit(0);
	}		
}
void admin::display_admin_bookings()
{
	ifstream fin("admin_bookings.dat",ios::in);
	
	fin.seekg(0);
	int r,flag=0,ct=0;
	cout<<"\n Enter room no: ";
	cin>>r;
	cout<<"\n*******room:"<<r;
	while(!fin.eof())
	{
		fin.read((char*)this,sizeof(admin));
		if(room_no==r)
		{
			cout<<"\n Cusromer Details";
			cout<<"\n ----------------";
			cout<<"\n\n Room no: "<<room_no;
			cout<<"\n Name of the customer: "<<name;
			cout<<"\n Customer Address: "<<address;
			cout<<"\n Phone: "<<phone;
			cout<<"\n No. of days to be stayed: "<<nod;
			cout<<"\n No. of Guests: "<<nogts;
			cout<<"\n Date of alloted :";
			for(int i=0;i<3;i++)
			{
				cout<<date[i]<<"-";
			}
			flag=1;
		}
		if(flag==1)
		break;
	}
		/*if(ct==1)
		{
			cout<<"\n Cusromer Details";
			cout<<"\n ----------------";
			cout<<"\n\n Room no: "<<room_no;
			cout<<"\n Name of the customer: "<<name;
			cout<<"\n Customer Address: "<<address;
			cout<<"\n Phone: "<<phone;
			cout<<"\n No. of days to be stayed: "<<nod;
			cout<<"\n No. of Guests: "<<nogts;
			cout<<"\n Date of alloted :";
			for(int i=0;i<3;i++)
			{
				cout<<date[i]<<"-";
			}
			flag=1;
		}*/
		if(flag==0)
			cout<<"\n Sorry Room no. not found or vacant....!!";
		cout<<"\n\n Press any key to continue....!!";
		getch();
		fin.close();
}
void admin::display_user_bookings()
{
	user u;
	ifstream fin("admin_bookings.dat",ios::in);
	ifstream user_fin("user_bookings",ios::in);
	//fin.seekg(0);
	cout<<"\n---------------------ADMIN BOOKINGS--------------------------:";
	cout<<"\nRoom_no \tName \t\t Address \t\t No. of Guests \t\t cost_per_head \t Tot_no_Guests \t Total_amout\n";
	cout<<"\n";
	
	while(!fin.eof() && fin.read((char*)this,sizeof(admin)))
	{
		//fin.read((char*)this,sizeof(admin));
		
		cout<<room_no<<"\t\t"<<name<<"\t\t"<<address<<"\t\t"<<nogts<<"\t\t\t"<<cost<<"\t\t\t"<<nogts<<"\t"<<tot_amt<<"\n";
		cout<<"\n";
	}
	u.all_rooms();
	fin.close();
}
void admin::admin_tot_rooms()
{
	ifstream fin("admin_bookings.dat",ios::in);
	fin.seekg(0);
	cout<<"\nRoom_no \tName \t\t Address \t\t No. of Guests \t\t cost_per_head \t Tot_no_Guests \t Total_amout\n";
	cout<<"\n";
	while(!fin.eof() && fin.read((char*)this,sizeof(admin)))
	{
		//fin.read((char*)this,sizeof(*this));
		
		cout<<room_no<<"\t\t"<<name<<"\t\t"<<address<<"\t\t"<<nogts<<"\t\t\t"<<cost<<"\t\t\t"<<nogts<<"\t"<<tot_amt<<"\n";
		cout<<"\n";
	}
}
void admin::edit_admin_bookings()
{
	int choice,r;
	cout<<"\n EDIT MENU";
	cout<<"\n ---------";
	cout<<"\n\n 1.Modify Customer Record";
	cout<<"\n 2.Delete Customer Record";
	cout<<"\n Enter your choice: ";
	cin>>choice;
	cout<<"\n Enter room no: " ;
	cin>>r;
	switch(choice)
	{
		case 1:	modify_admin(r);
				break;
		case 2:	delete_rec_admin(r);
				break;
		default: cout<<"\n Wrong Choice.....!!";
	}
	cout<<"\n Press any key to continue....!!!";
	getch();
}
void admin::modify_admin(int r)
{
	long pos,flag=0;
	fstream file("admin_bookings.dat",ios::in|ios::out);
	while(!file.eof())
	{
		pos=file.tellg();
		file.read((char*)this,sizeof(admin));
		if(room_no==r)
		{
			cout<<"\n Enter New Details";
			cout<<"\n -----------------";
			cout<<"\n : ";
			cout<<" Name:";
			cin>>name;
			cout<<" Address: ";
			cin>>address;
			cout<<" Phone no: ";
			while(1)
			{
				gets(phone);
				if(strlen(phone)==10)
				break;
				else 
				cout<<"Enter exactly 10-digit phone number"<<endl;
			}
			cout<<"Number of days you want to stay: ";
			cin>>nod;
			cout<<"How many no. of guests";
			cin>>nogts;
			cout<<"Today's Date: ";
			while(1)
			{
				for(int i=0;i<3;i++)
				{
					cout<<d[i]<<":";
					cin>>date[i];
				}
				if((date[0]>=1&&date[0]<=31)&&(date[1]>=1 && date[1]<=12) && (date[2]>=2021))
				break;
				else
				cout<<"Please enter valid date:)";
			}
			file.seekg(pos);
			file.write((char*)this,sizeof(admin));
			cout<<"\n Record is modified....!!";
			flag=1;
			break;
		}
	}
	if(flag==0)
	cout<<"\n Sorry Room no. not found or vacant...!!";
	file.close();
}
void admin::delete_rec_admin(int r)
{
	int flag=0;
	char ch;
	int ct=0;
	ifstream fin("admin_bookings.dat",ios::in);
	fin.seekg(0);
	ofstream fout("temp.dat",ios::out);
	while(!fin.eof())
	{
		fin.read((char*)this,sizeof(admin));
		if(room_no==r)
		{
		   cout<<"\n Name: "<<name;
		   cout<<"\n Address: "<<address;
		   cout<<"\n Pone No: "<<phone;
		   cout<<"\n Number of days are: "<<nod;
		   cout<<"\n Number of guests are: "<<nogts;
		   cout<<"\n Date of alloted: ";
			for(int i=0;i<3;i++)
			{
				
				cout<<date[i]<<"-";
			}
		   cout<<"\n\n Do you want to delete this record(y/n): ";
		   cin>>ch;
			if(ch=='n')
		  		fout.write((char*)this,sizeof(admin));
			flag=1;
		}
		else
		fout.write((char*)this,sizeof(admin));
		if(flag==1)
		break;
	}
			
	fin.close();
	fout.close();
	if(flag==0)
		cout<<"\n Sorry room no. not found or vacant...!!";
	else
	{
		remove("admin_bookings.dat");
		rename("temp.dat","admin_bookings.dat");
	}
/******/
}
main()
{
	cout<<"*****WELCOME This is Ajay*****";
	regis r;
	while(1)
	r.menu();
}
