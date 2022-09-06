//Created by Callum Watt
//v0.2

#include <iostream>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <windows.h>
#include <cstdlib>
using namespace std;

int upcard;
int dealer = 0;
int player = 0;
int money = 100;
int bet = 0;
int cardGen;
int card;
int value;
int dealerCard;
int games;
int wagered;
int playerAce;
int dealerAce;
int playerCardsDealt;
int dealerCardsDealt;
int option;
int baltop;
bool inPlay = true;
bool dealerLoop = true;
bool draw;
bool dealerDraw;
bool enabled;
bool playerBlackjack;
bool dealerBlackjack;
string input;
string confirm;
string nexti;

int drawCard() { //draws a card for player
	srand((unsigned int)time(0)); //uses random number generator seed
	cardGen = rand() % 52 + 1; //generates a random number between 1-52 (decides where in the deck the card might be)
	cout << "Drawing players card..." << "\n";
	Sleep(1000);
	if (cardGen > 35) //if the card is in the last 16 in the deck, it should be a 10
	{
		card = 10;
	}
	if (cardGen <= 35 && cardGen > 4) //if the card is anything else that isn't a 10 or an ace then creaets random number between
	{
		card = rand() % 9 + 2;
	}
	if (cardGen <= 4) //if card is the first 4 then ace is drawn
	{
		playerAce++;
		card = 11;
	}
	playerCardsDealt++; //adds to player cards dealt (checks for blackjack really)
	cout << "Player drew - " << card << "\n";
	return card;
}

int dealerNewCard() { //same as above, really should've used a different lazier way to do this
	srand((unsigned int)time(0));
	cardGen = rand() % 52 + 1;
	cout << "Drawing dealers card..." << "\n";
	Sleep(1000);
	if (cardGen > 35)
	{
		card = 10;
	}
	if (cardGen <= 35 && cardGen > 4)
	{
		card = rand() % 9 + 2;
	}
	if (cardGen <= 4)
	{
		dealerAce++;
		card = 11;
	}
	dealerCardsDealt++;
	cout << "Dealer drew - " << card << "\n";
	return dealerCard;
}

int checkValue() { //checks the player total
	player = card + player; //adds last card drawn to the total
	if (player > 21) //checks if player total is above 21
	{
		if (playerAce > 0) { //if the player has an ace, can take 10 from total
			player = player - 10;
			playerAce--;
		}
		else {
			cout << "You have busted" << "\n"; //player busts without any aces left
			return 0;
		}
	}
	if (player == 21 && playerCardsDealt == 2) //checks for Blackjack
	{
		playerBlackjack = true;
	}
	return player;
}

int dealerCheckValue() { //same as above (really should've made this more optimal)
	dealer = card + dealer;
	cout << "Dealer total value: " << dealer << "\n";
	if (dealer > 21) {
		if (dealerAce > 0) {
			dealer = dealer - 10;
			dealerAce--;
		}
		else {
			cout << "Dealer went bust!" << "\n";
			return 0;
		}
	}
	return dealer;
}



void endGame() { //end of current game calculations
	if (playerBlackjack == false && dealerBlackjack == false) //checks for blackjack advantages firstly
	{
		while (dealer < 17) //dealer keeps drawing till 17
		{
			dealerNewCard();
			dealerCheckValue();
		}
		if (player > dealer && player <= 21) //checks if player has higher total
		{
			cout << "You win!" << "\n";
			money = bet + money;
		}
		if (player > 21)
		{
			cout << "You lose!" << "\n"; //checks if player went bust
			money = money - bet;
		}
		if (player < dealer && dealer <= 21) { //checks if player has lower total
			cout << "You lose!" << "\n";
			money = money - bet;
		}
		if (player < dealer && player < 21 && dealer > 21) //checks if dealer has gone bust
		{
			cout << "You win!" << "\n";
			money = bet + money;
		}
		if (player == dealer && player <= 21) { //checks if draw
			cout << "Push!" << "\n";
		}
		if (money <= 0) //checks balance incase bankrupt
		{
			cout << "You went bankrupt!" << "\n";
			enabled = false;
			inPlay = false;
		}
	}
	if (playerBlackjack == true && dealerBlackjack == false) //if player has blackjack pay
	{
		cout << "Blackjack!" << "\n";
		money = (bet * 2) + money;
		playerBlackjack = false;
	}
	if (playerBlackjack == false && dealerBlackjack == true) //if dealer has blackjack, player may have 21 but still loses if it wasn't a blackjack
	{
		cout << "Dealer has blackjack" << "\n";
		money = money - bet;
		dealerBlackjack = false;
	}
	if (playerBlackjack == true && dealerBlackjack == true) //if both have blackjack, push
	{
		cout << "Push!" << "\n";
		dealerBlackjack = false;
		playerBlackjack = false;
	}
	if (money > baltop) //checks top balance
	{
		baltop = money;
	}
	cout << "Type anything to continue" << "\n"; //makes player input to continue to the next round
	cin >> nexti;
	wagered = bet + wagered;
	player = 0;
	dealer = 0;
	inPlay = true;
	system("CLS");
}

void welcomeMessage() { //starts welcome message
	cout << "Welcome to blackjack" << "\n";
	cout << "Type 1 to play, Type 2 for rules, Type anything else to terminate." << '\n';
	cin >> option;
	system("CLS");
}

void rules() {
	system("CLS");
	cout << "Rules: " << '\n' << '\n';
	cout << "You must try to get the highest number up to 21 against the dealer, if you surpass 21 you will go bust." << '\n' << "Dealer always stands on 17 or above." << "\n";
	cout << "If you double your bet, one card can only be drawn and you must stand past that point." << "\n" << "Blackjack pays double, aces are equal to 11 or 1 depending on if you go over 21." << '\n';
}



int main() {
	welcomeMessage();
	if (option == 2) {
		rules();
	}
	if (option == 1) {
		while (enabled = true && money > 0)
		{
			cout << "Current balance: " << money << "\n";
			cout << "Please input bet" << "\n";
			cin >> bet;
			system("CLS");
			while (bet > money) {
				cout << "Error - You do not have enough funds for that!" << "\n";
				cout << "Please input bet" << "\n";
				cin >> bet;
			}
			cout << "Dealing cards" << "\n";
			drawCard();
			checkValue();
			drawCard();
			checkValue();
			dealerNewCard();
			dealerCheckValue();
			while (inPlay == true) {
				system("CLS");
				cout << "\n" << "Current value - " << player << "\n" << "Dealer upcard - " << dealer << "\n" << "Do you wish to draw? y/n or d for double:" << "\n" << flush;
				cin >> input;
				system("CLS");
				if (input == "y")
				{
					draw = true;
				}
				if (input == "n")
				{
					draw = false;
				}
				if (input == "d")
				{
					draw = true;
					bet = bet * 2;
					inPlay = false;
				}
				if (draw == true)
				{
					drawCard();
					checkValue();
				}
				if (draw == false)
				{
					inPlay = false;
				}
				if (player > 21)
				{
					inPlay = false;
				}
				Sleep(1000);
				system("CLS");
			}
			games++;
			endGame();
		}
		cout << "Final statistics: " << "\n" << "Wagered: " << wagered << "\n" << "Games: " << games << '\n' << "Top balance: " << baltop;
		return 0;
	}
}
