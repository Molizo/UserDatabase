#include <iostream>
#include <fstream>
#include <windows.h>
#include <iomanip>
#include <algorithm>
#include <string>
#define filename "Users.cab"
#define productKey "AB1280CD0468EFRT"

using namespace std;
int userCount=0,loginUser,domainUserCount=0,domainLoginUserID;
bool localLogin = true;

struct domainUsers
{
    string username,password;
    int permissionLevel;
};
domainUsers domain[1000];

struct settings
{
    int foregroundColor,backroundColor;
    int autosave,importOnStartup,autoLogin;
    string userPassword,username;
    string serverIP,serverPort;int enableNetworking,inboundTransfer,outboundTransfer;
    int firstRun;
};
settings setting;

int ftpScript(int n)
{
    ofstream out("FTP.txt");
    out<<"open "<<setting.serverIP<<" "<<setting.serverPort<<"\n";
    if(n%10 == 1)  out<<"get "<<filename<<"\n";
    if(n%10 == 2)  out<<"send "<<filename<<"\n";
    if(n == 31 || n == 32)  out<<"disconnect\nquit\n";
}

int getUsersFromDomain()
{
    domainUserCount = 0;
    ofstream out("FTP.txt");
    out<<"open "<<setting.serverIP<<" "<<setting.serverPort<<"\nget Users.crt\ndisconnect\nquit";
    out.close();
    system("ftp /s:FTP.txt /A");
    system("del FTP.txt");
    ifstream in("Users.crt");
    while(in>>domain[domainUserCount].username)
    {
        in>>domain[domainUserCount].password;
        in>>domain[domainUserCount].permissionLevel;
        domainUserCount++;
    }
    in.close();
    system("del Users.crt");
}

int changeUser()
{string input,input2,input3;
    ofstream out("Settings.ini");
    cout<<"\n Please enter the current username: ";cin>>input;
    cout<<"\n Please enter a new username: ";cin>>input2;
    cout<<"\n Please repeat the username: ";cin>>input3;
    if(input2 == input3 && input == setting.username)
    {
        setting.username = input2;
        cout<<"\n\n Username changed succesfully\n";
        system("pause");
        system("cls");
        out<<setting.firstRun<<" "<<setting.foregroundColor<<" "<<setting.backroundColor<<" "<<setting.autosave<<" "<<setting.importOnStartup<<" "<<setting.username<<" "<<setting.userPassword<<" "<<setting.autoLogin<<" "<<setting.enableNetworking<<" "<<setting.inboundTransfer<<" "<<setting.outboundTransfer<<" "<<setting.serverIP<<" "<<setting.serverPort;
    }
    else
    {
        cout<<"\n\n Username not correct.Please try again\n";
        system("pause");
        system("cls");
    }
}

int changePassw()
{string input,input2,input3;
    ofstream out("Settings.ini");
    cout<<"\n Please enter the current password: ";cin>>input;
    cout<<"\n Please enter a new password: ";cin>>input2;
    cout<<"\n Please repeat the password: ";cin>>input3;
    if(input2 == input3 && input == setting.userPassword)
    {
        setting.userPassword = input2;
        cout<<"\n\n Password changed succesfully\n";
        system("pause");
        system("cls");
        out<<setting.firstRun<<" "<<setting.foregroundColor<<" "<<setting.backroundColor<<" "<<setting.autosave<<" "<<setting.importOnStartup<<" "<<setting.username<<" "<<setting.userPassword<<" "<<setting.autoLogin<<" "<<setting.enableNetworking<<" "<<setting.inboundTransfer<<" "<<setting.outboundTransfer<<" "<<setting.serverIP;
    }
    else
    {
        cout<<"\n\n Password not correct.Please try again\n";
        system("pause");
        system("cls");
    }
}


int settingsimport()
{
    ifstream in("Settings.ini");
    in>>setting.firstRun>>setting.foregroundColor>>setting.backroundColor>>setting.autosave>>setting.importOnStartup>>setting.username>>setting.userPassword>>setting.autoLogin>>setting.enableNetworking>>setting.inboundTransfer>>setting.outboundTransfer>>setting.serverIP>>setting.serverPort;
}

