/* -------------------------------Assignment 1 - Gale Shapley Algorithm--------------------------
Galeshapely_sukriti.cpp

Member function definitions for Class prefer:

void readdata() - Reads data from file and stores into variables
void add_free_people() - adds names of unmatched people to vector - freeperson
void initialize_ranking() - initializes the rankings of people in the pet preference list
void begin_matching() - begins the stable matching algorithm
void stable_matching(string current_person_name) - main stable matching algorithm implementation
void print_answer() - to print the answer to console


Author: Sukriti Tiwari  ----------------------------------------------------------------------    */

/* -----------------------------------------------------------------------
"Prefer" class includes private variables and public functions to store data read from file "program1data.txt".
Member functions are used to initialte each task.
None of the member functions has any return type apart from void.

Assumptions:
Input file name has to be "program1data.txt".
Input data file should handle no more than 100 inputs
No user input from console
**No two names must be same/duplicate**
Preferences are in range 1 to N where N is total number of inputs
Both preference matrices should be n*n
Names are strings and preferences are of type int


----------------------------------------------------------------------------------*/

// ---------------------HEADER FILES------------------------------

#include <iostream>
#include <stdio.h>
#include <string>
#include <list>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

// ----------------------------------------CLASS DEFINED---------------------------------
class prefer
{

    //--------------------------MEMBER VARIABLES DEFINED---------------------------

    vector<pair<int, int>> tentative_pairs;       // to store tentative pairs made during the process of stable matching
    int n, current_owner, current_index;          // to store indices
    string str1, str2, str3, current_person_name; //to store names or intermediate input
    string peoplenames[101], petnames[101];       //array to store names of people and pets
    vector<string> freeperson;
    int peopleList[101][101];                   // people's preference list
    int petList[101][101];                      // pet's preference list
    int ranking[101][101];                      // rankings of people in pet preference list
    ifstream infile;                            //file stream object
    bool available = true;                      //boolean variable to determine if a person is available for matching or not
    map<string, int> string2index;              // Map to link indices and names

    public:
    //------------------------READ DATA FROM FILE-------------------------------
    void readdata()
    {

        infile.open("program1data.txt");
        //---------check if file opens or not-------------------
        if (infile.fail())
        {
            cout << "Error reading file!";
        }

        // -------------if file opens, start reading data--------------
        else
        {

            infile >> n;                 // read number of inputs

            for (int i = 0; i < n; i++)
            {
                infile >> peoplenames[i];               //read names of people

            }
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    infile >> peopleList[i][j];                 //read pet preferences of people
                    peopleList[i][j] = peopleList[i][j] - 1;
                }
            }

            for (int i = 0; i < n; i++)
            {
                infile >> petnames[i];          // read names of pets
            }

            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    infile >> petList[i][j];        // read preferences of pets
                    petList[i][j] = petList[i][j] - 1;
                }
            }
        }
        infile.close();                 // make sure you close the file after reading
    }

    //-------------------------------------ADD NAMES OF PEOPLE TO VECTOR FREEPERSON---------------------------
    void add_free_people()
    {

        for (int i = 0; i < n; i++)
        {
            freeperson.push_back(peoplenames[i]);
            string2index[peoplenames[i]] = i;
        }
    }

    //----------------------------INITIALIZE THE RANKINGS OF PEOPLE IN PET PREFERENCE LIST------------------

    void initialize_ranking()
    {

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
                ranking[i][petList[i][j]] = j; // initialize ranking
        }
    }

    //----------------------------------------------------------------------------------------
    //----------------------------------STABLE MATCHING ALGORITHM----------------------------
    //---------------------------------------------------------------------------------------

    
    void stable_matching(string current_person_name)
    {
//-------------update index of free person-------------------

        auto itr = find(freeperson.begin(), freeperson.end(), current_person_name);
        current_index = string2index[current_person_name];

//------------------loop through preferences of people-------------        
        for (int i = 0; i < n; i++)
        {
            int temp = peopleList[current_index][i];
            for (auto it : tentative_pairs)
            {
                //if pair does not exist, then boolean "available" is true, else false
                if (it.second != temp)
                {
                    available = true;
                }
                else
                {
                    current_owner = it.first;
                    available = false;
                    break;
                }
            }

//---------------IF AVAILABLE = TRUE------------------------            
            if (available == true)
            {
                tentative_pairs.push_back(make_pair(current_index, temp));
                for (auto it2 : freeperson)
                {
                    if (it2 == peoplenames[current_index])
                    {
                        freeperson.erase(remove(freeperson.begin(), freeperson.end(), it2), freeperson.end());
                        break;
                    }
                }
                break;
            }


//-------------------------IF AVAILABLE = FALSE---------------------------------------
            else if (available == false)
            {
                //if pet prefers new person to current owner
                if (ranking[temp][current_index] < ranking[temp][current_owner])
                {
                    //update tentative_pairs
                    for (auto it1 : tentative_pairs)
                    {
                        if (it1.second == temp)
                        {
                            
                            tentative_pairs.erase(remove(tentative_pairs.begin(), tentative_pairs.end(), it1), tentative_pairs.end());
                            tentative_pairs.push_back(make_pair(current_index, temp));
                            break;
                            
                        }
                    }

                    //update freeperson list
                    for (auto it2 : freeperson)
                    {
                        if (it2 == peoplenames[current_index])
                        {
                            freeperson.erase(remove(freeperson.begin(), freeperson.end(), it2), freeperson.end());
                            freeperson.push_back(peoplenames[current_owner]);
                            break;
                        }
                    }
                    break;
                }
            }
        }
    }
//------------------------END OF STABLE MATCHING ALGORITHM-------------------------------

//-------------------------------------BEGIN MATCHING FUNCTION--------------------------

    void begin_matching()
    {
        //--------while freeperson vector is not empty----------------------
        while (!freeperson.empty())
        {
            auto it = freeperson.front();
            stable_matching(it);
        }
    }


//---------------------------PRINT ANSWER TO CONSOLE-------------------------------

    void print_answer()
    {
        sort(tentative_pairs.begin(), tentative_pairs.end());
        for (auto it : tentative_pairs)
        {
            cout << peoplenames[it.first] << " / " << petnames[it.second] << "\n";
        }
    }
};


// -----------------------------------MAIN--------------------------------------------
int main()
{

    //---------------------Class objects defined-------------------------

    prefer p1;

    //------------------------member functions called-----------------------------

    p1.readdata();
    p1.add_free_people();
    p1.initialize_ranking();
    p1.begin_matching();
    p1.print_answer();


    return 0;


        //--------------------end of program----------------------------------------

}
