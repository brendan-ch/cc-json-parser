#include "parse.hpp"
#include <iostream>

// key constraint: we're not actually building a tree, just validating
// the json string

bool is_number_str(const string &s)
{
    // https://stackoverflow.com/questions/29169153/how-do-i-verify-a-string-is-valid-double-even-if-it-has-a-point-in-it
    char* end = nullptr;
    double val = strtod(s.c_str(), &end);
    return end != s.c_str() && *end == '\0' && val != HUGE_VAL;
}

int find_first_non_whitespace_char_index_inclusive(const string &str)
{
    int end = str.length();
    int index = 0;

    char index_char = str.at(index);
    while (index < end - 1 && (index_char == ' ' || index_char == '\n'))
    {
        index++;
        index_char = str.at(index);
    }

    return index;
}

int find_last_non_whitespace_char_index_exclusive(const string &str)
{
    int index = str.length();
    char end_char = str.at(index - 1);
    while (0 < index - 1 && (end_char == ' ' || end_char == '\n'))
    {
        index--;
        end_char = str.at(index - 1);
    }

    return index;
}

string trim(const string &json)
{
    if (json.length() == 0)
        return "";

    int start = find_first_non_whitespace_char_index_inclusive(json);
    int end = find_last_non_whitespace_char_index_exclusive(json);

    auto substr = json.substr(start, end - start);
    return substr;
}

int parse_relation(const string &relation)
{
    // exclusive to keys: must be a string

    string trimmed_relation = trim(relation);
    if (trimmed_relation.length() == 0)
    {
        return 1;
    }

    if (trimmed_relation.at(0) != '"')
    {
        return 1;
    }

    int end_key = trimmed_relation.find('"', 1);
    if (end_key == string::npos)
    {
        return 1;
    }

    int delimiter = trimmed_relation.find(':', end_key);
    if (delimiter == string::npos)
    {
        return 1;
    }

    string value = trimmed_relation.substr(delimiter + 1);
    return parse(value);
}

int parse_object(const string &json)
{
    string unparsed = json.substr(1, json.length() - 2);

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
    int result = parse_relation(unparsed);
    if (result != 0)
    {
        return result;
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
    else if (start_char == '"' && end_char == '"')
    {
        return 0;
    }
    else if (substr == "true" || substr == "false" || substr == "null")
    {
        return 0;
    }
    else if (is_number_str(substr))
    {
        return 0;
    }

    // also include cases for keyword literals (true/false/null) and numbers (ints + floats)

    // cout << start << " " << end << endl;

    return 1;
}
