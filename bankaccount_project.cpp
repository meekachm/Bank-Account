//Libraries
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

//Class declaration - Bank Account Default
class bankAccount
{
protected:
    string Name;
    int AcctNumber;
    double Balance;
    double withdrawalTotal;
    double depositTotal;
    int numDeposits;
    int numWithdrawals;
    string accountType;

public:
    //Account Constructor
    bankAccount(int acctNum, string name, double initialBalance)
    {
        AcctNumber = acctNum;
        Name = name;
        Balance = initialBalance;
        depositTotal = 0.0;
        withdrawalTotal = 0.0;
        numDeposits = 0;
        numWithdrawals = 0;
        accountType = ' ';
    }

    ~bankAccount(void) {}

    //Accessors Functions
    string get_Name()
    {
        return Name;
    }

    int get_AcctNumber()
    {
        return AcctNumber;
    }

    double get_Balance()
    {
        return Balance;
    }

    int getNumDeposits()
    {
        return numDeposits;
    }

    int getNumWithdrawals()
    {
        return numWithdrawals;
    }

    string getaccountType()
    {
        return accountType;
    }

    void deposit(double amount)
    {
        Balance += amount;
        cout << endl;
        cout << "$" << amount << " has been deposited to your account." << endl;

        depositTotal += amount;
        numDeposits++;
    }

    virtual void withdraw(double amount) = 0;
    virtual void printStatement()
    {
        cout << setw(64) << setfill('-') << "" << setfill(' ') << endl;
        cout << setw(23) << "" << "MONTHLY STATEMENT" << endl;
        cout << setw(64) << setfill('-') << "" << setfill(' ') << endl;
        cout << setw(25) << "Account Holder:   " << Name << endl;
        cout << setw(25) << "Account Type:   " << accountType << endl;
        cout << setw(25) << "Account #:   " << AcctNumber << endl;
        cout << endl;
        cout << setw(25) << "No of Deposits:   " << numDeposits << endl;
        cout << setw(26) << "Total of Deposits:   $" << depositTotal << endl;
        cout << setw(25) << "No of Withdrawal:   " << numWithdrawals << endl;
        cout << setw(26) << "Total of Withdrawals:   $" << withdrawalTotal << endl;
        cout << endl;
        cout << setw(26) << "Current Balance:   $" << Balance << endl;
        cout << endl;
    }

    virtual void printStatementCoD()
    {
        cout << setw(64) << setfill('-') << "" << setfill(' ') << endl;
        cout << setw(23) << "" << "MONTHLY STATEMENT" << endl;
        cout << setw(64) << setfill('-') << "" << setfill(' ') << endl;
        cout << setw(25) << "Account Holder:   " << Name << endl;
        cout << setw(25) << "Account Type:   " << accountType << endl;
        cout << setw(25) << "Account #:   " << AcctNumber << endl;
        cout << endl;
        cout << setw(26) << "Current Balance:   $" << Balance << endl;
        cout << endl;
    }

    virtual void printSummary()
    {
        cout << setw(64) << setfill('-') << "" << setfill(' ') << endl;
        cout << setw(24) << "" << "ACCOUNT SUMMARY" << endl;
        cout << setw(64) << setfill('-') << "" << setfill(' ') << endl;
        cout << setw(25) << "Account Holder:   " << Name << endl;
        cout << setw(25) << "Account Type:   " << accountType << endl;
        cout << setw(25) << "Account #:   " << AcctNumber << endl;
        cout << setw(26) << "Current Balance:   $" << Balance << endl;
    }

};


