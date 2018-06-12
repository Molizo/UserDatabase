#include <iostream>
#include <fstream>
#include <windows.h>
#include <ctime>
#include <string>
#include <conio.h>
#include <iomanip>
#include "wtypes.h"
#include "rlutil.h"
#define filename "Database.cab"
#define version "3.5.4 Client"
#define edition "Professional"

using namespace std;
string [1000];int fieldCount=0;
int dataCount=0;int permissionLevel;
int serverUserCount=0;bool localUser = true;
int userID;

struct serverUsers
{
    string username,userPass;
    int permissionID;
    int BackgroundColor,ForegroundColor;
    int threshold;
};
serverUsers serverUser[1000];

struct settings
{
    string title;int productID;
    string localUser,localPass;
    string serverIP;int serverPort;
    int networking,outboundTransfers,inboundTransfers;
    int BackgroundColor,ForegroundColor;
    int debug,plugins,firstRun = 0;
    string pluginExe[1000],pluginName[1000];int pluginCount = 0;
    int enableThreshold,threshold,settingsRestricted;
};
settings setting;

int settingsExport()
{
    ofstream out("DefaultSettings.ini");
    out<<setting.productID<<" "<<setting.localUser<<" "<<setting.localPass<<" "<<setting.serverIP<<" "<<setting.serverPort<<" ";
    out<<setting.networking<<" "<<setting.outboundTransfers<<" "<<setting.inboundTransfers<<" "<<setting.ForegroundColor<<" ";
    out<<setting.BackgroundColor<<" "<<setting.debug<<" "<<setting.plugins<<" "<<setting.firstRun<<" ";
    char name[setting.title.size()+1];
    strcpy(name, setting.title.c_str());
    out<<"~";
    for(int i=0;i<setting.title.size();i++)
    {
        if(name[i] == 32)
            out<<"[";
        else
            out<<name[i];
    }
    out<<"~ ";
    out.close();
    system("attrib +h DefaultSettings.ini");
}

int settingsImport()
{char temp;int counter = 0;
    ifstream in("DefaultSettings.ini");
    in>>setting.productID>>setting.localUser>>setting.localPass>>setting.serverIP>>setting.serverPort>>setting.networking;
    in>>setting.outboundTransfers>>setting.inboundTransfers>>setting.ForegroundColor>>setting.BackgroundColor>>setting.debug>>setting.plugins>>setting.firstRun;
    if(setting.firstRun == 0)
        counter = 3;
    while(counter < 3)
    {
        in>>temp;
        if(temp == '~')
            counter++;
        else if(temp == '[')
            setting.title = setting.title + ' ';
        else
            setting.title = setting.title + temp;
    }
    in.close();
}

int loadingScreen(string text)
{char ch =  219;
    system("cls");
    for(int i=0;i<23;i++)
        cout<<"\n";
    cout<<text<<" ...\n";
    rlutil::setColor(9);
    for(int i=0;i<80;i++)
    {
        cout<<ch;
        Sleep(15+(i%25)*3);
    }
    rlutil::setColor(setting.ForegroundColor);
    system("cls");
}

int title()
{
    system("cls");
    ofstream out("Services.bat");
    out<<"title "<<setting.title<<"\n";
    out.close();
    system("Services.bat");
    system("del Services.bat");
    system("cls");
    cout<<setting.title<<"\n";
    for(int i=0;i<setting.title.length();i++)
        cout<<"=";
}

int loadDefaultSettings()
{
    rlutil::setColor(setting.ForegroundColor);
    rlutil::setBackgroundColor(setting.BackgroundColor);
}

int loadPersonalizedSettings()
{
    rlutil::setColor(serverUser[userID].ForegroundColor);
    rlutil::setBackgroundColor(serverUser[userID].BackgroundColor);
    if(userID == -1)
        loadDefaultSettings;
}

int passwordCheck(string correctPass)
{string inputPassword="";char ch;
    cout<<"  Please Enter Password: ";
    while(true)
    {
        ch = getch();
        if(ch == 8 && inputPassword != "")
        {
            cout<<"\b  \b\b";
            inputPassword.resize(inputPassword.size() - 1);
        }
        else if(ch == 13)
            break;
        else if(ch == 27)
        {
            for(int i=0;i<inputPassword.size();i++)cout<<"\b";
            cout<<inputPassword;
            Sleep(25);
            for(int i=0;i<inputPassword.size();i++)cout<<"\b";
            for(int i=0;i<inputPassword.size();i++)cout<<"*";
        }
        if(ch != 8 && ch != 13 && ch != 27)
        {
            inputPassword = inputPassword + ch;
            cout<<"*";
        }
    }
    cout<<"\n\n";
    if(inputPassword == correctPass)
        return true;
    else
        return false;
}

