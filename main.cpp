#include <iostream>
#include <ctime>

using namespace std;

string **deal_hands(string *deck, int hands, int cards_per_hand)
{
    if (hands * cards_per_hand > 52)
    {
        cerr << "NOT ENOUGH CARDS";
        return NULL;
    }
    string **deal = new string *[hands];
    int index = 0;
    for (int i = 0; i < hands; i++)
    {
        string *hand = new string[cards_per_hand];
        for (int j = 0; j < cards_per_hand; j++)
        {
            hand[j] = deck[index];
            index++;
        }
        deal[i] = hand;
    }

    return deal;
}

void shuffle_deck(string *deck)
{
    srand(time(0));
    int rand_repetitions = std::rand() % 1000;
    string temp;
    int a, b;
    for (int i = 0; i < rand_repetitions; i++)
    {
        a = std::rand() % 52;
        b = std::rand() % 52;
        temp = deck[a];
        deck[a] = deck[b];
        deck[b] = temp;
    }
}

string *initialize_deck()
{

    // H = Hearts, C = Clubs, S = Spades, D = Diamonds
    string suits[4] = {"H", "C", "S", "D"};
    // A = Ace, K = King, Q = Queen, J = Jack, T = Ten
    string values[13] = {"A", "K", "Q", "J", "T", "9", "8", "7", "6", "5", "4", "3", "2"};

    string *deck = new string[52];

    int index;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 13; j++)
        {
            index = i * 13 + j;
            deck[index] = values[j] + suits[i];
        }
    }

    return deck;
}

void print_hands(string **hands, int players, int cards)
{
    for (int i = 0; i < players; i++)
    {
        cout << "Hand " << i + 1 << ": ";
        for (int j = 0; j < cards; j++)
        {
            cout << hands[i][j] << " ";
        }
        cout << endl;
    }
}

void print_hands_hiding_some(string **hands, int players, int cards, int show_count)
{
    for (int i = 0; i < players; i++)
    {
        cout << "Hand " << i + 1 << ": ";
        for (int j = 0; j < cards; j++)
        {
            if (j < show_count)
                cout << hands[i][j] << " ";
            else
                cout << " X ";
        }
        cout << endl;
    }
}

string format_card(string card)
{
    string suit;
    if (card[1] == 'H')
        suit = "Hearts";
    if (card[1] == 'D')
        suit = "Diamonds";
    if (card[1] == 'S')
        suit = "Spades";
    if (card[1] == 'C')
        suit = "Clubs";

    string result = card.substr(0, 1) + " of " + suit;
    return result;
}

int map_hand_value(char val)
{
    if (val == 'A') return 14;
    if (val == 'K') return 13;
    if (val == 'Q') return 12;
    if (val == 'J') return 11;
    if (val == 'T') return 10;
    return val - '0';
}

bool handle_round_1(string **hands, int player)
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
    if (hands[player][0][1] == 'H' || hands[player][0][1] == 'D')
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

bool handle_round_2(string **hands, int player)
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
    int oldCardVal = map_hand_value(hands[player][0][0]);
    int newCardVal = map_hand_value(hands[player][1][0]);

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

bool handle_round_3(string **hands, int player)
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
    int cardOneVal = map_hand_value(hands[player][0][0]);
    int cardTwoVal = map_hand_value(hands[player][1][0]);
    int cardThreeVal = map_hand_value(hands[player][2][0]);

    if (cardThreeVal == cardOneVal || cardThreeVal == cardTwoVal)
    {
        cout << "Ouch! Double drink!" << endl;
        cout << "The card was: " << format_card(hands[player][2]) << endl;
        return false;
    }

    bool outside = (cardThreeVal > cardOneVal && cardThreeVal > cardTwoVal 
        || cardThreeVal < cardOneVal && cardThreeVal < cardTwoVal);
    
    if (outside && choice == "o" || !outside && choice == "i") {
        cout << "Correct!" << endl;
        cout << "The card was: " << format_card(hands[player][2]) << endl;
        return true;
    }
    cout << "WRONG! Drink up!" << endl;
    cout << "The card was: " << format_card(hands[player][2]) << endl;
    return false;
}

bool handle_round_4(string **hands, int player)
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
    if (choice[0] == hands[player][3][1]) {
        cout << "Correct!" << endl;
        cout << "The card was: " << format_card(hands[player][3]) << endl;
        return true;
    }
    cout << "WRONG! Drink up!" << endl;
    cout << "The card was: " << format_card(hands[player][3]) << endl;
    return false;
}

int main()
{

    cout << "Welcome to ride the bus." << endl;

    bool ended = false;
    while (!ended)
    {
        string *deck = initialize_deck();
        shuffle_deck(deck);
        cout << "How many players? ";
        int players;
        cin >> players;
        string **hands = deal_hands(deck, players, 4);
        cout << "Let's begin." << endl;

        for (int stage = 0; stage < 4; stage++)
        {
            cout << "Round " << stage + 1 << ": " << endl;
            cout << "Current state of the hands: " << endl;
            print_hands_hiding_some(hands, players, 4, stage);
            cout << endl;
            for (int player = 0; player < players; player++)
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
        if (yn == "n") {
            ended = true;
        }
    }

    return 0;
}