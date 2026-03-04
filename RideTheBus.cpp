#include <iostream>
#include <ctime>
#include "Deck.cpp"

using namespace std;

class RideTheBus
{
public:
    void run_game()
    {
        cout << "Welcome to ride the bus." << endl;

        while (play_again)
        {

            for (int stage = 0; stage < 4; stage++)
            {
                game_in_progress = true;
                cout << "Round " << stage + 1 << ": " << endl;
                cout << "Current state of the hands: " << endl;
                print_hands_hiding_some(hands, numPlayers, 4, stage);
                cout << endl;
                for (int player = 0; player < numPlayers; player++)
                {
                    cout << "Player " << player + 1 << "'s turn." << endl;
                    if (stage == 0)
                    {
                        handle_round_1(hands, player);
                    }
                    if (stage == 1)
                    {
                        handle_round_2(hands, player);
                    }
                    if (stage == 2)
                    {
                        handle_round_3(hands, player);
                    }
                    if (stage == 3)
                    {
                        handle_round_4(hands, player);
                    }
                }
            }

            cout << "Type n to stop playing. Type anything else to keep playing. ";
            string yn;
            cin >> yn;
            if (yn == "n")
            {
                play_again = false;;
            }
        }
    }

    RideTheBus(int players)
    {
        this->numPlayers = players;
        hands = new Card *[players];
        player_round_success = new bool *[players];
        for (int p = 0; p < players; p++)
        {
            hands[p] = new Card[4];
            player_round_success[p] = new bool[4];
        }

        deck.shuffle();
        game_in_progress = false;
        play_again = true;
    }

private:
    int numPlayers;

    Deck deck;
    Card **hands;

    bool **player_round_success;

    bool game_in_progress;
    bool play_again;
    int stage;

    void print_hands(Card **hands, int players, int cards)
    {
        for (int i = 0; i < players; i++)
        {
            cout << "Hand " << i + 1 << ": ";
            for (int j = 0; j < cards; j++)
            {
                cout << hands[i][j].getVal() << hands[i][j].getSuit();
            }
            cout << endl;
        }
    }

    void print_hands_hiding_some(Card **hands, int players, int cards, int show_count)
    {
        for (int i = 0; i < players; i++)
        {
            cout << "Hand " << i + 1 << ": ";
            for (int j = 0; j < cards; j++)
            {
                if (j < show_count)
                    cout << hands[i][j].getVal() << hands[i][j].getSuit() << " ";
                else
                    cout << " X ";
            }
            cout << endl;
        }
    }

    string format_card(Card card)
    {
        string suit;
        if (card.getSuit() == 'H')
            suit = "Hearts";
        if (card.getSuit() == 'D')
            suit = "Diamonds";
        if (card.getSuit() == 'S')
            suit = "Spades";
        if (card.getSuit() == 'C')
            suit = "Clubs";

        string strval(1, card.getVal());
        string result = strval + " of " + suit;
        return result;
    }

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

    bool handle_round_1(Card **hands, int player)
    {
        string choice;
        bool flag = true;
        while (flag)
        {
            cout << "Red or black? (r/b)";
            cin >> choice;
            if (choice != "r" && choice != "b")
                cout << "bad answer, try again!" << endl;
            else
                flag = false;
        }
        string color;
        if (hands[player][0].getSuit() == 'H' || hands[player][0].getSuit() == 'D')
        {
            color = "r";
        }
        else
        {
            color = "d";
        }
        if (color == choice)
        {
            cout << "Correct!" << endl;
            cout << "The card was: " << format_card(hands[player][0]) << endl;
            return true;
        }
        else
        {
            cout << "WRONG! Take a drink" << endl;
            cout << "The card was: " << format_card(hands[player][0]) << endl;
            return false;
        }
    }

    bool handle_round_2(Card **hands, int player)
    {
        string choice;
        bool flag = true;
        while (flag)
        {
            cout << "Higher or lower? (h/l)";
            cin >> choice;
            if (choice != "h" && choice != "l")
                cout << "bad answer, try again!" << endl;
            else
                flag = false;
        }
        int oldCardVal = map_hand_value(hands[player][0].getVal());
        int newCardVal = map_hand_value(hands[player][1].getVal());

        if (choice == "h" && newCardVal > oldCardVal || choice == "l" && newCardVal < oldCardVal)
        {
            cout << "Correct!" << endl;
            cout << "The card was: " << format_card(hands[player][1]) << endl;
            return true;
        }
        else if (newCardVal == oldCardVal)
        {
            cout << "Ouch! Double drink!" << endl;
        }
        else
            cout << "WRONG! Drink up!" << endl;
        cout << "The card was: " << format_card(hands[player][1]) << endl;
        return false;
    }

    bool handle_round_3(Card **hands, int player)
    {
        string choice;
        bool flag = true;
        while (flag)
        {
            cout << "Inside or Outside? (i/o)";
            cin >> choice;
            if (choice != "i" && choice != "o")
                cout << "bad answer, try again!" << endl;
            else
                flag = false;
        }
        int cardOneVal = map_hand_value(hands[player][0].getVal());
        int cardTwoVal = map_hand_value(hands[player][1].getVal());
        int cardThreeVal = map_hand_value(hands[player][2].getVal());

        if (cardThreeVal == cardOneVal || cardThreeVal == cardTwoVal)
        {
            cout << "Ouch! Double drink!" << endl;
            cout << "The card was: " << format_card(hands[player][2]) << endl;
            return false;
        }

        bool outside = (cardThreeVal > cardOneVal && cardThreeVal > cardTwoVal || cardThreeVal < cardOneVal && cardThreeVal < cardTwoVal);

        if (outside && choice == "o" || !outside && choice == "i")
        {
            cout << "Correct!" << endl;
            cout << "The card was: " << format_card(hands[player][2]) << endl;
            return true;
        }
        cout << "WRONG! Drink up!" << endl;
        cout << "The card was: " << format_card(hands[player][2]) << endl;
        return false;
    }

    bool handle_round_4(Card **hands, int player)
    {
        string choice;
        bool flag = true;
        while (flag)
        {
            cout << "Last round. What suit? (h/d/s/c)";
            cin >> choice;
            if (choice != "h" && choice != "d" && choice != "s" && choice != "c")
                cout << "bad answer, try again!" << endl;
            else
                flag = false;
        }
        if (choice[0] == std::tolower(hands[player][3].getSuit()))
        {
            cout << "Correct!" << endl;
            cout << "The card was: " << format_card(hands[player][3]) << endl;
            return true;
        }
        cout << "WRONG! Drink up!" << endl;
        cout << "The card was: " << format_card(hands[player][3]) << endl;
        return false;
    }
};