int screenColor(int en)
{
    if(en==0)
    {
        cout<<"\n Foreground Color: ";cin>>setting.foregroundColor;
        cout<<"\n Background Color: ";cin>>setting.backroundColor;
    }
    int f=setting.foregroundColor,b=setting.backroundColor;
    if(f==0)
    {
        if(b==0)    system("color 00");
        if(b==1)    system("color 01");
        if(b==2)    system("color 02");
        if(b==3)    system("color 03");
        if(b==4)    system("color 04");
        if(b==5)    system("color 05");
        if(b==6)    system("color 06");
        if(b==7)    system("color 07");
        if(b==8)    system("color 08");
        if(b==9)    system("color 09");
        if(b==10)     system("color 0F");
    }
    if(f==1)
    {
        if(b==0)    system("color 10");
        if(b==1)    system("color 11");
        if(b==2)    system("color 12");
        if(b==3)    system("color 13");
        if(b==4)    system("color 14");
        if(b==5)    system("color 15");
        if(b==6)    system("color 16");
        if(b==7)    system("color 17");
        if(b==8)    system("color 18");
        if(b==9)    system("color 19");
        if(b==10)     system("color 1F");
    }
    if(f==2)
    {
        if(b==0)    system("color 20");
        if(b==1)    system("color 21");
        if(b==2)    system("color 22");
        if(b==3)    system("color 23");
        if(b==4)    system("color 24");
        if(b==5)    system("color 25");
        if(b==6)    system("color 26");
        if(b==7)    system("color 27");
        if(b==8)    system("color 28");
        if(b==9)    system("color 29");
        if(b==10)     system("color 2F");
    }
    if(f==3)
    {
        if(b==0)    system("color 30");
        if(b==1)    system("color 31");
        if(b==2)    system("color 32");
        if(b==3)    system("color 33");
        if(b==4)    system("color 34");
        if(b==5)    system("color 35");
        if(b==6)    system("color 36");
        if(b==7)    system("color 37");
        if(b==8)    system("color 38");
        if(b==9)    system("color 39");
        if(b==10)     system("color 3F");
    }
    if(f==4)
    {
        if(b==0)    system("color 40");
        if(b==1)    system("color 41");
        if(b==2)    system("color 42");
        if(b==3)    system("color 43");
        if(b==4)    system("color 44");
        if(b==5)    system("color 45");
        if(b==6)    system("color 46");
        if(b==7)    system("color 47");
        if(b==8)    system("color 48");
        if(b==9)    system("color 49");
        if(b==10)     system("color 4F");
    }
    if(f==5)
    {
        if(b==0)    system("color 50");
        if(b==1)    system("color 51");
        if(b==2)    system("color 52");
        if(b==3)    system("color 53");
        if(b==4)    system("color 54");
        if(b==5)    system("color 55");
        if(b==6)    system("color 56");
        if(b==7)    system("color 57");
        if(b==8)    system("color 58");
        if(b==9)    system("color 59");
        if(b==10)     system("color 5F");
    }
    if(f==6)
    {
        if(b==0)    system("color 60");
        if(b==1)    system("color 61");
        if(b==2)    system("color 62");
        if(b==3)    system("color 63");
        if(b==4)    system("color 64");
        if(b==5)    system("color 65");
        if(b==6)    system("color 66");
        if(b==7)    system("color 67");
        if(b==8)    system("color 68");
        if(b==9)    system("color 69");
        if(b==10)     system("color 6F");
    }
    if(f==7)
    {
        if(b==0)    system("color 70");
        if(b==1)    system("color 71");
        if(b==2)    system("color 72");
        if(b==3)    system("color 73");
        if(b==4)    system("color 74");
        if(b==5)    system("color 75");
        if(b==6)    system("color 76");
        if(b==7)    system("color 77");
        if(b==8)    system("color 78");
        if(b==9)    system("color 79");
        if(b==10)     system("color 7F");
    }
    if(f==8)
    {
        if(b==0)    system("color 80");
        if(b==1)    system("color 81");
        if(b==2)    system("color 82");
        if(b==3)    system("color 83");
        if(b==4)    system("color 84");
        if(b==5)    system("color 85");
        if(b==6)    system("color 86");
        if(b==7)    system("color 87");
        if(b==8)    system("color 88");
        if(b==9)    system("color 89");
        if(b==10)     system("color 8F");
    }
    if(f==9)
    {
        if(b==0)    system("color 90");
        if(b==1)    system("color 91");
        if(b==2)    system("color 92");
        if(b==3)    system("color 93");
        if(b==4)    system("color 94");
        if(b==5)    system("color 95");
        if(b==6)    system("color 96");
        if(b==7)    system("color 97");
        if(b==8)    system("color 98");
        if(b==9)    system("color 99");
        if(b==10)     system("color 9F");
    }
    if(f==10)
    {
        if(b==0)    system("color F0");
        if(b==1)    system("color F1");
        if(b==2)    system("color F2");
        if(b==3)    system("color F3");
        if(b==4)    system("color F4");
        if(b==5)    system("color F5");
        if(b==6)    system("color F6");
        if(b==7)    system("color F7");
        if(b==8)    system("color F8");
        if(b==9)    system("color F9");
        if(b==10)     system("color FF");
    }
    if(en==0)
    {
        cout<<"\n\nSettings were succesfully applied.";
        Sleep(500);
        system("cls");
    }
}

int autosaveConf()
{char input;
    cout<<"\n\n Enable Autosave? (Yes/No) ";cin>>input;
    if(input == 'y' || input == 'Y')
        setting.autosave = 1;
    else
        setting.autosave = 0;
    system("cls");
}

int networkingConf()
{
    char input;
    cout<<"\n\n Enable Networking? (Yes/No) ";cin>>input;
    if(input == 'y' || input == 'Y')
        setting.enableNetworking = 1;
    else
        setting.enableNetworking = 0;
    system("cls");
}

int outboundTransferConf()
{
    char input;
    cout<<"\n You must have Networking enabled to use this feature\n Enable Outbound Transfers? (Yes/No) ";cin>>input;
    if(input == 'y' || input == 'Y')
        setting.outboundTransfer = 1;
    else
        setting.outboundTransfer = 0;
    system("cls");
}

int inboundTransferConf()
{
    char input;
    cout<<"\n You must have Networking enabled to use this feature\n Enable Inbound Transfers? (Yes/No) ";cin>>input;
    if(input == 'y' || input == 'Y')
        setting.inboundTransfer = 1;
    else
        setting.inboundTransfer = 0;
    system("cls");
}

