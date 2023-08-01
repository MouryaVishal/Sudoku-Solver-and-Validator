#include<bits/stdc++.h>
using namespace std;

class sudoku{
    int sudokuFrame[9][9];
	vector<vector<int>> ans;
private:
    void menu(){
		cout<<"\n======================\n";
		cout<<"    Sudoku Solver\n";
		cout<<"======================\n\n";

		cout<<"Welcome to Sudoku Solver!\n";
		cout<<"Before we start, \nPlease input the puzzle into this program.\n\n";
		cout<<"You can either:-\n";
		cout<<"\t1. Input the puzzle by entering the values manually. (Enter 1)\n";
		cout<<"\t2. Input the puzzle by reading a file with values in it. (Enter 2)\n";
		cout<<"\t   The file must not have a name > 20 characters.\n";
		cout<<"\t   The file must be in the same directory as this C++ file.\n";
		cout<<"\t   The file must have all 81 values seperated with spaces.\n";
		cout<<"\t   Blank cells must be filled in as 0 (eg; 1 0 0 2 0 0 ...).\n";
		cout<<"\t   --> ";

		int option;
		cin>>option;

		if(option==1) _readFrameValuesFromUser();
		else if(option==2) _readFrameValuesFromFile();
		else{
			while(true){
				cout<<"\nYou seem to have entered an invalid option. Try again.\n";
				cout<<"\t   --> ";
				cin>>option;

				if(option==1) _readFrameValuesFromUser();
				else if(option==2) _readFrameValuesFromFile();
				else continue;

				break;
			}
		}

	}


    
	private:void _readFrameValuesFromUser(){
		cout<<"\nEnter the specified value when prompted.\n";
		cout<<"Enter 0 if cell is empty.\n\n";
		int rowNum, colNum;
		for(rowNum=0; rowNum<9; rowNum++){ 
			for(colNum=0; colNum<9; colNum++){
				int enteredValue;

				cout<<"Enter value for cell["<<rowNum+1<<"]["<<colNum+1<<"] --> ";
				cin>>enteredValue;

				if(!(enteredValue>=0 && enteredValue<=9)){ //Upper Bound for input
					while(true){ // looping untill user put valid input
						cout<<"Oops! You seem to have entered a wrong value! Try again.\n";
						cout<<"Enter value for cell ["<<rowNum+1<<"]["<<colNum+1<<"] --> ";
						cin>>enteredValue;

						if(enteredValue>=0 && enteredValue<=9) break;
					}
				}
				sudokuFrame[rowNum][colNum]=enteredValue;
			}
			cout<<"-------\n"; 
		}
	}

    
	private:void _readFrameValuesFromFile(){

		char filename[30]; 
		cout<<"\nEnter the name of the file that contains the Sudoku Puzzle.\n";
		cout<<"\t   --> ";
		cin>>filename;


		//Opening file for reading.
		ifstream sudokuFile; 
		sudokuFile.open(filename,ios::in);
		
		int rowNum, colNum;

		for(rowNum=0; rowNum<9; rowNum++){ 
			for(colNum=0; colNum<9; colNum++){
				int readValue;
				sudokuFile>>readValue;

				if(!(readValue>=0 && readValue<=9)){
					cout<<"\nValue "<<((rowNum*9)+colNum+1)<<" in "<<filename;
					cout<<" seems to be wrong! Correct the value and try again!\n";
					exit(EXIT_FAILURE);
				}

				sudokuFrame[rowNum][colNum]=readValue;
				if(sudokuFile.eof()) break;
			}
		}
		sudokuFile.close();
	}

public:
	
    sudoku(){
        menu();
		ans.resize(9,vector<int>(9,0));
		for(int i=0;i<9;i++){
			for(int j=0;j<9;j++){
				ans[i][j]=sudokuFrame[i][j];
			}
		}
    }
    void solveSudoko(){

        if(isValidSudoko()==false){
            cout<<"Your have input wrong Sudoko Frame!!!";
        }else{
			// for(int i=0;i<9;i++){
			// 	for(int j=0;j<9;j++){
			// 		ans[i][j]=sudokuFrame[i][j];
			// 	}
			// }
            helperSolve(ans);
            displayFrame();
        }
        
    }

    bool isValidSudoko(){
        unordered_map<string,bool> mp;
        for(int i=0;i<9;i++){
            for(int j=0;j<9;j++){
                if(sudokuFrame[i][j]!=0){
                    string row=to_string(sudokuFrame[i][j])+'r'+to_string(i);
                    string col=to_string(sudokuFrame[i][j])+'c'+to_string(j);
                    string box=to_string(sudokuFrame[i][j])+'r'+to_string(i/3)+'c'+to_string(j/3);
                    if(mp[row] || mp[col]|| mp[box]){
                        return false;
                    }else{
                        mp[row]=mp[col]=mp[box]=1;
                    }
                }
            }
        }
        return true;
    }

    bool helperSolve(vector<vector<int>>&ans){
        for(int i=0;i<9;i++){
            for(int j=0;j<9;j++){
                if(ans[i][j]==0){
                    for(int c=1;c<=9;c++){
                        if(isValidChar(i,j,c)){
                            ans[i][j]=c;
                            if(helperSolve(ans)){
                                return true;
                            }
                            	ans[i][j]=0;
							
                        }
                    }

                    return false;
                }
            }
        }

        return true;
    }


    bool isValidChar(int &row,int &col,int &c){
        // cout<<"weW"<<endl;
        for(int i=0;i<9;i++){
            if(ans[i][col]==c){
                return false;
            }
            if(ans[row][i]==c){
                return  false;
            }
            if(ans[3*(row/3)+i/3][3*(col/3)+i%3]==c){
                return false;
            }
        }
        return true;
    }

    public:void displayFrame(){

		cout<<"\033[0;36m++=====================================++";
		int rowNum, colNum;

		for(rowNum=0; rowNum<9; rowNum++){
			int cellIter=1;

			cout<<"\n\033[0;36m||";
			for(colNum=0; colNum<9; colNum++){
				if(cellIter==3){
					cout<<"\033[0m "<<ans[rowNum][colNum]<<" ";
					cout<<"\033[0;36m||";
					cellIter=1;
				}
				else{
					cout<<"\033[0m "<<ans[rowNum][colNum]<<"  ";
					cellIter++;	
				}
			}

			if(rowNum%3!=2) cout<<"\n\033[0;36m++-----------++-----------++-----------++";
			else cout<<"\n\033[0;36m++=====================================++";
		}

	}
};


int main(){
    sudoku obj;
    obj.solveSudoko();
}