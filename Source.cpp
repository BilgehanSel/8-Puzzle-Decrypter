#include <iostream>
#include <string>
#include <vector>


using namespace std;



vector <vector<int>> aim = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 0 } };
vector <vector<int>> init = { { 1, 2, 3 }, { 0, 6, 8 }, { 4, 7, 5 } };

string result_string;

bool solved = false;

vector <pair<vector<vector<int>>, string>> storage;



void Display_vector(vector<vector<int>> vector) {
	for (unsigned i = 0; i < vector.size(); i++) {
		for (unsigned j = 0; j < vector[i].size(); j++) {
			cout << vector[i][j] << " ";
		}
		cout << endl;
	}
	cout << "-------------" << endl;
}



void Swaps(pair<vector<vector<int>>, string> puzzle) {
	vector<vector<int>> num = puzzle.first;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			num = puzzle.first;
			if (num[i][j] == 0) {
				//UP
				if (j - 1 >= 0 && (puzzle.second[puzzle.second.size() - 1] != '2' || puzzle.second.size() == 1)) {
					swap(num[i][j - 1], num[i][j]);
					if (aim == num) {
						//cout << "Solved :D" << endl;
						//Display_vector(num);
						solved = true;
						pair<vector<vector<int>>, string> temp;
						temp.first = num;
						temp.second = puzzle.second + "1";
						result_string = temp.second;
						storage.push_back(temp);
						return;
					}
					else if (true) {
						pair<vector<vector<int>>, string> temp;
						temp.first = num;
						temp.second = puzzle.second + "1";
						storage.push_back(temp);
					}
				}

				//DOWN
				num = puzzle.first;
				if (j + 1 <= 2 && (puzzle.second[puzzle.second.size() - 1] != '1' || puzzle.second.size() == 1)) {
					swap(num[i][j + 1], num[i][j]);
					if (aim == num) {
						//cout << "Solved :D" << endl;
						//Display_vector(num);
						solved = true;
						pair<vector<vector<int>>, string> temp;
						temp.first = num;
						temp.second = puzzle.second + "2";
						result_string = temp.second;
						storage.push_back(temp);
						return;
					}
					else if (true) {
						pair<vector<vector<int>>, string> temp;
						temp.first = num;
						temp.second = puzzle.second + "2";
						storage.push_back(temp);
					}
				}
				//LEFT
				num = puzzle.first;
				if (i - 1 >= 0 && (puzzle.second[puzzle.second.size() - 1] != '4' || puzzle.second.size() == 1)) {
					swap(num[i - 1][j], num[i][j]);
					if (aim == num) {
						//cout << "Solved :D" << endl;
						//Display_vector(num);
						solved = true;
						pair<vector<vector<int>>, string> temp;
						temp.first = num;
						temp.second = puzzle.second + "3";
						result_string = temp.second;
						storage.push_back(temp);
						return;
					}
					else if (true) {
						pair<vector<vector<int>>, string> temp;
						temp.first = num;
						temp.second = puzzle.second + "3";
						storage.push_back(temp);
					}
				}

				//RIGHT
				num = puzzle.first;
				if (i + 1 <= 2 && (puzzle.second[puzzle.second.size() - 1] != '3' || puzzle.second.size() == 1)) {
					swap(num[i + 1][j], num[i][j]);
					//Display_vector(num);
					if (aim == num) {
						//cout << "Solved :D" << endl;
						//Display_vector(num);
						solved = true;
						pair<vector<vector<int>>, string> temp;
						temp.first = num;
						temp.second = puzzle.second + "4";
						result_string = temp.second;
						storage.push_back(temp);
						return;
					}
					else if (true) {
						pair<vector<vector<int>>, string> temp;
						temp.first = num;
						temp.second = puzzle.second + "4";
						storage.push_back(temp);
					}
				}
				return;
			}
		}
	}
}

///Converting the encrypted message;
int convert(int ascii, int minus) {
	if (ascii - minus >= 0) {
		return (ascii - minus);
	}
	else {
		return (95 - ((minus - ascii) % 95));
	}
}



int main() {
	string encrypted;
	cout << "Enter the encrypted message: ";
	getline(cin, encrypted);
	//cout << endl;
	string pass;
	cout << "Enter the password: ";
	cin >> pass;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			char temp_char = pass[j * 3 + i];
			int temp_int = temp_char;
			temp_int -= 48;
			init[j][i] = temp_int;
		}
	}





	//Display_vector(init);
	pair <vector<vector<int>>, string> temp;
	temp.first = init;
	temp.second = "1";
	storage.push_back(temp);

	int floor = 1;
	int size;

	while (!solved) {
		size = storage.size();
		for (int i = size - 1; i >= 0; i--) {
			if (storage[i].second.size() == floor) {
				Swaps(storage[i]);
				//Sleep(1000);
				if (solved) {
					break;
				}
			}
			else {
				break;
			}
		}
		floor++;
	}

	vector<vector<vector<int>>> answers;

	for (int i = result_string.size(); i >= 1; i--) {
		string temp = result_string.substr(0, i);
		for (unsigned j = storage.size() - 1; j >= 0; j--) {
			if (storage[j].second == temp) {
				answers.push_back(storage[j].first);
				break;
			}
		}
	}

	vector<int> values;

	for (int k = 0; k < answers.size(); k++) {
		int sum = 0;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				sum += answers[k][i][j] * ((j * 3) + (i + 1));
			}
		}
		values.push_back(sum);
	}
	vector<int> values_copy = values;
	if (encrypted.size() > values_copy.size()) {
		for (int i = 0; i < encrypted.size() / values_copy.size(); i++) {
			for (int j = 0; j < values_copy.size(); j++) {
				values.push_back(values_copy[j]);
			}
		}
		for (int i = 0; i < encrypted.size() % values_copy.size(); i++) {
			values.push_back(values_copy[i]);
		}
	}


	char ch;
	int ascii;
	string text;

	for (int i = 0; i < encrypted.size(); i++) {
		ch = encrypted[i];
		ascii = ch;

		ascii = convert(ascii - 32, values[i]);
		if (ascii == 95) {
			ascii = 0;
		}
		ch = static_cast<char>(ascii + 32);
		text += ch;
	}
	//cout << endl;
	cout << "The original text is: " << text << endl;

	return 0;
}
