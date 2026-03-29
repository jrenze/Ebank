#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <string>
#include <fstream>
#include <thread>
#include <chrono>
#include <filesystem>
#include <ctime>
#include <iomanip>

#define grey "\033[90m"
#define red "\033[31m"
#define green "\033[32m"
#define r "\033[0m"

using namespace std;


string ebank =
            "                                               \n"
            " ══════════════════════════════════════════════\n"
            "                                               \n"
            "   ███████╗██████╗  █████╗ ███╗   ██╗██╗  ██╗\n"
            "   ██╔════╝██╔══██╗██╔══██╗████╗  ██║██║ ██╔╝\n"
            "   █████╗  ██████╔╝███████║██╔██╗ ██║█████╔╝\n"
            "   ██╔══╝  ██╔══██╗██╔══██║██║╚██╗██║██╔═██╗\n"
            "   ███████╗██████╔╝██║  ██║██║ ╚████║██║  ██╗\n"
            "   ╚══════╝╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝  ╚═╝\n";


//global variable
bool exitM = false;
bool signup_exit = false;
bool fKill = false;
//global variable



void loading_S(string color, string color2,int time, int time2){

    string frames[]={"    /","    -","    \\","    |"};

    cout << "\033[?25l";

    for(int i = 0; i < time; i++){
        cout << "    " << color << "\r" << frames[i%4] << flush << red;
        this_thread::sleep_for(chrono::milliseconds(120));
    }
    for(int i = 0; i < time2; i++){
        cout << "    " << color2 << "\r" << frames[i%4] << flush << red;

        this_thread::sleep_for(chrono::milliseconds(120));
    }

    cout << "\r ";
    cout << "\033[?25h";
}


//sign up section
void usrCheck(string usr){
    bool f1 = false, f2 = false, f3 = false, f4 = false;

    if(usr.length() >= 5){
        fKill = false;
    }else{
        f1 = true;
        cout << red << "    └Username must be at least 5 characters long. ";
    }

    for(int i = 0; i < usr.length(); i++){

        if(usr[i] == ' ')
            f3 = true;

        if(!(isalnum(usr[i])))
            f4 = true;
    }

    if(f3 == true){
        if(f1 == true){cout << endl;}
        cout << red << "    └Spaces are not allowed. ";
    }

    if(f4 == true){
        if(f3 == true){cout << endl;}
        cout << red << "    └Username can only contain letters and numbers. ";
    }

    string file_usr;
    ifstream user_dataFile("userData.txt");

    while(user_dataFile >> file_usr){
        if(file_usr == usr){
            f2 = true;
            if(f1 == true || f3 == true || f4 == true) cout << endl;
            cout << grey << "    └Username is already in use. ";
            break;
        }
    }

    if(f1 == true || f2 == true || f3 == true || f4 == true){
        fKill = true;
        system("pause");
        cout << r;
        return;
    }
}


void emailCheck(string email){
    bool check = false;
    bool f1 = false, f2 = false;
    bool hasAt = false;
    bool hasDot = false;
    bool hasSpace = false;

    for(int i = 0; i < email.length(); i++){
        if(email[i] == '@'){
            hasAt = true;
        }
        if(email[i] == '.'){
            hasDot = true;
        }
        if(email[i] == ' '){
            hasSpace = true;
        }
    }

    if(hasAt && hasDot && !hasSpace){
        fKill = false;
    }else{
        f1 = true;
        cout << red << "    └Invalid Email. ";
    }

    //check if alreaady exist Email
    string file_usr, file_mail;
     ifstream user_dataFile("userData.txt");
        while(user_dataFile >> file_usr >> file_mail) {
            if(file_mail == email){
                f2 = true;
                cout << grey << "    └Email is already in use. ";
                break;
            }
            }
        if(f1 == true || f2 == true){
            fKill = true;
            system("pause");
            cout << r;
        }
}


void numCheck(string number){
    bool f1 = false, f2 = false, f3 = false;
    if(number.length() >= 11 && number.length() <= 13 ){
        fKill = false;
    }else {
        cout << red << "    └Invalid Number. ";
        f1 = true;
    }
    for(int i = 0; i < number.length(); i++){
        if(!isdigit(number[i])){
            f2 = true;
        }
    }
    if(f2 == true) { cout << red << "    └Invalid Number. "; }

    //check if number already exist
    string file_usr, file_mail, file_num;
     ifstream user_dataFile("userData.txt");
        while(user_dataFile >> file_usr >> file_mail >> file_num) {
            if(file_num == number){
                f3 = true;
                cout << grey << "    └Number is already in use. ";
                break;
            }
            }
            if(f1 == true || f2 == true || f3 == true){
            fKill = true;
            system("pause");
            cout << r;
        }

            return;
}


void passCheck(string pass){
    bool f1 = false, f2 = false;
    if(pass.length() >= 10){
        fKill = false;
    }else {
        cout << red << "    └Password must be at least 10 characters long. ";
        f1 = true;
    }
    for(int i = 0; i < pass.length(); i++){
        if(pass[i] == ' '){
            f2 = true;
        }
    }
    if( f2 == true){
            if(f1 == true){cout << endl;}
            cout << red << "    └Spaces are not allowed. ";
        }
    if(f1 == true || f2 == true){
        fKill = true;
        system("pause");
        cout << r;
    }
       return;
}


//mainAcc section


void userBal_Hist(string userCreate){
    if(!filesystem::exists("userBalance&History")){
        filesystem::create_directory("userBalance&History");
    }

    filesystem::create_directory("userBalance&History/" + userCreate + "_Data");
    ofstream user_dataFile_Bal("userBalance&History/" + userCreate + "_Data" + "/balData.txt", ios::app);
    ofstream user_dataFile_Hist("userBalance&History/" + userCreate + "_Data" + "/histData.txt", ios::app);
    user_dataFile_Bal.close();
    user_dataFile_Hist.close();
}

