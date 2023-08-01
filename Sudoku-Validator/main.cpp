#include<iostream>
#include<fstream>
using namespace std;

class SudokuFrame{

	int sudokuFrame[9][9];

	public:SudokuFrame(){
		menuForUser();
	}
	
	private:void menuForUser(){

                cout<<"\n======================\n";
                cout<<"   Sudoku Validator\n";
                cout<<"======================\n\n";

                cout<<"Welcome to Sudoku Validator!\n";
                cout<<"Before we start,\n PLease input the puzzle into this program.\n\n";
                cout<<"You can either:-\n";
                cout<<"\t1. Input the puzzle by entering the values manually. (Enter 1)\n";
                cout<<"\t2. Input the puzzle by reading a file with values in it. (Enter 2)\n";
                cout<<"\t   The file must not have a name > 30 characters.\n";
                cout<<"\t   The file should be in  same directory as this C++ file.\n";
                cout<<"\t   The file must have all 81 values seperated with spaces.\n";
                cout<<"\t   Blank cells must be filled in as 0 (eg; 1 2 9 8 1 9 ...).\n";
                cout<<"\t   --> ";

                int option;
                cin>>option;

                if(option==1) readFrameValuesFromUser();
                else if(option==2) readFrameValuesFromFile();
                else{
                        while(true){
                                cout<<"\nYou entered an invalid option. \nPlease!! Try again.\n";
                                cout<<"\t   --> ";
                                cin>>option;

                                if(option==1) readFrameValuesFromUser();
                                else if(option==2) readFrameValuesFromFile();
                                else continue;

                                break;
                        }
                }

        }

        private:void readFrameValuesFromUser(){
                cout<<"\nEnter the specified value when prompted.\n";
                cout<<"Enter 0 if cell is empty.\n\n";

		int rowNum, colNum;

                for(rowNum=0; rowNum<9; rowNum++){ 
                        for(colNum=0; colNum<9; colNum++){
                                int enteredValue;

                                cout<<"Enter value for cell["<<rowNum+1<<"]["<<colNum+1<<"] --> ";
                                cin>>enteredValue;

                                if(!(enteredValue>=1 && enteredValue<=9)){ 
                                        while(true){ 
                                                cout<<"Oops! You seem to have entered a wrong value! Try again.\n";
                                                cout<<"Enter value for cell ["<<rowNum+1<<"]["<<colNum+1<<"] --> ";
                                                cin>>enteredValue;

                                                if(enteredValue>=1 && enteredValue<=9) break;
                                        }
                                }

                                sudokuFrame[rowNum][colNum]=enteredValue;
                        }
                        cout<<"-------\n"; 
                }
        }

	private:void readFrameValuesFromFile(){
		
		int rowNum, colNum;
		char filename[30];
		ifstream file;
		
		cout<<"\nEnter the name of the file which contains the puzzle --> ";
		cin>>filename;

		file.open(filename,ios::in);

		for(rowNum=0; rowNum<9; rowNum++){
			for(colNum=0; colNum<9; colNum++){

				int readValue;
				file>>readValue;

				sudokuFrame[rowNum][colNum]=readValue;

				if(file.eof()) break;

			}
		}
		
		// If there aren't 81 values in the file, then it is invalid.	
		if((colNum*rowNum)!=81){
			cout<<"Oops! The file doesn't have the required amount of values.\n";
			cout<<"Try again!\n";
			exit(EXIT_FAILURE);
		}

		file.close();

	}

	public:int getCellValue(int row, int col){
		return sudokuFrame[row][col];
	}

};


class SudokuValidator{

	SudokuFrame frame;
	
	public:SudokuValidator(){
		validateFrame();		
	}

	private:void validateFrame(){
		if(valuesAreValid()){
			if(rowsAreValid()){
				if(columnsAreValid()){
					if(ThreeByThreeSquaresAreValid()){
						cout<<"\nYour puzzle is valid!\n\n";
					}
					else cout<<"Your puzzle is invalid!\n";
				}
				else cout<<"Your puzzle is invalid!\n";
			}
			else cout<<"Your puzzle is invalid!\n";
		}
		else cout<<"Your puzzle is invalid!\n";
	}

	private:bool valuesAreValid(){		
		int rowNum, colNum;

		for(rowNum=0; rowNum<9; rowNum++){
			for(colNum=0; colNum<9; colNum++){
				int cellValue=frame.getCellValue(rowNum,colNum);
				if(!(cellValue>=0 && cellValue<=9)) return false;
			}
		}

		return true;
	}

	private:bool rowsAreValid(){
		
		int rowNum, colNum, valIter;

		for(rowNum=0; rowNum<9; rowNum++){ 

			for(valIter=1; valIter<=9; valIter++){ 
				if(rowContains(rowNum,valIter)==false)
					return false;

			} 

		} 
		return true;
	}
	private:bool columnsAreValid(){
		
		int rowNum, colNum, valIter;
		
		for(colNum=0; colNum<9; colNum++){
		
			for(valIter=1; valIter<=9; valIter++){ 
				
				if(columnContains(colNum,valIter)==false)
					return false;

			} 

		} 
		
		return true;
	}
	
	
	private:bool ThreeByThreeSquaresAreValid(){
		
		int squareIter, valIter;

		for(squareIter=0; squareIter<9; squareIter++){ 
			
			for(valIter=1; valIter<=9; valIter++){ 

				if(squareContains(squareIter,valIter)==false)
					return false;

			} 

		} 
		
		return true;
	}


	private:bool rowContains(int row, int value){
		int colNum;
		for(colNum=0; colNum<9; colNum++){
			if(frame.getCellValue(row,colNum)==value)
				return true;
		}
		return false;
	}

	private:bool columnContains(int col, int value){
		int rowNum=0;
		for(rowNum=0; rowNum<9; rowNum++){
			if(frame.getCellValue(rowNum,col)==value)
				return true;
		}
		return false;
	}

	private:bool squareContains(int squareNumber, int value){
		int rowStart=(squareNumber/3)*3;
		int rowEnd=rowStart+2;
		
		int colStart=(squareNumber%3)*3;
		int colEnd=colStart+2;

		int rowNum, colNum;
		for(rowNum=rowStart; rowNum<=rowEnd; rowNum++){
			for(colNum=colStart; colNum<=colEnd; colNum++){
				if(frame.getCellValue(rowNum,colNum)==value)
					return true;
			}
		}

		return false;
	}

};


int main(){
	SudokuValidator s;
	return 0;
}