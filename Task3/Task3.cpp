#include <fstream>
#include <iostream>
#include <string>

using namespace std;


void compressFileRLE(const string &sourceFile, const string &compressedFile) {
    ifstream inputFile(sourceFile);  
    ofstream outputFile(compressedFile);  

    if (!inputFile.is_open() || !outputFile.is_open()) {
        cerr << "Failed to open file(s)!" << endl;  
        return;
    }

    char currentChar, prevChar;
    int charCount = 1;  

    inputFile.get(prevChar);  
    while (inputFile.get(currentChar)) {  
        if (currentChar == prevChar) {
            charCount++; 
        } else {
            outputFile.put(prevChar);  
            outputFile << charCount;  
            prevChar = currentChar;  
            charCount = 1;
        }
    }

   
    outputFile.put(prevChar);
    outputFile << charCount;

   
    inputFile.close();
    outputFile.close();
}


void decompressFileRLE(const string &compressedFile, const string &outputFileName) {
    ifstream inputFile(compressedFile);  
    ofstream outputFileStream(outputFileName);  

    if (!inputFile.is_open() || !outputFileStream.is_open()) {
        cerr << "Failed to open file(s)!" << endl;
        return;
    }

    char currentChar;
    int charCount;

   
    while (inputFile.get(currentChar) && inputFile >> charCount) {
        for (int i = 0; i < charCount; ++i) {
            outputFileStream.put(currentChar);
        }
    }

  
    inputFile.close();
    outputFileStream.close();
}

int main() {
    string sourceFile = "source.txt";  
    string compressedFile = "compressed.rle";  
    string outputFile = "output.txt";  

    compressFileRLE(sourceFile, compressedFile);
    cout << "File successfully compressed." << endl;

    decompressFileRLE(compressedFile, outputFile);
    cout << "File successfully decompressed." << endl;

    return 0;
}
