#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <time.h>
#include <cstdlib>

using namespace std;

bool changes = true;
bool Game_On = true;
int seed = time(NULL);
int board[4][4];

enum Keys {
	L_UP =  119, L_DOWN = 115, L_LEFT = 97, L_RIGHT = 100, U_UP = 87, U_DOWN=83, U_LEFT=65, U_RIGHT=68
};

void Game_State() {

	int Sqr_Num = 0;

	for (int h = 0; h < 4; h++) { // horizontal value
		for (int v = 0; v < 4; v++) { //vertical value
		
			if (board[v][h] != 0) {
				Sqr_Num++;
			}
			if (Sqr_Num == 16) {
				Game_On = false;
			}

		}
	}

}

void draw() {
	system("CLS");
	int score = 0;
	for (int v = 0; v < 4; v++) {
		for (int h = 0; h < 4; h++) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112);
			score += board[v][h];
		}
	}
	cout << "Score:" << score << endl;

	for (int v = 0; v < 4; v++) {
		cout << " ------ ----- ----- ------" << endl;
		for (int h = 0; h < 4; h++) {
			if (board[v][h] == 0) {
				cout << " |  " << (char)board[v][h] << " ";
			}
			else if ((int)board[v][h] == 16 || (int)board[v][h] == 32 || (int)board[v][h] == 64) {
				cout << " | " << board[v][h] << " ";
			}

			else if ((int)board[v][h] == 128 || (int)board[v][h] == 256 || (int)board[v][h] == 512) {
				cout << " | " << board[v][h] << "";
			}

			else if ((int)board[v][h] == 1024 || (int)board[v][h] == 2048) {
				cout << " |" << board[v][h] << "";
			}

			else {
				cout << " |  " << (int)board[v][h] << " ";
			}
		}
		cout << " |" << endl;
	}
	cout << " ------ ----- ----- ------" << endl;
}

void new_block() {
	if(changes == true){
		while (true) {
			srand(seed);
			seed++;
			int Vertic = rand() % 4;
			srand(seed);
			seed++;
			int Horiz = rand() % 4;
			cout << Vertic << Horiz << endl;
			seed++;
			if (board[Vertic][Horiz] == 0) {
				board[Vertic][Horiz] = 2;
				draw();
				changes = false;
				break;
			}
		}
	}
	else {
		
		cout << "Try a different key" << endl;
		return;
	}
}

void logic() {

	while (Game_On){

		new_block(); //after you type in the wrong key how do you get a new block to appear
		int UserInput = _getch();
		_getch();
		switch (UserInput)
		{
		case L_UP:
		case U_UP:
			
			for (int h = 0; h < 4; h++) { // horizontal value

				for (int v = 1; v < 4; v++) { //vertical value

					if (board[v][h] != 0) {//check for block having a value

						for (int i = 0; i < 3; i++) {

							for (int i = 1; i < v + 1; i++) {
								//(v+1) indicates by how many more blocks a value can be raised

								if (board[v - i][h] == 0) { // moving the block up
									board[v - i][h] = board[v - (i - 1)][h];
									board[v - (i - 1)][h] = 0;
									changes = true;
								}
								else if (board[v - i][h] == board[v - (i - 1)][h]) { // addition

									board[v - i][h] = 2 * (board[v - i][h]);
									board[v - (i - 1)][h] = 0;
									changes = true;
								}
							}
						}
					}
				}
			}
			draw();
			break;

		case L_DOWN:
		case U_DOWN:// first block doesn't always move - figure out why

			for (int h = 0; h < 4; h++) { // horizontal value

				for (int v = 0; v < 3; v++) { //vertical value

					if (board[v][h] != 0) {//check for block having a value

						for (int i = 0; i < 3; i++) {
							for (int i = 1; i < 4 - v; i++) {
								//(4-v) indicates by how many blocks a value can be lowered

								if (board[v + i][h] == 0) { // moving the block down
									board[v + i][h] = board[v + (i - 1)][h];
									board[v + (i - 1)][h] = 0;
									changes = true;
								}
								else if (board[v + i][h] == board[v + (i - 1)][h]) { // addition
									board[v + i][h] = 2 * (board[v + i][h]);
									board[v + (i - 1)][h] = 0;
									changes = true;
								}
							}
						}
					}
				}
			}
			draw();
			break;

		case L_RIGHT:
		case U_RIGHT:

			for (int h = 0; h < 3; h++) { // horizontal value

				for (int v = 0; v < 4; v++) { //vertical value

					if (board[v][h] != 0) {//check for block having a value

						for (int i = 0; i < 3; i++) {
							for (int i = 1; i < 4 - h; i++) {
								//(h-4) indicates by how many blocks a val can be moved to the right

								if (board[v][h + i] == 0) { // moving the block to the right
									board[v][h + i] = board[v][h + (i - 1)];
									board[v][h + (i - 1)] = 0;
									changes = true;
								}
								else if (board[v][h + i] == board[v][h + (i - 1)]) { // addition
									board[v][h + i] = 2 * (board[v][h + i]);
									board[v][h + (i - 1)] = 0;
									changes = true;
								}
							}
						}
					}
				}
			}
			draw();
			break;

		case L_LEFT:
		case U_LEFT:
	
			for (int h = 1; h < 4; h++) { // horizontal value

				for (int v = 0; v < 4; v++) { //vertical value

					if (board[v][h] != 0) {//check for block having a value

						for (int i = 0; i < 3; i++) {
							for (int i = 1; i < h + 1; i++) {
								//(v+1) indicates by how many blocks a value can be moved to the left

								if (board[v][h - i] == 0) { // moving the block up
									board[v][h - i] = board[v][h - (i - 1)];
									board[v][h - (i - 1)] = 0;
									changes = true;
								}
								else if (board[v][h - i] == board[v][h - (i - 1)]) { // addition

									board[v][h - i] = 2 * (board[v][h - i]);
									board[v][h - (i - 1)] = 0;
									changes = true;
								}
							}
						}
					}
				}
			}
			draw();
			break;
	
		default:
			
			cout << "W - UP" << endl;
			cout << "S - DOWN" << endl;
			cout << "D - RIGHT" << endl;
			cout << "A - LEFT" << endl;

			changes = false;
			break;
		}
		Game_State();
	}

}

int main() {
	
	new_block();
	changes = true;
	new_block();
	changes = true;
	logic();

}