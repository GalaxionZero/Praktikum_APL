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


struct populationData
{
    string populationAmount;
    string populationMedianAge;
};


struct cityData
{
    string name;
    struct populationData pop;
};


struct cityData data[7];


int menu(int numberOfChoices)
{
    while (true)
    {
        int choice;
        cout << "Enter: ";
        if (cin >> noskipws >> choice && choice >= 0 && choice <= numberOfChoices)
        {
            cin.clear();
            cin.ignore();
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
    string newCityName, newCityPopulation, newCityMedian;
    cin.clear();
    do
    {

        cout << "\nEnter the name of the new city El Presidente\n";
        getline(cin, newCityName);
        cout << "\nEnter the population of the new city El Presidente\n";
        getline(cin, newCityPopulation);
        cout << "\nEnter the median age of the new city El Presidente\n";
        getline(cin, newCityMedian);

        if (newCityName.empty() || newCityPopulation.empty() || newCityMedian.empty())
        {
            cout << "One of the data cannot simply be blank El Presidente!";
        }

    }while (newCityName.empty() || newCityPopulation.empty() || newCityMedian.empty());
    data[sizeOfArray].name = newCityName;
    data[sizeOfArray].pop.populationAmount = newCityPopulation;
    data[sizeOfArray].pop.populationMedianAge = newCityMedian;
    totalAmountOfCities += 1;

    return 0;
}


int readCityNames(int currentSize, int sizeOfArray)
{
    if (currentSize >= sizeOfArray)
    {
        return 0;
    }

    cout << endl << currentSize+1 << ". " << data[currentSize].name <<
    "| Population: " << data[currentSize].pop.populationAmount <<
    "| Median Age: " << data[currentSize].pop.populationMedianAge;


    return readCityNames(currentSize+1, sizeOfArray);
}


void changeCityData(int sizeOfArray)
{
    int position;
    string renamedCityName, renamedCityPopulation, renamedCityMedian;
    readCityNames(0, sizeOfArray);

    cout << endl << "\nChoose the city you'd like to change the data of El Presidente\n";
    position = menu(sizeOfArray);
    cin.clear();


    do
    {
        cout << "\nEnter the new name El Presidente: ";
        getline(cin, renamedCityName);
        cout << "\nEnter the city's population El Presidente: ";
        getline(cin, renamedCityPopulation);
        cout << "\nEnter the city's median age El Presidente: ";
        getline(cin, renamedCityMedian);

        if (renamedCityName.empty() || renamedCityPopulation.empty() || renamedCityMedian.empty())
        {
            cout << "One of the data cannot simply be blank El Presidente!";
        }
    }while (renamedCityName.empty() && renamedCityPopulation.empty() && renamedCityMedian.empty());

    data[position-1].name = renamedCityName;
    data[position-1].pop.populationAmount = renamedCityPopulation;
    data[position-1].pop.populationMedianAge = renamedCityMedian;
    cout << "\nThe city's name has been changed El Presidente\n";
}


void deleteCity(int sizeOfArray)
{
    int position;
    readCityNames(0, sizeOfArray);

    cout << endl << "\nChoose the city you'd like to destroy El Presidente\n";
    position = menu(sizeOfArray);
    cin.clear();

    for (int i = position-1; i < sizeOfArray-1; i++)
    {
        data[i].name = data[i+1].name;
        data[i].pop.populationAmount = data[i+1].pop.populationAmount;
        data[i].pop.populationMedianAge = data[i+1].pop.populationMedianAge;
    }

    totalAmountOfCities -= 1;
    cout << "\nThe city has been reduced to ashes El Presidente\n";
}


void cityNamesProgram()
{
    bool programRepeats = true;
    int choice;
    data[0].name = "Learoston";
    data[0].pop.populationAmount = "23000000";
    data[0].pop.populationMedianAge = "34";

    cout << "\nWELCOME TO THE REPUBLIC OF LEAROSTON\n"
            "THIS HERE IS A LIST OF THE CITIES WE HAVE";

    readCityNames(0, totalAmountOfCities);
    cout << endl;


    while (programRepeats == true)
    {
        if (totalAmountOfCities == 7)
        {
            cout << "El Presidente! You have controlled enough cities to declare yourself as the legitimate government!";
        }

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
            createCityName(totalAmountOfCities);
            cout << "\nThe city has been added El Presidente\n";
            break;
        case 2:
            cout << "\nHere is the names of our cities El Presidente:\n";
            readCityNames(0, totalAmountOfCities);
            cout << endl;
            break;
        case 3:
            changeCityData(totalAmountOfCities);
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
        do
        {
            cout << "Enter your username: ";
            getline(cin, inputName);
            if (inputName.empty())
            {
                cout << "Enter a name!\n";
            }
        }while (inputName.empty());

        cout << "Enter your NIM: ";
        cin >> noskipws >> inputNIM;
        cin.clear();
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


/*
    do
    {
        cin.clear();
        cin.ignore();
        cout << "\nEnter the new name El Presidente: ";
        getline(cin, renamedCityName);

        if (renamedCityName.empty())
        {
            cout << "One of the data cannot simply be blank El Presidente!";
        }

    }while (renamedCityName.empty());


    do
    {
        cin.clear();
        cin.ignore();
        cout << "\nEnter the city's population El Presidente: ";
        getline(cin, renamedCityPopulation);
        if (renamedCityPopulation.empty())
        {
            cout << "There needs to be people for a city to exist El Presidente!";
        }

    }while (renamedCityPopulation.empty());

    do
    {
        cin.clear();
        cin.ignore();
        cout << "\nEnter the city's median age El Presidente: ";
        getline(cin, renamedCityMedian);
        if (renamedCityMedian.empty())
        {
            cout << "A city with a population must have a median age El Presidente!";
        }
    }while (renamedCityMedian.empty());

    */
