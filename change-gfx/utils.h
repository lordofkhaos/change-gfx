#pragma once
#include <string>
#include <vector>

std::vector<std::string> split(const std::string& str, const char delim);
void print_help();
bool handle_startup_args(const int argc, char** argv, int& return_value);
void set_gfx_setting(std::vector<std::string>& file_contents);
