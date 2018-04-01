#include <iostream>
using namespace std;



int main(){
	const int LENGTH = 9;
	
	char matrix[9][9];
	string temp;
	for (int line = 0; line < LENGTH; line++){
		cin >> temp;
		if (temp.size() < LENGTH){
			line--;
			continue;
		}
		int col = 0;
		for(int index = 0; index < temp.size(); index++){
			if(col >= LENGTH)
				return -1;
			if(isdigit(temp[index])){
				matrix[line][col++] = temp[index];
			}else if(temp[index] == '?'){
				matrix[line][col++] = '0';
			}else if(temp[index] == ' '){
				continue;
			}else{
				return -1;
			}
		}	

	}

		
	for(int line = 0; line < LENGTH; line++){
		for(int col = 0; col < LENGTH; col++){
			cout << matrix[line][col];
		}
		cout << "\n";
	}
	return 0;
}
