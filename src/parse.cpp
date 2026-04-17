#include "parse.hpp"
#include <iostream>

// key constraint: we're not actually building a tree, just validating
// the json string

string trim(const string &json)
{
    int start = 0;
    int end = json.length();

    if (start >= end)
        return "";

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

    auto substr = json.substr(start, end - start);
    return substr;
}

int parse_relation(const string &relation)
{
    // parses a single relation (e.g. "key": "value")
    return 0;
}

int parse_object(const string &json)
{
    auto relations = json.substr(1, json.length() - 2);

    string unparsed = relations.substr();

    auto delimiter_index = unparsed.find(',');
    while (delimiter_index != string::npos)
    {
        // parse before delimiter, then update substring to exclude parsed
        int result = parse_relation(unparsed.substr(0, delimiter_index));
        if (result != 0)
        {
            return result;
        }

        unparsed = unparsed.substr(delimiter_index + 1);
        delimiter_index = unparsed.find(',');
    }

    return 0;
}

int parse(const string &json)
{
    auto substr = trim(json);
    if (substr.length() == 0)
        return 1;

    char start_char = substr.at(0);
    char end_char = substr.at(substr.length() - 1);

    if (start_char == '{' && end_char == '}')
    {
        return parse_object(substr);
    }
    else if (start_char == '"' && end_char == '}')
    {
        return 0;
    }

    // also include cases for keyword literals (true/false/null) and numbers (ints + floats)

    // cout << start << " " << end << endl;

    return 1;
}
