#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <SFML/Graphics.hpp>

enum round_outcome
{
    TBD,
    CORRECT,
    WRONG,
    DOUBLE
};

int map_hand_value(char val)
{
    if (val == 'A')
        return 1;
    if (val == 'K')
        return 13;
    if (val == 'Q')
        return 12;
    if (val == 'J')
        return 11;
    if (val == 'T')
        return 10;
    return val - '0';
}

std::string wrapText(std::string text, float maxWidth, sf::Text &sample)
{
    std::stringstream ss(text);
    std::string word;
    std::vector<std::string> words;

    while (ss >> word)
    {
        words.push_back(word);
    }

    std::string final = "";
    std::string current_line = "";
    for (int i = 0; i < words.size(); i++)
    {
        std::string newline = current_line + words[i] + " ";
        sample.setString(newline);
        if (sample.getLocalBounds().size.x >= maxWidth)
        {
            final += current_line + "\n";
            current_line = words[i] + " ";
        }
        else
            current_line += words[i] + " ";
    }
    if (current_line != "")
    {
        final += current_line + "\n";
    }
    return final;
}