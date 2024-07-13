#pragma once
#ifndef HEADER_H_
#define HEADER_H_
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <windows.h>
using namespace std;

class User {
protected:
	string name;
	string cnic;
	char UserType;
	string username;
	string password;
public:
	//parameterised constructor
	User(string name = "eman", string cnic = "61101111111111", char UserType = 'a', string username = "eman1234", string password = "eFeef123@")
	{
		this->name = name;
		this->cnic = cnic;
		this->UserType = UserType;
		this->username = username;
		this->password = password;
	}
	//getters
	string getUsername()
	{
		return username;
	}
	string getpassword()
	{
		return password;
	}
	//displays values
	void show()
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		cout << "****************************";
		SetConsoleTextAttribute(hConsole, 6);
		cout << "USER ";
		SetConsoleTextAttribute(hConsole, 1);
		cout << "DETAILS";
		SetConsoleTextAttribute(hConsole, 15);
		cout << " ****************************\n\n\n";
		cout << "Name: " << name << endl;
		cout << "cnic : " << cnic << endl;
		cout << "User type: " << UserType << endl;
		cout << "User name: " << username;
		cout << "Password: " << password;
		cout << "****************************************** \n \n";
	}
	//use the retrieve object function here
	void GetUserDetails()			
	{
		string Username;
		cout << "Enter username: ";
		cin >> Username;
		char type;
		cout << "Enter Type of User (C/M/A): \n";
		cin >> type;

		if (type == 'C' || type == 'c')
		{
			User temp;
			ifstream myFile("Customer.bin", ios::binary);
			while (myFile.read((char*)&temp, sizeof(temp)))
			{
				if (temp.getUsername() == Username)
				{
					temp.show();
					myFile.close();
				}
			}
		}
		else if (type == 'M' || type == 'm')
		{
			User temp;
			ifstream myFile("Manager.bin", ios::binary);
			while (myFile.read((char*)&temp, sizeof(temp)))
			{
				if (temp.getUsername() == Username)
				{
					temp.show();
					myFile.close();
				}
			}
		}
		else if (type == 'A' || type == 'a')
		{
			User temp;
			ifstream myFile("Admin.bin", ios::binary);
			while (myFile.read((char*)&temp, sizeof(temp)))
			{
				if (temp.getUsername() == Username)
				{
					temp.show();
					myFile.close();
				}
			}
		}
		cout << "user shown " << endl << endl;
	}
	//login
	void login()
	{
		char type;
		string user, pass;
		cout << "Enter the type of user you want to login";
		cin >> type;
		cout << "Enter username: ";
		cin >> user;
		cout << "Enter password: ";
		cin >> pass;

		if (type == 'C' || type == 'c')
		{
			User temp;
			ifstream myFile("Customer.bin", ios::binary);
			while (myFile.read((char*)&temp, sizeof(temp)))
			{
				if (temp.getUsername() == user && temp.getpassword() == pass)
				{
					cout << " login successful" << endl;
					temp.show();
					myFile.close();
				}
			}
		}

		else if (type == 'M' || type == 'm')
		{
			User temp;

			ifstream myFile("Manager.bin", ios::binary);
			while (myFile.read((char*)&temp, sizeof(temp)))
			{
				if (temp.getUsername() == user && temp.getpassword() == pass)
				{
					cout << "login successful " << endl;
					temp.show();
					myFile.close();
				}
			}
		}

		else if (type == 'a' || type == 'A')
		{
			User temp;
			ifstream myFile("Admin.bin", ios::binary);
			while (myFile.read((char*)&temp, sizeof(temp)))
			{
				if (temp.getUsername() == user && temp.getpassword() == pass)
				{
					cout << "login successful " << endl;
					temp.show();
					myFile.close();
				}
			}
		}

		else cout << "Account not found, try again";
	}

	//register
	void RegisterAccount()
	{
		User obj;
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		cout << "****************************";
		SetConsoleTextAttribute(hConsole, 6);
		cout << "REGISTRATION ";
		SetConsoleTextAttribute(hConsole, 1);
		cout << "PORTAL";
		SetConsoleTextAttribute(hConsole, 15);
		cout << " ****************************\n\n\n";
		cout << "Register as: \n";
		cout << "C/c - Customer\n";
		cout << "M/m - Manager\n";
		cout << "A/a - Admin\n";
		cout << " ****************************\n\n";
		char type;
		cin >> type;

		cout << "************** Please enter your information ************** \n \n";
		cout << "Enter cnic: ";
		cin >> obj.cnic;
		cout << "Enter name: ";
		cin >> obj.name;
		obj.UserType = type;
		cout << "Enter username: ";
		cin >> obj.username;

		cout << "Enter password: ";
		cin >> obj.password;

		if (type == 'C'|| type == 'c')
		{
			ofstream myFile("Customer.bin", ios::binary | ios::app);
			myFile.write((char*)&obj, sizeof(obj));
			myFile.close();
		}

		else if (type == 'M' || type == 'm')
		{
			ofstream myFile("Manager.bin", ios::binary | ios::app);
			myFile.write((char*)&obj, sizeof(obj));
			myFile.close();
		}

		else if (type == 'a' || type == 'A')
		{
			ofstream myFile("Admin.bin", ios::binary | ios::app);
			myFile.write((char*)&obj, sizeof(obj));
			myFile.close();
		}
		else 
			cout << "invalid entry \n";
	}

	//deleting an Acount
	void DeleteAccount()
	{
		char type;
		string username;
		cout << "Enter username please:";
		cin >> username;

		cout << "Enter which type of account you want to delete (M/A/C): " << endl;
		cin >> type;

		cout << endl;

		if (type == 'c' || type == 'C')
		{
			User temp;
			fstream myFile("Patient.bin", ios::in | ios::out | ios::binary);
			ofstream myFile_temp("temp.bin", ios::app | ios::binary);           //new temp file for only writing, an empty file
			while (myFile.read((char*)&temp, sizeof(temp))) {                   //one object will keep coming from temp
				if (temp.getUsername() != username) {                       //condition will only write if the object is not equal to the required one
					myFile_temp.write((char*)&temp, sizeof(temp));              // prints all objects in file except the roll number one
				}
			}
			myFile.close();
			myFile_temp.close();
			remove("Customer.bin");           //deleted the file with filename
			rename("temp.bin", "Customer.bin");
		}

		else if (type == 'M' || type == 'm')
		{
			User temp;
			fstream myFile1("Manager.bin", ios::in | ios::out | ios::binary);
			ofstream myFile_temp1("temp.bin", ios::app | ios::binary);           //new temp file for only writing, an empty file
			while (myFile1.read((char*)&temp, sizeof(temp))) {                   //one object will keep coming from temp
				if (temp.getUsername() != username) {                       //condition will only write if the object is not equal to the required one
					myFile_temp1.write((char*)&temp, sizeof(temp));              // prints all objects in file except the roll number one
				}
			}
			myFile1.close();
			myFile_temp1.close();
			remove("Manager.bin");           //deleted the file with filename
			rename("temp.bin", "Manage.bin");
		}

		else if (type == 'a' || type == 'A')
		{
			User temp;
			fstream myFile2("Admin.bin", ios::in | ios::out | ios::binary);
			ofstream myFile_temp2("temp.bin", ios::app | ios::binary);           //new temp file for only writing, an empty file
			while (myFile2.read((char*)&temp, sizeof(temp))) {                   //one object will keep coming from temp
				if (temp.getUsername() != username) {                       //condition will only write if the object is not equal to the required one
					myFile_temp2.write((char*)&temp, sizeof(temp));              // prints all objects in file except the roll number one
				}
			}
			myFile2.close();
			myFile_temp2.close();
			remove("Admin.bin");           //deleted the file with filename
			rename("temp.bin", "Admin.bin");
		}
	}

	//updating or changing details
	void ChangeCredentials()
	{
		char type;
		string username;
		cout << "Enter username: ";
		cin >> username;

		cout << "Enter your type of account: ";
		cin >> type;

		if (type == 'c' || type == 'C')
		{
			string u, p;
			User temp;
			fstream myFile("Customer.bin", ios::in | ios::out | ios::binary);

			while (myFile.read((char*)&temp, sizeof(temp)))
			{
				if (temp.getUsername() == username)
				{

					cout << "Enter new username: ";
					cin >> u;

					cout << "Enter new password: ";
					cin >> p;
					//strcpy(temp.getUsername(), username.c_str());

					temp.getUsername() = u;
					temp.getpassword() = p;

					std::streamoff current = myFile.tellg();                           //tells where the pointer is at currently, it will be after all the objects at the end
					int oneblock = sizeof(temp);            //tells the size of one temp object
					myFile.seekg(current - oneblock);          //seekg is used to move the pointer forward or backwards
					myFile.write((char*)&temp, sizeof(temp));           //write the entire temp object in place of the pointer location
					myFile.close();
					cout << "Updated: \n";
				}
			}
		}

		else if (type == 'm' || type == 'M')
		{
			string u, p;
			User temp;
			fstream myFile("Manager.bin", ios::in | ios::out | ios::binary);
			while (myFile.read((char*)&temp, sizeof(temp)))
			{
				if (temp.getUsername() == username)
				{

					cout << "Enter new username: ";
					cin >> u;

					cout << "Enter new password: ";
					cin >> p;
					//strcpy(temp.getUsername(), username.c_str());

					temp.getUsername() = u;
					temp.getpassword() = p;

					std::streamoff current = myFile.tellg();                           //tells where the pointer is at currently, it will be after all the objects at the end
					int oneblock = sizeof(temp);            //tells the size of one temp object
					myFile.seekg(current - oneblock);          //seekg is used to move the pointer forward or backwards
					myFile.write((char*)&temp, sizeof(temp));           //write the entire temp object in place of the pointer location
					myFile.close();
					cout << "Updated: \n";
				}
			}
		}

		else if (type == 'a' || type == 'A')
		{
			string u, p;
			User temp;
			fstream myFile("Admin.bin", ios::in | ios::out | ios::binary);
			while (myFile.read((char*)&temp, sizeof(temp)))
			{
				if (temp.getUsername() == username)
				{
					cout << "Enter new username: ";
					cin >> u;

					cout << "Enter new password: ";
					cin >> p;
					//strcpy(temp.getUsername(), username.c_str());

					temp.getUsername() = u;
					temp.getpassword() = p;

					std::streamoff current = myFile.tellg();                           //tells where the pointer is at currently, it will be after all the objects at the end
					int oneblock = sizeof(temp);            //tells the size of one temp object
					myFile.seekg(current - oneblock);          //seekg is used to move the pointer forward or backwards
					myFile.write((char*)&temp, sizeof(temp));           //write the entire temp object in place of the pointer location
					myFile.close();
					cout << "Updated: \n";
				}
			}
			myFile.close();
		}
	}
};

