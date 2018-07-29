#include <iostream>
#define TAB "\t\t"
#include<fstream>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<windows.h>

using namespace std;


class Phone_book
{
public:

    Phone_book(){}

    void setData();

    void getData();

    char* getName();

    void showData();



    friend double Total_balance();
    friend void call_2nd_part(int choice);


private:

    char name[20];

    char number[20];


};

void write_data();

void read_data();

void update();

int total();

void del();

void save_call_record_in_file_1(char* name);
void read_call_record_in_file();


void save_Time_in_File(double t); /// saves the total talk time int a file
void read_Time_in_File(); /// reads the total talk time from the file

void fex();

double total_Talk_time_of_mobile;

void calling(); /// displays calling in the screen
void makeCall();  /// this is where the call is made

bool flag_seacrh=false; /// flag to use search data in searching name
bool call_flag=false;

void read_balance();
void write_balance(double balance);

void search_data();

string last_100_call_Record[100];
int index;
void display_the_call_Record();

void call();
void call_2nd_part(int choice);

double balance;

int main()
{
    char choice[10];


    while(true)
    {

    read_balance();
    read_Time_in_File();

     system("cls");

     system("color 0b");

     cout<<"Total contacts:"<<total()<<"\t\t\t\t"<<"balance:"<<balance<<" TK"<<endl;;
     cout<<"Total talk time:"<<total_Talk_time_of_mobile<<" s"<<" ("
     <<total_Talk_time_of_mobile/60<<" min )"<<endl;

    cout<<"\n\n\n\n\n\n";
    cout<<TAB<<"...................................."<<endl;
    cout<<TAB<<"|          1.Add data              |"<<endl;
    cout<<TAB<<"|          2.Display Contacts      |"<<endl;
    cout<<TAB<<"|          3.Update Contacts       |"<<endl;
    cout<<TAB<<"|          4.Delete data           |"<<endl;
    cout<<TAB<<"|          5.Flexiload             |"<<endl;
    cout<<TAB<<"|          6.Exit                  |"<<endl;
    cout<<TAB<<"|          7.Search                |"<<endl;
    cout<<TAB<<"|          8.Call                  |"<<endl;
    cout<<TAB<<"|          9.Call log              |"<<endl;
    cout<<TAB<<"|..................................|"<<endl;

    cout<<"\n\n\nEnter your option:"<<endl;

    cin>>choice[0];

    switch(choice[0])
    {
    case '1':

        system("cls");

        write_data();


        break;

    case '2':

        system("cls");

        read_data();

        cin.ignore();

        cin.get();

        break;

    case '3':

        system("cls");

        update();

        break;

    case '4':

        system("cls");

        del();

        break;

    case '6':

        exit(1);
    case '5':

        fex();

        cout<<"Flexiload successfully."<<endl;
        cin.get();

        break;

    case '7':

        system("cls");
        search_data();

        break;

    case '8' :

        call();

        break;

    case '9' :

        system("cls");
        read_call_record_in_file();
        display_the_call_Record();
        fflush(stdin);
        cout<<"Enter any key:"<<endl;
        cin.get();

        break;

    default:

        cout<<"Invalid argument !!"<<endl;

        cin.ignore();

        cin.get();




    }

    }
    return 0;
}

/***************    member function        ****************/

void Phone_book ::setData()
{
    cout<<"Enter the name:"<<endl;

  //  cin.ignore();

  fflush(stdin);

    cin.getline(name,20);

    cout<<"Enter the number:"<<endl;

    cin>>number;
}





void Phone_book:: getData()
{
    cout<<"Name:"<<name<<endl;

    cout<<"Number:"<<number<<endl;
}

char* Phone_book::getName()
{
    return name;
}


///********************************************************