int searchForUser(string username)
{bool found = false;
    ofstream ftp("FTP.txt");
    ftp<<"open "<<setting.serverIP<<" "<<setting.serverPort<<"\nget Login.crt\nquit";
    ftp.close();
    Sleep(250);
    system("start /min ftp /s:FTP.txt /A");
    Sleep(375);
    system("start /min del /f FTP.txt");
    system("start /min taskkill /f /im cmd.exe");
    ifstream in("Login.crt");
    while(in>>serverUser[serverUserCount].username)
    {
        in>>serverUser[serverUserCount].userPass;
        in>>serverUser[serverUserCount].permissionID;
        in>>serverUser[serverUserCount].BackgroundColor;
        in>>serverUser[serverUserCount].ForegroundColor;
        in>>serverUser[serverUserCount].threshold;
        serverUserCount++;
    }
    in.close();
    system("attrib +h Login.crt | find \"poop\"");
    for(int i=0;i<serverUserCount;i++)
    {
        if(username == serverUser[i].username)
        {
            found = true;
            return i;
            break;
        }
    }
    if(found == false)
        return -1;
}

int networkLogin()
{string username;int loginAttempts = 0;
    while(true)
    {
        if(loginAttempts % 5 == 0 && loginAttempts > 0)
        {
            system("cls");
            title();
            cout<<"\n\n\n  Login Disabled for "<<loginAttempts/2<<" minutes\n\n";
            Sleep(loginAttempts/2 * 1000 * 60);
        }
        system("cls");
        title();
        loginAttempts++;
        cout<<"\n  Login type: ";
        rlutil::setColor(14);
        cout<<"Server";
        rlutil::setColor(15);
        cout<<"\n\n  Please Enter Username: ";
        cin>>username;
        userID = searchForUser(username);
        if(userID != -1)
        {
            if(passwordCheck(serverUser[userID].userPass) == true)
            {
                system("cls");
                title();
                loadingScreen("Logging in as "+serverUser[userID].username);
                if(serverUser[userID].permissionID == 0)
                    permissionLevel = 0;
                else
                    permissionLevel = 1;
                loadPersonalizedSettings();
                break;
            }
            else
            {
                rlutil::setColor(12);
                cout<<"\n\n  Username or Password is incorrect.\n  Please try again.\n\n  ";
                rlutil::setColor(15);
                system("pause");
            }
        }
        else
        {
            rlutil::setColor(12);
            cout<<"\n\n  Username or Password is incorrect.\n  Please try again.\n\n  ";
            rlutil::setColor(15);
            system("pause");
        }
    }
}

int localLogin()
{string username;int loginAttempts = 0;
    while(true)
    {
        if(loginAttempts % 5 == 0 && loginAttempts > 0)
        {
            system("cls");
            title();
            cout<<"\n\n\n  Login Disabled for 2 minutes\n\n";
            Sleep(2 * 1000 * 60);
        }
        system("cls");
        title();
        loginAttempts++;
        cout<<"\n  Login type: ";
        rlutil::setColor(14);
        cout<<"Local";
        rlutil::setColor(15);
        cout<<"\n\n  Please Enter Username: ";
        cin>>username;
        if(username == "Administrator")
        {
            if(passwordCheck("admin") == true)
            {
                system("cls");
                title();
                loadingScreen("Logging in as Administrator");
                permissionLevel = 0;
                userID = -1;
                break;
            }
            else
            {
                rlutil::setColor(12);
                cout<<"\n\n  Username or Password is incorrect.\n  Please try again.\n\n  ";
                rlutil::setColor(15);
                system("pause");
            }
        }
        else if(username == setting.localUser)
        {
            if(passwordCheck(setting.localPass) == true)
            {
                system("cls");
                title();
                loadingScreen("Logging in as " + setting.localUser);
                userID = -1;
                permissionLevel = 1;
                break;
            }
            else
            {
                rlutil::setColor(12);
                cout<<"\n\n  Username or Password is incorrect.\n  Please try again.\n\n  ";
                rlutil::setColor(15);
                system("pause");
            }
        }
        else
        {
            rlutil::setColor(12);
            cout<<"\n\n  Username or Password is incorrect.\n  Please try again.\n\n  ";
            rlutil::setColor(15);
            system("pause");
        }
    }
}

