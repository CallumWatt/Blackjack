#include <iostream>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
using namespace std;

int upcard;
int dealer = 0;
int player = 0;
int money = 100;
int bet = 0;
int card;
int value;
int dealerCard;
bool inPlay = true;
bool draw;
string input;

int drawCard() {
	srand(time(NULL));
	card = rand() % 11 + 1;
	return card;
}

int dealerNewCard() {
	srand(time(NULL));
	dealerCard = rand() % 11 + 1;
	return dealerCard;
}

int dealerCheckValue() {
	dealer = dealerCard + dealer;
	if (dealer > 21) {
		cout << "Dealer went bust";
	}
	return dealer;
}

int checkValue() {
	player = card + player;
	if (player > 21)
	{
		cout << "You have busted";
		return 0;
	}
	return player;
}

int firstHand() {
	int drawCard();
	value = card;
	return value;
}

void endGame() {
	while (dealer < 17)
	{
		dealerNewCard();
		dealerCheckValue();
	}
	if (player > dealer && player < 21)
	{
		cout << "You win!";
	}
	if (player > 21)
	{
		cout << "You lose!";
	}
	if (player < dealer && dealer < 21) {
		cout << "You lose!";
	}
	if (player < dealer && dealer > 21)
	{
		cout << "You win!";
	}
}

int initiliseDealer() {
	srand(time(NULL));
	upcard = rand() % 11 + 1;
	return upcard;
}

int main() {
	cout << "Please input bet";
	cin >> bet;
	cout << "Dealing cards";
	drawCard();
	checkValue();
	drawCard();
	checkValue();
	initiliseDealer();
	while (inPlay == true) {
		cout << "\n" << "Current value - " << player << "\n" << "Dealer upcard - " << upcard << "\n" << "Do you wish to draw? y/n";
		cin >> input;
		if (input == "y")
		{
			draw = true;
		}
		if (input == "n")
		{
			draw = false;
		}
		if (draw == true)
		{
			drawCard();
			checkValue();
		}
		if (draw == false)
		{
			inPlay =false;
		}
		if (player > 21)
		{
			inPlay = false;
		}
	}
	endGame();
	
}