class Manager : public User {
protected:
	string location;
public:
	//opens file to see Managers
	void viewManagerslist()
	{
		Manager temp;
		ifstream myFile("Manager.bin", ios::binary);
		while (myFile.read((char*)&temp, sizeof(temp))) {
			temp.show();
		}
		myFile.close();
	}
	//getters
	string getLocation()
	{
		return location;
	}
	string getcnic()
	{
		return cnic;
	}
	//register
	void registerManager()
	{
		Manager man;
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		cout << "****************************";
		SetConsoleTextAttribute(hConsole, 6);
		cout << "Manager Regis ";
		SetConsoleTextAttribute(hConsole, 1);
		cout << "tration Portal";
		SetConsoleTextAttribute(hConsole, 15);
		cout << " ****************************\n\n\n";

		cout << "Enter the Following: ";
		cout << "enter name: ";
		cin >> man.name;
		cout << "cnic: ";
		cin >> man.cnic;
		cout << "username: ";
		cin >> man.username;
		cout << "password: ";
		cin >> man.password;
		cout << endl;
		ofstream myFile("Manager.bin", ios::binary | ios::app);
		myFile.write((char*)&man, sizeof(man));
		myFile.close();
	}
	//operator=
	void operator= (Manager& obj)
	{
		this->cnic = obj.cnic;
		this->location = obj.location;
		this->name = obj.name;
		this->password = obj.password;
		this->username = obj.username;
	}
};