int login()
{int loginType;
    title();
    loadDefaultSettings();
    if(setting.networking == 0)
        localLogin();
    if(setting.networking == 1)
        networkLogin();
}

int pluginAdd()
{string plugins[1000];int pluginCnt = 0,menu;
    system("md Plugins");
    system("attrib -h Plugins");
    system("cls");
    title();
    cout<<"\n\n  In order to Add a Plugin,Please Place it in the 'Plugins' Folder.\n  If you do not Add it now,you will need to restart the Wizard\n\n  ";
    cout<<"\n\n  Place the Plugins now,and after that,";
    system("pause");
    system("attrib +h Plugins");
    ofstream batch("Plugins.bat");
    batch<<"cd Plugins\n"<<"dir /b | find \".exe\" > ..\\Plugins.txt";
    batch.close();
    system("Plugins.bat");
    system("del Plugins.bat");
    ifstream in("Plugins.txt");
    while(in>>plugins[pluginCnt])
        pluginCnt++;
    in.close();
    system("del Plugins.txt");
    if(pluginCnt == 0)
    {
        title();
        cout<<"\n\n  No Plugins Found.\n  Please Restart the Wizard\n  ";
        system("pause");
        exit(0);
    }
    while(pluginCnt > 0)
    {
        system("cls");
        title();
        cout<<"\n  Please Select Plugins to Add: \n\n";
        cout<<"  1.Go back\n";
        for(int i=0;i<pluginCnt;i++)
            cout<<"  "<<i+2<<"."<<plugins[i]<<"\n";
        cout<<"\n\n  Your Choice: ";
        cin>>menu;
        if(menu == 1)
            break;
        else if(menu - 2 < pluginCnt)
        {
            setting.pluginExe[setting.pluginCount] = plugins[menu - 2];
            cout<<"\n\n  Chosen Plugin: "<<plugins[menu-2]<<"\n";
            cout<<"  Please enter a Display Name for the Plugin: ";
            cin>>setting.pluginName[setting.pluginCount];
            setting.pluginCount++;
            loadingScreen("Adding Plugin");
        }
        else
        {
            cout<<"\n  Please Select Valid option\n  ";
            system("pause");
        }
    }
    system("attrib -h plgdt.cfg | find \"poop\"");
    ofstream plg("plgdt.cfg");
    plg<<setting.pluginCount<<"\n";
    for(int i=0;i<setting.pluginCount;i++)
        plg<<setting.pluginExe[i]<<" "<<setting.pluginName[i]<<"\n";
    system("attrib +h plgdt.cfg | find \"poop\"");
}

int pluginImport()
{
    system("attrib -h plgdt.cfg | find \"poop\"");
    ifstream plg("plgdt.cfg");
    plg>>setting.pluginCount;
    for(int i=0;i<setting.pluginCount;i++)
        plg>>setting.pluginExe[i]>>setting.pluginName[i];
    plg.close();
    system("attrib +h plgdt.cfg | find \"poop\"");
}

int pluginMenu()
{int input;
    while(true)
    {
        system("cls");
        title();
        cout<<"\n  Please Select Plugin to Start: \n\n";
        cout<<"  1.Go back\n";
        for(int i=0;i<setting.pluginCount;i++)
            cout<<"  "<<i+2<<"."<<setting.pluginName[i]<<"\n";
        cout<<"\n\n  Your Choice: ";
        cin>>input;
        if(input == 1)  break;
        else if(input - 2 < setting.pluginCount)
        {
            ofstream batch("Plugins.bat");
            batch<<"echo off\n";
            batch<<"cd Plugins\n";
            batch<<"attrib -h "<<filename<<"\n";
            batch<<"attrib -h DefaultSettings.ini\n";
            batch<<"del DefaultSettings.ini\n";
            batch<<"del "<<filename<<"\n";
            batch<<"cd ..\n";
            batch<<"attrib -h "<<filename<<"\n";
            batch<<"attrib -h DefaultSettings.ini\n";
            batch<<"copy DefaultSettings.ini Plugins\\DefaultSettings.ini\n";
            batch<<"copy "<<filename<<" Plugins\\"<<filename<<"\n";
            batch<<"attrib +h "<<filename<<"\n";
            batch<<"attrib +h DefaultSettings.ini\n";
            batch<<"cd Plugins\n";
            batch<<"attrib +h "<<filename<<"\n";
            batch<<"attrib +h DefaultSettings.ini\n";
            batch<<setting.pluginExe[input-2]<<"\n";
            batch<<"echo "<<setting.title<<"\n";
            batch<<"echo ";
            for(int i=0;i<setting.title.length();i++)
                batch<<"=";
            batch.close();
            system("Plugins.bat /Q");
            system("del Plugins.bat");
            char ch;
            cout<<"\n\n  Get Data Saved by Plugin? (Yes/No) ";cin>>ch;
            if(ch == 'y' || ch == 'Y')
            {
                ofstream batch("Plugins.bat");
                batch<<"echo off\n";
                batch<<"attrib -h "<<filename<<"\n";
                batch<<"attrib -h DefaultSettings.ini\n";
                batch<<"del DefaultSettings.ini\n";
                batch<<"del "<<filename<<"\n";
                batch<<"copy Plugins\\DefaultSettings.ini DefaultSettings.ini\n";
                batch<<"copy Plugins\\"<<filename<<" "<<filename<<"\n";
                batch<<"attrib +h "<<filename<<"\n";
                batch<<"attrib +h DefaultSettings.ini\n";
                system("Plugins.bat /Q");
                system("del Plugins.bat");
            }
        }
        else
        {
            cout<<"\n  Please enter a Valid Option\n  ";
            system("pause");
        }
    }
}