int importOnStartupConf()
{char input;
    cout<<"\n\n Enable import on Startup? (Yes/No) ";cin>>input;
    if(input == 'y' || input == 'Y')
        setting.importOnStartup = 1;
    else
        setting.importOnStartup = 0;
    system("cls");
}

int autoLoginConf()
{char input;
    cout<<"\n\n Enable Automatic Login on Startup? (Yes/No) ";cin>>input;
    if(input == 'y' || input == 'Y')
        setting.autoLogin = 1;
    else
        setting.autoLogin = 0;
    system("cls");

}

int domainChangeLogin(int a)
{string username,password;
    getUsersFromDomain();
    system("cls");
    ofstream out("Users.crt");
    ofstream ftp("FTP.txt");
    if(a == 0) ///If it is a Username Change
    {
        cout<<"\n\nPlease enter a new Username: ";cin>>username;
        for(int i=0;i<domainUserCount;i++)
        {
            if(i == domainLoginUserID)  out<<username<<" "<<domain[i].password<<" "<<domain[i].permissionLevel<<"\n";
            else out<<domain[i].username<<" "<<domain[i].password<<" "<<domain[i].permissionLevel<<"\n";
        }
    }
    else ///If it is a Password Change
    {
        cout<<"\n\nPlease enter a new Password: ";cin>>password;
        for(int i=0;i<domainUserCount;i++)
        {
            if(i == domainLoginUserID)  out<<domain[i].username<<" "<<password<<" "<<domain[i].permissionLevel<<"\n";
            else out<<domain[i].username<<" "<<domain[i].password<<" "<<domain[i].permissionLevel<<"\n";
        }
    }
    ftp<<"open "<<setting.serverIP<<" "<<setting.serverPort<<"\nsend Users.crt\ndisconnect\nquit";
    ftp.close();
    out.close();
    system("ftp /s:FTP.txt /A");
    system("del Users.crt");
    system("del FTP.txt");
    system("cls");
}

int settingMenu()
{int input;
    ofstream out("Settings.ini");
    system("cls");
    while(true)
    {
        cout<<"Microsoft Windows Control Panel\n===============================\n\n";
        cout<<"  1.Get information on screen colours\n";
        cout<<"  2.Change screen colours\n";
        cout<<"  3.Enable import on Startup\n";
        cout<<"  4.Enable Autosave\n";
        cout<<"  5.Enable Automatic Login on Startup\n";
        cout<<"  6.Enable Networking\n";
        cout<<"  7.Enable Outbound Transfers\n";
        cout<<"  8.Enable Inbound Transfers\n";
        cout<<"  9.Change Server IP & Port\n";
        cout<<"  10.Change Username\n";
        cout<<"  11.Change Password\n";
        cout<<"  12.Go back\n";
        cout<<"\n\nYour choice: ";cin>>input;
        if(input==1)
        {
            system("cls");
            cout<<"Microsoft Windows Control Panel\n=================================\n\n";
            cout<<"  0 - BLACK\n  1 - BLUE\n  2 - GREEN\n  3 - AQUA\n  4 - RED\n  5 - PURPLE\n  6 - YELLOW\n  7 - WHITE\n  8 - GRAY\n  9 - LIGHT BLUE\n  10 - BRIGHT WHITE\n\n";
            system("pause");
            system("cls");
        }
        if(input==2)    screenColor(0);
        if(input==3)    importOnStartupConf();
        if(input==4)    autosaveConf();
        if(input==5)    autoLoginConf();
        if(input==6)    networkingConf();
        if(input==7)    outboundTransferConf();
        if(input==8)    inboundTransferConf();
        if(input==9)
        {
            cout<<"\n\n Please enter the Server IP: ";
            cin>>setting.serverIP;
            cout<<"\n\n Please enter the Server Port: ";
            cin>>setting.serverPort;
            system("cls");
        }
        if(input==10)
        {
            if(localLogin == true)
            {
                cout<<"Now changing Local Restricted Account Username.";
                changeUser();
            }
            else    domainChangeLogin(0);
        }
        if(input==11)
        {
            if(localLogin == true)
            {
                cout<<"Now changing Local Restricted Account Password.";
                changePassw();
            }
            else    domainChangeLogin(1);
        }
        if(input==12)   break;
    }
    out<<setting.firstRun<<" "<<setting.foregroundColor<<" "<<setting.backroundColor<<" "<<setting.autosave<<" "<<setting.importOnStartup<<" "<<setting.username<<" "<<setting.userPassword<<" "<<setting.autoLogin<<" "<<setting.enableNetworking<<" "<<setting.inboundTransfer<<" "<<setting.outboundTransfer<<" "<<setting.serverIP;
}

int loading_screen(int n)
{
    for(int i=0; i<=14; i++)
        cout<<"\n";
    cout<<"LOADING... \n";
    for(int i=0; i<n; i++)
    {
        cout<<"|";
        Sleep(25+i*2);
    }
    system("cls");
}

int loading_screen_addUser()
{
    for(int i=0; i<=10; i++)
        cout<<"\n";
    cout<<"Adding User... \n";
    for(int i=0; i<75; i++)
    {
        cout<<"|";
        Sleep(10+i%2);
    }
    cout<<"\n\nUsers were saved succesfully";
    Sleep(750);
    system("cls");
}

