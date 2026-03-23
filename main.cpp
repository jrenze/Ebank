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
                cout << red << "  └Insufficient balance." << endl;
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
        cout << grey << "  └Deposit Successful. ";
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
        loading_S(grey, green, 30, 0);
        ofstream clearFile(path, ios::trunc);
        clearFile.close();
        cout << grey << "  └History cleared.\n";
        loading_S(grey, green, 35, 0);
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
                break;
            case '2':
                break;
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
    char choice = '0';
    do{
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