struct dataFields
{
    int ID;
    string FirstName,LastName;
    string data[1000];
};
dataFields dataField[1000];

void GetDesktopResolution(int& horizontal, int& vertical)
{
   RECT desktop;
   // Get a handle to the desktop window
   const HWND hDesktop = GetDesktopWindow();
   // Get the size of screen to the variable desktop
   GetWindowRect(hDesktop, &desktop);
   // The top left corner will have coordinates (0,0)
   // and the bottom right corner will have coordinates
   // (horizontal, vertical)
   horizontal = desktop.right;
   vertical = desktop.bottom;
}

int osVersion()
{string input;
    system("ver > \Version.txt");
    ifstream in("Version.txt");
    while(in>>input)
        cout<<input<<" ";
    in.close();
    system("del Version.txt");
}

int debugInfo()
{int ScreenH,ScreenW;
    GetDesktopResolution(ScreenW,ScreenH);
    title();
    cout<<"\n\n  System Configuration Inspector\n\n";

    cout<<left<<setw(37)<<"  OS Version is   ";
    Sleep(500);
    rlutil::setColor(14);
    osVersion();
    rlutil::setColor(setting.ForegroundColor);
    cout<<"\n";
    cout<<left<<setw(63)<<"  Screen Rezolution is   ";
    Sleep(500);
    rlutil::setColor(14);
    cout<<ScreenW<<"x"<<ScreenH;
    rlutil::setColor(setting.ForegroundColor);
    cout<<"\n";
    cout<<left<<setw(63)<<"  Software Version is   ";
    Sleep(500);
    rlutil::setColor(14);
    cout<<version;
    rlutil::setColor(setting.ForegroundColor);
    cout<<"\n";
    cout<<left<<setw(63)<<"  Software Edition is   ";
    Sleep(500);
    rlutil::setColor(14);
    cout<<edition;
    rlutil::setColor(setting.ForegroundColor);
    cout<<"\n";
    cout<<left<<setw(63)<<"  Product ID is   ";
    Sleep(500);
    rlutil::setColor(14);
    cout<<setting.productID;
    rlutil::setColor(setting.ForegroundColor);
    cout<<"\n\n";

    cout<<left<<setw(63)<<"  Networking is   ";
    if(setting.networking == 0)
    {
        Sleep(750);
        rlutil::setColor(12);
        cout<<"DISABLED";
    }
    else
    {
        Sleep(500);
        rlutil::setColor(10);
        cout<<"ENABLED";
    }
    rlutil::setColor(setting.ForegroundColor);
    cout<<"\n";

    cout<<left<<setw(63)<<"  Outbound Transfers are   ";
    if(setting.outboundTransfers == 0 && setting.networking == 1)
    {
        Sleep(750);
        rlutil::setColor(12);
        cout<<"BLOCKED";
    }
    else if(setting.outboundTransfers == 1 && setting.networking == 1)
    {
        Sleep(500);
        rlutil::setColor(10);
        cout<<"UNBLOCKED";
    }
    else
    {
        Sleep(750);
        rlutil::setColor(12);
        cout<<"NOT AVALABLE";
    }
    rlutil::setColor(setting.ForegroundColor);
    cout<<"\n";

    cout<<left<<setw(63)<<"  Inbound Transfers are   ";
    if(setting.inboundTransfers == 0 && setting.networking == 1)
    {
        Sleep(750);
        rlutil::setColor(12);
        cout<<"BLOCKED";
    }
    else if(setting.inboundTransfers == 1 && setting.networking == 1)
    {
        Sleep(500);
        rlutil::setColor(10);
        cout<<"UNBLOCKED";
    }
    else
    {
        Sleep(750);
        rlutil::setColor(12);
        cout<<"NOT AVALABLE";
    }
    rlutil::setColor(setting.ForegroundColor);
    cout<<"\n";

    cout<<left<<setw(63)<<"  Server IP is   ";
    if(setting.serverIP == "" || setting.networking == 0)
    {
        Sleep(750);
        rlutil::setColor(12);
        cout<<"NOT AVALABLE";
    }
    else
    {
        Sleep(500);
        rlutil::setColor(14);
        cout<<setting.serverIP;
    }
    rlutil::setColor(setting.ForegroundColor);
    cout<<"\n";
    cout<<left<<setw(63)<<"  Server Port is   ";
    if(setting.serverPort == 0  || setting.networking == 0)
    {
        Sleep(750);
        rlutil::setColor(12);
        cout<<"NOT AVALABLE";
    }
    else
    {
        Sleep(500);
        rlutil::setColor(14);
        cout<<setting.serverPort;
    }
    rlutil::setColor(setting.ForegroundColor);
    cout<<"\n\n";

    cout<<left<<setw(63)<<"  Access to Settings for Restricted Users   ";
    if(setting.settingsRestricted == 0)
    {
        Sleep(750);
        rlutil::setColor(12);
        cout<<"DENY";
    }
    else
    {
        Sleep(500);
        rlutil::setColor(10);
        cout<<"ALLOW";
    }
    rlutil::setColor(setting.ForegroundColor);
    cout<<"\n";
    cout<<left<<setw(63)<<"  Threshold per User for Adding Data is     ";
    if(setting.enableThreshold == 0)
    {
        Sleep(750);
        rlutil::setColor(12);
        cout<<"DISABLED";
    }
    else
    {
        Sleep(500);
        rlutil::setColor(10);
        cout<<"ENABLED";
    }
    rlutil::setColor(setting.ForegroundColor);
    cout<<"\n";
    cout<<left<<setw(63)<<"  The Threshold is set to    ";
    if(setting.enableThreshold == 0  || setting.threshold == 0)
    {
        Sleep(750);
        rlutil::setColor(12);
        cout<<"NOT AVALABLE";
    }
    else
    {
        Sleep(500);
        rlutil::setColor(14);
        cout<<setting.serverPort;
    }
    rlutil::setColor(setting.ForegroundColor);
    cout<<"\n\n";

    cout<<left<<setw(63)<<"  Local Restricted Account Username is   ";
    Sleep(500);
    rlutil::setColor(14);
    cout<<setting.localUser;
    rlutil::setColor(setting.ForegroundColor);
    cout<<"\n";
    cout<<left<<setw(63)<<"  Local Restricted Account Password is   ";
    Sleep(500);
    rlutil::setColor(14);
    cout<<setting.localPass;
    rlutil::setColor(setting.ForegroundColor);
    cout<<"\n\n";

    cout<<left<<setw(63)<<"  Foreground Console Color Code is   ";
    Sleep(500);
    rlutil::setColor(14);
    cout<<setting.ForegroundColor;
    rlutil::setColor(setting.ForegroundColor);
    cout<<"\n";
    cout<<left<<setw(63)<<"  Background Console Color Code is   ";
    Sleep(500);
    rlutil::setColor(14);
    cout<<setting.BackgroundColor;
    rlutil::setColor(setting.ForegroundColor);
    cout<<"\n\n";

    cout<<left<<setw(63)<<"  Number of Additional Data Fields is   ";
    Sleep(500);
    rlutil::setColor(14);
    cout<<fieldCount;
    rlutil::setColor(setting.ForegroundColor);
    cout<<"\n";
    cout<<left<<setw(63)<<"  Additional Data Fields are   ";
    if(fieldCount == 0)
    {
        Sleep(500);
        rlutil::setColor(12);
        cout<<"NONE";
    }
    else
    {
        rlutil::setColor(14);
        Sleep(500);
        cout<<fields[0]<<"\n";
        for(int i = 1;i<fieldCount;i++)
        {
            Sleep(500);
            cout<<left<<setw(63)<<""<<fields[i]<<"\n";
        }
    }
    rlutil::setColor(setting.ForegroundColor);
    cout<<"\n";

    cout<<left<<setw(63)<<"  Plugins are    ";
    if(setting.plugins == 0)
    {
        Sleep(750);
        rlutil::setColor(12);
        cout<<"DISABLED";
    }
    else
    {
        Sleep(500);
        rlutil::setColor(10);
        cout<<"ENABLED";
    }
    rlutil::setColor(setting.ForegroundColor);
    cout<<"\n";
    cout<<left<<setw(63)<<"  Plugins currently installed are   ";
    if(setting.pluginCount == 0)
    {
        Sleep(500);
        rlutil::setColor(12);
        cout<<"NONE";
    }
    else
    {
        rlutil::setColor(14);
        Sleep(500);
        cout<<setting.pluginName[0]<<"\n";
        for(int i = 1;i<setting.pluginCount;i++)
        {
            Sleep(500);
            cout<<left<<setw(63)<<""<<setting.pluginName[i]<<"\n";
        }
    }
    rlutil::setColor(setting.ForegroundColor);
    cout<<"\n\n  ";

    system("pause");
}