class Customer : public User {
protected:
	long long int phone;
	char gender;
public:
	//parameterised constructor
	Customer(long int phonenum = 03141567423, char gender = 'M')
	{ 
		//this->name = name;
		//this->id = id;
		this->phone = phonenum;
		//this->address = address;
		this->gender = gender;
	}
	//getters
	long long int getPhoneNumber()
	{
		return phone;
	}
	char getgender()
	{
		return gender;
	}
	//displays customer details
	void show()
	{
		cout << "Name: " << name << endl;
		cout << "Gender: " << gender << endl;
		cout << "Username: " << username << endl;
		cout << "Password: " << password << endl;
	}
	//opens file and shows customer details
	void viewCustomer(string username)
	{
		Customer temp;
		ifstream myFile("Customer.bin", ios::binary);
		while (myFile.read((char*)&temp, sizeof(temp)))
		{
			if (temp.getUsername() == username)
			{
				temp.show();
				myFile.close();
			}
		}
	}
	//register
	void registerCustomer()
	{
		Customer obj;
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		cout << "****************************";
		SetConsoleTextAttribute(hConsole, 6);
		cout << "Customer Regis ";
		SetConsoleTextAttribute(hConsole, 1);
		cout << "tration Portal";
		SetConsoleTextAttribute(hConsole, 15);
		cout << " ****************************\n\n\n";
		cout << "Please enter your information: ";
		cout << "Enter name: ";
		cin >> obj.name;
		cout << "Enter username: ";
		cin >> obj.username;
		cout << "Enter password: ";
		cin >> obj.password;
		cout << "Enter phone number: ";
		cin >> obj.phone;
		cout << "Enter Gender: ";
		cin >> obj.gender;
		cout << "Enter cnic: ";
		cin >> obj.cnic;

		ofstream myFile("Customer.bin", ios::binary | ios::app);
		myFile.write((char*)&obj, sizeof(obj));
		myFile.close();
	}
	//operator=
	void operator = (Customer& obj)
	{
		this->gender = obj.gender;
		this->cnic = obj.cnic;
		this->name = obj.name;
		this->password = obj.password;
		this->phone = obj.phone;
		this->username = obj.username;
	}
};

