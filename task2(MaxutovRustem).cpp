#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// Structure for a customer
struct Customer {
    string name;
    int priority;
    string ticketType;

    // For priority queue (higher number = higher priority)
    bool operator<(const Customer& other) const {
        return priority < other.priority;
    }
};

// Priority queue for ticket holders (e.g., VIP, Early-Bird, etc.)
class TicketQueue {
private:
    priority_queue<Customer> pq;
public:
    void enqueue(Customer c) {
        pq.push(c);
    }

    Customer dequeue() {
        if (pq.empty()) {
            cout << "[Error] Queue is empty!\n";
            return { "", -1, "" };
        }
        Customer top = pq.top();
        pq.pop();
        return top;
    }

    Customer peek() {
        if (pq.empty()) {
            return { "", -1, "" };
        }
        return pq.top();
    }

    bool isEmpty() {
        return pq.empty();
    }
};

// Normal queue for spectators
class SpectatorQueue {
private:
    queue<string> spectators;
public:
    void enqueue(string name) {
        spectators.push(name);
    }

    void dequeue() {
        if (spectators.empty()) {
            cout << "[Error] No spectators in queue.\n";
            return;
        }
        cout << "Spectator " << spectators.front() << " has exited.\n";
        spectators.pop();
    }

    void display() {
        cout << "Current Spectators: ";
        queue<string> temp = spectators;
        while (!temp.empty()) {
            cout << temp.front() << " ";
            temp.pop();
        }
        cout << "\n";
    }
};

// Instead of saving to file, print CSV to console
void saveToCSV(vector<Customer> customers) {
    cout << "\n=== CSV DATA ===\n";
    cout << "Name,Priority,Ticket Type\n";
    for (const auto& c : customers) {
        cout << c.name << "," << c.priority << "," << c.ticketType << "\n";
    }
}

int main() {
    TicketQueue ticketQueue;
    SpectatorQueue spectatorQueue;

    vector<Customer> customers = {
        {"Alice", 3, "VIP"},
        {"Bob", 2, "Early-Bird"},
        {"Charlie", 1, "Regular"},
        {"Diana", 3, "VIP"},
        {"Ethan", 1, "Regular"}
    };

    for (const auto& c : customers) {
        ticketQueue.enqueue(c);
    }

    cout << "Current highest priority: "
         << ticketQueue.peek().name << " ("
         << ticketQueue.peek().ticketType << ")\n";

    spectatorQueue.enqueue(ticketQueue.dequeue().name);
    spectatorQueue.enqueue(ticketQueue.dequeue().name);
    spectatorQueue.enqueue(ticketQueue.dequeue().name);

    spectatorQueue.display();
    saveToCSV(customers);

    return 0;
}