int ftpBrowse()
{
    if(setting.networking == 1 && setting.inboundTransfers == 1 && setting.outboundTransfers == 1)
    {
        ofstream ftp("FTP.txt");
        ftp<<"open "<<setting.serverIP<<" "<<setting.serverPort<<"\n dir";
        ftp.close();
        system("start \"Server\" ftp /s:FTP.txt /A");
    }
    if(setting.networking == 0)
    {
        cout<<"\n Networking is ";
        rlutil::setColor(12);
        cout<<"DISABLED";
        rlutil::setColor(15);
        cout<<".";
    }
    if(setting.outboundTransfers == 0)
    {
        cout<<"\n Outbound Transfers are ";
        rlutil::setColor(12);
        cout<<"BLOCKED";
        rlutil::setColor(15);
        cout<<".";
    }
    if(setting.inboundTransfers == 0)
    {
        cout<<"\n Inbound Transfers are ";
        rlutil::setColor(12);
        cout<<"BLOCKED";
        rlutil::setColor(15);
        cout<<".";
    }
    if(setting.networking == 0 || setting.inboundTransfers == 0 || setting.outboundTransfers == 0)
    {
        cout<<"\n Please check the Configuration.\n\n ";
        system("pause");
    }
}

int sendToServer()
{
    ofstream out(filename);
    for(int i=0;i<dataCount;i++)
    {
        out<<dataField[i].ID<<" ";
        out<<dataField[i].FirstName<<" ";
        out<<dataField[i].LastName<<" ";
        for(int j=0;j<fieldCount;j++)
            out<<dataField[i].data[j]<<" ";
        out<<"\n";
    }
    out.close();
    ofstream ftp("FTP.txt");
    ftp<<"open "<<setting.serverIP<<" "<<setting.serverPort<<"\nsend "<<filename<<"\ndisconnect\nquit";
    ftp.close();
    system("start /min ftp /s:FTP.txt /A");
    loadingScreen("Sending Data");
    system("del FTP.txt");
    system("cls");
}

