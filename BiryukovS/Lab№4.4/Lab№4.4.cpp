#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
using std::cout;
using std::cin;
using std::string;

long long int number() {
	long long int x;
	while (!(cin >> x)) {
		cout << "ERROR: enter the number: ";
		cin.clear();
		cin.ignore(10000, '\n');
	}
	return x;
}

void menu() {
	cout << '\n' << "1 - to change SNP\n" << "2 - to change the phone\n" << "3 - to change the birthday\n" << '\n';
}

string birth() {
	cout << "Enter the birthday in the format \"00.00.0000\": ";
	string day = "00";
	string month = "00";
	string year = "0000";
	while (true) {
		cout << "Enter the day: ";
		cin >> day;
		cout << '\n';
		if (day.size() >= 1 && day.size() <= 2) {
			if (((day[0] >= '0' && day[0] <= '2') && (day[1] >= '0' && day[1] <= '9' && day != "00")) || (day == "30") || (day == "31")) {
				break;
			}
			else {
			cout << "ERROR: incorrect day of birthday. Try again: ";
			}
		}
		else {
			cout << "ERROR: incorrect day of birthday. Try again: ";
		}
	}
	while (true) {
		cout << "Enter the month: ";
		cin >> month;
		cout << '\n';
		if (month.size() >= 1 && month.size() <= 2) {
			if (month[0] == '0') {
				if (month[1] >= '0' && month[1] <= '9' && month != "00") {
					break;
				}
				else {
					cout << "ERROR: incorrect month of birthday. Try again: ";
				}
			}
			else if (month[0] == '1') {
				if (month[1] >= '0' && month[1] <= '2' && month != "00") {
					break;
				}
				else {
					cout << "ERROR: incorrect month of birthday. Try again: ";
				}
			}
		}
		else {
			cout << "ERROR: incorrect month of birthday. Try again: ";
		}
	}
	while (true) {
		cout << "Enter the year: ";
		cin >> year;
		cout << '\n';
		bool check = true;
		if (year.size() >= 1 && year.size() <= 4 && year != "0000") {
			for (int i = 0; i < year.size(); ++i) {
				if (year[i] < '0' || year[i] > '9') {
					check = false;
				}
			}
			if (check == true) {
				break;
			}
			else {
				cout << "ERROR: incorrect year of birthday. Try again: ";
			}
		}
		else {
			cout << "ERROR: incorrect year of birthday. Try again: ";
		}
	}
	string birthday = day + "." + month + "." + year;
	return birthday;
}

class Contact {
private:
	string surname;
	string name;
	string patr;
	long long int phone;
	string birthday;
	bool favourite;
public:
	Contact() : phone(80000000000), favourite(false), birthday("00.00.0000") {}
	Contact(string surname_, string name_, string patr_, long long int phone_, string birthday_, bool favourite_) :
		surname(surname_), name(name_), patr(patr_), phone(phone_), birthday(birthday_), favourite(favourite_) {
	}
	bool operator<(const Contact& other) const { // для функции std::sort()
		if (surname != other.surname) {
			return surname < other.surname;
		}
		if (name != other.name) {
			return name < other.name;
		}
		return patr < other.patr;
	}
	string getsur() {
		return surname;
	}
	string getname() {
		return name;
	}
	string getpatr() {
		return patr;
	}
	long long int getphone() {
		return phone;
	}
	bool getfav() {
		return favourite;
	}
	void change() {
		cout << "what do you want to change?\n";
		int choice = 0;
		while (true) {
			menu();
			choice = number();
			if (choice < 1 || choice > 3) {
				cout << "ERROR: incorrect number. Try again: ";
			}
			else {
				switch (choice) {
				case 1:
					cout << "Enter new surname, name and patronymic: ";
					cin >> surname >> name >> patr;
					break;
				case 2:
					cout << "Enter new phone number: ";
					phone = number();
					break;
				case 3:
					birthday = birth();
					break;
				}
				return;
			}
		}
	}
	void setfavour() {
		favourite = true;
	}
	void delfavour() {
		favourite = false;
	}
	friend std::ostream& operator<<(std::ostream& ios, const Contact& c) {
		ios << "Surname: " << c.surname << '\n'
			<< "Name: " << c.name << '\n'
			<< "Patronymic: " << c.patr << '\n'
			<< "Phone number: " << c.phone << '\n'
			<< "Birthday: " << c.birthday << '\n'
			<< "Favourite: ";
		if (c.favourite == true) {
			ios << "yes" << '\n';
		}
		else {
			ios << "no" << '\n';
		}
		return ios;
	}
	friend std::istream& operator>>(std::istream& ios, Contact& c) {
		ios >> c.surname >> c.name >> c.patr >> c.phone >> c.birthday;
		string a;
		ios >> a;
		if (a == "yes") {
			c.favourite = true;
		}
		else {
			c.favourite = false;
		}
		return ios;
	}
};

