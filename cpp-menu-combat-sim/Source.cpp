/*Author: Jill Russell
CIS 115 - Fundamentals of Programming
Menu Driven Combat Simulator
*/

#include <conio.h>
#include <iostream>
#include <iomanip>
#include "CIS115-P02S - Menu Driven Combat Simulator.h"

using namespace std;


//constants
//for loops
#define GAME_ONGOING	1
#define GAME_OVER		0
#define TRUE			1
#define FALSE			0

//for menu selections
#define MENU_LOWEST		1
#define MENU_ATTACK		1
#define MENU_HEAL		2
#define MENU_HIGHEST	2


//for calculations
const int DEAD_HP = 0;
const int BASE_DAMAGE_MIN = 1;
const int BASE_DAMAGE_MAX = 10;
const int HEAL_MIN = 3;
const int HEAL_MAX = 25;
const int MIN_HIT_CHANCE = 0;
const int MAX_HIT_CHANCE = 100;
const int HIT_THRESHOLD = 20;
const int CRIT_THRESHOLD = 80;

//function prototypes
void BattleScreen(int, int);
void PlayerAttack(int&);
void PlayerHeal(int&);
void EnemyAttack(int&);

int main() {
	//declare variables
	int gameProgress = GAME_ONGOING;
	int playerHP = 100;
	int enemyHP = 100;
	int selectAction = 0;


	//rng function call
	SeedRNGToSystemClock();
	

	while (gameProgress == GAME_ONGOING) {

		//Display menu to player
		BattleScreen(playerHP, enemyHP);

		cout << "Select an action..." << endl << "1.) Attack" << endl << "2.) Heal" << endl << ":";
		cin >> selectAction;


		//verify action selection
		while (cin.fail() == TRUE || selectAction < MENU_LOWEST || selectAction > MENU_HIGHEST) {
			cout << "This is not a valid menu selection." << endl;
			cin.clear();
			rewind(stdin);
			selectAction = 0;
			cout << endl << "Select an action..." << endl << "1.) Attack" << endl << "2.) Heal" << endl << ":";
			cin >> selectAction;
		}


		//if player attacks
		if (selectAction == MENU_ATTACK) {
			PlayerAttack(enemyHP);
		}

		//if player heals
		if (selectAction == MENU_HEAL) {
			PlayerHeal(playerHP);
		}

		//if results in enemy 0 hp - end game
		if (enemyHP <= DEAD_HP) {
			cout << "You have defeated the enemy!" << endl;
			gameProgress = GAME_OVER;
		}

		//enemy attacks after player turn
		if (gameProgress == GAME_ONGOING && (selectAction == MENU_ATTACK || selectAction == MENU_HEAL)) {
			EnemyAttack(playerHP);
		}


		//if results in player 0 hp - end game
		if (playerHP <= DEAD_HP) {
			cout << "You have been defeated. RIP" << endl;
			gameProgress = GAME_OVER;
		}


		_getch();
		ClearScreen();

	}


	return 0;

}

//function definitions

//HP display
void BattleScreen(int playerHP, int enemyHP) {
	cout << left << setw(10) << "Player HP" << ": " << playerHP << endl;
	cout << setw(10) << "Enemy HP" << ": " << enemyHP << endl;
	
}


//Attack - 20% chance of miss - if hit, 1-10 damage - 20% of hits are critical, multiples damage by 2.5 then also add 5 (2.5d + 5)
void PlayerAttack(int& enemyHP) {
	int attackDamage = 0;
	int hitSuccess = 0;
	int critSuccess = 0;
	int baseDamage = 0;

	baseDamage = generateRandomValue(BASE_DAMAGE_MIN, BASE_DAMAGE_MAX);
	hitSuccess = generateRandomValue(MIN_HIT_CHANCE, MAX_HIT_CHANCE);

	if (hitSuccess < HIT_THRESHOLD) {
		cout << "You miss" << endl;
	}

	if (hitSuccess > HIT_THRESHOLD) {
		critSuccess = generateRandomValue(MIN_HIT_CHANCE, MAX_HIT_CHANCE);
	}

	if (hitSuccess > HIT_THRESHOLD && critSuccess > CRIT_THRESHOLD) {
		attackDamage = (2.5 * baseDamage) + 5;
		enemyHP = enemyHP - attackDamage;
		cout << "Critical hit! You hit for " << attackDamage << " damage" << endl;
	}

	if (hitSuccess > HIT_THRESHOLD && critSuccess < CRIT_THRESHOLD) {
		attackDamage = baseDamage;
		enemyHP = enemyHP - attackDamage;
		cout << "You hit for " << attackDamage << " damage" << endl;
	}

}

//Heal - random between 3 and 25 - no attack
void PlayerHeal(int& playerHP) {
	int playerHeal = 0;
	playerHeal = generateRandomValue(HEAL_MIN, HEAL_MAX);
	cout << "You heal " << playerHeal << " HP" << endl;
	playerHP = playerHP + playerHeal;

}


//Enemy Attack - damage identical to player attack
void EnemyAttack(int& playerHP) {
	int attackDamage = 0;
	int hitSuccess = 0;
	int critSuccess = 0;
	int baseDamage = 0;

	baseDamage = generateRandomValue(BASE_DAMAGE_MIN, BASE_DAMAGE_MAX);
	hitSuccess = generateRandomValue(MIN_HIT_CHANCE, MAX_HIT_CHANCE);

	if (hitSuccess < HIT_THRESHOLD) {
		cout << "The enemy misses" << endl;
	}

	if (hitSuccess > HIT_THRESHOLD) {
		critSuccess = generateRandomValue(MIN_HIT_CHANCE, MAX_HIT_CHANCE);
	}

	if (hitSuccess > HIT_THRESHOLD && critSuccess > CRIT_THRESHOLD) {
		attackDamage = (2.5 * baseDamage) + 5;
		playerHP = playerHP - attackDamage;
		cout << "The enemy crits for " << attackDamage << " damage" << endl;
	}

	if (hitSuccess > HIT_THRESHOLD && critSuccess < CRIT_THRESHOLD) {
		attackDamage = baseDamage;
		playerHP = playerHP - attackDamage;
		cout << "The enemy hits for " << attackDamage << " damage" << endl;
	}

}