int getFromServer()
{
    dataField[0].ID = 0;
    dataField[0].FirstName = "";
    dataField[0].LastName = "";
    for(int i=0;i<fieldCount;i++)
        dataField[0].data[i] = "";
    while(dataCount > 0)
    {
        dataField[dataCount].ID = 0;
        dataField[dataCount].FirstName = "";
        dataField[dataCount].LastName = "";
        for(int i=0;i<fieldCount;i++)
            dataField[dataCount].data[i] = "";
        dataCount--;
    }
    ofstream out("FTP.txt");
    out<<"open "<<setting.serverIP<<" "<<setting.serverPort<<"\nget "<<filename<<"\ndisconnect\nquit";
    out.close();
    system("start /min ftp /s:FTP.txt /A");
    loadingScreen("Receiving Data");
    system("del FTP.txt");
    ifstream in(filename);
    while(in>>dataField[dataCount].ID)
    {
        in>>dataField[dataCount].FirstName;
        in>>dataField[dataCount].LastName;
        for(int i=0;i<fieldCount;i++)
            in>>dataField[dataCount].data[i];
        dataCount++;
    }
    system("cls");
}

int exportData()
{
    ofstream out(filename);
    for(int i=0;i<dataCount;i++)
    {
        out<<dataField[i].ID<<" ";
        out<<dataField[i].FirstName<<" ";
        out<<dataField[i].LastName<<" ";
        for(int j=0;j<fieldCount;j++)
            out<<dataField[i].data[j]<<" ";
        out<<"\n";
    }
    if(setting.networking == 1 && setting.outboundTransfers == 1)
        sendToServer();
}

