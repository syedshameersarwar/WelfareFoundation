#include <iostream>
#include <winsock.h>
#include "mysql.h"
#include <string>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <conio.h>
#include <windows.h>
#include "TextTable.h"

using namespace std;


/**************Class Declarations******************/

class Database{
    private:
        string user;
        string pass;
        string db;
        string host;
        bool connect_to_db(void);
    public:
        static MYSQL *connect;
        Database();
        bool checkConnect(void);
        ~Database();
};



class Testing{
    public:
        bool is_valid_name(string);
        bool is_valid_num(string);
        bool is_valid_year(string);
        bool is_valid_month(int);
        bool is_valid_date(int,int,int);
        bool is_valid_amount(string);
        bool is_valid_id(string);
        bool is_valid_choice(string);
};


class Person{ //person class for design
    protected:
        string firstname;
        string lastname;

};


class Donor:public Person{
    private:
        int id;
        string phone_no;
        string join_date;
        string Status;
        Testing t;
    public:
        void add_donor(void);
        int search_donor_id(void);
        void delete_donor(void);
        void modify_donor(void);
        void display_donors(void);
};



class Donation{
    private:
        int ID;
        double amount,total;
        string month,year;
        bool in_organ_year(string);
        string return_month(int);
        Testing t;
    public:
        Donation();
        void add_donation(void);
        void get_donor_monthly(void);
        void get_donor_yearly(void);
        void get_donor_total(void);
        void delete_donation_monthly(void);
        void delete_donation_yearly(void);
        void modify_donation(void);
        void get_donation_monthly(void);
        void get_donation_yearly(void);
        void get_total_donation_id(void);
        void display_total_record_id(void);
};


class Targets{
    private:
        int target_id;
        string target_descryption;
        double expected_amount;
        double spend_amount;
        string status;
        Testing t;
    public:
        Targets();
        void add_target(void);
        int search_target(void);
        void delete_target(void);
        void modify_target(void);
        void display_targets(void);
};



class Accomplishment{
    private:
        int s_no;
        string description;
        double sp_amount;
        string acc_date;
        Testing t;
    public:
        Accomplishment();
        void add_accomplishment(void);
        int search_accomplishment(void);
        void delete_accomplishment(void);
        void modify_accomplishment(void);
        void display_accomplishment(void);
};


class User:public Person{
    private:
        string password;
        int s_no;
        Testing t;
    public:
        User();
        void add_user(void);
        void modify_user(void);
        int search_user(void);
        void delete_user(void);
        void display_users(void);
};


class Members:public Person{
    private:
        int id;
        string full_name;
        string designation;
        string phone_number;
        Testing t;
    public:
        void add_member(void);
        void delete_member(void);
        int search_member(void);
        void modify_member(void);
        void display_members(void);
};


class WelfareFoundation{
    private:
        Donor d;
        Accomplishment a;
        Donation D;
        Members m;
        Targets T;
        User u;
        Testing t;
        Database db;
    public:
        void welcome_screen(void);
        void login(void);
        void main_menu(void);
        void donor_section(void);
        void donation_section(void);
        void target_section(void);
        void accomplishment_section(void);
        void user_section(void);
        void Member_section(void);
        void exit_screen(void);
};



/*********************Definitions of Class Member Functions*********************************/


Database::Database(){
    user = "root";
    pass = "mathswithned123:D";
    db = "WelfareFoundation";
    host = "127.0.0.1";
}


MYSQL* Database::connect = mysql_init(NULL);
bool Database::checkConnect(void){
    if(connect){
        if(connect_to_db())
            return true;
        else
            return false;
    }
    else{
        cout<<"Failed to connect with Database."<<endl;
        return true;
    }
}


bool Database::connect_to_db(void){
    cout<<"Connecting to Database";

    for(int i=0;i<2;i++){
        Sleep(400);
        cout<<".";
        Sleep(400);
        cout<<".";
        Sleep(400);
        cout<<".";
        Sleep(400);
        cout<<"\b\b\b   \b\b\b";
    }
    if(mysql_real_connect(connect,host.c_str(),user.c_str(),pass.c_str(),db.c_str(),3306,NULL,CLIENT_MULTI_QUERIES)){
        cout<<"\nConnection to Database established."<<endl;
        Sleep(1000);
        return true;
    }
    else{
        cout<<"Connection Error."<<endl;
        return false;
    }
}


Database::~Database(){
    mysql_close(connect);
}


void gotoxy( int column, int line )
{
    COORD coord;
    coord.X = column;
    coord.Y = line;
    SetConsoleCursorPosition(
        GetStdHandle( STD_OUTPUT_HANDLE ),
        coord
    );
}

int wherex()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (!GetConsoleScreenBufferInfo(
        GetStdHandle( STD_OUTPUT_HANDLE ),
        &csbi
        ))
        return -1;
    return csbi.dwCursorPosition.X;
}

int wherey()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (!GetConsoleScreenBufferInfo(
         GetStdHandle( STD_OUTPUT_HANDLE ),
         &csbi
         ))
        return -1;
    return csbi.dwCursorPosition.Y;
}


bool Testing::is_valid_name(string s){
    if(s.empty())
        return false;
    for(int i=0;i<s.length();i++){
        if(isalpha(s[i])||s[i]==' ')
            continue;
        else
            return false;
    }
    return true;
}


bool Testing::is_valid_num(string s){
    if (s.empty())
        return true;
    if (s.length()>15)
        return false;
    for(int i=0;i<s.length();i++){
        if(s[i]>= '0'&&s[i]<='9')
            continue;
        else
            return false;
    }
    return true;
}


bool Testing::is_valid_id(string id){
    for(int i=0;i<id.length();i++){
        if(id[i]>= '0'&&id[i]<='9')
            continue;
        else
            return false;
    }
    return true;
}