class Feedback {
protected:
	char stars[10];
	string comment;
	string reply;
	int count;
public:
	//rate product
	void RateProduct()
	{
		cout << "Enter the number of stars you want to give: ";
		cin.get(stars, 10);
		cout << "Thankyou for your review \n";
		for (int i = 0; stars[i] != '\0'; i++)
		{
			count++;
		}
	}
	//comment on product
	void CommentProduct()
	{
		cout << "Enter any comment you want to add for doctor: ";
		cin >> comment;
		cout << "Thankyou for your comment";
	}
	//gives reply to feedback
	void GetReply()
	{
		if (count < 5)
		{
			cout << "Sorry for your bad experience and thank you for your feedback. We aim to improve!\n";
		}
		else if (count > 5)
		{
			cout << "Thankyou for the good rating, do visit us again!\n";
		}
	}
};

/*
class Product {
	string* food[20];
	string* hygeine;
	string* care;
public:
	void displayFood() {
		Product p;
		for (int i = 0; i < 20; i++)
		{
			cout << "Enter food: ";
			cin >> food[i];
		}
		ofstream myFile("ProductCatalog.bin", ios::binary | ios::app);
		myFile.write((char*)&p, sizeof(p));
		myFile.close();
	}
};*/

class FoodItem {
	int itemNumber;
	std::string foodItemName;
	int quantity;
	double totalPriceForFoodItem;
	int foodprice;
public:
	//default constructor
	FoodItem() {
		itemNumber = 0;
		foodItemName = "\0";
		quantity = 0;
		totalPriceForFoodItem = 0.0;
		foodprice = 2;
	}
	//parameterised constructor
	FoodItem(std::string foodName)
	{
		foodItemName = foodName;
	}
	FoodItem(int numberOfItems, std::string nameOfFood)
	{
		setFoodQuantity(numberOfItems);
		setFoodName(nameOfFood);
	}
	//getting food items
	double getFoodItemTotal()
	{
		totalPriceForFoodItem = getFoodQuantity() * foodprice;
		return totalPriceForFoodItem;
	}

