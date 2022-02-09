//------------------------------------------------------ Header Files --------------------------------------------------------------
#include<iostream>
#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<cstring>                                                      //working with string in better(getline)
#include<windows.h>                                                    //coordinate(gotoxy,clrscr)
#include<unistd.h>                                                     //Time(sleep)
#include<fstream>                                                      //work with files(Load,Save)
#include<algorithm>                                                    //uppercase the word

using namespace std;
//----------------------------------------------- Definition of Constant Values ----------------------------------------------------
#define N 5                                                               // y axis of each Screen
#define P 100                                                             // Number of Persons
#define G 200                                                             // Number of Goods
#define L 30                                                              // x axis of Logo Screen
#define C 55                                                              // x axis of each Screen
#define F 35                                                              // minesing C for Place of THANK YOU FOR BUYING
//------------------------------------------ Definition of Data Structures & variables ---------------------------------------------
int ID;                                                                //Id of each person for know who is it(search)
int Type = -1;                                                         //Type of each persno for know which access who has.
int pcount=0;                                                          //Number of Persons that SignIn
int gcount=0;                                                          //Number of Goods
int ccount=0;
string Code = "DigiMahal!13812";                                       //The code that if someone write it we know hi/she is employee.
string Chert,Chert2;                                                   //for transformating str to int with stoi()
string color;
int counter=0;
int Scategory;                                                         //Selected Category
int NSgoods=0;                                                         //Number of Selected Goods
int Payment=0;                                                         //Price of Goods(whithout mail)
int Mail_Payment=0;                                                    //Price of Mail
int Tamam=0;                                                           //exit from the Application

string C1 ="\x1B[";                                                    //Coloring
string C2 ="\033[0m";
string Red = "31m";
string Green = "32m";
string Yellow = "33m";
string Blue = "34m";
string Purple = "35m";
string Turquoise = "36m";
string Gray = "90m";
string red = "91m";
string green = "92m";
string yellow = "93m";
string blue = "94m";
string pink = "95m";
string turquoise = "96m";

struct Person{
	int  ID;                                                           //each Person has a Id
	int  Type;                                                         //employee or customer
	int  Zip_Code;                                                     //Number of Mahalle
	string First_name;
	string Last_name;
	string CellPhone;
	string Address;
	string Username;                                                   //for Login
	string Password;                                                   //for Login
}; struct Person person[100];

struct Goods{
	int Code;                                                          //each Goods has a code
	string Name;
	string Category;                                                   //Type of Goods
	int Goods_price;
}; struct Goods goods[200];

struct Category{
	string Name;
	int Count;
	int ID;
}; struct Category Cat[200];

