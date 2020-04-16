#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#define PATROL_R 800
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

void Patrol0(Pos start, Pos end, Pos wizard, int thrust);
void Patrol1(Pos start, Pos end, Pos wizard, int thrust);
void Throw(Pos des, int power);
void Spell(int mp, int Id, Pos des);
void Move(int x, int y, int thrust);
vector <Entity> find_object(vector <Entity> list, int entities, const char* obj);
double Distance(int x1, int y1, int x2, int y2); 
int near_des(vector <Entity> units, Pos des);
int far_des(vector <Entity> units, Pos des);
bool cmp(const Entity& a, const Entity& b);
int in_bound(Pos obj, vector <Entity> units, int range);

int main()
{
    int myTeamId; // if 0 you need to score on the right of the map, if 1 you need to score on the left
    cin >> myTeamId; cin.ignore();
	int myScore;
    int myMagic;
	int opponentScore;
    int opponentMagic;
	int entities;
    // game loop
    while (1) {
        cin >> myScore >> myMagic; cin.ignore();
        cin >> opponentScore >> opponentMagic; cin.ignore();
        // number of entities still in game
        cin >> entities; cin.ignore();

		vector <Entity> entity_list(entities);
        for (int i = 0; i < entities; i++) {
			cin >> entity_list[i].entityId >> entity_list[i].entityType 
			>> entity_list[i].x >> entity_list[i].y >> entity_list[i].vx >> entity_list[i].vy 
			>> entity_list[i].state; cin.ignore();
        }
		vector <Entity> snaffles(find_object(entity_list, entities, "SNAFFLE"));
		vector <Entity> wizards(find_object(entity_list, entities, "WIZARD"));
		vector <Entity> op_wizards(find_object(entity_list, entities, "OPPONENT_WIZARD"));
		Pos my_goal, op_goal;
		if (myTeamId == 0) {
			op_goal.x = 16000; op_goal.y = 3750;
			my_goal.x = 0; my_goal.y = 3750;
		}
		else {
			op_goal.x = 0; op_goal.y = 3750;
			my_goal.x = 16000; my_goal.y = 3750;
		}
		Pos wizard0_pos = {wizards[0].x, wizards[0].y};
		Pos wizard1_pos = {wizards[1].x, wizards[1].y};
		//wizard0 command
			Pos p1 = {8000, 1000}; Pos p2 = {8000, 6500};
			Pos p3 = {my_goal.x + 800, (my_goal.y - 2000)}; Pos p4 = {my_goal.x + 800, (my_goal.y + 2000)};
			if (wizards[0].state == 1) {
				Throw(op_goal, 500);
			}
			else if (myMagic > 30) {
				Spell(myMagic / 2, near_des(snaffles, op_goal), op_goal);
			}
			else {
			    Patrol0(p1, p2, wizard0_pos, 150);
			}
			//wizard1 command
			if (wizards[1].state == 1) {
				Throw(p1, 500);
			}
			else if (in_bound(wizard1_pos, snaffles, 800) && myMagic >= 20) {
				Spell(myMagic / 2, near_des(snaffles, wizard1_pos), op_goal);
			}
			else {
			    Patrol1(p3, p4, wizard1_pos, 150);
			}
		//cerr << "Debug messages..." << endl;
	}
}

double Distance(int x1, int y1, int x2, int y2)
{
	return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

bool cmp(const Entity& a, const Entity& b)
{
    return (a.entityId < b.entityId);
}

vector <Entity> find_object(vector <Entity> list, int entities, const char* obj)
{
	vector <Entity> object;
	for (int i=0;i<entities;i++) {
		if (list[i].entityType == obj) {
			object.push_back(list[i]);
		}
	}
	sort(object.begin(), object.end(), cmp);
	return object;
}

int in_bound(Pos obj, vector <Entity> units, int range)
{
	for (int i=0;i<units.size();i++) {
		if (Distance(obj.x, obj.y, units[i].x, units[i].y) <= range)
			return 1;
	}
	return 0;
}

int near_des(vector <Entity> units, Pos des)
{
	int dis = 16000;
	int nearId;
	for (int i=0;i<units.size();i++) {
		if (Distance(units[i].x, units[i].y, des.x, des.y) <= dis) {
			dis = Distance(units[i].x, units[i].y, des.x, des.y);
			nearId = units[i].entityId;
		}
	}
	return nearId;
}

int far_des(vector <Entity> units, Pos des)
{
	int dis = 0;
	int farId;
	for (int i=0;i<units.size();i++) {
		if (Distance(units[i].x, units[i].y, des.x, des.y) >= dis) {
			dis = Distance(units[i].x, units[i].y, des.x, des.y);
			farId = units[i].entityId;
		}
	}
	return farId;
}

void Move(int x, int y, int thrust)
{
	cout<<"MOVE "<<x<<" "<<y<<" "<<thrust<<endl;
}

void Spell(int mp, int Id, Pos des)
{
	cout << "WINGARDIUM "<<Id<<" "<<des.x<<" "<<des.y<<" "<<mp<< endl;
}

void Throw(Pos des, int power)
{
	cout<<"THROW "<<des.x<<" "<<des.y<<" "<<power<< endl;
}

void Patrol0(Pos start, Pos end, Pos wizard, int thrust)
{
	static int flag = 0;
	double dis_from_start = Distance(start.x, start.y, wizard.x, wizard.y);
	double dis_from_end = Distance(end.x, end.y, wizard.x, wizard.y);
	if (flag == 0) {
		if (dis_from_end > PATROL_R)
			Move(end.x, end.y, thrust);
		else if (dis_from_end <= PATROL_R) {
			Move(end.x, end.y, (int)(thrust * 0.5));
			flag = 1;
		}
	}
	else if (flag == 1) {
		if (dis_from_start > PATROL_R)
			Move(start.x, start.y, thrust);
		else if (dis_from_start <= PATROL_R) {
			Move(start.x, start.y, (int)(thrust * 0.5));
			flag = 0;
		}
	}
}

void Patrol1(Pos start, Pos end, Pos wizard, int thrust)
{
	static int flag = 0;
	double dis_from_start = Distance(start.x, start.y, wizard.x, wizard.y);
	double dis_from_end = Distance(end.x, end.y, wizard.x, wizard.y);
	if (flag == 0) {
		if (dis_from_end > PATROL_R)
			Move(end.x, end.y, thrust);
		else if (dis_from_end <= PATROL_R) {
			Move(end.x, end.y, (int)(thrust * 0.5));
			flag = 1;
		}
	}
	else if (flag == 1) {
		if (dis_from_start > PATROL_R)
			Move(start.x, start.y, thrust);
		else if (dis_from_start <= PATROL_R) {
			Move(start.x, start.y, (int)(thrust * 0.5));
			flag = 0;
		}
	}
}