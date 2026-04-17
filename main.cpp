#include <fstream>
#include <filesystem>
#include <iostream>
#include <string>
#include "src/parse.hpp"
#include "src/read_file.hpp"

using namespace std;
namespace fs = std::filesystem;

void run_tests(string directory)
{
    vector<tuple<string, string, int>> test_cases = {};

    std::string path = string("./tests/") + directory;

    // https://stackoverflow.com/questions/612097/how-can-i-get-the-list-of-files-in-a-directory-using-c-or-c
    for (const auto &entry : fs::directory_iterator(path))
    {
        auto path = entry.path();
        ifstream input(path);
        string contents = read_file(path.string());

        if (path.string().find("invalid") != string::npos)
        {
            test_cases.push_back({path.filename(), contents, 1});
        }
        else
        {
            test_cases.push_back({path.filename(), contents, 0});
        }
    }

    for (int i = 0; i < test_cases.size(); i++)
    {
        string json = get<1>(test_cases[i]);
        int expected_code = get<2>(test_cases[i]);

        int result = parse(json);
        if (result == expected_code)
        {
            cout << "Test case passed for " << get<0>(test_cases[i]) << ": expected " << expected_code << ", got " << result << endl;
        }
        else
        {
            cout << "Test case failed for " << get<0>(test_cases[i]) << ": expected " << expected_code << ", got " << result << endl;
        }
    }
}

void print_usage_guide()
{
    cout << "Usage: ./main tests <name of directory under tests>\n       ./main <filename>" << endl;
}

int main(int count, char **args)
{
    if (count < 2)
    {
        print_usage_guide();
        return 1;
    }

    if (string(args[1]) == "tests")
    {
        if (count == 3)
        {
            run_tests(string(args[2]));
            return 0;
        }
        else
        {
            print_usage_guide();
            return 1;
        }
    }
    string contents = read_file(args[1]);
    return parse(contents);
}
