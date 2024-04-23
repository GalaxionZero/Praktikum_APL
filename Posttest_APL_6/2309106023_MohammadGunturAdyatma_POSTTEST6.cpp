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


struct cityData citdat[7];


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


int createCityName(int& sizeOfArray)
{
    if (sizeOfArray == 7)
    {
        cout << "You do not need to take over more cities El Presidente!";
        return -1;
    }

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
    citdat[sizeOfArray].name = newCityName;
    citdat[sizeOfArray].pop.populationAmount = newCityPopulation;
    citdat[sizeOfArray].pop.populationMedianAge = newCityMedian;
    sizeOfArray += 1;

    return 0;
}


void selectionSort(cityData citdat[], int* sizeOfArray, bool sortAscending)
{
    int i, j, minimum;
    if (sortAscending == true)
    {
        cityData temp;
        for (i = 0; i < *sizeOfArray - 1; i++)
        {
            minimum = i;
            for (j = i+1; j < *sizeOfArray; j++)
            {
                if (citdat[j].name > citdat[minimum].name)
                {
                    minimum = j;
                }
            }
            if (minimum != i)
            {
                temp = citdat[minimum];
                citdat[minimum] = citdat[j];
                citdat[j] = temp;
            }

        }
    }
        else
        {
            cityData temp;
            for (i = 0; i < *sizeOfArray - 1; i++)
            {
                minimum = i;
                for (j = i+1; j < *sizeOfArray; j++)
                {
                    if (citdat[j].name < citdat[minimum].name)
                    {
                        minimum = j;
                    }
                }
                if (minimum != i)
                {
                    temp = citdat[minimum];
                    citdat[minimum] = citdat[j];
                    citdat[j] = temp;
                }
            }
        }
}


void insertionSort(cityData citdat[], int* sizeOfArray)
{
    int i, j;
    cityData key;
    for (i = 1; i < *sizeOfArray; i++)
    {
        key = citdat[i];
        j = i-1;
        while (j >= 0 && citdat[j].pop.populationAmount > key.pop.populationAmount)
        {
            citdat[j+1] = citdat[j];
            j = j-1;
        }
        citdat[j+1] = key;
    }
}


void shellSort(cityData citdat[], int* sizeOfArray)
{
    for (int gap = *sizeOfArray/2; gap > 0; gap/=2)
    {
        for (int i = gap; i < *sizeOfArray; i++)
        {
            cityData temp = citdat[i];
            int j;
            for (j = i; j >= gap && citdat[j-gap].pop.populationMedianAge > temp.pop.populationMedianAge; j -= gap)
            {
                citdat[j] = citdat[j-gap];
            }
            citdat[j] = temp;
        }
    }
}


int readCityNames(int currentSize, int sizeOfArray, int choiceForSorting)
{
    if (currentSize >= sizeOfArray)
    {
        return 0;
    }

    switch (choiceForSorting)
    {
    case 1:
        selectionSort(citdat, &totalAmountOfCities, false);
        break;
    case 2:
        insertionSort(citdat, &totalAmountOfCities);
        break;
    case 3:
        shellSort(citdat, &totalAmountOfCities);
        break;
    }

    cout << endl << currentSize+1 << ". " << citdat[currentSize].name <<
    "| Population: " << citdat[currentSize].pop.populationAmount <<
    "| Median Age: " << citdat[currentSize].pop.populationMedianAge;


    return readCityNames(currentSize+1, sizeOfArray, choiceForSorting);
}


int citySearch(string key, int* sizeOfArray, cityData citdat[], int searchingType)
{
    if (searchingType == 1)
    {
        selectionSort(citdat, sizeOfArray, true);
        // Binary Search
        int low = 0;
        int high = *sizeOfArray;
        int mid = (low + high)/2;

        while (true)
        {
            if (key != citdat[mid].name)
            {
                if (low == high)
                {
                    return -1;
                }
                    else if (key > citdat[mid].name)
                    {
                        high = mid - 1;
                        mid = (mid - 1 + low)/2;
                    }
                    else
                    {
                        low = mid + 1;
                        mid = (mid + 1 + high)/2;
                    }
            }
                else
                {
                    return mid;
                }
        }
    }
        else
        {
            selectionSort(citdat, sizeOfArray, false);
            // Interpolation Search
            int low = 0;
            int high = *sizeOfArray - 1;

            while (low <= high && citdat[low].name <= key && key <= citdat[high].name)
            {
                if (low == high)
                {
                    if (citdat[low].name == key)
                    {
                        return low;
                    }
                    return -1;
                }

                int position = low + ((high - low) / (citdat[high].name[0] - citdat[low].name[0])) * (key[0] - citdat[low].name[0]);
                cout << endl << position << endl;

                if (citdat[position].name == key)
                {
                    return position;
                }
                    else if (citdat[position].name > key)
                    {
                        high = position - 1;
                    }
                    else
                    {
                        low = position + 1;
                    }
            }
            return -1;
        }
}


