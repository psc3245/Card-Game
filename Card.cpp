class Card
{
public:
    bool face_up;
    char suit;
    char val;

    char getSuit() { return suit; }
    char getVal() { return val; }
    bool isFaceUp() {return face_up;}

    void setSuit(char suit) { this->suit = suit;}
    void setVal(char val) {this->val = val;}
    void toggleFaceUp(bool face_up) {this->face_up = face_up;}

    Card(char suit, char val) {
        this->suit = suit;
        this->val = val;
        this->face_up = false;
    }

    Card() {
        this->face_up = false;
    }
};