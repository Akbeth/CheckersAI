#include <iostream>
#include <ctime>
#include <sys/time.h>
#include <stdlib.h>
#include <functional>
#include <list>
#include "../include/Board.h"
#include "../include/Turn.h"
#include "../include/NegMaxNode.h"
#include "../include/RandomCarlo.h"
#include "../include/SSS.h"
#include "../include/NegMax.h"
#include <chrono>

using namespace std;

// TODO ajouter les conditions de victoire
// TODO on dirait que les noirs veulent perdre, checker NegMaxNode et MoveStack.getHeuristics()

void test6() {
    cout << "----------------- TEST 6 ------------------" << endl;
    cout << "|       Test of biggest depth for a row   |" << endl;
    cout << "-------------------------------------------" << endl << endl;

    std::chrono::system_clock::time_point start = std::chrono::system_clock::now();

    //Board b = Board("oooooowwwooBooooooowWoooooooooooowooowoooWoooooooo");
    Board b = Board("bbbbbbbbbbbbbbbbbbbboooooooooowwwwwwwwwwwwwwwwwwww");
    bool isWhite = false;
    Turn *t = new Turn(b, isWhite, 1);
    int depth = 5;
    cout << *t;
    for (int i = 0; i < 200 ; i++) {
        NegMax *n = new NegMax(t, isWhite);
        t = n->nextTurn(depth, isWhite);
        cout << *t;
        delete n;
        if(t->getBoard().getAllPawns(true).size() == 0) {
            cout << "BLACK WINS" << endl;
            break;
        } else if(t->getBoard().getAllPawns(false).size() == 0) {
            cout << "WHITE WINS" << endl;
            break;
        }
        break;
    }
    std::chrono::duration<double> sec = std::chrono::system_clock::now() - start;
    cout << sec.count() << endl;
    delete t;
}

void test5() {
    cout << "----------------- TEST 5 ------------------" << endl;
    cout << "|       Ia for MonteCarlo algorithm        |" << endl;
    cout << "-------------------------------------------" << endl << endl;

    std::chrono::system_clock::time_point start = std::chrono::system_clock::now();

    Board b = Board("bbbbbbbbbbbbbbbbbbbboooooooooowwwwwwwwwwwwwwwwwwww");
    bool isWhite = false;
    Turn *t = new Turn(b, isWhite, 1);
    int depth = 12;
    cout << *t;
    RandomCarlo rC;
    t = rC.play(b, isWhite);
    cout << *t;
    std::chrono::duration<double> sec = std::chrono::system_clock::now() - start;
    cout << sec.count() << endl;
    delete t;
}

void test3() {
    cout << "----------------- TEST 3 ------------------" << endl;
    cout << "|       real IA game test - depth 5       |" << endl;
    cout << "-------------------------------------------" << endl << endl;
    Board b = Board("bbbbbbbbbbbbbbbbbbbboooooooooowwwwwwwwwwwwwwwwwwww");
    timeval tim;
    double moyenne = 0;
    double played = 0;
    double t1 = 0;
    double t2 = 0;
    bool isWhite = false;
    Turn *t = new Turn(b, isWhite, 1);
    int depth = 6;
    cout << *t;
    for (int i = 0; i < 200 ; i++) {
        gettimeofday(&tim, NULL);
        t1=tim.tv_sec+(tim.tv_usec/1000000.0);
        NegMax *n = new NegMax(t, isWhite);
        t = n->nextTurn(depth, isWhite);
        cout << *t;
        delete n;
        if(t->getBoard().getAllPawns(true).size() == 0) {
            cout << "BLACK WINS" << endl;
            break;
        } else if(t->getBoard().getAllPawns(false).size() == 0) {
            cout << "WHITE WINS" << endl;
            break;
        }
        gettimeofday(&tim, NULL);
        t2=tim.tv_sec+(tim.tv_usec/1000000.0);
        moyenne += t2-t1;
        played++;
    }
    cout << "moyenne : " << moyenne / played << "s" << endl;
    delete t;
}

void test2() {
    cout << "----------------- TEST 2 ------------------" << endl;
    cout << "|        heuristic check - get king       |" << endl;
    cout << "-------------------------------------------" << endl << endl;
    Board b = Board("oooooobbbowooooooboooooooooooooooooooooooooooooooo");
    Turn t = Turn(b, true, 1);
    t.generateTurn();
    cout << t;
    std::list<MoveStack *> list = t.getAvailableMoves();
    for (auto it = list.begin(); it != list.end(); it++) {
        cout << "--------------- MOVE FOUND ----------------" << endl;
        cout << **it;
        cout << "Heuristic : " << (*it)->getHeuristic(t) << endl << endl;
        Turn *t2 = t.getNextTurn(*it);
        cout << *t2;
        delete t2;
    }
}


void test1() {
    cout << "----------------- TEST 1 ------------------" << endl;
    cout << "|    legal moves check - complex moves    |" << endl;
    cout << "-------------------------------------------" << endl << endl;
    Board b = Board("oooooowwwooBooooooowWoooooooooooowooowoooWoooooooo");
    Turn t = Turn(b, false, 42);
    t.generateTurn();
    cout << t;
    std::list<MoveStack *> list = t.getAvailableMoves();
    for (auto it = list.begin(); it != list.end(); it++) {
        cout << "--------------- MOVE FOUND ----------------" << endl;
        cout << **it;
        cout << "Heuristic : " << (*it)->getHeuristic(t) << endl << endl;
        Turn *t2 = t.getNextTurn(*it);
        cout << *t2;
        delete t2;
    }
}

void test4() {
    cout << "----------------- TEST 4 ------------------" << endl;
    cout << "|             Black heuristic              |" << endl;
    cout << "-------------------------------------------" << endl << endl;
    Board b = Board("oooooooooooboooooooooowoowoooooooooooooooooooooooo");
    bool isWhite = false;
    Turn *t = new Turn(b, isWhite, 42);
    cout << *t;
    NegMaxNode *n = new NegMaxNode(t, isWhite);
    t = n->nextTurn(4, isWhite);
    cout << *t;
    delete n;
}

void test7() {
    cout << "----------------- TEST 7 ------------------" << endl;
    cout << "|              Test of SSS*               |" << endl;
    cout << "-------------------------------------------" << endl << endl;

    std::chrono::system_clock::time_point start = std::chrono::system_clock::now();

    Board b = Board("bbbbbbbbbbbbbbbbbbbboooooooooowwwwwwwwwwwwwwwwwwww");
    bool isWhite = false;
    Turn *t = new Turn(b, isWhite, 1);
    int depth = 5;
    cout << *t;
    for (int i = 0; i < 200 ; i++) {
        SSS *sss = new SSS();
        t = sss->play(t, isWhite, depth);
        cout << *t;
        delete sss;
        if(t->getBoard().getAllPawns(true).size() == 0) {
            cout << "BLACK WINS" << endl;
            break;
        } else if(t->getBoard().getAllPawns(false).size() == 0) {
            cout << "WHITE WINS" << endl;
            break;
        }
        break;
        isWhite = !isWhite;
    }
    std::chrono::duration<double> sec = std::chrono::system_clock::now() - start;
    cout << sec.count() << endl;
    delete t;
}

int main() {
    //test1();
    //test2();
    //test4();
    //test3();
    //test5();
    test6();
    //test7();
    return 0;
}