//Class declaration - Checking Account
class checkingAccount :
    public bankAccount
{
public:
    checkingAccount(int acctNum, string name, double initialBalance)
        : bankAccount(acctNum, name, initialBalance)
    {
    }
    ~checkingAccount(void) {}

    virtual void writeCheck(double amount) = 0;

    void withdraw(double amount)
    {
        if (Balance - amount < 0)
        {
            cout << "DECLINED: Insufficient funds." << endl;
            return;
        }
        if (Balance - amount < MinimumBalance)
        {
            cout << "DECLINED: Insufficient funds. Minimum balance required." << endl;
            return;
        }

        Balance -= amount;
        cout << endl;
        cout << "$" << amount << " was withdrawn from your account." << endl;

        withdrawalTotal += amount;
        numWithdrawals++;

    }

    void printStatement()
    {
    }

protected:
    double InterestRate;
    int ChecksRemaining;
    double MinimumBalance;
};


const int MAX_CHECKS = 5;
const double SVC_CHARGE = 10.0l;


//Class declaration - Checking Account with Service Charge
class serviceChargeChecking :
    public checkingAccount
{
public:
    serviceChargeChecking(int acctNum, string name, double initialBalance)
        : checkingAccount(acctNum, name, initialBalance)
    {
        InterestRate = 0; // No interest
        ChecksRemaining = MAX_CHECKS; // Limit of 5 checks
        MinimumBalance = 0; // No minimum balance

        accountType = "Checking Account with Service Charge";
    }

    ~serviceChargeChecking(void) {}

    void writeCheck(double amount)
    {
        if (ChecksRemaining == 0)
        {
            cout << "DECLINED: Insufficient funds." << endl;
            return;
        }
        if (Balance - amount < 0)
        {
            cout << "DECLINED: Insufficient funds." << endl;
            return;
        }

        ChecksRemaining--;
        Balance -= amount;
    }



    void printSummary()
    {
        bankAccount::printSummary();
        cout << setw(25) << "Checks Remaining:   " << ChecksRemaining << endl;
        cout << setw(26) << "Monthly Service Fee:   $" << SVC_CHARGE << endl;
        cout << endl;
        cout << setw(37) << "No Interest " << endl;
        cout << setw(41) << "No Minimum Balance " << endl;
        cout << setw(64) << setfill('-') << "" << setfill(' ') << endl;
    }

    void printStatement()
    {
        bankAccount::printStatement();
        cout << setw(25) << "Checks Remaining:   " << ChecksRemaining << endl;
        cout << setw(26) << "Monthly Service Fee:   $" << SVC_CHARGE << endl;
        cout << endl;
        cout << setw(37) << "No Interest " << endl;
        cout << setw(41) << "No Minimum Balance " << endl;
        cout << setw(64) << setfill('-') << "" << setfill(' ') << endl;
    }
};


//Class declaration - Checking Account with No Service Charge
class noServiceChargeChecking :
    public checkingAccount
{
public:
    noServiceChargeChecking(int acctNum, string name, double initialBalance)
        : checkingAccount(acctNum, name, initialBalance)
    {
        InterestRate = 0.5;
        ChecksRemaining = -1;
        MinimumBalance = 500;

        accountType = "Checking Account with No Service Charge";
    }

    ~noServiceChargeChecking(void) {}

    void writeCheck(double amount)
    {
        if (Balance - amount < 0)
        {
            cout << endl;
            cout << "DECLINED: Insufficient funds." << endl;
            return;
        }

        Balance -= amount;
    }

    void printSummary()
    {
        bankAccount::printSummary();
        cout << setw(25) << "Interest Rate:   " << InterestRate << "%" << endl;
        cout << setw(26) << "Minimum Balance:   $" << MinimumBalance << endl;
        cout << endl;
        cout << setw(44) << "Unlimited Checks   " << endl;
        cout << setw(47) << "No Monthly Service Fee   " << endl;
        cout << setw(64) << setfill('-') << "" << setfill(' ') << endl;
    }

    void printStatement()
    {
        bankAccount::printStatement();
        cout << setw(25) << "Interest Rate:   " << InterestRate << "%" << endl;
        cout << setw(26) << "Minimum Balance:   $" << MinimumBalance << endl;
        cout << endl;
        cout << setw(44) << "Unlimited Checks   " << endl;
        cout << setw(47) << "No Monthly Service Fee   " << endl;
        cout << setw(64) << setfill('-') << "" << setfill(' ') << endl;
    }

};