string result;
void balSys(long long pesos, long long centavos, string usr){
    fstream user_dataFile_Bal("userBalance&History/" + usr + "_Data/balData.txt");
    ofstream tempData("userBalance&History/" + usr + "_Data/temp.txt");

    long long bal, balCent;
    bool found = false;
    if(user_dataFile_Bal >> bal >> balCent){
        found = true;
    }

    pesos = pesos + bal;
    centavos = centavos + balCent;

    if(found == false){
        pesos = 0;
        centavos = 0;
    }

    pesos += centavos / 100;
    centavos = centavos % 100;

    if(centavos < 0){
    centavos += 100;
    pesos -= 1;
}

    string num = to_string(pesos);
    string formatted = "";
    int count = 0;


    for(int i = num.length() - 1; i >= 0; i--){
        formatted = num[i] + formatted;
        count++;
        if(count == 3 && i != 0){
            formatted = "," + formatted;
            count = 0;
        }
    }

    result = "₱" + formatted + ".";
    if(centavos < 10) {result += "0";}
    result += to_string(centavos);

    tempData << pesos << " " << centavos;
    tempData.close();
    user_dataFile_Bal.close();

    remove(("userBalance&History/" + usr + "_Data/balData.txt").c_str());
    rename(("userBalance&History/" + usr+ "_Data/temp.txt").c_str(),
           ("userBalance&History/" + usr + "_Data/balData.txt").c_str());
}

void BalHistory(string histType, string balAmount, string usr){
    ofstream user_dataFile_Hist("userBalance&History/" + usr + "_Data" + "/histData.txt", ios::app);
    time_t now = time(0);
    tm* time = localtime(&now);

    user_dataFile_Hist << histType << balAmount << " | " << put_time(time, "%Y-%m-%d %I:%M %p" ) << endl;
    user_dataFile_Hist.close();

}

bool exitF = false;
void moneyValidator(string depMoney){
        bool allDigits = true;
        while(true){
        for (char c : depMoney) {
            if (!isdigit(c)) {
                allDigits = false;
                break;
            }
        }

        if (allDigits && !depMoney.empty()) {
                break;
        }else{
            cout << grey << "    └Invalid input! Only whole numbers without spaces, commas, or dots are allowed. ";
            exitF = true;
            system("pause");
            cout << r;
            break;
        }
        }
    return;
}

void deposite(string usrName){
    string depVal, depVal2;

    cout << r;
    cout << "\033[?25h";
        system("cls");
        cout << ebank << endl;
        balSys(0, 0, usrName);
        cout << " ══════════════════════════════════════════════\n" << endl;
        cout << " " << grey << "@" << r << usrName << endl;
        cout << " "<< result << endl << endl;
        cout << " ══════════════════════════════════════════════\n" << endl;
        cout << " Deposite" << endl;
        cout << " └Enter amount: " << grey << "₱" << r;

        exitF = false;
        getline(cin, depVal);
        moneyValidator(depVal);
        if(exitF == true){return;}

        system("cls");
        cout << ebank << endl;
        balSys(0, 0, usrName);
        cout << " ══════════════════════════════════════════════\n" << endl;
        cout << " " << grey << "@" << r << usrName << endl;
        cout << " "<< result << endl << endl;
        cout << " ══════════════════════════════════════════════\n" << endl;
        cout << " Deposite" << endl;
        cout << " └Enter amount: " << grey << "₱" << r << depVal << ".";

        exitF = false;
        getline(cin, depVal2);
        moneyValidator(depVal2);
        if(exitF == true){return;}
        cout << r;

        string Fresult = result;
        try {
            int depVal_int = stoi(depVal);
            int depVal2_int = stoi(depVal2);
            balSys(depVal_int, depVal2_int, usrName);
            loading_S(grey, green, 20, 10);
            cout << grey << "  └Deposit Successful." << r << endl;
        } catch (out_of_range&) {
            loading_S(grey, red, 20, 10);
            cout << red << "  └Amount exceeds maximum allowed." << endl;
            system("pause");
            cout << r;
            return;
        } catch (invalid_argument&) {
            loading_S(grey, red, 20, 10);
            cout << red << "  └Invalid input." << endl;
            system("pause");
            cout << r;
            return;
        }

        string DepSend = "₱" + depVal + "." + depVal2;

        BalHistory("Deposite: +", DepSend, usrName);

        cout << "\033[?25l";
        system("cls");
        cout << ebank << endl;
        balSys(0, 0, usrName);
        cout << " ══════════════════════════════════════════════\n" << endl;
        cout << " " << grey << "@" << r << usrName << endl;
        cout << " "<< Fresult;
        cout << grey << " +₱" << depVal << "." << depVal2 << r << endl << endl;
        cout << " ══════════════════════════════════════════════\n" << endl;
        cout << " Deposite" << endl;
        cout << " └Enter amount: " << grey << "₱" << r << depVal << "." << depVal2 << endl;
        cout << grey << "  └Deposit Successful." << r << endl;
        loading_S(grey, green, 20, 10);
        cout << r;

        system("cls");
        cout << ebank << endl;
        balSys(0, 0, usrName);
        cout << " ══════════════════════════════════════════════\n" << endl;
        cout << " " << grey << "@" << r << usrName << endl;
        cout << " "<< result << endl << endl;
        cout << " ══════════════════════════════════════════════\n" << endl;
        cout << " Deposite" << endl;
        cout << " └Enter amount: " << grey << "₱" << r << depVal << "." << depVal2 << endl;
        cout << grey << "  └Deposit Successful. ";
        system("pause");
        cout << r;
    return;
}

