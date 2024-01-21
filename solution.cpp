#include <iostream>
#include <typeinfo>
#include <vector>
#include <windows.h>

using namespace std;

class Task1 {
private:
  vector<vector<int>> m_matrix; // Matrix to store the input data
  int m_rowSize;                // Number of rows in the matrix
  int m_columnSize;             // Number of columns in the matrix

  // function to set matrix elements to zero according to the specific condition
  const void setToZero() 
  {
    int rowIndex = 0, colIndex = 0, tempMatrix = 1;

    for (rowIndex = 0; rowIndex < m_rowSize; rowIndex++) {
      if (m_matrix[rowIndex][0] == 0)
        tempMatrix = 0;
    }

    for (colIndex = 1; colIndex < m_columnSize; colIndex++) {
      if (m_matrix[0][colIndex] == 0)
        m_matrix[0][0] = 0;
    }

    for (rowIndex = 1; rowIndex < m_rowSize; rowIndex++) {
      for (colIndex = 1; colIndex < m_columnSize; colIndex++) {
        if (m_matrix[rowIndex][colIndex] == 0) {
          m_matrix[rowIndex][0] = 0;
          m_matrix[0][colIndex] = 0;
        }
      }
    }

    for (rowIndex = 1; rowIndex < m_rowSize; rowIndex++) {
      for (colIndex = 1; colIndex < m_columnSize; colIndex++) {
        if (m_matrix[rowIndex][0] == 0 || m_matrix[0][colIndex] == 0) {
          m_matrix[rowIndex][colIndex] = 0;
        }
      }
    }

    if (m_matrix[0][0] == 0) {
      for (rowIndex = 0; rowIndex < m_rowSize; rowIndex++) {
        m_matrix[0][rowIndex] = 0;
      }
    }

    if (tempMatrix == 0) {
      for (rowIndex = 0; rowIndex < m_rowSize; rowIndex++) {
        m_matrix[rowIndex][0] = 0;
      }
    }
  }

  // funtion to output the matrix in solution.txt file in the current directory
  const void printOutput() 
  {
    HANDLE hFile = CreateFileW(L"solution.txt", GENERIC_WRITE, 0, NULL,
                               CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    if (hFile == INVALID_HANDLE_VALUE) {
      cerr << "Error creating the file for writing." << endl;
      return;
    }

    const char newLine = '\n';
    const char space = ' ';

    for (int rowIndex = 0; rowIndex < m_rowSize; rowIndex++) {
      for (int colIndex = 0; colIndex < m_columnSize; colIndex++) {
        string temp = to_string(m_matrix[rowIndex][colIndex]);

        for (int i = 0; i < temp.length(); i++) {
          WriteFile(hFile, &temp[i], sizeof(char), NULL, NULL);
        }

        WriteFile(hFile, &space, sizeof(char), NULL, NULL);
      }

      WriteFile(hFile, &newLine, sizeof(char), NULL, NULL);
    }

    CloseHandle(hFile);
  }

// funtion to read a number from a given file
  const int readNumber(HANDLE &hFile, DWORD &bytesRead) 
  {
    char tempChar = ' ';
    int number = 0;

    while (true) {
      if (ReadFile(hFile, &tempChar, sizeof(char), &bytesRead, NULL) &&
          bytesRead == sizeof(char)) {
        if (tempChar == ' ' || tempChar == '\n' || tempChar == '\t' ||
            tempChar == '\r') {
          if (tempChar == '\r') {
            ReadFile(hFile, &tempChar, sizeof(char), &bytesRead, NULL);
          }
          break;
        } else {
          if (tempChar == '-') {
            number = -1;
          } else {
            number = number * 10 + (tempChar - '0');
          }
        }
      } else {
        CloseHandle(hFile);
        return number;
      }
    }

    return number;
  }

public:
  // constructor
  Task1() {
    m_rowSize = 0;
    m_columnSize = 0;
  }

  // Function to load data from a file
  const void loadFile(const wstring &path) 
  {
    vector<int> tempMatrix;
    HANDLE hFile = CreateFileW(
        path.c_str(),
        GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    if (hFile == INVALID_HANDLE_VALUE) {
      cerr << "Error opening the file." << endl;
      return;
    }

    // Read the number of rows from the file
    DWORD bytesRead;
    m_rowSize = readNumber(hFile, bytesRead);

    // Read the number of columns from the file
    m_columnSize = readNumber(hFile, bytesRead);

    // Read matrix data from the file
    for (int rowIndex = 0; rowIndex < m_rowSize; rowIndex++) {
      for (int colIndex = 0; colIndex < m_columnSize; colIndex++) {
        tempMatrix.push_back(readNumber(hFile, bytesRead));
      }
      m_matrix.push_back(tempMatrix);
      tempMatrix.clear();
    }

    CloseHandle(hFile);
  }

  // Function to save the solution to a file
  const void saveSolution() 
  {
    setToZero();
    printOutput();
  }
};

int main() 
{
  const wstring path =
      L"C:\\Users\\rawth\\OneDrive\\Desktop\\egnyte\\Egnyte-week2\\input.txt";

  Task1 task;
  task.loadFile(path);
  task.saveSolution();

  return 0;
}