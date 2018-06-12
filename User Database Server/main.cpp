#include <iostream>
#include <fstream>
#include <windows.h>
#define username "Administrator"
#define userPass "admin"

using namespace std;
bool UserLoggedIn=false;
string IP,port="21";

int loading_screen_startup1()
{
    system("cls");
    cout<<"Database Server\n===============";
    for(int i=0;i<=20;i++)
        cout<<"\n";
    cout<<"Starting services...\n";
    for(int i=0;i<20;i++)
    {
        cout<<"|";
        Sleep(75+i);
    }
}

int loading_screen_startup2()
{
    system("cls");
    cout<<"Database Server\n===============";
    for(int i=0;i<=20;i++)
        cout<<"\n";
    cout<<"Loading files...\n";
    for(int i=0;i<20;i++)   cout<<"|";
    for(int i=0;i<20;i++)
    {
        cout<<"|";
        Sleep(75+i);
    }
}

int loading_screen_startup3()
{
    system("cls");
    cout<<"Database Server\n===============";
    for(int i=0;i<=20;i++)
        cout<<"\n";
    cout<<"Connecting to the network...\n";
    for(int i=0;i<40;i++)   cout<<"|";
    for(int i=0;i<20;i++)
    {
        cout<<"|";
        Sleep(75+i);
    }
}

int loading_screen_startup4()
{
    system("cls");
    cout<<"Database Server\n===============";
    for(int i=0;i<=20;i++)
        cout<<"\n";
    cout<<"Finishing startup...\n";
    for(int i=0;i<60;i++)   cout<<"|";
    for(int i=0;i<15;i++)
    {
        cout<<"|";
        Sleep(75+i);
    }
}

int startupRoutine()
{
    system("title Database Server");
    system("color 1F");
    loading_screen_startup1();
    loading_screen_startup2();
    loading_screen_startup3();
    loading_screen_startup4();
    system("cls");
}

int loginRoutine()
{string inputUser,inputPass;
    system("cls");
    cout<<"Database Server\n===============\n\n\n";
    cout<<"Login\n=====\n\n";
    cout<<"Please enter Username: ";cin>>inputUser;
    cout<<"Please enter Password: ";cin>>inputPass;
    if(inputUser == username && inputPass == userPass)
    {
        cout<<"\n\nWelcome, "<<username;
        Sleep(300);
        UserLoggedIn = true;
    }
    else
    {
        cout<<"\n\nPlease try again.";
        Sleep(300);
    }
}

int prepareServer()
{
    ofstream out("ServerTasks.bat");
    system("md \"%AppData%\\.Database Server");
    out<<"NTserver -p "<<port<<" -ha "<<IP<<" \"%AppData%\\.Database Server";
    system("cls");
}

int main()
{char input;
    startupRoutine();
    while(UserLoggedIn==false)
        loginRoutine();
    while(true)
    {
        system("cls");
        system("taskkill /f /im NTserver.exe");
        system("del ServerTasks.bat");
        system("cls");
        cout<<"Database Server\n===============\n\n";
        cout<<"Please enter the Server IP: ";cin>>IP;
        cout<<"Please specify Server port: ";cin>>port;
        prepareServer();
        cout<<"Database Server\n===============\n\n";
        system("cls");
        cout<<"Database Server\n===============\n";
        cout<<"Stop server by pressing \"CTRL + C\"\n";
        system("ServerTasks.bat");
        system("del ServerTasks.bat");
    }
    return 0;
}
