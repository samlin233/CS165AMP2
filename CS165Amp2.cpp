#include <iostream>
#include <algorithm>
#include <cmath>
#include <map>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include <cstdlib>
using namespace std;

bool xianshou = 0;
int size = 0;
int myAI = 1;
int opponent =2;
struct position{
    int y;
    int x;
}; 
struct direction{
    int dy;
    int dx;
};
const direction dlr = {0, 1}; //向右→
const direction dud = {1, 0}; //向下↓
const direction ddl = {1, -1}; //左下↙
const direction ddr = {1, 1};  //右下↘
// direction of left right(lr) up down(ud) down left(dl) down right(dr)  

vector<vector<int>> chessboard;

position messtoposi(string message){

    position p1;
    p1.y =message[0]-'a';
    p1.x =stoi(message.substr(1))-1;
    return p1;
}

bool isOnBoard(position p, int size){
    if(p.y >= 0 && p.y < size && p.x >= 0 && p.x < size){
        return true;
    }
    else{
        return false;
    }
}

position newposition (position p, direction d, int lenth){
    position p1 = {p.y + d.dy * lenth, p.x + d.dx * lenth};
    return p1;
}


long int score(position p, int calcopp,int size){
    int win5 = 0, huo4 = 0, si4 = 0, doublesi4 = 0, huo3 = 0, 
    doublehuo3 = 0, si3 = 0, huo2 = 0, doublehuo2 = 0, si2 = 0, mode = 0;
    int oppchess;
    if(calcopp == 1){
        oppchess = 2;
    }
    else{
        oppchess = 1;
    }
    for(int i = 1; i <= 4; i ++){
        direction directions [4]= {dlr,dud,ddl,ddr};
        direction d = directions[i+1];
        int l = 1;               //连子长度
        position lef, rig, p1;
        int left[5], right[5];
        p1 = newposition(p, d, -1);                                 //向左向下检查
        lef = p;
        while(isOnBoard(p1,size) && chessboard[p1.y][p1.x] == calcopp){
            lef = p1;
            p1 = newposition(p1, d, -1);
            l ++;
        }
        p1 = newposition(p, d, 1);                                  //向右向下检查
        rig = p;
        while(isOnBoard(p1,size) && chessboard[p1.y][p1.x] == calcopp){
            rig = p1;
            p1 = newposition(p1, d, 1);
            l ++;
        }
        for(int j = 1; j <= 4; j ++){
            p1 = newposition(lef, d, -j);
            if(isOnBoard(p1,size)){
                left[j] = chessboard[p1.y][p1.x];
            }
            else{
                left[j] = oppchess;
            }
            p1 = newposition(rig, d, j);
            if(isOnBoard(p1,size)){
                right[j] = chessboard[p1.y][p1.x];
            }
            else{
                right[j] = oppchess;
            }
        }
        if(l==5){   //连5获胜
            win5++;
        }
        else if(l == 4){
            if(left[1] == 0 && right[1] == 0){//活四
                huo4 ++;
            }
            else if(left[1] == 0 || right[1] == 0){//死4
                si4 ++;
            }
            else{//无事发生
                   mode ++;
            }
        }
        else if(l == 3){
            if((left[1] == 0 && left[2] == calcopp) || (right[1] == 0 && right[2] == calcopp)){//双死4
            doublesi4 ++;
       }
        else if(left[1] == 0 && right[1] == 0 && (left[2] == 0 || right[2] == 0)){//huo3
            huo3 ++;                             
        }
       else if((left[1] == 0 && left[2] == 0) || (right[1] == 0 && right[2] == 0)){//si3
            si3 ++;
        }
        else if(left[1] == 0 && right[1] == 0){//si3
                   si3 ++; 
           } 
           else{//mode
                   mode ++;
           }
       }
       else if(l == 2){
              if((left[1] == 0 && left[2] == calcopp && left[3] == calcopp) && 
                 (right[1] == 0 && right[2] == calcopp && right[3] == calcopp)){//si4
                   doublesi4 ++;
           }
           else if(left[1] == 0 && right[1] == 0 && 
                   ((left[2] == calcopp && left[3] == 0) || (right[2] == calcopp && right[3] == 0))){//doublehuo3
                   doublehuo3 ++;
           }
           else if((left[1] == 0 && left[3] == 0 && left[2] == calcopp) || 
                   (right[1] == 0 && right[3] == 0 && right[2] == calcopp)){//si3
                si3 ++;
           }
           else if((left[1] == 0 && right[1] == 0) && 
                   (left[2] == calcopp || right[2] == calcopp)){//si3
                   si3 ++;
           }
           else if((left[1] == 0 && left[2] == 0 && left[3] == calcopp) || 
                   (right[1] == 0 && right[2] == 0 && right[3] == calcopp)){//si3
                si3 ++;
           }
           else if((left[1] == 0 && right[1] == 0 && right[2] == 0 && right[3] == 0) || 
                   (left[1] == 0 && left[2] == 0 && right[1] == 0 && right[2] == 0) || 
                   (left[1] == 0 && left[2] == 0 && left[3] == 0 && right[1] == 0)){//huo2
                   huo2 ++;
           }
           else if((left[1] == 0 && left[2] == 0 && left[3] == 0) || 
                   (right[1] == 0 && right[2] == 0 && right[3] == 0)){//si2
                   si2 ++;
           }
           else{//mode
                   mode ++;
           }
       }
       else if(l == 1){
              if((left[1] == 0 && left[2] == calcopp && left[3] == calcopp && left[4] == calcopp) || 
                 (right[1] == 0 && right[2] == calcopp && right[3] == calcopp && right[4] == calcopp)){//doublesi4
                   doublesi4 ++;
           }
           else if((left[1] == 0 && right[1] == 0) && ((left[2] == calcopp && left[3] == calcopp && left[4] == 0) || 
                   (right[2] == calcopp && right[3] == calcopp && right[4] == 0))){//doublehuo3
                   doublehuo3 ++;
           }
           else if((left[1] == 0 && right[1] == 0) && 
                   ((left[2] == calcopp && left[3] == calcopp) || (right[2] == calcopp && right[3] == calcopp))){//si3
                   si3 ++;
           }
           else if((left[1] == 0 && left[4] == 0 && left[2] == calcopp && left[3] == calcopp) || 
                   (right[1] == 0 && right[4] == 0 && right[2] == calcopp && right[3] == calcopp)){//si3
                   si3 ++;
           }
           else if((left[1] == 0 && left[2] == 0 && left[3] == calcopp && left[4] == calcopp) || 
                   (right[1] == 0 && right[2] == 0 && right[3] == calcopp && right[4] == calcopp)){//si3
                   si3 ++;
           } 
           else if((left[1] == 0 && left[3] == 0 && left[2] == calcopp && left[4] == calcopp) || 
                   (right[1] == 0 && right[3] == 0 && right[2] == calcopp && right[4] == calcopp)){//si3
                   si3 ++;
           }
           else if((left[1] == 0 && right[1] == 0 && right[3] == 0 && right[2] == calcopp) && (left[2] == 0 || right[4] == 0)){//doublehuo2
                   doublehuo2 ++;
           }
           else if((right[1] == 0 && left[1] == 0 && left[3] == 0 && left[2] == calcopp) && 
                   (right[2] == 0 || left[4] == 0)){//doublehuo2
                   doublehuo2 ++;
           }
           else if((left[1] == 0 && right[1] == 0 && right[2] == 0 && right[4] == 0 && right[3] == calcopp) || 
                   (right[1] == 0 && left[1] == 0 && left[2] == 0 && left[4] == 0 && left[3] == calcopp)){//doublehuo2
                   doublehuo2 ++;
           }
           else if((left[1] == 0 && left[3] == 0 && left[4] == 0 && left[2] == calcopp) || 
                   (right[1] == 0 && right[3] == 0 && right[4] == 0 && right[2] == calcopp)){//si2
                   si2 ++;
           }
           else if((left[1] == 0 && right[1] == 0 && right[2] == 0 && left[2] == calcopp) || 
                   (right[1] == 0 && left[1] == 0 && left[2] == 0 && right[2] == calcopp)){//si2
                   si2 ++;
           }
           else if((left[1] == 0 && left[2] == 0 && left[4] == 0 && left[3] == calcopp) || 
                   (right[1] == 0 && right[2] == 0 && right[4] == 0 && right[3] == calcopp)){//si2
                   si2 ++;
           }
           else if((left[1] == 0 && left[2] == 0 && right[1] == 0 && left[3] == calcopp) || 
                   (right[1] == 0 && right[2] == 0 && left[1] == 0 && right[3] == calcopp)){//si2
                   si2 ++;
           }
           else if((left[1] == 0 && left[2] == 0 && left[3] == 0 && left[4] == calcopp) || 
                   (right[1] == 0 && right[2] == 0 && right[3] == 0 && right[4] == calcopp)){//si2
                   si2 ++;
           }
           else{//mode
                   mode ++;
           }
       }
    }
    if (win5 >= 1)
        return 99999999999999;//贏5
    if (huo4 >= 1 || si4 >= 2 || (si4 >= 1 && huo3 >= 1))
        return 9999999999999;//活4 双死4 死4活3
    if (huo3 >= 2)
        return 999999999999;//双活3
    if (si3 >= 1 && huo3 >= 1)
        return 99999999999;//死3活3
    if (si4 >= 1)
        return 9999999999;//死4
    if (doublesi4 >= 1)
        return 999999999;//死4
    if (huo3 >= 1)
        return 99999999;//活3
    if (doublehuo3 >= 1)
        return 9999999;//双活3
    if (huo2 >= 2)
        return 999999;//高等双活2
    if (huo2 >= 1)
        return 99999;//单活2
    if (doublehuo2 >= 1)
        return 9999;//双活2
    if (si3 >= 1)
        return 999;//死3S
    if (si2 >= 1)
        return 99;//死2
    return 9;//无事发生
}

