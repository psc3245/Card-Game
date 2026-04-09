#pragma once
#include <iostream>
#include <ctime>
#include "Deck.cpp"

using namespace std;

enum round_outcome
{
    CORRECT,
    WRONG,
    DOUBLE
};

class RideTheBus
{
public:
    int stage;

    round_outcome handle_round_1(char choice, int player)
    {
        stage++;
        char color;
        if (hands[player][0].getSuit() == 'H' || hands[player][0].getSuit() == 'D')
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

    round_outcome handle_round_2(char choice, int player)
    {
        stage++;
        int prev = map_hand_value(hands[player][0].getVal());
        int curr = map_hand_value(hands[player][1].getVal());
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

    round_outcome handle_round_3(char choice, int player)
    {
        stage++;
        int first = map_hand_value(hands[player][0].getVal());
        int second = map_hand_value(hands[player][1].getVal());
        int third = map_hand_value(hands[player][2].getVal());
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

    round_outcome handle_round_4(char choice, int player)
    {
        stage++;
        if (choice == std::tolower(hands[player][3].getSuit()))
            return CORRECT;
        return WRONG;
    }

    RideTheBus(int players)
    {
        this->numPlayers = players;
        this->players_remaining = players;
        hands = new Card *[players];

        for (int p = 0; p < players; p++)
        {
            hands[p] = new Card[4];
        }

        stage = 0;

        deck.shuffle();

        hands = deck.deal_hands(numPlayers, 4);
    }

    Card *getHand(int player)
    {
        if (player > this->numPlayers)
        {
            cerr << "Out of bounds" << endl;
            return NULL;
        }
        return hands[player - 1];
    }

    int getNumPlayers() {
        return numPlayers;
    }

    void setNumPlayers(int n) {
        numPlayers = n;
    }

private:
    int numPlayers;
    int players_remaining;

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
};