struct SGoods{                                                             //Information of Selected goods                                                             
	int Code;
	int Number;
}; struct SGoods SCat[100];
//-------------------------------------------------- Define Essential Function ---------------------------------------------------------------
void gotoxy(int x, int y){                                                 //Making gotoxy() function
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
//---------------------------------------------------- Prototype Of Functions -----------------------------------------------------------------
void Save(void);
void Load(void);

void Logo(void);
int Welcome(void);
	int Login(void);
	void SignUp(void);

void Company_Menu(void);
	void Input_Data_Of_Goods(void);
	void Search_In_Goods(void);
	void Search_In_Persons(void);
	void Delete_Goods(void);

void Customers_Menu(void);
	void Category (void);
		void List_Of_Goods(void);
	void Information(void);
	void Orders (void);

void Color(void);
void Prices (void);
void Mail (void);
void Sale_Facture (void);
void End(void);
//------------------------------------------------------ Main Function ----------------------------------------------------------------------
int main(){
	if (Tamam == 1)
		goto L20;
	Load();
	Logo();	
	switch(Welcome()){
		case 1:
			Login();
			break;
		case 2:
			SignUp();	 	
			break;
	}
	switch(Type){
		case 0:
			Customers_Menu();
			break;
		case 1:
			Company_Menu();
			break;
	}
	L20:
	Save();
	End();
	return 0;
}
//-------------------------------------------------------- 1) Save --------------------------------------------------------------------------
void Save(void){                     //the algorithm of save and load is making a line of string and seprate they with each other with _ and using endl
	string str;

	ofstream fc;                     //file counts       // output fstream >> Write
	fc.open("Count.txt");
	fc << pcount << endl << gcount << endl << ccount;
	fc.close();

	ofstream fp;                     //file persons
	fp.open("Persons.txt");
	for(int i=1;i<=pcount;i++){
		str = to_string(person[i].ID)+ "_" + to_string(person[i].Type) + "_" + to_string(person[i].Zip_Code) + "_"
			+ person[i].First_name + "_" + person[i].Last_name +"_"+ person[i].CellPhone +"_"+ person[i].Address + "_"
			+ person[i].Username + "_" + person[i].Password + "_";
	fp << str << endl;
	}
	fp.close();

	ofstream fg;                     //file goods
	fg.open("Goods.txt");
	for(int i=1;i<=gcount;i++){
		str = to_string(goods[i].Code)+ "_" + goods[i].Name + "_" + goods[i].Category + "_"
			+ to_string(goods[i].Goods_price) + "_";
	fg << str << endl;
	}
	fg.close();

	ofstream fa;
	fa.open("Category.txt");
	for(int i=1;i<=ccount;i++){
		str = Cat[i].Name + "_" + to_string(Cat[i].Count) + "_" + to_string(Cat[i].ID) + "_";
		fa << str << endl;
	}
	fa.close();
}
//-------------------------------------------------------- 2) Load --------------------------------------------------------------------------
void Load(void){
	string line;
	
	ifstream fp("Persons.txt");
	int num=1;
	if(fp.is_open()){
		while(getline(fp,line)){
			int j=0;
			string arr[10];
			for(int i=0;i<line.length();i++){
				Chert = line[i];
				if(Chert!="_"){
					arr[j]+=line[i];
				}else{
					j++;
				}
			}
			person[num].ID = stoi(arr[0]);
			person[num].Type = stoi(arr[1]);
			person[num].Zip_Code = stoi(arr[2]);
			person[num].First_name = arr[3];
			person[num].Last_name = arr[4];
			person[num].CellPhone = arr[5];
			person[num].Address = arr[6];
			person[num].Username = arr[7];
			person[num].Password = arr[8];

			num++;
		}
		fp.close();
	}

	ifstream fg("Goods.txt");
	num=1;
	if(fg.is_open()){
		while(getline(fg,line)){
			int j=0;
			string arr[5];
			for(int i=0;i<line.length();i++){
				Chert = line[i];
				if(Chert!="_"){
					arr[j]+=line[i];
				}else{
					j++;
				}
			}
			goods[num].Code = stoi(arr[0]);
			goods[num].Name = arr[1];
			goods[num].Category = arr[2];
			goods[num].Goods_price = stoi(arr[3]);

			num++;
		}
		fg.close();
	}

	num=1;
	ifstream fa("Category.txt");
	if(fa.is_open()){
		while(getline(fa,line)){
			int j=0;
			string arr[3];
			for(int i=0;i<line.length();i++){
				Chert = line[i];
				if(Chert!="_"){
					arr[j]+=line[i];
				}else{
					j++;
				}
			}
			Cat[num].Name = arr[0];
			Cat[num].Count = stoi(arr[1]);
			Cat[num].ID = stoi(arr[2]);
			num++;
		}
		fa.close();
	}

	ifstream fc("Count.txt");
	if(fc.is_open()){
		getline(fc,Chert); pcount = stoi(Chert);
		getline(fc,Chert); gcount = stoi(Chert);
		getline(fc,Chert); ccount = stoi(Chert);
		fc.close();
	}
}
//-------------------------------------------------------- 3) Logo --------------------------------------------------------------------------
void Logo(void){ 
	string color1,color2,color3; int counter=1;
	color1=Blue; color2=Red; color3=Yellow; usleep(500000);
	system("cls");
	L1:                                                                                                      
	gotoxy(L,N+0); cout<<C1+color1+"                 /DDDDDDDDDDDDDDDDDDDDDDDDDDDDn                                                    "+C2;
	gotoxy(L,N+1); cout<<C1+color1+"           /DDDDDDDD/       nDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD                                  "+C2;
	gotoxy(L,N+2); cout<<C1+color1+"       /DDDDDDDD/     DDD             /DDDDD/          DDDDDDDDDDDDDDDDDDD                         "+C2;
	gotoxy(L,N+3); cout<<C1+color1+"    /DDDDDDDDDD         DDD          /DDDDD/                       DDDDDDDDDDDDD                   "+C2;
	gotoxy(L,N+4); cout<<C1+color1+"       DDDDDDDDDDD   DDDDDDD        /DDDDD/                                DDDDDDDDDD              "+C2;
	gotoxy(L,N+5); cout<<C1+color1+"             DDDDDDDDDDDD          /DDDDD/                                       DDDDDDDD          "+C2;
	gotoxy(L,N+6); cout<<C1+color1+"                 DDDDDD           /DDDDD/     "+C2+C1+color2+"                       MMM        "+C2+C1+color1+"    DDDDDDD        "+C2;
	gotoxy(L,N+7); cout<<C1+color1+"                   DD            /DDDDD/      "+C2+C1+color2+"                      MMMMM      "+C2+C1+color1+"          DDDD      "+C2;
	gotoxy(L,N+8); cout<<C1+color1+"                                /DDDDD/     "+C2+C1+color2+"                       MMMMMMMM      "+C2+C1+color1+"          dDDD    "+C2;
	gotoxy(L,N+9); cout<<C1+color1+"                               /DDDDD/  "+C2+C1+color2+"  MMMM                    MMMMMMMMMMM        "+C2+C1+color1+"        DDDD  "+C2;
	gotoxy(L,N+10);cout<<C1+color1+"                              /DDDDD/  "+C2+C1+color2+"  MMMMMM                  MMMMM^^^MMMMM    "+C2+C1+color1+"            DDDD "+C2;
	gotoxy(L,N+11);cout<<C1+color1+"                             /DDDDD/  "+C2+C1+color2+"  MMMMMMMM                MMMMM^^^^^MMMMM       "+C2+C1+color1+"        DDDD "+C2;
	gotoxy(L,N+12);cout<<C1+color1+"                            /DDDDD/  "+C2+C1+color2+"  MMMMM^^MMMMM            MMMMM^^^^^^^MMMMM      "+C2+C1+color1+"       DDDD  "+C2;
	gotoxy(L,N+13);cout<<C1+color1+"                           /DDDDD/  "+C2+C1+color2+"  MMMMM^^^^MMMMM          MMMMM^^^^^^^^^MMMMM    "+C2+C1+color1+"      DDDD    "+C2;
	gotoxy(L,N+14);cout<<C1+color1+"                          /DDDDD/  "+C2+C1+color2+"  MMMMM^^^^^^MMMMM        MMMMM           MMMMM   "+C2+C1+color1+"    DDDD      "+C2;
	gotoxy(L,N+15);cout<<C1+color1+"                         /DDDDD/  "+C2+C1+color2+"  MMMMM^^^^^^^^MMMMM      MMMMM             MMMMM  "+C2+C1+color1+"  DDDD        "+C2;
	gotoxy(L,N+16);cout<<C1+color1+"                        /DDDDD/  "+C2+C1+color2+"  MMMMM^^^^^^^^^^MMMMM    MMMMM       "+C2+C1+color1+"              DDDD          "+C2;
	gotoxy(L,N+17);cout<<C1+color1+"                       /DDDDD/ "+C2+C1+color2+"   MMMMM            MMMMM  MMMMM     "+C2+C1+color1+"              DDDD             "+C2;
	gotoxy(L,N+18);cout<<C1+color1+"                      /DDDDD/  "+C2+C1+color2+"  MMMMM              MMMMMMMMM     "+C2+C1+color1+"            DDDDD                "+C2;
	gotoxy(L,N+19);cout<<C1+color1+"                     /DDDDD/ "+C2+C1+color2+"   MMMMM                 MMMMM      "+C2+C1+color1+"          DDDDD                   "+C2;
	gotoxy(L,N+20);cout<<C1+color1+"                    /DDDDD/  "+C2+C1+color2+"  MMMMM          "+C2+C1+color1+"                       DDDDD/                        "+C2;
	gotoxy(L,N+21);cout<<C1+color1+"                   /DDDDD/  "+C2+C1+color2+"  MMMMM            "+C2+C1+color1+"                 DDDDDDD/                           "+C2;
	gotoxy(L,N+22);cout<<C1+color1+"                  /DDDDD/ "+C2+C1+color2+"   MMMMM           "+C2+C1+color1+"             DDDDDDD/                                 "+C2;
	gotoxy(L,N+23);cout<<C1+color1+"                 /DDDDD/                          DDDDDDDDDDDD/                                    "+C2;
	gotoxy(L,N+24);cout<<C1+color1+"                /DDDDD/                 DDDDDDDDDDDDDDD/                                           "+C2;
	gotoxy(L,N+25);cout<<C1+color1+"               /DDDDD/       DDDDDDDDDDDDDDDDDDD/                                                  "+C2;
	gotoxy(L,N+26);cout<<C1+color1+"    /DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD/                                                         "+C2;
	gotoxy(L,N+27);cout<<C1+color1+"           /DDDDDDD/                                                                               "+C2;
	gotoxy(L,N+28);cout<<C1+color1+"          /DDDDDDD/                                           "+C2+C1+color3+"         DigiMahal_Company           "+C2;
	gotoxy(L,N+29);cout<<C1+color3+"                                                                       Copy_Right (2022)           "+C2;
	 
	 switch(counter){
		case 1:
			color1=green; color2=Yellow; color3=turquoise; usleep(500000); counter++; goto L1; 
		case 2:
			color1=pink; color2=Turquoise; color3=red; usleep(500000); counter++; goto L1; 
		case 3:	
			color1=Green; color2=Red; color3=Purple; usleep(500000); counter++; goto L1;			
		case 4:
			color1=Blue; color2=Yellow; color3=blue; usleep(500000); counter++; goto L1;
		case 5:	
			color1=Gray; color2=yellow; color3=red; usleep(500000); counter++; goto L1; 
	 }
}
//-------------------------------------------------------- 4) Welcome -----------------------------------------------------------------------
int Welcome(void){
	int x=0;
	Color();
	L1:
	system("cls");
	gotoxy(C,N+0); cout<<C1+color+"================================================================================\n"+C2;
	gotoxy(C,N+1); cout<<C1+color+"=====                                                                      =====\n"+C2;
	gotoxy(C,N+2); cout<<C1+color+"=====                   ***[ Hi man/woman! Welcome to ]***                 =====\n"+C2;
	gotoxy(C,N+3); cout<<C1+color+"=====                   ***[        DigiMahal         ]***                 =====\n"+C2;
	gotoxy(C,N+4); cout<<C1+color+"=====                                                                      =====\n"+C2;
	gotoxy(C,N+5); cout<<C1+color+"================================================================================\n"+C2;
	gotoxy(C,N+6); cout<<C1+color+"=====                                                                      =====\n"+C2;
	gotoxy(C,N+7); cout<<C1+color+"=====     1) Login                                                         =====\n"+C2;
	gotoxy(C,N+8); cout<<C1+color+"=====     2) SignUp                                                        =====\n"+C2;
	gotoxy(C,N+9); cout<<C1+color+"=====                                                                      =====\n"+C2;
	gotoxy(C,N+10);cout<<C1+color+"================================================================================\n"+C2;
	gotoxy(C,N+11);cout<<C1+color+"=====     Select Item (1 or 2) :                                           =====\n"+C2;
	gotoxy(C,N+12);cout<<C1+color+"================================================================================\n"+C2;//L:80.
	gotoxy(C+33,N+11); getline(cin,Chert); x = stoi(Chert);
	if(x==1){
		return 1;
	}else if(x==2){				
		return 2;
	}else{
		goto L1;
	}
}
//-------------------------------------------------------- 5) Login -------------------------------------------------------------------------
int Login(void){
	string username;
	string password;
	do{
		system("cls");
		Color();
		gotoxy(C,N+0); cout<<C1+color+"================================================================================\n"+C2;
		gotoxy(C,N+1); cout<<C1+color+"=====                                                                      =====\n"+C2;
		gotoxy(C,N+2); cout<<C1+color+"=====                        ***[ Login Page ]***                          =====\n"+C2;
		gotoxy(C,N+3); cout<<C1+color+"=====                                                                      =====\n"+C2;
		gotoxy(C,N+4); cout<<C1+color+"================================================================================\n"+C2;
		gotoxy(C,N+5); cout<<C1+color+"=====                                                                      =====\n"+C2;
		gotoxy(C,N+6); cout<<C1+color+"=====     Username :                                                       =====\n"+C2;
		gotoxy(C,N+7); cout<<C1+color+"=====     Password :                                                       =====\n"+C2;
		gotoxy(C,N+8); cout<<C1+color+"=====                                                                      =====\n"+C2;
		gotoxy(C,N+9); cout<<C1+color+"================================================================================\n"+C2;
		gotoxy(C,N+10);cout<<C1+color+"=====     Do You Want To Login(Y/y) Exit(E/e) :                            =====\n"+C2;
		gotoxy(C,N+11);cout<<C1+color+"================================================================================\n"+C2;
		
		gotoxy(C+21,N+6); getline(cin,username);
		gotoxy(C+21,N+7); getline(cin,password);

		gotoxy(C+48,N+10); getline(cin,Chert);
		if (Chert=="E" || Chert=="e"){
			return 0;
		}else if(Chert=="Y" || Chert=="y"){
			for(int i=1;i<=pcount;i++){
				if(person[i].Username==username && person[i].Password==password){                    // if we have this username and password before, login!
					ID = person[i].ID;
					Type = person[i].Type;
					return 0;
				}
			}
		}
	}while(1);
}
//-------------------------------------------------------- 6) SignUp ------------------------------------------------------------------------
void SignUp(void){
	string companycode;
	do{
		if(Tamam==1){
			break;
		}
		system("cls");
		Color();
		gotoxy(C,N+0); cout<<C1+color+"================================================================================\n"+C2;
		gotoxy(C,N+1); cout<<C1+color+"=====                                                                      =====\n"+C2;
		gotoxy(C,N+2); cout<<C1+color+"=====                        ***[ SignUp Page ]***                         =====\n"+C2;
		gotoxy(C,N+3); cout<<C1+color+"=====                                                                      =====\n"+C2;
		gotoxy(C,N+4); cout<<C1+color+"================================================================================\n"+C2;
		gotoxy(C,N+5); cout<<C1+color+"=====                                                                      =====\n"+C2;
		gotoxy(C,N+6); cout<<C1+color+"=====    First Name :                                                      =====\n"+C2;
		gotoxy(C,N+7); cout<<C1+color+"=====    Last Name :                                                       =====\n"+C2;
		gotoxy(C,N+8); cout<<C1+color+"=====    CellPhone :                                                       =====\n"+C2;
		gotoxy(C,N+9); cout<<C1+color+"=====    ZipCode(Your Mahalle/Number) :                                    =====\n"+C2;
		gotoxy(C,N+10);cout<<C1+color+"=====    Address :                                                         =====\n"+C2;
		gotoxy(C,N+11);cout<<C1+color+"=====    Company Code(If you have) :                                       =====\n"+C2;
		gotoxy(C,N+12);cout<<C1+color+"=====    Username :                                                        =====\n"+C2;
		gotoxy(C,N+13);cout<<C1+color+"=====    Password :                                                        =====\n"+C2;
		gotoxy(C,N+14);cout<<C1+color+"=====                                                                      =====\n"+C2;
		gotoxy(C,N+15);cout<<C1+color+"================================================================================\n"+C2;
		gotoxy(C,N+16);cout<<C1+color+"=====    Do You wanna SignIn(Y/y) |defualt N) Or E/e :                     =====\n"+C2;
		gotoxy(C,N+17);cout<<C1+color+"================================================================================\n"+C2;//L:80.


		gotoxy(C+22,N+6);  getline(cin,person[pcount+1].First_name); 
		gotoxy(C+21,N+7);  getline(cin,person[pcount+1].Last_name); 
		gotoxy(C+21,N+8);  getline(cin,person[pcount+1].CellPhone); 
		gotoxy(C+40,N+9);  getline(cin,Chert); person[pcount+1].Zip_Code = stoi(Chert); 
		gotoxy(C+19,N+10); getline(cin,person[pcount+1].Address); 
		gotoxy(C+37,N+11); getline(cin,companycode); 
		gotoxy(C+20,N+12); getline(cin,person[pcount+1].Username); 
		gotoxy(C+20,N+13); getline(cin,person[pcount+1].Password); 

		string YN;
		gotoxy(C+55,N+16); getline(cin,YN);
		if(YN=="e" || YN=="E"){
			break;
		}

		int same=0;                                                             // for check that nobody that has same username loged in.
		for(int i=0;i<=pcount;i++){
			if(person[i].Username==person[pcount+1].Username){
				same=1;
				break;
			} 
		}

		if((YN=="Y" || YN=="y")&&same==0){                                  // check he want to signin and save the data or not
			if(companycode==Code) {person[pcount+1].Type=1;}
			else{person[pcount+1].Type=0;}
			person[pcount+1].ID = pcount+1;                                    //Number of Person++ and go to the Next index of Struct
			ID = person[pcount+1].ID;
			Type = person[pcount+1].Type;
			pcount++;
			break;
		}
	}while(1);
}
//-------------------------------------------------------- 7) Company Menu ------------------------------------------------------------------
void Company_Menu(void){
	do{
		system("cls");
		Color();
		int x=0;
		gotoxy(C,N+0); cout<<C1+color+"================================================================================\n"+C2;
		gotoxy(C,N+1); cout<<C1+color+"=====                                                                      =====\n"+C2;
		gotoxy(C,N+2); cout<<C1+color+"=====                        ***[ Company Menu ]***                        =====\n"+C2;
		gotoxy(C,N+3); cout<<C1+color+"=====                                                                      =====\n"+C2;
		gotoxy(C,N+4); cout<<C1+color+"================================================================================\n"+C2;
		gotoxy(C,N+5); cout<<C1+color+"=====                                                                      =====\n"+C2;
		gotoxy(C,N+6); cout<<C1+color+"=====    1) Input Data Of Goods                                            =====\n"+C2;
		gotoxy(C,N+7); cout<<C1+color+"=====    2) Search And Edit Goods                                          =====\n"+C2;
		gotoxy(C,N+8); cout<<C1+color+"=====    3) Search And Edit Persons                                        =====\n"+C2;
		gotoxy(C,N+9); cout<<C1+color+"=====    4) Delete Goods                                                   =====\n"+C2;
		gotoxy(C,N+10);cout<<C1+color+"=====                                                                      =====\n"+C2;
		gotoxy(C,N+11);cout<<C1+color+"================================================================================\n"+C2;
		gotoxy(C,N+12);cout<<C1+color+"=====    Select Item (1 to 4) or Exit(E/e) :                               =====\n"+C2;
		gotoxy(C,N+13);cout<<C1+color+"================================================================================\n"+C2;
		gotoxy(C+45,N+12); getline(cin,Chert);
		
		if(Chert=="e" || Chert=="E")
			break;
		//goto L20;
		x = stoi(Chert);
		switch(x){
			case 1:Input_Data_Of_Goods();	break;
			case 2:Search_In_Goods();		break;
			case 3:Search_In_Persons();		break;
			case 4:Delete_Goods();			break;
		}
	}while(1);
	Tamam=1;
	main();
}
//-------------------------------------------------------- 8) Search In Goods ---------------------------------------------------------------
void Search_In_Goods(void){
	Color();
	string items;
	string item;
	int che;																// to now backspace and esc
	string srch;
	int moze;															// we get this string to search
	system("cls");
	gotoxy(C,N+0); cout<<C1+color+"================================================================================\n"+C2;
	gotoxy(C,N+1); cout<<C1+color+"=====     Search The Good's Name (You Can Press 'esc' Key To Get Back).    =====\n"+C2;
	gotoxy(C,N+2); cout<<C1+color+"======================= = = = = = = = = = = = = = = = = = ======================\n"+C2;
	gotoxy(C,N+3); cout<<C1+color+"=====    Search :                                                          =====\n"+C2;
	gotoxy(C,N+4); cout<<C1+color+"================================================================================\n"+C2;
	for(int j=C+18;j<160;j++){
		L11:
		gotoxy(C,N+5); cout<<C1+color+"=====             Press Enter to Choose Items : -                          =====\n"+C2;
		gotoxy(C,N+6); cout<<C1+color+"================================================================================\n"+C2;
		gotoxy(j,N+3); srch[j-C-18]=getch(); che=srch[j-C-18];
		gotoxy(j,N+3);cout<<srch[j-C-18];
		switch (che){
		case 27: Company_Menu();
			break;
		case 8:  
			if(j>C+18-1){
			gotoxy(j-1,N+3);  cout<<" ";
			j--;
			}
			goto L11;
			break;
		case 13: gotoxy(C+48,N+5); getline(cin,item); goto L14;
			break;
		}
		if (j<=C+18+0) continue;
		for(moze=1;moze<=30;moze++){
			gotoxy(C,N+9+moze); cout<<"                                                                                 \n";
		}
		gotoxy(C,N+6); cout<<C1+color+"================================================================================\n"+C2;
		gotoxy(C,N+7); cout<<C1+color+"=====                           [ Found Goods ]                            =====\n"+C2;
		gotoxy(C,N+8); cout<<C1+color+"================================================================================\n"+C2;
		int m=0;
		int m1;
		for(int i=1;i<=gcount;i++){
			int k=0;
			int l=0;
			for(int k=0;k<=j-C-18;k++){ 	
				if (srch[l]==goods[i].Name[k])
				l++;}
	
			if(l==j-C-18+1){	
				gotoxy(C,N+9+3*m); cout<<C1+color+"=====    1)Name :                                                          =====\n"+C2;
				gotoxy(C,N+10+3*m);cout<<C1+color+"= "+to_string(m+1)+" =    2)Code :                                                          =====\n"+C2;
				gotoxy(C,N+11+3*m);cout<<C1+color+"================================================================================\n"+C2;
				gotoxy(C+18,N+9+3*m); cout<<C1+color+goods[i].Name+C2;
				gotoxy(C+18,N+10+3*m);cout<<C1+color+to_string(goods[i].Code)+C2;
				m++;
				
				items[m]=i;
			}
		}
		continue;
	}

	L14:
	system("cls");
	Color(); 
	int i,ii;
	ii=stoi(item);
	i=items[ii];
	L5:
	gotoxy(C,N+6); cout<<C1+color+"================================================================================\n"+C2;
	gotoxy(C,N+7); cout<<C1+color+"=====                                                                      =====\n"+C2;
	gotoxy(C,N+8); cout<<C1+color+"=====                        ***[ Good's Data ]***                         =====\n"+C2;
	gotoxy(C,N+9); cout<<C1+color+"=====                                                                      =====\n"+C2;
	gotoxy(C,N+10);cout<<C1+color+"================================================================================\n"+C2;
	gotoxy(C,N+11);cout<<C1+color+"=====                                                                      =====\n"+C2;
	gotoxy(C,N+12);cout<<C1+color+"=====    1)Name :                                                          =====\n"+C2;
	gotoxy(C,N+13);cout<<C1+color+"=====    2)Code :                                                          =====\n"+C2;
	gotoxy(C,N+14);cout<<C1+color+"=====    3)Category :                                                      =====\n"+C2;
	gotoxy(C,N+15);cout<<C1+color+"=====    4)Price :                                                         =====\n"+C2;
	gotoxy(C,N+16);cout<<C1+color+"=====                                                                      =====\n"+C2;
	gotoxy(C,N+17);cout<<C1+color+"================================================================================\n"+C2;
	gotoxy(C,N+18);cout<<C1+color+"=====        Enter Number Of Each Case To Edit Or(b/B)To Get Back:-        =====\n"+C2;
	gotoxy(C,N+19);cout<<C1+color+"================================================================================\n"+C2;
	gotoxy(C+18,N+12); cout<<goods[i].Name;
	gotoxy(C+18,N+13); cout<<goods[i].Code;
	gotoxy(C+22,N+14); cout<<goods[i].Category;
	gotoxy(C+19,N+15); cout<<goods[i].Goods_price;
	gotoxy(C+66,N+18); getline(cin,Chert);
	
	if(Chert=="B" || Chert=="b"){
		Company_Menu();	
	}
	int x = stoi(Chert);
	switch(x){
		case 1:gotoxy(C+5,N+18);cout<<C1+color+"==  Enter The New Name :                                       "+C2;
					gotoxy(C+29,N+18);getline(cin,Chert); goods[i].Name=Chert;					break;
		case 2:gotoxy(C+5,N+18);cout<<C1+color+"==  Enter The New Code :                                       "+C2;
					gotoxy(C+29,N+18);getline(cin,Chert); goods[i].Code=stoi(Chert);			break;
		case 3:gotoxy(C+5,N+18);cout<<C1+color+"==  Enter The New Category :                                   "+C2;
					gotoxy(C+33,N+18);getline(cin,Chert); goods[i].Category=Chert;				break;
		case 4:gotoxy(C+5,N+18);cout<<C1+color+"==  Enter The New Price :                                      "+C2;
					gotoxy(C+30,N+18);getline(cin,Chert); goods[i].Goods_price=stoi(Chert);	break;
	} 		
	goto L5;
}
//-------------------------------------------------------- 9) Search In Persons -------------------------------------------------------------
void Search_In_Persons(void){
	char ch;                                          //to get a simple character like "y" mean's yes
    string namelname;									//to join name and last name and have them together
	string srch;
	system("cls");
	Color();
	gotoxy(C,N+0); cout<<C1+color+"================================================================================\n"+C2;
	gotoxy(C,N+1); cout<<C1+color+"=====    Enter The Persons ID or First Name & Last Name or UserName        =====\n"+C2;
	gotoxy(C,N+2); cout<<C1+color+"=====                                                                      =====\n"+C2;
	gotoxy(C,N+3); cout<<C1+color+"=====    Search :                                                          =====\n"+C2;
	gotoxy(C,N+4); cout<<C1+color+"================================================================================\n"+C2;
	gotoxy(C+18,N+3); getline(cin,srch);
	for(int i=1;i<=pcount;i++){
		namelname = person[i].First_name+" "+person[i].Last_name;
		int a=0;
		try{
			a = stoi(srch);	
		}catch(exception &err){}
        if(srch==namelname || a==person[i].ID || srch==person[i].Username){
			L6:
			gotoxy(C,N+6); cout<<C1+color+"================================================================================\n"+C2;
			gotoxy(C,N+7); cout<<C1+color+"=====                                                                      =====\n"+C2;
			gotoxy(C,N+8); cout<<C1+color+"=====                      ***[         's Data ]***                       =====\n"+C2;
			gotoxy(C,N+9); cout<<C1+color+"=====                                                                      =====\n"+C2;
			gotoxy(C,N+10);cout<<C1+color+"================================================================================\n"+C2;
			gotoxy(C,N+11);cout<<C1+color+"=====                                                                      =====\n"+C2;
			gotoxy(C,N+12);cout<<C1+color+"=====    1)First name :                                                    =====\n"+C2;
			gotoxy(C,N+13);cout<<C1+color+"=====    2)Last name :                                                     =====\n"+C2;
			gotoxy(C,N+14);cout<<C1+color+"=====    3)Phon number :                                                   =====\n"+C2;
			gotoxy(C,N+15);cout<<C1+color+"=====    4)Zip code(Mahalle number) :                                      =====\n"+C2;
			gotoxy(C,N+16);cout<<C1+color+"=====    5)ID :                                                            =====\n"+C2;
			gotoxy(C,N+17);cout<<C1+color+"=====    6)Address :                                                       =====\n"+C2;
			gotoxy(C,N+18);cout<<C1+color+"=====    7)Username :                                                      =====\n"+C2;
			gotoxy(C,N+19);cout<<C1+color+"=====    8)Password :                                                      =====\n"+C2;
			gotoxy(C,N+20);cout<<C1+color+"=====                                                                      =====\n"+C2;
			gotoxy(C,N+21);cout<<C1+color+"================================================================================\n"+C2;
			gotoxy(C,N+22);cout<<C1+color+"=====        Enter Number Of Each Case To Edit Or(b/B)To Get Back:-        =====\n"+C2;
			gotoxy(C,N+23);cout<<C1+color+"================================================================================\n"+C2;
			gotoxy(C+24,N+12);cout<<person[i].First_name;
			gotoxy(C+23,N+13);cout<<person[i].Last_name;
			gotoxy(C+25,N+14);cout<<person[i].CellPhone;
			gotoxy(C+38,N+15);cout<<person[i].Zip_Code;	
			gotoxy(C+16,N+16);cout<<person[i].ID;
			gotoxy(C+21,N+17);cout<<person[i].Address;
			gotoxy(C+21,N+18);cout<<person[i].Username;
			gotoxy(C+21,N+19);cout<<person[i].Password;
			gotoxy(C+32,N+8);
			if(0==person[i].Type) 		cout<<C1+color+"Customer"+C2;
			else if(1==person[i].Type)	cout<<C1+color+"Employee"+C2;
			gotoxy(C+66,N+22); getline(cin,Chert);
			
			if(Chert=="B" || Chert=="b"){
				Company_Menu();	
				break;
			}
			int x = stoi(Chert);
			switch(x){
				case 1:gotoxy(C+3,N+22);cout<<C1+color+"==  Enter The New First Name :                        =="+C2;
				         gotoxy(C+34,N+22);getline(cin,Chert); person[i].First_name=Chert;			break;
				case 2:gotoxy(C+3,N+22);cout<<C1+color+"==  Enter The New Last Name :                         =="+C2;
				         gotoxy(C+33,N+22);getline(cin,Chert); person[i].Last_name=Chert;			break;
				case 3:gotoxy(C+3,N+22);cout<<C1+color+"==  Enter The New CellPhone Number :                  =="+C2;
				         gotoxy(C+36,N+22);getline(cin,Chert); person[i].CellPhone=Chert;			break;
				case 4:gotoxy(C+3,N+22);cout<<C1+color+"==  Enter The New Zipe Code :                         =="+C2;
				         gotoxy(C+33,N+22);getline(cin,Chert); person[i].Zip_Code=stoi(Chert);		break;
				case 5:gotoxy(C+3,N+22);cout<<C1+color+"==  Enter The New ID :                                =="+C2;
				         gotoxy(C+26,N+22);getline(cin,Chert); person[i].ID=stoi(Chert);			break;
				case 6:gotoxy(C+3,N+22);cout<<C1+color+"==  Enter The New Address :                           =="+C2;
				         gotoxy(C+31,N+22);getline(cin,Chert); person[i].Address=Chert;				break;
				case 7:gotoxy(C+3,N+22);cout<<C1+color+"==  Enter The New Username :                          =="+C2;
				         gotoxy(C+32,N+22);getline(cin,Chert); person[i].Username=Chert;			break;
				case 8:gotoxy(C+3,N+22);cout<<C1+color+"==  Enter The New Password :                          =="+C2;
				         gotoxy(C+32,N+22);getline(cin,Chert); person[i].Password=Chert;			break;
			}
			goto L6;
		}
	}
}
//-------------------------------------------------------- 10) Delete Goods -----------------------------------------------------------------
void Delete_Goods(void){
	string srch;
	string ch;
	system("cls");
	Color();
	gotoxy(C,N+0); cout<<C1+color+"================================================================================\n"+C2;
	gotoxy(C,N+1); cout<<C1+color+"=====            Enter the Goods name or code to Delete                    =====\n"+C2;
	gotoxy(C,N+2); cout<<C1+color+"=====                                                                      =====\n"+C2;
	gotoxy(C,N+3); cout<<C1+color+"=====    Search :                                                          =====\n"+C2;
	gotoxy(C,N+4); cout<<C1+color+"================================================================================\n"+C2;
	gotoxy(C+18,N+3); getline(cin,srch);
	for(int i=1;i<=gcount;i++){
		if(srch==goods[i].Name || stoi(srch)==goods[i].Code){
			gotoxy(C,N+6); cout<<C1+color+"================================================================================\n"+C2;
			gotoxy(C,N+7); cout<<C1+color+"=====                                                                      =====\n"+C2;
			gotoxy(C,N+8); cout<<C1+color+"=====                        ***[ Good's Data ]***                         =====\n"+C2;
			gotoxy(C,N+9); cout<<C1+color+"=====                                                                      =====\n"+C2;
			gotoxy(C,N+10);cout<<C1+color+"================================================================================\n"+C2;
			gotoxy(C,N+11);cout<<C1+color+"=====                                                                      =====\n"+C2;
			gotoxy(C,N+12);cout<<C1+color+"=====    1)Name :                                                          =====\n"+C2;
			gotoxy(C,N+13);cout<<C1+color+"=====    2)Code :                                                          =====\n"+C2;
			gotoxy(C,N+14);cout<<C1+color+"=====    3)Category :                                                      =====\n"+C2;
			gotoxy(C,N+15);cout<<C1+color+"=====    4)Price :                                                         =====\n"+C2;
			gotoxy(C,N+16);cout<<C1+color+"=====                                                                      =====\n"+C2;
			gotoxy(C,N+17);cout<<C1+color+"================================================================================\n"+C2;
			gotoxy(C,N+18);cout<<C1+color+"=====    Are You Sure You Want To Delete (Y/y) Or Back(B/b)?               =====\n"+C2;
			gotoxy(C,N+19);cout<<C1+color+"================================================================================\n"+C2;
			gotoxy(C+16,N+12); cout<<goods[i].Name;
			gotoxy(C+16,N+13); cout<<goods[i].Code;
			gotoxy(C+20,N+14); cout<<goods[i].Category;
			gotoxy(C+17,N+15); cout<<goods[i].Goods_price;		
			gotoxy(C+60,N+18);getline(cin,ch);
			
			if(ch=="b" || ch=="B"){
				Company_Menu();
			}

			if (ch=="Y" || ch=="y"){
				for(int j=1;j<=ccount;j++){                                                     // In Category, differ from count becuase good shoud be deleted.
					if(Cat[j].Name==goods[i].Category){
						Cat[j].Count--;
					}
				}
				if(i==gcount){                                                                  // akharin
					gcount--;
				}else{                                                                          // akharin kala nist
					goods[gcount].Code = i;
					goods[i]=goods[gcount];
					gcount--;
				}
			}	
		break;
		}
	}
}
//-------------------------------------------------------- 11) Input Data Of Goods ----------------------------------------------------------
void Input_Data_Of_Goods(void){
	string Check;
	system("cls");
	Color();
	gotoxy(C,N+0); cout<<C1+color+"================================================================================\n"+C2;
	gotoxy(C,N+1); cout<<C1+color+"=====                                                                      =====\n"+C2;
	gotoxy(C,N+2); cout<<C1+color+"=====                                                                      =====\n"+C2;
	gotoxy(C,N+3); cout<<C1+color+"=====                                                                      =====\n"+C2;
	gotoxy(C,N+4); cout<<C1+color+"================================================================================\n"+C2;
	gotoxy(C,N+5); cout<<C1+color+"=====                                                                      =====\n"+C2;
	gotoxy(C,N+6); cout<<C1+color+"=====    1) Name :                                                         =====\n"+C2;
	gotoxy(C,N+7); cout<<C1+color+"=====    2) Category :                                                     =====\n"+C2;
	gotoxy(C,N+8); cout<<C1+color+"=====    3) Price :                                                        =====\n"+C2;
	gotoxy(C,N+9); cout<<C1+color+"=====                                                                      =====\n"+C2;
	gotoxy(C,N+10);cout<<C1+color+"================================================================================\n"+C2;
	gotoxy(C,N+11);cout<<C1+color+"=====                                                                      =====\n"+C2;
	gotoxy(C,N+12);cout<<C1+color+"================================================================================\n"+C2;
	gotoxy(C+23,N+2);cout<<C1+color+"***[ Enter The Good "+C2+to_string((gcount+1))+C1+color+" Data ]***"+C2;
	gotoxy(C+19,N+6); getline(cin,goods[gcount+1].Name);
	gotoxy(C+23,N+7); getline(cin,Check); goods[gcount+1].Category = Check;
	gotoxy(C+20,N+8); getline(cin,Chert); goods[gcount+1].Goods_price = stoi(Chert);
	goods[gcount+1].Code = gcount+1;
	gotoxy(C+10,N+11); cout<<"Are You Sure You Want To Save (Y/y) Or Any Key Or Back(B/b)?";
    gotoxy(C+71,N+11); getline(cin,Chert);
	
	if(Chert=="b" || Chert=="B"){
		Company_Menu();
	}

	if(Chert=="Y" || Chert=="y"){
		gcount++;
		bool B=false;
		for(int i=1;i<=ccount;i++){
			if(Cat[i].Name==Check){
				Cat[i].Count+=1;
				B=true;
				break;
			}
		}
		if(!B){
			Cat[ccount+1].Name = Check;
			Cat[ccount+1].Count = 1;
			Cat[ccount+1].ID = ccount+1;
			ccount++;
		}
	}
	else Company_Menu();

}
//-------------------------------------------------------- 12) Customers_Menu ---------------------------------------------------------------
void Customers_Menu(void)
{
	do{	
		system("cls");
		Color();
		gotoxy(C,N+0); cout<<C1+color+"================================================================================"+C2;
		gotoxy(C,N+1); cout<<C1+color+"=====                          <<   DigiMahal   >>                         ====="+C2;
		gotoxy(C,N+2); cout<<C1+color+"================================================================================"+C2;
		gotoxy(C,N+3); cout<<C1+color+"=========                                                              ========="+C2;
		gotoxy(C,N+4); cout<<C1+color+"=====                         1: My Informations                           ====="+C2;
		gotoxy(C,N+5); cout<<C1+color+"===                           2: My Orders                                   ==="+C2;
		gotoxy(C,N+6); cout<<C1+color+"=====                         3: Shop                                      ====="+C2;
		gotoxy(C,N+7); cout<<C1+color+"=========                                                              ========="+C2;
		gotoxy(C,N+8); cout<<C1+color+"================================================================================"+C2;
		gotoxy(C,N+9); cout<<C1+color+"=====<<        Notice:In Every Part You Can Back By Entering B/b.        >>====="+C2;
		gotoxy(C,N+10);cout<<C1+color+"================================================================================"+C2;
		gotoxy(C,N+11);cout<<C1+color+"=====                        <<                 >>                         ====="+C2;
		gotoxy(C,N+12);cout<<C1+color+"================================================================================"+C2;
		
		gotoxy(C+35,N+1);cout<<C1+Green+" DigiMahal "+C2;
		gotoxy(C+33,N+4);cout<<"My Informations";
		gotoxy(C+33,N+5);cout<<"My Orders";
		gotoxy(C+33,N+6);cout<<"Shop";
		gotoxy(C+15,N+9);cout<<C1+Red+"Notice:In Every Part You Can Back By Entering B/b."+C2;
		gotoxy(C+31,N+11);cout<<C2+"   Wellcome: -   ";
		gotoxy(C+44,N+11);getline(cin,Chert);
		
		if(Chert=="b" || Chert=="B"){
			gotoxy(C+31,N+11);cout<<C1+Red+"    Good By.     "+C2; usleep(1000000);
			break;
		}
		int k;
		try{
			stoi(Chert);	
		}catch(exception &err){
			gotoxy(C+7,N+11);cout<<C1+Yellow+person[ID].First_name+C2+" You Can Use (1 or 2 or 3 or b/B) Nothing Else."; usleep(2000000);continue;
		}
		
		switch (stoi(Chert))
		{
			case 1:
				Information();
				break;
			case 2:
			    	Orders();
				break;
			case 3:
				Category();
				break;
		}
		if(Tamam==1){
			break;
		}
	}while (1);	
}
//-------------------------------------------------------- 13) Category ---------------------------------------------------------------------
void Category(void)
{
    do{	
		if(Tamam==1){
			break;
		}
		system("cls");
		Color();
		gotoxy(C,N+0);      cout<<C1+color+"================================================================================"+C2;
		gotoxy(C,N+1);      cout<<C1+color+"<<<<<<<<<<<<<<<<<<<<<<<<<<<< Choose Your Category >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"+C2;
		gotoxy(C,N+2);      cout<<C1+color+"================================================================================"+C2;
		gotoxy(C,N+3);      cout<<C1+color+"=====            Enter Digit Of Category From The Down List.               ====="+C2;
		gotoxy(C,N+4);      cout<<C1+color+"================================================================================"+C2;//L=80.
		gotoxy(C,N+5);	    cout<<C1+color+"=====                                                                      ====="+C2;
		int aa=N+5; int i;
		for(i=1;i<=ccount;i++){
			 gotoxy(C,i+aa);cout<<C1+color+"=====                                                                      ====="+C2; 
		}
		
		for(int j=1;j<=ccount;j++){ 
			if(j%2==1)
				{gotoxy(C+10,aa+j);    cout << C1+color << (j) <<" ) "+C2 << Cat[j].Name;}
			else
				{gotoxy(C+40,aa+j-1);    cout << C1+color << (j) <<" ) "+C2 << Cat[j].Name;}
		}
		if(ccount %2 == 1){
			gotoxy(C,i+aa);  cout<<C1+color+"=====                                                                      ====="+C2;
			aa+=1;	
		}
		gotoxy(C,i+aa);     cout<<C1+color+"================================================================================"+C2;
		gotoxy(C,i+aa+1);   cout<<C1+color+"=====                        Choose Your Category:                         ====="+C2;
		gotoxy(C,i+aa+2);   cout<<C1+color+"================================================================================"+C2;
		
	gotoxy(C+51,i+aa+1);getline(cin,Chert);
	if(Chert=="b" || Chert=="B"){
		break;
	}
	int a; 
	try{
			a=stoi(Chert);	
	}catch(exception &err){
		gotoxy(C+19,i+aa+1);cout<<" You Can Enter An Intejer Number Or b/B. ";usleep(2000000);continue;
	}
	//int a = stoi(Chert);	
	if(1<=a && a<=ccount){
		Scategory = a;
		List_Of_Goods();
		break;
	}
  }while(1);
}
//-------------------------------------------------------- 14) List Of Goods ----------------------------------------------------------------
void List_Of_Goods(void)
{  
	do{
		system("cls");
		Color();	
		gotoxy(C,N+0);        cout<<C1+color+"================================================================================"+C2;
		gotoxy(C,N+1);        cout<<C1+color+">....................                   =                   ...................<"+C2;
		gotoxy(C,N+2);        cout<<C1+color+">..............                    = =     = =                   ..............<"+C2;
		gotoxy(C,N+3);        cout<<C1+color+">..........                   = = =           = = =                   .........<"+C2;
		gotoxy(C,N+4);        cout<<C1+color+">......                   = = = =               = = = =                   .....<"+C2;
		gotoxy(C,N+5);        cout<<C1+color+">..........                   = = =           = = =                   .........<"+C2; 
		gotoxy(C,N+6);        cout<<C1+color+">...............                   = =     = =                   ..............<"+C2;
		gotoxy(C,N+7);        cout<<C1+color+">.....................                  =                    ..................<"+C2;
		gotoxy(C,N+8);        cout<<C1+color+"================================================================================"+C2;
		gotoxy(C,N+9);        cout<<C1+color+"======= =<     Enter Number Of Good That You Need or b/B or O/o : -    >= ======"+C2;
		gotoxy(C,N+10);       cout<<C1+color+"================================================================================"+C2;
		gotoxy(C,N+11);       cout<<C1+color+"=====   Number            Code            Name Of Good          Price      ====="+C2;
		gotoxy(C,N+12);       cout<<C1+color+"================================================================================"+C2;
		int i;
		for(i=1;i<=Cat[Scategory].Count;i++){
			gotoxy(C,N+12+i); cout<<C1+color+"=====                                                                      ====="+C2;
		}
			gotoxy(C,N+12+i); cout<<C1+color+"================================================================================"+C2;
		string name = Cat[Scategory].Name;
		int b = (name.length())/2;                                                                //baraaye taghaaron.
		gotoxy(C+40-b,N+4); cout<<name;

		int h=0;
		int hcode[200];
		for(int j=1;j<=gcount;j++){
			if(goods[j].Category==Cat[Scategory].Name){
				h+=1;
				gotoxy(C+7,N+12+h);  cout<<C1+color+" ( "+to_string(h)+ " ) "+C2;
				gotoxy(C+27,N+12+h); cout<<C1+red+to_string(goods[j].Code)+C2; 
				gotoxy(C+42,N+12+h); cout<<C1+Green+goods[j].Name+C2;
				gotoxy(C+64,N+12+h); cout<<C1+Yellow+to_string(goods[j].Goods_price)+ C2; 
				hcode[h]=goods[j].Code;
			}
		}

		gotoxy(C+66,N+9); getline(cin,Chert);
		if(Chert=="b" || Chert=="B"){
			Category();
			break;
		}	
		if(Chert=="o" || Chert=="O"){
			Orders();
			break;
		}
		int a;
		try{
			a=stoi(Chert);	
		}catch(exception &err){
			gotoxy(C+15,N+9);cout<<"Enter Number Of Good That You Need or b/B or O/o :";usleep(1000000);continue;
		}
		if(0<a && a<=Cat[Scategory].Count){
			bool rep=false;
			for(int z=1;z<=NSgoods;z++)
				if(SCat[z].Code == hcode[a]){
					SCat[z].Number+=1;
					rep=true;
				}
				if(!rep){
					SCat[NSgoods+1].Code = hcode[a];
					SCat[NSgoods+1].Number = 1;
					NSgoods++;
				}
			
				gotoxy(C,N+9);cout<<C1+color+"===== =<                       Add Successfully.                      >= ====="+C2;
				usleep(1000000);
			
		}
	} while (1);
}
//-------------------------------------------------------- 15) Order ------------------------------------------------------------------------
void Orders (void){
	do
	{
	int a,b,Pr,len;//price.//lenth of name;
	string gname,pname,pad;//paddress;
	system("cls");
	Color();
	gotoxy(C,N);   cout<<"================================================================================";//L:80.
	gotoxy(C,N+1); cout<<"=======                       This Is Your Orders.                       =======";
	gotoxy(C,N+2); cout<<"================================================================================";
	gotoxy(C,N+3); cout<<"==== Number     Code     Name Of Good      Count    Y_Price    Total_Price  ====";
	gotoxy(C,N+4); cout<<"================================================================================";
	gotoxy(C+5,N+3);cout<<C1+color+"Number"+C2;
	gotoxy(C+16,N+3);cout<<C1+red+"Code"+C2;
	gotoxy(C+25,N+3);cout<<C1+Green+"Name Of Good"+C2;
	gotoxy(C+43,N+3);cout<<C1+Turquoise+"Count"+C2;
	gotoxy(C+52,N+3);cout<<C1+yellow+"Y_Price"+C2;
	gotoxy(C+63,N+3);cout<<C1+Yellow+"Total_Price"+C2;
	int i,j;
	for(i=1;i<=NSgoods;i++){
		gotoxy(C+5,N+4+i); cout<<C1+color+" ( "+to_string(i)+" ) "+C2;
		gotoxy(C+17,N+4+i);cout<<C1+red+to_string(SCat[i].Code)+C2;
		for(j=1;j<=gcount;j++)
			if(SCat[i].Code==goods[j].Code){
				gname=goods[j].Name;
				Pr=goods[j].Goods_price;
				break;
			}
		
		gotoxy(C+25,N+4+i);cout<<C1+Green+gname+C2;
		gotoxy(C+44,N+4+i);cout<<C1+Turquoise+to_string(SCat[i].Number)+C2;
		gotoxy(C+51,N+4+i);cout<<C1+yellow+to_string(Pr)+C2;
		int TP=Pr*SCat[i].Number;
		gotoxy(C+63,N+4+i);cout<<C1+Yellow+to_string(TP)+C2;

	}
	//gotoxy(C,N+); cout<<"====                                                                        ====";
	for(i=1;i<=max(10,NSgoods);i++){
		gotoxy(C,N+4+i); cout<<"====";
		gotoxy(C+76,N+4+i); cout<<"====";                                                                        
	}

	gotoxy(C,N+4+i); cout<<"================================================================================";
	//gotoxy(C,N+5+i); cout<<"======= seyyed mobin You Can Edit By Ener Namber Or Finish by (f/F):     =======";
	int k;
	for(k=1;k<=pcount;k++)
		if(ID==person[k].ID){
			pname=person[k].First_name;
			pad=person[k].Address;
			break;
		}
	len=pname.length();
	gotoxy(C,N+5+i); cout<<"======= "+C1+Blue+pname+C2;gotoxy(C+73,N+5+i);cout<<"=======";
	//gotoxy(C+8+len,N+5+i);cout<<" You Can Edit By Enter Number Or Finish by (f/F): ";
	gotoxy(C+8+len,N+5+i);cout<<" Enter Number For Edit Or Facture(f/F) Or (b/B): ";   
	// cout<<"    count of -name-?  0 is delet.  ";
	gotoxy(C,N+6+i);   cout<<"=== Your Arddress:                                                       =======";
	gotoxy(C+18,N+6+i);cout<<C1+Purple+pad+C2;
	gotoxy(C,N+7+i);   cout<<"================================================================================";
	gotoxy(C+56+len,N+5+i);getline(cin,Chert);
	if(Chert=="b" || Chert=="B"){
		gotoxy(C,N+5+i);   cout<<"=======                         You Are Backing.                         =======";usleep(2000000);
		break;
	}
	if(Chert=="f" || Chert=="F"){
		if(NSgoods==0){
			gotoxy(C,N+5+i); cout<<"========                 "+C1+Red+"There's Nothig In Your Orders."+C2+"                  =======";usleep(2000000);
			continue;
		}
		else{
			Sale_Facture();
			break;
		}	  
	}
	try{
			a=stoi(Chert);	
	}catch(exception &err){
		gotoxy(C+8+len,N+5+i);cout<<C1+red+" Enter Number For Edit Or Facture(f/F) Or (b/B): "+C2;usleep(1000000);continue;
	}
	
	if(0<a && a<=NSgoods){
		gotoxy(C,N+5+i);cout<<"=======                                                                  =======";
		gotoxy(C+10,N+5+i);cout<<"Enter New Count For Good"+to_string(a)+" : ";
		gotoxy(C+37,N+5+i);getline(cin,Chert);
		b=stoi(Chert);
		if(b==0){
			SCat[a]=SCat[NSgoods];
			NSgoods--;
		}
		if(b>0)
		SCat[a].Number=b;
	}
	}while(1);
}
//-------------------------------------------------------- 16) Price ------------------------------------------------------------------------
void Prices(void){
	for(int i=1;i<=NSgoods;i++)
		Payment+=goods[SCat[i].Code].Goods_price*SCat[i].Number;
	Payment*=1.09;
} 
//-------------------------------------------------------- 17) Mail -------------------------------------------------------------------------
void Mail (void){
	int Zip_payment[32]={2,2,2,4,5,3,4,3,6,5,2,8,3,2,3,3,3,4,6,3,2,4,7,0,4,1,1,3,4,4,0};
	Mail_Payment=Zip_payment[person[ID].Zip_Code]*2500;
}
//-------------------------------------------------------- 18) Sale Factor ------------------------------------------------------------------
void Sale_Facture(void){
	system("cls");
    Prices();
	Mail();
	Color();
	gotoxy(C,N+6); cout<<	 	  C1+color+"================================================================================\n"+C2;
	gotoxy(C,N+7); cout<<	 	  C1+color+"=======                                                                  =======\n"+C2;
	gotoxy(C,N+8); cout<<	 	  C1+color+"=====                               [ BILL ]                               =====\n"+C2;
	gotoxy(C,N+9); cout<<	 	  C1+color+"=======                                                                  =======\n"+C2;
	gotoxy(C,N+10);cout<<	   	  C1+color+"================================================================================\n"+C2;
	gotoxy(C,N+11);cout<<  	      C1+color+"=====  GOOD DESCRIPTION               | NUMBER | UNITY PRICE | PRICE       =====\n"+C2;
	gotoxy(C,N+12);cout<<	      C1+color+"================================================================================\n"+C2;
	for(int i=1;i<=NSgoods;i++){
		i--;
		gotoxy(C,N+13+2*i);cout<<  C1+color+"=   =                                 |        |             |             =====\n"+C2;
		gotoxy(C,N+14+2*i);cout<<  C1+color+"================================================================================\n"+C2;
		gotoxy(C+2,N+13+2*i);cout<<C1+color+to_string(i+1)+C2;
		gotoxy(C+7,N+13+2*i);cout<<C1+color+goods[SCat[i+1].Code].Name+C2;
		gotoxy(C+41,N+13+2*i);cout<<C1+color+to_string(SCat[i+1].Number)+C2;
		gotoxy(C+49,N+13+2*i);cout<<C1+color+to_string(goods[SCat[i+1].Code].Goods_price)+C2;
		gotoxy(C+63,N+13+2*i);cout<<C1+color+to_string(goods[SCat[i+1].Code].Goods_price*SCat[i+1].Number)+C2;
		i++;
	}
	gotoxy(C,N+13+2*NSgoods);cout<<C1+color+"================================================================================\n"+C2;
	gotoxy(C,N+14+2*NSgoods);cout<<C1+color+"=====                                                                      =====\n"+C2;
	gotoxy(C,N+15+2*NSgoods);cout<<C1+color+"================================================================================\n"+C2;
	gotoxy(C+10,N+14+2*NSgoods);cout<<C1+color+       "Postage price for your mahalle                     : "+to_string(Mail_Payment)+"T"+C2;
	gotoxy(C,N+16+2*NSgoods);cout<<C1+color+"=====                                                        :             =====\n"+C2;
	gotoxy(C,N+17+2*NSgoods);cout<<C1+color+"================================================================================\n"+C2;
	gotoxy(C+10,N+16+2*NSgoods);cout<<C1+color+       "Total price including 9% TAX and postage           : "+to_string(Payment+Mail_Payment)+"T"+C2;
	getch();
	system("cls");
	Color();         
			gotoxy(C-F,N+14);cout<<C1+color+"******* *     *     *     *     *  *   *    *    *     **    *    *    * * * *    **    * * *     * * *   *    *  * * * *  *****  *      *    ***   \n"+C2;
			gotoxy(C-F,N+15);cout<<C1+color+"   *    *     *   *   *   **    *  * *      *    *   *    *  *    *    *        *    *  *    *    *    *  *    *  *          *    **     *  *       \n"+C2;
			gotoxy(C-F,N+16);cout<<C1+color+"   *    * * * *  * * * *  *  *  *  *          * **   *    *  *    *    * * * *  *    *  * * *     * * *     * **  * * * *    *    *  *   *  *   *** \n"+C2;
			gotoxy(C-F,N+17);cout<<C1+color+"   *    *     *  *     *  *    **  * *      *    *   *    *  *    *    *        *    *  * *       *    *  *    *  *          *    *    * *  *    *  \n"+C2;
			gotoxy(C-F,N+18);cout<<C1+color+"   *    *     *  *     *  *     *  *   *      * *      **      * *     *          **    *   *     * * *     ***   * * * *  *****  *      *    **    \n"+C2;
    	getch();
	Tamam=1;
}
//-------------------------------------------------------- 19) info -------------------------------------------------------------------------
void Information(void){
	string same;
	do{
		system("cls");
		Color();
		gotoxy(C,N+0); cout<<C1+color+"================================================================================\n"+C2;
		gotoxy(C,N+1); cout<<C1+color+"=====                                                                      =====\n"+C2;
		gotoxy(C,N+2); cout<<C1+color+"=====                       **[Your Informations]**                        =====\n"+C2;
		gotoxy(C,N+3); cout<<C1+color+"=====                                                                      =====\n"+C2;
		gotoxy(C,N+4); cout<<C1+color+"================================================================================\n"+C2;
		gotoxy(C,N+5); cout<<C1+color+"=====                                                                      =====\n"+C2;
		gotoxy(C,N+6); cout<<C1+color+"=====    First Name :                                                      =====\n"+C2;
		gotoxy(C,N+7); cout<<C1+color+"=====    Last Name :                                                       =====\n"+C2;
		gotoxy(C,N+8); cout<<C1+color+"=====    CellPhone :                                                       =====\n"+C2;
		gotoxy(C,N+9); cout<<C1+color+"=====    ZipCode(Your Mahalle/Number) :                                    =====\n"+C2;
		gotoxy(C,N+10);cout<<C1+color+"=====    Address :                                                         =====\n"+C2;
		gotoxy(C,N+11);cout<<C1+color+"================================================================================\n"+C2;
		gotoxy(C,N+12);cout<<C1+color+"=====    Username :                                                        =====\n"+C2;
		gotoxy(C,N+13);cout<<C1+color+"=====    Password :                                                        =====\n"+C2;
		gotoxy(C,N+14);cout<<C1+color+"=====                                                                      =====\n"+C2;
		gotoxy(C,N+15);cout<<C1+color+"================================================================================\n"+C2;
		gotoxy(C,N+16);cout<<C1+color+"=====        Enter First Element For Edit(F/L/C/Z/A/U/P) Or b/B : -        =====\n"+C2;
		gotoxy(C,N+17);cout<<C1+color+"================================================================================\n"+C2;//L:80.
		
		gotoxy(C+22,N+6);  cout<<person[ID].First_name;
		gotoxy(C+21,N+7);  cout<<person[ID].Last_name;
		gotoxy(C+21,N+8);  cout<<person[ID].CellPhone;
		gotoxy(C+40,N+9);  cout<<person[ID].Zip_Code;
		gotoxy(C+19,N+10); cout<<person[ID].Address;
		gotoxy(C+20,N+12); cout<<person[ID].Username;
		gotoxy(C+20,N+13); cout<<person[ID].Password;


		gotoxy(C+66,N+16); getline(cin,Chert);
		if(Chert=="b" ||Chert=="B"){
			gotoxy(C,N+16);  cout<<C1+color+"=====                          YOU Are Come Back.                         ====="+C2; usleep(1000000); 
			break;
		}
		if(Chert=="f" ||Chert=="F")                                                                                
			{
			gotoxy(C,N+16);     cout<<C1+color+"=====      >>Enter Your New Firstname :                                    ====="+C2;gotoxy(C+40,N+16);getline(cin,Chert2);
			if(Chert2=="b" || Chert2=="B")continue; else person[ID].First_name=Chert2;
			gotoxy(C,N+16);  cout<<C1+color+"=====                    Changes Successfully Finished.                    ====="+C2; usleep(2000000);               
			}
		if(Chert=="l" ||Chert=="L")                                                                                
			{
			gotoxy(C,N+16);  cout<<C1+color+"=====      >>Enter Your New Lastname :                                     ====="+C2;gotoxy(C+40,N+16);getline(cin,Chert2);
			if(Chert2=="b" || Chert2=="B")continue; else person[ID].Last_name=Chert2;
			gotoxy(C,N+16);  cout<<C1+color+"=====                    Changes Successfully Finished.                    ====="+C2; usleep(2000000);               
			}
		if(Chert=="c" ||Chert=="C")                                                                                
			{
			gotoxy(C,N+16);  cout<<C1+color+"=====      >>Enter Your New CellPhone Number :                             ====="+C2;gotoxy(C+47,N+16);getline(cin,Chert2);
			if(Chert2=="b" || Chert2=="B")continue; else person[ID].CellPhone=Chert2;
			gotoxy(C,N+16);  cout<<C1+color+"=====                    Changes Successfully Finished.                    ====="+C2; usleep(2000000);                
			}
		if(Chert=="z" ||Chert=="Z")                                                                                
			{
			Ag:	
			gotoxy(C,N+16);  cout<<C1+color+"=====      >>Enter Your New ZipCode :                                      ====="+C2;gotoxy(C+38,N+16);getline(cin,Chert2);
			if(Chert2=="b" || Chert2=="B")continue; else 
			{try{stoi(Chert2);}catch(exception &err){gotoxy(C+38,N+16);cout<<"Shulde Be An Integer (0_32).";usleep(1000000);goto Ag;}person[ID].Zip_Code=stoi(Chert2);}
			gotoxy(C,N+16);  cout<<C1+color+"=====                    Changes Successfully Finished.                    ====="+C2; usleep(2000000);               
			}
		if(Chert=="a" ||Chert=="A")                                                                                
			{
			gotoxy(C,N+16);  cout<<C1+color+"=====      >>Enter Your New Address :                                      ====="+C2;gotoxy(C+38,N+16);getline(cin,Chert2);
			if(Chert2=="b" || Chert2=="B")continue; else person[ID].Address=Chert2;
			gotoxy(C,N+16);  cout<<C1+color+"=====                    Changes Successfully Finished.                    ====="+C2; usleep(2000000);             
			}
		if(Chert=="u" ||Chert=="U") 
		do
		{                                                                               
			gotoxy(C,N+16);cout<<C1+color+"=====      >>Enter Your New Username :                                     ====="+C2;gotoxy(C+39,N+16);getline(cin,same);
			if(same=="b" || same=="B")
				break;
			for(int j=1;j<=pcount;j++){
				if(person[j].Username==same){
					same="c";
					break;
				}
			}
			if(same != "c"){
				person[ID].Username=same;
				gotoxy(C,N+16);  cout<<C1+color+"=====                    Changes Successfully Finished.                    ====="+C2; usleep(2000000); break;
			}
			else{
				gotoxy(C,N+16);  cout<<C1+color+"=====                         This Username Exists.                        ====="+C2; usleep(2000000);
			}  
		}while(1);

		if(Chert=="p" ||Chert=="P")                                                                                
			{
				gotoxy(C,N+16);  cout << C1+color+"=====      >>Enter Your New Password :                                     ====="+C2;gotoxy(C+39,N+16); getline(cin,Chert2);
				if(Chert2=="b" || Chert2=="B")continue; else person[ID].Password=Chert2;
				gotoxy(C,N+16);  cout<<C1+color+"=====                    Changes Successfully Finished.                    ====="+C2; usleep(2000000);          
			}				
	} while (1);
}
//-------------------------------------------------------- 20) Color ------------------------------------------------------------------------
void Color(void){
	switch(counter){
		case 0:
			color=Purple; counter++;break;
		case 1:
			color=Blue; counter++;break;
		case 2:
			color=Yellow; counter++;break;
		case 3:
			color=Green; counter++;break;
		case 4:
			color=Gray; counter++;break;
		case 5:
			color=Red; counter++;break;
		case 6:
			color=Turquoise; counter=0;break;

	}
}
//-------------------------------------------------------- 21) End --------------------------------------------------------------------------
void End(void){
	system("cls");	
	int CHARS[26][5][5]={
	
	{{0,0,1,0,0},{0,1,0,1,0},{1,1,1,1,1},{1,0,0,0,1},{1,0,0,0,1}},
	{{1,1,1,1,0},{1,0,0,0,1},{1,1,1,1,0},{1,0,0,0,1},{1,1,1,1,0}},
	{{1,1,1,1,1},{1,0,0,0,0},{1,0,0,0,0},{1,0,0,0,0},{1,1,1,1,1}},
	{{1,1,1,1,0},{1,0,0,0,1},{1,0,0,0,1},{1,0,0,0,1},{1,1,1,1,0}},
	{{1,1,1,1,1},{1,0,0,0,0},{1,1,1,1,1},{1,0,0,0,0},{1,1,1,1,1}},
	{{1,1,1,1,1},{1,0,0,0,0},{1,1,1,1,1},{1,0,0,0,0},{1,0,0,0,0}},
	{{1,1,1,1,1},{1,0,0,0,0},{1,0,0,1,1},{1,0,0,0,1},{1,1,1,1,1}},
	{{1,0,0,0,1},{1,0,0,0,1},{1,1,1,1,1},{1,0,0,0,1},{1,0,0,0,1}},
	{{0,1,1,1,0},{0,0,1,0,0},{0,0,1,0,0},{0,0,1,0,0},{0,1,1,1,0}},
	{{0,1,1,1,0},{0,0,1,0,0},{0,0,1,0,0},{0,0,1,0,0},{0,1,1,0,0}},
	{{1,0,0,0,1},{1,0,0,1,0},{1,1,1,0,0},{1,0,0,1,0},{1,0,0,0,1}},
	{{1,0,0,0,0},{1,0,0,0,0},{1,0,0,0,0},{1,0,0,0,0},{1,1,1,1,1}},
	{{1,0,0,0,1},{1,1,0,1,1},{1,0,1,0,1},{1,0,0,0,1},{1,0,0,0,1}},
	{{1,0,0,0,1},{1,1,0,0,1},{1,0,1,0,1},{1,0,0,1,1},{1,0,0,0,1}},
	{{1,1,1,1,1},{1,0,0,0,1},{1,0,0,0,1},{1,0,0,0,1},{1,1,1,1,1}},
	{{1,1,1,0,0},{1,0,0,1,0},{1,1,1,0,0},{1,0,0,0,0},{1,0,0,0,0}},
	{{1,1,1,1,1},{1,0,0,0,1},{1,0,0,0,1},{1,0,0,1,1},{1,1,1,1,1}},
	{{1,1,1,0,0},{1,0,0,1,0},{1,1,1,0,0},{1,0,1,0,0},{1,0,0,0,1}},
	{{0,1,1,1,0},{1,0,0,0,0},{0,1,1,1,0},{0,0,0,0,1},{0,1,1,1,0}},
	{{1,1,1,1,1},{0,0,1,0,0},{0,0,1,0,0},{0,0,1,0,0},{0,0,1,0,0}},
	{{1,0,0,0,1},{1,0,0,0,1},{1,0,0,0,1},{1,0,0,0,1},{1,1,1,1,1}},
	{{1,0,0,0,1},{1,0,0,0,1},{1,0,0,0,1},{0,1,0,1,0},{0,0,1,0,0}},
	{{1,0,0,0,1},{1,0,0,0,1},{1,0,1,0,1},{1,1,0,1,1},{1,0,0,0,1}},
	{{1,0,0,0,1},{0,1,0,1,0},{0,0,1,0,0},{0,1,0,1,0},{1,0,0,0,1}},
	{{1,0,0,0,1},{0,1,0,1,0},{0,0,1,0,0},{0,0,1,0,0},{0,0,1,0,0}},
	{{1,1,1,1,1},{0,0,0,1,0},{0,0,1,0,0},{0,1,0,0,0},{1,1,1,1,1}},
	};

	string str = "YOU";
	for(int i=1;i<=pcount;i++){
		if(person[i].ID == ID){
			str = person[i].First_name;
			break;
		}
	}
	
	transform(str.begin(), str.end(), str.begin(), ::toupper);

	int vorodi[5][24];
	string Matn[5] = {"DIGIMAHAL","WISH",str,"HAVE","GOODTIME"};

	int x,count=0;
	for(int j=0;j<=4;j++){
        count=0;
		for(int i=0;i<Matn[j].size();i++){
			x = int(Matn[j][i]) - 65;
			vorodi[j][count] = x;
			count++;
		}
	}

    for(int h=0;h<6;h++){
		int aaa=0;
    	int aaaa=0;
        Color();
        for(int f=0;f<5;f++){
            for(int i=0;i<5;i++){
                aaa=0;
                for(int j=0;j<Matn[f].size();j++){
                    for(int k=0;k<5;k++){
                        gotoxy(5+aaa,5+aaaa);
                        if(CHARS[vorodi[f][j]][i][k]==1){
                            cout << C1+color+"*"+C2;
                            aaa++;
                        }else{
                            cout << " ";
                            aaa++;
                        }
                    }
                    cout << " ";
                    aaa++;
                }
                usleep(40000);
                //cout << endl;
                aaaa++;
            }
            //cout << endl << endl;
            aaaa++;
            aaaa++;
        }
    }
	getch();
	system("cls");
	exit(0);
}