void withdraw(string usrName){
    string withVal, withVal2;

    cout << r;
    cout << "\033[?25h";
    system("cls");
    cout << ebank << endl;

    balSys(0, 0, usrName);

    cout << " ══════════════════════════════════════════════\n" << endl;
    cout << " " << grey << "@" << r << usrName << endl;
    cout << " " << result << endl << endl;
    cout << " ══════════════════════════════════════════════\n" << endl;
    cout << " Withdraw" << endl;
    cout << " └Enter amount: " << grey << "₱" << r;

    exitF = false;
    getline(cin, withVal);
    moneyValidator(withVal);
    if(exitF) return;

    system("cls");
    cout << ebank << endl;

    balSys(0, 0, usrName);

    cout << " ══════════════════════════════════════════════\n" << endl;
    cout << " " << grey << "@" << r << usrName << endl;
    cout << " " << result << endl << endl;
    cout << " ══════════════════════════════════════════════\n" << endl;
    cout << " Withdraw" << endl;
    cout << " └Enter amount: " << grey << "₱" << r << withVal << ".";

    exitF = false;
    getline(cin, withVal2);
    moneyValidator(withVal2);
    if(exitF) return;

    string oldBal = result;

    try{
        long long withVal_int = stoll(withVal);
        long long withVal2_int = stoll(withVal2);

        fstream user_dataFile_Hist("userBalance&History/" + usrName + "_Data/balData.txt");
        long long bal = 0, balCent = 0;

        if(user_dataFile_Hist >> bal >> balCent){
            long long totalBal = bal * 100 + balCent;
            long long totalW = withVal_int * 100 + withVal2_int;

            if(totalW > totalBal){
                loading_S(grey, red, 20, 10);
                cout << red << "  └Insufficient balance. ";
                system("pause");
                cout << r;
                return;
            }
        }
        user_dataFile_Hist.close();

        balSys(-withVal_int, -withVal2_int, usrName);

        loading_S(grey, green, 20, 10);
        cout << grey << "  └Withdraw Successful." << r << endl;

    }catch(...){
        loading_S(grey, red, 20, 10);
        cout << red << "  └Invalid input." << endl;
        system("pause");
        cout << r;
        return;
    }

    string withSend = "₱" + withVal + "." + withVal2;
    BalHistory("Withdraw: -", withSend, usrName);

     cout << "\033[?25l";
        system("cls");
        cout << ebank << endl;
        balSys(0, 0, usrName);
        cout << " ══════════════════════════════════════════════\n" << endl;
        cout << " " << grey << "@" << r << usrName << endl;
        cout << " "<< oldBal;
        cout << grey << " -" << withSend << r << endl << endl;
        cout << " ══════════════════════════════════════════════\n" << endl;
        cout << " Deposite" << endl;
        cout << " └Enter amount: " << grey << "₱" << r << withVal << "." << withVal2 << endl;
        cout << grey << "  └Withdraw Successful." << r << endl;
        loading_S(grey, green, 20, 10);
        cout << r;

        system("cls");
        cout << ebank << endl;
        balSys(0, 0, usrName);
        cout << " ══════════════════════════════════════════════\n" << endl;
        cout << " " << grey << "@" << r << usrName << endl;
        cout << " "<< result << r << endl << endl;
        cout << " ══════════════════════════════════════════════\n" << endl;
        cout << " Deposite" << endl;
        cout << " └Enter amount: " << grey << "₱" << r << withVal << "." << withVal2 << endl;
        cout << grey << "  └Withdraw Successful. ";
        system("pause");
        cout << r;


}

void rcvMoney(string Rusr, string Susr, long long pesos, long long centavos){
    fstream Ruser_dataFile_Bal("userBalance&History/" + Rusr + "_Data/balData.txt");
    ofstream RtempData("userBalance&History/" + Rusr + "_Data/temp.txt");

    long long bal, balCent;
    bool found = false;
    if(Ruser_dataFile_Bal >> bal >> balCent){
        found = true;
    }

    pesos = pesos + bal;
    centavos = centavos + balCent;

    if(found == false){
        pesos = 0;
        centavos = 0;
    }

    pesos += centavos / 100;
    centavos = centavos % 100;

    if(centavos < 0){
    centavos += 100;
    pesos -= 1;
}

    string num = to_string(pesos);
    string formatted = "";
    int count = 0;


    for(int i = num.length() - 1; i >= 0; i--){
        formatted = num[i] + formatted;
        count++;
        if(count == 3 && i != 0){
            formatted = "," + formatted;
            count = 0;
        }
    }

    result = "₱" + formatted + ".";
    if(centavos < 10) {result += "0";}
    result += to_string(centavos);

    RtempData << pesos << " " << centavos;
    RtempData.close();
    Ruser_dataFile_Bal.close();

    remove(("userBalance&History/" + Rusr + "_Data/balData.txt").c_str());
    rename(("userBalance&History/" + Rusr+ "_Data/temp.txt").c_str(),
           ("userBalance&History/" + Rusr + "_Data/balData.txt").c_str());

    string Pstr = to_string(pesos);
    string Cstr = to_string(centavos);

    ofstream user_dataFile_Hist("userBalance&History/" + Rusr + "_Data" + "/histData.txt", ios::app);
    time_t now = time(0);
    tm* time = localtime(&now);

    user_dataFile_Hist << "Recieved: " << "@" << Susr << " | " << " +₱" << Pstr << "." << Cstr << " | " << put_time(time, "%Y-%m-%d %I:%M %p" ) << endl;
    user_dataFile_Hist.close();

}

