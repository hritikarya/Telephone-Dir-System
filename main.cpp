#include<fstream.h>
#include<conio.h>
#include<string.h>
#include<stdio.h>
#include<ctype.h>

void Create(int);
void DisplayAll();
void Display();
void Edit();
void Deletion();
void SortPno();
void Sortname();


class DIRECTORY
{
	int id;
	int pno;
	char name[20];
	char addr[80];

	public:
		void input();

		int returnID()
		{ return id; }

		int returnPNO()
		{ return pno; }

		char* returnADDR()
		{ return addr; }

		char* returnNAME()
		{ return name; }

		void EditAddress()
		{
			gets(addr);
		}

		void EditName()
		{
			gets(name);
		}

		void EditNumber();

		void EditId(int x)
		{
			id=x;
		}
};
void DIRECTORY::input()
{
	cout<<endl<<"\t Please enter your *4 digit* phone number: ";
	int x;
	cin>>x;
	while (x<1000 || x>9999)
	{
		cout<<endl<<"\t This is not a valid 4 digit number"<<endl;
		cout<<endl<<"\t Please enter your *4 digit* phone number: ";
		cin>>x;
	}
	pno=x;
	cout<<endl<<"\t Please enter your Name: ";
	gets(name);

	cout<<endl<<"\t Please enter your address: ";
	gets(addr);
}
void DIRECTORY::EditNumber()
{
	int x;
	cin>>x;
	while (x<1000 || x>9999)
	{
		cout<<endl<<"\t This is not a valid 4 digit number"<<endl;
		cout<<endl<<"\t Please enter your *4 digit* phone number"<<endl;
		cin>>x;
	}
	pno=x;
}