	//getters and setters
	void setFoodName(std::string itemName)
	{
		foodItemName = itemName;
	}
	std::string getFoodName()
	{
		return foodItemName;
	}
	void setFoodQuantity(int numberOfFoodItem)
	{
		quantity = numberOfFoodItem;
	}
	int getFoodQuantity()
	{
		return FoodItem::quantity;
	}
};

class Shopping {
private:
	FoodItem foodName;
	double totalPrice;
public:
	//default
	Shopping() {
		totalPrice = 0;
	}
	Shopping(int numItems, std::string itemsName) :
		foodName(numItems, itemsName) {}
	bool cartEmpty = true;
	double thisTotal;
	string name;

	//adds product to cart
	void addToCart(FoodItem fItem) {
		cartEmpty = false;
		name = fItem.getFoodName();
		FoodItem item(name);
		thisTotal += item.getFoodItemTotal();
		int tempQTY = item.getFoodQuantity();
		tempQTY--;
	}

	//gets total
	double getTotal() {
		if (cartEmpty = true)
			thisTotal = 0;
		return thisTotal;
	}
	//empties cart
	double emptyShoppingCart() {
		cartEmpty = true;
		thisTotal = 0;
		return thisTotal;
	}
};

class Inventory {
	int foodCode;
	char foodName[15];
	int quantity;
	double price;
public:
	//default
	Inventory() {
		foodCode = 0;
		for(int i=0;i<15;i++)
			foodName[i] = '\0';
		quantity = 0;
		price = 0;
	}
	//parameterised
	Inventory(const string& foodName,int quantity, double price)
		: quantity(quantity), price(price)
	{
		setFoodName(foodName);
	}
	//getters and setters
	string getFoodName() const
	{
		return foodName;
	}
	void setFoodName(const string& foodNameString)
	{
		int length = foodNameString.size();
		length = (length < 15 ? length : 14);
		foodNameString.copy(foodName, length);
		foodName[length] = '\0';
	}
	int getQuantity() const
	{
		return quantity;
	}
	void setQuantity(int quantityValue)
	{
		quantity = quantityValue;
	}
	double getPrice() const
	{
		return price;
	}
	void setPrice(double priceValue)
	{
		price = priceValue;
	}
	void reduceQuantity(int quantity)
	{
		quantity -= quantity;
	}
};

class Admin : public User {
public:
	//allocates manager to a location
	void allocateManager() {
		Manager obj;
		string str;
		cout << " Enter where to place Manager (Isb/Lhr/Krh): ";
		cin >> str;
		obj.getLocation() = str;
		ifstream myFile("Manager.bin", ios::binary);
		while (myFile.read((char*)&obj, sizeof(obj))) {
			obj.show();
		}
		myFile.close();
	}
	//admin can view customer details
	void viewCustomer() {
		Customer temp;
		ifstream myFile("Customer.bin", ios::binary);
		while (myFile.read((char*)&temp, sizeof(temp))) {
			temp.show();
		}
		myFile.close();
	}
	//admin can view manager details
	void viewManager() {
		Manager temp;
		ifstream myFile("Manager.bin", ios::binary);
		while (myFile.read((char*)&temp, sizeof(temp))) {
			temp.show();
		}
		myFile.close();
	}
	//admin can view product catalog
	void viewProducts() {
		Inventory i1;
		cout << "product name: " << i1.getFoodName() << endl;
		cout << "product price: " << i1.getPrice() << endl;
		cout << "product quantity: " << i1.getQuantity() << endl;
		ofstream myFile("Inventory.bin", ios::binary | ios::app);
		myFile.write((char*)&i1, sizeof(i1));
		myFile.close();
	}
};