//Class declaration - Checking Account with High Interest
class highInterestChecking :
    public noServiceChargeChecking
{
public:
    highInterestChecking(int acctNum, string name, double initialBalance)
        : noServiceChargeChecking(acctNum, name, initialBalance)
    {
        InterestRate = 1.6;
        ChecksRemaining = -1;
        MinimumBalance = 1000;

        accountType = "Checking Account with High Interest";
    }

    ~highInterestChecking(void) {}
};


//Class declaration - Savings Account
class savingsAccount :
    public bankAccount
{
public:
    savingsAccount(int acctNum, string name, double initialBalance)
        : bankAccount(acctNum, name, initialBalance)
    {
        InterestRate = 2.3;

        accountType = "Saving Account";
    }

    ~savingsAccount(void)
    {
    }

    void withdraw(double amount)
    {
        if (Balance - amount < 0)
        {
            cout << endl;
            cout << "DECLINED: Insufficient funds." << endl;
            return;
        }

        Balance -= amount;
        cout << endl;
        cout << "$" << amount << " was withdrawn from your account." << endl;

        withdrawalTotal += amount;
        numWithdrawals++;
    }

    void printSummary()
    {
        bankAccount::printSummary();
        cout << setw(25) << "Interest Rate:   " << InterestRate << "%" << endl << endl;
        cout << setw(64) << setfill('-') << "" << setfill(' ') << endl;
    }

    void printStatement()
    {
        bankAccount::printStatement();
        cout << setw(25) << "Interest Rate:   " << InterestRate << "%" << endl << endl;
        cout << setw(64) << setfill('-') << "" << setfill(' ') << endl;
    }

protected:
    double InterestRate;

};

//Class declaration - Savings Account with High Interest
class highInterestSavings :
    public savingsAccount
{
public:
    highInterestSavings(int acctNum, string name, double initialBalance)
        : savingsAccount(acctNum, name, initialBalance)
    {
        MinimumBalance = 5000;

        accountType = "Saving Account with High Interest";
    }

    ~highInterestSavings(void) {}

    void withdraw(double amount)
    {
        if (Balance - amount < 0)
        {
            cout << endl;
            cout << "DECLINED: Insufficient funds." << endl;
            return;
        }

        if (Balance - amount < MinimumBalance)
        {
            cout << endl;
            cout << "DECLINED: Insufficient funds. Minimum balance required." << endl;
            return;
        }

        Balance -= amount;
        cout << endl;
        cout << "$" << amount << " was withdrawn from your account." << endl;

        withdrawalTotal += amount;
        numWithdrawals++;
    }

    void printSummary()
    {
        bankAccount::printSummary();
        cout << setw(25) << "Interest Rate:   " << InterestRate << "%" << endl;
        cout << setw(26) << "Minimum Balance:   $" << MinimumBalance << endl << endl;
        cout << setw(64) << setfill('-') << "" << setfill(' ') << endl;
    }

    void printStatement()
    {
        bankAccount::printStatement();
        cout << setw(25) << "Interest Rate:   " << InterestRate << "%" << endl;
        cout << setw(26) << "Minimum Balance:   $" << MinimumBalance << endl << endl;
        cout << setw(64) << setfill('-') << "" << setfill(' ') << endl;
    }

protected:
    double MinimumBalance;

};


