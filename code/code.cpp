#include <iostream>
using namespace std;

// Function to generate a random password
string generator_password() {
    srand(time(0)); // Seed the random number generator with the current time

    // Array of allowed characters for the password
    const char characters[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789=-_+!@$#%^&*";
    const int characters_size = sizeof(characters) - 1; // Size of the character array, excluding the null terminator

    int length;
    do {
        cout << "Amount of symbols in your password: ";
        cin >> length;

        if (length <= 0) { // Check for invalid input
            cout << "Error: Length must be greater than zero! Please try again." << endl;
        }
    } while (length <= 0); // Repeat until a valid length is entered

    string password = "";

    for (int i = 0; i < length; i++) {
        // Append a random character from the array to the password
        password += characters[rand() % characters_size];
    }

    return "Your new password is: " + password;
}

int main() {
    // Call the password generator function and display the generated password
    cout << generator_password() << endl;
}