void main()
{
	clrscr();
	int autoid=0;
	fstream F;
	DIRECTORY D;
	F.open("Dir.dat", ios::binary|ios::in);
	while (F.read((char*)&D, sizeof(D)))
	{
		if (D.returnID()>autoid)
			autoid=D.returnID();
	}
	autoid++;
	F.close();
	cout<<"\n\n\n\n\n\t\t Welcome to the Telephone Directory System \n\t\t Class XII-K";
	cout<<"\n\t\t By Hritik Arya";
	getch();
	char Ch;
	do
	{
		clrscr();
		cout<<"\n\t\t Telephone Directory System \n\n\n";
		cout<<"\n\t 1. Create       : \tAdd a New Record";
		cout<<"\n\t 2. Display      : \tDisplay all existing Record";
		cout<<"\n\t 3. Edit         : \tEdit an existing Record";
		cout<<"\n\t 4. Sort Records : \tAscending Order by Phone Number";
		cout<<"\n\t 5. Sort Records : \tAscending Order by Name";
		cout<<"\n\t 6. Deletion     : \tDelete a Record";
		cout<<"\n\t 7. Search       : \tSearch for a Specific Record";
		cout<<"\n\t 8. Quit";
		cin>>Ch;
		switch(Ch)
		{
			case '1': Create(autoid);
				  autoid++;
				  break;
			case '2': DisplayAll();
				  break;
			case '3': Edit();
				  break;
			case '4': SortPno();
				  break;
			case '5': Sortname();
				  break;
			case '6': Deletion();
				  break;
			case '7': Display();
				  break;
		}
	}while (Ch!='8');
}
void Create(int id)
{
	clrscr();
	fstream Fil;
	DIRECTORY D;
	Fil.open("Dir.dat", ios::binary|ios::app);

	D.EditId(id);
	D.input();
	cout<<endl<<"\t Your ID is : "<<D.returnID()<<endl;

	Fil.write((char*)&D, sizeof(D));
	cout<<"Press any key to continue";
	getch();
	Fil.close();
}
void DisplayAll()
{
	clrscr();
	fstream Fil; DIRECTORY D;
	Fil.open("Dir.dat", ios::binary|ios::in);
	while(Fil.read((char*)&D, sizeof(D)))
	{
		cout<<endl<<"\t ID: "<<D.returnID();
		cout<<endl<<"\t Name: "<<D.returnNAME();
		cout<<endl<<"\t Phone Number: "<<D.returnPNO();
		cout<<endl<<"\t Address: "<<D.returnADDR()<<endl;
		cout<<"\t ###########################";
	}
	Fil.close();
	cout<<endl<<"Press any key to continue";
	getch();
}
void Display()
{
	clrscr();
	fstream Fil; DIRECTORY D;
	int ID, Found=0;
	int opp, phone;
	char sname[20];
	Fil.open("Dir.dat", ios::binary|ios::in);
	cout<<endl<<"\t Enter 1 to search by ID";
	cout<<endl<<"\t Enter 2 to search by Name";
	cout<<endl<<"\t Enter 3 to search by Phone Number";
	cin>>opp;
	if (opp==1)
	{
		cout<<endl<<"\t Enter ID to be searched: ";
		cin>>ID;

		while (Fil.read((char*)&D, sizeof(D)))
		{
			if(D.returnID()==ID)
			{
				cout<<"\t ID: "<<D.returnID()<<endl;
				cout<<"\t Name: "<<D.returnNAME()<<endl;
				cout<<"\t Address: "<<D.returnADDR()<<endl;
				cout<<"\t Phone: Number: "<<D.returnPNO()<<endl;
				cout<<"\t ########################"<<endl;
				Found++;
			}
		}
	} else if (opp==2)
	{
		cout<<endl<<"Enter Name to be searched: ";
		gets(sname);

		while(Fil.read((char*)&D, sizeof(D)))
		{
			if (strcmpi(sname, D.returnNAME())==0)
			{
				cout<<"\t ID: "<<D.returnID()<<endl;
				cout<<"\t Name: "<<D.returnNAME()<<endl;
				cout<<"\t Address: "<<D.returnADDR()<<endl;
				cout<<"\t Phone Number: "<<D.returnPNO()<<endl;
				cout<<"\t #######################"<<endl;
				Found++;
			}
		}
	} else if (opp==3)
	{
		cout<<"Enter phone number to be searched: ";
		cin>>phone;

		while(Fil.read((char*)&D, sizeof(D)))
		{
			if (phone==D.returnPNO())
			{
				cout<<"\t ID: "<<D.returnID()<<endl;
				cout<<"\t Name: "<<D.returnNAME()<<endl;
				cout<<"\t Address: "<<D.returnADDR()<<endl;
				cout<<"\t Phone Number: "<<D.returnPNO()<<endl;
				cout<<"\t #######################"<<endl;
				Found++;
			}
		}
	}

	if (Found==0)
		cout<<endl<<"Oops! Record not found!"<<endl;
	Fil.close();
	cout<<endl<<"Press any key to continue";
	getch();
}
void Edit()
{
	clrscr();
	fstream F;
	F.open("Dir.dat", ios::binary|ios::in|ios::out);
	DIRECTORY D;
	int ID, Found=0;
	int opp;

	cout<<endl<<"Enter 1 to edit Address";
	cout<<endl<<"Enter 2 to edit Phone Number";
	cin>>opp;

	if(opp==1)
	{
		cout<<endl<<"\t Enter the ID number: ";
		cin>>ID;
		while (!Found && F.read((char*)&D, sizeof(D)))
		{
			if (D.returnID()==ID)
			Found++;
		}
		if (Found)
		{
			cout<<endl<<"\t Please enter a new address: ";
			D.EditAddress();
			int N=F.tellg()-sizeof(D);
			F.seekp(N);
			F.write((char*)&D, sizeof(D));
		} else
		{
			cout<<endl<<"\t Oops! No ID matching for editing";
		}
	}
	else if (opp==2)
	{
		cout<<endl<<"\t Enter the ID number: ";
		cin>>ID;
		while (!Found && F.read((char*)&D, sizeof(D)))
		if (D.returnID()==ID)
			Found++;
		if (Found)
		{
			cout<<"Please enter a new Phone Number: ";
			D.EditNumber();
			int N=F.tellg()-sizeof(D);
			F.seekp(N);
			F.write((char*)&D, sizeof(D));
		}
		else
		{
			cout<<endl<<"\t Oops! ID not found!"<<endl;
		}
	}
	F.close();
	cout<<"Press any key to continue";
	getch();
}
void Deletion()
{
	clrscr();
	fstream Fil1, Fil2;
	DIRECTORY D;
	int ID;

	Fil1.open("Dir.dat", ios::binary|ios::in);
	Fil2.open("temp.dat", ios::binary|ios::out);
	cout<<endl<<"Enter ID to be deleted: ";
	cin>>ID;
	int Del=0;

	while (Fil1.read((char*)&D, sizeof(D)))
	{
		if (D.returnID()!=ID)
			Fil2.write((char*)&D, sizeof(D));
		else
			Del++;
	}
	if (!Del)
		cout<<endl<<"\t Oops! ID not found!"<<endl;
	else
		cout<<endl<<"\t ID successfully deleted"<<endl;
	cout<<endl<<"Press any key to continue"<<endl;
	getch();
	Fil1.close();
	Fil2.close();
	remove("Dir.dat");
	rename("temp.dat", "Dir.dat");
}
void SortPno()
{
	clrscr();
	fstream F;
	F.open("Dir.dat", ios::binary|ios::in|ios::out);
	DIRECTORY D;

	F.seekg(0, ios::end);
	int NOR=F.tellg()/sizeof(D);
	DIRECTORY DelFile, DelFile1;
	for (int i=0; i<NOR-1; i++)
		for (int j=0; j<NOR-1; j++)
		{
			F.seekg(j*sizeof(D));
			F.read((char*)&DelFile, sizeof(D));
			F.read((char*)&DelFile1, sizeof(D));
			if (DelFile.returnPNO()>DelFile1.returnPNO())
			{
				F.seekp(j*sizeof(D));
				F.write((char*)&DelFile1, sizeof(D));
				F.write((char*)&DelFile, sizeof(D));
			}
		}
	F.close();
	DisplayAll();
	getch();
}
void Sortname()
{
	clrscr();
	fstream F;
	DIRECTORY D;
	F.open("Dir.dat", ios::binary|ios::in|ios::out);

	F.seekg(0, ios::end);
	int NOR=F.tellg()/sizeof(D);
	DIRECTORY DelFile, DelFile1;
	for (int i=0; i<NOR-1; i++)
	{
		for(int j=0; j<NOR-i-1; j++)
		{
			F.seekg(j*sizeof(D));
			F.read((char*)&DelFile, sizeof(D));
			F.read((char*)&DelFile1, sizeof(D));
			if (strcmpi(DelFile.returnNAME(), DelFile1.returnNAME()) > 0)
			{
				F.seekp(j*sizeof(D));
				F.write((char*)&DelFile1, sizeof(D));
				F.write((char*)&DelFile, sizeof(D));
			}
		}
	}
	F.close();
	DisplayAll();
}

