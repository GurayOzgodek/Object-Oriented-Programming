#ifndef Operator_grid_h
#define Operator_grid_h
#include "Arithmetic_operator.h"
#include <cmath>
#define MAX_OPERATOR_SIZE 100

class OperatorGrid{
    int grid_rows;
    int grid_cols;
    char **grid;
    int num_operators;
    ArithmeticOperator *operators[MAX_OPERATOR_SIZE];

    public:
        OperatorGrid(int rows, int cols);
        ~OperatorGrid();
        bool first = true;
        bool place_operator(ArithmeticOperator *);
        bool move_operator(int, int, char, int);
        bool border(char **, ArithmeticOperator *);
        bool conflict(char **, ArithmeticOperator *);
        bool is_there(ArithmeticOperator **, ArithmeticOperator *);
        void delete_operator(char **, ArithmeticOperator *);
        void print_operators();
};

OperatorGrid::OperatorGrid(int rows, int cols){
    grid_rows = rows;
    grid_cols = cols;
    num_operators = 0;
    grid = new char*[grid_rows];
    for(int i=0;i<grid_rows;i++){
        grid[i] = new char[grid_cols];
    }
}

OperatorGrid::~OperatorGrid(){
    for(int i=0;i<grid_rows;i++){
        delete [] grid[i];
    }
    delete [] grid;
    cout << "DESTRUCTOR: GIVE BACK[" << grid_rows << "," << grid_cols <<"] chars."<< endl;
    cout << "DESTRUCTOR: GIVE BACK[" << num_operators << "] Operators" << endl;

}

bool OperatorGrid::border(char **grid, ArithmeticOperator *oper){

    int x = oper->get_x();
    int y = oper->get_y();
    int size = oper->get_size();
    int sign = oper->get_sign();
    if(sign == '-'){
        if(y + size > grid_cols || y - size < 1 ) return false;
        else return true;
    } 
    if(y + size > grid_cols || y - size < 1) return false;
    if(x + size > grid_rows || x - size < 1) return false;

    return true;
}
bool OperatorGrid::conflict(char **grid, ArithmeticOperator *oper){

    int x = oper->get_x();
    int y = oper->get_y();
    int size = oper->get_size();
    int sign = oper->get_sign();

    if(sign == '+'){
        for(int i=0,j=0;i<oper->get_size()+1;i++,j--){ //merkezleri de kontrol etmek için get_size + 1 kadar dönüyor
            if(x+i <= grid_rows && x+j>=0 && y+i <= grid_cols && y+j>=0 ){
                if( grid[x-1+i][y-1] != '\0' || grid[x-1+j][y-1] != '\0' ) return false;
                if( grid[x-1][y-1+i] != '\0' || grid[x-1][y-1+j] != '\0' ) return false;                
            }

        }
        return true;
    }

    else if(oper->get_sign() == '-'){
        for(int i=0,j=0;i<oper->get_size()+1;i++,j--){ //merkezleri de kontrol etmek için get_size + 1 kadar dönüyor
            if(x+i <= grid_rows && x+j>=0 && y+i <= grid_cols && y+j>=0 ){
                if(grid[oper->get_x()-1][oper->get_y()-1+i] != '\0' || grid[oper->get_x()-1][oper->get_y()-1+j] != '\0' ) return false;
            }
            
        }
        return true;
    }

    else if(oper->get_sign() == 'x'){
        for(int i=0,j=0;i<oper->get_size()+1;i++,j--){ //merkezleri de kontrol etmek için get_size + 1 kadar dönüyor
            if(x+i <= grid_rows && x+j>=0 && y+i <= grid_cols && y+j>=0 ){
                if(grid[oper->get_x()-1+i][oper->get_y()-1+i] != '\0' || grid[oper->get_x()-1+j][oper->get_y()-1+j] != '\0' ) return false;
                if(grid[oper->get_x()-1+i][oper->get_y()-1+j] != '\0' || grid[oper->get_x()-1+j][oper->get_y()-1+i] != '\0' ) return false;    
            }
            
        }
        return true;
    }

    else{
        for(int i=0,j=0;i<oper->get_size()+1;i++,j--){ //merkezleri de kontrol etmek için get_size + 1 kadar dönüyor
            if(x+i <= grid_rows && x+j>=0 && y+i <= grid_cols && y+j>=0 ){
                if(grid[oper->get_x()-1+i][oper->get_y()-1+j] != '\0' || grid[oper->get_x()-1+j][oper->get_y()-1+i] != '\0' ) return false;
            }
            
        }
        return true;
    }
}
bool OperatorGrid::is_there(ArithmeticOperator **operators, ArithmeticOperator *oper){
    for(int i=0;i<num_operators;i++){
        if(oper->get_x() == operators[i]->get_x() && oper->get_y() == operators[i]->get_y() && oper->get_sign() == operators[i]->get_sign()) return false;
    }
    return true;
}
void OperatorGrid::delete_operator(char **grid, ArithmeticOperator *oper){

    int x = oper->get_x();
    int y = oper->get_y();
     
        if(oper->get_sign() == '+'){
            for(int i=0;i<oper->get_size()+1;i++){ 
                grid[x-1+i][y-1] = '\0';
                grid[x-1-i][y-1] = '\0';
                grid[x-1][y-1+i] = '\0';
                grid[x-1][y-1-i] = '\0';
            }
        }
        else if(oper->get_sign() == '-'){
            for(int i=0;i<oper->get_size()+1;i++){ 
                grid[x-1][y-1+i] = '\0';
                grid[x-1][y-1-i] = '\0';
            }         
        }
        else if(oper->get_sign() == 'x'){
            for(int i=0;i<oper->get_size()+1;i++){ 
                grid[x-1+i][y-1+i] = '\0';
                grid[x-1+i][y-1-i] = '\0';
                grid[x-1-i][y-1+i] = '\0';
                grid[x-1-i][y-1-i] = '\0';
            }
        }
        else{
            for(int i=0;i<oper->get_size()+1;i++){ 
                grid[x-1+i][y-1-i] = '\0';
                grid[x-1-i][y-1+i] = '\0';
            }
        }
}

