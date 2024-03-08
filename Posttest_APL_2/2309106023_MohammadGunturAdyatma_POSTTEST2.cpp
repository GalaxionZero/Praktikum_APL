#include <iostream>
#include <limits>
using namespace std;

bool programIsFinished = false;
string cityNames[7] = {"Learoston"};
int totalAmountOfCities = 1;

struct
{
    string myName = "Mohammad Guntur Adyatma";
    string myNIM = "2309106023";
} dataMahasiswa;


int menu(int numberOfChoices)
{
    while (true)
    {
        int choice;
        if (cin >> choice && choice >= 0 && choice <= numberOfChoices)
        {
            return choice;
        }
            else
            {
                cout << "Enter numbers according to the menu! \n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
    }
}


int createCityName(int sizeOfArray)
{
    string newCityName;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, newCityName);
    cityNames[sizeOfArray] = newCityName;
    totalAmountOfCities += 1;

    return 0;
}


int readCityNames(int sizeOfArray)
{
    cout << endl;
    for (int i = 0; i < sizeOfArray; i++)
    {
        cout << i+1 << ". " << cityNames[i] << endl;
    }

    return 0;
}


void changeCityName(int sizeOfArray)
{
    int position;
    readCityNames(sizeOfArray);

    cout << "\nChoose the city you'd like to change the name of El Presidente\n";
    position = menu(sizeOfArray);
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "\nEnter the new name El Presidente\n";
    getline(cin, cityNames[position-1]);

    cout << "\nThe city's name has been changed El Presidente\n";
}


void deleteCity(int sizeOfArray)
{
    int position;
    readCityNames(sizeOfArray);

    cout << "\nChoose the city you'd like to delete El Presidente\n";
    position = menu(sizeOfArray);
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int i = position-1; i < sizeOfArray-1; i++)
    {
        cityNames[i] = cityNames[i+1];
    }

    totalAmountOfCities -= 1;
    cout << "\nThe city has been reduced to ashes El Presidente\n";
}


void cityNamesProgram()
{
    bool programRepeats = true;
    int choice;

    cout << "\nWELCOME TO THE REPUBLIC OF LEAROSTON\n"
            "THIS HERE IS A LIST OF THE CITIES WE HAVE";

    readCityNames(totalAmountOfCities);


    while (programRepeats == true)
    {
        cout << "\nWhat would you like to do El Presidente?\n"
                "1. Create a new city\n"
                "2. \"Show me the list of cities!\"\n"
                "3. Change the name of a city\n"
                "4. Destroy a city\n"
                "0. \"I would like to retire\"\n";


        choice = menu(4);

        switch (choice)
        {
        case 0:
            programRepeats = false;
            programIsFinished = true;
            break;
        case 1:
            cout << "\nEnter the name of the new city El Presidente\n";
            createCityName(totalAmountOfCities);
            cout << "\nThe city has been added El Presidente";
            break;
        case 2:
            cout << "\nHere is the names of our cities El Presidente:\n";
            readCityNames(totalAmountOfCities);
            break;
        case 3:
            changeCityName(totalAmountOfCities);
            break;
        case 4:
            deleteCity(totalAmountOfCities);
            break;
        default:
            cout << "You are not supposed to be here";
            break;
        }
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

    while (loginAttempts < 3 && !programIsFinished)
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
                cityNamesProgram();
            }

    }

    if (loginAttempts == 3)
    {
        cout << "\nLogin Attempts Exceeded"
                "\nClosing Program";
    }

    return 0;
}