void write_data()
{
   ofstream out("PhoneBook.dat",ios_base::app | ios_base:: binary);

   Phone_book ob;

   ob.setData();

   out.write((char *)& ob,sizeof(ob));

   out.close();
}
///*************************************
void read_data()
{
    try
    {


    ifstream in("Phonebook.dat",ios_base:: binary);

    if(in.fail())
    {
        cerr<<"There is no data in the file  !!"<<endl;

        cin.ignore();

        cin.get();

        return;
    }

    Phone_book ob;

    while(in.read((char *)& ob,sizeof(ob)))
    {
        ob.getData();

        cout<<"\n\n\n";
    }

    in.close();

    }

    catch(...)
    {
        cout<<"Error cought"<<endl;

        cin.get();
    }
}
///******************************************

int total()
{
    ifstream in("Phonebook.dat",ios_base:: in);

    if(in.fail())
    {
        in.close();

        return 0;
    }

    int count=0;

    Phone_book ob;

    while(in.read((char*)& ob,sizeof(ob)))
    {
        count++;
    }

    in.close();

    return count;

}

///******************

void update()
{
    fstream up("Phonebook.dat",ios_base :: in | ios_base :: out);

    if( up.fail())
    {
        cout<<"There is no file to update to update data"<<endl;

        cin.ignore();

        cin.get();

        return;
    }


    cout<<"Enter the name to update:"<<endl;

    cin.ignore();


    char name[20];

    cin.getline(name,20);

    Phone_book ob;



    while(up.read((char *)& ob,sizeof(ob)))
    {
        if(strcmp(name,ob.getName()) == 0)
        {
            cout<<"Name found, updating data"<<endl;


            ob.setData();

            int pos=sizeof(ob);

            up.seekg(-pos,ios_base::cur);

            up.write((char *)& ob,sizeof(ob));

            cin.ignore();

            cout<<"Update successful."<<endl;

           // cin.ignore();

            cin.get();

            up.close();

            return;



        }
    }

    up.close();


    cout<<"Could not fine the name to update."<<endl;

  // cin.ignore(10,'\n');

    cin.get();
}


void del()
{
    cout<<"Enter the name you want to delete:"<<endl;

    cin.ignore();
    char temp[20];

    bool flag= false;

    cin.getline(temp,20);

    Phone_book pb;

    ifstream old("PhoneBook.dat",ios_base::in | ios_base::out);

    if(old.fail())
    {
        cout<<"No data to delete."<<endl;

        cin.get();

        return;
    }

    ofstream out("new.dat",ios_base::out | ios_base :: binary);

    while(old.read((char *)&pb,sizeof(pb)))
    {
        if(strcmp(temp,pb.getName()) != 0)
        {
            out.write((char*)&pb,sizeof(pb));
        }

        else
        {
            flag =true;
        }
    }

    old.close();
    out.close();

    remove("PhoneBook.dat");
    rename("new.dat","PhoneBook.dat");

    if(flag == true)
    {
        cout<<"Data was deleted secessfully "<<endl;

    }

    else
    {
        cout<<"There is no name as "<<temp<<" in the phone book"<<endl;

    }

    cin.get();
}

void fex()
{

    double temp;
    cout<<"Enter the amount you want to charge:"<<endl;
    cin>>temp;
    balance+=temp;

    write_balance(balance);
}

void read_balance()
{
    ifstream read("balance.txt");

    if(read.fail())
    {
        balance=0;

    }

    read>>balance;

    read.close();
}

void write_balance(double balance=0)
{
    ofstream out("balance.txt");

    out<<balance;

    out.close();


}

void call()
{
    system("cls");

    cout<<"Press 1 to call by name or 0 to  call by  number:"<<endl;
    char choice[5];
    cin>>choice[0];

    if(choice[0] =='1')
    {
      /**  read_data();
        flag_seacrh=false;
        search_data();


        if(flag_seacrh == true)
        {
            call_flag=false;

            makeCall();  **/

            call_2nd_part(1);
        }

      /**  else
        {
            cout<<"No such name was found"<<endl;
            cin.get();
        }**/

   // }
    else if(choice[0] == '0')
    {
      /*  system("cls");

        cout<<"Enter the number:"<<endl;

        string number;

        cin>>number;

        fflush(stdin);*/

        call_2nd_part(2);



    }

}