int loading_screen_logout()
{
    system("cls");
    for(int i=0; i<=19; i++)
        cout<<"\n";
    cout<<"Logging Out... \n";
    for(int i=0; i<75; i++)
    {
        cout<<"|";
        Sleep(10+i%2);
    }
    cout<<"\n\nSettings were saved succesfully";
    Sleep(750);
    system("cls");
}

int loading_screen_fileOperations()
{
    system("cls");
    for(int i=0; i<=19; i++)
        cout<<"\n";
    cout<<"Processing File Operations... \n";
    for(int i=0; i<75; i++)
    {
        cout<<"|";
        Sleep(10+i%2);
    }
    cout<<"\n\nFile Operations completed succesfully";
    Sleep(750);
    system("cls");
}

int loading_screen_setup()
{
    system("cls");
    cout<<"Microsoft Windows People Database Setup\n======================================= \n\n";
    for(int i=0;i<=17;i++)  cout<<"\n";
    cout<<"Setup is copying files...\n";
    for(int i=0; i<75; i++)
    {
        cout<<"|";
        Sleep(10+i%2);
    }
}

int networkLogin()
{string input,input2;bool exist = false;
    getUsersFromDomain();
    system("cls");
    cout<<"Microsoft Windows Autentification Protocol\n========================================== \n\n";
    cout<<"\nPlease enter Username: ";
    cin>>input;
    for(int i=0;i<domainUserCount;i++)
    {
        if(input == domain[i].username)
        {
            exist = true;
            cout<<"Please enter Password: ";
            cin>>input2;
            if(input2 == domain[i].password)
            {
                if(domain[i].permissionLevel == 0)
                    loginUser = 0;
                else
                    loginUser = 1;
                system("cls");
                cout<<"Microsoft Windows Autentification Protocol\n========================================== \n\n";
                cout<<"Welcome, "<<domain[i].username<<"!";
                domainLoginUserID = i;
                localLogin = false;
                loading_screen(75);
            }
            else
            {
                cout<<"\n\nError 303: Password for specified User is not correct.\n";
                Sleep(250);
                cout<<"Please try again.\n";
                system("pause");
                loginUser = -1;
            }
        }
    }
    if(exist == false)
    {
        cout<<"\n\nError 404: User not found on Domain.\n";
        Sleep(250);
        cout<<"Please try again.\n";
        system("pause");
        loginUser = -1;
    }
}

int login()
{
    string input;char input2;
    while(true)
    {
        system("cls");
        cout<<"Microsoft Windows Autentification Protocol\n========================================== \n\n";
        if(setting.enableNetworking == 1)
        {
            cout<<"Connect locally or via the Server? (Local/Server) ";
            cin>>input2;
        }
        else    input2 = 'l';
        if(input2 == 'l' || input2 == 'L')
        {
            system("cls");
            cout<<"Microsoft Windows Autentification Protocol\n========================================== \n\n";
            cout<<"\nPlease enter username: ";
            cin>>input;
            if(input==setting.username)
            {
                cout<<"Please enter password: ";
                cin>>input;
                cout<<"\n";
                if(input==setting.userPassword)
                {
                    system("cls");
                    cout<<"Microsoft Windows Autentification Protocol\n========================================== \n\n";
                    cout<<"Welcome, "<<setting.username<<"!\n";
                    loading_screen(75);
                    loginUser=1;
                    localLogin = false;
                    break;
                }
                else
                {
                    cout<<"303 Error: Password incorrect for specified user.\n\n";
                    Sleep(250);
                    cout<<"Please try again.\n\n\n";
                    system("pause");
                }
            }
            else if(input=="Administrator")
            {
                cout<<"Please enter password: ";
                cin>>input;
                cout<<"\n";
                if(input=="admin")
                {
                    system("cls");
                    cout<<"Microsoft Windows Autentification Protocol\n========================================== \n\n";
                    cout<<"Welcome, Administrator!";
                    loading_screen(75);
                    loginUser=0;
                    localLogin = false;
                    break;
                }
                else
                {
                    cout<<"303 Error: Password incorrect for specified user.\n\n";
                    Sleep(250);
                    cout<<"Please try again.\n\n\n";
                    system("pause");
                }
            }
            else if(input == "Safe")
            {
                loginUser=2;
                break;
            }
            else
            {
                cout<<"404 Error: User does not exist.\n\n";
                Sleep(250);
                cout<<"Please try again.\n\n\n";
                system("pause");
            }
        }
        else if(setting.enableNetworking == 1)
        {
            networkLogin();
            if(loginUser != -1)
                break;
        }
        else
        {
            cout<<"203 Error: Networking disabled by Administrator.\n\n";
            Sleep(250);
            cout<<"Please Login Locally.\n\n\n";
            system("pause");
        }
    }
}

struct UserDetails
{
    string FirstName,LastName;
    string ID;
};
UserDetails user[1000];

int importUser()
{string input,input2,input3;int userAddCounter=0;
    ifstream in(filename);
    for(int i=0;i<11;i++)   in>>input;
    for(int i=0;i<1000;i++)
    {
        user[i].FirstName = "";
        user[i].LastName = "";
        user[i].ID = "";
    }
    while(in>>input)
    {
        in>>input2;
        in>>input3;
        user[userAddCounter].FirstName = input;
        user[userAddCounter].LastName = input2;
        user[userAddCounter].ID = input3;
        userAddCounter++;
    }
    userCount = userAddCounter;
}