class Payment {
protected:
	int amount;
	string account;
	string password;
public:
	//getters
	int getAmount()
	{
		return amount;
	}
	string getaccount()
	{
		return account;
	}
	string getpass()
	{
		return password;
	}
	//making a bankk account 
	void makebankacc()
	{
		Payment temp;
		cout << "Enter the username: ";
		cin >> temp.account;
		cout << "Enter password: ";
		cin >> temp.password;

		ofstream myFile("Bank.bin", ios::binary | ios::app);
		myFile.write((char*)&temp, sizeof(temp));
		myFile.close();
	}
	//verifying the bank account
	void verifyaccount()
	{
		string acc, p;
		cout << "Enter your bank account : ";
		cin >> acc;
		cout << "Enter your password: ";
		cin >> p;
		Payment temp;
		ifstream myFile("Bank.bin", ios::binary);
		while (myFile.read((char*)&temp, sizeof(temp))) {
			if (temp.getaccount() == acc && temp.getpass() == p) {
				cout << "Account verification done" << endl;
				myFile.close();
			}
		}
	}
	//paying for a profuct
	void sendPayment()
	{
		string a, p;
		cout << "enter your bank account: ";
		cin >> a;
		cout << "Enter your password: ";
		cin >> p;

		Payment temp;
		fstream myFile("Bank.bin", ios::in | ios::out | ios::binary);
		while (myFile.read((char*)&temp, sizeof(temp))) {
			if (temp.getaccount() == a && temp.getpass() == p) {
				//strcpy_s(temp.getStudentName(), 100, studentName.c_str());
				temp.amount -= 1000;
				int current = myFile.tellg();                           //tells where the pointer is at currently, it will be after all the objects at the end
				int oneblock = sizeof(temp);            //tells the size of one temp object
				myFile.seekg(current - oneblock);          //seekg is used to move the pointer forward or backwards
				myFile.write((char*)&temp, sizeof(temp));           //write the entire temp object in place of the pointer location
				myFile.close();
			}
		}
	}
	
	void returnpayment()
	{
		string a, p;
		cout << "enter your bank account: ";
		cin >> a;
		cout << "Enter your password: ";
		cin >> p;

		Payment temp;
		fstream myFile("Bank.bin", ios::in | ios::out | ios::binary);
		while (myFile.read((char*)&temp, sizeof(temp))) {
			if (temp.getaccount() == a && temp.getpass() == p) {
				//strcpy_s(temp.getStudentName(), 100, studentName.c_str());
				temp.amount += 1000;
				int current = myFile.tellg();                           //tells where the pointer is at currently, it will be after all the objects at the end
				int oneblock = sizeof(temp);            //tells the size of one temp object
				myFile.seekg(current - oneblock);          //seekg is used to move the pointer forward or backwards
				myFile.write((char*)&temp, sizeof(temp));           //write the entire temp object in place of the pointer location
				myFile.close();
			}
		}
	}
	//displays account details
	void display()
	{
		cout << "Current balance: " << amount << endl;
		cout << "account name: " << account << endl;
	}
	//opens up file which should account detail
	void viewaccount()
	{
		string u;
		cout << "Enter your username";
		cin >> u;

		Payment temp;
		ifstream myFile("Bank.bin", ios::binary);
		while (myFile.read((char*)&temp, sizeof(temp))) {
			if (temp.getaccount() == u) {
				temp.amount = this->amount;
				temp.display();
				myFile.close();
			}
		}
	}

	void getPayment()
	{
		string a, p;
		cout << "enter your bank account: ";
		cin >> a;
		cout << "Enter your password: ";
		cin >> p;

		Payment temp;
		fstream myFile("Bank.bin", ios::in | ios::out | ios::binary);
		while (myFile.read((char*)&temp, sizeof(temp))) {
			if (temp.getaccount() == a && temp.getpass() == p) {
				//strcpy_s(temp.getStudentName(), 100, studentName.c_str());
				temp.amount -= 1000;
				int current = myFile.tellg();                           //tells where the pointer is at currently, it will be after all the objects at the end
				int oneblock = sizeof(temp);            //tells the size of one temp object
				myFile.seekg(current - oneblock);          //seekg is used to move the pointer forward or backwards
				myFile.write((char*)&temp, sizeof(temp));           //write the entire temp object in place of the pointer location
				myFile.close();
			}
		}
	}
};

