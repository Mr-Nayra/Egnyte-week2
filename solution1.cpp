#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Task1
{
public:
    vector<vector<int>> matrix;
    int x;
    int y;

    void loadFile(string &path)
    {
        vector<int> temp;
        std::ifstream inputFile(path);

        if (!inputFile.is_open())
        {
            std::cerr << "Error opening the file." << std::endl;
            return;
        }

        int number;

        if (inputFile >> number)
        {
            x = number;
        }

        if (inputFile >> number)
        {
            y = number;
        }

        for (int i = 0; i < x; i++)
        {
            for (int j = 0; j < y; j++)
            {
                if (inputFile >> number)
                {
                    temp.push_back(number);
                }
                else
                {
                    cout << "error reading file";
                }
            }
            matrix.push_back(temp);
            temp.clear();
        }


        // Close the file
        inputFile.close();
    }

    void saveSolution()
    {
        vector<bool> row(x, false);
        vector<bool> col(y, false);
        int i, j;

        for (i = 0; i < x; i++)
        {
            for (j = 0; j < y; j++)
            {   
                if (matrix[i][j] == 0)
                {
                    row[i] = true;
                    col[j] = true;
                }
            }
        }

        std::ofstream outputFile({"solution.txt"});

        // Check if the file is open
        if (!outputFile.is_open())
        {
            std::cerr << "Error opening the file for writing." << std::endl;
        }

        for (i = 0; i < x; i++)
        {
            for (j = 0; j < y; j++)
            {
                if (row[i] || col[j])
                {
                    outputFile << 0 << " ";
                }
                else
                {
                    outputFile << matrix[i][j] << " ";
                }
            }

            outputFile << endl;
        }

        // Close the file
        outputFile.close();
    }
};

int main()
{
    string path = "input.txt";

    Task1 task;
    task.loadFile(path);
    task.saveSolution();

    return 0;
}