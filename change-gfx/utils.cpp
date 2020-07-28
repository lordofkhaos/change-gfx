#pragma once
#include <ostream>
#include <iostream>
#include <sstream>
#include <vector>
#include "global.h"
#include "utils.h"
#include "exit_codes.cpp"

void print_help() {
	std::cout << "Acceptable arguments include:" << std::endl
		<< "\t--help,-h             " << " :: " << "Shows this message." << std::endl
		<< "\t--path=<path>,p=<path>" << " :: " << "Pass the path of registry.txt." << std::endl
		<< "\t--true,-t             " << " :: " << "Always set the gfx value to true. NOTE: Exclusive" << std::endl << "\t                          " << "with --false." << std::endl
		<< "\t--false,-f            " << " :: " << "Always set the gfx value to false. NOTE: Exclusive" << std::endl << "\t                          " << "with --true." << std::endl
		<< "\t--toggle,-s           " << " :: " << "Swap whatever the current value of the gfx setting is." << std::endl
		<< "\t--quiet,-q            " << " :: " << "Print no messages to the console. NOTE: Implies " << std::endl << "\t                          " << "--toggle." << std::endl
		<< "\t--dry,-d              " << " :: " << "Performs a dry run, without making file changes." << std::endl;
}

std::vector<std::string> split(const std::string& str, const char delim) // StackOverflow
{
	std::vector<std::string> result;
	std::istringstream f(str);
	std::string s;
	while (std::getline(f, s, delim)) {
		result.push_back(s);
	}

	return result;
}

bool handle_startup_args(const int argc, char** argv, int& return_value) {
	// Assume toggle if no arguments are supplied
	if (argc == 0)
		toggle = true;
	else
		// Handle arguments
		for (int i = 1; i < argc; i++)
		{
			std::vector<std::string> arg = split(std::string(argv[i]), '=');

			if (arg[0] == "--help" || arg[0] == "-h") {
				help_msg = true;
			}
			else if (arg[0] == "--path" || arg[0] == "-p") {
				supplied_path = arg[1];
			}
			else if (arg[0] == "--true" || arg[0] == "-t") {
				force_true = true;
			}
			else if (arg[0] == "--false" || arg[0] == "-f") {
				force_false = true;
			}
			else if (arg[0] == "--toggle" || arg[0] == "-s") {
				toggle = true;
			}
			else if (arg[0] == "--quiet" || arg[0] == "-q") {
				quiet = true;
			}
			else if (arg[0] == "--dry" || arg[0] == "-d") {
				dry_run = true;
			}
		}

	// Check for bad combos
	if ((force_false && force_true) || quiet && dry_run) {
		print_help();
		return_value = user_error;
		return true;
	}

	if (!force_false && !force_true)
		toggle = true;
	return false;
}

void set_gfx_setting(std::vector<std::string>& file_contents) {
	if (!quiet) {
		std::cout << "Finding gfx setting..." << std::endl;
	}

	bool found = false;
	for (std::vector<std::string>::value_type& file_content : file_contents) {
		if (file_content.rfind("07gfxsets_hp::-%(|::", 0) == 0) {
			found = true;
			if (file_content.rfind("07gfxsets_hp::-%(|::0", 0) == 0) {
				if (toggle || force_true)
					file_content = "07gfxsets_hp::-%(|::1";
			}
			else if (file_content.rfind("07gfxsets_hp::-%(|::1", 0) == 0) {
				if (toggle || force_false)
					file_content = "07gfxsets_hp::-%(|::0";
			}
		}
	}

	if (!found) {
		file_contents.emplace_back("07gfxsets_hp::-%(|::1");
	}

	if (!quiet) {
		std::cout << "\tDone." << std::endl;
	}
}