int exportToConsole()
{
    system("cls");
    cout<<"Microsoft Windows People Database\n================================= \n\n";
    cout<<"First Name  Second Name     ID \n=============================== \n";
    for(int i=0; i<=userCount; i++)
        cout<<left<<setw(12)<<user[i].FirstName<<setw(13)<<user[i].LastName<<setw(5)<<user[i].ID<<"\n";
    system("pause");
}

int exportToFile(int en)
{char input;
    if(en == 1)
    {
        exportToConsole();
        cout<<"\n\n\nThe following user data is going to be exported.\nContinue? (Yes/No) ";
        cin>>input;
    }
    else
        input='y';
    if(input=='y'|| input=='Y')
    {
        system("cls");
        ofstream fout(filename);
        fout<<"Microsoft Windows People Database\n================================= \n\n";
        fout<<"First Name  Second Name     ID \n=============================== \n";
        for(int i=0; i<=userCount; i++)
            fout<<left<<setw(12)<<user[i].FirstName<<setw(13)<<user[i].LastName<<setw(5)<<user[i].ID<<"\n";
        if(en == 1)    loading_screen_fileOperations();
    }
    else
        system("cls");
}

int importFromFile(int en)
{
    char choice;
    int UserAddCounter=0;
    ifstream fin(filename);
    if(en == 1)
    {
        exportToConsole();
        cout<<"\n\n\n\nThe following users are currently in the Database.\nContinue importing? (Yes/No) ";
        cin>>choice;
    }
    else
        choice = 'y';
    if(choice=='y'|| choice=='Y')
    {
        string FrNm,LsNm,ID;int overwrite = 0,temp;
        loading_screen_fileOperations();
        for(int i=1;i<=11;i++)  fin>>ID;
        while(fin>>FrNm)
        {
            fin>>LsNm>>ID;
            for(int i=0;i<=userCount;i++)
            {
                if(ID == user[i].ID)
                {
                    overwrite = 1;
                    temp=i;
                }
            }
            if(overwrite == 1 && en == 1)
            {
                char input;
                cout<<"ATTENTION!\nUser with same data has been found.\nOverwrite? (Yes/No/All) ";cin>>input;
                if(input == 'y' || input == 'Y')
                {
                    user[temp].FirstName = FrNm;
                    user[temp].LastName = LsNm;
                    user[temp].ID = ID;
                    overwrite = 0;
                }
                else if(input == 'a' || input == 'A')
                {
                    user[temp].FirstName = FrNm;
                    user[temp].LastName = LsNm;
                    user[temp].ID = ID;
                }
            }
            if(overwrite == 0 && en == 1)
            {
                user[userCount].FirstName = FrNm;
                user[userCount].LastName = LsNm;
                user[userCount].ID = ID;
                UserAddCounter++;
                userCount++;
            }
            if(overwrite == 1 && en == 0)
            {
                user[temp].FirstName = FrNm;
                user[temp].LastName = LsNm;
                user[temp].ID = ID;
                overwrite = 0;
            }
        }
        if(en==1)
        {
            cout<<"\n\n\n\n\n\n\n\n\n\n\n"<<UserAddCounter<<" users were added to the Database";
            Sleep(750);
            loading_screen_fileOperations();
            exportToConsole();
            cout<<"\n\n\n\nImport of users to Database finished.\n";
            system("pause");
        }
    }
}

int addUser()
{
    if(setting.enableNetworking == 1 && setting.inboundTransfer == 1)
    {
        ftpScript(31);
        system("ftp /s:FTP.txt /A");
        importUser();
        system("del FTP.txt");
        system("cls");
    }
    system("cls");
    cout<<"Microsoft Windows People Database\n================================= \n\n";
    cout<<"   First Name: ";
    cin>>user[userCount].FirstName;
    cout<<"\n";
    cout<<"   Last Name: ";
    cin>>user[userCount].LastName;
    cout<<"\n";
    cout<<"   ID: ";
    cin>>user[userCount].ID;
    cout<<"\n";
    userCount++;
    loading_screen_addUser();
    if(setting.enableNetworking == 1 && setting.outboundTransfer == 1)
    {
        exportToFile(2);
        ftpScript(32);
        system("ftp /s:FTP.txt /A");
        system("del FTP.txt");
        system("cls");
    }
}

bool FLID(UserDetails a,UserDetails b)
{
    return a.FirstName > b.FirstName || (a.FirstName == b.FirstName && a.LastName > b.LastName) || (a.FirstName == b.FirstName && a.LastName == b.LastName && a.ID > b.ID);
}
bool LFID(UserDetails a,UserDetails b)
{
    return a.LastName > b.LastName || (a.LastName == b.LastName && a.FirstName > b.FirstName) || (a.LastName == b.LastName && a.FirstName == b.FirstName && a.ID > b.ID);
}
bool IDFL(UserDetails a,UserDetails b)
{
    return a.ID > b.ID || (a.ID == b.ID && a.FirstName > b.FirstName) || (a.ID == b.ID && a.FirstName == b.FirstName && a.LastName > b.LastName);
}
bool IDLF(UserDetails a,UserDetails b)
{
    return a.ID > b.ID || (a.ID == b.ID && a.LastName > b.LastName) || (a.ID == b.ID && a.LastName == b.LastName && a.FirstName > b.FirstName);
}
bool FIDL(UserDetails a,UserDetails b)
{
    return a.FirstName > b.FirstName || (a.FirstName == b.FirstName && a.ID > b.ID) || (a.FirstName == b.FirstName && a.ID == b.ID && a.LastName > b.LastName);
}
bool LIDF(UserDetails a,UserDetails b)
{
    return a.LastName > b.LastName || (a.LastName == b.LastName && a.ID > b.ID) || (a.LastName == b.LastName && a.ID == b.ID && a.FirstName > b.FirstName);
}

