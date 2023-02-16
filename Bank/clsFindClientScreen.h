#pragma once
#include <iostream>
#include "clsScreen.h"
#include "cls_person.h"
#include "cls_bank_client.h"
#include "clsInputValidate.h"

class clsFindClientScreen :
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
public:
    static void ShowFindClientScreen()
    {
        if (!CheckAccessRights(clsUser::enPermissions::pFindClient))
        {
            return;// this will exit the function and it will not continue
        }
        _DrawScreenHeader("\tFind Client Screen");

        string AccountNumber;
        cout << "\nPlease Enter Account Number: ";
        AccountNumber = clsInputValidate::ReadString();
        while (!cls_bank_client::is_client_exist(AccountNumber))
        {
            cout << "\nAccount number is not found, choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        cls_bank_client Client1 = cls_bank_client::find(AccountNumber);
        if (!Client1.is_empty())
        {
            cout << "\nClient Found :-)\n";
        }
        else
        {
            cout << "\nClient Was not Found :-(\n";
        }

        _PrintClient(Client1);
    }
};