void sendMoney(string usrName){
    string sendVal, sendVal2;

    cout << r;
    cout << "\033[?25h";
    system("cls");

    balSys(0, 0, usrName);
    fstream Fuser_dataFile("userData.txt");
    string temp_usr, temp_mail, temp_num, temp_pass;

    do{
        system("cls");
        cout << ebank << endl;
        cout << "\033[?25h";
        cout << " ══════════════════════════════════════════════\n" << endl;
        cout << " " << grey << "@" << r << usrName << endl;
        cout << " " << result << endl << endl;
        cout << " ══════════════════════════════════════════════\n" << endl;
        cout << " Send Money to" << grey << " @" << r;

        string usr;
        getline(cin, usr);


        cout << "\033[?25l";


        bool Fstop = false;
        while(Fuser_dataFile >> temp_usr >> temp_mail >> temp_num >> temp_pass) {
            if(usr == temp_usr){
                Fstop = true;
                break;
            }
        }



        cout << grey << " └" << r << "Searching for user" << r << endl;

        if(usr == usrName){
            loading_S(grey, red, 20, 10);
            cout << " └Cannot transfer to the same account. ";
            system("pause");
            cout << r;
            return;
        }

        if(Fstop == true){
            loading_S(grey, green, 20, 10);
            cout << green;
            cout << " └Found. " << endl;
            loading_S(grey, green, 20, 10);
            cout << r;
            break;
        }else{
            loading_S(grey, red, 20, 10);
            cout << " └User not found. ";
            system("pause");
            cout << r;
            return;
        }



    }while(true);
            Fuser_dataFile.close();


    system("cls");
    cout << ebank << endl;
    cout << " ══════════════════════════════════════════════\n" << endl;
    cout << " " << grey << "@" << r << usrName << endl;
    cout << " " << result << endl << endl;
    cout << " ══════════════════════════════════════════════\n" << endl;
    cout << " Send Money" << endl;
    cout << " └Enter amount: " << grey << "₱" << r;

    exitF = false;
    getline(cin, sendVal);
    moneyValidator(sendVal);
    if(exitF) return;

    system("cls");
    cout << ebank << endl;

    balSys(0, 0, usrName);

    cout << " ══════════════════════════════════════════════\n" << endl;
    cout << " " << grey << "@" << r << usrName << endl;
    cout << " " << result << endl << endl;
    cout << " ══════════════════════════════════════════════\n" << endl;
    cout << " Send Money" << endl;
    cout << " └Enter amount: " << grey << "₱" << r << sendVal << ".";

    exitF = false;
    getline(cin, sendVal2);
    moneyValidator(sendVal2);
    if(exitF) return;

    string oldBal = result;

    try{
        long long sendVal_int = stoll(sendVal);
        long long sendVal2_int = stoll(sendVal2);
        rcvMoney(temp_usr, usrName, sendVal_int, sendVal2_int);

        fstream user_dataFile_Hist("userBalance&History/" + usrName + "_Data/balData.txt");
        long long bal = 0, balCent = 0;

        if(user_dataFile_Hist >> bal >> balCent){
            long long totalBal = bal * 100 + balCent;
            long long totalW = sendVal_int * 100 + sendVal2_int;

            if(totalW > totalBal){
                loading_S(grey, red, 20, 10);
                cout << red << "  └Insufficient balance. ";
                system("pause");
                cout << r;
                return;
            }
        }
        user_dataFile_Hist.close();

        balSys(-sendVal_int, -sendVal2_int, usrName);

        loading_S(grey, green, 20, 10);
        cout << grey << "  └Send Money Successful." << r << endl;

    }catch(...){
        loading_S(grey, red, 20, 10);
        cout << red << "  └Invalid input." << endl;
        system("pause");
        cout << r;
        return;
    }

    string sendSendHist = "@" + temp_usr + " | -₱" + sendVal + "." + sendVal2;
    string sendSend = "-₱" + sendVal + "." + sendVal2;
    BalHistory("Send: ", sendSendHist, usrName);

     cout << "\033[?25l";
        system("cls");
        cout << ebank << endl;
        balSys(0, 0, usrName);
        cout << " ══════════════════════════════════════════════\n" << endl;
        cout << " " << grey << "@" << r << usrName << endl;
        cout << " "<< oldBal;
        cout << grey << " " << sendSend << r << endl << endl;
        cout << " ══════════════════════════════════════════════\n" << endl;
        cout << " Send Money" << endl;
        cout << " └Enter amount: " << grey << "₱" << r << sendVal << "." << sendVal2 << endl;
        cout << grey << "  └Send Money Successful." << r << endl;
        loading_S(grey, green, 20, 10);
        cout << r;

        system("cls");
        cout << ebank << endl;
        balSys(0, 0, usrName);
        cout << " ══════════════════════════════════════════════\n" << endl;
        cout << " " << grey << "@" << r << usrName << endl;
        cout << " "<< result << r << endl << endl;
        cout << " ══════════════════════════════════════════════\n" << endl;
        cout << " Send" << endl;
        cout << " └Enter amount: " << grey << "₱" << r << sendVal << "." << sendVal2 << endl;
        cout << grey << "  └Send Money Successful. ";
        system("pause");
        cout << r;
}

void showHistory(string usr){
    system("cls");

    string path = "userBalance&History/" + usr + "_Data/histData.txt";
    ifstream user_dataFile_Hist(path);

    cout << "\033[?25l";
    system("cls");
    cout << ebank << endl;
    cout << " ══════════════════════════════════════════════\n" << endl;
    cout << "   ╦ ╦╦╔═╗╔╦╗╔═╗╦═╗╦ ╦ \n"
            "   ╠═╣║╚═╗ ║ ║ ║╠╦╝╚╦╝\n"
            "   ╩ ╩╩╚═╝ ╩ ╚═╝╩╚═ ╩ \n" << endl;
    cout << " ══════════════════════════════════════════════" << endl;
    cout << "                                               " << endl;
        cout << " ╔════════════════════════════════════════════╗" << endl;
        cout << " ║                                            ║" << endl;
        cout << " ║  1. Clear History                          ║" << endl;
        cout << " ║  2. Exit                                   ║" << endl;
        cout << " ║                                            ║" << endl;
        cout << " ╚════════════════════════════════════════════╝" << endl;

    string line;
    if (!getline(user_dataFile_Hist, line)) {
        cout << grey << " └No history found. ";
        system("pause");
        cout << r;
        return;
    }

    int count = 1;
    cout << endl;
    do {
        cout << " " << count << ". " << line << endl;
        count++;
    } while (getline(user_dataFile_Hist, line));

    user_dataFile_Hist.close();
    char choice = getch();

    if(choice == '1'){
        cout << grey << " └Clearing history." << endl;
        loading_S(grey, green, 20, 10);
        ofstream clearFile(path, ios::trunc);
        clearFile.close();
        cout << grey << "  └History cleared.\n";
        loading_S(grey, green, 20, 10);
    }else{
        return;
    }
    cout << "\033[?25l";
    system("cls");
    cout << r;
    cout << ebank << endl;
    cout << " ══════════════════════════════════════════════\n" << endl;
    cout << "   ╦ ╦╦╔═╗╔╦╗╔═╗╦═╗╦ ╦ \n"
            "   ╠═╣║╚═╗ ║ ║ ║╠╦╝╚╦╝\n"
            "   ╩ ╩╩╚═╝ ╩ ╚═╝╩╚═ ╩ \n" << endl;
    cout << " ══════════════════════════════════════════════" << endl;
    cout << "                                               " << endl;
        cout << " ╔════════════════════════════════════════════╗" << endl;
        cout << " ║                                            ║" << endl;
        cout << " ║  1. Clear History                          ║" << endl;
        cout << " ║  2. Exit                                   ║" << endl;
        cout << " ║                                            ║" << endl;
        cout << " ╚════════════════════════════════════════════╝" << endl;

        cout << grey << " └No history found. ";
        system("pause");
        cout << r;
        return;
}

