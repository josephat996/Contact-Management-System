
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class Contact {
private:
    std::string name;
    std::string phone;
    std::string email;

public:
    // Constructor
    Contact() {}
    Contact(const std::string& name, const std::string& phone, const std::string& email)
        : name(name), phone(phone), email(email) {}

    // Getter and Setter Methods
    void setName(const std::string& name) { this->name = name; }
    void setPhone(const std::string& phone) { this->phone = phone; }
    void setEmail(const std::string& email) { this->email = email; }

    std::string getName() const { return name; }
    std::string getPhone() const { return phone; }
    std::string getEmail() const { return email; }

    // Save contact to file
    void saveToFile(std::ofstream& file) const {
        file << name << "," << phone << "," << email << std::endl;
    }

    // Load contact from a string
    static Contact fromString(const std::string& data) {
        size_t pos1 = data.find(',');
        size_t pos2 = data.find(',', pos1 + 1);
        return Contact(data.substr(0, pos1), data.substr(pos1 + 1, pos2 - pos1 - 1), data.substr(pos2 + 1));
    }

    // Display contact details
    void display() const {
        std::cout << "Name: " << name << "\nPhone: " << phone << "\nEmail: " << email << "\n";
    }
};

class ContactManager {
private:
    std::vector<Contact> contacts;
    const std::string filename = "contacts.txt";

public:
    // Load contacts from file
    void loadFromFile() {
        std::ifstream file(filename);
        std::string line;
        contacts.clear();
        while (std::getline(file, line)) {
            contacts.push_back(Contact::fromString(line));
        }
        file.close();
    }

    // Save contacts to file
    void saveToFile() const {
        std::ofstream file(filename, std::ios::trunc);
        for (const auto& contact : contacts) {
            contact.saveToFile(file);
        }
        file.close();
    }

    // Add a new contact
    void addContact(const Contact& contact) {
        contacts.push_back(contact);
        saveToFile();
    }

    // Search for a contact by name
    void searchContact(const std::string& name) const {
        for (const auto& contact : contacts) {
            if (contact.getName() == name) {
                contact.display();
                return;
            }
        }
        std::cout << "Contact not found!" << std::endl;
    }

    // Modify a contact by name
    void modifyContact(const std::string& name) {
        for (auto& contact : contacts) {
            if (contact.getName() == name) {
                std::string newPhone, newEmail;
                std::cout << "Enter new phone: ";
                std::cin >> newPhone;
                std::cout << "Enter new email: ";
                std::cin >> newEmail;
                contact.setPhone(newPhone);
                contact.setEmail(newEmail);
                saveToFile();
                std::cout << "Contact updated successfully!" << std::endl;
                return;
            }
        }
        std::cout << "Contact not found!" << std::endl;
    }

    // Display all contacts
    void displayContacts() const {
        for (const auto& contact : contacts) {
            contact.display();
            std::cout << "----------------------" << std::endl;
        }
    }
};

int main() {
    ContactManager manager;
    manager.loadFromFile();

    int choice;
    do {
        std::cout << "\nContact Management System\n";
        std::cout << "1. Add Contact\n2. Search Contact\n3. Modify Contact\n4. Display All Contacts\n5. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::string name, phone, email;
                std::cout << "Enter name: ";
                std::cin >> name;
                std::cout << "Enter phone: ";
                std::cin >> phone;
                std::cout << "Enter email: ";
                std::cin >> email;
                manager.addContact(Contact(name, phone, email));
                break;
            }
            case 2: {
                std::string name;
                std::cout << "Enter name to search: ";
                std::cin >> name;
                manager.searchContact(name);
                break;
            }
            case 3: {
                std::string name;
                std::cout << "Enter name to modify: ";
                std::cin >> name;
                manager.modifyContact(name);
                break;
            }
            case 4:
                manager.displayContacts();
                break;
            case 5:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid choice!\n";
        }
    } while (choice != 5);

    return 0;
}
