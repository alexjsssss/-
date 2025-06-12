
#include <iostream>
#include <ctime>
using namespace std;

//розміри поля
int board[11][11], used[11][11];

int row[] = {-1, -1, -1, 0, 0, 1, 1, 1};
int col[] = {-1, 0, 1, -1, 1, -1, 0, 1 };

//гравці
string player1, player2;

int moves;

void fill_board() {

	for (int i = 0; i < 11; ++i) {
		board[0][i] = -1;
		board[i][0] = -1;
		board[10][i] = -1;
		board[i][10] = -1;
	}

	// міни
	srand(time(0));
	int mines = 0;
	while (mines < 10) {
		int x = rand() % 9 + 1;
		int y = rand() % 9 + 1;
		if (board[x][y] != 9) {
			board[x][y] = 9;
			for (int i = 0; i < 8; ++i) {
				if (board[x + row[i]][y + col[i]] != -1 && board[x + row[i]][y + col[i]] != 9) {
					board[x + row[i]][y + col[i]]++;
				}
			}
			mines++;
		}
	}
}
//поле яке ми бачимо, налаштування границі
void print_board() {
	for (int i = 0; i < 11; ++i) {
		for (int j = 0; j < 11; ++j) {
			if(used[i][j]) { 
				cout << board[i][j] << ' '; 
			}
			else {
				cout << 'x' << ' ';
			}
		
		}
		cout << endl;
	}
}

// ввід нікнеймів, задаємо функцію
void enter_players_names() {
	cout << "Enter name for player1: \n";
	cin >> player1;
	cout << "Enter name for player2: \n";
	cin >> player2;
}

//хто за ким ходить (1 гравець, 2 гравець)
pair <int, int>  next_move() {
		bool valid = false;
		int cur_row, cur_col;
		while (!valid) {
			int turn = -1;
			if (moves % 2 == 0) {
				turn = 1;
				cout << "Player1, ";
			}
			else {
				turn = 2;
				cout << "Player2, ";
			}
		}


		cout << "Enter your move (row[1-9] column[1-9]): ";
		cin >> cur_row >> cur_col;

		// задаємл обмеження, виводимо попередження
		if (cur_row > 9 || cur_row < 1 || cur_col > 9 || cur_col < 1 || used[cur_row][cur_col]) {
			cout << "Invalid move. Please, try again: ";
		}
		else {
			valid = true;
		}
	}
	return { cur_row, cur_col };
}

	void recursion(int move_row, int move_col) {
		for (int = 0; i < 8; ++i) {
			if(board[move_row + row[i]][move_col + col[i]] > 0 && board[move_row + row[i]][move_col + col[i]] < 9 ){
				used[board[move_row + row[i]][move_col + col[i]] = true;
			} else if(board[move_row + row[i]][move_col + col[i]] == 0){
				recursion(move_row + row[i], move_col + col[i]);
	}
}

	void game() {
		pair <int, int> move = next_move();
		int move_row = move.first;
		int move_col = move.second;
		if (board[move_row][move_col] == 9) {
			cout << " Oops! ";
			if (moves % 2 == 0) {
				turn = 1;
				cout << "player1";
			}
			else {
				turn = 2;
				cout << "player2";
			}
			cout << "Lose. Would you like to try again? (Y/N): ";
			char re;
			cin >> re;
			if (re == 'Y') {
				restart();
			}
			else if (re == 'N') {
				exit(0);
			}
			else {
				bool good = false;
				while (!good) {
					cout << "You have entered wrong value. Answer again. Would you like to try again? (Y/N): "
						cin >> re;
					if (re == 'Y' || re == 'N') {
						good == true;
					}
				}
				if (re == 'Y') {
					restart();
				}
				else if (re == 'N') {
					exit(0);
				}
			}
		}
		else if (board[move_row][move_col] == 0) {
			used[move_row][move_col] = true;
			recursion(move_row, move_col);
		} else {
			used[move_row][move_col] = true;
	}
		moves++;
		game();
}

	void restart() {
		cout << "---------------------------------------------\nNew game:\n";

		enter_players_names();

		fill_board();

		game();

	}

int main() {
#ifdef LOCAL
	freopen("input.in", "r", stdin);
	freopen("output.in", "w", stdout);
#endif
	restart();

	print_board();
	return 0;
}