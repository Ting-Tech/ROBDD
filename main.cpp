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

    inputFile.open("test.txt");

    string inputStr;

    int i = 0, o = 0, p = 0;
    char ob;
    vector<char> ilb;
    vector<vector<string>> sheet;
    vector<string> logicSheet;
    vector<vector<char>> trueCombination;

    while (true)
    {
        string command;

        inputFile >> command;
        // cout << command << endl;

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
            for (size_t c = 0; c < i; c++)
            {
                char sign;
                inputFile >> sign;
                ilb.push_back(sign);
            }
        }

        else if (command == ".ob")
            inputFile >> ob;

        else if (command == ".p")
        {
            int num = 0;
            inputFile >> num;

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
            string edgeCount = "2";
            for (size_t j = 0, signCount = 0; j < pow(2, i) - 1; j++)
            {
                if (j > (pow(2, signCount) - 2)) // 判斷是否下一層了
                {
                    signCount++;
                }
                // 計算表格數值
                // if (j == 0) // 第一row數值
                // {
                //     sheet.push_back({'0', 'X', 'X', '0'});
                // }
                // else if (j == (pow(2, i) - 1)) // 最後一row數值
                // {
                //     sheet.push_back({'1', 'X', 'X', '1'});
                // }
                // else // 中間row的數值
                // {
                string variable, comment;
                string elseEdge, thenEdge;

                variable = (96 + signCount); // 符號判斷
                if (signCount == i)
                {
                    for (size_t c = 0; c < pow(2, i); c++) // 結果判斷
                    {
                        for (size_t d = 0; d < trueCombination.size(); d++) // 跟會成立的條件比較
                        {
                            for (size_t e = 0; e < i; e++)
                            {
                                // cout << "{" << trueCombination[d][e] << " " << logicSheet[c][e] << "}";
                                if (trueCombination[d][e] != '-')
                                {
                                    if ((trueCombination[d][e] != logicSheet[c][e]))
                                    {
                                        if (c % 2 == 0)
                                        {
                                            elseEdge = '0';
                                        }
                                        else
                                        {
                                            thenEdge = '0';
                                        }
                                        break;
                                    }
                                    else
                                    {
                                        int num = pow(2, i);
                                        if (c % 2 == 0)
                                        {
                                            elseEdge = to_string(num);
                                        }
                                        else
                                        {
                                            thenEdge = to_string(num);
                                        }
                                    }
                                }
                            }
                        }
                        // cout << endl;
                    }
                    comment = 'X';
                    sheet.push_back({variable, elseEdge, thenEdge, comment});
                }
                else
                {
                    elseEdge = edgeCount;
                    int num = stoi(edgeCount) + 1;
                    edgeCount = to_string(num);
                    thenEdge = edgeCount;
                    int num2 = stoi(edgeCount) + 1;
                    edgeCount = to_string(num2);
                    comment = 'X';
                    sheet.push_back({variable, elseEdge, thenEdge, comment});
                }
                // }
            }
        }

        else if (command == ".e")
        {
            // for (auto &logic : logicSheet)
            // {
            //     cout << logic << endl;
            // }
            // cout << sheet.size() << endl;
            // cout << trueCombination.size() << endl;
            for (auto &sheets : sheet)
            {
                for (auto &element : sheets)
                {
                    cout << element << " ";
                }
                // cout << sheets[0];
                cout << endl;
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