#include<iostream>
#include<fstream>
using namespace std;
class BankAccount
{
    int accNo;
    char name[50];
    float balance;
public:
    void createAccount()
    {
        cout<<"\nEnter Account Number: ";
        cin>>accNo;
        cout<<"Enter Name: ";
        cin>>name;
        cout<<"Enter Initial Balance: ";
        cin>>balance;
    }
    void display()
    {
        cout<<"\nAcc No: "<<accNo<<"|Name: "<<name<<"|Balance: "<<balance<<endl;
    }
    int getAccNo() 
    {
        return accNo;
    }
    void deposit() 
    {
        float amt;
        cout<<"Enter amount to deposit: ";
        cin>>amt;
        balance+=amt;
    }
    void withdraw()
    {
        float amt;
        cout<<"Enter amount to withdraw: ";
        cin>>amt;
        if(amt<=balance)
            balance-=amt;
        else
            cout<<"Insufficient balance!\n";
    }
};
void addAccount() 
{
    BankAccount a;
    ofstream file("bank.txt", ios::app);
    a.createAccount();
    file.write((char*)&a, sizeof(a));
    file.close();
    cout<<"Account created!\n";
}
void displayAccounts() 
{
    BankAccount a;
    ifstream file("bank.txt");
    while(file.read((char*)&a, sizeof(a))) 
    {
        a.display();
    }
    file.close();
}
void transaction(int accNo, int type) 
{
    BankAccount a;
    fstream file("bank.txt",ios::in | ios::out | ios::binary);
    while(file.read((char*)&a,sizeof(a))) 
    {
        if(a.getAccNo()==accNo) 
        {
            if(type==1)a.deposit();
            else if(type == 2)a.withdraw();
            int pos=-1*sizeof(a);
            file.seekp(pos,ios::cur);
            file.write((char*)&a,sizeof(a));
            cout<<"Transaction successful!\n";
            return;
        }
    }
    cout<<"Account not found!\n";
    file.close();
}
void checkBalance(int accNo) 
{
    BankAccount a;
    ifstream file("bank.txt",ios::binary);
    while(file.read((char*)&a,sizeof(a))) {
        if(a.getAccNo() == accNo)
        {
            a.display();
            return;
        }
    }
    cout<<"Account not found!\n";
}
int main()
{
    int choice,accNo;
    do
    {
        cout<<"\n===== BANK MANAGEMENT SYSTEM =====\n";
        cout<<"1. Create Account\n";
        cout<<"2. Display All Accounts\n";
        cout<<"3. Deposit\n";
        cout<<"4. Withdraw\n";
        cout<<"5. Check Balance\n";
        cout<<"6. Exit\n";
        cout<<"Enter choice: ";
        cin>>choice;
    switch(choice)
    {
        case 1:addAccount(); 
        break;
        case 2:displayAccounts(); 
        break;
        case 3:
        cout<<"Enter Account No: ";
        cin>>accNo;
        transaction(accNo,1);
        break;
        case 4:
        cout<<"Enter Account No: ";
        cin>>accNo;
        transaction(accNo,2);
        break;
        case 5:
        cout<<"Enter Account No: ";
        cin>>accNo;
        checkBalance(accNo);
        break;
        }

    }while(choice!=6);
 return 0;
}