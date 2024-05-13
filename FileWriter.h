#include <fstream>
#include "Matrix.h"
#pragma once

class FileWriter {
private:
	std::ofstream _writer;
	bool _firstWrite = true;
public:
	FileWriter(const std::string& path);

	~FileWriter();

	void writeMatrixToFile(const Matrix& matrix);

	void writeTimeToFile(const double& time);
};