int userSort()
{
    int input,input2,input3;
    while(true)
    {
        if(setting.enableNetworking == 1 && setting.inboundTransfer == 1)
        {
            ftpScript(31);
            system("ftp /s:FTP.txt /A");
            importUser();
            system("del FTP.txt");
            system("cls");
        }
        system("cls");
        cout<<"Microsoft Windows People Database\n================================= \n\n";
        cout<<"  1.Sort Users by First Name\n";
        cout<<"  2.Sort Users by Last Name\n";
        cout<<"  3.Sort Users by ID\n";
        cout<<"  4.Go back\n";
        cout<<"\n\n\n\n\nYour choice: ";
        cin>>input;
        if(input==1)
        {
            system("cls");
            cout<<"Microsoft Windows People Database\n================================= \n\n";
            cout<<"  1.Sort Users in descending order\n";
            cout<<"  2.Sort Users in ascending order\n";
            cout<<"  3.Go back\n";
            cout<<"\n\n\n\n\nYour choice: ";
            cin>>input2;
            if(input2==1)
            {
                system("cls");
                cout<<"Microsoft Windows People Database\n================================= \n\n";
                cout<<"  1.Sort Users secondly by Last Name\n";
                cout<<"  2.Sort Users secondly by ID\n";
                cout<<"  3.Go back\n";
                cout<<"\n\n\n\n\nYour choice: ";
                cin>>input3;
                if(input3==1)
                {
                    sort(user,user+userCount,FLID);
                    break;

                }
                if(input3==2)
                {
                    sort(user,user+userCount,FIDL);
                    break;
                }
                else
                    break;
            }
            if(input2==2)
            {
                system("cls");
                cout<<"Microsoft Windows People Database\n================================= \n\n";
                cout<<"  1.Sort Users secondly by Last Name\n";
                cout<<"  2.Sort Users secondly by ID\n";
                cout<<"  3.Go back\n";
                cout<<"\n\n\n\n\nYour choice: ";
                cin>>input3;
                if(input3==1)
                {
                    sort(user+userCount,user,FLID);
                    break;
                }
                if(input3==2)
                {
                    sort(user+userCount,user,FIDL);
                    break;
                }
                else
                    break;
            }
            else
                break;
        }
        if(input==2)
        {
            system("cls");
            cout<<"Microsoft Windows People Database\n================================= \n\n";
            cout<<"  1.Sort Users in descending order\n";
            cout<<"  2.Sort Users in ascending order\n";
            cout<<"  3.Go back\n";
            cout<<"\n\n\n\n\nYour choice: ";
            cin>>input2;
            if(input2==1)
            {
                system("cls");
                cout<<"Microsoft Windows People Database\n================================= \n\n";
                cout<<"  1.Sort Users secondly by First Name\n";
                cout<<"  2.Sort Users secondly by ID\n";
                cout<<"  3.Go back\n";
                cout<<"\n\n\n\n\nYour choice: ";
                cin>>input3;
                if(input3==1)
                {
                    sort(user,user+userCount,LFID);
                    break;
                }
                if(input3==2)
                {
                    sort(user,user+userCount,LIDF);
                    break;
                }
                else
                    break;
            }
            if(input2==2)
            {
                system("cls");
                cout<<"Microsoft Windows People Database\n================================= \n\n";
                cout<<"  1.Sort Users secondly by Last Name\n";
                cout<<"  2.Sort Users secondly by ID\n";
                cout<<"  3.Go back\n";
                cout<<"\n\n\n\n\nYour choice: ";
                cin>>input3;
                if(input3==1)
                {
                    sort(user+userCount,user,FLID);
                    break;
                }
                if(input3==2)
                {
                    sort(user+userCount,user,LIDF);
                    break;
                }
                else
                    break;
            }
            else
                break;
        }
        if(input==3)
        {
            system("cls");
            cout<<"Microsoft Windows People Database\n================================= \n\n";
            cout<<"  1.Sort Users in descending order\n";
            cout<<"  2.Sort Users in ascending order\n";
            cout<<"  3.Go back\n";
            cout<<"\n\n\n\n\nYour choice: ";
            cin>>input2;
            if(input2==1)
            {
                system("cls");
                cout<<"Microsoft Windows People Database\n================================= \n\n";
                cout<<"  1.Sort Users secondly by First Name\n";
                cout<<"  2.Sort Users secondly by Last Name\n";
                cout<<"  3.Go back\n";
                cout<<"\n\n\n\n\nYour choice: ";
                cin>>input3;
                if(input3==1)
                {
                    sort(user,user+userCount,IDFL);
                    break;
                }
                if(input3==2)
                {
                    sort(user,user+userCount,IDLF);
                    break;
                }
                else
                    break;
            }
            if(input2==2)
            {
                system("cls");
                cout<<"Microsoft Windows People Database\n================================= \n\n";
                cout<<"  1.Sort Users secondly by First Name\n";
                cout<<"  2.Sort Users secondly by Last Name\n";
                cout<<"  3.Go back\n";
                cout<<"\n\n\n\n\nYour choice: ";
                cin>>input3;
                if(input3==1)
                {
                    sort(user+userCount,user,IDFL);
                    break;
                }
                if(input3==2)
                {
                    sort(user+userCount,user,IDLF);
                    break;
                }
                else
                    break;
            }
            else
                break;
        }
        else
            break;
    }
}

