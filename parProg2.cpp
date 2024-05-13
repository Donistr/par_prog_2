#include <iostream>
#include <chrono>
#include <string>
#include <stdlib.h>
#include <direct.h>
#include <array>
#include <omp.h>
#include "Matrix.h"
#include "FileWriter.h"

static const int MULTIPLYING_COUNT_FOR_MATRIX_SIZE = 100;

void checkResult(const std::string& pythonFilePath, const std::string& matricies1FilePath, const std::string& matricies2FilePath, const std::string& matriciesResFilePath) {
    system(std::string("py " + pythonFilePath + " " + matricies1FilePath + " " + matricies2FilePath + " " + matriciesResFilePath).c_str());
}

int main() {
    srand(time(0));
    _mkdir("results");

    std::array<size_t, 6> matriciesSizeArr = { 10, 50, 100, 250, 500, 1000 };
    FileWriter fileWriterAvgTime("results\\avg_times.json");

    for (size_t matrixSize : matriciesSizeArr) {
        std::cout << std::to_string(matrixSize) << "x" << std::to_string(matrixSize) << std::endl;

        std::string path = "results\\" + std::to_string(matrixSize) + "x" + std::to_string(matrixSize);
        _mkdir(path.c_str());

        std::string matricies1Path = path + "\\matricies_1.json";
        std::string matricies2Path = path + "\\matricies_2.json";
        std::string matriciesResPath = path + "\\matricies_res.json";
        std::string timesPath = path + "\\times.json";

        FileWriter fileWriterMatrix1(matricies1Path);
        FileWriter fileWriterMatrix2(matricies2Path);
        FileWriter fileWriterMatrixRes(matriciesResPath);
        FileWriter fileWriterTimes(timesPath);

        double avgTime = 0;
        for (int i = 0; i < MULTIPLYING_COUNT_FOR_MATRIX_SIZE; ++i) {
            std::cout << i + 1 << "/" << MULTIPLYING_COUNT_FOR_MATRIX_SIZE << std::endl;

            Matrix matrix1 = Matrix(matrixSize, matrixSize);
            matrix1.fillMatrixRandomNumbers(10);
            Matrix matrix2 = Matrix(matrixSize, matrixSize);
            matrix2.fillMatrixRandomNumbers(10);

            double start = omp_get_wtime();
            Matrix res = matrix1.multiply(matrix2);
            double time = omp_get_wtime() - start;

            avgTime += time;

            fileWriterMatrix1.writeMatrixToFile(matrix1);
            fileWriterMatrix2.writeMatrixToFile(matrix2);
            fileWriterMatrixRes.writeMatrixToFile(res);
            fileWriterTimes.writeTimeToFile(time);
        }
        avgTime /= MULTIPLYING_COUNT_FOR_MATRIX_SIZE;

        fileWriterAvgTime.writeTimeToFile(avgTime);
    }

    for (size_t matrixSize : matriciesSizeArr) {
        std::cout << "check: " + std::to_string(matrixSize) + "x" + std::to_string(matrixSize) << std::endl;
        std::string path = "results\\" + std::to_string(matrixSize) + "x" + std::to_string(matrixSize);
        std::string matricies1Path = path + "\\matricies_1.json";
        std::string matricies2Path = path + "\\matricies_2.json";
        std::string matriciesResPath = path + "\\matricies_res.json";

        checkResult("validation\\matrixValidator.py", matricies1Path, matricies2Path, matriciesResPath);
    }

    return 0;
}