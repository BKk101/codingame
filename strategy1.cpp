#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct Entity
{
    int entityId;
	string entityType;
	int x;
	int y;
	int vx;
	int vy;
	int state;
};

struct Pos
{
	int x;
	int y;
};

void Patrol(int pos, vector <Entity> list, int i);
void Throw(int pos);
void Spell(int pos, int mp, vector <Entity> snaffles, Pos des);
vector <Entity> find_object(vector <Entity> list, int entities, char* obj);
double Distance(int x1, int y1, int x2, int y2); 

int main()
{
    int myTeamId; // if 0 you need to score on the right of the map, if 1 you need to score on the left
    cin >> myTeamId; cin.ignore();

    // game loop
    while (1) {
        int myScore;
        int myMagic;
        cin >> myScore >> myMagic; cin.ignore();
        int opponentScore;
        int opponentMagic;
        cin >> opponentScore >> opponentMagic; cin.ignore();
        int entities; // number of entities still in game
        cin >> entities; cin.ignore();

		vector <Entity> entity_list(entities);
        for (int i = 0; i < entities; i++) {
			cin >> entity_list[i].entityId >> entity_list[i].entityType 
			>> entity_list[i].x >> entity_list[i].y >> entity_list[i].vx >> entity_list[i].vy 
			>> entity_list[i].state; cin.ignore();
        }
		vector <Entity> snaffles(find_object(entity_list, entities, "SNAFFLE"));
		if (myTeamId == 0) {
			Pos op_goal = {16000, 3750};
			Pos my_goal = {0, 3750};
		}
		else {
			Pos op_goal = {0, 3750};
			Pos my_goal = {16000, 3750};
		}
        for (int i = 0; i < 2; i++) {
			//wizard0 command
			if (entity_list[i].state == 1) {
					Throw(myTeamId);
					continue;
			}
            if (i == 0) {
				cout << "MOVE 8000 3750 100" << endl;
			}
			//wizard1 command
			else if (i == 1) {
				if (myMagic > 50) {
					Spell(myTeamId, myMagic, snaffles, op_goal);
					continue;
				}
				if (entity_list[i].state == 1) {
					Throw(myTeamId);
					continue;
				}
				Patrol(myTeamId, entity_list, i);
			}
            // To debug: cerr << "Debug messages..." << endl;
        }
    }
}

double Distance(int x1, int y1, int x2, int y2)
{
	return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

vector <Entity> find_object(vector <Entity> list, int entities, char* obj)
{
	int cnt = 0;
	for (int i=0;i<entities;i++) {
		if (list[i].entityType == obj)
			cnt++;
	}
	vector <Entity> object(cnt);
	for (int i=0;i<entities;i++) {
		if (list[i].entityType == obj) {
			object.push_back(list[i]);
		}
	}
	return object;
}

void Spell(int pos, int mp, vector <Entity> snaffles, Pos des)
{
	int dis = 16000;
	int nearId;
	for (int i=0;i<snaffles.size();i++) {
		if (Distance(snaffles[i].x, snaffles[i].y, des.x, des.y) <= dis) {
			dis = Distance(snaffles[i].x, snaffles[i].y, des.x, des.y);
			nearId = snaffles[i].entityId;
		}
	}
	cout << "WINGARDIUM "<<nearId<<" "<<des.x<<" "<<des.y<<" "<<50<< endl;
}

void Throw(int pos)
{
	if (pos == 0)
		cout << "THROW 16000 3750 500" << endl;
	else
		cout << "THROW 0 3750 500" << endl;
}

void Patrol(int pos, vector <Entity> list, int i)
{
	static int flag = 0;
	if (pos == 0) {
		if (flag == 0){
			if (list[i].y <= 2400) {
				cout << "MOVE 750 5400 150" << endl;
			}
			else if (list[i].y > 2400 && list[i].y <= 5100) {
				cout << "MOVE 750 5400 150" << endl;
			}
			else if (list[i].y > 5100) {
				cout << "MOVE 750 5400 50" << endl;
				flag = 1;
			}
		}
		else {
			if (list[i].y <= 2400) {
				cout << "MOVE 750 1400 50" << endl;
				flag = 0;
			}
			else if (list[i].y > 2400 && list[i].y <= 5100) {
				cout << "MOVE 750 1400 150" << endl;
			}
			else if (list[i].y > 5100) {
				cout << "MOVE 750 1400 150" << endl;
			}
		}
	}
	else {
		if (flag == 0){
			if (list[i].y <= 2400) {
				cout << "MOVE 15250 5400 150" << endl;
			}
			else if (list[i].y > 2400 && list[i].y <= 5100) {
				cout << "MOVE 15250 5400 150" << endl;
			}
			else if (list[i].y > 5100) {
				cout << "MOVE 15250 5400 50" << endl;
				flag = 1;
			}
		}
		else {
			if (list[i].y <= 2400) {
				cout << "MOVE 15250 1400 50" << endl;
				flag = 0;
			}
			else if (list[i].y > 2400 && list[i].y <= 5100) {
				cout << "MOVE 15250 1400 150" << endl;
			}
			else if (list[i].y > 5100) {
				cout << "MOVE 15250 1400 150" << endl;
			}
		}
	}
}