int userDelete()
{char input,input2;
    if(setting.enableNetworking == 1 && setting.inboundTransfer == 1)
    {
        ftpScript(31);
        system("ftp /s:FTP.txt /A");
        importUser();
        system("del FTP.txt");
        system("cls");
    }
    cout<<"\nALL of the USER DATABASE will be ERASED!\nContinue? (Yes/No) ";cin>>input;
    if(input == 'y' || input == 'Y')
    {
        cout<<"Are you sure? (Yes/No) ";cin>>input2;
        if(input2 == 'y' || input2 == 'Y')
        {
            for(int i=0;i<1000;i++)
            {
                user[i].FirstName = "";
                user[i].LastName = "";
                user[i].ID = "";
            }
            userCount = 0;
            loading_screen_fileOperations();
        }
    }
    if(setting.enableNetworking == 1 && setting.outboundTransfer == 1)
    {
        exportToFile(0);
        ftpScript(32);
        system("ftp /s:FTP.txt /A");
        system("del FTP.txt");
        system("cls");
    }
}

int user_Administrator()
{
    int menuOption;
    system("cls");
    cout<<"Microsoft Windows People Database\n================================= \n   ";
    system("echo %date% %time%");
    cout<<"\n\n";
    cout<<"   1.Add People to Database\n";
    cout<<"   2.Export Users to file\n";
    cout<<"   3.Import Users from file\n";
    cout<<"   4.Show Users to console\n";
    cout<<"   5.Sort User list\n";
    cout<<"   6.Delete All Users\n";
    cout<<"   7.Change Settings\n";
    cout<<"   8.Edit Server files\n";
    cout<<"   9.Log out of Database\n";
    cout<<"   10.Exit Database\n";
    cout<<"\n\n\n\n\n\n\n\nYour choice: ";
    cin>>menuOption;
    if(menuOption == 1) addUser();
    if(menuOption == 2) exportToFile(1);
    if(menuOption == 3) importFromFile(1);
    if(menuOption == 4)
    {
        if(setting.enableNetworking == 1 && setting.inboundTransfer == 1)
        {
            ftpScript(31);
            system("ftp /s:FTP.txt /A");
            importUser();
            system("del FTP.txt");
            system("cls");
        }
        exportToConsole();
    }
    if(menuOption == 5) userSort();
    if(menuOption == 6) userDelete();
    if(menuOption == 7) settingMenu();
    if(menuOption == 8)
    {
        ftpScript(0);
        system("cls");
        cout<<"Microsoft Windows People Database\n================================= \n   ";
        system("echo %date% %time%");
        cout<<"\n\n";
        system("ftp /s:FTP.txt /A");
        system("del FTP.txt");
    }
    if(menuOption == 9)
    {
        loading_screen_logout();
        login();
    }
    if(menuOption == 10)
    {
        system("color 0F");
        system("cls");
        if(setting.autosave == 1)
            exportToFile(0);
        if(setting.enableNetworking == 1 && setting.outboundTransfer == 1)
        {
            exportToFile(0);
            ftpScript(32);
            system("ftp /s:FTP.txt /A");
            system("del FTP.txt");
        }
        exit(0);
    }

}

int user_Restricted()
{
    int menuOption;
    system("cls");
    cout<<"Microsoft Windows People Database\n================================= \n   ";
    system("echo %date% %time%");
    cout<<"\n\n";
    cout<<"   1.Add People to Database\n";
    cout<<"   2.Export Users to file\n";
    cout<<"   3.Show Users to console\n";
    cout<<"   4.Sort User list\n";
    cout<<"   5.Change Username\n";
    cout<<"   6.Change Password\n";
    cout<<"   7.Log out of Database\n";
    cout<<"   8.Exit Database\n";
    cout<<"\n\n\n\n\n\n\n\n\nYour choice: ";
    cin>>menuOption;
    if(menuOption == 1) addUser();
    if(menuOption == 2) exportToFile(1);
    if(menuOption == 3)
    {
        if(setting.enableNetworking == 1 && setting.inboundTransfer == 1)
        {
            ftpScript(31);
            system("ftp /s:FTP.txt /A");
            importUser();
            system("del FTP.txt");
            system("cls");
        }
        exportToConsole();
    }
    if(menuOption == 4) userSort();
    if(menuOption == 5)
    {
        if(localLogin == true)  changeUser();
        else    domainChangeLogin(0);
    }
    if(menuOption == 6)
    {
        if(localLogin == true)  changePassw();
        else    domainChangeLogin(1);
    }
    if(menuOption == 7)
    {
        loading_screen_logout();
        login();
    }
    if(menuOption == 8)
    {
        system("color 0F");
        system("cls");
        if(setting.autosave == 1)
            exportToFile(0);
        if(setting.enableNetworking == 1 && setting.outboundTransfer == 1)
        {
            exportToFile(0);
            ftpScript(32);
            system("ftp /s:FTP.txt /A");
            system("del FTP.txt");
        }
        exit(0);
    }
}

