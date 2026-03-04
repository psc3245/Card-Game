#include <vector>
#include "Card.cpp"

using namespace std;

class Deck
{
public:
    Card draw() {}
    void shuffle() {}

    Deck()
    {
        char suits[4] = {'H', 'D', 'S', 'C'};
        // A = Ace, K = King, Q = Queen, J = Jack, T = Ten
        char values[13] = {'A', 'K', 'Q', 'J', 'T', '9', '8', '7', '6', '5', '4', '3', '2'};

        int index;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 13; j++)
            {
                Card* c = new Card(suits[i], values[j]);
                deck.push_back(*c);
            }
        }
    }

private:
    vector<Card> deck;
};