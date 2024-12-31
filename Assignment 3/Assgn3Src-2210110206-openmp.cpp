#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <omp.h>

bool isValidRow(const std::vector<std::vector<int>>& sudoku, int row) {
    std::vector<bool> used(sudoku.size() + 1, false);
    for (int col = 0; col < sudoku.size(); col++) {
        int num = sudoku[row][col];
        if (num != 0) {
            if (used[num]) {
                return false;
            }
            used[num] = true;
        }
    }
    return true;
}

bool isValidColumn(const std::vector<std::vector<int>>& sudoku, int col) {
    std::vector<bool> used(sudoku.size() + 1, false);
    for (int row = 0; row < sudoku.size(); row++) {
        int num = sudoku[row][col];
        if (num != 0) {
            if (used[num]) {
                return false;
            }
            used[num] = true;
        }
    }
    return true;
}

bool isValidGrid(const std::vector<std::vector<int>>& sudoku, int startRow, int startCol) {
    std::vector<bool> used(sudoku.size() + 1, false);
    for (int row = startRow; row < startRow + 3; row++) {
        for (int col = startCol; col < startCol + 3; col++) {
            int num = sudoku[row][col];
            if (num != 0) {
                if (used[num]) {
                    return false;
                }
                used[num] = true;
            }
        }
    }
    return true;
}

bool isValidSudoku(const std::vector<std::vector<int>>& sudoku) {
    #pragma omp parallel for
    for (int i = 0; i < sudoku.size(); i++) {
        if (!isValidRow(sudoku, i)) {
            std::cout << "Thread " << omp_get_thread_num() << " checks row " << i + 1 << " and is invalid." << std::endl;
        } else {
            std::cout << "Thread " << omp_get_thread_num() << " checks row " << i + 1 << " and is valid." << std::endl;
        }
    }

    #pragma omp parallel for
    for (int i = 0; i < sudoku.size(); i++) {
        if (!isValidColumn(sudoku, i)) {
            std::cout << "Thread " << omp_get_thread_num() << " checks column " << i + 1 << " and is invalid." << std::endl;
        } else {
            std::cout << "Thread " << omp_get_thread_num() << " checks column " << i + 1 << " and is valid." << std::endl;
        }
    }

    #pragma omp parallel for
    for (int i = 0; i < sudoku.size(); i += 3) {
        for (int j = 0; j < sudoku.size(); j += 3) {
            if (!isValidGrid(sudoku, i, j)) {
                std::cout << "Thread " << omp_get_thread_num() << " checks grid " << (i / 3) * 3 + (j / 3) + 1 << " and is invalid." << std::endl;
            } else {
                std::cout << "Thread " << omp_get_thread_num() << " checks grid " << (i / 3) * 3 + (j / 3) + 1 << " and is valid." << std::endl;
            }
        }
    }

    return true;
}

int main() {
    int K, N;
    std::ifstream inputFile("input.txt");
    inputFile >> K >> N;

    std::vector<std::vector<int>> sudoku(N, std::vector<int>(N));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            inputFile >> sudoku[i][j];
        }
    }

    auto start = std::chrono::high_resolution_clock::now();
    isValidSudoku(sudoku);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::micro> duration = end - start;

    std::ofstream outputFile("output.txt");
    outputFile << "The total time taken is " << duration.count() << " microseconds." << std::endl;

    return 0;
}