int showData()
{
    if(setting.networking == 1 && setting.inboundTransfers == 1)
        getFromServer();
    system("cls");
    title();
    cout<<"\nID  First Name   Last Name   ";
    cout<<"\n\n";
    for(int i=0;i<dataCount;i++)
    {
        cout<<left<<setw(4)<<dataField[i].ID;
        cout<<left<<setw(13)<<dataField[i].FirstName;
        cout<<left<<setw(12)<<dataField[i].LastName;
        cout<<"\n";
    }
    cout<<"\n";
    system("pause");
}

int showDataDetail()
{int ID,menu;
    if(setting.networking == 1 && setting.inboundTransfers == 1)
        getFromServer();
    title();
    cout<<"\n";
    cout<<"  Please enter the Data ID: ";
    cin>>ID;
    cout<<"\n";
    cout<<left<<setw(60)<<"  Details";
    cout<<"Current Data\n\n";
    cout<<left<<setw(60)<<"  First Name";
    rlutil::setColor(14);
    cout<<dataField[ID].FirstName<<"\n";
    rlutil::setColor(setting.ForegroundColor);
    cout<<left<<setw(60)<<"  Last Name";
    rlutil::setColor(14);
    cout<<dataField[ID].LastName<<"\n";
    rlutil::setColor(setting.ForegroundColor);

    for(int i=0;i<fieldCount;i++)
    {
        cout<<"  "<<left<<setw(58)<<fields[i];
        rlutil::setColor(14);
        cout<<dataField[ID].data[i]<<"\n";
        rlutil::setColor(setting.ForegroundColor);
    }
    cout<<"\n\n  ";
    system("pause");
}

int addData()
{
    if(setting.networking == 1 && setting.inboundTransfers == 1)
        getFromServer();
    title();
    cout<<"\n";
    dataField[dataCount].ID = dataCount;
    cout<<"Please enter First Name: ";cin>>dataField[dataCount].FirstName;
    cout<<"Please enter Last Name: ";cin>>dataField[dataCount].LastName;
    for(int i=0;i<fieldCount;i++)
    {
        cout<<"Please enter "<<fields[i]<<": ";
        cin>>dataField[dataCount].data[i];
    }
    dataCount++;
    exportData();
}

int modifyData()
{int ID,menu;
    if(setting.networking == 1 && setting.inboundTransfers == 1)
        getFromServer();
    title();
    cout<<"\n";
    cout<<"  Please enter the Data ID: ";
    cin>>ID;
    cout<<"\n";
    cout<<left<<setw(60)<<"  Modifications";
    cout<<"Current Data\n\n";
    cout<<left<<setw(60)<<"  1.Go back";
    cout<<"\n";
    cout<<left<<setw(60)<<"  2.Modify First Name";
    rlutil::setColor(14);
    cout<<dataField[ID].FirstName<<"\n";
    rlutil::setColor(setting.ForegroundColor);
    cout<<left<<setw(60)<<"  3.Modify Last Name";
    rlutil::setColor(14);
    cout<<dataField[ID].LastName<<"\n";
    rlutil::setColor(setting.ForegroundColor);

    for(int i=0;i<fieldCount;i++)
    {
        string temp=".Modify " + fields[i];
        cout<<"  "<<i+4<<left<<setw(57)<<temp;
        rlutil::setColor(14);
        cout<<dataField[ID].data[i]<<"\n";
        rlutil::setColor(setting.ForegroundColor);
    }
    cout<<"\n\n  Your Choice: ";
    cin>>menu;
    cout<<"\n\n";
    if(menu == 1)   Sleep(0);
    else if(menu == 2)
    {
        cout<<"  Please enter First Name: ";
        cin>>dataField[ID].FirstName;
        loadingScreen("Applying Changes");
        exportData();
    }
    else if(menu == 3)
    {
        cout<<"  Please enter Last Name: ";
        cin>>dataField[ID].LastName;
        loadingScreen("Applying Changes");
        exportData();
    }
    else
    {
        cout<<"  Please enter "<<fields[menu-4]<<": ";
        cin>>dataField[ID].data[menu-4];
        loadingScreen("Applying Changes");
        exportData();
    }
}

