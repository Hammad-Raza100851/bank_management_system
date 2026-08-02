#include <iostream>
#include <fstream>
#include <string>
#include "nlohmann/json.hpp"

using namespace std;
using json = nlohmann :: json;
class BMS{
protected:
    string bankName;
    string customerFile;
    json customerData ;
    json transactionData;
    string transactionFile;
protected:

    BMS(string customerFile = "customer.json",string transactionFile = "transaction.json", string bankName = "HAMMAD's BANK"){
        this->bankName = bankName;
        this->customerFile = customerFile;
        this->transactionFile = transactionFile;
        customerData = loadCustomer();
        transactionData = loadTransactionData();
    }

    json loadCustomer(){
        json data;
        ifstream in (customerFile);
        in >> data;
        return data;
    }

    void savecustomer(){
        ofstream out (customerFile);
        out << customerData.dump(4);
    }

    json loadTransactionData(){
        json data;
        ifstream in (transactionFile);
        in >> data;
        return data;
    }

    void saveTransactionData(){
        ofstream out (transactionFile);
        out << transactionData.dump(4);
    }

    void createTransaction(double balanceBefore , double currentBalance , string accountNumber ){
        string nextId = newId();
        transactionData [nextId] = {
            {"accountNumber" , accountNumber},
            {"balanceBefore" , balanceBefore},
            {"currentBalance" , currentBalance},
            {"transactionId" , nextId}
        };
        saveTransactionData();
    }
    
