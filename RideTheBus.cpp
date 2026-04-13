#pragma once
#include <iostream>
#include <ctime>
#include "Deck.cpp"

using namespace std;

enum round_outcome
{
    TBD,
    CORRECT,
    WRONG,
    DOUBLE
};

class RideTheBus
{
public:
    RideTheBus(int players)
    {
        this->numPlayers = players;

        deck.shuffle();

        hands = deck.deal_hands(numPlayers, 4);

        round_results = std::vector<std::vector<round_outcome>>(numPlayers, std::vector<round_outcome>(4));
        for (int i = 0; i < numPlayers; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                round_results[i][j] = TBD;
            }
        }

        stage = 0;
        turn = 0;
    }

    round_outcome submitGuess(char choice)
    {
        round_outcome result;
        switch (stage)
        {
        case 0:
            result = handle_round_1(choice);
            round_results[turn][stage] = result;
            break;
        case 1:
            result = handle_round_2(choice);
            round_results[turn][stage] = result;
            break;
        case 2:
            result = handle_round_3(choice);
            round_results[turn][stage] = result;
            break;
        case 3:
            result = handle_round_4(choice);
            round_results[turn][stage] = result;
            break;
        case 4:
            // game is over
            break;
        }
        turn ++;
        if (turn == numPlayers) {
            turn = 0;
            stage ++;
        }
        return result;
    }

    

    Card *getHand(int player)
    {
        if (player >= this->numPlayers)
        {
            cerr << "Out of bounds" << endl;
            return NULL;
        }
        return hands[player];
    }

    int getNumPlayers()
    {
        return numPlayers;
    }

    void setNumPlayers(int n)
    {
        numPlayers = n;
    }

    int getStage() { return stage; }

    int getTurn() { return turn; }

private:
    int numPlayers;

    int stage;
    int turn;

    std::vector<std::vector<round_outcome>> round_results;

    Deck deck;
    Card **hands;

    int map_hand_value(char val)
    {
        if (val == 'A')
            return 14;
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

    round_outcome handle_round_1(char choice)
    {
        char color;
        if (hands[turn][0].getSuit() == 'H' || hands[turn][0].getSuit() == 'D')
        {
            color = 'r';
        }
        else
        {
            color = 'd';
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
        int prev = map_hand_value(hands[turn][0].getVal());
        int curr = map_hand_value(hands[turn][1].getVal());
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
        int first = map_hand_value(hands[turn][0].getVal());
        int second = map_hand_value(hands[turn][1].getVal());
        int third = map_hand_value(hands[turn][2].getVal());
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
        if (choice == std::tolower(hands[turn][3].getSuit()))
            return CORRECT;
        return WRONG;
    }
};