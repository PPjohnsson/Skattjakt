//Team Aliens consists of: Elias Hermansson, Sofie Bengts and Felicia Lorentzon

#include "pch.h"
#include <debugapi.h>
#include "RobotControl_Player2.h"
#include <vector>
#include <string>

using namespace Player2;
using namespace std;

int lastStep[4] = { 3, 2, 1, 0 };
int x = 0;

void updateLastStep(int);
int getLastStep();

Player2::RobotControl::RobotControl()
{
	robot_bitmap_row = 7;          // Pick a unique monster icon for your robot!
	robot_bitmap_col = 26;
	team_name = L"Team Aliens";
}


Command Player2::RobotControl::do_command(const Info& info)
{
	OutputDebugString(L"Nu körs do_command()\n");
	if (info.last_event == Event::COLLISION)
		OutputDebugString(L"Krockade i förra rundan!\n");

	Dir dir;
	Action act;

	enum compass { N = 0, E, S, W, NE, SE, SW, NW };

	/*The coordinates of the neighbor cells = {{{0,0},{0,1},{0,2}},
											   {{1,0},{ R },{1,2}},
											   {{2,0},{2,1},{2,2}}};*/

											   //The directions  N = 0, E, S, W, NE, SE, SW, NW
	vector<vector<int>> directions = { {7, 0, 4},
									   {3, 0, 1},
									   {6, 2, 5 } };

	//Check for treasure
	for (int x = 0; x < 3; x++) {
		for (int y = 0; y < 3; y++) {
			if (info.neighbor_cells[x][y] == Cell_content::TREASURE) {

				x = directions[x][y];
				updateLastStep(x);
				OutputDebugString(L"Hittade en skatt!\n");
				dir = static_cast<Dir>(x);
				act = Action::STEP;
				return Command{ act,dir };
			}
		}
	}

	// Check for neighbor walls/robots/traps to avoid
	for (int x = 0; x < 3; x++) {
		for (int y = 0; y < 3; y++) {
			if (directions[x][y] == getLastStep()) {

				if (!(info.neighbor_cells[x][y] == Cell_content::WALL)
					&& !(info.neighbor_cells[x][y] == Cell_content::TRAP)
					&& !(info.neighbor_cells[x][y] == Cell_content::ROBOT)) {

					x = getLastStep();
					OutputDebugString(L"Går i förgående riktning!\n");
					dir = static_cast<Dir>(x);
					act = Action::STEP;
					return Command{ act,dir };
				}
			}
		}
	}

	//To avoid getting stuck in a loop
	if ((lastStep[0] == lastStep[2]) && (lastStep[1] == lastStep[3])) {
		OutputDebugString(L"Sitter fast i en loop!\n");
		do {
			x = rand() % 8;
		} while ((x == lastStep[0]));
	}
	else {

		//position in left upper corner
		if ((info.neighbor_cells[0][0] == Cell_content::WALL)
			|| (info.neighbor_cells[0][1] == Cell_content::WALL)
			|| (info.neighbor_cells[1][0] == Cell_content::WALL)) {

			if (!(info.neighbor_cells[2][2] == Cell_content::WALL)
				|| !(info.neighbor_cells[2][2] == Cell_content::TRAP)
				|| !(info.neighbor_cells[2][2] == Cell_content::ROBOT)) {
				x = compass::SE;
			}
		}

		//position in left lower corner
		else if ((info.neighbor_cells[1][0] == Cell_content::WALL)
			|| (info.neighbor_cells[2][0] == Cell_content::WALL)
			|| (info.neighbor_cells[2][1] == Cell_content::WALL)) {

			if (!(info.neighbor_cells[0][2] == Cell_content::WALL)
				|| !(info.neighbor_cells[0][2] == Cell_content::TRAP)
				|| !(info.neighbor_cells[0][2] == Cell_content::ROBOT)) {
				x = compass::NE;
			}
		}

		//position in right upper corner
		else if ((info.neighbor_cells[0][1] == Cell_content::WALL)
			|| (info.neighbor_cells[0][2] == Cell_content::WALL)
			|| (info.neighbor_cells[1][2] == Cell_content::WALL)) {

			if (!(info.neighbor_cells[2][0] == Cell_content::WALL)
				|| !(info.neighbor_cells[2][0] == Cell_content::TRAP)
				|| !(info.neighbor_cells[2][0] == Cell_content::ROBOT)) {
				x = compass::SW;
			}
		}

		//position in right lower corner
		else if ((info.neighbor_cells[1][2] == Cell_content::WALL)
			|| (info.neighbor_cells[2][1] == Cell_content::WALL)
			|| (info.neighbor_cells[2][2] == Cell_content::WALL)) {

			if (!(info.neighbor_cells[0][0] == Cell_content::WALL)
				|| !(info.neighbor_cells[0][0] == Cell_content::TRAP)
				|| !(info.neighbor_cells[0][0] == Cell_content::ROBOT)) {
				x = compass::NW;
			}
		}
		else {
			x = rand() % 8;
		}
	}

	updateLastStep(x);
	dir = static_cast<Dir>(x);
	act = Action::STEP;
	if (rand() % 20 == 0)
		act = Action::PLACE_TRAP;
	return Command{ act,dir };
}

void updateLastStep(int step) {
	lastStep[0] = lastStep[1];
	lastStep[1] = lastStep[2];
	lastStep[2] = lastStep[3];
	lastStep[3] = step;
}

int getLastStep() {
	return lastStep[3];
}
