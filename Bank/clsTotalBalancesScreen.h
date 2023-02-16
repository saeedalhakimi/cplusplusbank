#pragma once
#include <iostream>
#include "clsScreen.h"
#include "cls_bank_client.h"
#include <iomanip>
#include "clsUtil.h"

class clsTotalBalancesScreen :
    protected clsScreen
{
private:
    static void PrintClientRecordBalanceLine(cls_bank_client Client)
    {
        cout << setw(25) << left << "" << "| " << setw(15) << left << Client.get_account_number();
        cout << "| " << setw(40) << left << Client.get_full_name();
        cout << "| " << setw(12) << left << Client.account_balance;
    }
public:

    static void ShowTotalBalances()
    {

        vector <cls_bank_client> vClients = cls_bank_client::get_clients_list();

        string Title = "\t  Balances List Screen";
        string SubTitle = "\t    (" + to_string(vClients.size()) + ") Client(s).";

        _DrawScreenHeader(Title, SubTitle);

        cout << setw(25) << left << "" << "\n\t\t_______________________________________________________";
        cout << "__________________________\n" << endl;

        cout << setw(25) << left << "" << "| " << left << setw(15) << "Accout Number";
        cout << "| " << left << setw(40) << "Client Name";
        cout << "| " << left << setw(12) << "Balance";
        cout << setw(25) << left << "" << "\t\t_______________________________________________________";
        cout << "__________________________\n" << endl;

        double TotalBalances = cls_bank_client::GetTotalBalances();

        if (vClients.size() == 0)
            cout << "\t\t\t\tNo Clients Available In the System!";
        else

            for (cls_bank_client Client : vClients)
            {
                PrintClientRecordBalanceLine(Client);
                cout << endl;
            }

        cout << setw(25) << left << "" << "\n\t\t_______________________________________________________";
        cout << "__________________________\n" << endl;

        cout << setw(8) << left << "" << "\t\t\t\t\t\t\t     Total Balances = " << TotalBalances << endl;
        cout << setw(8) << left << "" << "\t\t\t\t  ( " << clsUtil::NumberToText(TotalBalances) << ")";
    }
};

