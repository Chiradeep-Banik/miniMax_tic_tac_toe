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
    int boardSize;
    int maxDepth = 2;
public:
    Game(int n=3,int depth=2){
        board.clear();
        for(int i=0;i<n;i++){
            vector<char> v;
            for(int j=0;j<n;j++){
                v.push_back('-');
            }
            board.push_back(v);
        }
        left=n*n;
        boardSize = n;
        maxDepth=depth;
    }
    void printBoard() {
        for(int i = 0; i < boardSize;i++){
            for(int j = 0; j < boardSize;j++){
                cout << board[i][j];
                if(j != boardSize-1) cout << " | ";
            }cout <<endl;
        }
    }
    int getLeftMoves(){
        return left;
    } 
    bool isValid(int x,int y){
        if(x < 0 || y < 0 || x > boardSize-1 || y > boardSize-1) return false;
        if(board[x][y] != '-'){
            return false;
        }
        return true;
    }
    bool hasWon(bool oTurn){
        char checkFor = '-';
        if(oTurn) checkFor = 'O';
        else checkFor ='X';

        bool won = true;

        //horizontal
        for(int i=0;i<boardSize;i++){
            won = true;
            for(int j=0;j<boardSize;j++){
                if(board[i][j] != checkFor){
                    won = false;
                    break;
                }
            }
            if(won) break;
        }
        if(won) return true;
        //vertical
        for(int i=0;i<boardSize;i++){
            won = true;
            for(int j=0;j<boardSize;j++){
                if(board[j][i] != checkFor){
                    won = false;
                    break;
                }
            }
            if(won) break;
        }
        if(won) return true;
        //diagonal
        int i =0,j=0;
        won = true;
        while(i<boardSize && j<boardSize){
            if(board[i][j] != checkFor){
                won = false;
                break;
            }
            i++;
            j++;
        }
        if(won) return true;
        won = true;
        i = 0,j = boardSize-1;
        while(i<boardSize && j>-1){
            if(board[i][j] != checkFor){
                won = false;
                break;
            }
            i++;
            j--;
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
        board[x][y] = '-';
        left++;
    }
    int miniMax(int x, int y,int maximizing,int depth,int alpha, int beta){
        cout << "miniMax :: " << endl;
        printBoard();
        if(hasWon(true) && maximizing) return 1000;
        if(hasWon(false) && !maximizing) return 1000;
        if(left == 0) return 0;
        if(depth == 0){
            if(maximizing){
                return 1;
            }else{
                return -1;
            }
        }
        if(maximizing){
            int maxScore = INT_MIN;
            for(int i=0;i<board.size();i++){
                for(int j=0;j<board.size();j++){
                    if(board[i][j] =='-'){
                        move(i,j,true);
                        int score = miniMax(i,j,false,depth-1,alpha,beta);
                        undo(i,j);
                        alpha = max(alpha,score);
                        maxScore = max(score,maxScore);
                        if(beta < alpha ) cout<<"pruned ";break;
                    }
                }
            }
            return maxScore;
        }else{
            int maxScore = INT_MAX;
            for(int i=0;i<board.size();i++){
                for(int j=0;j<board.size();j++){
                    if(board[i][j] =='-'){
                        move(i,j,false);
                        int score = miniMax(i,j,true,depth-1,alpha,beta);
                        undo(i,j);
                        beta = min(beta,score);
                        maxScore = min(score,maxScore);
                        if(beta < alpha) cout<<"pruned ";break;
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
        for(int i=0;i<boardSize;i++){
            bool ifMoved = false;
            for(int j=0;j<boardSize;j++){
                vector<vector<char>> tempBoard= board;
                if(board[i][j] == '-'){
                    move(i,j,true);
                    int curScore = miniMax(i,j,false,maxDepth,INT_MIN,INT_MAX);
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
    int boardSize,maxDepth;
    cout << "Board size: ";
    cin >> boardSize;
    cout << "max depth: ";
    cin >> maxDepth;
    Game g = Game(boardSize,maxDepth);
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