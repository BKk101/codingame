#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

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

void Patrol(int pos, vector <Entity> list, int i);
void Throw(int pos);

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
				if (entity_list[i].state == 1) {
					Throw(myTeamId);
					continue;
				}
				Patrol(myTeamId, entity_list, i);
			}
            // Write an action using cout. DON'T FORGET THE "<< endl"
            // To debug: cerr << "Debug messages..." << endl;

            // Edit this line to indicate the action for each wizard (0 ≤ thrust ≤ 150, 0 ≤ power ≤ 500, 0 ≤ magic ≤ 1500)
            // i.e.: "MOVE x y thrust" or "THROW x y power" or "WINGARDIUM id x y magic"
        }
    }
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
		if (list[i].y <= 2750 && flag <= 0) {
			cout << "MOVE 0 5750 150" <<endl;
			flag++;
		}
		else if (list[i].y > 2750 && list[i].y <= 4750) {
			return ;
		}
		else if (list[i].y > 4750 && flag >= 4) {
			cout << "MOVE 0 1750 150" <<endl;
			flag--;
		}
		//if (list[i].y <= 2000) {
		//	cout << "MOVE 0 4750 150" << endl;
		//}
		//else if (list[i].y > 2000 && list[i].y <= 3750) {
		//	cout << "MOVE 0 5750 150" << endl;
		//}
		//else if (list[i].y > 3750 && list[i].y <= 5500) {
		//	cout << "MOVE 0 1750 150" << endl;
		//}
		//else if (list[i].y > 5500) {
		//	cout << "MOVE 0 2750 150" << endl;
		//}
	}
	else {
		if (list[i].y <= 2000) {
			cout << "MOVE 16000 4750 150" << endl;
		}
		else if (list[i].y > 2000 && list[i].y <= 3750) {
			cout << "MOVE 16000 5750 150" << endl;
		}
		else if (list[i].y > 3750 && list[i].y <= 5500) {
			cout << "MOVE 16000 1750 150" << endl;
		}
		else if (list[i].y > 5500) {
			cout << "MOVE 16000 2750 150" << endl;
		}
	}
}