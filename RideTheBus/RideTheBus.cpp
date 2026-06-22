#pragma once
#include <iostream>
#include <ctime>
#include "Deck.cpp"
#include "util.cpp"

using namespace std;

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
        // printf("Choice: %c \n", choice);
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
        turn++;
        if (turn == numPlayers)
        {
            turn = 0;
            stage++;
        }
        // cout << "Result: " << (int)result << endl;
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

    round_outcome handle_round_1(char choice)
    {
        // printf("Card: %c %c\n", hands[turn][0].getSuit(), hands[turn][0].getVal());
        char color;
        if (hands[turn][0].getSuit() == 'H' || hands[turn][0].getSuit() == 'D')
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
        // printf("First Card: %c %c ", hands[turn][0].getSuit(), hands[turn][0].getVal());
        // printf("Second Card: %c %c\n", hands[turn][1].getSuit(), hands[turn][1].getVal());

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
        // printf("First Card: %c %c ", hands[turn][0].getSuit(), hands[turn][0].getVal());
        // printf("Second Card: %c %c ", hands[turn][1].getSuit(), hands[turn][1].getVal());
        // printf("Second Card: %c %c\n", hands[turn][2].getSuit(), hands[turn][2].getVal());

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
        // printf("Card: %c %c\n", hands[turn][3].getSuit(), hands[turn][3].getVal());

        if (choice == std::tolower(hands[turn][3].getSuit()))
            return CORRECT;
        return WRONG;
    }
};