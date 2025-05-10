#include <iostream>
#include <queue>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

class Player {
public:
    string name;
    Player(string n) : name(n) {}
};

class Match {
public:
    Player player1, player2;
    bool played;
    string result;

    Match(Player p1, Player p2) : player1(p1), player2(p2), played(false), result("Pending") {}
};

class MatchQueue {
private:
    queue<Match> matches;
public:
    void enqueue(Match m) { matches.push(m); }
    Match dequeue() { Match m = matches.front(); matches.pop(); return m; }
    bool isEmpty() { return matches.empty(); }

    vector<Match> getMatches() {
        vector<Match> matchList;
        while (!matches.empty()) {
            matchList.push_back(matches.front());
            matches.pop();
        }
        return matchList;
    }
};

// Generate random match result
string getRandomResult() {
    int outcome = rand() % 3;
    if (outcome == 0) return "Player 1 Wins";
    else if (outcome == 1) return "Player 2 Wins";
    else return "Draw";
}

// Print match results as CSV
void printCSV(const vector<Match>& matches) {
    cout << "\n=== TOURNAMENT RESULTS ===\n";
    cout << "Player1,Player2,Played,Result\n";
    for (auto& match : matches) {
        string result = getRandomResult();
        cout << match.player1.name << "," << match.player2.name << ",Yes," << result << "\n";
    }
}

int main() {
    srand(time(0));

    vector<Player> players = { Player("Alice"), Player("Bob"), Player("Charlie"), Player("Diana") };
    MatchQueue matchQueue;

    // Create match combinations
    for (size_t i = 0; i < players.size(); i++) {
        for (size_t j = i + 1; j < players.size(); j++) {
            matchQueue.enqueue(Match(players[i], players[j]));
        }
    }

    vector<Match> matchResults = matchQueue.getMatches();
    printCSV(matchResults);

    return 0;
}