#include <iostream>
#include <fstream>
#include <vector>
#include <pthread.h>
#include <chrono>

using namespace std;

struct ThreadInfo {
    int threadId;
    int startRow;
    int startCol;
    bool isValid;
};

int N; 
vector<vector<int>> sudoku; 
vector<ThreadInfo> threadInfo; 
pthread_mutex_t mutex; 
ofstream outputFile; 

void* checkRow(void* arg) {
    ThreadInfo* info = (ThreadInfo*)arg;
    int row = info->startRow;
    int col = 0;
    int freq[N + 1] = {0}; 

    for (col = 0; col < N; col++) {
        int num = sudoku[row][col];
        if (num < 1 || num > N || freq[num] == 1) {
            info->isValid = false;
            return NULL;
        }
        freq[num] = 1;
    }

    info->isValid = true;
    return NULL;
}

void* checkColumn(void* arg) {
    ThreadInfo* info = (ThreadInfo*)arg;
    int row = 0;
    int col = info->startCol;
    int freq[N + 1] = {0};

    for (row = 0; row < N; row++) {
        int num = sudoku[row][col];
        if (num < 1 || num > N || freq[num] == 1) {
            info->isValid = false;
            return NULL;
        }
        freq[num] = 1;
    }

    info->isValid = true;
    return NULL;
}

void* checkGrid(void* arg) {
    ThreadInfo* info = (ThreadInfo*)arg;
    int startRow = info->startRow;
    int startCol = info->startCol;
    int freq[N + 1] = {0};

    for (int i = startRow; i < startRow + N / 3; i++) {
        for (int j = startCol; j < startCol + N / 3; j++) {
            int num = sudoku[i][j];
            if (num < 1 || num > N || freq[num] == 1) {
                info->isValid = false;
                return NULL;
            }
            freq[num] = 1;
        }
    }

    info->isValid = true;
    return NULL;
}

#include <pthread.h>

void writeOutput(int threadId, const string& message) {
    pthread_mutex_lock(&mutex);
    outputFile << "Thread " << threadId << " " << message << endl;
    pthread_mutex_unlock(&mutex);
}

bool validateSudoku(int K) {
    pthread_t threads[K];
    threadInfo.resize(K);
    bool isValid = true;

    for (int i = 0; i < K; i++) {
        threadInfo[i].threadId = i + 1;
        threadInfo[i].startRow = i * (N / K);
        threadInfo[i].startCol = 0;
        threadInfo[i].isValid = false;
        pthread_create(&threads[i], NULL, checkRow, (void*)&threadInfo[i]);
    }

    for (int i = 0; i < K; i++) {
        pthread_join(threads[i], NULL);
        if (!threadInfo[i].isValid) {
            writeOutput(threadInfo[i].threadId, "checks row " + to_string(threadInfo[i].startRow + 1) + " and is invalid.");
            isValid = false;
        } else {
            writeOutput(threadInfo[i].threadId, "checks row " + to_string(threadInfo[i].startRow + 1) + " and is valid.");
        }
    }

    for (int i = 0; i < K; i++) {
        threadInfo[i].startRow = 0;
        threadInfo[i].startCol = i * (N / K);
        threadInfo[i].isValid = false;
        pthread_create(&threads[i], NULL, checkColumn, (void*)&threadInfo[i]);
    }

    for (int i = 0; i < K; i++) {
        pthread_join(threads[i], NULL);
        if (!threadInfo[i].isValid) {
            writeOutput(threadInfo[i].threadId, "checks column " + to_string(threadInfo[i].startCol + 1) + " and is invalid.");
            isValid = false;
        } else {
            writeOutput(threadInfo[i].threadId, "checks column " + to_string(threadInfo[i].startCol + 1) + " and is valid.");
        }
    }

    int gridSize = N / 3;
    int gridCount = gridSize * gridSize;
    for (int i = 0; i < K; i++) {
        threadInfo[i].startRow = (i % gridSize) * gridSize;
        threadInfo[i].startCol = (i / gridSize) * gridSize;
        threadInfo[i].isValid = false;
        pthread_create(&threads[i], NULL, checkGrid, (void*)&threadInfo[i]);
    }

    for (int i = 0; i < K; i++) {
        pthread_join(threads[i], NULL);
        if (!threadInfo[i].isValid) {
            writeOutput(threadInfo[i].threadId, "checks grid " + to_string(i + 1) + " and is invalid.");
            isValid = false;
        } else {
            writeOutput(threadInfo[i].threadId, "checks grid " + to_string(i + 1) + " and is valid.");
        }
    }

    return isValid;
}

int main() {
    ifstream inputFile("input.txt");
    if (!inputFile) {
        cout << "Failed to open input file." << endl;
        return 1;
    }

    int K;
    inputFile >> K >> N;

    sudoku.resize(N, vector<int>(N));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            inputFile >> sudoku[i][j];
        }
    }

    outputFile.open("output.txt");
    if (!outputFile) {
        cout << "Failed to open output file." << endl;
        return 1;
    }

    auto startTime = chrono::high_resolution_clock::now();

    bool isValid = validateSudoku(K);

    auto endTime = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(endTime - startTime).count();

    if (isValid) {
        outputFile << "Sudoku is valid." << endl;
    } else {
        outputFile << "Sudoku is invalid." << endl;
    }

    outputFile << "The total time taken is " << duration << " microseconds." << endl;

    outputFile.close();

    return 0;
}