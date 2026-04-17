#include "parse.hpp"
#include <iostream>

int parse(const string &json)
{
    int start = 0;
    int end = json.length();
    cout << start << " " << end << endl;

    if (start >= end)
        return 1;

    char start_char = json.at(start);
    while (start < end - 1 && (start_char == ' ' || start_char == '\n'))
    {
        start++;
        start_char = json.at(start);
    }

    char end_char = json.at(end - 1);
    while (start < end - 1 && (end_char == ' ' || end_char == '\n'))
    {
        end--;
        end_char = json.at(end - 1);
    }

    if (start_char == '{')
    {
        // parse object
    }
    else if (start_char == '"')
    {
        // save as string literal
    }
    // also include cases for keyword literals (true/false/null) and numbers (ints + floats)

    // cout << start << " " << end << endl;

    return 0;
}
