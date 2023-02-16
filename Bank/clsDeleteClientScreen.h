#pragma once

#include <iostream>
#include "clsScreen.h"
#include "cls_person.h"
#include "cls_bank_client.h"
#include "clsInputValidate.h"

class clsDeleteClientScreen :
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

    static void ShowDeleteClientScreen()
    {
        if (!CheckAccessRights(clsUser::enPermissions::pDeleteClient))
        {
            return;// this will exit the function and it will not continue
        }
        _DrawScreenHeader("\tDelete Client Screen");

        string account_number = "";
        cout << "\nPlease Enter client Account Number: ";
        account_number = clsInputValidate::ReadString();
        while (!cls_bank_client::is_client_exist(account_number))
        {
            cout << "\nAccount number is not found, choose another one: ";
            account_number = clsInputValidate::ReadString();
        }
        cls_bank_client client1 = cls_bank_client::find(account_number);
        _PrintClient(client1);

        cout << "\nAre you sure you want to delete this client y/n? ";
        char answer = 'n';

        cin >> answer;
        if (answer == 'y' || answer == 'Y')
        {
            if (client1.delet())
            {
                cout << "\nClient Deleted Successfully :-)\n";

                _PrintClient(client1);
            }
            else
            {
                cout << "\nError Client Was not Deleted\n";
            }
        }
    }
};