int SafeMode()
{
    int menuOption;
    while(true)
    {
        if(setting.enableNetworking == 1 && setting.inboundTransfer == 1)
        {
            ftpScript(31);
            system("ftp /s:FTP.txt /A");
            importUser();
            system("del FTP.txt");
            system("cls");
        }
        system("color CF");
        system("cls");
        cout<<"Safe Mode\n=========\n\n";
        cout<<"  1.Exit to Command Prompt\n";
        cout<<"  2.Display System Information\n";
        cout<<"  3.Edit System Registry\n";
        cout<<"  4.Power Options\n";
        cout<<"  5.Go back to login\n";
        cout<<"  6.Exit Database\n";
        cout<<"\n\n\n\n\nYour Choice: ";
        cin>>menuOption;
        if(menuOption == 1)
        {
            system("color 0F");
            system("cls");
            cout<<"To return to the database,please type EXIT\n\n";
            system("cmd");

        }
        if(menuOption == 2)
        {
            system("color 0F");
            system("cls");
            system("systeminfo");
            system("pause");
        }
        if(menuOption == 3)
        {
            system("cls");
            system("regedit");
        }
        if(menuOption == 4)
        {
            int option;
            system("cls");
            cout<<"Power Options\n=============\n\n";
            cout<<"  1.Shutdown\n";
            cout<<"  2.Restart\n";
            cout<<"  3.Hibernate\n";
            cout<<"  4.Lock User\n";
            cout<<"  5.Remote Power Options\n";
            cout<<"  6.Go back\n";
            cout<<"\n\n\n\n\nYour Choice: ";
            cin>>option;
            if(option == 1)
                system("Shutdown.exe -s -t 00");
            if(option == 2)
                system("Shutdown.exe -r -t 00");
            if(option == 3)
                system("rundll32.exe PowrProf.dll,SetSuspendState");
            if(option == 4)
                system("Rundll32.exe User32.dll,LockWorkStation");
            if(option == 5)
                system("shutdown -i");
        }
        if(menuOption == 5)
        {
            screenColor(1);
            login();
        }
        if(menuOption == 6)
        {
            system("color 0F");
            system("cls");
            if(setting.autosave == 1)
                exportToFile(0);
            if(setting.enableNetworking == 1 && setting.outboundTransfer == 1)
            {
                exportToFile(0);
                ftpScript(32);
                system("ftp /s:FTP.txt /A");
                system("del FTP.txt");
            }
            exit(0);
        }
    }
}

int setup()
{
    system("color 1F");
    system("title Setup");
    ofstream out("Settings.ini");
    setting.firstRun=1;
    char input;string key;
    cout<<"Microsoft Windows People Database Setup\n======================================= \n";
    for(int i=0;i<9;i++)
        cout<<"\n";
    cout<<"Setup is loading files ... \n";
    Sleep(250);
    for(int i=0;i<75;i++)
    {
        cout<<"|";
        Sleep(50);
    }
    system("cls");
    cout<<"Microsoft Windows People Database Setup\n======================================= \n\n";
    cout<<"\nUser Configuration Wizard\n\n\n\n\n";
    cout<<"Please enter a login Username: ";cin>>setting.username;
    cout<<"Please enter a login Password: ";cin>>setting.userPassword;
    system("cls");
    cout<<"Microsoft Windows People Database Setup\n======================================= \n\n";
    cout<<"\nMicrosoft Product Activation\n\n\n\n\n\n\n\n\n";
    cout<<"Please enter the Product Key that came with the software:\n";cin>>key;
    if(key != productKey)
    {
        cout<<"\nProduct key invalid.\nPlease retry the installation.\n\n\n";
        system("pause");
        exit(0);
    }
    loading_screen_setup();
    system("cls");
    cout<<"Microsoft Windows People Database Setup\n======================================= \n\n";
    for(int i=0;i<=14;i++)  cout<<"\n";
    cout<<"\nOther settings can be changed by using an Administrator account.\nWould you like to configure those now? (Yes/No) ";cin>>input;
    if(input == 'y' || input == 'Y')
        settingMenu();
    cout<<"\n\nSetup completed.";
    out<<setting.firstRun<<" "<<setting.foregroundColor<<" "<<setting.backroundColor<<" "<<setting.autosave<<" "<<setting.importOnStartup<<" "<<setting.username<<" "<<setting.userPassword<<" "<<setting.autoLogin<<" "<<setting.enableNetworking<<" "<<setting.inboundTransfer<<" "<<setting.outboundTransfer<<" "<<setting.serverIP<<" "<<setting.serverPort;
    cout<<"\n";system("pause");
    system("cls");
}

int startupRoutine()
{
    system("cls");
    settingsimport();
    screenColor(1);
    if(setting.firstRun != 1)   setup();
    if(setting.importOnStartup == 1 && (setting.enableNetworking == 0 || setting.inboundTransfer == 0))    importUser();
    system("title Microsoft Windows People Database Client");
    system("attrib +h Settings.ini");
    if(setting.autoLogin == 1)  loginUser = 1;
    else    login();
}

int main()
{
    startupRoutine();
    while(true)
    {
        if(loginUser == 0)
            user_Administrator();
        if(loginUser == 1)
            user_Restricted();
        if(loginUser == 2)
            SafeMode();
    }
    return 0;
}
