#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
#include <string>
#include <math.h>

using namespace std;

int main()
{
    ifstream inputFile;
    ofstream outputFile;

    string inputStr;

    int i = 0, o = 0, p = 0;
    char ob;
    vector<char> ilb;
    vector<vector<char>> sheet;
    vector<string> logicSheet;

    while (true)
    {
        string command;

        if (command == ".i")
        {
            inputFile >> i;
            const int bitsize = 8;
            string logic;
            for (size_t a = 0; a < (pow(2, i + 1)); a++) // 製作預設邏輯樹
            {
                logic = bitset<bitsize>(a).to_string();
                int logicLength = logic.length();
                if (logicLength > i)
                {
                    logic.erase(0, logicLength - i);
                }
                else if (logicLength < i)
                {
                    logic.insert(0, i - logicLength, 0);
                }
                logicSheet.push_back(logic);
            }
        }

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

            for (size_t a = 0; a < num; a++) // 讀True的組合
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
            // 製作出表格陣列
            for (size_t j = 0, signCount = 0, edgeCount = 2; j < p; j++)
            {
                if (j > pow(2, signCount)) // 判斷是否下一層了
                    signCount++;
                for (size_t k = 0; k < 3; k++) // 計算表格數值
                {
                    if (i == 0) // 第一row數值
                    {
                        sheet.push_back({'0', 'X', 'X', '0'});
                    }
                    else if (i == (pow(2, i) - 1)) // 最後一row數值
                    {
                        sheet.push_back({'1', 'X', 'X', '1'});
                    }
                    else // 中間row的數值
                    {
                        char variable, elseEdge, thenEdge, comment;

                        variable = (97 + signCount); // 符號判斷
                        if (signCount == i)
                        {
                            for (size_t c = 1; c < pow(2, i); c++) // 結果判斷
                            {
                            }
                        }
                        else
                        {
                            elseEdge = edgeCount;
                            edgeCount++;
                            thenEdge = edgeCount;
                            edgeCount++;
                        }
                        comment = 'X';
                        sheet.push_back({variable, elseEdge, thenEdge, comment});
                    }
                }
            }
        }

        else if (command == ".e")
        {
            for (auto &logic : logicSheet)
            {
                cout << logic << endl;
            }
            return 0;
        }

        else
        {
            cout << "Command Error" << endl;
            return 1;
        }
    }
}