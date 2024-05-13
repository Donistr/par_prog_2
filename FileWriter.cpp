#include <string>
#include "FileWriter.h"

FileWriter::FileWriter(const std::string& path) {
    _writer = std::ofstream(path);
    _writer << "[";
}

FileWriter::~FileWriter() {
    _writer.seekp(-1, std::ios_base::end);
    _writer << "]";
    _writer.close();
}

void FileWriter::writeMatrixToFile(const Matrix& matrix) {
    size_t rows = matrix.getRows();
    size_t columns = matrix.getColumns();

    _writer << "{" << "\"rows\":" << rows << "," << "\"columns\":" << columns << "," << "\"matrix\":[";

    for (int i = 0; i < rows; ++i) {
        _writer << "[";

        for (int j = 0; j < columns; ++j) {
            _writer << matrix.get(i, j);

            if (j != columns - 1) {
                _writer << ",";
            }
        }

        _writer << "]";
        if (i != rows - 1) {
            _writer << ",";
        }
    }
    _writer << "]},";
}

void FileWriter::writeTimeToFile(const double& time) {
    _writer << time << ",";
}
