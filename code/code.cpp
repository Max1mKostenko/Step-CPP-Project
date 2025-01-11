#include <iostream>  
#include <string>    
using namespace std;

// Function to generate a random password of a given length
string generator_password(int length) {
    const char characters[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-_+!@$#%^&*";
    const int characters_size = sizeof(characters) - 1; // Calculate the size of available characters

    string password = "";
    for (int i = 0; i < length; i++) {
        password += characters[rand() % characters_size]; // Add a random character from the list
    }

    return password;
}

int main() {
    srand(time(0));

    int length;
    do {
        cout << "Amount of symbols in your passwords: ";
        cin >> length;

        if (length <= 0) {
            cout << "Error: Length must be greater than zero! Please try again." << endl;
        }
    } while (length <= 0); // Repeat until the user enters a valid length

    int count;
    do {
        cout << "How many passwords do you want to generate? ";
        cin >> count;

        if (count <= 0) {
            cout << "Error: The number of passwords must be greater than zero! Please try again." << endl;
        }
    } while (count <= 0); // Repeat until the user enters a valid count

    for (int i = 0; i < count; i++) {
        cout << "Password " << i + 1 << ": " << generator_password(length) << endl; // Generate and display passwords
    }
}