bool OperatorGrid::place_operator(ArithmeticOperator *oper){

    int x = oper->get_x();
    int y = oper->get_y();  
    int size = oper->get_size();
    char sign = oper->get_sign();

    bool brd = border(grid, oper);
    if(!brd && is_there(operators, oper)) cout << "BORDER ERROR: Operator " << sign << " with size " << size << " can not be placed on (" << x << "," << y << ")." << endl;
    bool cnfl = conflict(grid, oper);
    if(!cnfl && is_there(operators, oper)) cout << "CONFLICT ERROR: Operator " << sign << " with size " << size << " can not be placed on (" << x << "," << y << ")." << endl;

    if(brd && cnfl){ // if there is no mistake
        if (first) {
            operators[num_operators] = oper;
            num_operators++;
            first = false;
            cout << "SUCCESS: Operator " << sign << " with size " << size <<  " is placed on (" << x << "," << y << ")." << endl;
        }
        if(is_there(operators, oper)) {
            operators[num_operators] = oper; 
            num_operators++; 
            cout << "SUCCESS: Operator " << sign << " with size " << size <<  " is placed on (" << x << "," << y << ")." << endl;
        }
        
        if(oper->get_sign() == '+'){
            for(int i=0;i<oper->get_size()+1;i++){ 
                grid[x-1+i][y-1] = '+';
                grid[x-1-i][y-1] = '+';
                grid[x-1][y-1+i] = '+';
                grid[x-1][y-1-i] = '+';
            }
        }
        else if(oper->get_sign() == '-'){
            for(int i=0;i<oper->get_size()+1;i++){ 
                grid[x-1][y-1+i] = '-';
                grid[x-1][y-1-i] = '-';
            }         
        }
        else if(oper->get_sign() == 'x'){
            for(int i=0;i<oper->get_size()+1;i++){ 
                grid[x-1+i][y-1+i] = 'x';
                grid[x-1+i][y-1-i] = 'x';
                grid[x-1-i][y-1+i] = 'x';
                grid[x-1-i][y-1-i] = 'x';
            }
        }
        else{
            for(int i=0;i<oper->get_size()+1;i++){ 
                grid[x-1+i][y-1-i] = '/';
                grid[x-1-i][y-1+i] = '/';
            }
        }
        return true;
    }
    return false;
}

