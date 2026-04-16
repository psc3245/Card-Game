#pragma once
#include <iostream>
#include <ctime>
#include "Deck.cpp"
#include "util.cpp"

class RideTheBusAlone
{

public:
    RideTheBusAlone()
    {
        reset();
    }
    round_outcome next_round(char choice)
    {
        if (stage > 3) return TBD; // ?
        switch (stage)
        {
        case 0:
        {
            round_outcome result = handle_round_1(choice);
            if (result == CORRECT)
            {
                stage++;
            }
            else
            {
                stage = 0;
                reset();
            }
            return result;
        }
        case 1:
        {
            round_outcome result = handle_round_2(choice);
            if (result == CORRECT)
            {
                stage++;
            }
            else
            {
                stage = 0;
                reset();
            }
            return result;
        }
        case 2:
        {
            round_outcome result = handle_round_3(choice);
            if (result == CORRECT)
            {
                stage++;
            }
            else
            {
                stage = 0;
                reset();
            }
            return result;
        }
        case 3:
        {
            round_outcome result = handle_round_4(choice);
            if (result == CORRECT)
            {
                escaped = true;
            }
            else
            {
                stage = 0;
                reset();
            }
            return result;
        }
        }
    }

    void reset()
    {
        deck = Deck();
        deck.shuffle();
        first = deck.draw();
        second = deck.draw();
        third = deck.draw();
        fourth = deck.draw();
    }

    int getStage() { return stage; }

    bool getEscaped() { return escaped; }

private:
    Deck deck;
    int stage = 0;
    bool escaped = false;
    Card first;
    Card second;
    Card third;
    Card fourth;

    round_outcome handle_round_1(char choice)
    {
        char color;
        if (first.getSuit() == 'H' || first.getSuit() == 'D')
        {
            color = 'r';
        }
        else
        {
            color = 'b';
        }
        if (color == choice)
        {
            return CORRECT;
        }
        else
        {
            return WRONG;
        }
    }

    round_outcome handle_round_2(char choice)
    {
        int prev = map_hand_value(first.getVal());
        int curr = map_hand_value(second.getVal());
        if (curr == prev)
        {
            return DOUBLE;
        }
        if ((choice == 'h' && curr > prev) || (choice == 'l' && curr < prev))
        {
            return CORRECT;
        }
        return WRONG;
    }

    round_outcome handle_round_3(char choice)
    {
        int first = map_hand_value(this->first.getVal());
        int second = map_hand_value(this->second.getVal());
        int third = map_hand_value(this->third.getVal());
        if (third == first || third == second)
        {
            return DOUBLE;
        }
        if (choice == 'i')
        {
            if ((first > third && second < third) || (first < third && second > third))
                return CORRECT;
        }
        if (choice == 'o')
        {
            if ((first < third && second < third) || (first > third && second > third))
                return CORRECT;
        }
        return WRONG;
    }

    round_outcome handle_round_4(char choice)
    {
        if (choice == std::tolower(fourth.getSuit()))
            return CORRECT;
        return WRONG;
    }
};