//Class declaration - Certificate of Deposit
class certificateOfDeposit :
    public bankAccount
{
public:
    certificateOfDeposit(int acctNum, string name, double initialBalance, int matMon)
        : bankAccount(acctNum, name, initialBalance)
    {
        MaturityMonths = matMon;
        CurrentMonth = 1;
        InterestRate = 5;

        accountType = "Certificate of Deposit";
    }

    ~certificateOfDeposit(void) {}

    //Withdraw Certificate of Deposit
    void withdraw(double NewBalance)
    {
        NewBalance = Balance - (Balance * 0.2);
        cout << endl;
        cout << setw(64) << setfill('-') << "" << setfill(' ') << endl;
        cout << "Your total amount withdrawn is $" << NewBalance << endl;
        cout << setw(64) << setfill('-') << "" << setfill(' ') << endl;

        Balance -= Balance;
    }

    void printSummary()
    {
        //Summary/Statement if CoD was withdrawn
        if (Balance <= 0)
        {
            cout << endl;
            cout << setw(64) << setfill('-') << "" << setfill(' ') << endl;
            cout << "You currently don't have any Certificates of Deposit." << endl;
            cout << setw(64) << setfill('-') << "" << setfill(' ') << endl;
        }
        else
        {
            bankAccount::printSummary();
            cout << setw(25) << "Interest Rate:   " << InterestRate << "%" << endl;
            cout << setw(25) << "Maturity Months:   " << MaturityMonths << endl;
            cout << setw(25) << "Current Month:   " << CurrentMonth << endl;
            cout << endl;
            cout << setw(48) << "*** Early-Withdrawal Penalty ***" << endl;
            cout << setw(50) << "An overall balance reduction of 20%" << endl;
            cout << setw(64) << setfill('-') << "" << setfill(' ') << endl;
        }
    }

    void printStatement()
    {
        bankAccount::printStatementCoD();
        cout << setw(25) << "Interest Rate:   " << InterestRate << "%" << endl;
        cout << setw(25) << "Maturity Months:   " << MaturityMonths << endl;
        cout << setw(25) << "Current Month:   " << CurrentMonth << endl;
        cout << endl;
        cout << setw(48) << "*** Early-Withdrawal Penalty ***" << endl;
        cout << setw(50) << "An overall balance reduction of 20%." << endl;
        cout << setw(64) << setfill('-') << "" << setfill(' ') << endl;
    }

private:
    double InterestRate;
    int MaturityMonths;
    int CurrentMonth;
};

//Ouput selection for Checking Account with Service Charge
void CheckingWithService()
{
    serviceChargeChecking acct(501001, "Miki Nakatani", 362.83);

    char input = 0;
    double amount;

    cout << endl;
    acct.printSummary();
    cout << endl;

    while (input != 'x')
    {
        cout << "Select a transaction:" << endl;
        cout << endl;
        cout << " [1] WITHDRAW" << endl;
        cout << " [2] DEPOSIT" << endl;
        cout << " [3] PRINT SUMMARY" << endl;
        cout << " [4] PRINT MONTHLY STATEMENT" << endl;
        cout << " [5] WRITE CHECK" << endl;
        cout << " [x] EXIT" << endl;
        cout << endl;
        cout << "Enter selection: ";
        cin >> input;

        switch (input)
        {
        case '1':
            cout << "Enter amount: ";
            cin >> amount;
            acct.withdraw(amount);
            break;
        case '2':
            cout << "Enter amount: ";
            cin >> amount;
            acct.deposit(amount);
            break;
        case '3':
            acct.printSummary();
            break;
        case '4':
            acct.printStatement();
            break;
        case '5':
            cout << "Enter amount: ";
            cin >> amount;
            acct.writeCheck(amount);
            break;
        case 'x':
            break;
        default:
            cout << "Invalid Selection" << endl;
            break;
        }

        cout << endl;
    }
}

