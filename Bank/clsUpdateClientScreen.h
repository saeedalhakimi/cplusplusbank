#pragma once
#include <iostream>
#include "clsScreen.h"
#include "cls_person.h"
#include "cls_bank_client.h"
#include "clsInputValidate.h"


class clsUpdateClientScreen :
    protected clsScreen
{
private:

    static void _ReadClientInfo(cls_bank_client& Client)
    {
        cout << "\nEnter FirstName: ";
        Client.first_name = clsInputValidate::ReadString();

        cout << "\nEnter LastName: ";
        Client.last_name = clsInputValidate::ReadString();

        cout << "\nEnter Email: ";
        Client.email = clsInputValidate::ReadString();

        cout << "\nEnter Phone: ";
        Client.phone = clsInputValidate::ReadString();

        cout << "\nEnter PinCode: ";
        Client.pincode = clsInputValidate::ReadString();

        cout << "\nEnter Account Balance: ";
        Client.account_balance = clsInputValidate::ReadFloatNumber();
    }
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
    static void ShowUpdateClientScreen()
    {
       
        if (!CheckAccessRights(clsUser::enPermissions::pUpdateClients))
        {
            return;// this will exit the function and it will not continue
        }

        _DrawScreenHeader("\tUpdate Client Screen");

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

        cout << "\nAre you sure you want to update this client y/n? ";

        char Answer = 'n';
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            cout << "\n\nUpdate Client Info:";
            cout << "\n____________________\n";
            _ReadClientInfo(client1);

            cls_bank_client::en_save_results save_result;
            save_result = client1.save();

            switch (save_result)
            {
            case cls_bank_client::en_save_results::sv_succeeded:
            {
                cout << "\nAccount Updated Successfully :-)\n";
                _PrintClient(client1);
                break;
            }
            case cls_bank_client::en_save_results::sv_faild_empty_object:
            {
                cout << "\nError account was not saved because it's Empty";
                break;
            }
            }
        }
    }
};