bool Testing::is_valid_date(int dd,int mm,int yy){
    int checkdate[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
    if(dd>=1 && dd<=31){
        if (mm>=1 && mm<=12){
            if (checkdate[mm]>=dd){
                if (yy>=1900 && yy<=2200)
                    return true;
            }
        }
    }
    return false;
}


bool Testing::is_valid_year(string y){
    if (y.length()!=4)
        return false;
    if(atoi(y.c_str())>=1900 && atoi(y.c_str())<=2200)
        return true;
    else
        return false;
}


bool Testing::is_valid_month(int m){
    if (m>=1 && m<=12)
        return true;
    else
        return false;
}


bool Testing::is_valid_amount(string am){
    int i;
    for(i=0;i<am.length();i++){
        if((am[i]>='0'&&am[i]<='9')||am[i]=='.')
            continue;
        else
            return false;
    }
    return true;
}

bool Testing::is_valid_choice(string c){
    if (c.length()==0 || c.length()>1)
        return false;
    if(c[0]=='y'||c[0]=='Y'||c[0]=='n'||c[0]=='N')
        return true;
    else
        return false;
}
void Donor::add_donor(void){
    system("cls");
    int valid = 0;
    char ch1,ch2;
    string fname,lname,phone,date;
    stringstream query1;
    while (!valid){
        system("cls");
        cout<<"Enter Donor's First Name : "<<endl;
        getline(cin,fname);
        if(cin.fail()){
            cin.clear();
            cin.ignore(256,'\n');
            cout<<"Enter a valid name."<<endl;
            Sleep(2000);
            continue;
        }
        if(!t.is_valid_name(fname)){
            cout<<"Special characters and digits are not allowed."<<endl;
            Sleep(2000);
            continue;
        }
        firstname = fname;
        valid = 1;
    }
    valid = 0;
    while (!valid){
        cout<<"Enter Donor's Last Name : "<<endl;
        getline(cin,lname);
        if(cin.fail()){
            cout<<"Enter a valid name."<<endl;
            cin.clear();
            cin.ignore(256,'\n');
            Sleep(2000);
            system("cls");
            cout<<"Enter Donor's First Name : "<<endl;
            cout<<fname<<endl;
            continue;
        }
        if(!t.is_valid_name(lname)){
            cout<<"Special characters and digits are not allowed."<<endl;
            Sleep(2000);
            system("cls");
            cout<<"Enter Donor's First Name : "<<endl;
            cout<<fname<<endl;
            continue;
        }
        lastname = lname;
        valid = 1;
    }
    valid = 0;
    cout<<"Want to add donor's phone number ? (y/n) : ";
    ch1 = getche();
    cout<<endl;
    if(ch1=='y'||ch1=='Y'){
        while(!valid){
            cout<<"Enter Donor's Phone Number : "<<endl;
            getline(cin,phone);
            if(cin.fail()){
                cout<<"Enter a valid Phone number."<<endl;
                cin.clear();
                cin.ignore(256,'\n');
                Sleep(2000);
                system("cls");
                cout<<"Enter Donor's First Name : "<<endl;
                cout<<fname<<endl;
                cout<<"Enter Donor's Last Name : "<<endl;
                cout<<lname<<endl;
                cout<<"Want to add donor's phone number ? (y/n) : "<<ch1<<endl;
                continue;
            }
            if(!t.is_valid_num(phone)){
                cout<<"Invalid number.Only 15 digits(0-9) are allowed"<<endl;
                Sleep(2000);
                system("cls");
                cout<<"Enter Donor's First Name : "<<endl;
                cout<<fname<<endl;
                cout<<"Enter Donor's Last Name : "<<endl;
                cout<<lname<<endl;
                cout<<"Want to add donor's phone number ? (y/n) : "<<ch1<<endl;
                continue;
            }
            phone_no = phone;
            valid = 1;
        }
    }
    else{
        phone_no = "-";
    }
    valid = 0;
    cout<<"Want to add Joining Date? (y/n) : ";
    ch2 = getche();
    cout<<endl;
    if (ch2 == 'y'||ch2 =='Y'){
        while(!valid){
            int dd,mm,yy;
            cout<<"Enter Joining Date of Donor(DD-MM-YY) : "<<endl;
            cin>>dd;
            cin.get();
            cin>>mm;
            cin.get();
            cin>>yy;
            cin.get();
            if(cin.fail()){
                cout<<"Enter a valid date with correct format(DD-MM-YY)."<<endl;
                cin.clear();
                cin.ignore(256,'\n');
                Sleep(2000);
                system("cls");
                cout<<"Enter Donor's First Name : "<<endl;
                cout<<fname<<endl;
                cout<<"Enter Donor's Last Name : "<<endl;
                cout<<lname<<endl;
                cout<<"Want to add donor's phone number ? (y/n) : "<<ch1<<endl;
                if (ch1=='y'||ch1=='Y')
                    cout<<"Enter Donor's Phone Number : "<<endl<<phone<<endl;
                cout<<"Want to add Joining Date? (y/n) : "<<ch2<<endl;
                continue;
            }
            if(!t.is_valid_date(dd,mm,yy)){
                cout<<"Invalid Date.Enter Date with correct ranges."<<endl;
                Sleep(2000);
                system("cls");
                cout<<"Enter Donor's First Name : "<<endl;
                cout<<fname<<endl;
                cout<<"Enter Donor's Last Name : "<<endl;
                cout<<lname<<endl;
                cout<<"Want to add donor's phone number ? (y/n) : "<<ch1<<endl;
                if (ch1=='y'||ch1=='Y')
                    cout<<"Enter Donor's Phone Number : "<<endl<<phone<<endl;
                cout<<"Want to add Joining Date? (y/n) : "<<ch2<<endl;
                continue;
            }
            date = to_string(yy)+"-"+to_string(mm)+"-"+to_string(dd);
            join_date = date;
            valid = 1;
        }
    }
    else{
        join_date = "-";
    }
    valid = 0;
    while(!valid){
        int choice;
        cout<<"Enter Donor Status {1:Active,2:In-active,3:Unknown} : "<<endl;
        cin>>choice;
        if(cin.fail()){
            cout<<"Enter a valid choice."<<endl;
            cin.clear();
            cin.ignore(256,'\n');
            Sleep(2000);
            system("cls");
            cout<<"Enter Donor's First Name : "<<endl;
            cout<<fname<<endl;
            cout<<"Enter Donor's Last Name : "<<endl;
            cout<<lname<<endl;
            cout<<"Want to add donor's phone number ? (y/n) : "<<ch1<<endl;
                if (ch1=='y'||ch1=='Y')
                    cout<<"Enter Donor's Phone Number : "<<endl<<phone<<endl;
            cout<<"Want to add Joining Date? (y/n) : "<<ch2<<endl;
            if(ch2=='y'||ch2=='Y')
                cout<<"Enter Joining Date of Donor(DD-MM-YY) : "<<endl<<date<<endl;
            continue;
        }
        if(!(choice >= 1 && choice <=3)){
            cout<<"Select given choice."<<endl;
            Sleep(2000);
            system("cls");
            cout<<"Enter Donor's First Name : "<<endl;
            cout<<fname<<endl;
            cout<<"Enter Donor's Last Name : "<<endl;
            cout<<lname<<endl;
            cout<<"Want to add donor's phone number ? (y/n) : "<<ch1<<endl;
                if (ch1=='y'||ch1=='Y')
                    cout<<"Enter Donor's Phone Number : "<<endl<<phone<<endl;
            cout<<"Want to add Joining Date? (y/n) : "<<ch2<<endl;
            if(ch2=='y'||ch2=='Y')
                cout<<"Enter Joining Date of Donor(DD-MM-YY) : "<<endl<<date<<endl;
            continue;
        }
        if(choice == 1)
            Status = "Active";
        else if(choice == 2)
            Status = "In-Active";
        else
            Status = "Unknown";
        valid = 1;
    }
    if(ch2=='y'||ch2=='Y'){
        query1<<"INSERT INTO DonorsInfo(FirstName,LastName,PhoneNo,JoinDate,STATUS) "
              <<"VALUES ('"<<firstname<<"','"<<lastname<<"','"<<phone_no<<"',DATE('"<<join_date<<"'),'"<<Status<<"')";
    }
    else{
        query1<<"INSERT INTO DonorsInfo(FirstName,LastName,PhoneNo,STATUS) "
              <<"VALUES ('"<<firstname<<"','"<<lastname<<"','"<<phone_no<<"','"<<Status<<"')";
    }
    if(!mysql_query(Database::connect,query1.str().c_str())){
        cout<<"Donor Successfully added."<<endl;
        Sleep(3000);
    }
    else{
        cout<<"Donor addition get failed."<<endl;
        Sleep(3000);
    }
}


void Donor::delete_donor(void){
    stringstream query;
    int id,valid = 0;
    string d;
    while(!valid){
        system("cls");
        cout<<"\t   Note : This function can only delete Donor with nil record.For complete deletion first delete full donor record year by year in Donation section"<<endl<<endl;
        cout<<"Enter Valid Donor ID : "<<endl;
        cin>>d;
        if(cin.fail()){
            cout<<"Enter a valid ID-number(digits only)."<<endl;
            cin.clear();
            cin.ignore(256,'\n');
            Sleep(2000);
            system("cls");
            continue;
        }
        if(!t.is_valid_num(d)||d.length()==0){
            cout<<"Enter a valid ID-number(digits only)."<<endl;
            cin.clear();
            cin.ignore(256,'\n');
            Sleep(2000);
            system("cls");
            continue;
        }
        id = atoi(d.c_str());
        valid = 1;
    }
    query<<"DELETE FROM DonorsInfo WHERE ID = "<<id;
    if(!mysql_query(Database::connect,query.str().c_str())){
        if(mysql_affected_rows(Database::connect))
            cout<<"Donor Successfully deleted from Database."<<endl;
        else{
            cout<<"No Donor Found with ID = "<<id<<" in our Database."<<endl;
        }
        Sleep(2000);
    }
    else{
        cout<<"Donor Deletion Failed."<<endl;
        Sleep(2000);
    }
}


int Donor::search_donor_id(void){
    int valid = 0,id;
    string d;
    stringstream query;
    while(!valid){
        system("cls");
        cout<<"Enter Valid Donor ID : "<<endl;
        cin>>d;
        if(cin.fail()){
            cout<<"Enter a valid ID-number(digits only)."<<endl;
            cin.clear();
            cin.ignore(256,'\n');
            Sleep(2000);
            system("cls");
            continue;
        }
        if(!t.is_valid_id(d)||d.length()==0){
            cout<<"Enter a valid ID-number(digits only)."<<endl;
            cin.clear();
            cin.ignore(256,'\n');
            Sleep(2000);
            system("cls");
            continue;
        }
        id = atoi(d.c_str());
        valid = 1;
    }
    query <<"SELECT * FROM DonorsInfo WHERE ID = "<<id;
    cout<<"Searching";

    for(int i=0;i<2;i++){
        Sleep(400);
        cout<<".";
        Sleep(400);
        cout<<".";
        Sleep(400);
        cout<<".";
        Sleep(400);
        cout<<"\b\b\b   \b\b\b";
    }
    if(!mysql_query(Database::connect,query.str().c_str())){
        MYSQL_RES* result = mysql_store_result(Database::connect);
        if(mysql_num_rows(result)){
            MYSQL_ROW row;
            cout<<"\n\t\t     Match Found."<<endl<<endl;
            TextTable t( '-', '|', '+' );
            t.add("First Name");
            t.add("Last Name");
            t.add("Phone Number");
            t.add("Joining Date");
            t.add("Status");
            t.endOfRow();
            Sleep(2000);
            while((row = mysql_fetch_row(result))!=NULL){
                /*cout<<"First Name : "*/;if(row[1]){t.add(row[1]);}else{t.add("Nil");}
                /*cout<<"Last Name : ";*/if(row[2]){t.add(row[2]);}else{t.add("Nil");}
                /*cout<<"Phone Number ";*/if(row[3]){t.add(row[3]);}else{t.add("Nil");}
                /*cout<<"Joining Date ";*/if(row[4]){t.add(row[4]);}else{t.add("Nil");}
                /*cout<<"Status : ";*/if(row[5]){t.add(row[5]);}else{t.add("Nil");}
                t.endOfRow();
            }
            t.setAlignment( 2, TextTable::Alignment::LEFT );
            cout<<t;
            mysql_free_result(result);
            return id;
        }
        else{
            cout<<"\nNo Record Found associated with input ID : "<<id<<endl;
            return 0;
        }
    }
    else{
        cout<<"Failed to Access Database."<<mysql_error(Database::connect)<<endl;
        Sleep(2000);
        return -1;
    }
}


void Donor::modify_donor(void){
    int id,valid = 0,i=0,modify_flag=0,update_flag = 0;
    char ch;
    string fname,lname,phone,date,status,temp;
    stringstream query1,query2;
    id = search_donor_id();
    if(id==0)
        return;
    cout<<endl<<endl;
    cout<<"Want to modify Donor's First Name? (y/n) : ";
    cin.ignore(256,'\n');
    ch = getche();
    cout<<endl;
    if(ch=='y'||ch=='Y'){
        while(!valid){
            if(i==0)
                cout<<"Enter Donor's new First Name : "<<endl;
            else
                cout<<"Enter Donor's new First Name Again : "<<endl;
            getline(cin,fname);
            if(cin.fail()){
                cin.clear();
                cin.ignore(256,'\n');
                continue;
            }
            if(!t.is_valid_name(fname)){
                cout<<"Enter a valid name.Only alphabets are allowed."<<endl;
                Sleep(2000);
                i++;
                continue;
            }
            valid = 1;
            temp = fname;
            fname = "'"+temp+"'";
            modify_flag = 1;
        }
    }
    else{
        fname = "FirstName";
    }
    valid = 0;
    i = 0;
    cout<<"Want to modify Donor's Last Name? (y/n) : ";
    ch = getche();
    cout<<endl;
    if(ch=='y'||ch=='Y'){
        while(!valid){
            if(i==0)
                cout<<"Enter Donor's new Last Name : "<<endl;
            else
                cout<<"Enter Donor's new Last Name Again : "<<endl;
            getline(cin,lname);
            if(cin.fail()){
                cout<<"Enter a valid name.Only alphabets are allowed."<<endl;
                cin.clear();
                cin.ignore(256,'\n');
                i++;
                continue;
            }
            if(!t.is_valid_name(lname)){
                cout<<"Enter a valid name.Only alphabets are allowed."<<endl;
                Sleep(2000);
                i++;
                continue;
            }
            valid = 1;
            modify_flag = 1;
            temp = lname;
            lname = "'"+temp+"'";
        }
    }
    else{
        lname = "LastName";
    }
    valid = 0;i=0;
    cout<<"Want to modify Donor's Phone Number? (y/n) : ";
    ch = getche();
    cout<<endl;
    if(ch=='y'||ch=='Y'){
        while(!valid){
            if(i==0)
                cout<<"Enter Donor's new Phone Number : "<<endl;
            else
                cout<<"Enter Donor's new Phone Number Again : "<<endl;
            getline(cin,phone);
            if(cin.fail()){
                cout<<"Enter a valid number.Only digits(0-9) are allowed."<<endl;
                i++;
                cin.clear();
                cin.ignore(256,'\n');
                continue;
            }
            if(!t.is_valid_num(phone)){
                cout<<"Enter a valid number.Only digits(0-9) are allowed."<<endl;
                Sleep(2000);
                i++;
                continue;
            }
            valid = 1;
            temp = phone;
            phone = "'"+temp+"'";
            modify_flag = 1;
        }
    }
    else{
        phone = "PhoneNo";
    }
    valid = 0,i=0;
    cout<<"Want to modify Donor's Joining Date? (y/n) : ";
    ch = getche();
    cout<<endl;
    if(ch=='y'||ch=='Y'){
        int dd,mm,yy;
        while(!valid){
            if(i==0)
                cout<<"Enter Donor's new Joining Date: "<<endl;
            else
                cout<<"Enter Donor's new Joining Date Again : "<<endl;
            cin>>dd;
            cin.get();
            cin>>mm;
            cin.get();
            cin>>yy;
            cin.get();
            if(cin.fail()){
                cout<<"Enter a valid date with correct format(DD-MM-YY)."<<endl;
                cin.clear();
                cin.ignore(256,'\n');
                i++;
                Sleep(2000);
                continue;
            }
            if(!t.is_valid_date(dd,mm,yy)){
                cout<<"Invalid Date.Enter Date with correct ranges."<<endl;
                cin.ignore(256,'\n');
                i++;
                Sleep(2000);
                continue;
            }
            valid = 1;
            date = std::to_string(yy)+"-"+to_string(mm)+"-"+to_string(dd);
            temp = date;
            date = "'"+date+"'";
            modify_flag = 1;
        }
    }
    else{
        date="JoinDate";
    }
    valid = 0,i=0;
    cout<<"Want to modify Donor's Status? (y/n) : ";
    ch = getche();
    cout<<endl;
    if(ch=='y'||ch=='Y'){
        while(!valid){
            int choice;
            if(i==0)
                cout<<"Enter Donor Status {1:Active,2:In-active,3:Unknown} : "<<endl;
            else
                cout<<"Enter Donor Status  Again {1:Active,2:In-active,3:Unknown} : "<<endl;
            cin>>choice;
            if(cin.fail()){
                cout<<"Enter a valid choice."<<endl;
                cin.clear();
                cin.ignore(256,'\n');
                i++;
                Sleep(2000);
                continue;
            }
            if(!(choice >= 1 && choice <=3)){
                cout<<"Select a given choice."<<endl;
                i++;
                Sleep(2000);
                continue;
            }
            if(choice == 1)
                status = "Active";
            else if(choice == 2)
                status = "In-Active";
            else
                status = "Unknown";
            valid = 1;
            temp = status;
            status = "'"+status+"'";
            modify_flag = 1;
        }

    }
    else{
        status="STATUS";
    }
    if(!modify_flag){
        cout<<"No changes are made as per your choices."<<endl;
        Sleep(3000);
        return;
    }
    if (date=="JoinDate")
        query1<<"UPDATE DonorsInfo SET FirstName = "<<fname<<",LastName = "<<lname<<",PhoneNo = "<<phone
        <<",JoinDate = "<<date<<",STATUS= "<<status<<" WHERE ID = "<<id;
    else
        query1<<"UPDATE DonorsInfo SET FirstName = "<<fname<<",LastName = "<<lname<<",PhoneNo = "<<phone
        <<",JoinDate = DATE("<<date<<"),STATUS= "<<status<<" WHERE ID = "<<id;

    if(!mysql_query(Database::connect,query1.str().c_str())){
        if(mysql_affected_rows(Database::connect)){
            cout<<"Record Updated Successfully."<<endl;
            update_flag = 1;
            Sleep(2000);
        }
        else{
            cout<<"\nNo record found associated with ID = "<<id<<endl;
            Sleep(2000);
        }
    }
    else{
        cout<<"Failed to access database correctly."<<mysql_error(Database::connect)<<endl;
    }
    if(update_flag){
        query2<<"SELECT * FROM DonorsInfo WHERE ID = "<<id;
        if(!mysql_query(Database::connect,query2.str().c_str())){
            MYSQL_RES* result = mysql_store_result(Database::connect);
            if(mysql_num_rows(result)){
                cout<<"\n\n\t\t     Updated Record."<<endl<<endl<<endl;
                TextTable t( '-', '|', '+' );
                t.add("First Name");
                t.add("Last Name");
                t.add("Phone Number");
                t.add("Joining Date");
                t.add("Status");
                t.endOfRow();
                MYSQL_ROW row;
                while((row = mysql_fetch_row(result))!=NULL){
                    /*cout<<"Donor ID : ";*///if(row[0]){t.add(row[0]);}else{t.add("Nil");}
                    /*cout<<"First Name : "*/;if(row[1]){t.add(row[1]);}else{t.add("Nil");}
                    /*cout<<"Last Name : ";*/if(row[2]){t.add(row[2]);}else{t.add("Nil");}
                    /*cout<<"Phone Number ";*/if(row[3]){t.add(row[3]);}else{t.add("Nil");}
                    /*cout<<"Joining Date ";*/if(row[4]){t.add(row[4]);}else{t.add("Nil");}
                    /*cout<<"Status : ";*/if(row[5]){t.add(row[5]);}else{t.add("Nil");}
                    t.endOfRow();
                }
            t.setAlignment( 2, TextTable::Alignment::LEFT );
            cout<<t;
            mysql_free_result(result);
            }
        }
    }
}


void Donor::display_donors(void){
    stringstream  query;
    system("cls");
    query<<"SELECT * FROM DonorsInfo";
    if(!mysql_query(Database::connect,query.str().c_str())){
        MYSQL_RES* result = mysql_store_result(Database::connect);
        if(mysql_num_rows(result)){
            cout<<"\t\t\tDonor Records"<<endl<<endl<<endl;
            MYSQL_ROW row;
            TextTable t( '-', '|', '+' );
            t.add("Donor ID");
            t.add("First Name");
            t.add("Last Name");
            t.add("Phone Number");
            t.add("Joining Date");
            t.add("Status");
            t.endOfRow();
            while((row = mysql_fetch_row(result))!=NULL){
                /*cout<<"Donor ID : ";*/if(row[0]){t.add(row[0]);}else{t.add("Nil");}
                /*cout<<"First Name : "*/;if(row[1]){t.add(row[1]);}else{t.add("Nil");}
                /*cout<<"Last Name : ";*/if(row[2]){t.add(row[2]);}else{t.add("Nil");}
                /*cout<<"Phone Number ";*/if(row[3]){t.add(row[3]);}else{t.add("Nil");}
                /*cout<<"Joining Date ";*/if(row[4]){t.add(row[4]);}else{t.add("Nil");}
                /*cout<<"Status : ";*/if(row[5]){t.add(row[5]);}else{t.add("Nil");}
                t.endOfRow();
            }
            t.setAlignment( 2, TextTable::Alignment::LEFT );
            cout<<t;
        }
        else{
            cout<<"No records are present in Donor Table."<<endl;
            Sleep(3000);
        }
        mysql_free_result(result);
    }
    else{
        cout<<"Failed to access Database correctly."<<mysql_error(Database::connect)<<endl;
    }
    cout<<"\n\nPress Enter key to return..."<<endl;
    getche();
}


Donation::Donation(){
    amount = 0;
    total = 0;
}


bool Donation::in_organ_year(string y){
    int number_of_years,i;
    string *years;
    stringstream query;
    query<<"SELECT * FROM OrganYears"<<endl;
    if(!mysql_query(Database::connect,query.str().c_str())){
        MYSQL_RES* result = mysql_store_result(Database::connect);
        if((number_of_years = mysql_num_rows(result))){
            years = new string[number_of_years];
            i=0;
            MYSQL_ROW row;
            while((row=mysql_fetch_row(result))!=NULL){
                years[i]=row[0];
                i++;
            }
        }
        else{
            cout<<"Organisation Working years table is empty."<<endl;
            return -2;
        }
        mysql_free_result(result);
    }
    else{
        cout<<"Failed to access Database correctly."<<mysql_error(Database::connect)<<endl;
        return -1;
    }
    for(i=0;i<number_of_years;i++){
        if(y==years[i])
            return true;
    }
    return false;
}


string Donation::return_month(int month){
    string m[13]={"0","JAN","FEB","MAR","APR","MAY","JUN","JUL","AUG","SEP","OCT","NOV","DECM"};
    if(month>=1 &&month<=12)
        return m[month];
    else
        return m[0];
}


void Donation::add_donation(void){
    stringstream query1,query2,query3,query4,query5,query6;
    string id,am,y;
    MYSQL_RES* result;
    int valid = 0,create_table = 0,insert_into=0,m,change_flag = 0,insert_year = 0,is_present = 1;
    while(!valid){
        system("cls");
        cout<<"Enter Donor ID : "<<endl;
        getline(cin,id);
        if(cin.fail()){
            cout<<"Enter a valid Donor ID."<<endl;
            cin.clear();
            cin.ignore(256,'\n');
            Sleep(2000);
            continue;
        }
        if(!t.is_valid_id(id)||id.length()==0){
            cout<<"Enter a valid Donor ID.Only digits(0-9) are allowed."<<endl;
            Sleep(2000);
            continue;
        }
        valid = 1;
        ID = atoi(id.c_str());
    }
    query1<<"SELECT * FROM DonorsInfo WHERE ID = "<<ID;
    if(!mysql_query(Database::connect,query1.str().c_str())){
        result = mysql_store_result(Database::connect);
        if(!mysql_num_rows(result)){
            cout<<"No record associated with ID = "<<ID<<" in our Database.Add it first in donors area."<<endl;
            Sleep(2000);
            is_present = 0;
        }
        mysql_free_result(result);
    }
    else{
        cout<<"Failed to access Database correctly."<<mysql_error(Database::connect)<<endl;
    }
    if(!is_present)
        return;
    valid = 0;
    while(!valid){
        cout<<"Enter Donation Receiving Year(XXXX) : "<<endl;
        getline(cin,y);
        if(cin.fail()){
            cout<<"Enter a valid year.Only digits are allowed."<<endl;
            cin.clear();
            cin.ignore(256,'\n');
            Sleep(2000);
            system("cls");
            cout<<"Enter Donor ID : "<<endl;
            cout<<id<<endl;
            continue;
        }
        if(!t.is_valid_year(y)){
            cout<<"Enter a valid year(1900-2200)."<<endl;
            Sleep(2000);
            system("cls");
            cout<<"Enter Donor ID : "<<endl;
            cout<<id<<endl;
            continue;
        }
        valid = 1;
        year = y;
    }
    if(!in_organ_year(year)){
        query2<<"CREATE TABLE IF NOT EXISTS _"<<year<<" ("
              <<"ID INT NOT NULL,"
              <<"JAN DOUBLE NOT NULL DEFAULT 0,"
              <<"FEB DOUBLE NOT NULL DEFAULT 0,"
              <<"MAR DOUBLE NOT NULL DEFAULT 0,"
              <<"APR DOUBLE NOT NULL DEFAULT 0,"
              <<"MAY DOUBLE NOT NULL DEFAULT 0,"
              <<"JUN DOUBLE NOT NULL DEFAULT 0,"
              <<"JUL DOUBLE NOT NULL DEFAULT 0,"
              <<"AUG DOUBLE NOT NULL DEFAULT 0,"
              <<"SEP DOUBLE NOT NULL DEFAULT 0,"
              <<"OCT DOUBLE NOT NULL DEFAULT 0,"
              <<"NOV DOUBLE NOT NULL DEFAULT 0,"
              <<"DECM DOUBLE NOT NULL DEFAULT 0,"
              <<"TOTAL DOUBLE NOT NULL DEFAULT 0,"
              <<"FOREIGN KEY(ID) REFERENCES DonorsInfo(ID)"
              <<")";
    }
    if(!in_organ_year(year)){
    if(!mysql_query(Database::connect,query2.str().c_str())){
        if(!mysql_affected_rows(Database::connect)){
            create_table = 1;
        }
    }
    else{
        cout<<"Unable to access Database correctly."<<mysql_error(Database::connect)<<endl;
        Sleep(2000);
    }
    }
    if(create_table){
        query6<<"INSERT INTO OrganYears(YR) VALUES("<<year<<")";
        if(!mysql_query(Database::connect,query6.str().c_str())){
           if(mysql_affected_rows(Database::connect)){
               insert_year = 1;
           }
        }
        else{
        cout<<"Failed to access Database correctly."<<mysql_error(Database::connect)<<endl;
        }
    }
    valid = 0;
    while(!valid){
        cout<<"Select a month{1:JAN,2:FEB,3:MAR,4:APR,5:MAY,6:JUN,7:JUL,8:AUG,9:SEP,10:OCT,11:NOVM,12:DECM} : "<<endl;
        cin>>m;
        if(cin.fail()){
            cout<<"Input a valid choice."<<endl;
            cin.clear();
            cin.ignore(256,'\n');
            Sleep(2000);
            system("cls");
            cout<<"Enter Donor ID : "<<endl;
            cout<<id<<endl;
            cout<<"Enter Donation Receiving Year(XXXX) : "<<endl;
            cout<<y<<endl;
            continue;
        }
        if(!t.is_valid_month(m)){
            cout<<"Enter a valid month(1-12)."<<endl;
            Sleep(2000);
            system("cls");
            cout<<"Enter Donor ID : "<<endl;
            cout<<id<<endl;
            cout<<"Enter Donation Receiving Year(XXXX) : "<<endl;
            cout<<y<<endl;
            continue;
        }
        valid = 1;
        month = return_month(m);
    }
    valid = 0;
    cin.ignore(256,'\n');
    while(!valid){
        cout<<"Enter Donation Amount : "<<endl;
        getline(cin,am);
        if(cin.fail()){
            cout<<"Enter a valid donation amount."<<endl;
            cin.clear();
            cin.ignore(256,'\n');
            Sleep(2000);
            system("cls");
            cout<<"Enter Donor ID : "<<endl;
            cout<<id<<endl;
            cout<<"Enter Donation Receiving Year(XXXX) : "<<endl;
            cout<<y<<endl;
            cout<<"Select a month{1:JAN,2:FEB,3:MAR,4:APR,5:MAY,6:JUN,7:JUL,8:AUG,9:SEP,10:OCT,11:NOVM,12:DECM} : "<<endl;
            cout<<m<<endl;
            continue;
        }
        else if(!t.is_valid_amount(am)){
            cout<<"Enter a valid amount.Only digits(0-9) and decimal points are allowed."<<endl;
            Sleep(2000);
            system("cls");
            cout<<"Enter Donor ID : "<<endl;
            cout<<id<<endl;
            cout<<"Enter Donation Receiving Year(XXXX) : "<<endl;
            cout<<y<<endl;
            cout<<"Select a month{1:JAN,2:FEB,3:MAR,4:APR,5:MAY,6:JUN,7:JUL,8:AUG,9:SEP,10:OCT,11:NOVM,12:DECM} : "<<endl;
            cout<<m<<endl;
            continue;
        }
        valid = 1;
        amount = atof(am.c_str());
    }
    query3<<"SELECT * FROM _"<<year<<" WHERE ID = "<<ID;
    if(!mysql_query(Database::connect,query3.str().c_str())){
        result = mysql_store_result(Database::connect);
        if(!mysql_num_rows(result)){
            insert_into = 1;
        }
        mysql_free_result(result);
    }
    else{
        cout<<"Failed to access Database correctly."<<mysql_error(Database::connect)<<endl;
    }
    if(insert_into){
        query4<<"INSERT INTO _"<<year<<" (ID,"<<month<<") VALUES("<<id<<","<<am<<")";
    }
    else{
        query4<<"UPDATE _"<<year<<" SET "<<month<<" = "<<am<<" WHERE ID = "<<ID;
    }
    if(!mysql_query(Database::connect,query4.str().c_str())){
        if(mysql_affected_rows(Database::connect)){
            change_flag = 1;
        }
        else{
            cout<<"Failed to add donation."<<endl;
            Sleep(2000);
        }
    }
    else{
        cout<<"Failed to access Database correctly."<<mysql_error(Database::connect)<<endl;
        Sleep(2000);
    }
    if(change_flag){
        query5<<"UPDATE _"<<year<<" SET TOTAL =JAN+FEB+MAR+APR+MAY+JUN+JUL+AUG+SEP+OCT+NOV+DECM WHERE ID = "<<ID;
    }
    else{
        return;
    }
    if(!mysql_query(Database::connect,query5.str().c_str())){
        if(mysql_affected_rows(Database::connect)){
            cout<<"Donation Added Successfully."<<endl;
            Sleep(3000);
        }
        else{
            cout<<"Donation Addition process failed."<<endl;
            Sleep(2000);
        }
    }
    else{
        cout<<"Failed to access Database correctly."<<mysql_error(Database::connect)<<endl;
        Sleep(2000);
    }
}


void Donation::delete_donation_monthly(void){
    int valid = 0,m,in_year=0,update_flag = 0,is_present = 1;
    MYSQL_RES* result;
    string id,y;
    stringstream query1,query2,query3,query4;
    while(!valid){
        system("cls");
        cout<<"\t\t\tNote : Deleting Monthly Donation will affect the total donation count of organization."<<endl;
        cout<<"Enter Donor ID : "<<endl;
        getline(cin,id);
        if(cin.fail()){
            cout<<"Enter a valid Donor ID : "<<endl;
            cin.clear();
            cin.ignore(256,'\n');
            Sleep(2000);
            continue;
        }
        if(!t.is_valid_id(id)||id.length()==0){
            cout<<"Enter a valid Donor ID.Only Digits(0-9) are allowed."<<endl;
            Sleep(2000);
            continue;
        }
        valid = 1;
        ID = atoi(id.c_str());
    }
    query1<<"SELECT * FROM DonorsInfo WHERE ID = "<<ID;
    if(!mysql_query(Database::connect,query1.str().c_str())){
        result = mysql_store_result(Database::connect);
        if(!mysql_num_rows(result)){
            cout<<"\nNo record associated with ID = "<<ID<<" in our Database.Add it first in donors area."<<endl;
            Sleep(2000);
            is_present = 0;
        }

        mysql_free_result(result);
    }
    else{
        cout<<"Failed to access Database correctly."<<mysql_error(Database::connect)<<endl;
    }
    if(!is_present)
        return;
    valid = 0;
    while(!valid){
        cout<<"Enter Donation Year(XXXX) : "<<endl;
        getline(cin,y);
        if(cin.fail()){
            cout<<"Enter a valid year.Only digits are allowed."<<endl;
            cin.clear();
            cin.ignore(256,'\n');
            Sleep(2000);
            system("cls");
            cout<<"\t\t\tNote : Deleting Monthly Donation will affect the total donation count of organization."<<endl;
            cout<<"Enter Donor ID : "<<endl;
            cout<<id<<endl;
            continue;
        }
        if(!t.is_valid_year(y)){
            cout<<"Enter a valid year(1900-2200)."<<endl;
            Sleep(2000);
            system("cls");
            cout<<"\t\t\tNote : Deleting Monthly Donation will affect the total donation count of organization."<<endl;
            cout<<"Enter Donor ID : "<<endl;
            cout<<id<<endl;
            continue;
        }
        valid = 1;
        year = y;
    }
    if(!in_organ_year(year)){
        cout<<"\nNo record exist for Year : "<<year<<" in our Database."<<endl;
        return;
    }
    valid = 0;
    query2<<"SELECT * FROM _"<<year<<" WHERE ID = "<<id;
    if(!mysql_query(Database::connect,query2.str().c_str())){
        int n_of_r;
        result = mysql_store_result(Database::connect);
        if((n_of_r=mysql_num_rows(result))> 0){
            MYSQL_ROW row;
            cout<<"\t\t\t\tDonation Record In "<<year<<" of ID "<<ID<<endl<<endl;
            in_year = 1;
            TextTable t( '-', '|', '+' );
            t.add("JANUARY");
            t.add("FEBUARY");
            t.add("MARCH");
            t.add("APRIL");
            t.add("MAY");
            t.add("JUNE");
            t.add("JULY");
            t.add("AUGUST");
            t.add("SEPTEMBER");
            t.add("OCTOBER");
            t.add("NOVEMBER");
            t.add("DECEMBER");
            t.add("TOTAL");
            t.endOfRow();
            while((row=mysql_fetch_row(result))!=NULL){
                /*cout<<"Jan : ";*/if(strcmp(row[1],"0")){t.add(row[1]);}else{t.add("nil");}
                /*cout<<"Feb : ";*/if(strcmp(row[2],"0")){t.add(row[2]);}else{t.add("nil");}
                /*cout<<"Mar : ";*/if(strcmp(row[3],"0")){t.add(row[3]);}else{t.add("nil");};
                /*cout<<"Apr : ";*/if(strcmp(row[4],"0")){t.add(row[4]);}else{t.add("nil");}
                /*cout<<"May : ";*/if(strcmp(row[5],"0")){t.add(row[5]);}else{t.add("nil");}
                /*cout<<"June : ";*/if(strcmp(row[6],"0")){t.add(row[6]);}else{t.add("nil");}
                /*cout<<"July : ";*/if(strcmp(row[7],"0")){t.add(row[7]);}else{t.add("nil");}
                /*cout<<"Aug : ";*/if(strcmp(row[8],"0")){t.add(row[8]);}else{t.add("nil");}
                /*cout<<"Sep : ";*/if(strcmp(row[9],"0")){t.add(row[9]);}else{t.add("nil");}
                /*cout<<"Oct : ";*/if(strcmp(row[10],"0")){t.add(row[10]);}else{t.add("nil");}
                /*cout<<"Nov : ";*/if(strcmp(row[11],"0")){t.add(row[11]);}else{t.add("nil");}
                /*cout<<"Dec : ";*/if(strcmp(row[12],"0")){t.add(row[12]);}else{t.add("nil");}
                /*cout<<"Total : ";*/if(strcmp(row[13],"0")){t.add(row[13]);}else{t.add("nil");}
                t.endOfRow();
            }
            t.setAlignment( 2, TextTable::Alignment::LEFT );
            cout<<t;
        }
        else{
            cout<<"\nNo record exist for ID : "<<ID<<" in "<<year<<endl;
            Sleep(2000);
        }
        mysql_free_result(result);
    }
    else{
        cout<<"Failed to access Database correctly."<<mysql_error(Database::connect)<<endl;
    }
    if(!in_year)
        return;
    cout<<endl<<endl;
    valid = 0;
    while(!valid){
        cout<<"Select a month to delete record{1:JAN,2:FEB,3:MAR,4:APR,5:MAY,6:JUN,7:JUL,8:AUG,9:SEP,10:OCT,11:NOVM,12:DECM} : "<<endl;
        cin>>m;
        if(cin.fail()){
            cout<<"Input a valid choice."<<endl;
            cin.clear();
            cin.ignore(256,'\n');
            Sleep(2000);
            system("cls");
            cout<<"\t\t\tNote : Deleting Monthly Donation will affect the total donation count of organization."<<endl;
            cout<<"Enter Donor ID : "<<endl;
            cout<<id<<endl;
            cout<<"Enter Donation Year(XXXX) : "<<endl;
            cout<<y<<endl;
            if(!mysql_query(Database::connect,query2.str().c_str())){
                int n_of_r;
                result = mysql_store_result(Database::connect);
                if((n_of_r=mysql_num_rows(result))> 0){
                    MYSQL_ROW row;
                    cout<<"\t\t\t\tDonation Record In "<<year<<" of ID "<<ID<<endl<<endl;
                    TextTable t( '-', '|', '+' );
                    t.add("JANUARY");
                    t.add("FEBUARY");
                    t.add("MARCH");
                    t.add("APRIL");
                    t.add("MAY");
                    t.add("JUNE");
                    t.add("JULY");
                    t.add("AUGUST");
                    t.add("SEPTEMBER");
                    t.add("OCTOBER");
                    t.add("NOVEMBER");
                    t.add("DECEMBER");
                    t.add("TOTAL");
                    t.endOfRow();
                    while((row=mysql_fetch_row(result))!=NULL){
                        /*cout<<"Jan : ";*/if(strcmp(row[1],"0")){t.add(row[1]);}else{t.add("nil");}
                        /*cout<<"Feb : ";*/if(strcmp(row[2],"0")){t.add(row[2]);}else{t.add("nil");}
                        /*cout<<"Mar : ";*/if(strcmp(row[3],"0")){t.add(row[3]);}else{t.add("nil");};
                        /*cout<<"Apr : ";*/if(strcmp(row[4],"0")){t.add(row[4]);}else{t.add("nil");}
                        /*cout<<"May : ";*/if(strcmp(row[5],"0")){t.add(row[5]);}else{t.add("nil");}
                        /*cout<<"June : ";*/if(strcmp(row[6],"0")){t.add(row[6]);}else{t.add("nil");}
                        /*cout<<"July : ";*/if(strcmp(row[7],"0")){t.add(row[7]);}else{t.add("nil");}
                        /*cout<<"Aug : ";*/if(strcmp(row[8],"0")){t.add(row[8]);}else{t.add("nil");}
                        /*cout<<"Sep : ";*/if(strcmp(row[9],"0")){t.add(row[9]);}else{t.add("nil");}
                        /*cout<<"Oct : ";*/if(strcmp(row[10],"0")){t.add(row[10]);}else{t.add("nil");}
                        /*cout<<"Nov : ";*/if(strcmp(row[11],"0")){t.add(row[11]);}else{t.add("nil");}
                        /*cout<<"Dec : ";*/if(strcmp(row[12],"0")){t.add(row[12]);}else{t.add("nil");}
                        /*cout<<"Total : ";*/if(strcmp(row[13],"0")){t.add(row[13]);}else{t.add("nil");}
                        t.endOfRow();
                    }
                    t.setAlignment( 2, TextTable::Alignment::LEFT );
                    cout<<t;
                }
                mysql_free_result(result);
            }
            continue;
        }
        if(!t.is_valid_month(m)){
            cout<<"Enter a valid month(1-12)."<<endl;
            cin.ignore(256,'\n');
            Sleep(2000);
            system("cls");
            cout<<"\t\t\tNote : Deleting Monthly Donation will affect the total donation count of organization."<<endl;
            cout<<"Enter Donor ID : "<<endl;
            cout<<id<<endl;
            cout<<"Enter Donation Year(XXXX) : "<<endl;
            cout<<y<<endl;
            if(!mysql_query(Database::connect,query2.str().c_str())){
                int n_of_r;
                result = mysql_store_result(Database::connect);
                if((n_of_r=mysql_num_rows(result))> 0){
                    MYSQL_ROW row;
                    cout<<"\t\t\t\tDonation Record In "<<year<<" of ID "<<ID<<endl<<endl;
                    TextTable t( '-', '|', '+' );
                    t.add("JANUARY");
                    t.add("FEBUARY");
                    t.add("MARCH");
                    t.add("APRIL");
                    t.add("MAY");
                    t.add("JUNE");
                    t.add("JULY");
                    t.add("AUGUST");
                    t.add("SEPTEMBER");
                    t.add("OCTOBER");
                    t.add("NOVEMBER");
                    t.add("DECEMBER");
                    t.add("TOTAL");
                    t.endOfRow();
                    while((row=mysql_fetch_row(result))!=NULL){
                        /*cout<<"Jan : ";*/if(strcmp(row[1],"0")){t.add(row[1]);}else{t.add("nil");}
                        /*cout<<"Feb : ";*/if(strcmp(row[2],"0")){t.add(row[2]);}else{t.add("nil");}
                        /*cout<<"Mar : ";*/if(strcmp(row[3],"0")){t.add(row[3]);}else{t.add("nil");};
                        /*cout<<"Apr : ";*/if(strcmp(row[4],"0")){t.add(row[4]);}else{t.add("nil");}
                        /*cout<<"May : ";*/if(strcmp(row[5],"0")){t.add(row[5]);}else{t.add("nil");}
                        /*cout<<"June : ";*/if(strcmp(row[6],"0")){t.add(row[6]);}else{t.add("nil");}
                        /*cout<<"July : ";*/if(strcmp(row[7],"0")){t.add(row[7]);}else{t.add("nil");}
                        /*cout<<"Aug : ";*/if(strcmp(row[8],"0")){t.add(row[8]);}else{t.add("nil");}
                        /*cout<<"Sep : ";*/if(strcmp(row[9],"0")){t.add(row[9]);}else{t.add("nil");}
                        /*cout<<"Oct : ";*/if(strcmp(row[10],"0")){t.add(row[10]);}else{t.add("nil");}
                        /*cout<<"Nov : ";*/if(strcmp(row[11],"0")){t.add(row[11]);}else{t.add("nil");}
                        /*cout<<"Dec : ";*/if(strcmp(row[12],"0")){t.add(row[12]);}else{t.add("nil");}
                        /*cout<<"Total : ";*/if(strcmp(row[13],"0")){t.add(row[13]);}else{t.add("nil");}
                        t.endOfRow();
                    }
                    t.setAlignment( 2, TextTable::Alignment::LEFT );
                    cout<<t;
                }
                mysql_free_result(result);
            }
            continue;
        }
        valid = 1;
        month = return_month(m);
    }
    query3<<"UPDATE _"<<year<<" SET "<<month<<" = 0 WHERE ID = "<<ID;
    if(!mysql_query(Database::connect,query3.str().c_str())){
        if(mysql_affected_rows(Database::connect)){
            update_flag = 1;
        }

    }
    else{
        cout<<"Failed to access Database correctly."<<mysql_error(Database::connect)<<endl;
    }
    if(update_flag)
        query4<<"UPDATE _"<<year<<" SET TOTAL =JAN+FEB+MAR+APR+MAY+JUN+JUL+AUG+SEP+OCT+NOV+DECM WHERE ID = "<<ID;
    else{
        cout<<"No need to delete nil value."<<endl;
        Sleep(2000);
        return;
    }
    if(!mysql_query(Database::connect,query4.str().c_str())){
        if(mysql_affected_rows(Database::connect)){
            cout<<"Donation Deleted Successfully."<<endl;
            Sleep(3000);
        }
        else{
            cout<<"Donation Deletion process failed."<<endl;
            Sleep(2000);
        }
    }
    else{
        cout<<"Failed to access Database correctly."<<mysql_error(Database::connect)<<endl;
        Sleep(2000);
    }
}


void Donation::delete_donation_yearly(void){
    int valid = 0,is_present = 1,in_year =0;
    string id,y;
    MYSQL_RES * result;
    stringstream query1,query2,query3;
    char ch;
    while(!valid){
        system("cls");
        cout<<"\t\t\tNote : Deleting Yearly Donation will heavily affect the total donation count of organization."<<endl;
        cout<<"Enter Donor ID  : "<<endl;
        getline(cin,id);
        if(cin.fail()){
            cout<<"Enter a valid Donor ID : "<<endl;
            cin.clear();
            cin.ignore(256,'\n');
            Sleep(2000);
            continue;
        }
        if(!t.is_valid_id(id)||id.length()==0){
            cout<<"Enter a valid Donor ID.Only Digits(0-9) are allowed."<<endl;
            Sleep(2000);
            continue;
        }
        valid = 1;
        ID = atoi(id.c_str());
    }
    query1<<"SELECT * FROM DonorsInfo WHERE ID = "<<ID;
    if(!mysql_query(Database::connect,query1.str().c_str())){
        result = mysql_store_result(Database::connect);
        if(!mysql_num_rows(result)){
            cout<<"\nNo record associated with ID = "<<ID<<" in our Database.Add it first in donors area."<<endl;
            is_present = 0;
            Sleep(2000);
        }
        mysql_free_result(result);
    }
    else{
        cout<<"Failed to access Database correctly."<<mysql_error(Database::connect)<<endl;
    }
    if(!is_present)
        return;
    valid = 0;
    while(!valid){
        cout<<"Enter Donation Year(XXXX) : "<<endl;
        getline(cin,y);
        if(cin.fail()){
            cout<<"Enter a valid year.Only digits are allowed."<<endl;
            cin.clear();
            cin.ignore(256,'\n');
            Sleep(2000);
            system("cls");
            cout<<"\t\t\tNote : Deleting Yearly Donation will heavily affect the total donation count of organization."<<endl;
            cout<<"Enter Donor ID : "<<endl;
            cout<<id<<endl;
            continue;
        }
        if(!t.is_valid_year(y)){
            cout<<"Enter a valid year(1900-2200)."<<endl;
            Sleep(2000);
            system("cls");
            cout<<"\t\t\tNote : Deleting Yearly Donation will heavily affect the total donation count of organization."<<endl;
            cout<<"Enter Donor ID : "<<endl;
            cout<<id<<endl;
            continue;
        }
        valid = 1;
        year = y;
    }
    if(!in_organ_year(year)){
        cout<<"No record exist for Year : "<<year<<" in our Database."<<endl;
        Sleep(2000);
        return;
    }
    valid = 0;
    query2<<"SELECT * FROM _"<<year<<" WHERE ID = "<<ID;
    if(!mysql_query(Database::connect,query2.str().c_str())){
        int n_of_r;
        result = mysql_store_result(Database::connect);
        if((n_of_r=mysql_num_rows(result))> 0){
            MYSQL_ROW row;
            in_year = 1;
            cout<<"\t\t\t\tDonation Record In "<<year<<" of ID "<<ID<<endl<<endl;
            TextTable t( '-', '|', '+' );
            t.add("JANUARY");
            t.add("FEBUARY");
            t.add("MARCH");
            t.add("APRIL");
            t.add("MAY");
            t.add("JUNE");
            t.add("JULY");
            t.add("AUGUST");
            t.add("SEPTEMBER");
            t.add("OCTOBER");
            t.add("NOVEMBER");
            t.add("DECEMBER");
            t.add("TOTAL");
            t.endOfRow();
            while((row=mysql_fetch_row(result))!=NULL){
                /*cout<<"Jan : ";*/if(strcmp(row[1],"0")){t.add(row[1]);}else{t.add("nil");}
                /*cout<<"Feb : ";*/if(strcmp(row[2],"0")){t.add(row[2]);}else{t.add("nil");}
                /*cout<<"Mar : ";*/if(strcmp(row[3],"0")){t.add(row[3]);}else{t.add("nil");};
                /*cout<<"Apr : ";*/if(strcmp(row[4],"0")){t.add(row[4]);}else{t.add("nil");}
                /*cout<<"May : ";*/if(strcmp(row[5],"0")){t.add(row[5]);}else{t.add("nil");}
                /*cout<<"June : ";*/if(strcmp(row[6],"0")){t.add(row[6]);}else{t.add("nil");}
                /*cout<<"July : ";*/if(strcmp(row[7],"0")){t.add(row[7]);}else{t.add("nil");}
                /*cout<<"Aug : ";*/if(strcmp(row[8],"0")){t.add(row[8]);}else{t.add("nil");}
                /*cout<<"Sep : ";*/if(strcmp(row[9],"0")){t.add(row[9]);}else{t.add("nil");}
                /*cout<<"Oct : ";*/if(strcmp(row[10],"0")){t.add(row[10]);}else{t.add("nil");}
                /*cout<<"Nov : ";*/if(strcmp(row[11],"0")){t.add(row[11]);}else{t.add("nil");}
                /*cout<<"Dec : ";*/if(strcmp(row[12],"0")){t.add(row[12]);}else{t.add("nil");}
                /*cout<<"Total : ";*/if(strcmp(row[13],"0")){t.add(row[13]);}else{t.add("nil");}
                t.endOfRow();
            }
            t.setAlignment( 2, TextTable::Alignment::LEFT );
            cout<<t;
        }
        else{
            cout<<"\nNo record exist for ID : "<<ID<<" in "<<year<<endl;
            Sleep(2000);
        }
        mysql_free_result(result);
    }
    else{
        cout<<"Failed to access Database correctly."<<mysql_error(Database::connect)<<endl;
    }
    if(!in_year)
        return;
    cout<<endl;
    while(!valid){
        cout<<"Want to Delete the above yearly Donation Data? Enter(y/n) : "<<endl;
        cin>>ch;
        if(ch=='y'||ch=='Y')
            query3<<"UPDATE _"<<year<<" SET JAN = 0,FEB = 0,MAR = 0,APR = 0,MAR = 0,JUN = 0,"
                  <<"JUL = 0,AUG = 0, SEP = 0,OCT = 0,NOV = 0,DECM = 0, TOTAL = 0 WHERE ID = "<<ID;
        else if(ch=='n'||ch=='N'){
            cout<<"Donation Data is not deleted."<<endl;
            Sleep(2000);
            return;
        }
        else{
            cout<<"Enter a valid choice."<<endl;
            cin.ignore(256,'\n');
            Sleep(2000);
            continue;
        }
        valid = 1;
    }
    if(!mysql_query(Database::connect,query3.str().c_str())){
        if(mysql_affected_rows(Database::connect)){
            cout<<"Donor Data Deleted Successfully."<<endl;
        }
        else{
            cout<<"Failed to Delete the above yearly Donation Data.\nThis error also occurs when trying to delete the nill data for whole year."<<endl;
        }
        Sleep(2000);
    }
    else{
        cout<<"Failed to access Database correctly."<<mysql_error(Database::connect)<<endl;
        Sleep(2000);
    }
}


void Donation::get_donation_monthly(void){
    string yr;
    stringstream query1,query2,query3;
    MYSQL_RES* result;
    int m,valid = 0,choice;
    while(!valid){
        system("cls");
        cout<<"1) Get Total of Specific Month."<<endl;
        cout<<"2) Get Total of Current Month."<<endl;
        cout<<"\nEnter your choice : "<<endl;
        cin>>choice;
        if(cin.fail()){
            cout<<"Select a valid choice."<<endl;
            cin.clear();
            cin.ignore(256,'\n');
            Sleep(2000);
            continue;
        }
        else if(choice<1 || choice>2){
            cout<<"Enter a valid choice."<<endl;
            cin.ignore(256,'\n');
            Sleep(2000);
            continue;
        }
        valid = 1;
    }
    valid = 0;
    cin.ignore(256,'\n');
    if (choice == 1){
        while(!valid){
            cout<<"Enter the year(XXXX) : "<<endl;
            getline(cin,yr);
            if(cin.fail()){
                cout<<"Enter a valid year(XXXX) : "<<endl;
                cin.clear();
                cin.ignore(256,'\n');
                Sleep(2000);
                system("cls");
                cout<<"1) Get Total of Specific Month."<<endl;
                cout<<"2) Get Total of Current Month."<<endl;
                cout<<"\nEnter your choice : "<<endl;
                cout<<choice<<endl;
                continue;
            }
            if(!t.is_valid_year(yr)){
                cout<<"Enter a valid year(1900-2200).Only digits(0-9) are allowed."<<endl;
                Sleep(2000);
                system("cls");
                cout<<"1) Get Total of Specific Month."<<endl;
                cout<<"2) Get Total of Current Month."<<endl;
                cout<<"\nEnter your choice : "<<endl;
                cout<<choice<<endl;
                continue;
            }
            valid = 1;
        }
        if(!in_organ_year(yr)){
            cout<<"No Record exist of year "<<yr<<" in our Database."<<endl;
            Sleep(2000);
            return;
        }
        valid = 0;
        while(!valid){
            cout<<"Select a month{1:JAN,2:FEB,3:MAR,4:APR,5:MAY,6:JUN,7:JUL,8:AUG,9:SEP,10:OCT,11:NOVM,12:DECM} : "<<endl;
            cin>>m;
            if(cin.fail()){
                cout<<"Enter a valid choice."<<endl;
                cin.clear();
                cin.ignore(256,'\n');
                Sleep(2000);
                system("cls");
                cout<<"1) Get Total of Specific Month."<<endl;
                cout<<"2) Get Total of Current Month."<<endl;
                cout<<"\nEnter your choice : "<<endl;
                cout<<choice<<endl;
                cout<<"Enter the year(XXXX) : "<<endl;
                cout<<yr<<endl;
                continue;
            }
            if(!t.is_valid_month(m)){
                cout<<"Select correct month(1-12)."<<endl;
                Sleep(2000);
                system("cls");
                cout<<"1) Get Total of Specific Month."<<endl;
                cout<<"2) Get Total of Current Month."<<endl;
                cout<<"\nEnter your choice : "<<endl;
                cout<<choice<<endl;
                cout<<"Enter the year(XXXX) : "<<endl;
                cout<<yr<<endl;
                continue;
            }
            valid = 1;
            month = return_month(m);
        }
        query1<<"SELECT SUM("<<month<<") FROM _"<<yr;
        if(!mysql_query(Database::connect,query1.str().c_str())){
            result = mysql_store_result(Database::connect);
            if(mysql_num_rows(result)){
                MYSQL_ROW row;
                while((row=mysql_fetch_row(result))!=NULL)
                    cout<<"\n\nTotal Donation of month "<<month<<" of "<<yr<<" is  Rs. "<<row[0]<<endl;
            }
            else{
                cout<<"\nFailed to calculate  monthly total."<<endl;
            }
            mysql_free_result(result);
            }
            else{
            cout<<"Failed to access Database correctly."<<mysql_error(Database::connect)<<endl;
            }
    }
    else if(choice == 2){
        query2<<"SELECT YEAR(CURDATE()),MONTH(CURDATE())";
        if(!mysql_query(Database::connect,query2.str().c_str())){
           result = mysql_store_result(Database::connect);
           MYSQL_ROW row;
           while((row=mysql_fetch_row(result))!=NULL){
               yr = row[0];
               month = row[1];
           }
           mysql_free_result(result);
        }
        else{
            cout<<"Failed to access Database correctly."<<mysql_error(Database::connect)<<endl;
        }
        if(!in_organ_year(yr)){
            cout<<"No Record exist of year "<<yr<<" in our Database."<<endl;
            Sleep(2000);
            return;
        }
        month = return_month(atoi(month.c_str()));
        query3<<"SELECT SUM("<<month<<") FROM _"<<yr;
        if(!mysql_query(Database::connect,query3.str().c_str())){
            result = mysql_store_result(Database::connect);
            if(mysql_num_rows(result)){
                MYSQL_ROW row;
                while((row=mysql_fetch_row(result))!=NULL)
                    cout<<"\n\nTotal Donation of month "<<month<<" of "<<yr<<" is  Rs. "<<row[0]<<endl;
            }
            else{
                cout<<"\nFailed to calculate  monthly total."<<endl;
            }
            mysql_free_result(result);
        }
        else{
            cout<<"Failed to access Database correctly."<<mysql_error(Database::connect)<<endl;
        }
    }
}


void Donation::get_donation_yearly(void){
    string yr;
    stringstream query1,query2;
    MYSQL_RES *result;
    int valid = 0,choice;
    while(!valid){
        system("cls");
        cout<<"1) Get Total of Specific Year."<<endl;
        cout<<"2) Get Total of Current Year."<<endl;
        cout<<"\nEnter your choice : "<<endl;
        cin>>choice;
        if(cin.fail()){
            cout<<"Select a valid choice."<<endl;
            cin.clear();
            cin.ignore(256,'\n');
            Sleep(2000);
            continue;
        }
        else if(choice<1 || choice>2){
            cout<<"Enter a valid choice."<<endl;
            cin.ignore(256,'\n');
            Sleep(2000);
            continue;
        }
        valid = 1;
    }
    valid = 0;
    cin.ignore(256,'\n');
    if(choice == 1){
    while(!valid){
            cout<<"Enter the year(XXXX) : "<<endl;
            getline(cin,yr);
            if(cin.fail()){
                cout<<"Enter a valid year(XXXX) : "<<endl;
                cin.clear();
                cin.ignore(256,'\n');
                Sleep(2000);
                system("cls");
                cout<<"1) Get Total of Specific Year."<<endl;
                cout<<"2) Get Total of Current Year."<<endl;
                cout<<"\nEnter your choice : "<<endl;
                cout<<choice<<endl;
                continue;
            }
            if(!t.is_valid_year(yr)){
                cout<<"Enter a valid year(1900-2200).Only digits(0-9) are allowed."<<endl;
                Sleep(2000);
                system("cls");
                cout<<"1) Get Total of Specific Year."<<endl;
                cout<<"2) Get Total of Current Year."<<endl;
                cout<<"\nEnter your choice : "<<endl;
                cout<<choice<<endl;
                continue;
            }
            valid = 1;
        }

    if(!in_organ_year(yr)){
        cout<<"\nNo Record exist of year "<<yr<<" in our Database."<<endl;
        Sleep(2000);
        return;
    }
    query1<<"SELECT SUM(TOTAL) FROM _"<<yr;
    }
    else{
        query2<<"SELECT YEAR(CURDATE())";
        if(!mysql_query(Database::connect,query2.str().c_str())){
               result = mysql_store_result(Database::connect);
               MYSQL_ROW row;
               while((row=mysql_fetch_row(result))!=NULL)
                   yr = row[0];
               mysql_free_result(result);
        }
        if(!in_organ_year(yr)){
            cout<<"\nNo Record exist of year "<<yr<<" in our Database."<<endl;
            Sleep(2000);
            return;
        }
        query1<<"SELECT SUM(TOTAL) FROM _"<<yr;
    }
    if(!mysql_query(Database::connect,query1.str().c_str())){
        result = mysql_store_result(Database::connect);
        if(mysql_num_rows(result)){
            MYSQL_ROW row;
            while((row=mysql_fetch_row(result))!=NULL)
                cout<<"\n\nTotal Donation of Year "<<yr<<" is Rs. "<<row[0]<<endl;
        }
        else{
            cout<<"Failed to calculate yearly total."<<endl;
        }
        mysql_free_result(result);
    }
    else{
        cout<<"Failed to access Database correctly."<<mysql_error(Database::connect)<<endl;
    }
}


void Donation::get_total_donation_id(void){
    total = 0;
    stringstream query1,query2,query3;
    string id,q,temp,*years;
    char k[1500];
    MYSQL_RES* result;
    int valid = 0,is_present=0,n_of_y,i=0,j,field_ct;
    while(!valid){
        system("cls");
        cout<<"Enter Donor ID  : "<<endl;
        getline(cin,id);
        if(cin.fail()){
            cout<<"Enter a valid Donor ID."<<endl;
            cin.clear();
            cin.ignore(256,'\n');
            Sleep(2000);
            continue;
        }
        if(!t.is_valid_id(id)||id.length()==0){
            cout<<"Enter a valid Donor ID.Only Digits(0-9) are allowed."<<endl;
            Sleep(2000);
            continue;
        }
        valid = 1;
        ID = atoi(id.c_str());
    }
    query1<<"SELECT * FROM DonorsInfo WHERE ID = "<<id;
    if(!mysql_query(Database::connect,query1.str().c_str())){
        result = mysql_store_result(Database::connect);
        if(mysql_num_rows(result))
            is_present=1;
        else{
            cout<<"\nNo record exits with ID : "<<id<<" in our Database."<<endl;
            Sleep(2000);
        }
        mysql_free_result(result);
    }
    else{
        cout<<"Failed to access Database correctly."<<mysql_error(Database::connect)<<endl;
        return;
    }
    if(!is_present)
        return;
    query2<<"SELECT * FROM OrganYears";
    if(!mysql_query(Database::connect,query2.str().c_str())){
        result = mysql_store_result(Database::connect);
        if((n_of_y=mysql_num_rows(result))>0){
            years = new string[n_of_y];
            MYSQL_ROW row;
            while((row=mysql_fetch_row(result))!=NULL){
                years[i]=row[0];
                i++;
            }
        }
        else{
            cout<<"\nOrganization Years table is empty."<<endl;
        }
        mysql_free_result(result);
    }
    else{
        cout<<"Failed to access Database correctly."<<mysql_error(Database::connect)<<endl;
        return;
    }
    //temp ="SELECT " ;
    for(i=0;i<n_of_y-1;i++){
        q.clear();
        if(i==0)
            q = "SELECT TOTAL FROM _"+years[i]+" WHERE ID = "+id + " UNION ALL ";
        else
            q = temp+ "SELECT TOTAL FROM _"+years[i]+" WHERE ID = "+id + " UNION ALL ";
        temp = q;
    }
    temp += "SELECT TOTAL FROM _"+years[i]+" WHERE ID = "+id;
    q.clear();
    q = temp;
    for(i=0, j=0;i<q.length();i++){                 //patch for query
        if((q[i]>='a'&&q[i]<='z')||(q[i]>='A'&&q[i]<='Z')||(q[i]>='0'&&q[i]<='9')||q[i]==','||q[i]=='='||q[i]==' '||q[i]=='_'||q[i]=='.'){
            k[j++]=q[i];
        }
    }
    k[j]= '\0';
    query3<<k;
    if(!mysql_query(Database::connect,query3.str().c_str())){
        result = mysql_store_result(Database::connect);
        if(mysql_num_rows(result)){
            MYSQL_ROW row;
            while((row=mysql_fetch_row(result))!=NULL){
                //j=0;
                //while(j<(field_ct=mysql_num_fields(result)))
                    total += atof((const char*)row[0]);
            }
        }
        mysql_free_result(result);
    }
    else{
        cout<<"Failed to access Database correctly."<<mysql_error(Database::connect)<<endl;
        return;
    }
    cout<<"Total Donation by Donor with ID = "<<id<<" is Rs. "<<total<<endl;
}


void Donation::display_total_record_id(void){
    int valid = 0,is_present = 0,n_of_y,i,j=0,get = 0,*present_year;
    stringstream query1,query2,query3,extra;
    string id,*years,q,temp;
    char k[1500];
    MYSQL_RES *result;
    while(!valid){
        system("cls");
        cout<<"\t\t\tGet Donor Full Donation Record Here."<<endl;
        cout<<"Enter Donor ID : "<<endl;
        getline(cin,id);
        if(cin.fail()){
            cout<<"Enter a valid Donor ID."<<endl;
            cin.clear();
            cin.ignore(256,'\n');
            Sleep(2000);
            continue;
        }
        if(!t.is_valid_id(id)||id.length()==0){
            cout<<"Enter a valid Donor ID.Only digits(0-9) are allowed."<<endl;
            Sleep(2000);
            continue;
        }
        valid = 1;
        ID = atoi(id.c_str());
    }
    query1<<"SELECT * FROM DonorsInfo WHERE ID = "<<id;
    cout<<"Searching";

    for(int k=0;k<2;k++){
        Sleep(400);
        cout<<".";
        Sleep(400);
        cout<<".";
        Sleep(400);
        cout<<".";
        Sleep(400);
        cout<<"\b\b\b   \b\b\b";
    }
    if(!mysql_query(Database::connect,query1.str().c_str())){
        result = mysql_store_result(Database::connect);
        if(mysql_num_rows(result))
            is_present = 1;
        else{
            cout<<"\nNo record Present for ID : "<<id<<" in our Database."<<endl;
            Sleep(2000);
        }
        mysql_free_result(result);
    }
    else{
        cout<<"Failed to access Database correctly."<<mysql_error(Database::connect)<<endl;
        return;
    }
    if(!is_present)
        return;

    query2<<"SELECT * FROM OrganYears";
    if(!mysql_query(Database::connect,query2.str().c_str())){
        result = mysql_store_result(Database::connect);
        if((n_of_y=mysql_num_rows(result))>0){
            years = new string[n_of_y];
            present_year = new int[n_of_y];
            MYSQL_ROW row;
            i=0;
            while((row=mysql_fetch_row(result))!=NULL){
                years[i]=row[0];
                present_year[i]=0;
                i++;
            }
        }
        else{
            cout<<"\nOrganization Years table is empty."<<endl;
        }
        mysql_free_result(result);
    }
    else{
        cout<<"Failed to access Database correctly."<<mysql_error(Database::connect)<<endl;
        return;
    }
    for(i=0;i<n_of_y-1;i++){
        extra<<"SELECT * FROM _"<<years[i]<<" WHERE ID = "<<id;
        if(!mysql_query(Database::connect,extra.str().c_str())){
            result = mysql_store_result(Database::connect);
            if(mysql_num_rows(result)==1)
                present_year[i] = 1;
        }
        mysql_free_result(result);
        extra.str("");
        q.clear();
        if(i==0)
            q = "SELECT JAN,FEB,MAR,APR,MAY,JUN,JUL,AUG,SEP,OCT,NOV,DECM,TOTAL FROM _"+years[i]+" WHERE ID = "+id + " UNION ALL ";
        else
            q = temp + "SELECT JAN,FEB,MAR,APR,MAY,JUN,JUL,AUG,SEP,OCT,NOV,DECM,TOTAL FROM _"+years[i]+" WHERE ID = "+id + " UNION ALL ";
        temp = q;
    }
    extra<<"SELECT * FROM _"<<years[i]<<" WHERE ID = "<<id;
    if(!mysql_query(Database::connect,extra.str().c_str())){
        result = mysql_store_result(Database::connect);
        if(mysql_num_rows(result)==1)
            present_year[i] = 1;
    }
    mysql_free_result(result);
    extra.str("");
    temp += "SELECT JAN,FEB,MAR,APR,MAY,JUN,JUL,AUG,SEP,OCT,NOV,DECM,TOTAL FROM _"+years[i]+" WHERE ID = "+id;
    q.clear();
    q = temp;
    for(i=0, j=0;i<q.length();i++){                 //patch for query
        if((q[i]>='a'&&q[i]<='z')||(q[i]>='A'&&q[i]<='Z')||(q[i]>='0'&&q[i]<='9')||q[i]==','||q[i]=='='||q[i]==' '||q[i]=='_'||q[i]=='.'){
            k[j++]=q[i];
        }
    }
    k[j]= '\0';
    query3<<k;
    cout<<endl;
    if(!mysql_query(Database::connect,query3.str().c_str())){
        result = mysql_store_result(Database::connect);
        if(mysql_num_rows(result)>0){
            MYSQL_ROW row;
            get = 1;
            j=0;
            i=0;
            cout<<"\n\t\t\t\tFull record for ID : "<<id<<endl<<endl;
            while((row=mysql_fetch_row(result))!=NULL){
                TextTable t( '-', '|', '+' );
                for(i=j;i<n_of_y;i++){
                    if(present_year[i]==1){
                        cout<<"\t\t\t\t          "<<years[i]<<endl<<endl;
                        j = ++i;
                        break;
                    }
                }
                t.add("JANUARY");
                t.add("FEBUARY");
                t.add("MARCH");
                t.add("APRIL");
                t.add("MAY");
                t.add("JUNE");
                t.add("JULY");
                t.add("AUGUST");
                t.add("SEPTEMBER");
                t.add("OCTOBER");
                t.add("NOVEMBER");
                t.add("DECEMBER");
                t.add("TOTAL");
                t.endOfRow();
                /*cout<<"Jan : ";*/if(strcmp(row[0],"0")){t.add(row[0]);}else{t.add("nil");}
                /*cout<<"Feb : ";*/if(strcmp(row[1],"0")){t.add(row[1]);}else{t.add("nil");}
                /*cout<<"Mar : ";*/if(strcmp(row[2],"0")){t.add(row[2]);}else{t.add("nil");};
                /*cout<<"Apr : ";*/if(strcmp(row[3],"0")){t.add(row[3]);}else{t.add("nil");}
                /*cout<<"May : ";*/if(strcmp(row[4],"0")){t.add(row[4]);}else{t.add("nil");}
                /*cout<<"June : ";*/if(strcmp(row[5],"0")){t.add(row[5]);}else{t.add("nil");}
                /*cout<<"July : ";*/if(strcmp(row[6],"0")){t.add(row[6]);}else{t.add("nil");}
                /*cout<<"Aug : ";*/if(strcmp(row[7],"0")){t.add(row[7]);}else{t.add("nil");}
                /*cout<<"Sep : ";*/if(strcmp(row[8],"0")){t.add(row[8]);}else{t.add("nil");}
                /*cout<<"Oct : ";*/if(strcmp(row[9],"0")){t.add(row[9]);}else{t.add("nil");}
                /*cout<<"Nov : ";*/if(strcmp(row[10],"0")){t.add(row[10]);}else{t.add("nil");}
                /*cout<<"Dec : ";*/if(strcmp(row[11],"0")){t.add(row[11]);}else{t.add("nil");}
                /*cout<<"Total : ";*/if(strcmp(row[12],"0")){t.add(row[12]);}else{t.add("nil");}
                t.endOfRow();
                t.setAlignment( 2, TextTable::Alignment::LEFT );
                cout<<t;
                cout<<endl<<endl;
            }
        }
        else{
            cout<<"\nNo record exists for ID : "<<id<<" in our Database."<<endl;
            Sleep(2000);
        }
        mysql_free_result(result);
    }
    else{
        cout<<"Failed to access Database correctly."<<mysql_error(Database::connect)<<endl;
        return;
    }
    if(!get)
        return;

}


void Donation::modify_donation(void){
    int valid = 0,is_present = 0,n_of_y,i,updated = 0,is_modify = 0,years_present = 0,get= 0,done = 0,n_of_r;
    stringstream query1,query2,query3,query4,query5,query6;
    string id,*years,y,choice,a,am[12],m[12]={"JAN","FEB","MAR","APR","MAY","JUN","JUL","AUG","SEP","OCT","NOV","DECM"};
    char ch;
    MYSQL_RES* result;
    while(!valid){
        system("cls");
        cout<<"Enter Donor ID to modify record : "<<endl;
        getline(cin,id);
        if(cin.fail()){
            cout<<"Enter a valid Donor ID."<<endl;
            cin.clear();
            cin.ignore(256,'\n');
            Sleep(2000);
            continue;
        }
        if(!t.is_valid_id(id)||id.length()==0){
            cout<<"Enter a valid Donor ID.Only Digits(0-9) are allowed."<<endl;
            Sleep(2000);
            continue;
        }
        valid = 1;
        ID = atoi(id.c_str());
    }
    valid = 0;
    query1<<"SELECT * FROM DonorsInfo WHERE ID = "<<id;
    if(!mysql_query(Database::connect,query1.str().c_str())){
        result = mysql_store_result(Database::connect);
        if(mysql_num_rows(result))
            is_present=1;
        else{
            cout<<"\nNo record exits with ID : "<<id<<" in our Database."<<endl;
            Sleep(2000);
        }
    }
    else{
        cout<<"Failed to access Database correctly."<<mysql_error(Database::connect)<<endl;
        return;
    }
    if(!is_present){
        return;
    }
    query2<<"SELECT * FROM OrganYears";
    if(!mysql_query(Database::connect,query2.str().c_str())){
        result = mysql_store_result(Database::connect);
        if((n_of_y=mysql_num_rows(result))>0){
            MYSQL_ROW row;
            i = 0;
            years_present = 1;
            years = new string [n_of_y];
            while((row= mysql_fetch_row(result))!=NULL)
                years[i++]=row[0];
        }
        else{
            cout<<"\nOrganization years table is empty.Fill it first."<<endl;
            Sleep(2000);
        }
        mysql_free_result(result);
    }
    else{
        cout<<"Failed to access Database correctly."<<mysql_error(Database::connect)<<endl;
        return;
    }
    if(!years_present){
        return;
    }
    for(i=0;i<n_of_y;i++){
        cout<<i+1<<") "<<years[i]<<endl;
    }
    cout<<"Select the year to modify : "<<endl;
    while(!valid){
        getline(cin,choice);
        if(cin.fail()){
            cout<<"Enter a valid choice."<<endl;
            cin.clear();
            cin.ignore(256,'\n');
            Sleep(2000);
            cout<<"Select the year to modify correctly : "<<endl;
            continue;
        }
        if(!t.is_valid_id(choice)){
            cout<<"Enter a valid choice.Enter a digit only."<<endl;
            Sleep(2000);
            cout<<"Select the year to modify correctly : "<<endl;
            continue;
        }
        else if(atoi(choice.c_str())<1 || atoi(choice.c_str())>n_of_y){
            cout<<"Select from the given choices."<<endl;
            Sleep(2000);
            cout<<"Select the year to modify correctly : "<<endl;
            continue;
        }
        valid = 1;
        y = years[atoi(choice.c_str())-1];
    }
    query3<<"SELECT JAN,FEB,MAR,APR,MAY,JUN,JUL,AUG,SEP,OCT,NOV,DECM,TOTAL FROM _"<<y<<" WHERE ID = "<<id;
    if(!mysql_query(Database::connect,query3.str().c_str())){
        result = mysql_store_result(Database::connect);
        if(mysql_num_rows(result)>0){
            MYSQL_ROW row;
            get = 1;
            cout<<"\n\t\t\t\tDonor Record in "<<y<<endl<<endl;
            TextTable t( '-', '|', '+' );
            t.add("JANUARY");
            t.add("FEBUARY");
            t.add("MARCH");
            t.add("APRIL");
            t.add("MAY");
            t.add("JUNE");
            t.add("JULY");
            t.add("AUGUST");
            t.add("SEPTEMBER");
            t.add("OCTOBER");
            t.add("NOVEMBER");
            t.add("DECEMBER");
            t.add("TOTAL");
            t.endOfRow();
            while((row=mysql_fetch_row(result))!=NULL){
                /*cout<<"Jan : ";*/if(strcmp(row[0],"0")){t.add(row[0]);}else{t.add("nil");}
                /*cout<<"Feb : ";*/if(strcmp(row[1],"0")){t.add(row[1]);}else{t.add("nil");}
                /*cout<<"Mar : ";*/if(strcmp(row[2],"0")){t.add(row[2]);}else{t.add("nil");};
                /*cout<<"Apr : ";*/if(strcmp(row[3],"0")){t.add(row[3]);}else{t.add("nil");}
                /*cout<<"May : ";*/if(strcmp(row[4],"0")){t.add(row[4]);}else{t.add("nil");}
                /*cout<<"June : ";*/if(strcmp(row[5],"0")){t.add(row[5]);}else{t.add("nil");}
                /*cout<<"July : ";*/if(strcmp(row[6],"0")){t.add(row[6]);}else{t.add("nil");}
                /*cout<<"Aug : ";*/if(strcmp(row[7],"0")){t.add(row[7]);}else{t.add("nil");}
                /*cout<<"Sep : ";*/if(strcmp(row[8],"0")){t.add(row[8]);}else{t.add("nil");}
                /*cout<<"Oct : ";*/if(strcmp(row[9],"0")){t.add(row[9]);}else{t.add("nil");}
                /*cout<<"Nov : ";*/if(strcmp(row[10],"0")){t.add(row[10]);}else{t.add("nil");}
                /*cout<<"Dec : ";*/if(strcmp(row[11],"0")){t.add(row[11]);}else{t.add("nil");}
                /*cout<<"Total : ";*/if(strcmp(row[12],"0")){t.add(row[12]);}else{t.add("nil");}
                t.endOfRow();
            }
            t.setAlignment( 2, TextTable::Alignment::LEFT );
            cout<<t;
        }
        else{
            cout<<"\nNo record exists in "<<y<<" for ID : "<<id<<" in our Database."<<endl;
            Sleep(2000);
        }
        mysql_free_result(result);
    }
    else{
        cout<<"Failed to access Database correctly."<<mysql_error(Database::connect)<<endl;
        return;
    }
    if(!get){
        return;
    }
    i=0;
    while(i<12){
        valid = 0;
        cout<<"\nWant to modify for "<<m[i]<<" ? (y/n) :";
        ch = getche();
        if(ch == 'y'||ch == 'Y'){
            while(!valid){
                cout<<"\nEnter new Donation amount : "<<endl;
                getline(cin,a);
                if(cin.fail()){
                    cout<<"Enter a valid donation amount."<<endl;
                    cin.clear();
                    cin.ignore(256,'\n');
                    Sleep(2000);
                    continue;
                }
                else if(!t.is_valid_amount(a)){
                    cout<<"Enter a valid amount.Only digits(0-9) and decimal points are allowed."<<endl;
                    Sleep(2000);
                    continue;
                }
                valid = 1;
                amount = atof(a.c_str());
            }
            am[i]="'"+a+"'";
            i++;
            is_modify = 1;
        }
        else{
            am[i]=m[i];
            i++;
        }
    }
    if(!is_modify){
        cout<<"\n\nNo record is updated on your request."<<endl;
        Sleep(2000);
        return;
    }
    query4<<"UPDATE _"<<y<<" SET JAN = "<<am[0]<<" ,FEB = "<<am[1]<<" , MAR = "<<am[2]
          <<" ,APR = "<<am[3]<<" , MAY = "<<am[4]<<" ,JUN = "<<am[5]<<" , JUL = "<<am[6]
          <<" ,AUG = "<<am[7]<<" , SEP = "<<am[8]<<" ,OCT = "<<am[9]<<" , NOV = "<<am[10]
          <<" ,DECM = "<<am[11]<<" WHERE ID = "<<id;
    if(!mysql_query(Database::connect,query4.str().c_str())){
        if(mysql_affected_rows(Database::connect))
            updated = 1;
        else{
            cout<<"Failed to update the above record due to unknown error."<<endl;
            Sleep(2000);
        }
    }
    else{
        cout<<"Failed to access Database correctly."<<mysql_error(Database::connect)<<endl;
        return;
    }
    if(!updated){
        return;
    }
    query5<<"UPDATE _"<<y<<" SET TOTAL =JAN+FEB+MAR+APR+MAY+JUN+JUL+AUG+SEP+OCT+NOV+DECM WHERE ID = "<<ID;
    if(!mysql_query(Database::connect,query5.str().c_str())){
        if(mysql_affected_rows(Database::connect)){
            cout<<"\n\nRecord modification is successful."<<endl;
            done = 1;
        }
        else{
            cout<<"\nRecord modification is unsuccessful."<<endl;
            Sleep(2000);
        }
    }
    else{
        cout<<"Failed to access Database correctly."<<mysql_error(Database::connect)<<endl;
        return;
    }
    if(!done)
        return;
    query6<<"SELECT * FROM _"<<y<<" WHERE ID = "<<ID;
    if(!mysql_query(Database::connect,query6.str().c_str())){
        result = mysql_store_result(Database::connect);
        if((n_of_r=mysql_num_rows(result))> 0){
            MYSQL_ROW row;
            cout<<"\n\t\t\t\tUpdated Donation Record In "<<y<<" of ID "<<ID<<endl<<endl;
            TextTable t( '-', '|', '+' );
            t.add("JANUARY");
            t.add("FEBUARY");
            t.add("MARCH");
            t.add("APRIL");
            t.add("MAY");
            t.add("JUNE");
            t.add("JULY");
            t.add("AUGUST");
            t.add("SEPTEMBER");
            t.add("OCTOBER");
            t.add("NOVEMBER");
            t.add("DECEMBER");
            t.add("TOTAL");
            t.endOfRow();
            while((row=mysql_fetch_row(result))!=NULL){
                /*cout<<"Jan : ";*/if(strcmp(row[1],"0")){t.add(row[1]);}else{t.add("nil");}
                /*cout<<"Feb : ";*/if(strcmp(row[2],"0")){t.add(row[2]);}else{t.add("nil");}
                /*cout<<"Mar : ";*/if(strcmp(row[3],"0")){t.add(row[3]);}else{t.add("nil");};
                /*cout<<"Apr : ";*/if(strcmp(row[4],"0")){t.add(row[4]);}else{t.add("nil");}
                /*cout<<"May : ";*/if(strcmp(row[5],"0")){t.add(row[5]);}else{t.add("nil");}
                /*cout<<"June : ";*/if(strcmp(row[6],"0")){t.add(row[6]);}else{t.add("nil");}
                /*cout<<"July : ";*/if(strcmp(row[7],"0")){t.add(row[7]);}else{t.add("nil");}
                /*cout<<"Aug : ";*/if(strcmp(row[8],"0")){t.add(row[8]);}else{t.add("nil");}
                /*cout<<"Sep : ";*/if(strcmp(row[9],"0")){t.add(row[9]);}else{t.add("nil");}
                /*cout<<"Oct : ";*/if(strcmp(row[10],"0")){t.add(row[10]);}else{t.add("nil");}
                /*cout<<"Nov : ";*/if(strcmp(row[11],"0")){t.add(row[11]);}else{t.add("nil");}
                /*cout<<"Dec : ";*/if(strcmp(row[12],"0")){t.add(row[12]);}else{t.add("nil");}
                /*cout<<"Total : ";*/if(strcmp(row[13],"0")){t.add(row[13]);}else{t.add("nil");}
                t.endOfRow();
            }
            t.setAlignment( 2, TextTable::Alignment::LEFT );
            cout<<t;
        }
        else{
            cout<<"\nNo record exist for ID : "<<ID<<" in "<<year<<endl;
            Sleep(2000);
        }
        mysql_free_result(result);
    }
    else{
        cout<<"Failed to access Database correctly."<<mysql_error(Database::connect)<<endl;
    }

}


Targets::Targets(){
    target_id = 0;
    target_descryption=" ";
    expected_amount = 0;
    spend_amount = 0;
    status = " ";
}


void Targets::add_target(void){
    int valid = 0;
    char ch1,ch2;
    string d,a,sa;
    stringstream query;
    while(!valid){
        system("cls");
        cout<<"Enter a Target Description : "<<endl;
        getline(cin,d);
        if(cin.fail()){
            cout<<"Enter a valid Target Description."<<endl;
            cin.clear();
            cin.ignore(256,'\n');
            Sleep(2000);
            system("cls");
            cout<<"Enter a Target Description : "<<endl;
            continue;
        }
        else if (d.length()<10){
            cout<<"Enter a Target Description of minimum 10 letters."<<endl;
            Sleep(2000);
            system("cls");
            cout<<"Enter a Target Description : "<<endl;
            continue;
        }
        valid = 1;
        target_descryption = d;
    }
    valid = 0;
    cout<<"Want to add the expected amount for target? (y/n) : ";
    ch1 = getche();
    cout<<endl;
    if(ch1=='y'||ch1=='Y'){
        while(!valid){
            cout<<"Enter the expected amount."<<endl;
            getline(cin,a);
            if(cin.fail()){
                cout<<"Enter a valid amount."<<endl;
                cin.clear();
                cin.ignore(256,'\n');
                Sleep(2000);
                system("cls");
                cout<<"Enter a Target Description : "<<endl;
                cout<<d<<endl;
                cout<<"Want to add the expected amount for target? (y/n) : ";
                cout<<ch1<<endl;
                continue;
            }
            else if(!t.is_valid_amount(a)||a.length()==0){
                cout<<"Enter a valid a amount.Only(digits) and decimal point is allowed."<<endl;
                Sleep(2000);
                system("cls");
                cout<<"Enter a Target Description : "<<endl;
                cout<<d<<endl;
                cout<<"Want to add the expected amount for target? (y/n) : ";
                cout<<ch1<<endl;
                continue;
            }
            valid = 1;
            expected_amount = atof(a.c_str());
        }
    }
    else{
        a = "Not-specified";
    }
    valid = 0;
    cout<<"\nWant to add the spend amount for target, Press y only if Target is achieved? (y/n) : ";
    ch2 = getche();
    cout<<endl;
    if(ch2=='y'||ch2=='Y'){
        while(!valid){
            cout<<"Enter the amount spend."<<endl;
            getline(cin,sa);
            if(cin.fail()){
                cout<<"Enter a valid amount."<<endl;
                cin.clear();
                cin.ignore(256,'\n');
                Sleep(2000);
                system("cls");
                cout<<"Enter a Target Description : "<<endl;
                cout<<d<<endl;
                cout<<"Want to add the expected amount for target? (y/n) : ";
                cout<<ch1<<endl;
                if(ch1=='y'||ch1=='Y'){
                    cout<<"Enter the expected amount."<<endl;
                    cout<<a<<endl;
                }
                cout<<"\nWant to add the spend amount for target, Press y only if Target is achieved? (y/n) : ";
                cout<<ch2<<endl;
                continue;
            }
            else if(!t.is_valid_amount(sa)||sa.length()==0){
                cout<<"Enter a valid a amount.Only(digits) and decimal point is allowed."<<endl;
                Sleep(2000);
                system("cls");
                cout<<"Enter a Target Description : "<<endl;
                cout<<d<<endl;
                cout<<"Want to add the expected amount for target? (y/n) : ";
                cout<<ch1<<endl;
                if(ch1=='y'||ch1=='Y'){
                    cout<<"Enter the expected amount."<<endl;
                    cout<<a<<endl;
                }
                cout<<"\nWant to add the spend amount for target, Press y only if Target is achieved? (y/n) : ";
                cout<<ch2<<endl;
                continue;
            }
            valid = 1;
            spend_amount = atof(sa.c_str());
        }

    }
    else{
        sa = "UNKNOWN";
    }
    valid = 0;
    cout<<endl;
    while(!valid){
        int choice;
        cout<<"Enter Target Status {1:Achieved,2:Unachieved,3:Unknown} : "<<endl;
        cin>>choice;
        if(cin.fail()){
            cout<<"Enter a valid choice."<<endl;
            cin.clear();
            cin.ignore(256,'\n');
            Sleep(2000);
            system("cls");
            cout<<"Enter a Target Description : "<<endl;
            cout<<d<<endl;
            cout<<"Want to add the expected amount for target? (y/n) : ";
            cout<<ch1<<endl;
            if(ch1=='y'||ch1=='Y'){
                cout<<"Enter the expected amount."<<endl;
                cout<<a<<endl;
            }
            cout<<"\nWant to add the spend amount for target, Press y only if Target is achieved? (y/n) : ";
            cout<<ch2<<endl;
            if(ch2=='y'||ch2=='Y'){
                cout<<"Enter the amount spend."<<endl;
                cout<<sa<<endl;
            }
            continue;
        }
        if(!(choice >= 1 && choice <=3)){
            cout<<"Select given choice."<<endl;
            Sleep(2000);
            system("cls");
            cout<<"Enter a Target Description : "<<endl;
            cout<<d<<endl;
            cout<<"Enter the expected amount."<<endl;
            cout<<a<<endl;
            cout<<"Enter the amount spend."<<endl;
            cout<<sa<<endl;
            continue;
        }
        if(choice == 1)
            status = "Achieved";
        else if(choice == 2)
            status = "Unachieved";
        else
            status = "Unknown";
        valid = 1;
    }
    query<<"INSERT INTO Targets(DESCRYPTION,ExpectedAmount,SpendAmount,STATUS) VALUES('"
         <<target_descryption<<"', '"<<a<<"','"<<sa<<"','"<<status<<"')";
    if(!mysql_query(Database::connect,query.str().c_str())){
           if(mysql_affected_rows(Database::connect)){
               cout<<"Target Added."<<endl;
               Sleep(2000);
           }
           else{
            cout<<"\nTarget Addition Process Failed."<<endl;
            Sleep(2000);
           }
    }
    else{
        cout<<"Failed to access Database correctly."<<mysql_error(Database::connect)<<endl;
        return;
    }

}


int  Targets::search_target(void){
    string id;
    int valid = 0,is_present= 0;
    MYSQL_RES *result;
    stringstream query;
    while(!valid){
        system("cls");
        cout<<"Enter Target's ID : "<<endl;
        getline(cin,id);
        if(cin.fail()){
            cout<<"Enter a valid ID : "<<endl;
            cin.clear();
            cin.ignore(256,'\n');
            Sleep(2000);
            continue;
        }
        if(!t.is_valid_id(id)||id.length()==0){
            cout<<"Enter a valid ID.Only digits(0-9) are allowed."<<endl;
            Sleep(2000);
            continue;
        }
        target_id = atoi(id.c_str());
        valid = 1;
    }
    query<<"SELECT * FROM Targets WHERE ID = "<<id;
    cout<<"Searching";

    for(int i=0;i<2;i++){
        Sleep(400);
        cout<<".";
        Sleep(400);
        cout<<".";
        Sleep(400);
        cout<<".";
        Sleep(400);
        cout<<"\b\b\b   \b\b\b";
    }
    if(!mysql_query(Database::connect,query.str().c_str())){
        result = mysql_store_result(Database::connect);
        if(mysql_num_rows(result)){
            MYSQL_ROW row;
            cout<<"\t\t      Target Found."<<endl<<endl;
            TextTable t( '-', '|', '+' );
            t.add("Description");
            t.add("Expected Amount(Rs.)");
            t.add("Spend Amount(Rs.)");
            t.add("Target Status");
            t.endOfRow();
            while((row=mysql_fetch_row(result))!=NULL){
                /*cout<<"Description : ";*/if(row[1]){t.add(row[1]);}else{t.add("Nil");}
                /*cout<<"Expected Amount Rs : ";*/if(row[2]){t.add(row[2]);}else{t.add("Nil");}
                /*cout<<"Spend Amount Rs : ";*/if(row[3]){t.add(row[3]);}else{t.add("Nil");}
                /*cout<<"Target Status : ";*/if(row[4]){t.add(row[4]);}else{t.add("Nil");}
                t.endOfRow();
            }
            t.setAlignment( 2, TextTable::Alignment::LEFT );
            cout<<t;
            is_present = 1;
        }
        else{
            cout<<"\nNo Target is associated with ID : "<<id<<endl;
            Sleep(2000);
        }
        mysql_free_result(result);
    }
    else{
        cout<<"Failed to access Database correctly."<<mysql_error(Database::connect)<<endl;
        return -1;
    }
    if(is_present)
        return target_id;
    else
        return 0;
}


void Targets::delete_target(void){
    int target_id,valid = 0;
    string choice;
    stringstream query;
    target_id = search_target();
    if(target_id==0)
        return;
    cout<<endl<<endl;
    while(!valid){
        cout<<"Want to Delete this target? Enter(y/n) : "<<endl;
        getline(cin,choice);
        if(cin.fail()){
            cout<<"Enter a valid choice."<<endl;
            cin.clear();
            cin.ignore(256,'\n');
            Sleep(2000);
            continue;
        }
        else if(!t.is_valid_choice(choice)){
            cout<<"\nEnter (y/n)."<<endl;
            Sleep(2000);
            continue;
        }
        valid = 1;
    }
    if(choice[0]=='y'||choice[0] =='Y')
        query<<"DELETE FROM Targets WHERE ID = "<<target_id;
    else{
        cout<<"Target is not deleted as per your command."<<endl;
        Sleep(2000);
        return;
    }
    if(!mysql_query(Database::connect,query.str().c_str())){
        if(mysql_affected_rows(Database::connect)){
            cout<<"Target is Deleted."<<endl;
            Sleep(2000);
        }
        else{
            cout<<"Target Deletion Process Failed."<<endl;
            Sleep(2000);
        }
    }
    else{
        cout<<"Failed to access Database correctly."<<mysql_error(Database::connect)<<endl;
    }
}


void Targets::modify_target(void){
    int count = 0,valid = 0,is_modify = 0;
    char ch;
    string d,a,sa,sta,temp;
    stringstream query;
    target_id = search_target();
    if(target_id==0)
        return;
    cout<<endl<<endl;
    cout<<"Want to modify Targets Description ? (y/n) : "<<endl;
    ch=getche();
    cout<<endl;
    if(ch=='y'||ch=='Y'){
        while(!valid){
            count++;
            if(count==1)
                cout<<"Enter Target's new Description : "<<endl;
            else
                cout<<"Enter Target's new Description correctly : "<<endl;
            getline(cin,d);
            if(cin.fail()){
                cout<<"Enter a valid Target Description."<<endl;
                cin.clear();
                cin.ignore(256,'\n');
                Sleep(2000);
                continue;
            }
            else if(d.length()<10){
                cout<<"Enter a Target Description of minimum 10 characters."<<endl;
                Sleep(2000);
                continue;
            }
            valid = 1;
            temp = d;
            d = "'"+temp+"'";
            is_modify=1;
        }
    }
    else{
        d = "DESCRYPTION";
    }
    valid = 0;
    count = 0;
    cout<<"Want to change the expected amount ? (y/n) :"<<endl;
    ch = getche();
    cout<<endl;
    if(ch=='y'||ch=='Y'){
        while(!valid){
            count++;
            if(count==1)
                cout<<"Enter new expected amount : "<<endl;
            else
                cout<<"Enter new expected amount correctly: "<<endl;
            getline(cin,a);
            if(cin.fail()){
                cout<<"Enter a valid amount."<<endl;
                cin.clear();
                cin.ignore(256,'\n');
                Sleep(2000);
                continue;
            }
            else if(!t.is_valid_amount(a)||a.length()==0){
                cout<<"Enter a valid a amount.Only(digits) and decimal point is allowed."<<endl;
                Sleep(2000);
                continue;
            }
            valid = 1;
            expected_amount = atof(a.c_str());
            temp = a;
            a= "'"+temp+"'";
            is_modify =1;
        }
    }
    else{
        a = "ExpectedAmount";
    }
    valid = 0;
    count = 0;
    cout<<"Want to change the spend amount ? (y/n) :"<<endl;
    ch = getche();
    cout<<endl;
    if(ch=='y'||ch=='Y'){
        while(!valid){
            count++;
            if(count==1)
                cout<<"Enter new spend amount : "<<endl;
            else
                cout<<"Enter new spend amount correctly: "<<endl;
            getline(cin,sa);
            if(cin.fail()){
                cout<<"Enter a valid amount."<<endl;
                cin.clear();
                cin.ignore(256,'\n');
                Sleep(2000);
                continue;
            }
            else if(!t.is_valid_amount(sa)||sa.length()==0){
                cout<<"Enter a valid a amount.Only(digits) and decimal point is allowed."<<endl;
                Sleep(2000);
                continue;
            }
            valid = 1;
            spend_amount = atof(sa.c_str());
            temp = sa;
            sa= "'"+temp+"'";
            is_modify =1;
        }
    }
    else{
        sa = "SpendAmount";
    }
    valid = 0;
    count = 0;
    cout<<"Want to change Target's status ? (y/n) : "<<endl;
    ch = getche();
    cout<<endl;
    if(ch=='y'||ch=='Y'){
        while(!valid){
            count++;
            int choice;
            if(count == 1)
                cout<<"Enter new Target's Status {1:Achieved,2:Unachieved,3:Unknown} : "<<endl;
            else
                cout<<"Enter new Target's Status correctly {1:Achieved,2:Unachieved,3:Unknown} : "<<endl;
            cin>>choice;
            if(cin.fail()){
                cout<<"Enter a valid choice."<<endl;
                cin.clear();
                cin.ignore(256,'\n');
                Sleep(2000);
                continue;
            }
            if(!(choice >= 1 && choice <=3)){
                cout<<"Select given choice."<<endl;
                Sleep(2000);
                continue;
            }
            valid = 1;
            if(choice == 1)
                sta = "Achieved";
            else if(choice == 2)
                sta = "Unachieved";
            else
                sta = "Unknown";
            temp = sta;
            sta = "'"+temp+"'";
            is_modify = 1;
        }
    }
    else{
        sta = "STATUS";
    }
    if(!is_modify){
        cout<<"No modification are made as per your command."<<endl;
        Sleep(2000);
        return;
    }
    query<<"UPDATE Targets SET DESCRYPTION = "<<d<<", ExpectedAmount = "<<a<<", SpendAmount = "<<sa<<", STATUS = "<<sta
        <<" WHERE ID = "<<target_id;
    if(!mysql_query(Database::connect,query.str().c_str())){
        if(mysql_affected_rows(Database::connect)){
            cout<<"Target is Updated.Can be checked in Display Targets section."<<endl;
            Sleep(2000);
        }
        else{
            cout<<"\nFailed to update the target."<<endl;
            Sleep(2000);
        }
    }
    else{
        cout<<"Failed to access Database correctly."<<mysql_error(Database::connect)<<endl;
    }
}


void Targets::display_targets(void){
    system("cls");
    int n_of_r;
    stringstream query;
    MYSQL_RES *result;
    query<<"SELECT * FROM Targets";
    if(!mysql_query(Database::connect,query.str().c_str())){
        result = mysql_store_result(Database::connect);
        if((n_of_r = mysql_num_rows(result)>0)){
            MYSQL_ROW row;
            cout<<"\t\t\t\t    Targets"<<endl<<endl;
            TextTable t( '-', '|', '+' );
            t.add("Target ID");
            t.add("Description");
            t.add("Expected Amount(Rs.)");
            t.add("Spend Amount(Rs.)");
            t.add("Target Status");
            t.endOfRow();
            while((row=mysql_fetch_row(result))!= NULL){
                /*cout<<"Target ID : ";*/if(row[0]){t.add(row[0]);}else{t.add("Nil");}
                /*cout<<"Description : ";*/if(row[1]){t.add(row[1]);}else{t.add("Nil");}
                /*cout<<"Expected Amount Rs : ";*/if(row[2]){t.add(row[2]);}else{t.add("Nil");}
                /*cout<<"Spend Amount Rs : ";*/if(row[3]){t.add(row[3]);}else{t.add("Nil");}
                /*cout<<"Target Status : ";*/if(row[4]){t.add(row[4]);}else{t.add("Nil");}
                t.endOfRow();
            }
            t.setAlignment( 2, TextTable::Alignment::LEFT );
            cout<<t;
        }
        else{
            cout<<"Target List is Empty."<<endl;
            Sleep(2000);
        }
        mysql_free_result(result);
    }
    else{
        cout<<"Failed to access Database correctly."<<mysql_error(Database::connect)<<endl;
        return;
    }
    cout<<"\n\nPress Enter key to return..."<<endl;
    getch();
}


Accomplishment::Accomplishment(){
    s_no = 0;
    description = " ";
    sp_amount = 0;
    acc_date= " ";
}


void Accomplishment::add_accomplishment(void){
    int valid = 0,mm,dd,yy;
    char ch;
    stringstream query;
    string d,am;
    while(!valid){
        system("cls");
        cout<<"Enter Description of Accomplishment : "<<endl;
        getline(cin,d);
        if(cin.fail()){
            cout<<"Enter a valid Description."<<endl;
            cin.clear();
            cin.ignore(256,'\n');
            Sleep(2000);
            continue;
        }
        if(d.length()<10){
            cout<<"Enter a valid Description.The Description must contain at-least 10 characters."<<endl;
            Sleep(2000);
            continue;
        }
        valid = 1;
        description = d;
    }
    valid = 0;
    while(!valid){
        cout<<"Enter the Spend Amount : "<<endl;
        getline(cin,am);
        if(cin.fail()){
            cout<<"Enter a valid Amount."<<endl;
            cin.clear();
            cin.ignore(256,'\n');
            Sleep(2000);
            system("cls");
            cout<<"Enter Description of Accomplishment : "<<endl;
            cout<<d<<endl;
            continue;
        }
        if(!t.is_valid_amount(am)||am.length()==0){
            cout<<"Enter a valid Amount.Only digits(0-9) and decimal point is allowed."<<endl;
            Sleep(2000);
            system("cls");
            cout<<"Enter Description of Accomplishment : "<<endl;
            cout<<d<<endl;
            continue;
        }
        valid = 1;
        sp_amount = atof(am.c_str());
    }
    valid = 0;
    cout<<"Want to add Accomplishment Date ? (y/n) : "<<endl;
    ch  = getche();
    cout<<endl;
    if(ch=='y'||ch=='Y'){
        while(!valid){
           cout<<"Enter the Accomplishment Date(dd-mm-yy) :"<<endl;
           cin>>dd;
           cin.get();
           cin>>mm;
           cin.get();
           cin>>yy;
           if(cin.fail()){
               cout<<"Enter a valid Date(dd-mm-yy)."<<endl;
               cin.clear();
               cin.ignore(256,'\n');
               Sleep(2000);
               system("cls");
               cout<<"Enter Description of Accomplishment : "<<endl;
               cout<<d<<endl;
               cout<<"Enter the Spend Amount : "<<endl;
               cout<<am<<endl;
               cout<<"Want to add Accomplishment Date ? (y/n) : "<<endl;
               cout<<ch<<endl;
               continue;
           }
           if(!t.is_valid_date(dd,mm,yy)){
               cout<<"Enter Date in correct ranges."<<endl;
               Sleep(2000);
               system("cls");
               cout<<"Enter Description of Accomplishment : "<<endl;
               cout<<d<<endl;
               cout<<"Enter the Spend Amount : "<<endl;
               cout<<am<<endl;
               cout<<"Want to add Accomplishment Date ? (y/n) : "<<endl;
               cout<<ch<<endl;
               continue;
           }
           acc_date = to_string(yy)+"-"+to_string(mm)+"-"+to_string(dd);
           valid = 1;
        }
    }
    else{
        acc_date = "-";
    }
    if (acc_date!="-"){
        query<<"INSERT INTO Accomplishments (DESCRYPTION, SpendAmount, AccDate) VALUES ('"
             <<d<<"','"<<am<<"', DATE('"<<acc_date<<"'))";
    }
    else{
        query<<"INSERT INTO Accomplishments (DESCRYPTION, SpendAmount) VALUES ('"
             <<d<<"','"<<am<<"')";
    }
    if(!mysql_query(Database::connect,query.str().c_str())){
        if(mysql_affected_rows(Database::connect)){
            cout<<"Accomplishment Added."<<endl;
            Sleep(2000);
        }
        else{
            cout<<"\nAccomplishment Adding process failed."<<endl;
            Sleep(2000);
        }
    }
    else{
        cout<<"Failed to access Database correctly."<<mysql_error(Database::connect)<<endl;
        return;
    }
}


int Accomplishment::search_accomplishment(void){
    int valid = 0,is_present = 0;
    string s;
    stringstream query;
    MYSQL_RES* result;
    while(!valid){
        system("cls");
        cout<<"Enter Accomplishment S_NO:  "<<endl;
        getline(cin,s);
        if(cin.fail()){
            cout<<"Enter  a valid S_NO : "<<endl;
            cin.clear();
            cin.ignore(256,'\n');
            Sleep(2000);
            system("cls");
            continue;
        }
        if(!t.is_valid_id(s)||s.length()==0){
            cout<<"Enter  a valid S_NO.Only digits(0-9) are allowed."<<endl;
            Sleep(2000);
            system("cls");
            continue;
        }
        valid = 1;
        s_no = atoi(s.c_str());
    }
    query<<"SELECT * FROM Accomplishments WHERE S_NO = "<<s_no;
    cout<<"Searching";

    for(int i=0;i<2;i++){
        Sleep(400);
        cout<<".";
        Sleep(400);
        cout<<".";
        Sleep(400);
        cout<<".";
        Sleep(400);
        cout<<"\b\b\b   \b\b\b";
    }
    if(!mysql_query(Database::connect,query.str().c_str())){
        result = mysql_store_result(Database::connect);
        if(mysql_num_rows(result)>0){
            MYSQL_ROW row;
            cout<<"\n\t\tAccomplishment Found."<<endl<<endl;
            TextTable t( '-', '|', '+' );
            t.add("Description");
            t.add("Spend Amount(Rs.)");
            t.add("Date of Accomplishment");
            t.endOfRow();
            while((row=mysql_fetch_row(result))!=NULL){
               /*cout<<"Accomplishment Description : ";*/if(row[1]){t.add(row[1]);}else{t.add("Nil");}
               /*cout<<"Spend Amount : Rs ";*/if(row[2]){t.add(row[2]);}else{t.add("Nil");}
               /*cout<<"Date of Accomplishment : ";*/if(row[3]){t.add(row[3]);}else{t.add("-");}
               t.endOfRow();
            }
            is_present = 1;
            t.setAlignment( 2, TextTable::Alignment::LEFT );
            cout<<t;
        }
        else{
            cout<<"\nNo Accomplishment found with S_NO : "<<s<<" in our Database."<<endl;
            Sleep(2000);
        }
        mysql_free_result(result);
    }
    else{
        cout<<"Failed to access Database correctly."<<mysql_error(Database::connect)<<endl;
        return -1;
    }
    if(is_present)
        return s_no;
    else
        return 0;
}


void Accomplishment::delete_accomplishment(void){
    int valid = 0;
    string choice;
    stringstream query;
    s_no = search_accomplishment();
    if(s_no==0)
        return;
    cout<<endl<<endl;
    while(!valid){
        cout<<"Want to Delete this Accomplishment ? Enter(y/n) : "<<endl;
        getline(cin,choice);
        if(cin.fail()){
            cout<<"Enter a valid choice."<<endl;
            cin.clear();
            cin.ignore(256,'\n');
            Sleep(2000);
            continue;
        }
        else if(!t.is_valid_choice(choice)){
            cout<<"\nEnter (y/n)."<<endl;
            Sleep(2000);
            continue;
        }
        valid = 1;
    }
    if(choice[0]=='y'||choice[0] =='Y')
        query<<"DELETE FROM Accomplishments WHERE S_NO = "<<s_no;
    else{
        cout<<"Accomplishment is not deleted as per your command."<<endl;
        Sleep(2000);
        return;
    }
    if(!mysql_query(Database::connect,query.str().c_str())){
        if(mysql_affected_rows(Database::connect)){
            cout<<"Accomplishment is Deleted."<<endl;
            Sleep(2000);
        }
        else{
            cout<<"Accomplishment Deletion Process Failed."<<endl;
            Sleep(2000);
        }
    }
    else{
        cout<<"Failed to access Database correctly."<<mysql_error(Database::connect)<<endl;
    }
}


void Accomplishment::modify_accomplishment(void){
    int valid =0,is_modify = 0,mm,yy,dd,count = 0;
    stringstream query;
    char ch;
    string d,am,date,temp;
    s_no = search_accomplishment();
    if (s_no == 0)
        return;
    cout<<endl<<endl;
    cout<<"Want to modify the Description of Accomplishment ? (y/n) : "<<endl;
    ch = getche();
    cout<<endl;
    if(ch=='y'||ch=='Y'){
        while(!valid){
            count++;
            if(count == 1)
                cout<<"Enter new Accomplishment Description : "<<endl;
            else
                cout<<"Enter new Accomplishment Description correctly : "<<endl;
            getline(cin,d);
            if(cin.fail()){
                cout<<"Enter a valid Accomplishment Description."<<endl;
                cin.clear();
                cin.ignore(256,'\n');
                Sleep(2000);
                continue;
            }
            else if(d.length()<10){
                cout<<"Enter a Description of minimum 10 characters."<<endl;
                Sleep(2000);
                continue;
            }
            valid = 1;
            temp = d;
            d = "'"+temp+"'";
            is_modify = 1;
            description = d;
        }
    }
    else{
        d = "DESCRYPTION";
    }
    valid = 0;
    count=0;
    cout<<"Want to modify the spend Amount ? (y/n) : "<<endl;
    ch = getche();
    cout<<endl;
    if(ch == 'y'||ch == 'Y'){
        while(!valid){
            count++;
            if (count == 1)
                cout<<"Enter new spend Amount : "<<endl;
            else
                cout<<"Enter new spend Amount correctly."<<endl;
            getline(cin,am);
            if(cin.fail()){
                cout<<"Enter a valid Amount."<<endl;
                cin.clear();
                cin.ignore(256,'\n');
                Sleep(2000);
                continue;
            }
            else if(!t.is_valid_amount(am)||am.length()==0){
                cout<<"Enter a valid a amount.Only(digits) and decimal point is allowed."<<endl;
                Sleep(2000);
                continue;
            }
            valid = 1;
            sp_amount = atof(am.c_str());
            temp = am;
            am = "'"+temp+"'";
            is_modify = 1;
        }
    }
    else{
        am = "SpendAmount";
    }
    valid = 0;
    count = 0;
    cout<<"Want to modify the Accomplishment Date ? (y/n) : "<<endl;
    ch=getche();
    cout<<endl;
    if(ch=='y'||ch=='Y'){
        while(!valid){
            count++;
            if(count == 1)
                cout<<"Enter new Accomplishment date(dd-mm-yy) : "<<endl;
            else
                cout<<"Enter new Accomplishment date correctly (dd-mm-yy) : "<<endl;
           cin>>dd;
           cin.get();
           cin>>mm;
           cin.get();
           cin>>yy;
           if(cin.fail()){
               cout<<"Enter a valid Date(dd-mm-yy)."<<endl;
               cin.clear();
               cin.ignore(256,'\n');
               Sleep(2000);
               continue;
           }
           if(!t.is_valid_date(dd,mm,yy)){
               cout<<"Enter Date in correct ranges."<<endl;
               Sleep(2000);
               continue;
           }
           date = to_string(yy)+"-"+to_string(mm)+"-"+to_string(dd);
           acc_date = date;
           is_modify = 1;
           temp = date;
           date = "DATE('"+temp+"')";
           valid = 1;
        }
    }
    else{
        date = "AccDate";
    }
    if(!is_modify){
        cout<<"No changes are made as per your request."<<endl;
        Sleep(2000);
        return;
    }
    query<<"UPDATE Accomplishments SET DESCRYPTION = "<<d<<", SpendAmount = "<<am<<", AccDate = "<<date<<" WHERE S_NO = "<<s_no;
    if(!mysql_query(Database::connect,query.str().c_str())){
        if(mysql_affected_rows(Database::connect)){
            cout<<"Accomplishment is Updated.Can be checked in List Accomplishments section."<<endl;
            Sleep(2000);
        }
        else{
            cout<<"Failed to update the Accomplishment."<<endl;
            Sleep(2000);
        }
    }
    else{
        cout<<"Failed to access Database correctly."<<mysql_error(Database::connect)<<endl;
    }
}


void Accomplishment::display_accomplishment(void){
    system("cls");
    stringstream query;
    MYSQL_RES* result;
    query<<"SELECT * FROM Accomplishments";
    if(!mysql_query(Database::connect,query.str().c_str())){
        result = mysql_store_result(Database::connect);
        if(mysql_num_rows(result)>0){
            cout<<"\t\t\t    Accomplishments"<<endl<<endl;
            TextTable t( '-', '|', '+' );
            t.add("Serial Number");
            t.add("Description");
            t.add("Spend Amount(Rs.)");
            t.add("Date of Accomplishment");
            t.endOfRow();
            MYSQL_ROW row;
            while((row=mysql_fetch_row(result))!=NULL){
                /*cout<<"Serial Number : ";*/if(row[0]){t.add(row[0]);}else{t.add("Nil");}
                /*cout<<"Accomplishment Description : ";*/if(row[1]){t.add(row[1]);}else{t.add("Nil");}
               /*cout<<"Spend Amount : Rs ";*/if(row[2]){t.add(row[2]);}else{t.add("Nil");}
               /*cout<<"Date of Accomplishment : ";*/if(row[3]){t.add(row[3]);}else{t.add("-");}
               t.endOfRow();
            }
           t.setAlignment( 2, TextTable::Alignment::LEFT );
           cout<<t;
        }
        else{
            cout<<"Accomplishment Section is Empty."<<endl;
            Sleep(2000);
        }
        mysql_free_result(result);
    }
    else{
        cout<<"Failed to access Database correctly."<<mysql_error(Database::connect)<<endl;
        return;
    }
    cout<<"\n\nPress any key to return..."<<endl;
    getch();
}

User::User(){
    s_no=0;
    password=" ";
}


void User::add_user(void){
    int valid = 0,i=0,count = 0;
    string fname,lname;
    stringstream query;
    char ch,pass1[50],pass2[50];
    while(!valid){
        system("cls");
        cout<<"Enter User First Name : "<<endl;
        getline(cin,fname);
        if(cin.fail()){
            cout<<"Enter a valid name."<<endl;
            cin.clear();
            cin.ignore(256,'\n');
            Sleep(2000);
            continue;
        }
        if(!t.is_valid_name(fname)){
            cout<<"Enter a valid name.Only alphabets are allowed."<<endl;
            Sleep(2000);
            continue;
        }
        valid = 1;
        firstname = fname;
    }
    valid = 0;
    while(!valid){
        cout<<"Enter User Last Name : "<<endl;
        getline(cin,lname);
        if(cin.fail()){
            cout<<"Enter a valid name."<<endl;
            cin.clear();
            cin.ignore(256,'\n');
            Sleep(2000);
            system("cls");
            cout<<"Enter User First Name : "<<endl;
            cout<<fname<<endl;
            continue;
        }
        if(!t.is_valid_name(lname)){
            cout<<"Enter a valid name.Only alphabets are allowed."<<endl;
            Sleep(2000);
            system("cls");
            cout<<"Enter User First Name : "<<endl;
            cout<<fname<<endl;
            continue;
        }
        valid = 1;
        lastname = lname;
    }
    valid = 0;
    while(!valid){
        count++;
        cout<<"Enter Password : "<<endl;
        while((ch=getch())!= 13){
            if(ch==8){
                if(i>0){
                    cout<<"\b \b";
                    i--;
                }
            }
            else{
                pass1[i++]=ch;
                cout<<"*";
            }
        }
        pass1[i]='\0';
        i=0;
        cout<<"\nConfirm Password : "<<endl;
        while((ch=getch())!= 13){
            if(ch==8){
                if(i>0){
                    cout<<"\b \b";
                    i--;
                }
            }
            else{
                pass2[i++]=ch;
                cout<<"*";
            }
        }
        pass2[i]='\0';
        i=0;
        if(strcmp(pass1,pass2)==0){
            cout<<"\nPassword Matched."<<endl;
            valid = 1;
            break;
        }
        else{
            if(count>3){
                cout<<"\nYou have entered the field more than 3 times incorrectly.\nReturning back..."<<endl;
                Sleep(2000);
                return;
            }
            cout<<"\nPassword Not Matched.Retry from the beginning."<<endl;
            Sleep(2000);
            system("cls");
            cout<<"Enter User First Name : "<<endl;
            cout<<fname<<endl;
            cout<<"Enter User Last Name : "<<endl;
            cout<<lastname<<endl;
            continue;
        }
    }
    query<<"INSERT INTO USERS (FirstName,LastName,PASS) VALUES('"<<firstname<<"','"<<lastname<<"','"<<pass1<<"')";
    if(!mysql_query(Database::connect,query.str().c_str())){
        if(mysql_affected_rows(Database::connect)){
            cout<<"User Inserted Successfully."<<endl;
            Sleep(2000);
        }
        else{
            cout<<"User Insertion Process Failed."<<endl;
            Sleep(2000);
        }
    }
    else{
        cout<<"Failed to access Database correctly."<<mysql_error(Database::connect)<<endl;
        return;
    }
}


void User::delete_user(void){
    int valid = 0,is_found = 0;
    stringstream query1,query2;
    MYSQL_RES *result;
    string s,choice;
    while(!valid){
        system("cls");
        cout<<"Enter the S_NO of user : "<<endl;
        getline(cin,s);
        if(cin.fail()){
            cout<<"Enter the valid serial number."<<endl;
            cin.clear();
            cin.ignore(256,'\n');
            Sleep(2000);
            system("cls");
            continue;
        }
        if(!t.is_valid_id(s)||s.length()==0){
            cout<<"Enter the valid serial number.Only digits are allowed."<<endl;
            Sleep(2000);
            system("cls");
            continue;
        }
        valid = 1;
        s_no = atoi(s.c_str());
    }
    query1<<"SELECT * FROM Users WHERE S_NO = "<<s_no;
    if(!mysql_query(Database::connect,query1.str().c_str())){
        result = mysql_store_result(Database::connect);
        if(mysql_num_rows(result)){
            MYSQL_ROW row;
            is_found = 1;
            cout<<"\n\t User Found"<<endl<<endl;
            TextTable t( '-', '|', '+' );
            t.add("First Name");
            t.add("Last Name");
            t.add("Password");
            t.endOfRow();
            while((row=mysql_fetch_row(result))!=NULL){
                string p;
                /*cout<<"First Name : "*/;if(row[1]){t.add(row[1]);}else{t.add("Nil");}
                /*cout<<"Last Name : ";*/if(row[2]){t.add(row[2]);}else{t.add("Nil");}
                /*cout<<"Password : ";*/if(row[3]){int i;for(i=0;i<strlen(row[3]);i++){if(i==0) p="*";else p+="*" ;}t.add(p);}else{t.add("Nil");}
                t.endOfRow();
            }
             t.setAlignment( 2, TextTable::Alignment::LEFT );
             cout<<t;
        }
        else{
            cout<<"\nNo user is associated with S_NO : "<<s_no<<endl;
            Sleep(2000);
        }
        mysql_free_result(result);
    }
    else{
        cout<<"Failed to access Database correctly."<<mysql_error(Database::connect)<<endl;
        return;
    }
    if(!is_found)
        return;
    valid = 0;
    cout<<endl;
    while(!valid){
        cout<<"Want to Delete this user? Enter(y/n) : "<<endl;
        getline(cin,choice);
        if(cin.fail()){
            cout<<"Enter a valid choice."<<endl;
            cin.clear();
            cin.ignore(256,'\n');
            Sleep(2000);
            continue;
        }
        else if(!t.is_valid_choice(choice)){
            cout<<"\nEnter (y/n)."<<endl;
            Sleep(2000);
            continue;
        }
        valid = 1;
    }
    if(choice[0]=='y'||choice[0] =='Y')
        query2<<"DELETE FROM Users WHERE S_NO = "<<s_no;
    else{
        cout<<"User is not deleted as per your command."<<endl;
        Sleep(2000);
        return;
    }
    if(!mysql_query(Database::connect,query2.str().c_str())){
        if(mysql_affected_rows(Database::connect)){
            cout<<"User Deleted Successfully."<<endl;
            Sleep(2000);
        }
        else{
            cout<<"User Deletion Process Failed."<<endl;
            Sleep(2000);
        }
    }
    else{
        cout<<"Failed to access Database correctly."<<mysql_error(Database::connect)<<endl;
        return;
    }
}


int User::search_user(void){
    int valid = 0,is_found = 0;
    string s;
    MYSQL_RES *result;
    stringstream query;
    while(!valid){
        system("cls");
        cout<<"Enter the S_NO of user : "<<endl;
        getline(cin,s);
        if(cin.fail()){
            cout<<"Enter the valid serial number."<<endl;
            cin.clear();
            cin.ignore(256,'\n');
            Sleep(2000);
            system("cls");
            continue;
        }
        if(!t.is_valid_id(s)||s.length()==0){
            cout<<"Enter the valid serial number.Only digits are allowed."<<endl;
            Sleep(2000);
            system("cls");
            continue;
        }
        valid = 1;
        s_no = atoi(s.c_str());
    }
    query<<"SELECT * FROM Users WHERE S_NO = "<<s_no;
    cout<<"Searching";

    for(int i=0;i<2;i++){
        Sleep(400);
        cout<<".";
        Sleep(400);
        cout<<".";
        Sleep(400);
        cout<<".";
        Sleep(400);
        cout<<"\b\b\b   \b\b\b";
    }
    if(!mysql_query(Database::connect,query.str().c_str())){
        result = mysql_store_result(Database::connect);
        if(mysql_num_rows(result)){
            MYSQL_ROW row;
            is_found = 1;
            cout<<"\n\n\t User Found"<<endl<<endl;
            TextTable t( '-', '|', '+' );
            t.add("First Name");
            t.add("Last Name");
            t.add("Password");
            t.endOfRow();
            while((row=mysql_fetch_row(result))!=NULL){
                string p;
                /*cout<<"First Name : "*/;if(row[1]){t.add(row[1]);}else{t.add("Nil");}
                /*cout<<"Last Name : ";*/if(row[2]){t.add(row[2]);}else{t.add("Nil");}
                /*cout<<"Password : ";*/if(row[3]){int i;for(i=0;i<strlen(row[3]);i++){if(i==0) p="*";else p+="*";}t.add(p);}else{t.add("Nil");}
                t.endOfRow();
            }
             t.setAlignment( 2, TextTable::Alignment::LEFT );
             cout<<t;
        }
        else{
            cout<<"\nNo user is associated with S_NO : "<<s_no<<endl;
            Sleep(2000);
        }
        mysql_free_result(result);
    }
    else{
        cout<<"Failed to access Database correctly."<<mysql_error(Database::connect)<<endl;
        return -1;
    }
    if(!is_found)
        return 0;
    else
        return s_no;
}

void User::display_users(void){
    stringstream query;
    MYSQL_RES *result;
    system("cls");
    query<<"SELECT * FROM Users";
    if(!mysql_query(Database::connect,query.str().c_str())){
        result = mysql_store_result(Database::connect);
        if(mysql_num_rows(result)){
            MYSQL_ROW row;
            cout<<"\t     User List"<<endl<<endl;
            TextTable t( '-', '|', '+' );
            t.add("S_NO");
            t.add("First Name");
            t.add("Last Name");
            t.add("Password");
            t.endOfRow();
            while((row=mysql_fetch_row(result))!=NULL){
                string p;
                /*cout<<"S_NO : "*/;if(row[0]){t.add(row[0]);}else{t.add("Nil");}
                /*cout<<"First Name : "*/;if(row[1]){t.add(row[1]);}else{t.add("Nil");}
                /*cout<<"Last Name : ";*/if(row[2]){t.add(row[2]);}else{t.add("Nil");}
                /*cout<<"Password : ";*/if(row[3]){int i;for(i=0;i<strlen(row[3]);i++){if(i==0) p="*";else p+="*";}t.add(p);}else{t.add("Nil");}
                t.endOfRow();
            }
            t.setAlignment( 2, TextTable::Alignment::LEFT );
            cout<<t;
        }
        else{
            cout<<"Users List is empty."<<endl;
            Sleep(2000);
        }
        mysql_free_result(result);
    }
    else{
        cout<<"Failed to access Database correctly."<<mysql_error(Database::connect)<<endl;
        return;
    }
    cout<<"\n\nPress Enter key to return."<<endl;
    getch();
}


void User::modify_user(void){
    int valid = 0,count = 0,is_modify = 0,is_found = 0,i=0,is_updated = 0;
    stringstream query1,query2,query3;
    string fname,lname,temp,s;
    MYSQL_RES *result;
    char pass[50],pass1[50],pass2[50],ch;
    system("cls");
    cout<<"Enter User's Password to modify user : "<<endl;
    while((ch=getch())!= 13){
        if(ch==8){
            if(i>0){
                cout<<"\b \b";
                i--;
            }
        }
        else{
            pass[i++]=ch;
            cout<<"*";
        }
    }
    pass[i]='\0';
    i=0;
    query1<<"SELECT * FROM Users WHERE PASS = '"<<pass<<"'";
    if(!mysql_query(Database::connect,query1.str().c_str())){
        result = mysql_store_result(Database::connect);
        if(mysql_num_rows(result)){
            MYSQL_ROW row;
            is_found = 1;
            cout<<"\n\n\t   User Found."<<endl<<endl;
            TextTable t( '-', '|', '+' );
            t.add("S_NO");
            t.add("First Name");
            t.add("Last Name");
            t.endOfRow();
            while((row=mysql_fetch_row(result))!=NULL){
                /*cout<<"S_NO : ";*/if(row[0]){t.add(row[0]);s_no = atoi(row[0]);}else{t.add("Nil");}
                /*cout<<"First Name :;*/if(row[1]){t.add(row[1]);}else{t.add("Nil");}
                /*cout<<"Last Name : ";*/if(row[2]){t.add(row[2]);}else{t.add("Nil");}
                t.endOfRow();
            }
            t.setAlignment( 2, TextTable::Alignment::LEFT );
            cout<<t;
        }
        else{
            cout<<"\nNo User is associated with this Password."<<endl;
            Sleep(2000);
        }
        mysql_free_result(result);
    }
    else{
        cout<<"Failed to access Database correctly."<<mysql_error(Database::connect)<<endl;
        return;
    }
    if(!is_found)
        return;
    cout<<endl<<endl;
    cout<<"Want to modify User's First Name? (y/n) : "<<endl;
    ch = getche();
    cout<<endl;
    if(ch=='y'||ch=='Y'){
        while(!valid){
            count++;
            if (count==1)
                cout<<"Enter User's new First Name : "<<endl;
            else
                cout<<"Enter User's new First Name correctly : "<<endl;
            getline(cin,fname);
            if(cin.fail()){
                cout<<"Enter a valid name."<<endl;
                cin.clear();
                cin.ignore(256,'\n');
                Sleep(2000);
                continue;
            }
            if(!t.is_valid_name(fname)){
                cout<<"Enter a valid name.Only alphabets are allowed."<<endl;
                Sleep(2000);
                continue;
            }
            valid = 1;
            is_modify = 1;
            firstname = fname;
            temp = fname;
            fname = "'"+temp+"'";
        }
    }
    else{
        fname = "FirstName";
    }
    valid = 0,count = 0;
    cout<<"Want to modify User's Last Name? (y/n) : "<<endl;
    ch = getche();
    cout<<endl;
    if(ch=='y'||ch=='Y'){
        while(!valid){
            count++;
            if (count==1)
                cout<<"Enter User's new Last Name : "<<endl;
            else
                cout<<"Enter User's new Last Name correctly : "<<endl;
            getline(cin,lname);
            if(cin.fail()){
                cout<<"Enter a valid name."<<endl;
                cin.clear();
                cin.ignore(256,'\n');
                Sleep(2000);
                continue;
            }
            if(!t.is_valid_name(lname)){
                cout<<"Enter a valid name.Only alphabets are allowed."<<endl;
                Sleep(2000);
                continue;
            }
            valid = 1;
            is_modify = 1;
            lastname = lname;
            temp = lname;
            lname = "'"+temp+"'";
        }
    }
    else{
        lname = "LastName";
    }
    valid = 0,count = 0;
    cout<<"Want to modify User Password ? (y/n) "<<endl;
    ch = getche();
    cout<<endl;
    if(ch=='y'||ch=='Y'){
        while(!valid){
            count++;
            if(count == 1)
                cout<<"Enter New Password(must be different from old password or else will not be modified) : "<<endl;
            else
                cout<<"Enter New Password Correctly(must be different from old password or else will not be modified): "<<endl;
            while((ch=getch())!= 13){
                if(ch==8){
                    if(i>0){
                        cout<<"\b \b";
                        i--;
                    }
                }
                else{
                    pass1[i++]=ch;
                    cout<<"*";
                }
            }
            pass1[i]='\0';
            i=0;
            cout<<"\nConfirm Password : "<<endl;
            while((ch=getch())!= 13){
                if(ch==8){
                    if(i>0){
                        cout<<"\b \b";
                        i--;
                    }
                }
                else{
                    pass2[i++]=ch;
                    cout<<"*";
                }
            }
            pass2[i]='\0';
            i=0;
            if(strcmp(pass1,pass2)==0){
                cout<<"\nPassword Matched."<<endl;
                valid = 1;
            }
            else{
                if(count>3){
                    cout<<"\nYou have entered the field more than 3 times incorrectly.\nReturning back..."<<endl;
                    Sleep(2000);
                    return;
                }
                cout<<"\nPassword Not Matched."<<endl;
                Sleep(2000);
                continue;
            }
        }
        password = pass1;
        temp = pass1;
        password = "'"+temp+"'";
        strcpy(pass1,password.c_str());
        is_modify = 1;
    }
    else{
        password = "PASS";
        strcpy(pass1,"PASS");
    }
    if(!is_modify){
        cout<<"No modifications are made on your request."<<endl;
        Sleep(2000);
        return;
    }
    query2<<"UPDATE Users SET FirstName = "<<fname<<",LastName = "<<lname<<",PASS = "<<pass1<<" WHERE S_NO = "<<s_no;
    if(!mysql_query(Database::connect,query2.str().c_str())){
        if(mysql_affected_rows(Database::connect)==1){
            cout<<"User is Updated."<<endl;
            Sleep(2000);
            is_updated = 1;
        }
        else{
            cout<<"User Updating Process Failed."<<endl;
            Sleep(2000);
        }
    }
    else{
        cout<<"Failed to access Database correctly."<<mysql_error(Database::connect)<<endl;
        return;
    }
    if(!is_updated)
        return;
    query3<<"SELECT * FROM Users WHERE S_NO = "<<s_no;
    if(!mysql_query(Database::connect,query3.str().c_str())){
        result = mysql_store_result(Database::connect);
        if(mysql_num_rows(result)){
            MYSQL_ROW row;
            cout<<"\n\t   Updated User"<<endl<<endl;
            TextTable t( '-', '|', '+' );
            t.add("S_NO");
            t.add("First Name");
            t.add("Last Name");
            t.add("Password");
            t.endOfRow();
            while((row=mysql_fetch_row(result))!=NULL){
                string p;
                /*cout<<"S_NO : "*/;if(row[0]){t.add(row[0]);}else{t.add("Nil");}
                /*cout<<"First Name : "*/;if(row[1]){t.add(row[1]);}else{t.add("Nil");}
                /*cout<<"Last Name : ";*/if(row[2]){t.add(row[2]);}else{t.add("Nil");}
                /*cout<<"Password : ";*/if(row[3]){int i;for(i=0;i<strlen(row[3]);i++){if(i==0) p="*";else p+="*";}t.add(p);}else{t.add("Nil");}
                t.endOfRow();
            }
            t.setAlignment( 2, TextTable::Alignment::LEFT );
            cout<<t;
        }
        else{
            cout<<"\nNo user is associated with S_NO : "<<s_no<<endl;
            Sleep(2000);
        }
        mysql_free_result(result);
    }
    else{
        cout<<"Failed to access Database correctly."<<mysql_error(Database::connect)<<endl;
        return;
    }
    Sleep(2000);
}


void Members::add_member(void){
    int valid = 0;
    char ch;
    string name,d,ph;
    stringstream query;
    while(!valid){
        system("cls");
        cout<<"Enter Member's Name : "<<endl;
        getline(cin,name);
        if(cin.fail()){
            cout<<"Enter a valid Name."<<endl;
            cin.clear();
            cin.ignore(256,'\n');
            Sleep(2000);
            continue;
        }
        if(!t.is_valid_name(name)||name.length()==0){
            cout<<"Enter a valid Name.Only alphabets are allowed."<<endl;
            Sleep(2000);
            continue;
        }
        valid = 1;
        full_name = name;
    }
    valid = 0;
    while(!valid){
        cout<<"Enter Member's Designation : "<<endl;
        getline(cin,d);
        if(cin.fail()){
            cout<<"Enter a valid Designation."<<endl;
            cin.clear();
            cin.ignore(256,'\n');
            Sleep(2000);
            system("cls");
            cout<<"Enter Member's Name : "<<endl;
            cout<<name<<endl;
            continue;
        }
        if(!t.is_valid_name(d)||d.length()==0){
            cout<<"Enter a valid Designation.Only alphabets are allowed."<<endl;
            Sleep(2000);
            system("cls");
            cout<<"Enter Member's Name : "<<endl;
            cout<<name<<endl;
            continue;
        }
        valid = 1;
        designation = d;
    }
    valid = 0;
    cout<<"Want to add Member's Phone number ? (y/n) :"<<endl;
    ch = getche();
    cout<<endl;
    if(ch=='y'||ch=='Y'){
        while(!valid){
            cout<<"Enter Member's Phone number : "<<endl;
            getline(cin,ph);
            if(cin.fail()){
                cout<<"Enter a valid Phone number."<<endl;
                cin.clear();
                cin.ignore(256,'\n');
                Sleep(2000);
                system("cls");
                cout<<"Enter Member's Name : "<<endl;
                cout<<name<<endl;
                cout<<"Enter Member's Designation : "<<endl;
                cout<<d<<endl;
                cout<<"Want to add Member's Phone number : "<<endl;
                cout<<ch<<endl;
                continue;
            }
            if(!t.is_valid_num(ph)||ph.length()==0){
                cout<<"Enter a valid Phone number.Only digits(0-9) are allowed."<<endl;
                Sleep(2000);
                system("cls");
                cout<<"Enter Member's Name : "<<endl;
                cout<<name<<endl;
                cout<<"Enter Member's Designation : "<<endl;
                cout<<d<<endl;
                cout<<"Want to add Member's Phone number : "<<endl;
                cout<<ch<<endl;
                continue;
            }
            valid = 1;
            phone_number = ph;
        }
    }
    else{
        ph = "-";
    }
    query<<"INSERT INTO Members(NAME,Designation,PhoneNm) VALUES('"<<name<<"','"<<d<<"','"<<ph<<"')";
    if(!mysql_query(Database::connect,query.str().c_str())){
        if(mysql_affected_rows(Database::connect)){
            cout<<"Member Added."<<endl;
            Sleep(2000);
        }
        else{
            cout<<"Member Addition Process Failed."<<endl;
            Sleep(2000);
        }
    }
    else{
        cout<<"Failed to access Database correctly."<<mysql_error(Database::connect)<<endl;
        return;
    }
}


int Members::search_member(void){
    int valid = 0,is_found = 0;
    stringstream query;
    string i;
    MYSQL_RES* result;
    while(!valid){
        system("cls");
        cout<<"Enter Member ID : "<<endl;
        getline(cin,i);
        if(cin.fail()){
            cout<<"Enter a valid ID."<<endl;
            cin.clear();
            cin.ignore(256,'\n');
            Sleep(2000);
            continue;
        }
        if(!t.is_valid_id(i)||i.length()==0){
            cout<<"Enter a valid ID.Only digits(0-9) are allowed."<<endl;
            Sleep(2000);
            continue;
        }
        valid = 1;
        id = atoi(i.c_str());
    }
    query<<"SELECT * FROM Members WHERE ID = "<<i;
    cout<<"Searching";

    for(int j=0;j<2;j++){
        Sleep(400);
        cout<<".";
        Sleep(400);
        cout<<".";
        Sleep(400);
        cout<<".";
        Sleep(400);
        cout<<"\b\b\b   \b\b\b";
    }
    if(!mysql_query(Database::connect,query.str().c_str())){
        result = mysql_store_result(Database::connect);
        if(mysql_num_rows(result)){
            TextTable t( '-', '|', '+' );
            t.add("Name");
            t.add("Designation");
            t.add("Phone Number");
            t.endOfRow();
            MYSQL_ROW row;
            is_found = 1;
            cout<<"\n\n\t     Member Found."<<endl<<endl<<endl;;
            while((row=mysql_fetch_row(result))!=NULL){
                /*cout<<"Name : ";*/if(row[1]){t.add(row[1]);}else{t.add("Nil");}
                /*cout<<"Designation : ";*/if(row[2]){t.add(row[2]);}else{t.add("Nil");}
                /*cout<<"Phone Number : ";*/if(row[3]){t.add(row[3]);}else{t.add("Nil");}
                t.endOfRow();
            }
            t.setAlignment( 2, TextTable::Alignment::LEFT );
            cout<<t;
        }
        else{
            cout<<"\nNo member is associated with ID : "<<id<<endl;
            Sleep(2000);
        }
        mysql_free_result(result);
    }
    else{
        cout<<"Failed to access Database correctly."<<mysql_error(Database::connect)<<endl;
        return -1;
    }
    if(is_found){
        Sleep(2000);
        return id;
    }
    else
        return 0;
}


void Members::delete_member(void){
    string choice;
    int valid = 0;
    stringstream query;
    id = search_member();
    if(id==0)
        return;
    cout<<endl<<endl;
    while(!valid){
        cout<<"Want to delete this member ? Enter(y/n) : "<<endl;
        getline(cin,choice);
        if(cin.fail()){
            cout<<"Enter a valid choice."<<endl;
            cin.clear();
            cin.ignore(256,'\n');
            Sleep(2000);
            continue;
        }
        if(!t.is_valid_choice(choice)){
            cout<<"Enter (y/n)."<<endl;
            Sleep(2000);
            continue;
        }
        valid = 1;
    }
    if(choice[0] == 'y'||choice[0] =='Y'){
        query<<"DELETE FROM Members WHERE ID = "<<id;
    }
    else{
        cout<<"Member is not deleted as per your request."<<endl;
        Sleep(2000);
        return;
    }
    if(!mysql_query(Database::connect,query.str().c_str())){
        if(mysql_affected_rows(Database::connect)){
            cout<<"Member Deleted Successfully."<<endl;
            Sleep(2000);
        }
        else{
            cout<<"Member Deletion Process Failed."<<endl;
            Sleep(2000);
        }
    }
    else{
        cout<<"Failed to access Database correctly."<<mysql_error(Database::connect)<<endl;
        return;
    }
}


void Members::display_members(void){
    stringstream query;
    MYSQL_RES *result;
    system("cls");
    query<<"SELECT * FROM Members";
    if(!mysql_query(Database::connect,query.str().c_str())){
        result = mysql_store_result(Database::connect);
        if(mysql_num_rows(result)){
            MYSQL_ROW row;
            cout<<"\t\t  Members List"<<endl<<endl<<endl;
            TextTable t( '-', '|', '+' );
            t.add("ID");
            t.add("Name");
            t.add("Designation");
            t.add("Phone Number");
            t.endOfRow();
            while((row=mysql_fetch_row(result))!=NULL){
                /*cout<<"ID : ";*/if(row[0]){t.add(row[0]);}else{t.add("Nil");}
                /*cout<<"Name : ";*/if(row[1]){t.add(row[1]);}else{t.add("Nil");}
                /*cout<<"Designation : ";*/if(row[2]){t.add(row[2]);}else{t.add("Nil");}
                /*cout<<"Phone Number : ";*/if(row[3]){t.add(row[3]);}else{t.add("Nil");}
                t.endOfRow();
            }
            t.setAlignment( 2, TextTable::Alignment::LEFT );
            cout<<t;
        }
        else{
            cout<<"Members List is empty."<<endl;
        }
    }
    else{
        cout<<"Failed to access Database correctly."<<mysql_error(Database::connect)<<endl;
        return;
    }
    cout<<"\nPress Enter key to return."<<endl;
    getch();
}

void Members::modify_member(void){
    char ch;
    int valid = 0,is_modify = 0,modified = 0,count =0;
    string n,d,ph,temp;
    stringstream query1,query2;
    MYSQL_RES *result;
    id = search_member();
    if(id==0)
        return;
    cout<<endl<<endl;
    cout<<"Want to modify the Name of Member ? (y/n) : "<<endl;
    ch = getche();
    cout<<endl;
    if(ch=='y'||ch=='Y'){
        while(!valid){
            count++;
            if(count == 1)
                cout<<"Enter Member's new name  : "<<endl;
            else
                cout<<"Enter Member's new name correctly : "<<endl;
            getline(cin,n);
            if(cin.fail()){
                cout<<"Enter a valid Name."<<endl;
                cin.clear();
                cin.ignore();
                Sleep(2000);
                continue;
            }
            if(!t.is_valid_name(n)||n.length()==0){
                cout<<"Enter a valid name.Only alphabets are allowed."<<endl;
                Sleep(2000);
                continue;
            }
            valid = 1;
            full_name = n;
            temp = n;
            n = "'"+temp+"'";
            is_modify = 1;
        }
    }
    else{
        n = "NAME";
    }
    valid = 0,count = 0;
    cout<<"Want to modify Member's Designation ? (y/n) " <<endl;
    ch = getche();
    cout<<endl;
    if(ch ==  'y'||ch =='Y'){
        while(!valid){
            count++;
            if(count == 1)
                cout<<"Enter Member's new Designation  : "<<endl;
            else
                cout<<"Enter Member's new Designation correctly : "<<endl;
            getline(cin,d);
            if(cin.fail()){
                cout<<"Enter a valid Designation."<<endl;
                cin.clear();
                cin.ignore();
                Sleep(2000);
                continue;
            }
            if(!t.is_valid_name(d)||d.length()==0){
                cout<<"Enter a valid Designation.Only alphabets are allowed."<<endl;
                Sleep(2000);
                continue;
            }
            valid = 1;
            designation = d;
            temp = d;
            is_modify = 1;
            d = "'"+temp+"'";
        }
    }
    else{
        d = "Designation";
    }
    valid = 0,count = 0;
    cout<<"Want to modify Member's Phone Number ? (y/n) : "<<endl;
    ch = getche();
    cout<<endl;
    if(ch=='y'||ch=='Y'){
        while(!valid){
            cout<<"Enter Member's new Phone Number : "<<endl;
            getline(cin,ph);
            if(cin.fail()){
                cout<<"Enter a valid Phone number."<<endl;
                cin.clear();
                cin.ignore(256,'\n');
                Sleep(2000);
                continue;
            }
            if(!t.is_valid_num(ph)||ph.length()==0){
                cout<<"Enter a valid Phone number.Only digits(0-9) are allowed."<<endl;
                Sleep(2000);
                continue;
            }
            valid = 1;
            phone_number = ph;
            temp = ph;
            is_modify = 1;
            ph = "'"+temp+"'";
        }
    }
    else{
        ph = "PhoneNm";
    }
    if(!is_modify){
        cout<<"No changes are made on your request."<<endl;
        Sleep(2000);
        return;
    }
    query1<<"UPDATE Members SET NAME = "<<n<<", Designation = "<<d<<", PhoneNm = "<<ph<<" WHERE ID = "<<id;
    if(!mysql_query(Database::connect,query1.str().c_str())){
        if(mysql_affected_rows(Database::connect)){
            cout<<"Member Updated."<<endl;
            modified = 1;
            Sleep(2000);
        }
        else{
            cout<<"Member Update Process Failed."<<endl;
            Sleep(2000);
        }
    }
    else{
        cout<<"Failed to access Database correctly."<<mysql_error(Database::connect)<<endl;
        return;
    }
    query2<<"SELECT * FROM Members WHERE ID = "<<id;
    if(!mysql_query(Database::connect,query2.str().c_str())){
        result = mysql_store_result(Database::connect);
        if(mysql_num_rows(result)){
            MYSQL_ROW row;
            cout<<"\n\n\t     Updated Member."<<endl<<endl;
            TextTable t( '-', '|', '+' );
            t.add("ID");
            t.add("Name");
            t.add("Designation");
            t.add("Phone Number");
            t.endOfRow();
            while((row=mysql_fetch_row(result))!=NULL){
                /*cout<<"ID : ";*/if(row[0]){t.add(row[0]);}else{t.add("Nil");}
                /*cout<<"Name : ";*/if(row[1]){t.add(row[1]);}else{t.add("Nil");}
                /*cout<<"Designation : ";*/if(row[2]){t.add(row[2]);}else{t.add("Nil");}
                /*cout<<"Phone Number : ";*/if(row[3]){t.add(row[3]);}else{t.add("Nil");}
                t.endOfRow();
            }
            t.setAlignment( 2, TextTable::Alignment::LEFT );
            cout<<t;
        }
        else{
            cout<<"\nNo member is associated with ID : "<<id<<endl;
            Sleep(2000);
        }
        mysql_free_result(result);
    }
    else{
        cout<<"Failed to access Database correctly."<<mysql_error(Database::connect)<<endl;
        return;
    }

}


void WelfareFoundation::welcome_screen(void){
    system("cls");
    db.checkConnect();
    system("cls");
    int i;
    string s1 = "Welcome to WELFARE FOUNDATION PROJECT",s2 = "A Project By:";
    string s3 = "Saad Muhammad Syed(CT-057)",s4= "Syed Kazim Raza(CT-054)",s5 = "Shabi ul Hasan(CT-058)";
    string s6 = "Syed Shameer Sarwar(CT-044)";
    system("cls");
    gotoxy(36,7);
    for(i=0;i<s1.length();i++){
        cout<<s1[i];
        Sleep(60);
    }
    gotoxy(47,9);
    for(i=0;i<s2.length();i++){
        cout<<s2[i];
        Sleep(60);
    }
    gotoxy(40,11);
    for(i=0;i<s3.length();i++){
        cout<<s3[i];
        Sleep(60);
    }
    gotoxy(40,13);
    for(i=0;i<s4.length();i++){
        cout<<s4[i];
        Sleep(60);
    }
    gotoxy(40,15);
    for(i=0;i<s5.length();i++){
        cout<<s5[i];
        Sleep(60);
    }
    gotoxy(40,17);
    for(i=0;i<s6.length();i++){
        cout<<s6[i];
        Sleep(60);
    }
    Sleep(2000);
    login();
    return;
}


void WelfareFoundation::login(void){
    system("cls");
    MYSQL_RES *result;
    int i =0,is_user = 0;
    string name;
    stringstream query;
    char pass[50],ch;
    gotoxy(43,9);
    cout<<"Enter Password :  ";
    while((ch=getch())!=13){
        if(ch==8){
            if(i>0){
                cout<<"\b \b";
                i--;
            }
        }
        else{
            pass[i++]=ch;
            cout<<"*";
        }
    }
    pass[i]='\0';
    query<<"SELECT LastName FROM Users WHERE PASS = '"<<pass<<"'";
    if(!mysql_query(Database::connect,query.str().c_str())){
        result = mysql_store_result(Database::connect);
        if(mysql_num_rows(result)){
            MYSQL_ROW row;
            while((row=mysql_fetch_row(result))!=NULL){
                name = row[0];
            }
            is_user = 1;
        }
        else{
            gotoxy(37,11);
            cout<<"No user is associated with this password.";
            Sleep(2000);
        }
        mysql_free_result(result);
    }
    else{
        cout<<"Failed to access Database correctly."<<mysql_error(Database::connect)<<endl;
        return;
    }
    if(!is_user){
        gotoxy(46,13);
        cout<<"Want to try again? (y/n) : ";
        ch=getche();
        if(ch=='y'||ch=='Y')
            login();
        else{
            //exit_screen();
            Sleep(1000);
            exit(1);
        }
    }
    else{
        system("cls");
        gotoxy(50,12);
        name = "Welcome "+name+",";
        for(i=0;i<name.length();i++){
            cout<<name[i];
            Sleep(60);
        }
        Sleep(2000);
        main_menu();
    }
}

void WelfareFoundation::main_menu(void){
    system("cls");
    string choice;
    gotoxy(49,8);
    cout<<"Main Menu.";
    gotoxy(43,10);
    cout<<"1) Donor Section.";
    gotoxy(43,11);
    cout<<"2) Donation Section.";
    gotoxy(43,12);
    cout<<"3) Target's Section.";
    gotoxy(43,13);
    cout<<"4) Accomplishment's Section.";
    gotoxy(43,14);
    cout<<"5) Member Section.";
    gotoxy(43,15);
    cout<<"6) User Section.";
    gotoxy(43,16);
    cout<<"7) Logout";
    gotoxy(43,17);
    cout<<"8) Exit.";
    gotoxy(43,19);
    cout<<"Enter your choice : ";
    getline(cin,choice);
    if(cin.fail()||(!t.is_valid_id(choice))){
        gotoxy(43,20);
        cout<<"Enter a valid choice."<<endl;
        Sleep(1000);
        main_menu();
        return;
    }
    if(atoi(choice.c_str())==1){
        donor_section();
    }
    else if(atoi(choice.c_str())==2){
        donation_section();
    }
    else if(atoi(choice.c_str())==3){
        target_section();
    }
    else if(atoi(choice.c_str())==4){
        accomplishment_section();
    }
    else if(atoi(choice.c_str())==5){
        Member_section();
    }
    else if(atoi(choice.c_str())==6){
        user_section();
    }
    else if(atoi(choice.c_str())==7){
        system("cls");
        gotoxy(50,12);
        cout<<"Logging Out";

        for(int i=0;i<2;i++){
            Sleep(400);
            cout<<".";
            Sleep(400);
            cout<<".";
            Sleep(400);
            cout<<".";
            Sleep(400);
            cout<<"\b\b\b   \b\b\b";
        }
        login();
    }
    else if(atoi(choice.c_str())==8){
        exit_screen();
    }
    else{
        gotoxy(43,20);
        cout<<"Enter a valid choice."<<endl;
        Sleep(1000);
        main_menu();
        return;
    }
}


void WelfareFoundation::donor_section(void){
    system("cls");
    string choice;
    gotoxy(49,8);
    cout<<"Donor Section.";
    gotoxy(43,10);
    cout<<"1) Add Donor.";
    gotoxy(43,11);
    cout<<"2) Delete Donor.";
    gotoxy(43,12);
    cout<<"3) Modify Donor.";
    gotoxy(43,13);
    cout<<"4) Search Donor.";
    gotoxy(43,14);
    cout<<"5) Display Donors.";
    gotoxy(43,15);
    cout<<"6) Back to main menu.";
    gotoxy(43,16);
    cout<<"7) Logout";
    gotoxy(43,17);
    cout<<"8) Exit.";
    gotoxy(43,19);
    cout<<"Enter your choice : ";
    getline(cin,choice);
    if(cin.fail()||(!t.is_valid_id(choice))){
        if(cin.fail()){
            cin.clear();
            cin.ignore(256,'\n');
        }
        else if(!t.is_valid_id(choice)){
            gotoxy(43,20);
            cout<<"Enter a valid choice."<<endl;
            Sleep(1000);
        }
        donor_section();
        return;
    }
    if(atoi(choice.c_str())==1){
        d.add_donor();
        cout<<"\n\nPress Enter key to return..."<<endl;
        getch();
        donor_section();
    }
    else if(atoi(choice.c_str())==2){
        d.delete_donor();
        cout<<"\n\nPress Enter key to return..."<<endl;
        getch();
        donor_section();
    }
    else if(atoi(choice.c_str())==3){
        d.modify_donor();
        cout<<"\n\nPress Enter key to return..."<<endl;
        getch();
        donor_section();
    }
    else if(atoi(choice.c_str())==4){
        d.search_donor_id();
        cout<<"\n\nPress Enter key to return..."<<endl;
        getch();
        donor_section();
    }
    else if(atoi(choice.c_str())==5){
        d.display_donors();
        donor_section();
    }
    else if(atoi(choice.c_str())==6){
        gotoxy(43,20);
        cout<<"Returning";
        for(int i=0;i<1;i++){
            Sleep(400);
            cout<<".";
            Sleep(400);
            cout<<".";
            Sleep(400);
            cout<<".";
            Sleep(400);
            cout<<"\b\b\b   \b\b\b";
        }
        main_menu();
    }
    else if(atoi(choice.c_str())==7){
        system("cls");
        gotoxy(50,12);
        cout<<"Logging Out";

        for(int i=0;i<2;i++){
            Sleep(400);
            cout<<".";
            Sleep(400);
            cout<<".";
            Sleep(400);
            cout<<".";
            Sleep(400);
            cout<<"\b\b\b   \b\b\b";
        }
        login();
    }
    else if(atoi(choice.c_str())==8){
        exit_screen();
    }
    else{
        if(cin.fail()){
            cin.clear();
            cin.ignore(256,'\n');
        }
        else if(choice.length()!=0){
            gotoxy(43,20);
            cout<<"Enter a valid choice."<<endl;
            Sleep(1000);
        }
        donor_section();
        return;
    }

}


void WelfareFoundation::donation_section(void){
    system("cls");
    string choice;
    gotoxy(49,4);
    cout<<"Donation Section.";
    gotoxy(43,7);
    cout<<"1) Add Donation.";
    gotoxy(43,8);
    cout<<"2) Delete Donor Monthly Record By Donor ID.";
    gotoxy(43,9);
    cout<<"3) Delete Donor Yearly Record By Donor ID.";
    gotoxy(43,10);
    cout<<"4) Modify Donor Full Record Using Donor ID.";
    gotoxy(43,11);
    cout<<"5) Get Monthly Donation Count.";
    gotoxy(43,12);
    cout<<"6) Get Yearly Donation Count.";
    gotoxy(43,13);
    cout<<"7) Get Total Donation Count of Donor By Donor ID.";
    gotoxy(43,14);
    cout<<"8) Get Total Record of Donor By Donor ID.";
    gotoxy(43,15);
    cout<<"9) Back to main menu.";
    gotoxy(43,16);
    cout<<"10) Logout";
    gotoxy(43,17);
    cout<<"11) Exit.";
    gotoxy(43,19);
    cout<<"Enter your choice : ";
    getline(cin,choice);
    if(cin.fail()||(!t.is_valid_id(choice))){
        if(cin.fail()){
            cin.clear();
            cin.ignore(256,'\n');
        }
        else if(!t.is_valid_id(choice)){
            gotoxy(43,20);
            cout<<"Enter a valid choice."<<endl;
            Sleep(1000);
        }
        donation_section();
        return;
    }
    if(atoi(choice.c_str())==1){
        D.add_donation();
        cout<<"\n\nPress Enter key to return..."<<endl;
        getch();
        donation_section();
    }
    else if(atoi(choice.c_str())==2){
        D.delete_donation_monthly();
        cout<<"\n\nPress Enter key to return..."<<endl;
        getch();
        donation_section();
    }
    else if(atoi(choice.c_str())==3){
        D.delete_donation_yearly();
        cout<<"\n\nPress Enter key to return..."<<endl;
        getch();
        donation_section();
    }
    else if(atoi(choice.c_str())==4){
        D.modify_donation();
        cout<<"\n\nPress Enter key to return..."<<endl;
        getch();
        donation_section();
    }
    else if(atoi(choice.c_str())==5){
        D.get_donation_monthly();
        cout<<"\n\nPress Enter key to return..."<<endl;
        getch();
        donation_section();
    }
    else if(atoi(choice.c_str())==6){
        D.get_donation_yearly();
        cout<<"\n\nPress Enter key to return..."<<endl;
        getch();
        donation_section();
    }
    else if(atoi(choice.c_str())==7){
        D.get_total_donation_id();
        cout<<"\n\nPress Enter key to return..."<<endl;
        getch();
        donation_section();
    }
    else if(atoi(choice.c_str())==8){
        D.display_total_record_id();
        cout<<"\n\nPress Enter key to return..."<<endl;
        getch();
        donation_section();
    }
    else if(atoi(choice.c_str())==9){
        gotoxy(43,20);
        cout<<"Returning";
        for(int i=0;i<1;i++){
            Sleep(400);
            cout<<".";
            Sleep(400);
            cout<<".";
            Sleep(400);
            cout<<".";
            Sleep(400);
            cout<<"\b\b\b   \b\b\b";
        }
        main_menu();
    }
    else if(atoi(choice.c_str())==10){
        system("cls");
        gotoxy(50,12);
        cout<<"Logging Out";

        for(int i=0;i<2;i++){
            Sleep(400);
            cout<<".";
            Sleep(400);
            cout<<".";
            Sleep(400);
            cout<<".";
            Sleep(400);
            cout<<"\b\b\b   \b\b\b";
        }
        login();
    }
    else if(atoi(choice.c_str())==11){
        exit_screen();
    }
    else{
        if(cin.fail()){
            cin.clear();
            cin.ignore(256,'\n');
        }
        else if(choice.length()!=0){
            gotoxy(43,20);
            cout<<"Enter a valid choice."<<endl;
            Sleep(1000);
        }
        donation_section();
        return;
    }

}


void WelfareFoundation::target_section(void){
    system("cls");
    string choice;
    gotoxy(49,8);
    cout<<"Target's Section.";
    gotoxy(43,10);
    cout<<"1) Add Target.";
    gotoxy(43,11);
    cout<<"2) Delete Target.";
    gotoxy(43,12);
    cout<<"3) Modify Target.";
    gotoxy(43,13);
    cout<<"4) Search Target.";
    gotoxy(43,14);
    cout<<"5) Display Targets.";
    gotoxy(43,15);
    cout<<"6) Back to main menu.";
    gotoxy(43,16);
    cout<<"7) Logout";
    gotoxy(43,17);
    cout<<"8) Exit.";
    gotoxy(43,19);
    cout<<"Enter your choice : ";
    getline(cin,choice);
    if(cin.fail()||(!t.is_valid_id(choice))){
        if(cin.fail()){
            cin.clear();
            cin.ignore(256,'\n');
        }
        else if(!t.is_valid_id(choice)){
            gotoxy(43,20);
            cout<<"Enter a valid choice."<<endl;
            Sleep(1000);
        }
        target_section();
        return;
    }
    if(atoi(choice.c_str())==1){
        T.add_target();
        cout<<"\n\nPress Enter key to return..."<<endl;
        getch();
        target_section();
    }
    else if(atoi(choice.c_str())==2){
        T.delete_target();
        cout<<"\n\nPress Enter key to return..."<<endl;
        getch();
        target_section();
    }
    else if(atoi(choice.c_str())==3){
        T.modify_target();
        cout<<"\n\nPress Enter key to return..."<<endl;
        getch();
        target_section();
    }
    else if (atoi(choice.c_str())==4){
        T.search_target();
        cout<<"\n\nPress Enter key to return..."<<endl;
        getch();
        target_section();
    }
    else if(atoi(choice.c_str())==5){
        T.display_targets();
        target_section();
    }
    else if(atoi(choice.c_str())==6){
        gotoxy(43,20);
        cout<<"Returning";
        for(int i=0;i<1;i++){
            Sleep(400);
            cout<<".";
            Sleep(400);
            cout<<".";
            Sleep(400);
            cout<<".";
            Sleep(400);
            cout<<"\b\b\b   \b\b\b";
        }
        main_menu();
    }
    else if(atoi(choice.c_str())==7){
        system("cls");
        gotoxy(50,12);
        cout<<"Logging Out";

        for(int i=0;i<2;i++){
            Sleep(400);
            cout<<".";
            Sleep(400);
            cout<<".";
            Sleep(400);
            cout<<".";
            Sleep(400);
            cout<<"\b\b\b   \b\b\b";
        }
        login();
    }
    else if(atoi(choice.c_str())==8){
        exit_screen();
    }
    else{
        if(cin.fail()){
            cin.clear();
            cin.ignore(256,'\n');
        }
        else if(choice.length()!=0){
            gotoxy(43,20);
            cout<<"Enter a valid choice."<<endl;
            Sleep(1000);
        }
        target_section();
        return;
    }
}


void WelfareFoundation::accomplishment_section(void){
    system("cls");
    string choice;
    gotoxy(49,8);
    cout<<"Accomplishment's Section.";
    gotoxy(43,10);
    cout<<"1) Add Accomplishment.";
    gotoxy(43,11);
    cout<<"2) Delete Accomplishment.";
    gotoxy(43,12);
    cout<<"3) Modify Accomplishment.";
    gotoxy(43,13);
    cout<<"4) Search Accomplishment.";
    gotoxy(43,14);
    cout<<"5) Display Accomplishments.";
    gotoxy(43,15);
    cout<<"6) Back to main menu.";
    gotoxy(43,16);
    cout<<"7) Logout";
    gotoxy(43,17);
    cout<<"8) Exit.";
    gotoxy(43,19);
    cout<<"Enter your choice : ";
    getline(cin,choice);
    if(cin.fail()||(!t.is_valid_id(choice))){
        if(cin.fail()){
            cin.clear();
            cin.ignore(256,'\n');
        }
        else if(!t.is_valid_id(choice)){
            gotoxy(43,20);
            cout<<"Enter a valid choice."<<endl;
            Sleep(1000);
        }
        accomplishment_section();
        return;
    }
    if(atoi(choice.c_str())==1){
        a.add_accomplishment();
        cout<<"\n\nPress Enter key to return..."<<endl;
        getch();
        accomplishment_section();
    }
    else if(atoi(choice.c_str())==2){
        a.delete_accomplishment();
        cout<<"\n\nPress Enter key to return..."<<endl;
        getch();
        accomplishment_section();
    }
    else if(atoi(choice.c_str())==3){
        a.modify_accomplishment();
        cout<<"\n\nPress Enter key to return..."<<endl;
        getch();
        accomplishment_section();
    }
    else if (atoi(choice.c_str())==4){
        a.search_accomplishment();
        cout<<"\n\nPress Enter key to return..."<<endl;
        getch();
        accomplishment_section();
    }
    else if(atoi(choice.c_str())==5){
        a.display_accomplishment();
        accomplishment_section();
    }
    else if(atoi(choice.c_str())==6){
        gotoxy(43,20);
        cout<<"Returning";
        for(int i=0;i<1;i++){
            Sleep(400);
            cout<<".";
            Sleep(400);
            cout<<".";
            Sleep(400);
            cout<<".";
            Sleep(400);
            cout<<"\b\b\b   \b\b\b";
        }
        main_menu();
    }
    else if(atoi(choice.c_str())==7){
        system("cls");
        gotoxy(50,12);
        cout<<"Logging Out";

        for(int i=0;i<2;i++){
            Sleep(400);
            cout<<".";
            Sleep(400);
            cout<<".";
            Sleep(400);
            cout<<".";
            Sleep(400);
            cout<<"\b\b\b   \b\b\b";
        }
        login();
    }
    else if(atoi(choice.c_str())==8){
        exit_screen();
    }
    else{
        if(cin.fail()){
            cin.clear();
            cin.ignore(256,'\n');
        }
        else if(choice.length()!=0){
            gotoxy(43,20);
            cout<<"Enter a valid choice."<<endl;
            Sleep(1000);
        }
        accomplishment_section();
        return;
    }
}


void WelfareFoundation::user_section(void){
    system("cls");
    string choice;
    gotoxy(49,8);
    cout<<"User's Section.";
    gotoxy(43,10);
    cout<<"1) Add User.";
    gotoxy(43,11);
    cout<<"2) Delete User.";
    gotoxy(43,12);
    cout<<"3) Modify User.";
    gotoxy(43,13);
    cout<<"4) Search User.";
    gotoxy(43,14);
    cout<<"5) Display User.";
    gotoxy(43,15);
    cout<<"6) Back to main menu.";
    gotoxy(43,16);
    cout<<"7) Logout";
    gotoxy(43,17);
    cout<<"8) Exit.";
    gotoxy(43,19);
    cout<<"Enter your choice : ";
    getline(cin,choice);
    if(cin.fail()||(!t.is_valid_id(choice))){
        if(cin.fail()){
            cin.clear();
            cin.ignore(256,'\n');
        }
        else if(!t.is_valid_id(choice)){
            gotoxy(43,20);
            cout<<"Enter a valid choice."<<endl;
            Sleep(1000);
        }
        user_section();
        return;
    }
    if(atoi(choice.c_str())==1){
        u.add_user();
        cout<<"\n\nPress Enter key to return..."<<endl;
        getch();
        user_section();
    }
    else if(atoi(choice.c_str())==2){
        u.delete_user();
        cout<<"\n\nPress Enter key to return..."<<endl;
        getch();
        user_section();
    }
    else if(atoi(choice.c_str())==3){
        u.modify_user();
        cout<<"\n\nPress Enter key to return..."<<endl;
        getch();
        user_section();
    }
    else if (atoi(choice.c_str())==4){
        u.search_user();
        cout<<"\n\nPress Enter key to return..."<<endl;
        getch();
       user_section();
    }
    else if(atoi(choice.c_str())==5){
        u.display_users();
        user_section();
    }
    else if(atoi(choice.c_str())==6){
        gotoxy(43,20);
        cout<<"Returning";
        for(int i=0;i<1;i++){
            Sleep(400);
            cout<<".";
            Sleep(400);
            cout<<".";
            Sleep(400);
            cout<<".";
            Sleep(400);
            cout<<"\b\b\b   \b\b\b";
        }
        main_menu();
    }
    else if(atoi(choice.c_str())==7){
        system("cls");
        gotoxy(50,12);
        cout<<"Logging Out";

        for(int i=0;i<2;i++){
            Sleep(400);
            cout<<".";
            Sleep(400);
            cout<<".";
            Sleep(400);
            cout<<".";
            Sleep(400);
            cout<<"\b\b\b   \b\b\b";
        }
        login();
    }
    else if(atoi(choice.c_str())==8){
        exit_screen();
    }
    else{
        if(cin.fail()){
            cin.clear();
            cin.ignore(256,'\n');
        }
        else if(choice.length()!=0){
            gotoxy(43,20);
            cout<<"Enter a valid choice."<<endl;
            Sleep(1000);
        }
        user_section();
        return;
    }
}


void WelfareFoundation::Member_section(void){
    system("cls");
    string choice;
    gotoxy(49,8);
    cout<<"Member's Section.";
    gotoxy(43,10);
    cout<<"1) Add Member.";
    gotoxy(43,11);
    cout<<"2) Delete Member.";
    gotoxy(43,12);
    cout<<"3) Modify Member.";
    gotoxy(43,13);
    cout<<"4) Search Member.";
    gotoxy(43,14);
    cout<<"5) Display Member.";
    gotoxy(43,15);
    cout<<"6) Back to main menu.";
    gotoxy(43,16);
    cout<<"7) Logout";
    gotoxy(43,17);
    cout<<"8) Exit.";
    gotoxy(43,19);
    cout<<"Enter your choice : ";
    getline(cin,choice);
    if(cin.fail()||(!t.is_valid_id(choice))){
        if(cin.fail()){
            cin.clear();
            cin.ignore(256,'\n');
        }
        else if(!t.is_valid_id(choice)){
            gotoxy(43,20);
            cout<<"Enter a valid choice."<<endl;
            Sleep(1000);
        }
        Member_section();
        return;
    }
    if(atoi(choice.c_str())==1){
        m.add_member();
        cout<<"\n\nPress Enter key to return..."<<endl;
        getch();
        Member_section();
    }
    else if(atoi(choice.c_str())==2){
        m.delete_member();
        cout<<"\n\nPress Enter key to return..."<<endl;
        getch();
        Member_section();
    }
    else if(atoi(choice.c_str())==3){
        m.modify_member();
        cout<<"\n\nPress Enter key to return..."<<endl;
        getch();
        Member_section();
    }
    else if (atoi(choice.c_str())==4){
        m.search_member();
        cout<<"\n\nPress Enter key to return..."<<endl;
        getch();
       Member_section();
    }
    else if(atoi(choice.c_str())==5){
        m.display_members();
        Member_section();
    }
    else if(atoi(choice.c_str())==6){
        gotoxy(43,20);
        cout<<"Returning";
        for(int i=0;i<1;i++){
            Sleep(400);
            cout<<".";
            Sleep(400);
            cout<<".";
            Sleep(400);
            cout<<".";
            Sleep(400);
            cout<<"\b\b\b   \b\b\b";
        }
        main_menu();
    }
    else if(atoi(choice.c_str())==7){
        system("cls");
        gotoxy(50,12);
        cout<<"Logging Out";

        for(int i=0;i<2;i++){
            Sleep(400);
            cout<<".";
            Sleep(400);
            cout<<".";
            Sleep(400);
            cout<<".";
            Sleep(400);
            cout<<"\b\b\b   \b\b\b";
        }
        login();
    }
    else if(atoi(choice.c_str())==8){
        exit_screen();
    }
    else{
        if(cin.fail()){
            cin.clear();
            cin.ignore(256,'\n');
        }
        else if(choice.length()!=0){
            gotoxy(43,20);
            cout<<"Enter a valid choice."<<endl;
            Sleep(1000);
        }
        Member_section();
        return;
    }
}


void WelfareFoundation::exit_screen(void){
    system("cls");
    int i;
    string s = "Thank you for using our software.Exiting";
    gotoxy(40,12);
    for(i =0;i<s.length();i++){
        cout<<s[i];
        Sleep(50);
    }
    for(i=0;i<2;i++){
        Sleep(400);
        cout<<".";
        Sleep(400);
        cout<<".";
        Sleep(400);
        cout<<".";
        Sleep(400);
        cout<<"\b\b\b   \b\b\b";
    }
    cout<<"...";
    exit(0);
}


int main()
{
    WelfareFoundation w;
    w.welcome_screen();
    return 0;
}

