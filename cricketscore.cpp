#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>

using namespace std;

class Player {
public:
    string name;
    int runs;
    int ballsFaced;

    Player(string n) : name(n), runs(0), ballsFaced(0) {}
};

class Team {
public:
    string teamName;
    vector<Player> players;
    int totalRuns;
    int wicketsLost;

    Team(string name, vector<string> playerNames) : teamName(name), totalRuns(0), wicketsLost(0) {
        for (int i = 0; i < playerNames.size(); ++i) {
            string pname = playerNames[i];
            players.push_back(Player(pname));
        }
    }
    
    void displayScorecard() {
        cout << "Scorecard for " << teamName << ":\n";
        for (int i = 0; i < players.size(); ++i) {
            Player& player = players[i];
            cout << player.name << " - Runs: " << player.runs << ", Balls: " << player.ballsFaced << "\n";
        }
        cout << "Total Runs: " << totalRuns << "/" << wicketsLost << "\n";
    }
};

class Match {
    int overs;
    Team* team1;
    Team* team2;
    Team* battingTeam;
    Team* bowlingTeam;
    
    void swapTeams() {
        Team* temp = battingTeam;
        battingTeam = bowlingTeam;
        bowlingTeam = temp;
    }
    
    void playOver(int overNum) {
        cout << "Over " << overNum + 1 << ":\n";
        for (int ball = 1; ball <= 6; ++ball) {
            if (battingTeam->wicketsLost == battingTeam->players.size() - 1) {
                cout << "All out!\n";
                return;
            }
            int outcome = rand() % 8;  // Randomly generate an outcome (0-7)
            Player& striker = battingTeam->players[battingTeam->wicketsLost];
            
            if (outcome <= 6) { // Runs from 0 to 6
                striker.runs += outcome;
                striker.ballsFaced++;
                battingTeam->totalRuns += outcome;
                cout << "Ball " << ball << ": " << striker.name << " scored " << outcome << " run(s)\n";
            } else { // Wicket
                striker.ballsFaced++;
                battingTeam->wicketsLost++;
                cout << "Ball " << ball << ": " << striker.name << " is OUT!\n";
            }
        }
        cout << "End of Over " << overNum + 1 << ". Score: " << battingTeam->totalRuns << "/" << battingTeam->wicketsLost << "\n\n";
    }
    
    void playInnings() {
        for (int i = 0; i < overs; ++i) {
            playOver(i);
            if (battingTeam->wicketsLost == battingTeam->players.size() - 1) {
                break;
            }
        }
        battingTeam->displayScorecard();
    }

public:
    Match(int o, Team* t1, Team* t2) : overs(o), team1(t1), team2(t2) {
        srand(time(0));  //  for random number generation
    }
    
    void start() {
        // Toss
        cout << "Tossing the coin...\n";
        if (rand() % 2 == 0) {
            cout << team1->teamName << " wins the toss and will bat first.\n";
            battingTeam = team1;
            bowlingTeam = team2;
        } else {
            cout << team2->teamName << " wins the toss and will bat first.\n";
            battingTeam = team2;
            bowlingTeam = team1;
        }
        
        // First innings
        cout << "First Innings:\n";
        playInnings();
        
        // Swap teams for second innings
        swapTeams();
        
        // Second innings
        cout << "Second Innings:\n";
        playInnings();
        
        // Determine the winner
        cout << "Match Result:\n";
        if (team1->totalRuns > team2->totalRuns) {
            cout << team1->teamName << " wins the match by " << team1->totalRuns - team2->totalRuns << " runs.\n";
        } else if (team2->totalRuns > team1->totalRuns) {
            cout << team2->teamName << " wins the match by " << team2->totalRuns - team1->totalRuns << " runs.\n";
        } else {
            cout << "The match is a tie.\n";
        }
    }
};

int main() {
    vector<string> team1Players = {"PRANAV", "AMIT", "RAUSHAN", "ABHISHEK", "ASHUTOSH"};
    vector<string> team2Players = {"PAWAN", "ROCKY", "GOLU", "KUNDAN", "MITHLESH"};
    
    Team team1("Team A(PRANAV)", team1Players);
    Team team2("LAFUA Team B", team2Players);
    
    Match match(2, &team1, &team2);  // 2-over match
    match.start();
    
    return 0;
}
