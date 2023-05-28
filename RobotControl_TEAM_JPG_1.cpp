// GRUPPMEDLEMMAR \\
// GUSTAV HULTMAN \\
// PONTUS ERIKSSON \\
// JENNY LAND \\;

#include "pch.h"
#include <debugapi.h>
#include "RobotControl_TEAM_JPG_1.h"
#include <vector>
#include <iostream>
#include <cstdlib> 
#include <ctime> 

using namespace std;
using namespace Player1;
int d;
vector<int> senaste_steg;
Player1::RobotControl::RobotControl()
{
	robot_bitmap_row = 5;          // Pick a unique monster icon for your robot!
	robot_bitmap_col = 10;
	team_name = L"TEAM JPG";
}



Command Player1::RobotControl::do_command(const Info& info)
{
	OutputDebugString(L"Nu körs do_command()\n");
	if (info.last_event == Event::COLLISION)
		OutputDebugString(L"Krockade i förra rundan!\n");

	if (senaste_steg.empty())
		senaste_steg.push_back(1);

	int steg[3][3] = {

		{7, 0, 4},
		{3, 0, 1},
		{6, 2, 5}

	};


	if (info.last_event == Event::OK) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (info.neighbor_cells[i][j] == Cell_content::EMPTY)
				{
					for (int i = 0; i < senaste_steg.size(); i++)
						d = senaste_steg[i];
					break;
				}

			}
		}
	}


	//Nedre vänster hörn!
	if (info.neighbor_cells[0][0] == Cell_content::WALL && info.neighbor_cells[1][0] == Cell_content::WALL && info.neighbor_cells[2][0] == Cell_content::WALL && info.neighbor_cells[2][1] == Cell_content::WALL && info.neighbor_cells[2][2] == Cell_content::WALL)
	{

		d = steg[0][2];
		senaste_steg.pop_back();
		senaste_steg.push_back(d);
	}

	//övre vänster hörn
	else if (info.neighbor_cells[2][0] == Cell_content::WALL && info.neighbor_cells[1][0] == Cell_content::WALL && info.neighbor_cells[0][0] == Cell_content::WALL && info.neighbor_cells[0][1] == Cell_content::WALL && info.neighbor_cells[0][2] == Cell_content::WALL)
	{

		d = steg[2][2];
		senaste_steg.pop_back();
		senaste_steg.push_back(d);
	}

	//övre höger hörn
	else if (info.neighbor_cells[0][0] == Cell_content::WALL && info.neighbor_cells[0][1] == Cell_content::WALL && info.neighbor_cells[0][2] == Cell_content::WALL && info.neighbor_cells[1][2] == Cell_content::WALL && info.neighbor_cells[2][2] == Cell_content::WALL)
	{

		d = steg[2][0];
		senaste_steg.pop_back();
		senaste_steg.push_back(d);
	}

	//nedre höger hörn
	else if (info.neighbor_cells[2][0] == Cell_content::WALL && info.neighbor_cells[2][1] == Cell_content::WALL && info.neighbor_cells[2][2] == Cell_content::WALL && info.neighbor_cells[1][2] == Cell_content::WALL && info.neighbor_cells[0][2] == Cell_content::WALL)
	{

		d = steg[0][0];
		senaste_steg.pop_back();
		senaste_steg.push_back(d);
	}

	//dem tre nedre
	else if (info.neighbor_cells[2][0] == Cell_content::WALL && info.neighbor_cells[2][1] == Cell_content::WALL && info.neighbor_cells[2][2] == Cell_content::WALL)
	{
		Action act = Action::STEP;
		srand(time(NULL));
		int i = rand() % 5;
		if (i == 0)
			d = steg[0][2];
		if (i == 1)
			d = steg[0][0];
		if (i == 2)
			d = steg[0][1];
		if (i == 3)
			d = steg[1][0];
		if (i == 4)
			d = steg[1][2];
		senaste_steg.pop_back();
		senaste_steg.push_back(d);
	}
	//dem tre övre
	else if (info.neighbor_cells[0][0] == Cell_content::WALL && info.neighbor_cells[0][1] == Cell_content::WALL && info.neighbor_cells[0][2] == Cell_content::WALL)
	{
		Action act = Action::STEP;
		srand(time(NULL));
		int i = rand() % 5;
		if (i == 0)
			d = steg[2][0];
		if (i == 1)
			d = steg[2][2];
		if (i == 2)
			d = steg[2][1];
		if (i == 3)
			d = steg[1][0];
		if (i == 4)
			d = steg[1][2];
		senaste_steg.pop_back();
		senaste_steg.push_back(d);
	}
	//dem tre till vänster
	else if (info.neighbor_cells[0][0] == Cell_content::WALL && info.neighbor_cells[1][0] == Cell_content::WALL && info.neighbor_cells[2][0] == Cell_content::WALL)
	{
		Action act = Action::STEP;
		srand(time(NULL));
		int i = rand() % 5;
		if (i == 0)
			d = steg[0][2];
		if (i == 1)
			d = steg[2][2];
		if (i == 2)
			d = steg[1][2];
		if (i == 3)
			d = steg[0][1];
		if (i == 4)
			d = steg[2][1];
		senaste_steg.pop_back();
		senaste_steg.push_back(d);
	}

	//dem tre till höger

	else if (info.neighbor_cells[0][2] == Cell_content::WALL && info.neighbor_cells[1][2] == Cell_content::WALL && info.neighbor_cells[2][2] == Cell_content::WALL)
	{
		Action act = Action::STEP;
		srand(time(NULL));
		int i = rand() % 5;
		if (i == 0)
			d = steg[0][0];
		if (i == 1)
			d = steg[2][0];
		if (i == 2)
			d = steg[1][0];
		if (i == 3)
			d = steg[0][1];
		if (i == 4)
			d = steg[2][1];
		senaste_steg.pop_back();
		senaste_steg.push_back(d);
	}


	if (info.neighbor_cells[0][0] == Cell_content::TRAP)
	{
		Action act = Action::STEP;
		Dir dir = Dir::SE;
		return Command{ act,dir };
	}
	else if (info.neighbor_cells[0][1] == Cell_content::TRAP)
	{
		Action act = Action::STEP;
		Dir dir = Dir::S;
		return Command{ act,dir };
	}
	else if (info.neighbor_cells[0][2] == Cell_content::TRAP)
	{
		Action act = Action::STEP;
		Dir dir = Dir::SW;
		return Command{ act,dir };
	}
	else if (info.neighbor_cells[1][2] == Cell_content::TRAP)
	{
		Action act = Action::STEP;
		Dir dir = Dir::W;
		return Command{ act,dir };
	}
	else if (info.neighbor_cells[2][2] == Cell_content::TRAP)
	{
		Action act = Action::STEP;
		Dir dir = Dir::NW;
		return Command{ act,dir };
	}
	else if (info.neighbor_cells[2][1] == Cell_content::TRAP)
	{
		Action act = Action::STEP;
		Dir dir = Dir::N;
		return Command{ act,dir };
	}
	else if (info.neighbor_cells[2][0] == Cell_content::TRAP)
	{
		Action act = Action::STEP;
		Dir dir = Dir::NE;
		return Command{ act,dir };
	}
	else if (info.neighbor_cells[1][0] == Cell_content::TRAP)
	{
		Action act = Action::STEP;
		Dir dir = Dir::E;
		return Command{ act,dir };
	}

	//Ifall det är en robot norr
	if (info.neighbor_cells[0][1] == Cell_content::ROBOT)
	{
		int i = rand() % 2;
		if (i==0)
		{
			Action act = Action::PLACE_TRAP;
			Dir dir = Dir::NW;
			return Command{ act,dir };
		}
		if (i == 1)
		{
			Dir dir = Dir::NE;
			Action act = Action::PLACE_TRAP;
			return Command{ act,dir };
		}
	}
	//Ifall det är en robot öst
	else if (info.neighbor_cells[1][2] == Cell_content::ROBOT)
	{
		int i = rand() % 2;
		if (i == 0)
		{
			Action act = Action::PLACE_TRAP;
			Dir dir = Dir::NE;
			return Command{ act,dir };
		}
		if (i == 1)
		{
			Dir dir = Dir::SE;
			Action act = Action::PLACE_TRAP;
			return Command{ act,dir };
		}
	}
	//Ifall det är en robot söder
	else if (info.neighbor_cells[2][1] == Cell_content::ROBOT)
	{
		int i = rand() % 2;
		if (i == 0)
		{
			Action act = Action::PLACE_TRAP;
			Dir dir = Dir::SW;
			return Command{ act,dir };
		}
		if (i == 1)
		{
			Dir dir = Dir::SE;
			Action act = Action::PLACE_TRAP;
			return Command{ act,dir };
		}
	}
	//Ifall det är en robot väst
	else if (info.neighbor_cells[1][0] == Cell_content::ROBOT)
	{
		int i = rand() % 2;
		if (i == 0)
		{
			Action act = Action::PLACE_TRAP;
			Dir dir = Dir::NW;
			return Command{ act,dir };
		}
		if (i == 1)
		{
			Dir dir = Dir::SW;
			Action act = Action::PLACE_TRAP;
			return Command{ act,dir };
		}
	}

	if (info.last_event == Event::COLLISION) {
		Action act = Action::STEP;
		srand(time(NULL));
		int i = rand() % 4;
		if (i == 0)
			d = steg[0][1];
		if (i == 1)
			d = steg[1][0];
		if (i == 2)
			d = steg[1][2];
		if (i == 3) {
			d = steg[2][1];
		}
		senaste_steg.pop_back();
		senaste_steg.push_back(d);
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (info.neighbor_cells[i][j] == Cell_content::TREASURE)
			{
				d = steg[i][j];
				break;
			}
		}
	}

	Dir dir = static_cast<Dir>(d);
	Action act = Action::STEP;
	return Command{ act,dir };

}