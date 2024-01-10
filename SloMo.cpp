// SloMo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>

class Contact {
public:
    Contact(const std::string& name, const std::string& homePhone, const std::string& workPhone,
        const std::string& mobilePhone, const std::string& additionalInfo)
        : name(new std::string(name)), homePhone(homePhone), workPhone(workPhone),
        mobilePhone(mobilePhone), additionalInfo(additionalInfo) {}

    Contact() : Contact("", "", "", "", "") {}

    ~Contact() {
        delete name;
    }

    void displayInfo() const {
        std::cout << "�I�: " << *name << std::endl;
        std::cout << "������i� �������: " << homePhone << std::endl;
        std::cout << "������� �������: " << workPhone << std::endl;
        std::cout << "���i����� �������: " << mobilePhone << std::endl;
        std::cout << "��������� i���������: " << additionalInfo << std::endl;
    }

    std::string getName() const {
        return *name;
    }

    void saveToFile(std::ofstream& outFile) const {
        outFile << *name << " " << homePhone << " " << workPhone << " "
            << mobilePhone << " " << additionalInfo << std::endl;
    }

private:
    std::string* name;
    std::string homePhone;
    std::string workPhone;
    std::string mobilePhone;
    std::string additionalInfo;
};

class PhoneBook {
public:
    void addContact(const Contact& contact) {
        if (size < capacity) {
            contacts[size++] = contact;
        }
        else {
            std::cout << "��������� ����� ���������. ��������� ������ ������ ��������." << std::endl;
        }
    }

    void removeContact(const std::string& name) {
        for (int i = 0; i < size; i++) {
            if (contacts[i].getName() == name) {
                contacts[i] = contacts[size - 1];
                size--;
                std::cout << "������� ���i��� ���������." << std::endl;
                return;
            }
        }

        std::cout << "������� � �I� " << name << " �� ���������." << std::endl;
    }

    void searchContact(const std::string& name) const {
        for (int i = 0; i < size; i++) {
            if (contacts[i].getName() == name) {
                contacts[i].displayInfo();
                return;
            }
        }

        std::cout << "������� � �I� " << name << " �� ���������." << std::endl;
    }

    void displayAllContacts() const {
        for (int i = 0; i < size; i++) {
            contacts[i].displayInfo();
            std::cout << "------------------------" << std::endl;
        }
    }

    void saveToFile(const std::string& filename) const {
        std::ofstream outFile(filename);

        if (outFile.is_open()) {
            for (int i = 0; i < size; i++) {
                contacts[i].saveToFile(outFile);
            }

            std::cout << "��������� ����� ���i��� ��������� � ���� " << filename << std::endl;
        }
        else {
            std::cout << "������� �i������� ����� ��� ������." << std::endl;
        }
    }

    void loadFromFile(const std::string& filename) {
        std::ifstream inFile(filename);

        if (inFile.is_open()) {
            size = 0;

            std::string name, homePhone, workPhone, mobilePhone, additionalInfo;
            while (inFile >> name >> homePhone >> workPhone >> mobilePhone >> additionalInfo) {
                Contact contact(name, homePhone, workPhone, mobilePhone, additionalInfo);
                contacts[size++] = contact;
            }

            std::cout << "��������� ����� ���i��� ����������� � ����� " << filename << std::endl;
        }
        else {
            std::cerr << "������� �i������� ����� ��� �������." << std::endl;
        }
    }

private:
    static const int capacity = 100;
    Contact contacts[capacity];
    int size = 0;
};

int main() {
    setlocale(LC_CTYPE, "ukr");
    PhoneBook phoneBook;

    while (true) {
        std::cout << "\n����i�� ���i�:" << std::endl;
        std::cout << "1. ������ ��������" << std::endl;
        std::cout << "2. �������� ��������" << std::endl;
        std::cout << "3. ������ �������� �� �I�" << std::endl;
        std::cout << "4. �������� ��i� �������i�" << std::endl;
        std::cout << "5. �������� ��������� ����� � ����" << std::endl;
        std::cout << "6. ����������� ��������� ����� � �����" << std::endl;
        std::cout << "0. ���i�" << std::endl;

        int choice;
        std::cin >> choice;

        switch (choice) {
        case 1: {
            std::string name, homePhone, workPhone, mobilePhone, additionalInfo;
            std::cout << "����i�� �I� ��������: ";
            std::cin >> name;
            std::cout << "����i�� ������i� �������: ";
            std::cin >> homePhone;
            std::cout << "����i�� ������� �������: ";
            std::cin >> workPhone;
            std::cout << "����i�� ���i����� �������: ";
            std::cin >> mobilePhone;
            std::cout << "����i�� ��������� i�������i�: ";
            std::cin >> additionalInfo;

            Contact newContact(name, homePhone, workPhone, mobilePhone, additionalInfo);
            phoneBook.addContact(newContact);
            std::cout << "������� ���i��� �������." << std::endl;
            break;
        }
        case 2: {
            std::string name;
            std::cout << "����i�� �I� ��������, ����� ����i��� ��������: ";
            std::cin >> name;
            phoneBook.removeContact(name);
            break;
        }
        case 3: {
            std::string name;
            std::cout << "������ �I� ��������, ����� ����i��� ������: ";
            std::cin >> name;
            phoneBook.searchContact(name);
            break;
        }
        case 4:
            phoneBook.displayAllContacts();
            break;
        case 5: {
            std::string filename;
            std::cout << "����i�� i�'� ����� ��� ���������� ��������� �����: ";
            std::cin >> filename;
            phoneBook.saveToFile(filename);
            break;
        }
        case 6: {
            std::string filename;
            std::cout << "����i�� i�'� ����� ��� ������������ ��������� �����: ";
            std::cin >> filename;
            phoneBook.loadFromFile(filename);
            break;
        }
        case 0:
            return 0;
        default:
            std::cout << "������������ ���i�. ��������� �� ���." << std::endl;
        }
    }
}



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
