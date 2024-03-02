#include <iostream>
#include <ios>
#include <limits>
using namespace std;


bool programIsFinished = false;

struct
{
    double rupiah = 0.00;
    double dollar = 0.00;
    double euro = 0.00;
    double yen = 0.00;
} dataCurrency;

struct
{
    string myName = "Mohammad Guntur Adyatma";
    string myNIM = "2309106023";
} dataMahasiswa;


int currencyExchange(int whichCurrency, double insertedCurrency)
{
    switch(whichCurrency)
    {
    case 1:
        dataCurrency.rupiah = insertedCurrency;
        dataCurrency.dollar = insertedCurrency / 15700;
        dataCurrency.euro = insertedCurrency / 17037;
        dataCurrency.yen = insertedCurrency / 104;
        break;
    case 2:
        dataCurrency.rupiah = insertedCurrency * 15700;
        dataCurrency.dollar = insertedCurrency;
        dataCurrency.euro = insertedCurrency * 0.92;
        dataCurrency.yen = insertedCurrency * 150;
        break;
    case 3:
        dataCurrency.rupiah = insertedCurrency * 17037;
        dataCurrency.dollar = insertedCurrency * 1.08;
        dataCurrency.euro = insertedCurrency;
        dataCurrency.yen = insertedCurrency * 162;
        break;
    case 4:
        dataCurrency.rupiah = insertedCurrency * 104;
        dataCurrency.dollar = insertedCurrency / 150;
        dataCurrency.euro = insertedCurrency / 162;
        dataCurrency.yen = insertedCurrency;
        break;
    }

    return 0;
}





int menu(int numberOfChoices)
{
    while (true)
    {
        int choice;
        cin >> choice;
        if (choice <= numberOfChoices)
        {
            return choice;
        }
            else
            {
                cout << "Masukkan sesuai jumlah opsi! \n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
    }
}


void currencyExchangeMain()
{
    bool programRepeats = true;
    int currencyChoice, repeatChoice;
    double amountOfCurrency;

    cout << endl << "Welcome to Currency Exchange Limited! \n";

    while (programRepeats == true)
    {
        cout << endl << "Choose a currency to exchange from: \n"
                "1. Rupiah \n"
                "2. Dollar \n"
                "3. Euro \n"
                "4. Yen \n";

        currencyChoice = menu(4);
        cout << endl << "Enter the desired amount to be converted: \n";
        cin >> amountOfCurrency;

        currencyExchange(currencyChoice, amountOfCurrency);

        cout << endl << "The currency after being converted: \n";
        cout << "Rupiah: " << dataCurrency.rupiah << endl;
        cout << "Dollar: " << dataCurrency.dollar << endl;
        cout << "Euro: " << dataCurrency.euro << endl;
        cout << "Yen: " << dataCurrency.yen << endl;


        cout << endl << "Would you like to repeat the program? \n"
                        "1. Yes \n"
                        "2. No \n";
        repeatChoice = menu(2);
        if (repeatChoice = 2)
        {
            programRepeats = false;
            programIsFinished = true;
        }
        cout << endl;
    }
}


int loginCheck(string insertedName, string insertedNIM)
{
    if (insertedName == dataMahasiswa.myName && insertedNIM == dataMahasiswa.myNIM)
    {
        return true;
    }
        else
        {
            return false;
        }
}

int main()
{
    string inputName, inputNIM;
    int loginAttempts = 0;

    while (loginAttempts < 3 && programIsFinished == false)
    {
        cout << "Enter your username: ";
        getline(cin, inputName);
        cout << "Enter your NIM: ";
        cin >> inputNIM;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (!loginCheck(inputName, inputNIM))
            {
            cout << "Login Failed! \n"
                    "Trying again... \n";
            loginAttempts += 1;
        }

            else
                {
                cout << "Login Succeeded! \n"
                        "Entering Program \n";
                currencyExchangeMain();
            }

    }

    if (loginAttempts = 3)
    {
        cout << "\nLogin Attempts Exceeded"
                "\nClosing Program";
    }

    return 0;
}
