#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

class PasswordGenerator {
private:
    const string digits = "0123456789";
    const string letters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const string letters_digits = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    const string all_characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-_+!@$#%^&*";

public:
    PasswordGenerator() {
        srand(time(0));
    }

    string generate(int length, int complexity) {
        string characters;
        switch (complexity) {
        case 1:
            characters = letters;
            break;
        case 2:
            characters = letters_digits;
            break;
        case 3:
            characters = all_characters;
            break;
        case 4:
            characters = digits;
            break;
        default:
            cout << "Error: Invalid complexity level. Using default (all characters)." << endl;
            characters = all_characters;
        }

        string password = "";
        for (int i = 0; i < length; i++) {
            password += characters[rand() % characters.size()]; // генерация паролей
        }
        return password;
    }
};

class PasswordFileManager {
private:
    const string file_name = "passwords.txt";

public:
    void save_password(const string& password) {
        ofstream file(file_name, ios::app); // запись в конец
        if (file.is_open()) {
            file << password << endl;
            file.close();
        }
        else {
            cout << "Error: Unable to open file for writing." << endl;
        }
    }

    void display_passwords() {
        ifstream file(file_name);
        if (file.is_open()) {
            string line;
            int index = 1;
            cout << "--- Saved Passwords ---" << endl;
            bool has_passwords = false;
            while (getline(file, line)) {
                cout << index << ": " << line << endl;
                index++;
                has_passwords = true;
            }
            file.close();

            if (!has_passwords) {
                cout << "No passwords have been saved yet." << endl;
            }
        }
        else {
            cout << "Error: Unable to open file for reading." << endl;
        }
    }

    void delete_all_passwords() {
        ofstream file(file_name, ios::trunc); // очистка всего файла
        if (file.is_open()) {
            file.close();
            cout << "All passwords have been deleted successfully." << endl;
        }
        else {
            cout << "Error: Unable to open file for deleting." << endl;
        }
    }

    void delete_password_by_number(int number) {
        ifstream file(file_name);
        if (!file.is_open()) {
            cout << "Error: Unable to open file for reading." << endl;
            return;
        }

        vector<string> passwords; // сохраняем все все пароли в вектор, потом 1 из них удалим и перезапишем файл
        string line;
        while (getline(file, line)) {
            passwords.push_back(line);
        }
        file.close();

        if (number < 1 || number > passwords.size()) {
            cout << "Error: Invalid password number." << endl;
            return;
        }

        passwords.erase(passwords.begin() + (number - 1));

        ofstream out_file(file_name, ios::trunc); // перезапись файла
        if (out_file.is_open()) {
            for (const auto& password : passwords) {
                out_file << password << endl;
            }
            out_file.close();
            cout << "Password number " << number << " has been deleted successfully." << endl;
        }
        else {
            cout << "Error: Unable to open file for writing." << endl;
        }
    }
};

class PasswordManager {
private:
    PasswordGenerator generator;
    PasswordFileManager file_manager;

    int get_positive_number(const string& prompt) { // проверка если пользователь ввел не цифру или число
        int value;
        while (true) {
            cout << prompt;
            string input;
            cin >> input;

            try {
                value = stoi(input);
                if (value > 0) {
                    break;
                }
                else {
                    cout << "Error: Value must be greater than zero! Please try again." << endl;
                }
            }
            catch (invalid_argument&) {
                cout << "Error: Please enter a valid number!" << endl;
            }
            catch (out_of_range&) {
                cout << "Error: Number is out of range!" << endl;
            }
        }
        return value;
    }

    int get_complexity_level() {
        int level;
        while (true) {
            cout << "Choose password complexity level:\n";
            cout << "1. Letters only\n";
            cout << "2. Letters and digits\n";
            cout << "3. All characters (letters, digits, symbols)\n";
            cout << "4. Digits only\n";
            cout << "Enter your choice: ";
            string input;
            cin >> input;

            try {
                level = stoi(input); // тоже проверка на числа
                if (level >= 1 && level <= 4) {
                    break;
                }
                else {
                    cout << "Error: Please choose a valid complexity level (1-4)." << endl;
                }
            }
            catch (invalid_argument&) {
                cout << "Error: Please enter a valid number!" << endl;
            }
            catch (out_of_range&) {
                cout << "Error: Number is out of range!" << endl;
            }
        }
        return level;
    }

    void generate_and_save_passwords() {
        int length = get_positive_number("Amount of symbols in your passwords: ");
        int complexity = get_complexity_level();
        int count = get_positive_number("How many passwords do you want to generate? ");

        for (int i = 0; i < count; i++) {
            string password = generator.generate(length, complexity);
            cout << "Password " << i + 1 << ": " << password << endl;
            file_manager.save_password(password);
        }
    }

    void display_menu() {
        cout << "\n--- Password Manager Menu ---" << endl;
        cout << "1. Generate and save passwords" << endl;
        cout << "2. Display saved passwords" << endl;
        cout << "3. Delete all saved passwords" << endl;
        cout << "4. Delete a specific password by its number" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
    }

public:
    void run() {
        while (true) {
            display_menu();
            int choice = get_positive_number("");

            switch (choice) {
            case 1:
                generate_and_save_passwords();
                break;
            case 2:
                file_manager.display_passwords();
                break;
            case 3:
                file_manager.delete_all_passwords();
                break;
            case 4:
            {
                int number = get_positive_number("Enter the number of the password to delete: ");
                file_manager.delete_password_by_number(number);
                break;
            }
            case 5:
                cout << "Exiting program. Goodbye!" << endl;
                return;
            default:
                cout << "Error: Invalid choice. Please try again." << endl;
            }
        }
    }
};

int main() {
    PasswordManager manager;
    manager.run();
}
