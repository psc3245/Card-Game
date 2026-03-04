#include <vector>
#include "Card.cpp"

using namespace std;

class Deck
{
public:

    Card** deal_hands(int players, int cards) {
        if (!is_shuffled || get_cards_remaining() < players * cards) {
            // What should I do here?
            // return;
        }
        Card** hands = new Card*[players];
        for (int p = 0; p < players; p++) {
            hands[p] = new Card[cards];
            for (int c = 0; c < cards; c++) {
                hands[p][c] = draw();
            }
        }
        return hands;
    }
    
    Card* deal_hand(int n) {
        if (!is_shuffled || get_cards_remaining() < n) {
            // What should I do here?
            // return;
        }
        Card *cards = new Card[n];
        for (int i = 0; i < n; i++) {
            cards[i] = draw();
        }
        return cards;
    }
    Card draw() {
        if (!is_shuffled || get_cards_remaining() < 1) {
            // What should I do here?
            // return;
        }
        Card c = deck.at(0);
        deck.erase(deck.begin());
        return c;
    }
    void shuffle()
    {
        srand(time(0));
        int rand_repetitions = std::rand() % 1000;
        int a, b;
        for (int i = 0; i < rand_repetitions; i++)
        {
            a = std::rand() % 52;
            b = std::rand() % 52;
            Card temp = this->deck[a];
            this -> deck[a] = this->deck[b];
            this->deck[b] = temp;
        }
        is_shuffled = true;
    }

    int get_cards_remaining() {
        return deck.size();
    }

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
                Card *c = new Card(suits[i], values[j]);
                deck.push_back(*c);
            }
        }
        is_shuffled = false;
    }

private:
    vector<Card> deck;
    bool is_shuffled;
};