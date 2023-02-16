#pragma once
#include <iostream>
#include "clsScreen.h"
#include "cls_bank_client.h"
#include <iomanip>

class clsClientListScreen :
    protected clsScreen
{
private:
    static void PrintClientRecordLine(cls_bank_client Client)
    {

        cout << setw(8) << left << "" << "| " << setw(15) << left << Client.get_account_number();
        cout << "| " << setw(20) << left << Client.get_full_name();
        cout << "| " << setw(12) << left << Client.phone;
        cout << "| " << setw(20) << left << Client.email;
        cout << "| " << setw(10) << left << Client.pincode;
        cout << "| " << setw(12) << left << Client.account_balance;

    }
public:
    static void ShowClientsList()
    {

        if (!CheckAccessRights(clsUser::enPermissions::pListClients))
        {
            return;// this will exit the function and it will not continue
        }

        vector <cls_bank_client> vClients = cls_bank_client::get_clients_list();
        string Title = "\t  Client List Screen";
        string SubTitle = "\t    (" + to_string(vClients.size()) + ") Client(s).";

        _DrawScreenHeader(Title, SubTitle);


        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(15) << "Accout Number";
        cout << "| " << left << setw(20) << "Client Name";
        cout << "| " << left << setw(12) << "Phone";
        cout << "| " << left << setw(20) << "Email";
        cout << "| " << left << setw(10) << "Pin Code";
        cout << "| " << left << setw(12) << "Balance";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vClients.size() == 0)
            cout << "\t\t\t\tNo Clients Available In the System!";
        else

            for (cls_bank_client Client : vClients)
            {

                PrintClientRecordLine(Client);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

    }

};