void changeCityData(int sizeOfArray)
{
    int position;
    string renamedCityName, renamedCityPopulation, renamedCityMedian;
    readCityNames(0, sizeOfArray, 1);

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

    citdat[position-1].name = renamedCityName;
    citdat[position-1].pop.populationAmount = renamedCityPopulation;
    citdat[position-1].pop.populationMedianAge = renamedCityMedian;
    cout << "\nThe city's name has been changed El Presidente\n";
}


void deleteCity(int* sizeOfArray)
{
    int position;
    readCityNames(0, *sizeOfArray, 1);

    cout << endl << "\nChoose the city you'd like to destroy El Presidente\n";
    position = menu(*sizeOfArray);
    cin.clear();

    for (int i = position-1; i < *sizeOfArray-1; i++)
    {
        citdat[i].name = citdat[i+1].name;
        citdat[i].pop.populationAmount = citdat[i+1].pop.populationAmount;
        citdat[i].pop.populationMedianAge = citdat[i+1].pop.populationMedianAge;
    }

    totalAmountOfCities -= 1;
    cout << "\nThe city has been reduced to ashes El Presidente\n";
}


void cityNamesProgram()
{
    bool programRepeats = true;
    int choice, sortingChoice, searchingIndex, searchingType;
    string searchedCity;
    citdat[0].name = "Learoston";
    citdat[0].pop.populationAmount = "23000000";
    citdat[0].pop.populationMedianAge = "34";

    cout << "\nWELCOME TO THE REPUBLIC OF LEAROSTON\n"
            "THIS HERE IS A LIST OF THE CITIES WE HAVE";

    readCityNames(0, totalAmountOfCities, 1);
    cout << endl;


    while (programRepeats == true)
    {
        if (totalAmountOfCities == 7)
        {
            cout << endl << "El Presidente! You have controlled enough cities to declare yourself as the legitimate government!";
        }

        cout << "\nWhat would you like to do El Presidente?\n"
                "1. Create a new city\n"
                "2. \"Show me the list of cities!\"\n"
                "3. \"Is there a city called...\"\n"
                "4. Change the name of a city\n"
                "5. Destroy a city\n"
                "0. \"I would like to retire\"\n";


        choice = menu(4);

        switch (choice)
        {
            case 0:
                programRepeats = false;
                programIsFinished = true;
                break;
            case 1:
                if (createCityName(totalAmountOfCities) == 0);
                {
                    cout << "\nThe city has been added El Presidente\n";
                }
                break;
            case 2:
                cout << "How would you like the information be presented El Presidente?" << endl;
                cout << "1. \"By Names\"" << endl;
                cout << "2. \"By Population\"" << endl;
                cout << "3. \"By Median Age\"" << endl;
                sortingChoice = menu(3);

                cout << "\nHere is the names of our cities El Presidente:\n";
                readCityNames(0, totalAmountOfCities, sortingChoice);
                cout << endl;
                break;
            case 3:
                cout << "What is the name of this city you are searching for El Presidente?\n";
                getline(cin, searchedCity);
                cout << "And how would you like it be done?" << endl <<
                        "1. \"As soon as possible!\"" << endl <<
                        "2. \"Take your time.\"";
                searchingType = menu(2);
                searchingIndex = citySearch(searchedCity, &totalAmountOfCities, citdat, searchingType);

                if (searchingIndex != -1)
                {
                    cout << "Here is the city's details:";
                    cout << endl << citdat[searchingIndex].name <<
                    "| Population: " << citdat[searchingIndex].pop.populationAmount <<
                    "| Median Age: " << citdat[searchingIndex].pop.populationMedianAge;
                }
                    else
                    {
                        cout << "The city you searched for does not exist El Presidente!" << endl;
                    }
                break;
            case 4:
                changeCityData(totalAmountOfCities);
                break;
            case 5:
                deleteCity(&totalAmountOfCities);
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
