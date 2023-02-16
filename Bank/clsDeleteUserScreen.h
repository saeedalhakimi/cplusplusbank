#pragma once
#include <iostream>
#include "clsScreen.h"
#include "cls_person.h"
#include "clsUser.h"
#include "clsInputValidate.h"

class clsDeleteUserScreen :
    protected clsScreen
{
private:
    static void _PrintUser(clsUser User)
    {
        cout << "\nUser Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << User.first_name;
        cout << "\nLastName    : " << User.last_name;
        cout << "\nFull Name   : " << User.get_full_name();
        cout << "\nEmail       : " << User.email;
        cout << "\nPhone       : " << User.phone;
        cout << "\nUser Name   : " << User.UserName;
        cout << "\nPassword    : " << User.Password;
        cout << "\nPermissions : " << User.Permissions;
        cout << "\n___________________\n";

    }
public:
    static void ShowDeleteUserScreen()
    {

        _DrawScreenHeader("\tDelete User Screen");

        string UserName = "";

        cout << "\nPlease Enter UserName: ";
        UserName = clsInputValidate::ReadString();
        while (!clsUser::IsUserExist(UserName))
        {
            cout << "\nUser is not found, choose another one: ";
            UserName = clsInputValidate::ReadString();
        }

        clsUser User1 = clsUser::Find(UserName);
        _PrintUser(User1);

        cout << "\nAre you sure you want to delete this User y/n? ";

        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {

            if (User1.Delete())
            {
                cout << "\nUser Deleted Successfully :-)\n";
                _PrintUser(User1);
            }
            else
            {
                cout << "\nError User Was not Deleted\n";
            }
        }
    }
};