bool delAcc_Exit = false;
void delAcc(string usr, string mail, string num, string pass){
    bool FdelAcc = true;
    do {
        cout << "\033[?25l";
        system("cls");
        cout << r;
        cout << ebank << endl;
        cout << " ══════════════════════════════════════════════\n" << endl;
        cout << "   ╔═╗╔═╗╔═╗╔═╗╦ ╦╔╗╔╔╦╗ \n"
                "   ╠═╣║  ║  ║ ║║ ║║║║ ║\n"
                "   ╩ ╩╚═╝╚═╝╚═╝╚═╝╝╚╝ ╩ \n" << endl;
        cout << " ══════════════════════════════════════════════" << endl << endl;

        cout << grey << " @" << r << usr << endl;
        cout << " └Email: " << grey << mail << r << endl;
        cout << " └Number: " << grey << num << r << endl;
        cout << " └Password: " << grey << pass << r << endl << endl;
        cout << " ══════════════════════════════════════════════" << endl << endl;
        cout << " 1. Update account info" << endl;
        cout << " 2. Delete account" << endl;
        cout << grey << "  └Do you want to delete your account? Y/N" << r << endl;
        cout << " 3. Exit" << endl;

        char choice;
        choice = getch();

        if(choice == 'Y' || choice == 'y'){
            FdelAcc = false;
        }else{
            return;
        }
    }while(FdelAcc == true);

    do {
        system("cls");
        cout << r;
        cout << ebank << endl;
        cout << " ══════════════════════════════════════════════\n" << endl;
        cout << "   ╔═╗╔═╗╔═╗╔═╗╦ ╦╔╗╔╔╦╗ \n"
                "   ╠═╣║  ║  ║ ║║ ║║║║ ║\n"
                "   ╩ ╩╚═╝╚═╝╚═╝╚═╝╝╚╝ ╩ \n" << endl;
        cout << " ══════════════════════════════════════════════" << endl << endl;
        cout << "\033[?25h";

        string usrIn;
        cout << "\r" << " Type '" << grey << "@" << r << usr << "' to delete account: " << grey << "@" << r;
        cin >> usrIn;

        cout << "\033[?25l";
        if(usrIn != usr){
            cout << grey << " └Aborted. ";
            system("pause");
            return;
            cout << r;
        }
        cout << red;
        string text = " └Processing account deletion. Press any key to abort. ";

        for(int i = 10; i >= 0; i--){
            if(_kbhit()){
                cout << grey << "\r └Aborted.                                                \n";
                cout << " └";
                system("pause");
                cout << r;
                return;
            }

            cout << "\r" << text << i << "   " << flush;
            this_thread::sleep_for(chrono::seconds(1));
        }

        cout << grey << "\r\r │" << "                                                       \n";
        cout << r << " Proccessing account deletion..." << endl;
        loading_S(grey, green, 20, 10);
        cout << grey << " └" << r << "Withdrawing: " << grey << result << endl;
        loading_S(grey, green, 20, 10);
        cout << grey << "  ├" << green << "Successful. " << endl;
        loading_S(grey, green, 20, 10);
        cout << grey << "  └" << r << "Deleting account from database " << endl;
        loading_S(grey, green, 20, 10);
        cout << grey << "   └" << green << "Successful. " << endl;
        loading_S(grey, green, 25, 10);
        cout << grey << "    ├" << red << "Account deleted. " << endl;
        loading_S(grey, green, 25, 10);
        cout << grey << "    └" << r << "Thank you for using " << green << "Ebank." << r;
        cout << "\033[?25l";
        this_thread::sleep_for(chrono::seconds(2));
        cout << " Press any key to exit . . .";

        ifstream user_dataFile("userData.txt");
        ofstream tempUpdate("usr_tempData.txt");

        while(user_dataFile >> usr >> mail >> num >> pass){
            if(usrIn != usr){
                tempUpdate << usr << " " << mail << " " << num << " " << pass << endl;
            }
        }
        user_dataFile.close();
        tempUpdate.close();

        remove("userData.txt");
        rename("usr_tempData.txt", "userData.txt");

        string path = "userBalance&History/" + usr + "_Data";
        filesystem::remove_all(path);

        delAcc_Exit = true;
        char e;
        e = getch();
        return;



    }while(true);
}

