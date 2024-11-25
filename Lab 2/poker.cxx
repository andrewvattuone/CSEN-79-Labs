/*
 * CSEN 79 Lab: Poker Statistics
 *
 * Name: Andrew Vattuone
 * Email: avattuone@scu.edu
 */
#include <iomanip>
#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>
#include "card.h"
#include "deck.h"
#include "poker.h"

using namespace std;

namespace lab2avattuone
{
	const std::string Poker::RankNames[] = {
		"High Card",	  // 0
		"Pair",			  // 1
		"Two Pairs",	  // 2
		"Triple",		  // 3
		"Straight",		  // 4
		"Flush",		  // 5
		"Full House",	  // 6
		"Four of a Kind", // 7
		"Straight Flush"  // 8
	};

	Poker::Poker() { deck.shuffle(); }

	// deal 5 cards
	void Poker::dealHand()
	{
		for (auto i = 0; i < Poker::POKER_HANDCARDS; ++i)
			hand[i] = deck.deal();
		this->sortHand();
	}

	// sort them in nice order
	// fancy way to use "greater", a lambda construct
	void Poker::sortHand()
	{
		size_t n = sizeof(hand) / sizeof(hand[0]);
		std::sort(hand, hand + n, std::greater<int>());
	}

	// helper funtions for ranking
	// We implemeneted "isStraight" as an example.
	bool Poker::isStraight(uint r[])
	{
		uint rankBits = 0;
		for (auto i = 0; i < Card::NRANKS; i++)
			if (r[i] != 0)
				rankBits |= 0x1 << (i + 1);
		if (r[12] != 0)
			rankBits |= 0x1;
		while ((rankBits & 0x1) == 0)
			rankBits >>= 1;
		return rankBits == 0x1F;
	}

	// checks if current hand is a flush (all 5 cards have the same suit)
	// precondition: s is an initialized array of uints
	// postcondition: no change in s and a boolean is returned
	bool Poker::isFlush(uint s[]) 
	{ 
		// iterates through each element in s to see how many cards of each suit are in the hand 
		for(int i = 0; i < Card::NSUITS; i++)
		{
			// if one suit has a value of 5, that means all 5 cards have the same suit, so it returns true since it's a flush
			if(s[i] == 5)
			{
				return true;
			}
		}
		// if no 5 was found in s, the hand isn't a suit, so return false
		return false;
	}
	
	// checks if a quad is present in the current hand
	// precondition: r is an initialized array of uints
	// postcondition: no change in r and a boolean is returned
	bool Poker::isQuad(uint r[]) 
	{ 
		// goes through every element in r to see if there are 4 cards with the same rank in a hand
		for(int i = 0; i < Card::NRANKS; i++)
		{
			// if an element of r has a value of 4, then the hand has 4 cards of the same rank and is therefore a quad, so return true
			if(r[i] == 4)
			{
				return true;
			}
		}
		// if no value of r is 4 then a quad wasn't found so return false
		return false; 
	}
	
	// checks if a triple (3 cards of the same rank) is present in the current hand
	// precondition: r is an initialized array of uints
	// postcondition: no change in r and a boolean is returned
	bool Poker::isTriple(uint r[]) 
	{ 
		// goes through every element in r to see if there are 3 cards with the same rank in the hand
		for(int i = 0; i < Card::NRANKS; i++)
		{
			// if an element of r has a value of 3, then the hand has 3 cards of the same rank and thus contains a triple, so return true
			if(r[i] == 3)
			{
				return true;
			}
		}
		// if no 3 was found in r, the hand doesn't contain a triple, so return false
		return false;
	}
	
	// checks if a pair (2 cards of same rank) is present in current hand
	// precondition: r is an initialized array of uints
	// postcondition: no change in r and a boolean is returned
	bool Poker::isPair(uint r[]) 
	{ 
		// iterates through each element in r to see if there are 2 cards with the same rank in the hand
		for(int i = 0; i < Card::NRANKS; i++)
		{
			// if an element of r has a value of 2, then the hand has 2 cards of same rank and thus contains a pair, so return true
			if(r[i] == 2)
			{
				return true;
			}
		}
		// if no 2 was found in r, the hand doesn't contain a pair, so return false
		return false; 
	}
	
	// checks if there are 2 pairs in current hand
	// precondition: r is an initialized array of uints
	// postcondition: no change in r and a boolean is returned
	bool Poker::is2Pair(uint r[]) 
	{ 
		// stores the number of pairs found
		int pairCount = 0;
		// iterates through each element in r to see if there are 2 cards with the same rank in the hand
		for(int i = 0; i < Card::NRANKS; i++)
		{
			// if an element of r has a value of 2, then the hand has 2 cards of same rank and thus contains a pair, so pairCount increases by 1
			if(r[i] == 2)
			{
				pairCount++;
			}
		}
		// if 2 pairs were found return true
		if(pairCount == 2)
		{
			return true;
		}
		// 2 pairs weren't found so return false
		return false;
	}

	bool Poker::countRank(uint r[], int n)
	{
		for (auto i = 0; i < Card::NRANKS; i++)
			if (r[i] == n)
				return true;
		return false;
	}

	Poker::Rank Poker::rankHand()
	{
		Poker::Rank rank; // the return value

		uint rankCount[Card::NRANKS];
		uint suitCount[Card::Suit::CLUB + 1];

		memset(rankCount, 0, sizeof(rankCount));
		memset(suitCount, 0, sizeof(suitCount));

		// first count the hand by rank and suit
		for (auto i = 0; i < this->POKER_HANDCARDS; ++i)
		{
			rankCount[hand[i].getRank() - 1]++;
			suitCount[hand[i].getSuit()]++;
		}

		// Poker ranking is a series of if/else's
		if (isFlush(suitCount))
		{
			// Flush can be a straight
			if (isStraight(rankCount))
				rank = POKER_STRAIGHT_FLUSH;
			else
				rank = POKER_FLUSH;
		}
		else if (isQuad(rankCount)) // 4 of a kind
			rank = POKER_QUAD;
		else if (isTriple(rankCount))
		{						   // 3 of a kind
			if (isPair(rankCount)) // also have a pair?  Then full house
				rank = POKER_FULLHOUSE;
			else
				rank = POKER_TRIPLE;
		}
		else if (isStraight(rankCount)) // simple straight
			rank = POKER_STRAIGHT;
		else if (is2Pair(rankCount))
			rank = POKER_2_PAIR;
		else if (isPair(rankCount))
			rank = POKER_PAIR;
		else
			rank = POKER_HIGHCARD; // default
		return rank;
	}

	ostream &operator<<(ostream &os, const Poker &h)
	{
		for (auto i = 0; i < h.POKER_HANDCARDS; i++)
			cout << h.hand[i];
		return os;
	}
}
