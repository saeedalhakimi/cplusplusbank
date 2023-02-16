#pragma once
#include <iostream>
#include "clsScreen.h"
#include "cls_person.h"
#include "clsUser.h"
#include "clsInputValidate.h"

class clsFindUserScreen :protected clsScreen
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
        cout << "\nUserName    : " << User.UserName;
        cout << "\nPassword    : " << User.Password;
        cout << "\nPermissions : " << User.Permissions;
        cout << "\n___________________\n";

    }

public:

    static void ShowFindUserScreen()
    {

        _DrawScreenHeader("\t  Find User Screen");

        string UserName;
        cout << "\nPlease Enter UserName: ";
        UserName = clsInputValidate::ReadString();
        while (!clsUser::IsUserExist(UserName))
        {
            cout << "\nUser is not found, choose another one: ";
            UserName = clsInputValidate::ReadString();
        }

        clsUser User1 = clsUser::Find(UserName);

        if (!User1.IsEmpty())
        {
            cout << "\nUser Found :-)\n";
        }
        else
        {
            cout << "\nUser Was not Found :-(\n";
        }

        _PrintUser(User1);

    }

};