    string newId(){
        int nextId = 0;
        for (auto id : transactionData.items()){
            nextId = max(nextId , stoi(id.key()));
        }
        return to_string(nextId+1);
    }
    
};

    class ADMIN : private BMS{
        private : 
            string adminPass , name , fatherName , cnic , phoneNumber , email , accountType , pin 
            , accountStatus;
            double balance ;
        
            void showfunction(){
                        int n;
                        while (1)
                        {
                        cout<<"\n1 for View a customer \n2 for View all customer \n";
                        cout<<"3 for Change account status \n4 for change customer Info \n";
                        cout<<"5 for add new customer \n6 for remove cutomer \n";
                        cout<<"7 for Check Transaction by Id \n 8 for logout : ";
                        cin >> n;
                        cout << endl;
                        if (n == 1)
                        {
                            viewCustomer();
                            cout << endl;
                        }else if (n == 2)
                        {
                            viewAllCustomer();
                             cout << endl;
                        }else if (n == 3)
                        {
                            changeStatus();
                             cout << endl;
                        }else if (n == 4)
                        {
                            changeCustomerInfo();
                             cout << endl;
                        }else if (n  == 5)
                        {
                            addCustomer();
                             cout << endl;
                        }else if (n  == 6)
                        {
                            removeCutomer();
                             cout << endl;
                        }else if (n  == 7)
                        {
                            showTransactionBid();
                             cout << endl;
                        }else if(n == 8)
                        {
                            cout << "Thanx for your time !!!!";
                            return;
                        }else{
                            cout<<"Wrong choice ." <<endl;
                            showfunction();
                        }                       
                        }
                    }

            void viewCustomer(){
                if(adminAuthentication()){
                    string id ;
                    cout << "Enter the Account Number : ";
                    cin>> id;
                    cout << endl;
                    
                    if(checkID(id)){
                        cout << "Name: " << customerData[id]["name"] << endl;
                        cout << "Father Name: " << customerData[id]["fatherName"] << endl;
                        cout << "CNIC: " << customerData[id]["cnic"] << endl;
                        cout << "Phone Number: " << customerData[id]["phoneNumber"] << endl;
                        cout << "Email: " << customerData[id]["email"] << endl;
                        cout << "Account Type: " << customerData[id]["accountType"] << endl;
                        cout << "Account Status: " << customerData[id]["accountStatus"] << endl;
                        cout << "PIN: " << customerData[id]["pin"] << endl;
                        cout << "Balance: " << customerData[id]["balance"] << endl;
                        cout << endl;
                    }else{
                        cout<<"Id not Found"<<endl;
                        cout << endl;
                    }
                }else{
                    cout <<"Authentication Failed"<<endl;
                    cout << endl;
                }
                showfunction();
            }

            void changeStatus(){
                if(adminAuthentication()){
                    string id ;
                    cout << "Enter the Account Number to change status : ";
                    cin>> id;
                    if (checkID(id))
                    {
                        int n;
                        cout << "1 to make Active \n2 to Block : ";
                        cin >> n;
                        if (n == 1)
                        {
                            customerData[id]["accountStatus"] = "active";
                        }else{
                            customerData[id]["accountStatus"] = "blocked";
                        }
                        cout << "Successfilly changed account status ";
                        savecustomer();
                    }else{
                        cout << "U entered wrong ID . ";
                    }  
                }else{
                    cout<<"Authentication Failed";
                }
                showfunction();
            }
            
            void viewAllCustomer(){
                if(adminAuthentication()){
                    for(auto& cutomers : customerData.items()){
                        cout << "Account Number : " << cutomers.value()["accountNumber"] << endl;
                        cout << "Name : " << cutomers.value()["name"] << endl;
                        cout << "Father Name : " << cutomers.value()["fatherName"] << endl;
                        cout << "Cnic : " << cutomers.value()["cnic"] << endl;
                        cout << "Phone Number : " << cutomers.value()["phoneNumber"] << endl;
                        cout << "Email : " << cutomers.value()["email"] << endl;
                        cout << "Account Type : " << cutomers.value()["accountType"] << endl;
                        cout << "Account Status : " << cutomers.value()["accountStatus"] << endl;
                        cout << "Pin : " << cutomers.value()["pin"] << endl;
                        cout << "Balance : " << cutomers.value()["balance"] << endl;
                        cout <<endl;
                    }
                }
                showfunction();
            }

            void changeCustomerInfo(){
                if(adminAuthentication()){
                    string id ;
                    cout << "Enter the Account Number for changes : ";
                    cin>> id;
                    if (checkID(id))
                    {
                        getCustomerInfo();
                        customerData[id] = {
                        {"name" , name},
                        {"fatherName" , fatherName},
                        {"cnic" , cnic},
                        {"phoneNumber" , phoneNumber},
                        {"email" , email},
                        {"accountType" , accountType},
                        {"accountStatus" , accountStatus},
                        {"pin" , pin},
                        {"balance" , balance},
                        {"accountNumber" , id}
                    };
                    savecustomer();
                    }else{
                      cout << "Wrong ID"<<endl;  
                    } 
                }else{
                    cout << "Authentication failed"<<endl;
                }
                showfunction();
            }

            void addCustomer(){
                if(adminAuthentication()){
                    string Id = NextID();
                    getCustomerInfo();
                    customerData[Id] = {
                        {"name" , name},
                        {"fatherName" , fatherName},
                        {"cnic" , cnic},
                        {"phoneNumber" , phoneNumber},
                        {"email" , email},
                        {"accountType" , accountType},
                        {"accountStatus" , accountStatus},
                        {"pin" , pin},
                        {"balance" , balance},
                        {"accountNumber" , Id}
                    };
                    savecustomer();
                }else
                {
                    cout << "Authentication Failed";
                }
                showfunction();
            }

            void removeCutomer(){
                if(adminAuthentication()){
                    string id ;
                    cout << "Enter the Account Number to delete: ";
                    cin>> id;
                    if (checkID(id))
                    {
                        customerData.erase(id);
                        savecustomer();
                        cout << "Removed successfully.";
                    }else{
                        cout << "U entered wrong ID : " << endl;
                    }
                }else{
                    cout<< "Authentication failed" << endl;
                }
                showfunction();
            }

            void showTransactionBid(){
                string id;
                cout << "Enter the Account Number : ";
                cin >> id;
                cout << "-------------------------"<<endl<<endl;
                for (auto i :  transactionData.items())
                {
                    string check = i.value()["accountNumber"];
                    if (check == id)
                    {
                        cout << "Acount Number : " <<i.value()["accountNumber"] << endl;
                        cout << "Balance Before : " << i.value()["balanceBefore"] << endl;
                        cout << "Current Balance : " << i.value()["currentBalance"] << endl;
                        cout << "Transaction Id: " << i.value()["transactionId"] << endl;
                        cout << "-------------------------"<<endl<<endl;
                    }
                }
            }

// -----------------------------------------------------------------------------------------
            void getCustomerInfo(){
                cout << "Enter customer name : ";
                cin >> name;
                cout << "Enter customer father name : ";
                cin >> fatherName;
                do{
                    cout << "Enter customer cnic : ";
                    cin >> cnic;
                    } while (cnic.length() != 13);
                do{
                    cout << "Enter customer phoneNumber : ";
                    cin >> phoneNumber;
                    } while (cnic.length() != 11);
                cout << "Enter customer email : ";
                cin >> email;
                do
                {
                    cout << "Enter customer accountType (saving/current) : ";
                    cin >> accountType;
                } while (accountType != "saving" && accountType != "current");
                 do
                {
                    cout << "Enter customer accountStatus (active/block) : ";
                    cin >> accountStatus;
                } while (accountStatus != "active"&& accountStatus != "block");
                do{
                        cout << "Enter PIN (4 digit): ";
                        cin >> pin;
                    } while (!validPin(pin));
                do{
                        cout << "Enter initial balance: ";
                        cin >> balance;
                    } while (balance < 0);
            }

            string NextID(){
               int next_id = 0;
                for(auto& id : customerData.items()){
                    next_id = max(next_id , stoi(id.key() ));
                }
                return to_string(next_id+1);
            }
            
            bool adminAuthentication() {
                string pass;
                cout << "Enter the pass : ";
                cin >> pass;
                if(pass == adminPass){
                    return true;
                }else{
                    return false;
                }
            }

            bool checkID(string id){
                for(auto& checkID : customerData.items()){
                    if (id == checkID.key())
                    {
                        return true;
                    }
                }
                return false;
            }

            bool validPin(string pin){
                    if (pin.length() != 4)
                        return false;

                    for (char c : pin)
                    {
                        if (!isdigit(c))
                            return false;
                    }

                    return true;
                }
        public :

            ADMIN(){
                this->adminPass = "admin1122";
            }

            void login(){
                string pass;
                cout << "Enter the admin pass : " ;
                cin >> pass;
                if (pass == adminPass)
                {
                    showfunction();
                }else{
                    cout << "Wrong pass !!!";
                }
            }
         
        
    };

    class CUSTOMER : private BMS{
        private : 
            string id , pin;
            double balanceBefore , currentBalance;

        
            void showfunction(){
                        int n;
                        while (1)
                        {
                        cout<<"\n1 for Deposit Money \n2 for Withdraw Money \n3 for Check Balance \n";
                        cout<<"4 for Check Info \n5 for change Info \n6 for Transaction \n";
                        cout <<"7 for logout : ";
                        cin >> n;
                         cout << endl;
                        if (n == 1)
                        {
                            depositMoney();
                            cout << endl;
                        }else if (n == 2)
                        {
                            withdrawMoney();
                             cout << endl;
                        }else if (n == 3)
                        {
                            Balance();
                             cout << endl;
                        }else if (n == 4)
                        {
                            checkInfo();
                             cout << endl;
                        }else if (n  == 5)
                        {
                            changeInfo();
                             cout << endl;
                        }else if (n  == 6)
                        {
                            showTransaction();
                             cout << endl;
                        }else if(n == 7)
                        {
                            cout << "Thanx for your time !!!!";
                            return; 
                        }else{
                            cout<<"Wrong choice ." <<endl;
                            showfunction();
                        }                       
                        }
                    }

            void depositMoney(){
                    double deposit;
                    cout << "Enter the amount u want to deposit : ";
                    cin >> deposit;
                    if(deposit > 0){
                        currentBalance = balanceBefore + deposit;
                        customerData[id]["balance"] = currentBalance;
                        savecustomer();
                        cout << "After deposit Balance : " << customerData[id]["balance"] <<endl;
                        showfunction();
                        createTransaction(balanceBefore , currentBalance , id);
                }
            }

            void withdrawMoney(){
                    double withdraw;
                    cout << "Enter the amount u want to withdraw : ";
                    cin >> withdraw;
                    if((balanceBefore >= withdraw) && (withdraw > 0)){
                        currentBalance =  balanceBefore - withdraw;
                        customerData[id]["balance"] = currentBalance;
                        savecustomer();
                        cout << "After deposit Balance : " << customerData[id]["balance"] <<endl;
                        createTransaction(balanceBefore , currentBalance , id);
                    }else{
                        cout << "Your balance is less than deposit money"<<endl;
                    }
                    showfunction();
            }

            void Balance(){         
                    double balance;
                    balance = customerData[id]["balance"];
                    cout << "Your balance is : "<< balance << endl;
                    showfunction();
            }

            void checkInfo(){    
                        cout << "Name: " << customerData[id]["name"] << endl;
                        cout << "Father Name: " << customerData[id]["fatherName"] << endl;
                        cout << "CNIC: " << customerData[id]["cnic"] << endl;
                        cout << "Phone Number: " << customerData[id]["phoneNumber"] << endl;
                        cout << "Email: " << customerData[id]["email"] << endl;
                        cout << "Account Type: " << customerData[id]["accountType"] << endl;
                        cout << "Account Status: " << customerData[id]["accountStatus"] << endl;
                        cout << "PIN: " << customerData[id]["pin"] << endl;
                        cout << "Balance: " << customerData[id]["balance"] << endl;
                        showfunction();
                    }

            void changeInfo(){
                    string change;
                    if(checkID(id)){
                        int n ;
                        cout<<"1 to change pin \n2 to change phone number \n3 to change email : ";
                        cin >> n;
                        if(n == 1){
                            cout << "Enter the pin (4 digit): ";
                            cin >> change;
                            customerData[id]["pin"] = change; 
                        }else if(n==2){
                            cout << "Enter the phone number : ";
                            cin >> change;
                            customerData[id]["phoneNumber"] = change; 
                        }else{
                            cout << "Enter the email : ";
                            cin >> change;
                            customerData[id]["email"] = change;
                        }
                        cout << "Sucessfully changed." << endl;
                        savecustomer();
                    }
                    showfunction();
                }

            void showTransaction(){
                    string nextId =to_string( stoi(newId())-1);
                    if (transactionData[nextId]["accountNumber"] == id )
                    {                    
                    cout << "Acount Number : " << id << endl;
                    cout << "Balance Before : " << balanceBefore << endl;
                    cout << "Current Balance : " << currentBalance << endl;
                    cout << "Transaction Id: " << nextId << endl;
                    }else
                    {
                        cout << "Please make a transaction first !!!"<<endl;
                    }
                    
                }
// -----------------------------------------------------------------------------------------
            bool checkID(string id){
                for(auto& checkID : customerData.items()){
                    if (id == checkID.key())
                    {
                        return true;
                    }
                }
                return false;
            }

            double getBalance(){
                    double balance;
                    balance = customerData[id]["balance"];
                    cout << "Your balance is : "<< balance << endl;
                    return balance;
            }

            public :
            

                void login(){
                cout <<"Enter your account number : ";
                cin >> id;
                if(checkID(id)){
                    if(customerData[id]["accountStatus"] == "active"){
                        cout << "Enter your pin : ";
                        cin >> pin;
                        if(customerData[id]["pin"] == pin){
                            balanceBefore = customerData[id]["balance"];
                            currentBalance = balanceBefore;
                            showfunction();
                        }else{
                            cout << "Wrong pin . " << endl;
                        }
                    }else{
                        cout << "Your Account is Blocked"<< endl;
                    }
                }else{
                    cout << "Wrong id !!"<< endl;
                }
            }

                
                
    };

int main()
{
    int n;
    cout<<"1 for login as admin \n2 for logim as customer : ";
    cin >> n;
    if (n==1)
    {
        ADMIN a1;
        a1.login();
    }else if (n==2)
    {
        CUSTOMER c1;
        c1.login();
    }else
    {
        cout<<"Wrong choice : ";
    }

    return 0;
}
