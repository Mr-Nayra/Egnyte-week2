

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Task1
{
private:
    vector<vector<int>> matrix;
    int x;
    int y;

    void setToZero()
    {
        int i, j, temp = 1;

        for (i = 0; i < x; i++)
        {
            if (matrix[i][0] == 0)
                temp = 0;
        }

        for (j = 1; j < y; j++)
        {
            if (matrix[0][j] == 0)
                matrix[0][0] = 0;
        }

        for (i = 1; i < x; i++)
        {
            for (j = 1; j < y; j++)
            {
                if (matrix[i][j] == 0)
                {
                    matrix[i][0] = 0;
                    matrix[0][j] = 0;
                }
            }
        }

        for (i = 1; i < x; i++)
        {
            for (j = 1; j < y; j++)
            {
                if (matrix[i][0] == 0 || matrix[0][j] == 0)
                {
                    matrix[i][j] = 0;
                }
            }
        }

        if (matrix[0][0] == 0)
        {
            for (i = 0; i < x; i++)
            {
                matrix[0][i] = 0;
            }
        }

        if (temp == 0)
        {
            for (i = 0; i < x; i++)
            {
                matrix[i][0] = 0;
            }
        }
    }

public:
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
        setToZero();

        std::ofstream outputFile({"solution.txt"});

        // Check if the file is open
        if (!outputFile.is_open())
        {
            std::cerr << "Error opening the file for writing." << std::endl;
        }

        for (int i = 0; i < x; i++)
        {
            for (int j = 0; j < y; j++)
            {
                outputFile << matrix[i][j] << " ";
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