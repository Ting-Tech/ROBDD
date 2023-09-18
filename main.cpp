#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
#include <string>
#include <math.h>

using namespace std;

int main(int argc, char *argv[])
{
    ifstream inputFile;
    ofstream outputFile;

    if(argc != 3)
    {
        cout << "Input fail" << endl;
        return 2;
    }

    inputFile.open(argv[1]);

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

        if (command == ".i")
        {
            inputFile >> i;
            const int bitsize = 8;
            string logic;
            for (size_t a = 0; a < (pow(2, i)); a++) // 製作預設邏輯樹
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
            sheet.push_back({"X", "X", "X", "0"});

            for (size_t j = 0, signCount = 0; j < pow(2, i) - 1; j++)
            {
                if (j > (pow(2, signCount) - 2)) // 判斷是否下一層了
                    signCount++;

                string variable, comment;
                string elseEdge, thenEdge;

                variable = (96 + signCount); // 符號判斷
                if (signCount == i)
                {
                    for (size_t c = 0; c < 2; c++)
                    {
                        for (size_t d = 0; d < trueCombination.size(); d++) // 跟會成立的條件比較
                        {
                            bool lastResult = true;
                            int index = ((j - (pow(2, (i - 1)) - 1)) * 2 + c);

                            for (size_t e = 0; e < i; e++)
                            {
                                bool result = true;

                                if (trueCombination[d][e] == '-')
                                    result = true;
                                else
                                {
                                    if ((trueCombination[d][e] ==
                                         logicSheet[index][e]))
                                        result = true;
                                    else
                                        result = false;
                                }
                                lastResult = (lastResult && result);
                            }
                            if (lastResult == true)
                            {
                                if ((index % 2) == 0)
                                    elseEdge = to_string((int)pow(2, i));
                                else
                                    thenEdge = to_string((int)pow(2, i));
                            }
                            else
                            {
                                if ((index % 2) == 0)
                                    elseEdge = '0';
                                else
                                    thenEdge = '0';
                            }
                            if (lastResult == true)
                                break;
                        }
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
            }
            sheet.push_back({"1", "X", "X", "1"});
        }

        else if (command == ".e")
        {
            for (size_t a = 1; a < sheet.size() - 1; a++)
            {
                for (size_t b = 1 + a; b < sheet.size() - 1; b++)
                {
                    // cout << a << " " << b << endl;
                    if ((sheet[a][0] == sheet[b][0]) &&
                        (sheet[a][1] == sheet[b][1]) &&
                        (sheet[a][2] == sheet[b][2]) &&
                        (sheet[a][3] != "R") &&
                        (sheet[a][1] != sheet[a][2]))
                    {
                        sheet[b][3] = "R";
                        sheet[((b / 2))][((b % 2) + 1)] = to_string((int)a);
                    }
                }
                for (size_t c = 1; c < sheet.size() - 1; c++)
                {
                    if (sheet[c][1] == sheet[c][2])
                    {
                        sheet[((c) / 2)][((c) % 2) + 1] = sheet[c][1];
                        sheet[c][3] = "R";
                    }
                    // if (sheet[c][3] == "R")
                    //     sheet[c].erase(sheet[c].begin(), sheet[c].end());
                }
            }

            // for (auto &logic : logicSheet)
            // {
            //     cout << logic << endl;
            // }

            // cout << sheet.size() << endl;
            // cout << trueCombination.size() << endl;

            for (int x = 0; x < sheet.size(); x++) // 輸出表格
            {
                cout << x << " ";
                for (auto &element : sheet[x])
                    cout << element << " ";
                cout << endl;
            }

            // 輸出dot
            cout << endl
                 << "digraph ROBDD {" << endl
                 << "\t{rank=same";

            string lastSign = "a";
            for (size_t y = 1; y < sheet.size() - 1; y++)
            {
                if (sheet[y][3] != "R")
                {
                    if (sheet[y][0] == lastSign)
                        cout << " " << y;
                    else
                    {
                        lastSign = sheet[y][0];
                        cout << "}" << endl
                             << "\t{rank=same " << y;
                    }
                }
            }
            cout << "}" << endl
                 << endl;

            for (size_t z = 0; z < sheet.size(); z++)
            {
                if (z == 0)
                    cout << "\t0[label=0, shape=box]" << endl;
                else if (z == (sheet.size() - 1))
                    cout << "\t" << z << "[label=1, shape=box]" << endl;
                else
                {
                    if (sheet[z][3] != "R")
                    {
                        cout << "\t" << z << "[label="
                             << '"' << sheet[z][0] << '"' << ']' << endl;
                    }
                }
            }
            cout << endl;
            for (size_t a = 1; a < sheet.size() - 1; a++)
            {
                if (sheet[a][3] != "R")
                {
                    for (size_t b = 1; b < 3; b++)
                    {
                        cout << "\t" << a << "->" << sheet[a][b]
                             << "[label=" << '"' << (b - 1) % 2 << '"'
                             << ", style=";
                        if (b == 1)
                            cout << "dotted";
                        else
                            cout << "solid";
                        cout << "]" << endl;
                    }
                }
            }
            cout << '}' << endl;
            return 0;
        }

        else
        {
            cout << "Command Error" << endl;
            return 1;
        }
    }
}