//Ouput selection for Checking Account with No Service Charge
void CheckingNoService()
{
    noServiceChargeChecking acct(501002, "Keiko Azuma", 922.36);
    char input = 0;
    double amount;

    cout << endl;
    acct.printSummary();
    cout << endl;

    while (input != 'x')
    {
        cout << "Select a transaction:" << endl;
        cout << endl;
        cout << " [1] WITHDRAW" << endl;
        cout << " [2] DEPOSIT" << endl;
        cout << " [3] PRINT SUMMARY" << endl;
        cout << " [4] PRINT MONTHLY STATEMENT" << endl;
        cout << " [5] WRITE CHECK" << endl;
        cout << " [x] EXIT" << endl;
        cout << endl;
        cout << "Enter selection: ";
        cin >> input;

        switch (input)
        {
        case '1':
            cout << "Enter amount: ";
            cin >> amount;
            acct.withdraw(amount);
            break;
        case '2':
            cout << "Enter amount: ";
            cin >> amount;
            acct.deposit(amount);
            break;
        case '3':
            acct.printSummary();
            break;
        case '4':
            acct.printStatement();
            break;
        case '5':
            cout << "Enter amount: ";
            cin >> amount;
            acct.writeCheck(amount);
            break;
        case 'x':
            break;
        default:
            cout << "Invalid Selection" << endl;
            break;
        }

        cout << endl;
    }

}

//Ouput selection for Checking Account with High Interest
void CheckingHighInterest()
{
    highInterestChecking acct(501003, "Takeru Satoh", 3848.64);

    char input = 0;
    double amount;

    cout << endl;
    acct.printSummary();
    cout << endl;

    while (input != 'x')
    {
        cout << "Select a transaction:" << endl;
        cout << endl;
        cout << " [1] WITHDRAW" << endl;
        cout << " [2] DEPOSIT" << endl;
        cout << " [3] PRINT SUMMARY" << endl;
        cout << " [4] PRINT MONTHLY STATEMENT" << endl;
        cout << " [5] WRITE CHECK" << endl;
        cout << " [X] EXIT" << endl;
        cout << endl;
        cout << "Enter selection: ";
        cin >> input;

        switch (input)
        {
        case '1':
            cout << "Enter amount: ";
            cin >> amount;
            acct.withdraw(amount);
            break;
        case '2':
            cout << "Enter amount: ";
            cin >> amount;
            acct.deposit(amount);
            break;
        case '3':
            acct.printSummary();
            break;
        case '4':
            acct.printStatement();
            break;
        case '5':
            cout << "Enter amount: ";
            cin >> amount;
            acct.writeCheck(amount);
            break;
        case 'x':
            break;
        default:
            cout << "Invalid Selection" << endl;
            break;
        }

        cout << endl;
    }
}

//Ouput selection for Saving Account
void Savings()
{
    savingsAccount acct(951001, "Hiro Mizushima", 1637.28);

    char input = 0;
    double amount;

    cout << endl;
    acct.printSummary();
    cout << endl;

    while (input != 'x')
    {
        cout << "Select a transaction:" << endl;
        cout << endl;
        cout << " [1] WITHDRAW" << endl;
        cout << " [2] DEPOSIT" << endl;
        cout << " [3] PRINT SUMMARY" << endl;
        cout << " [4] PRINT MONTHLY STATEMENT" << endl;
        cout << " [X] EXIT" << endl;
        cout << endl;
        cout << "Enter selection: ";
        cin >> input;

        switch (input)
        {
        case '1':
            cout << "Enter amount: ";
            cin >> amount;
            acct.withdraw(amount);
            break;
        case '2':
            cout << "Enter amount: ";
            cin >> amount;
            acct.deposit(amount);
            break;
        case '3':
            acct.printSummary();
            break;
        case '4':
            acct.printStatement();
            break;
        case 'x':
            break;
        default:
            cout << "Invalid Selection" << endl;
            break;
        }

        cout << endl;
    }
}

