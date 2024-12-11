//Created by Callum Watt
//v0.3

#include <iostream>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <windows.h>
#include <cstdlib>
using namespace std;

int upcard;
int dealer;
int player;
int money = 100;
int bet;
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
int baltopGames;
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


string userInput() {
	system("CLS");
	cout << "\n" << "Current value - " << player << "\n"
		<< "Dealer upcard - " << dealer << "\n"
		<< "Do you wish to draw? y/n or d for double:" << "\n";
	cin >> input; // Accept user input
	return input;
}


int drawCard() { //draws a card for player
	srand((unsigned int)time(0)); //uses random number generator seed
	cardGen = rand() % 52 + 1; //generates a random number between 1-52 (decides where in the deck the card might be)
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
	cout << "Dealer total value: " << dealer << "\n" << "\n";
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



void endGame() {
	cout << "\n--- End of Hand ---\n";
	cout << "Player total: " << player << "\n";
	cout << "Dealer total: " << dealer << "\n";

	// Dealer finishes their turn if not already done
	while (dealer < 17 && dealer > 0) {
		dealerNewCard();
		dealerCheckValue();
	}

	// Check outcomes
	if (playerBlackjack && dealerBlackjack) {
		cout << "Both have blackjack! Push.\n";
	}
	else if (playerBlackjack) {
		cout << "Blackjack! You win 2x your bet.\n";
		money += (bet * 2);
	}
	else if (dealerBlackjack) {
		cout << "Dealer has blackjack. You lose your bet.\n";
		money -= bet;
	}
	else if (player > 21) {
		cout << "You busted. Dealer wins.\n";
		money -= bet;
	}
	else if (dealer > 21) {
		cout << "Dealer busted. You win!\n";
		money += bet;
	}
	else if (player > dealer) {
		cout << "You win!\n";
		money += bet;
	}
	else if (player < dealer) {
		cout << "Dealer wins.\n";
		money -= bet;
	}
	else {
		cout << "Push! It's a tie.\n";
	}

	// Update statistics
	if (money > baltop) {
		baltop = money;
		baltopGames = games;
	}
	wagered += bet;

	// Reset game state
	player = 0;
	dealer = 0;
	playerAce = 0;
	dealerAce = 0;
	playerBlackjack = false;
	dealerBlackjack = false;
	inPlay = true;
	Sleep(3000);
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
	cout << "Playing with an infinite deck shoe, card counting won't be possible." << '\n';
}

int createBet() {
	cout << "Current balance: $" << money << "\n";
	cout << "Please input bet" << "\n" << "$";
	cin >> bet;
	system("CLS");
	while (bet > money) {
		cout << "Error - You do not have enough funds for that!" << "\n";
		cout << "Please input bet" << "\n";
		cin >> bet;
	}
	return bet;
}

void finalStatistics() {
	cout << "Final statistics: " << "\n" << "Wagered: " << wagered << "\n" << "Games: " << games << '\n' << "Top balance: " << baltop << "Top balance game: " << baltopGames;
}

bool isInPlay() {
	if (input == "d") { // Double down
		if ((bet * 2) <= money) {
			bet = bet * 2; // Double the bet
			drawCard();
			checkValue(); // Check if the player busts
			inPlay = false; // End the turn
		}
		else {
			cout << "Not enough funds for double down.\n";
		}
	}
	if (input == "n") { // Stand
		inPlay = false; // End player's turn
	}
	if (player > 21) { // Player busts
		inPlay = false;
	}
	return inPlay;
}

bool isDraw() {
	if (input == "y")
	{
		draw = true;
	}
	if (input == "n")
	{
		draw = false;
	}
	if (input == "d") {
		draw = true;
	}
	return draw;
}

int i = 0;
int main() {
	welcomeMessage();
	if (option == 2) {
		rules();
	}
	if (option == 1) {
			while (i < 1000 && money > 0)
			{
				createBet();
				drawCard();
				checkValue();
				drawCard();
				checkValue();
				dealerNewCard();
				dealerCheckValue();
				while (inPlay) {
					userInput();
					isDraw();

					if (input == "d") { // Double down
						isInPlay();
					}
					else if (input == "y") { // Draw card
						drawCard();
						checkValue();
						isInPlay();
					}
					else if (input == "n") { // Stand
						isInPlay(); // Ends player turn, proceeds to dealer logic in endGame
					}

					Sleep(1000);
					system("CLS");
				}
				games++;
				endGame();
				i++;
			}
			finalStatistics();
			return 0;
		}
	}
