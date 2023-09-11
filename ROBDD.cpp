#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main()
{
    ifstream inputFile;
    ofstream outputFile;

    string inputStr;

    int i = 0, p = 0, o = 0, p = 0;
    char ob;
    vector<char> ilb;
    vector<vector<char>> sheet;

    while (true)
    {
        string command;

        if (command == ".i")
            inputFile >> i;

        else if (command == ".o")
            inputFile >> o;

        else if (command == ".ilb")
        {
            char sign;
            inputFile >> sign;
            ilb.push_back(sign);
        }

        else if (command == ".ob")
            inputFile >> ob;

        else if (command == ".p")
        {
            int num = 0;
            vector<vector<char>> trueCombination;
            inputFile >> p >> num;

            for (size_t a = 0; a < num; a++)
            {
                vector<char> stateCombination;
                for (size_t b = 0; b < (i + o); b++)
                {
                    char state;
                    inputFile >> state;
                    stateCombination.push_back(state);
                }
                trueCombination.push_back(stateCombination);
            }

            for (size_t j = 0; j < p; j++)
            {
                for (size_t k = 0; k < 3; k++)
                {
                    if (i == 0)
                    {
                        sheet.push_back({'0', 'X', 'X', '0'});
                    }
                    else if (i == (pow(2, i) - 1))
                    {
                        sheet.push_back({'1', 'X', 'X', '1'});
                    }
                    else
                    {
                        char variable, elseEdge, thenEdge, comment;

                        sheet.push_back({variable, elseEdge, thenEdge, comment});
                    }
                }
            }
        }

        else
        {
            cout << "Command Error" << endl;
            return 1;
        }
    }
}