Contact nullcontact() {
	Contact A("Ivanov", "Ivan", "Ivanovich", 80000000000, "00.00.0000", false);
	return A;
}

class Book {
private:
	int size;
	Contact* contacts;
	
public:
	Book() : size(0), contacts(nullptr) {}
	Book(int size_) : size(size_), contacts(new Contact[size_]) {}
	~Book() {
		delete[] contacts;
	}
	Book& operator=(const Book& other){
		if (this == &other) {
			return *this;
		}
		Contact* newc = new Contact[other.size];
		for (int i = 0; i < other.size; ++i) {
			newc[i] = other.contacts[i];
		}
		delete[] contacts;
		contacts = newc;
		size = other.size;
		return *this;
	}
	void sortcon() {
		std::sort(contacts, contacts + size);
	}
	Book(const Book& other) {
		size = other.size;
		contacts = new Contact[size];
		for (int i = 0; i < size; ++i) {
			contacts[i] = other.contacts[i];
		}
	}
	Contact create() { // не стал предалагать пользователю добавить контакт в избранное при создании, обычно это отдельный функционал, как и здесь
		string s;
		string n;
		string p;
		long long int ph;
		string b;
		cout << "Enter the surname, name and patronymic: ";
		cin >> s >> n >> p;
		cout << "Enter the phone number: ";
		ph = number();
		b = birth();
		Contact newc(s, n, p, ph, b, false);
		return newc;
	}

