#pragma once

#include <iostream>
#include "clsScreen.h"
#include "cls_bank_client.h"
#include "clsInputValidate.h"

class clsDepositScreen :
    protected clsScreen
{
private:

    static void _PrintClient(cls_bank_client Client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << Client.first_name;
        cout << "\nLastName    : " << Client.last_name;
        cout << "\nFull Name   : " << Client.get_full_name();
        cout << "\nEmail       : " << Client.email;
        cout << "\nPhone       : " << Client.phone;
        cout << "\nAcc. Number : " << Client.get_account_number();
        cout << "\nPassword    : " << Client.pincode;
        cout << "\nBalance     : " << Client.account_balance;
        cout << "\n___________________\n";

    }
    static string _ReadAccountNumber()
    {
        string AccountNumber = "";
        cout << "\nPlease enter AccountNumber? ";
        cin >> AccountNumber;
        return AccountNumber;
    }

public:

    static void ShowDepositScreen()
    {
        _DrawScreenHeader("\t   Deposit Screen");

        string AccountNumber = _ReadAccountNumber();


        while (!cls_bank_client::is_client_exist(AccountNumber))
        {
            cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
            AccountNumber = _ReadAccountNumber();
        }

        cls_bank_client Client1 = cls_bank_client::find(AccountNumber);
        _PrintClient(Client1);

        double Amount = 0;
        cout << "\nPlease enter deposit amount? ";
        Amount = clsInputValidate::ReadDblNumber();

        cout << "\nAre you sure you want to perform this transaction? ";
        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'Y' || Answer == 'y')
        {
            Client1.Deposit(Amount);
            cout << "\nAmount Deposited Successfully.\n";
            cout << "\nNew Balance Is: " << Client1.account_balance;

        }
        else
        {
            cout << "\nOperation was cancelled.\n";
        }

    }

};