void accUpdate(string usr){
    do {
        cout << "\033[?25l";
        system("cls");
        cout << r;
        cout << ebank << endl;
        cout << " ══════════════════════════════════════════════\n" << endl;
        cout << "   ╔═╗╔═╗╔═╗╔═╗╦ ╦╔╗╔╔╦╗ \n"
                "   ╠═╣║  ║  ║ ║║ ║║║║ ║\n"
                "   ╩ ╩╚═╝╚═╝╚═╝╚═╝╝╚╝ ╩ \n" << endl;
        cout << " ══════════════════════════════════════════════" << endl << endl;

        char choice;
        string mailUp, numUp, passUp;
        bool f1 = true, f2 = true, f3 = true;

        cout << grey << " @" << r << usr << endl;

        cout << grey << " └Update Email? Y/N" << r;
        choice = getch();
        if(choice == 'Y' || choice == 'y'){
            cout << "\033[?25h";
            f1 = false;
            cout << "\r                        ";
            cout << "\r └Email: ";
            getline(cin, mailUp);
            emailCheck(mailUp);
            if(fKill == true){ return; }
        }

        if(f1 == true){cout << endl;};
        cout << "\033[?25l";
        cout << grey << " └Update Number? Y/N" << r;
        choice = getch();
        if(choice == 'Y' || choice == 'y'){
            cout << "\033[?25h";
            f2 = false;
            cout << "\r                        ";
            cout << "\r └Number: ";
            getline(cin, numUp);
            numCheck(numUp);
            if(fKill == true){ return; }
        }

        if(f2 == true){cout << endl;};
        cout << "\033[?25l";
        cout << grey << " └Update Password? Y/N" << r;
        choice = getch();
        if(choice == 'Y' || choice == 'y'){
            cout << "\033[?25h";
            f3 = false;
            cout << "\r                        ";
            cout << "\r └Password: ";
            getline(cin, passUp);
            passCheck(passUp);
            if(fKill == true){ return; }
        }

        cout << "\033[?25l";
        if(f1 == true && f2 == true && f3 == true){
            cout << grey << "\n  │" << endl;
            cout  << " Info update canceled. ";
            system("pause");
            cout << r;
            return;
        }

        if(f3 == true){
            cout << endl;
        }
        cout << grey << "  │" << endl;
        cout  << " Update account account? Y/N";
        choice = getch();

        if(choice != 'Y' && choice != 'y'){
            cout << grey << "\n  │" << endl;
            cout  << " Info update canceled. 2";
            system("pause");
            cout << r;
            return;
        }

        ifstream user_dataFile("userData.txt");
        string Fusr, Fmail, Fnum, Fpass;

        while(user_dataFile >> Fusr >> Fmail >> Fnum >> Fpass){
            if(Fusr == usr){
                break;
            }
        }
        user_dataFile.close();

            cout << "\033[?25l";
            cout << "\r                                       \r";
            cout << r << " Processing account info update..." << endl;
            loading_S(grey, green, 15, 10);

        if(f1 == false){
            cout << grey << " └" << r << "Updating email" << endl;
            loading_S(grey, green, 15, 10);
            cout << "\033[?25l";
            cout << grey << "  ├" << Fmail;
            cout << green;
            this_thread::sleep_for(chrono::milliseconds(700));
            cout << " >";
            this_thread::sleep_for(chrono::milliseconds(700));
            cout << ">";
            this_thread::sleep_for(chrono::milliseconds(700));
            cout << ">";
            this_thread::sleep_for(chrono::milliseconds(700));
            cout << ">";
            this_thread::sleep_for(chrono::milliseconds(700));
            cout << "> ";
            this_thread::sleep_for(chrono::milliseconds(700));
            cout << grey << mailUp << r << endl;
            loading_S(grey, green, 15, 10);
            cout << grey << "  └" << green << "Successful. " << endl;
        }

        if(f2 == false){
            if(f1 == false){
                loading_S(grey, green, 15, 10);
            }
            cout << grey << " └" << r << "Updating number" << endl;
            loading_S(grey, green, 15, 10);
            cout << "\033[?25l";
            cout << grey << "  ├" << Fnum;
            cout << green;
            this_thread::sleep_for(chrono::milliseconds(700));
            cout << " >";
            this_thread::sleep_for(chrono::milliseconds(700));
            cout << ">";
            this_thread::sleep_for(chrono::milliseconds(700));
            cout << ">";
            this_thread::sleep_for(chrono::milliseconds(700));
            cout << ">";
            this_thread::sleep_for(chrono::milliseconds(700));
            cout << "> ";
            this_thread::sleep_for(chrono::milliseconds(700));
            cout << grey << numUp << r << endl;
            loading_S(grey, green, 15, 10);
            cout << grey << "  └" << green << "Successful. " << endl;
        }

        if(f3 == false){
            if(f2 == false){
                loading_S(grey, green, 15, 10);
            }
            cout << grey << " └" << r << "Updating password" << endl;
            loading_S(grey, green, 15, 10);
            cout << "\033[?25l";
            cout << grey << "  ├" << Fpass;
            cout << green;
            this_thread::sleep_for(chrono::milliseconds(700));
            cout << " >";
            this_thread::sleep_for(chrono::milliseconds(700));
            cout << ">";
            this_thread::sleep_for(chrono::milliseconds(700));
            cout << ">";
            this_thread::sleep_for(chrono::milliseconds(700));
            cout << ">";
            this_thread::sleep_for(chrono::milliseconds(700));
            cout << "> ";
            this_thread::sleep_for(chrono::milliseconds(700));
            cout << grey << passUp << r << endl;
            loading_S(grey, green, 15, 10);
            cout << grey << "  └" << green << "Successful. " << endl;
        }


        ifstream user_dataFile2("userData.txt");
        ofstream tempUpdate("usr_tempData.txt");

        while(user_dataFile2 >> Fusr >> Fmail >> Fnum >> Fpass){
            if(Fusr == usr){
                tempUpdate << usr << " " << mailUp << " " << numUp << " " << passUp << endl;
            }else{
                tempUpdate << Fusr << " " << Fmail << " " << Fnum << " " << Fpass << endl;
            }
        }

        user_dataFile2.close();
        tempUpdate.close();
        remove("userData.txt");
        rename("usr_tempData.txt","userData.txt");

        loading_S(grey, green, 15, 10);
        cout << grey << "   │" << green << "\n   Account updated. ";
        system("pause");
        cout << r;
        return;
    }while(true);
}


