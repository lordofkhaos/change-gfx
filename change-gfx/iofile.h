#pragma once
#include <fstream>
#include <vector>

void find_file(std::fstream& my_file);
bool check_if_file_exists(const std::fstream& my_file, int& return_value);
bool read_file(std::fstream& my_file, std::vector<std::string>& file_contents, int& return_value);
void clear_file(std::fstream& my_file);
bool write_to_file(std::fstream& my_file, const std::vector<std::string>& file_contents, int& return_value);