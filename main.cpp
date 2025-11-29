#include<iostream>
#include<vector>
#include<algorithm>
#include<ctime>
#include<random>
#include<windows.h>
using namespace std;

void setColor(int c)
    {SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);}

// Create Deck of cards, total 52 card. (2-10, J, Q, K, A) * 4 
vector<int> makeDeck() {
    vector<int> deck;
    for (int i = 2; i<=10; i++) {
        for (int j = 0; j < 4; j++) {
            deck.push_back(i);
        }
    }
    for  (int f = 0; f < 3 * 4; f++) deck.push_back(10); // For J, Q, K

    for  (int f = 0; f < 4; f++) deck.push_back(1); // Initially consider it as 1 then later on we'll setup logic for 11
    return deck;
}

// Shuffle Deck 

void shuffleDeck(vector<int> &deck) { // Here we use pass by reference, because we want to changee the original deck
    shuffle(deck.begin(), deck.end(), default_random_engine(time(0))); 
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
       setColor(10); 
       Sleep(1000); cout << "Your Cards: ";
        for (int card : playerHand) cout << card << " ";
        cout << " | Total Score: " << calcScore(playerHand) << endl << endl; setColor(7);
        setColor(11);
        Sleep(0);
        cout << "Do you want to Hit (H) or Stand (S)? ";
        setColor(7);
        cin >> choice; 
        setColor(8); cout << "\n--------------------------------------------\n\n"; setColor(7);

        if (choice == 'H' || choice == 'h') {
            playerHand.push_back(drawCard(deck));

            if (calcScore(playerHand) > 21) {
               setColor(12); cout << "You Busted!\n\n"; setColor(7);
                break;
            }
            if (calcScore(playerHand) == 21) {
                cout << "You Hit Blackjack!\n\n";
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
    setColor(12);
    Sleep(600); cout << "Dealer's Turn....\n"; setColor(7);
    cout << "\nDealer Reveals Card: ";
    for (int card : dealerHand) cout << card << " ";
    
    while (calcScore(dealerHand) < 17) {
        setColor(12);
        cout << "\nDealer Hits...." << endl;
        setColor(7);
        dealerHand.push_back(drawCard(deck));
    }
    Sleep(600);
    cout << "\nDealer Total Score: " << calcScore(dealerHand);
    cout << "\n\n";
}

// Check the Winner 

void checkWinner(vector<int> &playerHand, vector<int>dealerHand) {
    int playerScore = calcScore(playerHand);
    int dealerScore = calcScore(dealerHand);
    setColor(8); 
    Sleep(800);
    cout << "============================================" << endl; setColor(7);
                            setColor(10);
    cout << "                 Final Scores               " << endl;
                            setColor(7);
    setColor(8);
    cout << "============================================" << endl;
    setColor(7);
    cout << "\n> Your Score: " << playerScore;
    cout << "\n> Dealer's Score: " << dealerScore << endl << endl;    
    
    int playerTotal = playerScore;
    int dealerTotal = dealerScore;
    setColor(14);
    Sleep(600);
    if (playerTotal > 21) {
        cout << "You Busted! Dealer Wins!\nReason: Total Exceed 21.\n";
    }
    else if (dealerTotal > 21) {
        cout << "Dealer Busted! You Win!\nReason: Total Exceed 21.\n";
    }
    else if (playerTotal > dealerTotal) {
        cout << "You Win!\nReason: Higher Total.\n";
    }
    else if (dealerTotal > playerTotal) {
        cout << "Dealer Wins!\nReason: Higher Total.\n";
    }
    else {
        cout << "It's a Tie!\nReason: Equal Total.\n";
    }
    setColor(7);
}

// Main Fucntion 

int main() { 
    int i, j, f, playerTotal, dealerTotal;
{
    const int consoleWidth = 100; // adjust to your console width

    string heading = R"(
    
  ____  _            _       _            _    
 | __ )| | __ _  ___| | __  | | __ _  ___| | __
 |  _ \| |/ _` |/ __| |/ /  | |/ _` |/ __| |/ /
 | |_) | | (_| | (__|   < |_| | (_| | (__|   < 
 |____/|_|\__,_|\___|_|\_\___/ \__,_|\___|_|\_\
                                               
    
)";

    string line;
    size_t pos = 0, next;
    while ((next = heading.find('\n', pos)) != string::npos) {
        line = heading.substr(pos, next - pos);
        int padding = (consoleWidth - line.length()) / 2;
        if (padding < 0) padding = 0; // in case line is too long
        cout << string(padding, ' ') << line << endl;
        pos = next + 1;
    }
    // int consoleWidth = 80; 
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Set color to bright cyan for the first line
    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    cout << string((consoleWidth - 24) / 2, ' ') << "Welcome to the Blackjack Game!\n\n";

    // Set color to bright yellow for the second line
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    cout << string((consoleWidth - 24) / 2, ' ') << "Created By Dawood and Aneed\n\n";

    // Reset to default color
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    srand(time(0));

}
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

        setColor(12);
         cout << "Dealer's Cards: " << dealerHand[0] << " and [hidden]\n\n";
        setColor(7);

        playerTurn(deck, playerHand);

        if (calcScore(playerHand) < 21) {
            dealerTurn(deck, dealerHand);
        }

        checkWinner(playerHand, dealerHand);
        setColor(11);
        Sleep(600);
        cout << "\nDo you want to play again? (Y/N): \n";
        setColor(7);
        cin >> again;
    }


    cin.ignore();
    return 0; 
}