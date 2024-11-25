/*
 * CSEN 79 Lab: Poker Statistics
 *
 * Name: Andrew Vattuone
 * Email: avattuone@scu.edu
 */
#include <ctime>
#include <iomanip>
#include <iostream>
#include <cstring>
#include <cmath>
#include "card.h"
#include "deck.h"
#include "poker.h"

using namespace std;
using namespace lab2avattuone;

// Generates one sample hand for each rank and prints out each example hand
// precondition: poker is an instantiated object
// postcondition: each example hand output is displayed correctly
void pokerHands(Poker &poker) 
{
	// array keeps track of which ranks are found based on their corresponding int values defined in poker.cxx
	int ranks[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0}; 
	// records the total number of different ranks that have been found
	int diffRanksFound = 0;
	// keeps dealing out hands until all 9 ranks have been found
	while (diffRanksFound < 9)
	{
		// deals a hand and ranks it
		poker.dealHand();
		Poker::Rank handRank = poker.rankHand();
		
		// checks if the rank has already been found, and if so it prints out the hand
		if(ranks[handRank] == 0)
		{
			// updates ranks to indicate that the hand has been found
			ranks[handRank] = 1;
			// increases diffRanksFound to indicate that a new rank has been found
			diffRanksFound++;
			cout << poker << " " << Poker::RankNames[handRank] << endl;
		}
	}
}

// Collect statistics for each rank of Poker by dealing hands until percentages of each hand of the total have stabilized
// precondition: poker is an instantiated object
// postcondition: stats are all correctly displayed
void pokerStats(Poker &poker) {
	time_t tmark = clock();
	// stores the number of times each rank is generated based on their correspodning int values defined in poker.cxx
	int rankCounts[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
	// for each hand rank, rankPercentages stores the percentage that a particular rank makes up of the total hands dealt
	double rankPercentages[9] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
	
	int handsDealt = 0; // stores the total number of hands dealt
	double epsilon = 0.000001; // epsilon value used later to check if pecentages have stabilized
	
	// stores the number of hand percentages that have been stabilized, which is used to determine if the while loop should be exited
	int handsStabilized;

	// while loop keeps generating hands until all 9 percentages have stabilized
	while(handsStabilized != 9)
	{
		handsStabilized = 0;
		poker.dealHand();
		Poker::Rank handRank = poker.rankHand();
		rankCounts[handRank]++;
		handsDealt++;
		
		// every 10000 hands it checks the percentages to see if they've changed
		if(handsDealt % 10000 == 0)
		{
			// calculates the new percentage for each rank and compares it to the rank's old percentage
			for(int i = 0; i < 9; i++)
			{
				double newPercentage = (double(rankCounts[i]) / handsDealt);
				// if the difference between the two percentages is less than epsilon (0.000001), then the percentage has stabilized
				if(abs(newPercentage - rankPercentages[i]) <= epsilon)
				{
					handsStabilized++; // increases the number of stabilized hands by 1
				}
				rankPercentages[i] = newPercentage; // updates the percentage to the new percentage
			}
		}
	}
	
	tmark = (clock() - tmark);	// stop the clock
	double secondsElapsed = double(tmark) / CLOCKS_PER_SEC; // convert clock time to seconds
	double averagePer50k = secondsElapsed / (handsDealt/50000); // find average time it takes to deal 50k hands
	cout << "Dealt " << handsDealt << " hands. Elapsed Time: " << secondsElapsed << " seconds." << endl;
	cout << "Average " << averagePer50k << " seconds per 50k hands." << endl;
	
	// prints out the total times each rank was generated and the percentage of each rank 
	for(int i = 8; i >= 0; i--)
	{	
		cout << setw(15) << Poker::RankNames[i] << ":" << setw(9) << rankCounts[i] << setw(12) << setprecision(4) << rankPercentages[i]*100 << "%" << endl;
	}
}

int main(void) {
	Poker poker;
	cout << "Sample hand for each Rank:" << endl;
	pokerHands(poker);
	cout << endl << "Statistics:" << endl;
	pokerStats(poker);

	return EXIT_SUCCESS;
}