class Menu {
	User u;
	Shopping S;
	Manager M;
	Customer C;
	Payment pay;
	Feedback f;
	Admin a;
public:
	bool programrun = true;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	//constructor
	Menu()
	{
		while (programrun = true)
		{
			int num;
			int t;

			cout << "*********************************";
			cout << " Welcome to ";
			SetConsoleTextAttribute(hConsole, 6);
			cout << "New Age ";
			SetConsoleTextAttribute(hConsole, 1);
			cout << "Grocery Store ";
			SetConsoleTextAttribute(hConsole, 15);
			cout << "********************************* \n\n\n";
			cout << "1 - Customer\n";
			cout << "2 - Manager \n";
			cout << "3 - Admin \n";

			cin >> t;
			string item;
			switch (t)
			{
				case 1:
					cout << "****************************";
					SetConsoleTextAttribute(hConsole, 6);
					cout << "CUSTOMER ";
					SetConsoleTextAttribute(hConsole, 1);
					cout << "PORTAL";
					SetConsoleTextAttribute(hConsole, 15);
					cout << "****************************\n\n";
					cout << "What would you like to do: " << endl;
					cout << "1. Register" << endl;
					cout << "2. Login" << endl;
					cout << "3. Online Shopping" << endl;
					cout << "4. Send Payment" << endl;
					cout << "5. Give Feedback" << endl;
					cin >> num;

					switch (num)
					{
						case 1:
							u.RegisterAccount();
							break;
						case 2:
							C.login();
							break;
						case 3:
							a.viewProducts();
							cout << "Enter Product to buy: ";
							cin >> item;
							S.addToCart(item);
							break;
						case 4:
							pay.sendPayment();
							break;
						case 5:;
							f.RateProduct();
							f.CommentProduct();
							f.GetReply();
							break;
					}
					break;

			case 2:
				cout << "****************************";
				SetConsoleTextAttribute(hConsole, 6);
				cout << "MANAGER ";
				SetConsoleTextAttribute(hConsole, 1);
				cout << "PORTAL";
				SetConsoleTextAttribute(hConsole, 15);
				cout << "****************************\n\n";

				cout << "1. Register" << endl;
				cout << "2. Login" << endl;
				cout << "3. Get User Details" << endl;
				cout << "4. Manage Inventory" << endl;

				cin >> num;

				switch (num)
				{
					case 1:
						M.registerManager();
						break;
					case 2:
						M.login();
						break;
					case 3:
						M.GetUserDetails();
						break;
					case 4:
						a.viewProducts();
						break;
				}
				break;

			case 3:
				cout << "****************************";
				SetConsoleTextAttribute(hConsole, 6);
				cout << "ADMIN ";
				SetConsoleTextAttribute(hConsole, 1);
				cout << "PORTAL";
				SetConsoleTextAttribute(hConsole, 15);
				cout << "****************************\n\n";

				cout << "What function would you like to perform" << endl;
				cout << "1. Login" << endl;
				cout << "2. Allocate Manager" << endl;
				cout << "3. Product Catalog" << endl;
				cout << "4. Checkout Simulation" << endl;
				cin >> num;

				switch (num)
				{
					case 1:
						u.login();
						break;
					case 2:
						a.allocateManager();
						break;
					case 3:
						a.viewProducts();
						break;
					case 4:
						cout << "Proceed to counter 2\n";
				}
				break;
			}

			int c = 0;
			cout << "Would you like to keep using the New Age Grocery Store" << endl;
			cout << "1 - No\n";
			cout << "2 - Yes\n";
			cin >> c;

			if (c != 2)
			{
				break;
				system("cls");		// command to clear screen
			}
			system("cls");		// command to clear screen
		}
	}
	//destructor
	~Menu()
	{
		cout << "Thank you, do visit again!" << endl;
	}
};

#endif // !HEADER_H_
