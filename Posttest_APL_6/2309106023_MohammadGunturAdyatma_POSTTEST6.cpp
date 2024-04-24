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
    int populationAmount;
    double populationMedianAge;
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

    string newCityName;
    int newCityPopulation;
    double newCityMedian;
    cin.clear();
    bool validName = false, validPopulation = false, validMedian = false;

    while (!validName)
    {
        cout << "\nEnter the name of the new city El Presidente\n";
        getline(cin, newCityName);
        if (newCityName.empty())
        {
            cout << "Please enter a name El Presidente!";
        }
            else
            {
                validName = true;
            }
    }
    cin.clear();
    while (!validPopulation)
    {
        cout << "\nEnter the population of the new city El Presidente\n";
        if (cin >> noskipws >> newCityPopulation && newCityPopulation > 0)
        {
            validPopulation = true;
            cin.clear();
            cin.ignore();
        }
            else
            {
                cout << "Please enter a number El Presidente!";
                cin.clear();
                cin.ignore();
            }
    }
    while (!validMedian)
    {
        cout << "\nEnter the median age of the new city El Presidente\n";
        if (cin >> noskipws >> newCityMedian && newCityMedian > 0)
        {
            validMedian = true;
            cin.clear();
            cin.ignore();
        }
            else
            {
                cout << "Pleas enter a number El Presidente!";
                cin.clear();
                cin.ignore();
            }
    }
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
            cityData temp = citdat[minimum];
            citdat[minimum] = citdat[i];
            citdat[i] = temp;
            }
        }
    }
        //Legacy code for a failed interpolation search integration
        //I'm leaving it as is for learning purposes
        else
        {
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
                cityData temp = citdat[minimum];
                citdat[minimum] = citdat[i];
                citdat[i] = temp;
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
        while (j >= 0 && citdat[j].pop.populationAmount < key.pop.populationAmount)
        {
            citdat[j+1] = citdat[j];
            j = j-1;
        }
        citdat[j+1] = key;
    }
}


void shellSort(cityData citdat[], int sizeOfArray)
{
    for (int gap = sizeOfArray/2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < sizeOfArray; i++)
        {
            cityData temp = citdat[i];
            int j;
            for (j = i; j >= gap && citdat[j-gap].pop.populationMedianAge < temp.pop.populationMedianAge; j -= gap)
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
        selectionSort(citdat, &totalAmountOfCities, true);
        break;
    case 2:
        insertionSort(citdat, &totalAmountOfCities);
        break;
    case 3:
        shellSort(citdat, totalAmountOfCities);
        break;
    }

    cout << endl << currentSize+1 << ". " << citdat[currentSize].name <<
    "| Population: " << citdat[currentSize].pop.populationAmount <<
    "| Median Age: " << citdat[currentSize].pop.populationMedianAge;


    return readCityNames(currentSize+1, sizeOfArray, choiceForSorting);
}


int cityNameSearch(string key, int sizeOfArray, cityData citdat[])
{
    // Binary Search
    selectionSort(citdat, &sizeOfArray, true); // Uses an ascending sort method categorised by the true argument.
    int low = 0;
    int high = sizeOfArray - 1;

    while (low <= high)
    {

        int mid = (low + high)/2;
        if (key == citdat[mid].name)
        {
            return mid;
        }
            else if (key < citdat[mid].name)
            {
                high = mid - 1;
            }
            else
            {
                low = mid + 1;
            }
    }
    return -1;
}


int cityMedianSearch(double key, int sizeOfArray, cityData citdat[])
{
    // Shell Sort
    shellSort(citdat, sizeOfArray);

    int low = 0;
    int high = sizeOfArray - 1;

    while (low <= high && key <= citdat[low].pop.populationMedianAge && key >= citdat[high].pop.populationMedianAge)
    {
        int position = low + ((double)(key - citdat[low].pop.populationMedianAge) / (citdat[high].pop.populationMedianAge - citdat[low].pop.populationMedianAge)) * (high - low);

        if (low == high)
        {
            if (citdat[low].pop.populationMedianAge == key)
            {
                return low;
            }
                else
                {
                    return -1;
                }
        }
        if (key == citdat[position].pop.populationMedianAge)
        {
            return position;
        }
        else if (key > citdat[position].pop.populationMedianAge)
        {
            low = position + 1;
        }
        else
        {
            high = position - 1;
        }
    }

    return -1;
}


