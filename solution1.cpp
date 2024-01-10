// Space Complexity: O(1)
// Time Complexity: O(nXm)

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Task1
{
private:
    vector<vector<int>> matrix; // Matrix to store the input data
    int x;                      // Number of rows in the matrix
    int y;                      // Number of columns in the matrix

public:
    // Function to load data from a file
    void loadFile(string &path)
    {
        vector<int> temp;
        std::ifstream inputFile(path);

        // Check if the file is open
        if (!inputFile.is_open())
        {
            std::cerr << "Error opening the file." << std::endl;
            return;
        }

        int number;

        // Read the number of rows from the file
        if (inputFile >> number)
        {
            x = number;
        }

        // Read the number of columns from the file
        if (inputFile >> number)
        {
            y = number;
        }

        // Read matrix data from the file
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

    // Function to save the solution to a files
    void saveSolution()
    {
        vector<bool> row(x, false);
        vector<bool> col(y, false);
        int i, j;

        // Mark rows and columns containing 0 in the matrix
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

        // Write the solution matrix to the file
        for (i = 0; i < x; i++)
        {
            for (j = 0; j < y; j++)
            {
                if (row[i] || col[j])
                {
                    outputFile << 0 << " "; // Write 0 for marked rows and columns
                }
                else
                {
                    outputFile << matrix[i][j] << " "; // Write the original value
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