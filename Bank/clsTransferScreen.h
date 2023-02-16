#pragma once
#include <iostream>
#include "clsScreen.h"
#include "cls_person.h"
#include "cls_bank_client.h"
#include "clsInputValidate.h"
//#include"Global.h"

class clsTransferScreen :protected clsScreen
{

private:
    static void _PrintClient(cls_bank_client Client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________\n";
        cout << "\nFull Name   : " << Client.get_full_name();
        cout << "\nAcc. Number : " << Client.get_account_number();
        cout << "\nBalance     : " << Client.account_balance;
        cout << "\n___________________\n";

    }

    static string _ReadAccountNumber()
    {
        string AccountNumber;
        cout << "\nPlease Enter Account Number to Transfer From/To: ";
        AccountNumber = clsInputValidate::ReadString();
        while (!cls_bank_client::is_client_exist(AccountNumber))
        {
            cout << "\nAccount number is not found, choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }
        return AccountNumber;
    }

    static float ReadAmount(cls_bank_client SourceClient)
    {
        float Amount;

        cout << "\nEnter Transfer Amount? ";

        Amount = clsInputValidate::ReadFloatNumber();

        while (Amount > SourceClient.account_balance)
        {
            cout << "\nAmount Exceeds the available Balance, Enter another Amount ? ";
            Amount = clsInputValidate::ReadDblNumber();
        }
        return Amount;
    }

public:

    static void ShowTransferScreen()
    {

        _DrawScreenHeader("\tTransfer Screen");

        cls_bank_client SourceClient = cls_bank_client::find(_ReadAccountNumber());

        _PrintClient(SourceClient);

        cls_bank_client DestinationClient = cls_bank_client::find(_ReadAccountNumber());

        _PrintClient(DestinationClient);

        float Amount = ReadAmount(SourceClient);


        cout << "\nAre you sure you want to perform this operation? y/n? ";
        char Answer = 'n';
        cin >> Answer;
        if (Answer == 'Y' || Answer == 'y')
        {
            if (SourceClient.Transfer(Amount, DestinationClient, CurrentUser.UserName))
            {
                cout << "\nTransfer done successfully\n";
            }
            else
            {
                cout << "\nTransfer Faild \n";
            }
        }

        _PrintClient(SourceClient);
        _PrintClient(DestinationClient);


    }

};

