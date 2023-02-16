#pragma once
#include <iostream>
#include <string>

using namespace std;

class cls_person
{
private:

	string _first_name;
	string _last_name;
	string _email;
	string _phone;

public:

	cls_person(string first_name, string last_name, string email, string phone)
	{
		_first_name = first_name;
		_last_name = last_name;
		_email = email;
		_phone = phone;
	}

	void set_first_name(string first_name)
	{
		_first_name = first_name;
	}
	string get_first_name()
	{
		return _first_name;
	}
	__declspec(property(get = get_first_name, put = set_first_name)) string first_name;

	void set_last_name(string last_name)
	{
		_last_name = last_name;
	}
	string get_last_name()
	{
		return _last_name;
	}
	__declspec(property(get = get_last_name, put = set_last_name)) string last_name;

	string get_full_name()
	{
		return _first_name + " " + _last_name;
	}

	void set_email(string email)
	{
		_email = email;
	}
	string get_email()
	{
		return _email;
	}
	__declspec(property(get = get_email, put = set_email)) string email;

	void set_phone(string phone)
	{
		_phone = phone;
	}
	string get_phone()
	{
		return _phone;
	}
	__declspec(property(get = get_phone, put = set_phone)) string phone;
	
	void print()
	{
		cout << "\nPerson Info";
		cout << "\____________________";
		cout << "\nFirst Name : " << first_name;
		cout << "\nLast  Name : " << last_name;
		cout << "\nEmail      : " << email;
		cout << "\nPhone      : " << phone;

	}
};