int deleteData(int en)
{char input1,input2;
    if(en == 0)
    {
        cout<<"ALL DATA will be DELETED PERMANENTLY.\nContinue? (Yes/No) ";cin>>input1;
        cout<<"Are you sure? (Yes/No) ";cin>>input2;
    }
    else
        input1 = input2 = 'y';
    if(setting.networking == 1 && setting.inboundTransfers == 1)
        getFromServer();
    while(dataCount > 0 && (input1 == 'y' || input1 == 'Y') && (input2 == 'y' || input2 == 'Y'))
    {
        dataField[dataCount].ID = 0;
        dataField[dataCount].FirstName = "";
        dataField[dataCount].LastName = "";
        for(int i=0;i<fieldCount;i++)
            dataField[dataCount].data[i] = "";
        dataCount--;
    }
    exportData();
}

int importData()
{
    int deleteData(1);
    ifstream in(filename);
    while(in>>dataField[dataCount].ID)
    {
        in>>dataField[dataCount].FirstName;
        in>>dataField[dataCount].LastName;
        for(int i=0;i<fieldCount;i++)
            in>>dataField[dataCount].data[i];
        dataCount++;
    }
}

int quit()
{
    if(setting.networking == 1 && setting.outboundTransfers == 1)
        sendToServer();
    else
        exportData();
    settingsExport();
    exit(0);
}

int userMenu()
{int input;
    title();
    cout<<"\n\n";
    if(permissionLevel == 0)
    {
        cout<<"  1.Add Data to Database\n";
        cout<<"  2.Modify Data in Database\n";
        cout<<"  3.Show List of Data in Database\n";
        cout<<"  4.Show Detailed Data Information\n";
        cout<<"  5.Refresh Database\n";
        cout<<"  6.Save Database\n";
        cout<<"  7.Delete Database\n";
        cout<<"  8.Browse Server Files\n";
        cout<<"  9.Log out\n";
        cout<<"  10.Exit Database\n";
        if(setting.debug == 1)cout<<"  11.Show Debug Information\n";
        if(setting.plugins == 1)cout<<"  12.Add Plugins\n";
        if(setting.plugins == 1 && setting.pluginCount > 0)cout<<"  13.Plugins\n";
        cout<<"\n\n  Your Choice: ";cin>>input;
        if(input == 1)   addData();
        if(input == 2)   modifyData();
        if(input == 3)   showData();
        if(input == 4)   showDataDetail();
        if(input == 5)   {loadingScreen("Importing");importData();}
        if(input == 6)   {loadingScreen("Exporting");exportData();}
        if(input == 7)   {loadingScreen("Deleting");deleteData(0);}
        if(input == 8)   ftpBrowse();
        if(input == 9)  {loadingScreen("Logging out");login();}
        if(input == 10)  quit();
        if(input == 11 && setting.debug == 1)   debugInfo();
        if(input == 12 && setting.plugins == 1)   pluginAdd();
        if(input == 13 && setting.plugins == 1 && setting.pluginCount > 0)    pluginMenu();
    }
    if(permissionLevel == 1)
    {
        cout<<"  1.Add Data to Database\n";
        cout<<"  2.Modify Data in Database\n";
        cout<<"  3.Show List of Data in Database\n";
        cout<<"  4.Show Detailed Data Information\n";
        cout<<"  5.Save Database\n";
        cout<<"  6.Log out\n";
        cout<<"  7.Exit Database\n";
        if(setting.plugins == 1 && setting.pluginCount > 0)cout<<"  9.Plugins\n";
        cout<<"\n\n  Your Choice: ";cin>>input;

        if(input == 1)   addData();
        if(input == 2)   modifyData();
        if(input == 3)   showData();
        if(input == 4)   showDataDetail();
        if(input == 5)   {loadingScreen("Exporting");exportData();}
        if(input == 6)   {loadingScreen("Logging out");login();}
        if(input == 7)   quit();
        if(input == 8 && setting.plugins == 1 && setting.pluginCount > 0)     pluginMenu();
    }
}

int startupScript()
{
    settingsImport();
    pluginImport();
    rlutil::setColor(setting.ForegroundColor);
    rlutil::setBackgroundColor(setting.BackgroundColor);
}

int main()
{
    startupScript();
    login();
    while(true)
    {
        loadDefaultSettings();
        userMenu();
        system("attrib +h Settings.ini | find \"something\"");
    }
    return 0;
}