//int cityMedianSearch(int key, int sizeOfArray, cityData citdat[])
//{
//    //Interpolation Search
//    shellSort(citdat, sizeOfArray);
//
//    int low = 0;
//    int high = sizeOfArray - 1;
//
//    while (low <= high && key >= citdat[low].pop.populationMedianAge && key <= citdat[high].pop.populationMedianAge)
//    {
//        int position = low + ((double)(key - citdat[low].pop.populationMedianAge) / (citdat[high].pop.populationMedianAge - citdat[low].pop.populationMedianAge)) * (high - low);
//
//        if (key == citdat[position].pop.populationMedianAge)
//        {
//            return position;
//        }
//            else if (key > citdat[position].pop.populationMedianAge)
//            {
//                high = position - 1;
//            }
//            else
//            {
//                low = position + 1;
//            }
//    }
//
//    return -1;
//}


void changeCityData(int sizeOfArray)
{
    int position;
    string renamedCityName;
    int renamedCityPopulation;
    double renamedCityMedian;
    bool validName = false, validPopulation = false, validMedian = false;

    while (!validName)
    {
        cout << "\nEnter the name of the new city El Presidente\n";
        getline(cin, renamedCityName);
        if (renamedCityName.empty())
        {
            cout << "Please enter a name El Presidente!";
        }
            else
            {
                validName = true;
            }
    }
    cin.clear();
    while (!validPopulation)
    {
        cout << "\nEnter the population of the new city El Presidente\n";
        if (cin >> noskipws >> renamedCityPopulation && renamedCityPopulation > 0)
        {
            validPopulation = true;
            cin.clear();
            cin.ignore();
        }
            else
            {
                cout << "Please enter a number El Presidente!";
                cin.clear();
                cin.ignore();
            }
    }
    while (!validMedian)
    {
        cout << "\nEnter the median age of the new city El Presidente\n";
        if (cin >> noskipws >> renamedCityMedian && renamedCityMedian > 0)
        {
            validMedian = true;
            cin.clear();
            cin.ignore();
        }
            else
            {
                cout << "Pleas enter a number El Presidente!";
                cin.clear();
                cin.ignore();
            }
    }
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
    double searchedMedian;
    string searchedCity;
    citdat[0].name = "Learoston";
    citdat[0].pop.populationAmount = 23000000;
    citdat[0].pop.populationMedianAge = 34;

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
                "4. \"What was the city with the median age...\"\n"
                "5. Change the name of a city\n"
                "6. Destroy a city\n"
                "0. \"I would like to retire\"\n";


        choice = menu(6);

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

                cout << "\nHere is the names of our cities El Presidente:" << endl;
                readCityNames(0, totalAmountOfCities, sortingChoice);
                cout << endl;
                break;
            case 3:
                cout << "\"Is there a city called...\"" << endl;
                cin >> searchedCity;
                searchingIndex = cityNameSearch(searchedCity, totalAmountOfCities, citdat);

                if (searchingIndex != -1)
                {
                    cout << "Here is the city's details:";
                    cout << endl << citdat[searchingIndex].name <<
                    "| Population: " << citdat[searchingIndex].pop.populationAmount <<
                    "| Median Age: " << citdat[searchingIndex].pop.populationMedianAge;
                    cin.clear();
                    cin.ignore();
                }
                    else
                    {
                        cout << "The city you searched for does not exist El Presidente!" << endl;
                        cin.clear();
                        cin.ignore();
                    }
                break;
            case 4:
                cout << "\"What was the city with the median age...\"" << endl;
                cin >> searchedMedian;
                searchingIndex = cityMedianSearch(searchedMedian, totalAmountOfCities, citdat);

                if (searchingIndex != -1)
                {
                    cout << "Here is the city's details:";
                    cout << endl << citdat[searchingIndex].name <<
                    "| Population: " << citdat[searchingIndex].pop.populationAmount <<
                    "| Median Age: " << citdat[searchingIndex].pop.populationMedianAge;
                    cin.clear();
                    cin.ignore();
                }
                    else
                    {
                        cout << "The city you searched for does not exist El Presidente!" << endl;
                        cin.clear();
                        cin.ignore();
                    }
                break;
            case 5:
                changeCityData(totalAmountOfCities);
                break;
            case 6:
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
