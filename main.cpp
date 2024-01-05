#include<iostream>
#include<vector>
#include<limits.h>

using namespace std;
/**
 * 
 * @author Chiradeep Banik
 * 
 * X -- For the player
 * O -- for the Computer
*/


class Game{
private:
    vector<vector<char>> board;
    int left;
public:
    Game(){
        board.clear();
        board = {
            {'+','+','+'},
            {'+','+','+'},
            {'+','+','+'}
        };
        left=9;
    }
    void printBoard() {
        for(int i = 0; i < 3;i++){
            for(int j = 0; j < 3;j++){
                cout << board[i][j] << " ";
            }cout << endl;
        }
        cout << endl;
    }
    int getLeftMoves(){
        return left;
    } 
    bool isValid(int x,int y){
        if(x < 0 || y < 0 || x > 2 || y > 2) return false;
        if(board[x][y] != '+'){
            return false;
        }
        return true;
    }
    bool hasWon(bool oTurn){
        char checkFor = '+';
        if(oTurn) checkFor = 'O';
        else checkFor ='X';

        bool won = false;

        //vecrtical
        for(int i=0;i<3;i++){
            if(board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] == checkFor){
                won = true;
            }
        }
        if(won) return true;
        //horizontal
        for(int i=0;i<3;i++){
            if(board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] == checkFor){
                won = true;
            }
        }
        if(won) return true;
        //diagonal
        if(board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] == checkFor){
            won = true;
        }
        if(won) return true;

        if(board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] == checkFor){
            won = true;
        }
        return won;

    }
    bool move(int x, int y,bool oTurn){
        if(!isValid(x,y)){
            cout << "NOT valid move" << endl;
            return false;
        }
        if(oTurn){
            board[x][y] = 'O';
        }else{
            board[x][y] = 'X';
        }
        left--;
        return true;
    } 
    void undo(int x, int y){
        board[x][y] = '+';
        left++;
    }
    int miniMax(int x, int y,int maximizing,int depth){
        // cout << "miniMax :: " << endl;
        // printBoard();
        if(hasWon(true)) return 1;
        if(hasWon(false)) return -1;
        if(left == 0) return 0;

        if(maximizing){
            int maxScore = INT_MIN;
            for(int i=0;i<board.size();i++){
                for(int j=0;j<board.size();j++){
                    if(board[i][j] =='+'){
                        move(i,j,true);
                        int score = miniMax(i,j,false,depth+1);
                        undo(i,j);
                        maxScore = max(score,maxScore);
                    }
                }
            }
            return maxScore;
        }else{
            int maxScore = INT_MAX;
            for(int i=0;i<board.size();i++){
                for(int j=0;j<board.size();j++){
                    if(board[i][j] =='+'){
                        move(i,j,false);
                        int score = miniMax(i,j,true,depth+1);
                        undo(i,j);
                        maxScore = min(score,maxScore);
                    }
                }
            }
            return maxScore;
        }

    }
    void getComputerMove(){
        if(getLeftMoves() == 0) return;
        int maxScore = INT_MIN;
        pair<int,int> bestMove;
        for(int i=0;i<3;i++){
            bool ifMoved = false;
            for(int j=0;j<3;j++){
                vector<vector<char>> tempBoard= board;
                if(board[i][j] == '+'){
                    move(i,j,true);
                    int curScore = miniMax(i,j,false,0);
                    undo(i,j);
                    if(curScore > maxScore){
                        bestMove = {i,j};
                        maxScore=curScore;
                    }
                }
            }
        }
        move(bestMove.first,bestMove.second,true);
    }
};

int main(){
    Game g = Game();
    int player = true;
    while(g.getLeftMoves() > 0){
        cout << "Current Board : " << endl;
        g.printBoard();
        int youMoveX,youMoveY;
        cout << "Enter your Move : " ; 
        cin >> youMoveX >> youMoveY;
        if(!g.isValid(youMoveX,youMoveY)){
            cout << "Invalid Move" << endl;
            continue;
        }
        g.move(youMoveX,youMoveY,!player);
        if(g.hasWon(!player)){
            cout << "You Won" << endl;
            break;
        }
        player = !player;
        g.getComputerMove();
        if(g.hasWon(!player)){
            cout << "Computer Won....Better Luck Next Time" << endl;
            break;
        }
        player = !player;
    }
    if(g.getLeftMoves() == 0){
        cout << "It is a tie" << endl;
    }
    g.printBoard();
}