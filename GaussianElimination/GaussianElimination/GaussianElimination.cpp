#include <omp.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <list>
#include "csv.hpp"

using namespace std;
using namespace csv;

auto const DELIMITER = ';';

template <typename T>
vector<vector<T>> parse_csv_to_matrix(string path, char delimiter) {
	CSVFormat format;
	format.delimiter(delimiter).variable_columns(true);
	CSVReader reader(path, format);
	vector<vector<T>> matrix = {};

	for (CSVRow& row : reader) {
		vector<T> cells = {};
		for (CSVField& field : row) {
			cells.push_back(field.get<T>());
		}
		matrix.push_back(cells);
	}

	return matrix;
}

template <typename T>
void save_matrix_to_csv(string path, vector<vector<T>> matrix) {
	ofstream ofs(path);
	auto writer = make_csv_writer(ofs);

	for (vector<T> const& row : matrix) {
		vector<string> string_vector = {};
		transform(begin(row), end(row), back_inserter(string_vector), [](T d) { return to_string(d); });
		writer << string_vector;
	}
}


int main()
{
	auto matrix = parse_csv_to_matrix<double>("C.csv", DELIMITER);
	save_matrix_to_csv<double>("test.csv", matrix);
}