//Ouput selection for Saving Account with High Interest
void SavingsHighInterest()
{
    highInterestSavings acct(951002, "Ayaka Iida", 12615.91);

    char input = 0;
    double amount;

    cout << endl;
    acct.printSummary();
    cout << endl;

    while (input != 'x')
    {
        cout << "Select a transaction:" << endl;
        cout << endl;
        cout << " [1] WITHDRAW" << endl;
        cout << " [2] DEPOSIT" << endl;
        cout << " [3] PRINT SUMMARY" << endl;
        cout << " [4] PRINT MONTHLY STATEMENT" << endl;
        cout << " [X] EXIT" << endl;
        cout << endl;
        cout << "Enter selection: ";
        cin >> input;

        switch (input)
        {
        case '1':
            cout << "Enter amount: ";
            cin >> amount;
            acct.withdraw(amount);
            break;
        case '2':
            cout << "Enter amount: ";
            cin >> amount;
            acct.deposit(amount);
            break;
        case '3':
            acct.printSummary();
            break;
        case '4':
            acct.printStatement();
            break;
        case 'x':
            break;
        default:
            cout << "Invalid Selection" << endl;
            break;
        }

        cout << endl;
    }
}

//Ouput selection for Certificate of Deposit
void CertificateOfDeposit()
{
    certificateOfDeposit acct(821001, "Mai Sakurai", 10000, 6);

    char input = 0;
    double NewBalance{};

    cout << endl;
    acct.printSummary();
    cout << endl;

    while (input != 'x')
    {
        cout << "Select a transaction:" << endl;
        cout << endl;
        cout << " [1] WITHDRAW" << endl;
        cout << " [2] PRINT SUMMARY" << endl;
        cout << " [3] PRINT MONTHLY STATEMENT" << endl;
        cout << " [X] EXIT" << endl;
        cout << endl;
        cout << "Enter selection: ";
        cin >> input;

        switch (input)
        {
        case '1':
            cout << endl;
            cout << setw(64) << setfill('-') << "" << setfill(' ') << endl;
            cout << setw(42) << "!!!!IMPORTANT NOTICE!!!!" << endl;
            cout << setw(56) << "A 20% early withdrawal fee will be deducted to " << endl;
            cout << setw(42) << "your overall balance." << endl;
            cout << setw(64) << setfill('-') << "" << setfill(' ') << endl;
            cout << endl;
            cout << "Do you still wish to withdraw?" << endl;
            cout << endl;
            cout << " [Y] YES" << endl;
            cout << " [N] NO" << endl;
            cout << endl;
            cout << "Enter selection: ";
            cin >> input;
            switch (input)
            {
            case 'y':
                acct.withdraw(NewBalance);

                break;
            case 'n':
                CertificateOfDeposit();
                break;
            }
            break;
        case '2':
            acct.printSummary();
            break;
        case '3':
            acct.printStatement();
            break;
        case 'x':
            break;
        default:
            cout << "Invalid Selection" << endl;
            break;
        }

        cout << endl;
    }
}


//Ouput Main Menu
int main()
{
    char input;
    cout << setw(64) << setfill('=') << "" << setfill(' ') << endl;
    cout << right << setw(40) << "WELCOME TO kURRA bANK" << endl;
    cout << setw(64) << setfill('=') << "" << setfill(' ') << endl;
    cout << "What would you like to do today?" << endl;
    cout << endl;
    cout << setw(35) << " [1] CHECKING WITH SERVICE CHARGE" << endl;
    cout << setw(38) << " [2] CHECKING WITH NO SERVICE CHARGE" << endl;
    cout << setw(34) << " [3] CHECKING WITH HIGH INTEREST" << endl;
    cout << setw(14) << " [4] SAVINGS" << endl;
    cout << setw(33) << " [5] SAVINGS WITH HIGH INTEREST" << endl;
    cout << setw(29) << " [6] CERTIFICATE OF DEPOSIT" << endl;
    cout << endl;
    cout << "Enter your selection: ";
    cin >> input;

    switch (input)
    {
    case '1':
        CheckingWithService();
        break;
    case '2':
        CheckingNoService();
        break;
    case '3':
        CheckingHighInterest();
        break;
    case '4':
        Savings();
        break;
    case '5':
        SavingsHighInterest();
        break;
    case '6':
        CertificateOfDeposit();
        break;
    default:
        cout << "Invalid Selection" << endl;
        break;
    }
}