void read_Time_in_File()
{
    ifstream inPut("time.txt");
    if(inPut.fail())
    {
        total_Talk_time_of_mobile=0;
    }


    inPut>>total_Talk_time_of_mobile;
    inPut.close();

}



void makeCall()
{
  /*  cout<<"Enter the name you want to call:"<<endl;
    char name[20];
    cin.getline(name,20);
    search_data() */

    if(balance == 0)
    {
        cout<<"You dont have enough balance to make the call."<<endl;
        cin.get();
        return;
    }

    calling();

    cout<<"Call has stated..."<<endl;

    time_t start_time,finish_time;
    time(&start_time);
    cout<<"Enter any key to end the call"<<endl;
    cin.get();
    time(&finish_time);
    double total_time=difftime(finish_time,start_time);
    total_Talk_time_of_mobile+=total_time;
    save_Time_in_File(total_Talk_time_of_mobile);
    double call_cost=(1.66*total_time)/100;
    balance-=call_cost;
    write_balance(balance);
    cout<<"Talk time: "<<total_time<<"second, Call cost:"<<call_cost<<endl;
    cin.get();




}

void search_data()
{
   // bool flag=false;

    ifstream in("PhoneBook.dat",ios_base::binary);
    if(in.fail())
    {
        cout<<"There is no data to search."<<endl;
        cin.get();
        return;
    }

    cout<<"Enter the name you want to search:"<<endl;
    cin.ignore();
    char temp[20];
    cin.getline(temp,20);


    Phone_book ob;

    while(in.read((char*)&ob,sizeof(ob)))
    {
        if(strcmp(temp,ob.getName()) == 0)
        {
            ob.getData();

            cout<<"Enter any key to continue"<<endl;
            cin.get();
            flag_seacrh=true;

        }

    }

   /* if(flag == false)
    {
        cout<<temp<<" was not found."<<endl;
        cin.get();
    }*/
}

void calling()
{
    int j=0;
    system("cls");

    cout<<"Calling";

    for(int i=0; i!=15;i++,j++)
    {

      cout<<".";

      if(j == 5)
      {
          system("cls");
          cout<<"Calling";
          j=0;
      }

       Sleep(300);



    }

}

void save_Time_in_File(double t)
{
    ofstream outPut("time.txt");

    outPut<<t;

    outPut.close();
}



void call_2nd_part(int choice)
{
    if (choice == 1)
    {




        ifstream input("PhoneBook.dat",ios_base::binary);
        if(input.fail())
        {
            cout<<"No name to search"<<endl;
            fflush(stdin);
            cin.get();
            return;
        }

         char temp[20];
         fflush(stdin);
         cout<<"Enter the name:"<<endl;
         cin.getline(temp,20);

         Phone_book ob;

         while(input.read((char*)&ob,sizeof(ob)) )
         {
             if(strcmp(temp,ob.name)==0)
             {

                 makeCall();

                 save_call_record_in_file_1(temp);

                 return;
             }
         }

         cout<<"The name is not in your phone book."<<endl;
         fflush(stdin);
         cin.get();
    }

    else
    {
        cout<<"Enter the number:"<<endl;
        char number[20];
        cin>>number;
        fflush(stdin);
        makeCall();
        save_call_record_in_file_1(number);


    }

}


void save_call_record_in_file_1(char* pName)
{
    char name[strlen(pName+1)];

    strcpy(name,pName);

     string temp;

     for(int i=0;name[i]!='\0';i++)
     {
         temp+=name[i];
     }

     ofstream outPut("nameRecord.txt",ios_base::app);
     outPut<<temp;
     outPut<<"\n";

     outPut.close();
}

void read_call_record_in_file()
{
    ifstream inPut("nameRecord.txt");
    if(inPut.fail())
    {
        return;
    }

   string temp;



    while(!inPut.eof())
    {
        inPut>>temp;

        if(inPut.fail())
        {
            return;
        }
        last_100_call_Record[index]=temp;
        index++;
    }
}

void display_the_call_Record()
{

    int j=1;

    for(int i=index-1;i>=0;i--)
    {
        cout<<j<<"."<<last_100_call_Record[i]<<endl;
        j++;
    }
}

