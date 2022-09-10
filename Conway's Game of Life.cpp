#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

//based on the number of alive neighbors, move the cell to next gen.
char cell_nextGen(char current, int alive_num){
    if (current == '-' && alive_num == 3){
        return '*';
    }
    if (current == '*'){
        if (alive_num < 2 || alive_num > 3){
            return '-';
        }
    }
    return current;
}

//chekc if the current cell runs out of the boundary
//note that size_t is unsigned 
bool sorrounding_check(size_t r, size_t c,
size_t num_of_rows, size_t number_of_cols){
    if (r > (num_of_rows - 1)){
        return false;
    }
    else if (c > (number_of_cols - 1)){
        return false;
    }
    return true;
}

//display current cell world
void display(const vector<string>& cell_world){
    for (size_t i = 0; i < cell_world.size(); ++i){
        cout << cell_world[i] << endl;
    }
    cout << "====================" << endl;
}


void pass_gens(size_t num_of_gens){
    vector<string> cell_world;
    fstream life("life.txt");
    if (!life) { 
        cerr << "Could not open the file.\n";
        exit(1);
    }

    //take the life.txt as a vector<string> input
    string line;
    cout << "Gen 0 Cell World:" << endl;
    while (getline(life, line)){
        cout << line << endl;
        cell_world.push_back(line);
    }
    life.close();
    //get number of rows an cols.
    size_t cols = cell_world[0].size();
    size_t rows = cell_world.size();
    for (size_t k = 0; k < num_of_gens; ++k){
        //set the nextGen cell world to the initial cell world so that they share the same number of cols and rows.
        vector<string> cell_world_nextGen = cell_world;
        for (size_t r = 0; r < rows; ++r){  
            //check for every cell's surroundings, change them accordingly.  
            for (size_t c = 0; c < cols; ++c){
                int alive_num = 0;
                if (sorrounding_check(r-1, c-1, rows, cols) &&
                    cell_world[r-1][c-1] == '*'){
                        ++alive_num;
                }
                if (sorrounding_check(r-1, c, rows, cols) &&
                    cell_world[r-1][c] == '*'){
                        ++alive_num;
                }
                if (sorrounding_check(r-1, c+1, rows, cols) &&
                    cell_world[r-1][c+1] == '*'){
                        ++alive_num;
                }
                if (sorrounding_check(r, c-1, rows, cols) &&
                    cell_world[r][c-1] == '*'){
                        ++alive_num;
                }
                if (sorrounding_check(r, c+1, rows, cols) &&
                    cell_world[r][c+1] == '*'){
                        ++alive_num;
                }
                if (sorrounding_check(r+1, c-1, rows, cols) &&
                    cell_world[r+1][c-1] == '*'){
                        ++alive_num;
                }
                if (sorrounding_check(r+1, c, rows, cols) &&
                    cell_world[r+1][c] == '*'){
                        ++alive_num;
                }
                if (sorrounding_check(r+1, c+1, rows, cols) &&
                    cell_world[r+1][c+1] == '*'){
                        ++alive_num;
                } 
                //after obtaining each cell's next generation, reshape each cell.       
                cell_world_nextGen[r][c] = cell_nextGen(cell_world[r][c], alive_num);
            }
        }
        //reset cell world
        cell_world = cell_world_nextGen;
        cout << "====================" << endl;
        cout << "Generation: " << k + 1 << endl;
        //display current cell world
        display(cell_world_nextGen);
    }
}

int main(){
    size_t x;
    cout << "How many gens? (greater or equal to 1)" << endl;
    cin >> x;
    pass_gens(x);
    return 0;
}