int main(int argc, char* argv[]){
    
    if(argc>1 && argv[1][1]=='n'){
        size = stoi(argv[2]);}
    else if(argc>2 && argv[2][1]=='n'){
        size = stoi(argv[3]);}
    if(argc>1 && argv[1][1]=='l'){
        xianshou = 1;}
    else if(argc>1 && argv[3][1] == 'l'){
        xianshou=1;}
    chessboard.resize(size);
    for( int i=0;i<size;i++){
        chessboard[i].resize(size);}
    if(xianshou == 1){
        char ch = static_cast<char>(size/2+97);
        cout<<"Move Played: "<<ch<<size/2+1<<endl;
        chessboard[size/2][size/2]=1;
        }
    while(true){
        string temp ="";
        cin>>temp;
        position p1 = messtoposi(temp);
        while (chessboard[p1.y][p1.x]!=0||p1.x>size||p1.y>size)
        {
            cout<<"Invalid move"<<endl;
            cin>>temp;
            p1 = messtoposi(temp);
        }
        
        cout<<"Move Played: "<<temp<<endl;

        chessboard[p1.y][p1.x] = 2;
 
        position beststep1, beststep2;  //1prio on attack 2prio on defence

       for(int i=0; i<size;i++){
           for(int j=0; j<size;j++){
               if(chessboard[i][j]==0){
                   beststep1.y=beststep2.y=i;
                   beststep1.x=beststep2.x=j;  
                   break;                 
               }
           }
       }
        long int a1 = score(beststep1, myAI, size), b1 = score(beststep1, opponent,size);   //attack first
        
        for(int i = 0; i < size; i ++){
            for(int j = 0; j < size; j ++){
                if(chessboard[i][j] == 0){
                
                position cur = {i, j};
                long int m1 = score(cur, myAI,size);
                long int m2 = score(cur, opponent,size);
                if(m1 > a1){
                    beststep1 = cur;
                    a1 = m1;
                    b1 = m2;}
                else if(m1 == a1){
                    if(m2 > b1){ 
                        beststep1 = cur;
                        b1 = m2;
                    }
                }
                }
            }
        }

        long int a2 = score(beststep2, opponent,size), b2 = score(beststep2, myAI,size);    //defence first
        for(int i = 0; i < size; i ++){
            for(int j = 0; j < size; j ++){
                if(chessboard[i][j] == 0){
                
                position cur = {i, j};
                long int m1 = score(cur, opponent,size);
                long int m2 = score(cur, myAI,size);
                if(m1 > a2){
                    beststep2 = cur;
                    a2 = m1;
                    b2 = m2;}
                else if(m1 == a2){
                    if(m2 > b2){
                        beststep2 = cur;
                        b2 = m2;
                    }
                }
            }
            }
        }
        if(a1 > a2){
            chessboard[beststep1.y][beststep1.x]=1;
            cout<<"Move Played: "<<char(beststep1.y+'a')<<beststep1.x+1<<endl;
        }
        else{
            chessboard[beststep2.y][beststep2.x]=1;
            cout<<"Move Played: "<<char(beststep2.y+'a')<<beststep2.x+1<<endl;
        }
    
    }
    return 0;
}