void accInfo(string usr){
    string Fusr, Fmail, Fnum, Fpass, temp_pass;
    ifstream user_dataFile("userData.txt");
    cout << " └Password: ";
    getline(cin, temp_pass);
    passCheck(temp_pass);
    if(fKill == true) {return;}

    bool found = false;
    while(user_dataFile >> Fusr >> Fmail >> Fnum >> Fpass){
        if(Fusr == usr && Fpass == temp_pass){
            found = true;
            break;
        }
    }

    if(found == false){
        cout << red << "  └Wrong password. ";
        system("pause");
        cout << r;
        return;
    }
    do {
        if(delAcc_Exit == true){return;}
        cout << "\033[?25l";
        system("cls");
        cout << r;
        cout << ebank << endl;
        cout << " ══════════════════════════════════════════════\n" << endl;
        cout << "   ╔═╗╔═╗╔═╗╔═╗╦ ╦╔╗╔╔╦╗ \n"
                "   ╠═╣║  ║  ║ ║║ ║║║║ ║\n"
                "   ╩ ╩╚═╝╚═╝╚═╝╚═╝╝╚╝ ╩ \n" << endl;
        cout << " ══════════════════════════════════════════════" << endl << endl;

        cout << grey << " @" << r << Fusr << endl;
        cout << " └Email: " << grey << Fmail << r << endl;
        cout << " └Number: " << grey << Fnum << r << endl;
        cout << " └Password: " << grey << Fpass << r << endl << endl;
        cout << " ══════════════════════════════════════════════" << endl << endl;

        char choice;
        cout << " 1. Update account info" << endl;
        cout << " 2. Delete account" << endl;
        cout << " 3. Exit" << endl;
        choice = getch();

        user_dataFile.close();

        switch(choice){
            case '1':
                accUpdate(Fusr); break;
            case '2':
                delAcc(Fusr, Fmail, Fnum, Fpass); break;
            case '3':
                return; break;

            default:
                cout << grey << " └Invalid Input. ";
                system("pause");
                cout <<r;
            }
    }while(true);
}


void mainInterfaceAcc(string usrName){
    char choice;
    do{
    if(delAcc_Exit == true){return;}
    cout << r;
    cout << "\033[?25l";
        system("cls");
        cout << ebank << endl;
        balSys(0, 0, usrName);
        cout << " ══════════════════════════════════════════════\n" << endl;
        cout << " " << grey << "@" << r << usrName << endl;
        cout << " "<< result << endl << endl;
        cout << " ══════════════════════════════════════════════\n" << endl;

        cout << " ╔════════════════════════════════════════════╗" << endl;
        cout << " ║                                            ║" << endl;
        cout << " ║  1. Deposite                               ║" << endl;
        cout << " ║  2. Withdraw                               ║" << endl;
        cout << " ║  3. Send                                   ║" << endl;
        cout << " ║  4. History                                ║" << endl;
        cout << " ║  5. Account                                ║" << endl;
        cout << " ║  6. Logout                                 ║" << endl;
        cout << " ║                                            ║" << endl;
        cout << " ╚════════════════════════════════════════════╝" << endl;
        choice = getch();

        cout << "\033[?25h";
        switch(choice){
            case '1':
                deposite(usrName); break;
            case '2':
                withdraw(usrName); break;
            case '3':
                sendMoney(usrName); break;
            case '4':
                showHistory(usrName); break;
            case '5':
                accInfo(usrName); break;
            case '6':
                cout << grey << " └Loging out. " << endl;
                loading_S(grey, grey, 20, 0);
                cout << grey << " └";
                break;

            default:
                cout << grey << " └Invalid Input. ";
                system("pause");
                break;
        }
    }while(choice != '6');


}

//mainAcc section


void signup(){
    string user_usr, email_usr, password_usr, number_usr;

    system("cls");
    cout << ebank << endl;
    cout << " ══════════════════════════════════════════════\n" << endl;
    cout << "   ╔═╗╦╔═╗╔╗╔ ╦ ╦╔═╗\n"
            "   ╚═╗║║ ╦║║║ ║ ║║═╝\n"
            "   ╚═╝╩╚═╝╝╚╝ ╚═╝╩\n" << endl;
    cout << " ══════════════════════════════════════════════" << endl;
    cout << "                                               " << endl;
    cout << endl;
    cout << "    Username:" << grey << " @" << r;
    getline(cin, user_usr);
        usrCheck(user_usr);
        if(fKill == true){ return; }
    cout << "    Email: ";
    getline(cin, email_usr);
        emailCheck(email_usr);
        if(fKill == true){ return; }
    cout << "    Number: ";
    getline(cin, number_usr);
        numCheck(number_usr);
        if(fKill == true){ return; }
    cout << "    Passwword: ";
    getline(cin, password_usr);
        passCheck(password_usr);
        if(fKill == true){ return; }

        ofstream user_dataFile("userData.txt", ios::app);

            if(user_dataFile.is_open()){
                user_dataFile << user_usr << " " << email_usr << " " << number_usr << " " << password_usr << endl;

                user_dataFile.close();

                userBal_Hist(user_usr);

                loading_S(grey, green, 30, 10);
                cout << grey << "   └Account created successfully. ";
                system("pause");
                cout << r;
                return;
            }else {
                loading_S(grey, red, 30, 10);
                cout << red << "    └Failed to create account. ";
                system("pause");
                cout << r;
                return;
            }
return;
}
//sign up section


//login section
void log_usrCheck(string log_usr){
    bool f1 = false, f2 = false, f3 = false;

    if(log_usr.length() >= 5){
        fKill = false;
    }else {
        f1 = true;
        cout << red << "    └Username must be at least 5 characters long. ";
    }
    for(int i = 0; i < log_usr.length(); i++){
        if(log_usr[i] == ' '){
            f2 = true;
        if(!(isalnum(log_usr[i])))
            f3 = true;
        }
    }

    if( f2 == true){
        if(f1 == true){cout << endl;}
            cout << red << "    └Spaces are not allowed. ";
        }
    if(f3 == true){
        if(f2 == true){cout << endl;}
        cout << red << "    └Username can only contain letters and numbers. ";
    }
        if(f1 == true || f2 == true){
            fKill = true;
            system("pause");
            cout << r;
            return;
        }
}



