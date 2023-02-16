#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include "clsString.h"
#include "cls_person.h"

using namespace std;

class cls_bank_client :
    public cls_person
{
private:

    enum en_mode { empty_mode = 0, update_mode = 1, add_new_mode = 2 };

    en_mode _mode;
    string  _account_number;
    string  _pincode;
    float   _account_balance;
    bool    _Marked_for_delete = false;

    static cls_bank_client _convert_line_to_client_object(string line, string seprator = "#//#")
    {
        vector<string> v_client_data;
        v_client_data = clsString::Split(line, seprator);
        return cls_bank_client(en_mode::update_mode, v_client_data[0], v_client_data[1],
            v_client_data[2], v_client_data[3], v_client_data[4], v_client_data[5], 
            stod(v_client_data[6]));
    }
    static cls_bank_client _get_empty_client_object()
    {
        return cls_bank_client(en_mode::empty_mode, "", "", "", "", "", "", 0);
    }
    struct stTrnsferLogRecord;

    static stTrnsferLogRecord _ConvertTransferLogLineToRecord(string Line, string Seperator = "#//#")
    {
        stTrnsferLogRecord TrnsferLogRecord;

        vector <string> vTrnsferLogRecordLine = clsString::Split(Line, Seperator);
        TrnsferLogRecord.DateTime = vTrnsferLogRecordLine[0];
        TrnsferLogRecord.SourceAccountNumber = vTrnsferLogRecordLine[1];
        TrnsferLogRecord.DestinationAccountNumber = vTrnsferLogRecordLine[2];
        TrnsferLogRecord.Amount = stod(vTrnsferLogRecordLine[3]);
        TrnsferLogRecord.srcBalanceAfter = stod(vTrnsferLogRecordLine[4]);
        TrnsferLogRecord.destBalanceAfter = stod(vTrnsferLogRecordLine[5]);
        TrnsferLogRecord.UserName = vTrnsferLogRecordLine[6];

        return TrnsferLogRecord;

    }
    string _PrepareTransferLogRecord(float Amount, cls_bank_client DestinationClient,
        string UserName, string Seperator = "#//#")
    {
        string TransferLogRecord = "";
        TransferLogRecord += clsDate::GetSystemDateTimeString() + Seperator;
        TransferLogRecord += get_account_number() + Seperator;
        TransferLogRecord += DestinationClient.get_account_number() + Seperator;
        TransferLogRecord += to_string(Amount) + Seperator;
        TransferLogRecord += to_string(account_balance) + Seperator;
        TransferLogRecord += to_string(DestinationClient.account_balance) + Seperator;
        TransferLogRecord += UserName;
        return TransferLogRecord;
    }
    void _RegisterTransferLog(float Amount, cls_bank_client DestinationClient, string UserName)
    {

        string stDataLine = _PrepareTransferLogRecord(Amount, DestinationClient, UserName);

        fstream MyFile;
        MyFile.open("TransferLog.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }

    }
    static string _conver_client_object_to_line(cls_bank_client Client, string Seperator = "#//#")
    {
        string stClientRecord = "";
        stClientRecord += Client.first_name + Seperator;
        stClientRecord += Client.last_name + Seperator;
        stClientRecord += Client.email + Seperator;
        stClientRecord += Client.phone+ Seperator;
        stClientRecord += Client.get_account_number() + Seperator;
        stClientRecord += Client.pincode + Seperator;
        stClientRecord += to_string(Client.account_balance);

        return stClientRecord;
    }
    static vector <cls_bank_client> _load_clients_data_from_file()
    {
        vector<cls_bank_client> v_clients;
        fstream my_file;
        my_file.open("Clients.txt", ios::in);
        if (my_file.is_open())
        {
            string line;
            while (getline(my_file, line))
            {
                cls_bank_client client = _convert_line_to_client_object(line);
                v_clients.push_back(client);
            }
            my_file.close();
        }
        return v_clients;
    }

    static void _save_cleints_data_to_file(vector<cls_bank_client> _v_clients)
    {
        fstream my_file;
        string data_line;

        my_file.open("Clients.txt", ios::out);
        if (my_file.is_open())
        {
            for (cls_bank_client c : _v_clients)
            { 
                if (c._Marked_for_delete == false)
                {
                    //we only write records that are not marked for delete. 
                    data_line = _conver_client_object_to_line(c);
                    my_file << data_line << endl;
                }
            }
            my_file.close();
        }
    }
    void _update()
    {
        vector<cls_bank_client> _v_clients;
        _v_clients = _load_clients_data_from_file();

        for (cls_bank_client &c : _v_clients)
        {
            if (c.get_account_number() == get_account_number())
            {
                c = *this;
                break;
            }
        }
        _save_cleints_data_to_file(_v_clients);
    }

    void _add_new()
    {
        _add_data_line_to_file(_conver_client_object_to_line(*this));
    }
    void _add_data_line_to_file(string data_line)
    {
        fstream my_file;
        my_file.open("Clients.txt", ios::out | ios::app);
        if (my_file.is_open())
        {
            my_file << data_line << endl;
            my_file.close();
        }
    }

public:
    struct stTrnsferLogRecord
    {
        string DateTime;
        string SourceAccountNumber;
        string DestinationAccountNumber;
        float Amount;
        float srcBalanceAfter;
        float destBalanceAfter;
        string UserName;

    };

    cls_bank_client(en_mode mode, string first_name, string last_name, string email, string phone,
        string account_number, string pincode, float account_balance)
        : cls_person(first_name, last_name, email, phone)
    {
        _mode = mode;
        _account_number = account_number;
        _pincode = pincode;
        _account_balance = account_balance;
    }

    string get_account_number()
    {
        return _account_number;
    }

    bool is_empty()
    {
        return (_mode == en_mode::empty_mode);
    }

    void set_pincode(string pincode)
    {
        _pincode = pincode;
    }
    string get_pincode()
    {
        return _pincode;
    }
    __declspec(property(get = get_pincode, put = set_pincode))string pincode;

    void set_account_balance(float account_balance)
    {
        _account_balance = account_balance;
    }
    float get_account_balance()
    {
        return _account_balance;
    }
    __declspec(property(get = get_account_balance, put = set_account_balance))float account_balance;

    /*void print()
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << first_name;
        cout << "\nLastName    : " << last_name;
        cout << "\nFull Name   : " << get_full_name();
        cout << "\nEmail       : " << email;
        cout << "\nPhone       : " << phone;
        cout << "\nAcc. Number : " << _account_number;
        cout << "\nPassword    : " << _pincode;
        cout << "\nBalance     : " << _account_balance;
        cout << "\n___________________\n";

    }*/

    static cls_bank_client find(string account_number)
    {
        fstream my_file;
        my_file.open("Clients.txt", ios::in); //read mode
        if (my_file.is_open())
        {
            string line;
            while (getline(my_file, line))
            {
                cls_bank_client client = _convert_line_to_client_object(line);
                if (client.get_account_number() == account_number)
                {
                    my_file.close();
                    return client;
                }
            }
            my_file.close();
        }
        return _get_empty_client_object();
    }
    static cls_bank_client find(string account_number, string pincode)
    {
        fstream my_file;
        my_file.open("Clients.txt", ios::in); //read mode
        if (my_file.is_open())
        {
            string line;
            while (getline(my_file, line))
            {
                cls_bank_client client = _convert_line_to_client_object(line);
                if (client.get_account_number() == account_number && client.pincode == pincode)
                {
                    my_file.close();
                    return client;
                }
            }
            my_file.close();
        }
        return _get_empty_client_object();
    }

    enum en_save_results
    {
        sv_faild_empty_object = 0, 
        sv_succeeded = 1,
        sv_faild_account_number_exists = 2
    };
    en_save_results save()
    {
        switch (_mode)
        {
        case en_mode::empty_mode:
        {
            if (is_empty())
            {
                return en_save_results::sv_faild_empty_object;
            }
        }
        case en_mode::update_mode:
        {
            _update();
            return en_save_results::sv_succeeded;
            break;
        }
        case en_mode::add_new_mode:
        {
            //This will add new record to file or database
            if (cls_bank_client::is_client_exist(_account_number))
            {
                return en_save_results::sv_faild_account_number_exists;
            }
            else
            {
                _add_new();
                //We need to set the mode to update after add new
                _mode = en_mode::update_mode;
                return en_save_results::sv_succeeded;
            }
            break;
        }
        }
    }

    static bool is_client_exist(string account_number)
    {
        cls_bank_client client = cls_bank_client::find(account_number);
        return (!client.is_empty());
    }
    bool delet()
    {
        vector <cls_bank_client> _v_clients;
        _v_clients = _load_clients_data_from_file();
        for (cls_bank_client &c : _v_clients)
        {
            if (c.get_account_number() == _account_number)
            {
                c._Marked_for_delete = true;
                break;
            }
        }
        _save_cleints_data_to_file(_v_clients);

        *this = _get_empty_client_object();

        return true;
    }
    static cls_bank_client get_add_new_client_object(string account_number)
    {
        return cls_bank_client(en_mode::add_new_mode, "", "", "", "", account_number, "", 0);
    }

    static vector <cls_bank_client> get_clients_list()
    {
        return _load_clients_data_from_file(); 
    }
    static double get_total_balances()
    {
        vector <cls_bank_client> vClients = cls_bank_client::get_clients_list();

        double TotalBalances = 0;

        for (cls_bank_client Client : vClients)
        {

            TotalBalances += Client.account_balance;
        }

        return TotalBalances;

    }

    void Deposit(double Amount)
    {
        _account_balance += Amount;
        save();
    }
    bool Withdraw(double Amount)
    {
        if (Amount > _account_balance)
        {
            return false;
        }
        else
        {
            _account_balance -= Amount;
            save();
        }
    }

    static double GetTotalBalances()
    {
        vector <cls_bank_client> vClients = cls_bank_client::get_clients_list();

        double TotalBalances = 0;

        for (cls_bank_client Client : vClients)
        {

            TotalBalances += Client.account_balance;
        }

        return TotalBalances;
    }
    
    bool Transfer(float Amount, cls_bank_client& DestinationClient, string UserName)
    {
        if (Amount > account_balance)
        {
            return false;
        }

        Withdraw(Amount);
        DestinationClient.Deposit(Amount);
        _RegisterTransferLog(Amount, DestinationClient, UserName);
        return true;
    }
    static  vector <stTrnsferLogRecord> GetTransfersLogList()
    {
        vector <stTrnsferLogRecord> vTransferLogRecord;

        fstream MyFile;
        MyFile.open("TransferLog.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {

            string Line;

            stTrnsferLogRecord TransferRecord;

            while (getline(MyFile, Line))
            {

                TransferRecord = _ConvertTransferLogLineToRecord(Line);

                vTransferLogRecord.push_back(TransferRecord);

            }

            MyFile.close();

        }

        return vTransferLogRecord;

    }

};

