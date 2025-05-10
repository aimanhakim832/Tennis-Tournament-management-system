#include <iostream>
#include <cstdlib>
#include <ctime>
#include <queue>
#include <map>

using namespace std;

// Struct for match record
struct Match {
    string player1;
    string player2;
    int score1;
    int score2;
    string round;
    string date;
    Match* next;
};

// Struct for player
struct Player {
    int id;
    string name;
};

// Match history manager using a custom singly linked list
class MatchHistory {
private:
    Match* head;
    map<int, Player> players; // Track players by ID

public:
    MatchHistory() : head(nullptr) {}

    void addMatch(string p1, string p2, int s1, int s2, string r, string d) {
        Match* newMatch = new Match{p1, p2, s1, s2, r, d, nullptr};
        if (!head) {
            head = newMatch;
        } else {
            Match* temp = head;
            while (temp->next)
                temp = temp->next;
            temp->next = newMatch;
        }
    }

    void displayHistory() {
        if (!head) {
            cout << "[Info] No match records available.\n";
            return;
        }

        Match* temp = head;
        int count = 1;
        cout << "\n=== Match History ===\n";
        while (temp) {
            cout << count++ << ". " << temp->date << " | " << temp->round << " | "
                 << temp->player1 << " [" << temp->score1 << "] vs "
                 << temp->player2 << " [" << temp->score2 << "]\n";
            temp = temp->next;
        }
    }

    void searchByPlayer(string name) {
        cout << "\n=== Matches for Player: " << name << " ===\n";
        Match* temp = head;
        bool found = false;

        while (temp) {
            if (temp->player1 == name || temp->player2 == name) {
                cout << temp->date << " | " << temp->round << " | "
                     << temp->player1 << " [" << temp->score1 << "] vs "
                     << temp->player2 << " [" << temp->score2 << "]\n";
                found = true;
            }
            temp = temp->next;
        }

        if (!found)
            cout << "[Info] No matches found for " << name << ".\n";
    }

    void printCSV() {
        cout << "\n=== CSV DATA ===\n";
        cout << "Date,Round,Player1,Score1,Player2,Score2\n";
        Match* temp = head;
        while (temp) {
            cout << temp->date << "," << temp->round << "," 
                 << temp->player1 << "," << temp->score1 << "," 
                 << temp->player2 << "," << temp->score2 << "\n";
            temp = temp->next;
        }
    }

    void handlePlayerWithdrawal(int withdrawnPlayerId, queue<Player>& replacementQueue) {
        // 1. Track player withdrawals and update the match history accordingly
        cout << "Player with ID " << withdrawnPlayerId << " has withdrawn from the tournament.\n";

        // Find and replace withdrawn players in match history
        Match* temp = head;
        while (temp) {
            if (temp->player1 == players[withdrawnPlayerId].name) {
                // Handle player1 withdrawal
                if (!replacementQueue.empty()) {
                    Player replacementPlayer = replacementQueue.front();
                    replacementQueue.pop();
                    temp->player1 = replacementPlayer.name; // Replace player1
                    cout << "Player " << temp->player1 << " replaced player " << players[withdrawnPlayerId].name << " in match.\n";
                } else {
                    temp->player1 = "TBD"; // No replacement, mark as TBD
                }
            }
            if (temp->player2 == players[withdrawnPlayerId].name) {
                // Handle player2 withdrawal
                if (!replacementQueue.empty()) {
                    Player replacementPlayer = replacementQueue.front();
                    replacementQueue.pop();
                    temp->player2 = replacementPlayer.name; // Replace player2
                    cout << "Player " << temp->player2 << " replaced player " << players[withdrawnPlayerId].name << " in match.\n";
                } else {
                    temp->player2 = "TBD"; // No replacement, mark as TBD
                }
            }
            temp = temp->next;
        }
    }

    void addPlayer(Player p) {
        players[p.id] = p;
    }

    ~MatchHistory() {
        while (head) {
            Match* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// Generate random scores between 0–7
int randomScore() {
    return rand() % 8;
}

int main() {
    srand(time(0));

    MatchHistory history;

    // Sample match records and players
    history.addPlayer({1, "Alice"});
    history.addPlayer({2, "Bob"});
    history.addPlayer({3, "Charlie"});

    history.addMatch("Alice", "Bob", randomScore(), randomScore(), "Quarterfinal", "2025-04-25");
    history.addMatch("Charlie", "Alice", randomScore(), randomScore(), "Semifinal", "2025-04-26");

    // Sample replacement queue
    queue<Player> replacementQueue;
    replacementQueue.push({4, "David"});

    // Display match history
    history.displayHistory();

    // Handle withdrawal of player Bob (ID 2)
    history.handlePlayerWithdrawal(2, replacementQueue);

    // Display updated match history
    history.displayHistory();

    return 0;
}