void accRec(){
    system("cls");
    cout << ebank << endl;
    cout << " ══════════════════════════════════════════════\n" << endl;
    cout << "   ╔═╗╔═╗╔═╗   ╦═╗╔═╗╔═╗╔═╗╦  ╦╔═╗╦═╗╦ ╦\n"
            "   ╠═╣║  ║     ╠╦╝║╣ ║  ║ ║╚╗╔╝║╣ ╠╦╝╚╦╝\n"
            "   ╩ ╩╚═╝╚═╝   ╩╚═╚═╝╚═╝╚═╝ ╚╝ ╚═╝╩╚═ ╩ \n" << endl;
    cout << " ══════════════════════════════════════════════" << endl;
    cout << endl;

    string Fmail_num[2] = {};
    string temp_usr, file_mail, file_num, Fpass;

    cout << "    Email: ";
    getline(cin, Fmail_num[0]);
    cout << "    Number: ";
    getline(cin, Fmail_num[1]);

    ifstream user_dataFile("userData.txt");
        bool found = false;
        while(user_dataFile >> temp_usr >> file_mail >> file_num >> Fpass) {
            if(file_mail == Fmail_num[0] && file_num == Fmail_num[1]){
                found = true;
                break;
            }
            }
            user_dataFile.close();
        bool Rfound = false;

        if(found == true){
            loading_S(grey, green, 40, 10);
            cout << grey << "   └Account found." << endl;
            cout << grey << "     ├@" << temp_usr << endl;

            ofstream tempUpdate("usr_tempData.txt");
            ifstream user_dataFile("userData.txt");

            string temp_mail, temp_num;

            while(user_dataFile >> temp_usr >> temp_mail >> temp_num >> Fpass){
                if(temp_mail == Fmail_num[0] && temp_num == Fmail_num[1]){
                        Rfound = true;
                        cout << "     Update" << endl;
                        cout << "     ├" << r << "Password: ";
                        cin >> Fpass;
                    tempUpdate << temp_usr << " " << temp_mail << " " << temp_num << " " << Fpass << endl;
                }else{
                    tempUpdate << temp_usr << " " << temp_mail << " " << temp_num << " " << Fpass << endl;
                }
            }

            tempUpdate.close();
            user_dataFile.close();

            remove("userData.txt");
            rename("usr_tempData.txt","userData.txt");

            if(Rfound == true){
                loading_S(grey, green, 30, 10);
                cout << grey << "     Password replaced succesfully. ";
            }else{
                loading_S(grey, red, 30, 10);
                cout << red << "   └Failed to replace the password. ";
            }


        }else {
            loading_S(grey, red, 40, 10);
            cout << red << "   └No account matches the provided credentials. ";
        }
            return;
            cout << r;
}
//login section

void login(){
system("cls");
    fKill = false;
    string user_usr, password_usr;
    string file_usr, file_pass;
    string temp_mail, temp_num;

    cout << ebank << endl;
    cout << " ══════════════════════════════════════════════\n" << endl;
    cout << "   ╦  ╔═╗╔═╗╦╔╗╔\n"
            "   ║  ║ ║║ ╦║║║║\n"
            "   ╩═╝╚═╝╚═╝╩╝╚╝\n" << endl;
    cout << " ══════════════════════════════════════════════" << endl;
    cout << "                                               " << endl;
    cout << "    Username:" << grey << " @" << r;
    getline(cin, user_usr);
    log_usrCheck(user_usr);
        if(fKill == true){ return; }
    cout << "    Passwword: ";
    getline(cin, password_usr);
    passCheck(password_usr);
        if(fKill == true){ return; }

        ifstream user_dataFile("userData.txt");
        bool found = false;
        while(user_dataFile >> file_usr >> temp_mail >> temp_num >> file_pass) {
            if(file_usr == user_usr && file_pass == password_usr){
                found = true;
                break;
            }
            }
            user_dataFile.close();
            if(found == true){
              loading_S(grey, green, 30, 10);
                cout << "\033[?25l";
                cout << grey << "   └Login successful." << endl << "    ";
                this_thread::sleep_for(chrono::milliseconds(500));
                cout << ".";
                this_thread::sleep_for(chrono::milliseconds(500));
                cout << ".";
                this_thread::sleep_for(chrono::milliseconds(500));
                cout << ".";
                this_thread::sleep_for(chrono::milliseconds(500));
                cout << ".";
                this_thread::sleep_for(chrono::milliseconds(500));
                cout << ".";
                this_thread::sleep_for(chrono::milliseconds(700));
                cout << "\033[?25h";

                mainInterfaceAcc(user_usr);
                if(delAcc_Exit == true){return;}
            }else {
                loading_S(grey, red, 30, 10);
                char choice;
                cout << red << "   └Wrong username or password." << r << endl;
                cout << grey << "     └Forget password? Y/N." << r;
                choice = getch();
                if(choice == 'Y' || choice == 'y'){
                    accRec();
                }else if(choice == 'N' || choice == 'n'){

                    return;
                }else{
                    cout << grey << " └Invalid input. ";
                }
            }


    system("pause");
    cout << r;
            }
//login section



//main section
int main()
{
    cout << r;
    system("chcp 65001 > nul");
    
    char choice;
    do{
    delAcc_Exit = false;
    cout << "\033[?25l";
        system("cls");
        cout << ebank << endl;
        cout << " ══════════════════════════════════════════════\n" << endl;
        cout << " ╔════════════════════════════════════════════╗" << endl;
        cout << " ║                                            ║" << endl;
        cout << " ║  1. Login                                  ║" << endl;
        cout << " ║  2. Sign up                                ║" << endl;
        cout << " ║                                            ║" << endl;
        cout << " ╚════════════════════════════════════════════╝" << endl;
        cout << " ";
        choice = getch();

        cout << "\033[?25h";
        switch(choice){
            case '1':
                login(); break;
            case '2':
                signup(); break;
            default:
                cout << "\033[?25l";
                cout << grey << " └Invalid Input. ";
                system("pause");
                cout <<r;
                break;
        }

    }while(true);



    return 0;
}
