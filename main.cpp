#include<iostream>
#include<vector>
#include<algorithm>
#include<ctime>
using namespace std;

// Create Deck 
vector<int> makeDeck() {
    vector<int> deck;
    for (int i = 2; i<=10; i++) {
        for (int j = 0; j < 4; j++) {
            deck.push_back(i);
        }
    }
    for  (int f = 0; f < 4; f++) deck.push_back(10);
    for  (int f = 0; f < 4; f++) deck.push_back(10);
    for  (int f = 0; f < 4; f++) deck.push_back(10);
    // Above three are for J, Q, K ⬆
    for  (int f = 0; f < 4; f++) deck.push_back(1); // Initially consider it as 1 then later on we'll setup logic for 11
    return deck;
}

// Shuffle Deck 

void shuffleDeck(vector<int> &deck) {
    random_shuffle(deck.begin(), deck.end());
}

// Draw Card

int drawCard(vector<int> &deck) {
    int card = deck.back();
    deck.pop_back();
    return card;
}

// Calculate Player Score 

int calcScore(vector<int> hand) {
    int total = 0;
    int aceCount = 0;

    for (int card : hand) {
        total += card;
        if (card == 1) aceCount++;
    }


while (aceCount > 0 && total + 10 <= 21) {
    total += 10;
    aceCount--;
}

return total;
}

void playerTurn(vector<int> &deck, vector<int> &playerHand) {
    char choice;

    while(true) {
        cout << "Your Cards: ";
        for (int card : playerHand) cout << card << " ";
        cout << " | Score: " << calcScore(playerHand) << endl;
        cout << "Do you want to Hit (H) or Stand (S)? ";
        cin >> choice; 

        if (choice == 'H' || choice == 'h') {
            playerHand.push_back(drawCard(deck));

            if (calcScore(playerHand) > 21) {
                cout << "\nYou Busted!\nReason: Total Exceed 21.";
                break;
            }
        }
        else if ( choice == 'S' || choice == 's') {
            break;
        }
        else {
            cout << "Invalid Choice, Please Enter S or H." << endl;
        }
    }
}

void dealerTurn(vector<int> &deck, vector<int> &dealerHand) {
    cout << "\nDealer's Turn:\n";
    cout << "Dealer Reveals Card: ";
    for (int card : dealerHand) cout << card << " ";
    
    while (calcScore(dealerHand) < 17) {
        cout << "\nDealer Hits....\n";
        dealerHand.push_back(drawCard(deck));
    }

    cout << "Dealer Total Score: " << calcScore(dealerHand) << endl;
}

// Check the Winner 

void checkWinner(vector<int> &playerHand, vector<int>dealerHand) {
    int playerScore = calcScore(playerHand);
    int dealerScore = calcScore(dealerHand);

    cout << "\n-----------Final Scores------------";
    cout << "\nYour Score: " << playerScore;
    cout << "\nDealer's Score: " << dealerScore << endl;    
    
    int playerTotal = playerScore;
    int dealerTotal = dealerScore;

    if (playerTotal > 21) {
        cout << "You Busted! Dealer Wins!\nReason: Total Exceed 21.";
    }
    else if (dealerTotal > 21) {
        cout << "Dealer Busted! You Win!\nReason: Total Exceed 21.";
    }
    else if (playerTotal > dealerTotal) {
        cout << "You Win!\nReason: Higher Total.";
    }
    else if (dealerTotal > playerTotal) {
        cout << "Dealer Wins!\nReason: Higher Total.";
    }
    else {
        cout << "It's a Tie!\nReason: Equal Total.";
    }
}

// Main Fucntion 

int main() { 
    int i, j, f, playerTotal, dealerTotal;
    srand(time(0));
    char again = 'Y';

    while (again == 'Y' || again == 'y') {
        vector<int> deck = makeDeck(); 
        shuffleDeck(deck);

        vector<int> playerHand;
        vector<int> dealerHand;

        // starting Card
        playerHand.push_back(drawCard(deck));
        playerHand.push_back(drawCard(deck));
        dealerHand.push_back(drawCard(deck));
        dealerHand.push_back(drawCard(deck));

        cout << "Dealer's Showing Card: " << dealerHand[0] << endl;

        playerTurn(deck, playerHand);

        if (calcScore(playerHand) < 21) {
            dealerTurn(deck, dealerHand);
        }

        checkWinner(playerHand, dealerHand);

        cout << "\nDo you want to play again? (Y/N): ";
        cin >> again;
    }


    system("pause");
    return 0; 
}