//#define DEBUG

#include <fstream>
#include <vector>
#include "iofile.h"
#include "global.h"
#include "utils.h"
#include "exit_codes.cpp"


std::string supplied_path;
bool help_msg = false;
bool force_true = false;
bool force_false = false;
bool toggle = false;
bool quiet = false;
bool dry_run = false;

/// <summary>
/// Entry point of the application.
/// </summary>
/// <param name="argc">The number of arguments supplied to the program.</param>
/// <param name="argv">The arguments applied to the program.</param>
/// <returns></returns>
int main(const int argc, char* argv[])
{
	int return_value;
	if (handle_startup_args(argc, argv, return_value)) return return_value;

	if (help_msg) {
		print_help();
		return good;
	}

	// Find file
	std::fstream my_file;
	find_file(my_file);

	// Check if file exists
	if (check_if_file_exists(my_file, return_value)) return return_value;

	// Read file
	std::vector<std::string> file_contents;
	if (read_file(my_file, file_contents, return_value)) return return_value;

	// Find and set gfx setting
	set_gfx_setting(file_contents);

	// Clear out old file
	clear_file(my_file);
	
	// Write new data to file
	if (write_to_file(my_file, file_contents, return_value)) return return_value;

	return good;
}
