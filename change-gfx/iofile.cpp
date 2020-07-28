#include <iostream>
#include "iofile.h"
#include "global.h"
#include "exit_codes.cpp"

void find_file(std::fstream& my_file) {
	if (!quiet) {
		std::cout << "Finding file..." << std::endl;
	}

	if (supplied_path.empty()) {
		my_file = std::fstream("./registry.txt");
	}
	else {
		my_file = std::fstream(supplied_path);
	}
}

bool check_if_file_exists(const std::fstream& my_file, int& return_value) {
	if (!quiet) {
		std::cout << "Checking if file exists..." << std::endl;
	}

	if (my_file.good()) {
		if (!quiet)
			std::cout << "\tDone." << std::endl;
	}
	else {
		if (!quiet) {
			std::cout << "ERROR: Cannot find file specified." << std::endl;
		}

		return_value = file_error;
		return true;
	}
	return false;
}

bool read_file(std::fstream& my_file, std::vector<std::string>& file_contents, int& return_value) {
	if (!quiet) {
		std::cout << "Reading file..." << std::endl;
	}

	std::string line;
	if (my_file.is_open()) {
		while (std::getline(my_file, line)) {
			file_contents.push_back(line);
		}

		my_file.close();
	}
	else {
		if (!quiet) {
			std::cout << "ERROR: File lock encountered." << std::endl;
		}

		return_value = file_error;
		return true;
	}

	if (!quiet) {
		std::cout << "\tDone." << std::endl;
	}
	return false;
}

void clear_file(std::fstream& my_file) {
	if (!dry_run) {
		if (!quiet) {
			std::cout << "Clearing old data from file..." << std::endl;
		}

		if (supplied_path.empty()) {
			my_file = std::fstream("./registry.txt", std::fstream::out | std::fstream::trunc);
		}
		else {
			my_file = std::fstream(supplied_path, std::fstream::out | std::fstream::trunc);
		}

		my_file.close();

		if (!quiet) {
			std::cout << "\tDone." << std::endl;
		}
	}
}

bool write_to_file(std::fstream& my_file, const std::vector<std::string>& file_contents, int& return_value) {
	if (!quiet) {
		std::cout << "Writing new setting to file..." << std::endl;
	}

	if (supplied_path.empty()) {
		my_file = std::fstream("./registry.txt");
	}
	else {
		my_file = std::fstream(supplied_path);
	}

	for (const std::string& file_content : file_contents) {
		if (my_file.is_open()) {
			if (!quiet) {
				std::cout << "\t->" << file_content << std::endl;
			}

			if (!dry_run)
				my_file << file_content << std::endl;
		}
		else {
			return_value = file_error;
			return true;
		}
	}

	if (!quiet) {
		std::cout << "\tDone." << std::endl;
	}
	return false;
}