	void newcon() {
		++size;
		Contact* newc = new Contact[size];
		for (int i = 0; i < size - 1; ++i) {
			newc[i] = contacts[i];
		}
		newc[size - 1] = create();
		delete[] contacts;
		contacts = newc;
		sortcon();
	}
	void addcon(const Contact& c) {
		++size;
		Contact* newc = new Contact[size];
		for (int i = 0; i < size - 1; ++i) {
			newc[i] = contacts[i];
		}
		newc[size - 1] = c;
		delete[] contacts;
		contacts = newc;
	}
	Contact findsur(string sur, string nam, string patr) {
		for (int i = 0; i < size; ++i) {
			if (contacts[i].getsur() == sur) {
				if (contacts[i].getname() == nam) {
					if (contacts[i].getpatr() == patr) {
						cout << contacts[i];
						return contacts[i];
					}
				}
			}
		}
		cout << "Such contact has not been found\n";
		return nullcontact();
	}
	Contact findphone(long long int phone) {
		for (int i = 0; i < size; ++i) {
			if (contacts[i].getphone() == phone) {
				cout << contacts[i];
				return contacts[i];
			}
		}
		cout << "The contact with such phone number fas not been found\n";
		return nullcontact();
	}
	void changecon(long long int phone) {
		bool check = false;
		for (int i = 0; i < size; ++i) {
			if (contacts[i].getphone() == phone) {
				contacts[i].change();
				check = true;
			}
		}
		if (check == false) {
			cout << "Such number has not been found\n";
		}
	}
	void changecon(string surname, string name, string patr) {
		bool check = false;
		for (int i = 0; i < size; ++i) {
			if (contacts[i].getsur() == surname && contacts[i].getname() == name && contacts[i].getpatr() == patr) {
				contacts[i].change();
				check = true;
			}
		}
		if (check == false) {
			cout << "Such contact has not been found\n";
		}
		sortcon();
	}
	int numbercon() {
		return size;
	}
	void setfav(long long int phone) {
		bool check = false;
		for (int i = 0; i < size; ++i) {
			if (contacts[i].getphone() == phone) {
				contacts[i].setfavour();
				check = true;
				break;
			}
		}
		if (check == false) {
			cout << "Such number has not been found\n";
		}
	}
	void setfav(string surname, string name, string patr) {
		bool check = false;
		for (int i = 0; i < size; ++i) {
			if (contacts[i].getsur() == surname && contacts[i].getname() == name && contacts[i].getpatr() == patr) {
				contacts[i].setfavour();
				check = true;
				break;
			}
		}
		if (check == false) {
			cout << "Such contact has not been found\n";
		}
	}
	void delfav(long long int phone) {
		bool check = false;
		for (int i = 0; i < size; ++i) {
			if (contacts[i].getphone() == phone) {
				contacts[i].delfavour();
				check = true;
				break;
			}
		}
		if (check == false) {
			cout << "Such number has not been found\n";
		}
	}
	void delfav(string surname, string name, string patr) {
		bool check = false;
		for (int i = 0; i < size; ++i) {
			if (contacts[i].getsur() == surname && contacts[i].getname() == name && contacts[i].getpatr() == patr) {
				contacts[i].delfavour();
				check = true;
				break;
			}
		}
		if (check == false) {
			cout << "Such contact has not been found\n";
		}
	}
	void charprint(char a) {
		bool check = false;
		for (int i = 0; i < size; ++i) {
			if (contacts[i].getsur()[0] == a) {
				cout << contacts[i];
				check = true;
			}
		}
		if (check == false) {
			cout << "Such Contacts has not been found\n";
		}
	}
	void printfavour() {
		bool check = false;
		for (int i = 0; i < size; ++i) {
			if (contacts[i].getfav() == true) {
				cout << contacts[i];
				check = true;
			}
		}
		if (check == false) {
			cout << "There are no favourite contacts\n";
		}
	}
	void delcontact(long long int phone) {
		int a = 0;
		for (int i = 0; i < size; ++i) {
			if (contacts[i].getphone() == phone) {
				a = i;
			}
		}
		--size;
		Contact* newc = new Contact[size];
		for (int i = 0; i < a; ++i) {
			newc[i] = contacts[i];
		}
		for (int i = a + 1; i < size; ++i) {
			newc[i - 1] = contacts[i];
		}
		delete[] contacts;
		contacts = newc;
		sortcon();
	}
	void writefile() {
		std::ofstream file("ContactBook.txt");
		if (!file) {
			cout << "ERROR: incorrect opening";
			return;
		}
		for (int i = 0; i < size; ++i) {
			file << contacts[i] << '\n';
		}
	}
	void readfile() {
		std::ifstream file("ContactBook.txt");
		if (!file) {
			cout << "ERROR: incorrect opening";
			return;
		}
		delete[] contacts;
		size = 0;
		contacts = nullptr;
		Contact c;
		while (file >> c) {
			addcon(c);
		}
		sortcon();
	}
	void print() {
		bool check = false;
		for (int i = 0; i < size; ++i) {
			cout << contacts[i];
			check = true;
		}
		if (check == false) {
			cout << "There are no contacts in the book\n";
		}
	}
};

int main() {
	Contact A ("Ivanov", "Ivan", "Ivanovich", 89576379587, "01.01.2000", false);
	Contact B ("Sidorov", "Nicolay", "Vladimirovich", 89987379587, "02.01.2002", true);
	Book book;
	book.addcon(A);
	book.addcon(B);
	book.newcon();
	Contact finds1 = book.findsur("Ivanov", "Ivan", "Ivanovich");
	Contact finds2 = book.findsur("Ivanov", "Ivan", "Sergeevich");
	Contact findph1 = book.findphone(89987379587);
	Contact findph2 = book.findphone(84484846657);
	book.changecon("Ivanov", "Ivan", "Ivanovich");
	book.setfav(89576379587);
	book.printfavour();
	book.delfav(89987379587);
	book.delcontact(89987379587);
	book.print();
	book.writefile();
}