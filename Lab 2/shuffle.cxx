/*
 * Name: Andrew Vattuone
 * Email: avattuone@scu.edu
 */
#include <iostream>
#include <cstdlib>
#include "card.h"
#include "deck.h"

namespace lab2avattuone 
{
	// shuffles the deck using the Fisher-Yates algorithm
	// precondition: nCards > 0 and there are 2 or more elements in cards array
	// postcondition: array of cards has same elements but they're all shuffled
	void Deck::shuffle(void) 
	{	
		// Fisher-Yates algorithm shuffling loop
		for(int i = Deck::nCards-1; i >= 1; i--)
		{
			// generates a random index to randomly pick a card from the array
			int j = rand() % (Deck::nCards-1);
			// swaps the randomly chosen card with the current card (based on the current iteration of the loop)
			Card temp = cards[j];
			cards[j] = cards[i];
			cards[i] = temp;
		}
	}

	// deals out the top card
	// precondition: guard > 0 and nCards > 0
	// postcondition: next is 1 larger (represents that a card has been removed from the top of the deck)
	const Card &Deck::deal() {
		// if there number of cards left in the deck is less than guard, it reshuffles it and resets the counter
		if(nCards - next < guard)
		{
			// resets next since the next card will be on the top of the deck after shuffling
			next = 0;
			shuffle();
		}
		// returns the next card in the array (which always is the top card in this case)
		return cards[next++];
	}
}