bool OperatorGrid::move_operator(int x, int y, char direction, int move_by){
    char temp = grid[x-1][y-1];
    int i=0;
    while(operators[i]){
        int getx = operators[i]->get_x();
        int gety = operators[i]->get_y();
        int getsize = operators[i]->get_size();
        char getsign = operators[i]->get_sign();
        if(getsign == temp){
            if((abs(x - getx) <= getsize && abs(y - gety) <= getsize)){ //bitişik aynı işaretleri ayırt etmek için
                delete_operator(grid, operators[i]);
                if(direction == 'R'){
                    operators[i]->set_y(gety + move_by);
                    if(!place_operator(operators[i])){
                        bool brd = border(grid, operators[i]);
                        if(!brd) cout << "BORDER ERROR: " << getsign << " can not be moved from (" << getx << "," << gety << ") to (" << getx << "," << gety + move_by << ")." << endl;
                        bool cnfl = conflict(grid, operators[i]);
                        if (!cnfl) cout <<  "CONFLICT ERROR: " << getsign << " can not be moved from (" << getx << "," << gety << ") to (" << getx << "," << gety + move_by << ")." << endl;
                        operators[i]->set_y(gety);
                        place_operator(operators[i]);
                    }
                    else{
                        cout << "SUCCESS: " << getsign << " moved from (" << getx << "," << gety << ") to (" << getx << "," << gety + move_by << ")." << endl;
                    }
                }
                else if(direction == 'L'){
                    operators[i]->set_y(gety - move_by);
                    if(!place_operator(operators[i]) ){
                        bool brd = border(grid, operators[i]);
                        if(!brd) cout << "BORDER ERROR: " << getsign << " can not be moved from (" << getx << "," << gety << ") to (" << getx << "," << gety - move_by << ")." << endl;
                        bool cnfl = conflict(grid, operators[i]);
                        if (!cnfl) cout <<  "CONFLICT ERROR: " << getsign << " can not be moved from (" << getx << "," << gety << ") to (" << getx << "," << gety - move_by << ")." << endl;
                        operators[i]->set_y(gety);
                        place_operator(operators[i]);
                    }
                    else{
                        cout << "SUCCESS: " << getsign << " moved from (" << getx << "," << gety << ") to (" << getx << "," << gety - move_by << ")." << endl;
                    }
                }
                else if(direction == 'U'){
                    operators[i]->set_x(getx - move_by);
                    if(!place_operator(operators[i])){
                        bool brd = border(grid, operators[i]);
                        if(!brd) cout << "BORDER ERROR: " << getsign << " can not be moved from (" << getx << "," << gety << ") to (" << getx - move_by << "," << gety << ")." << endl;
                        bool cnfl = conflict(grid, operators[i]);
                        if (!cnfl) cout <<  "CONFLICT ERROR: " << getsign << " can not be moved from (" << getx << "," << gety << ") to (" << getx - move_by << "," << gety << ")." << endl;
                        operators[i]->set_x(getx);
                        place_operator(operators[i]);
                    }
                    else{
                        cout << "SUCCESS: " << getsign << " moved from (" << getx << "," << gety << ") to (" << getx - move_by << "," << gety << ")." << endl;
                    }
                }
                else{
                    operators[i]->set_x(getx + move_by);
                    if(!place_operator(operators[i])){
                        bool brd = border(grid, operators[i]);
                        if(!brd) cout << "BORDER ERROR: " << getsign << " can not be moved from (" << getx << "," << gety << ") to (" << getx + move_by << "," << gety << ")." << endl;
                        bool cnfl = conflict(grid, operators[i]);
                        if (!cnfl) cout <<  "CONFLICT ERROR: " << getsign << " can not be moved from (" << getx << "," << gety << ") to (" << getx + move_by << "," << gety << ")." << endl;
                        operators[i]->set_x(getx);
                        place_operator(operators[i]);
                    }
                    else{
                        cout << "SUCCESS: " << getsign << " moved from (" << getx << "," << gety << ") to (" << getx + move_by << "," << gety << ")." << endl;
                    }
                }
                return true;
            }   
        }
        i++;
    }
    return false;
}   

void OperatorGrid::print_operators(){
    cout << grid_rows << " " << grid_cols <<endl;
    for(int i=0;i<grid_rows;i++){
        for(int j=0;j<grid_cols;j++){
            if(grid[i][j] == '\0') cout << " ";
            else cout << grid[i][j]; 
        }
        cout << endl;
    }
}

#endif