// A C++ Program to implement A* Search Algorithm 
#include<bits/stdc++.h> 
#include <algorithms.hpp>
using namespace std; 

int ROW; 
int COL; 

// Creating a shortcut for int, int pair type 
typedef pair<int, int> Pair; 

// Creating a shortcut for pair<int, pair<int, int>> type 
typedef pair<double, pair<int, int>> pPair; 

// A structure to hold the neccesary parameters 
struct cell 
{ 
	// Row and Column index of its parent 
	// Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1 
	int parent_i; 
	int parent_j;
	// f = g + h 
	double f; 
	double g;
	double h;
}; 

vector<vector<cell>> cellDetails;

// A Utility Function to check whether given cell (row, col) 
// is a valid cell or not. 
bool isValid(int row, int col) 
{ 
	// Returns true if row number and column number 
	// is in range 
	return (row >= 0) && (row < ROW) && 
		(col >= 0) && (col < COL); 
} 

// A Utility Function to check whether the given cell is 
// blocked or not 
bool isUnBlocked(vector<vector<int>> grid, int row, int col) 
{ 
	// Returns true if the cell is not blocked else false 
	if (grid[row][col] == 1) 
		return (true); 
	else
		return (false); 
} 

// A Utility Function to check whether destination cell has 
// been reached or not 
bool isDestination(int row, int col, Pair dest) 
{ 
	if (row == dest.first && col == dest.second) 
		return (true); 
	else
		return (false); 
} 

// A Utility Function to calculate the 'h' heuristics. 
double calculateHValue(int row, int col, Pair dest) 
{ 
	// Return using the distance formula 
	return ((double)sqrt ((row-dest.first)*(row-dest.first) 
						+ (col-dest.second)*(col-dest.second))); 
} 

// A Utility Function to trace the path from the source 
// to destination 
void tracePath(vector<vector<cell>> cellDetails, Pair dest) 
{ 
	//std::cout << "The Path is " << endl;  -----
	int row = dest.first; 
	int col = dest.second; 

	stack<Pair> Path; 

	while (!(cellDetails[row][col].parent_i == row 
			&& cellDetails[row][col].parent_j == col )) 
	{ 
		Path.push (make_pair (row, col)); 
		int temp_row = cellDetails[row][col].parent_i; 
		int temp_col = cellDetails[row][col].parent_j; 
		row = temp_row; 
		col = temp_col; 
	} 

	Path.push (make_pair (row, col)); 
	while (!Path.empty()) 
	{ 
		pair<int,int> p = Path.top(); 
		Path.pop();
		std::cout << p.first; 
		std::cout << " "; 
		std::cout << p.second << endl; 
	} 

	return; 
} 

void algorithms::generar1(int row1, int col1){
    for(unsigned int i=0; i<row1; i++){
        vector<cell> v1; 
        for(unsigned int j=0; j<col1; j++){
            cell x;
			x.f = FLT_MAX;
			x.g = FLT_MAX; 
			x.h = FLT_MAX; 
			x.parent_i = -1; 
			x.parent_j = -1; 
			v1.push_back(x);
        }
        cellDetails.push_back(v1); 
    }
}

// A Function to find the shortest path between 
// a given source cell to a destination cell according 
// to A* Search Algorithm 
void algorithms::algoritmo_aStar(Pair src, Pair dest, vector<vector<int>> mapa) 
{ 
	ROW = mapa.size();
    COL = mapa[0].size(); 

	// If the source is out of range 
	if (isValid (src.first, src.second) == false) 
	{ 
		std::cout << "Source is invalid" << endl; 
		return; 
	} 

	// If the destination is out of range 
	if (isValid (dest.first, dest.second) == false) 
	{ 
		std::cout << "Destination is invalid" << endl;
		return; 
	} 

	// Either the source or the destination is blocked 
	if (isUnBlocked(mapa, src.first, src.second) == false || 
			isUnBlocked(mapa, dest.first, dest.second) == false) 
	{ 
		std::cout << "Source or the destination is blocked" << endl;
		return; 
	} 

	// If the destination cell is the same as source cell 
	if (isDestination(src.first, src.second, dest) == true) 
	{ 
		std::cout << "We are already at the destination" << endl;
		return; 
	} 

	// Create a closed list and initialise it to false which means 
	// that no cell has been included yet 
	// This closed list is implemented as a boolean 2D array 
	bool closedList[ROW][COL]; 
	memset(closedList, false, sizeof (closedList)); 

	// Declare a 2D array of structure to hold the details 
	//of that cell 
	//cell cellDetails[ROW][COL]; 

	//vector<vector<cell>> cellDetails;
	generar1(ROW, COL);

	int i, j; 

	for (i=0; i<ROW; i++) 
	{ 
		for (j=0; j<COL; j++) 
		{ 
			cellDetails[i][j].f = FLT_MAX; 
			cellDetails[i][j].g = FLT_MAX; 
			cellDetails[i][j].h = FLT_MAX; 
			cellDetails[i][j].parent_i = -1; 
			cellDetails[i][j].parent_j = -1; 
		} 
	} 

	// Initialising the parameters of the starting node 
	i = src.first, j = src.second; 
	cellDetails[i][j].f = 0.0; 
	cellDetails[i][j].g = 0.0; 
	cellDetails[i][j].h = 0.0; 
	cellDetails[i][j].parent_i = i; 
	cellDetails[i][j].parent_j = j; 

	/* 
	Create an open list having information as- 
	<f, <i, j>> 
	where f = g + h, 
	and i, j are the row and column index of that cell 
	Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1 
	This open list is implenented as a set of pair of pair.*/
	set<pPair> openList; 

	// Put the starting cell on the open list and set its 
	// 'f' as 0 
	openList.insert(make_pair (0.0, make_pair (i, j))); 

	// We set this boolean value as false as initially 
	// the destination is not reached. 
	bool foundDest = false; 

	while (!openList.empty()) 
	{ 
		pPair p = *openList.begin(); 

		// Remove this vertex from the open list 
		openList.erase(openList.begin()); 

		// Add this vertex to the closed list 
		i = p.second.first; 
		j = p.second.second; 
		closedList[i][j] = true; 
	
	/* 
		Generating all the 8 successor of this cell 

			N.W N N.E 
			\ | / 
			\ | / 
			W----Cell----E 
				/ | \ 
			/ | \ 
			S.W S S.E 

		Cell-->Popped Cell (i, j) 
		N --> North	 (i-1, j) 
		S --> South	 (i+1, j) 
		E --> East	 (i, j+1) 
		W --> West		 (i, j-1) 
		N.E--> North-East (i-1, j+1) 
		N.W--> North-West (i-1, j-1) 
		S.E--> South-East (i+1, j+1) 
		S.W--> South-West (i+1, j-1)*/

		// To store the 'g', 'h' and 'f' of the 8 successors 
		double gNew, hNew, fNew; 

		//----------- 1st Successor (North) ------------ 

		// Only process this cell if this is a valid one 
		if (isValid(i-1, j) == true) 
		{ 
			// If the destination cell is the same as the 
			// current successor 
			if (isDestination(i-1, j, dest) == true) 
			{ 
				// Set the Parent of the destination cell 
				cellDetails[i-1][j].parent_i = i; 
				cellDetails[i-1][j].parent_j = j; 
				std::cout << "The destination cell is found" << endl;
				tracePath (cellDetails, dest); 
				foundDest = true; 
				return; 
			} 
			// If the successor is already on the closed 
			// list or if it is blocked, then ignore it. 
			// Else do the following 
			else if (closedList[i-1][j] == false && 
					isUnBlocked(mapa, i-1, j) == true) 
			{ 
				gNew = cellDetails[i][j].g + 1.0; 
				hNew = calculateHValue (i-1, j, dest); 
				fNew = gNew + hNew; 

				// If it isn’t on the open list, add it to 
				// the open list. Make the current square 
				// the parent of this square. Record the 
				// f, g, and h costs of the square cell 
				//			 OR 
				// If it is on the open list already, check 
				// to see if this path to that square is better, 
				// using 'f' cost as the measure. 
				if (cellDetails[i-1][j].f == FLT_MAX || 
						cellDetails[i-1][j].f > fNew) 
				{ 
					openList.insert( make_pair(fNew, 
											make_pair(i-1, j))); 

					// Update the details of this cell 
					cellDetails[i-1][j].f = fNew; 
					cellDetails[i-1][j].g = gNew; 
					cellDetails[i-1][j].h = hNew; 
					cellDetails[i-1][j].parent_i = i; 
					cellDetails[i-1][j].parent_j = j; 
				} 
			} 
		} 

		//----------- 2nd Successor (South) ------------ 

		// Only process this cell if this is a valid one 
		if (isValid(i+1, j) == true) 
		{ 
			// If the destination cell is the same as the 
			// current successor 
			if (isDestination(i+1, j, dest) == true) 
			{ 
				// Set the Parent of the destination cell 
				cellDetails[i+1][j].parent_i = i; 
				cellDetails[i+1][j].parent_j = j; 
				std::cout << "The destination cell is found" << endl;
				tracePath(cellDetails, dest); 
				foundDest = true; 
				return; 
			} 
			// If the successor is already on the closed 
			// list or if it is blocked, then ignore it. 
			// Else do the following 
			else if (closedList[i+1][j] == false && 
					isUnBlocked(mapa, i+1, j) == true) 
			{ 
				gNew = cellDetails[i][j].g + 1.0; 
				hNew = calculateHValue(i+1, j, dest); 
				fNew = gNew + hNew; 

				// If it isn’t on the open list, add it to 
				// the open list. Make the current square 
				// the parent of this square. Record the 
				// f, g, and h costs of the square cell 
				//			 OR 
				// If it is on the open list already, check 
				// to see if this path to that square is better, 
				// using 'f' cost as the measure. 
				if (cellDetails[i+1][j].f == FLT_MAX || 
						cellDetails[i+1][j].f > fNew) 
				{ 
					openList.insert( make_pair (fNew, make_pair (i+1, j))); 
					// Update the details of this cell 
					cellDetails[i+1][j].f = fNew; 
					cellDetails[i+1][j].g = gNew; 
					cellDetails[i+1][j].h = hNew; 
					cellDetails[i+1][j].parent_i = i; 
					cellDetails[i+1][j].parent_j = j; 
				} 
			} 
		} 

		//----------- 3rd Successor (East) ------------ 

		// Only process this cell if this is a valid one 
		if (isValid (i, j+1) == true) 
		{ 
			// If the destination cell is the same as the 
			// current successor 
			if (isDestination(i, j+1, dest) == true) 
			{ 
				// Set the Parent of the destination cell 
				cellDetails[i][j+1].parent_i = i; 
				cellDetails[i][j+1].parent_j = j; 
				std::cout << "The destination cell is found" << endl;
				tracePath(cellDetails, dest); 
				foundDest = true; 
				return; 
			} 

			// If the successor is already on the closed 
			// list or if it is blocked, then ignore it. 
			// Else do the following 
			else if (closedList[i][j+1] == false && 
					isUnBlocked (mapa, i, j+1) == true) 
			{ 
				gNew = cellDetails[i][j].g + 1.0; 
				hNew = calculateHValue (i, j+1, dest); 
				fNew = gNew + hNew; 

				// If it isn’t on the open list, add it to 
				// the open list. Make the current square 
				// the parent of this square. Record the 
				// f, g, and h costs of the square cell 
				//			 OR 
				// If it is on the open list already, check 
				// to see if this path to that square is better, 
				// using 'f' cost as the measure. 
				if (cellDetails[i][j+1].f == FLT_MAX || 
						cellDetails[i][j+1].f > fNew) 
				{ 
					openList.insert( make_pair(fNew, 
										make_pair (i, j+1))); 

					// Update the details of this cell 
					cellDetails[i][j+1].f = fNew; 
					cellDetails[i][j+1].g = gNew; 
					cellDetails[i][j+1].h = hNew; 
					cellDetails[i][j+1].parent_i = i; 
					cellDetails[i][j+1].parent_j = j; 
				} 
			} 
		} 

		//----------- 4th Successor (West) ------------ 

		// Only process this cell if this is a valid one 
		if (isValid(i, j-1) == true) 
		{ 
			// If the destination cell is the same as the 
			// current successor 
			if (isDestination(i, j-1, dest) == true) 
			{ 
				// Set the Parent of the destination cell 
				cellDetails[i][j-1].parent_i = i; 
				cellDetails[i][j-1].parent_j = j; 
				std::cout << "The destination cell is found" << endl;
				tracePath(cellDetails, dest); 
				foundDest = true; 
				return; 
			} 

			// If the successor is already on the closed 
			// list or if it is blocked, then ignore it. 
			// Else do the following 
			else if (closedList[i][j-1] == false && 
					isUnBlocked(mapa, i, j-1) == true) 
			{ 
				gNew = cellDetails[i][j].g + 1.0; 
				hNew = calculateHValue(i, j-1, dest); 
				fNew = gNew + hNew; 

				// If it isn’t on the open list, add it to 
				// the open list. Make the current square 
				// the parent of this square. Record the 
				// f, g, and h costs of the square cell 
				//			 OR 
				// If it is on the open list already, check 
				// to see if this path to that square is better, 
				// using 'f' cost as the measure. 
				if (cellDetails[i][j-1].f == FLT_MAX || 
						cellDetails[i][j-1].f > fNew) 
				{ 
					openList.insert( make_pair (fNew, 
										make_pair (i, j-1))); 

					// Update the details of this cell 
					cellDetails[i][j-1].f = fNew; 
					cellDetails[i][j-1].g = gNew; 
					cellDetails[i][j-1].h = hNew; 
					cellDetails[i][j-1].parent_i = i; 
					cellDetails[i][j-1].parent_j = j; 
				} 
			} 
		} 

		//----------- 5th Successor (North-East) ------------ 

		// Only process this cell if this is a valid one 
		if (isValid(i-1, j+1) == true) 
		{ 
			// If the destination cell is the same as the 
			// current successor 
			if (isDestination(i-1, j+1, dest) == true) 
			{ 
				// Set the Parent of the destination cell 
				cellDetails[i-1][j+1].parent_i = i; 
				cellDetails[i-1][j+1].parent_j = j; 
				std::cout << "The destination cell is found" << endl;
				tracePath (cellDetails, dest); 
				foundDest = true; 
				return; 
			} 

			// If the successor is already on the closed 
			// list or if it is blocked, then ignore it. 
			// Else do the following 
			else if (closedList[i-1][j+1] == false && 
					isUnBlocked(mapa, i-1, j+1) == true) 
			{ 
				gNew = cellDetails[i][j].g + 1.414; 
				hNew = calculateHValue(i-1, j+1, dest); 
				fNew = gNew + hNew; 

				// If it isn’t on the open list, add it to 
				// the open list. Make the current square 
				// the parent of this square. Record the 
				// f, g, and h costs of the square cell 
				//			 OR 
				// If it is on the open list already, check 
				// to see if this path to that square is better, 
				// using 'f' cost as the measure. 
				if (cellDetails[i-1][j+1].f == FLT_MAX || 
						cellDetails[i-1][j+1].f > fNew) 
				{ 
					openList.insert( make_pair (fNew, 
									make_pair(i-1, j+1))); 

					// Update the details of this cell 
					cellDetails[i-1][j+1].f = fNew; 
					cellDetails[i-1][j+1].g = gNew; 
					cellDetails[i-1][j+1].h = hNew; 
					cellDetails[i-1][j+1].parent_i = i; 
					cellDetails[i-1][j+1].parent_j = j; 
				} 
			} 
		} 

		//----------- 6th Successor (North-West) ------------ 

		// Only process this cell if this is a valid one 
		if (isValid (i-1, j-1) == true) 
		{ 
			// If the destination cell is the same as the 
			// current successor 
			if (isDestination (i-1, j-1, dest) == true) 
			{ 
				// Set the Parent of the destination cell 
				cellDetails[i-1][j-1].parent_i = i; 
				cellDetails[i-1][j-1].parent_j = j; 
				std::cout << "The destination cell is found" << endl;
				tracePath (cellDetails, dest); 
				foundDest = true; 
				return; 
			} 

			// If the successor is already on the closed 
			// list or if it is blocked, then ignore it. 
			// Else do the following 
			else if (closedList[i-1][j-1] == false && 
					isUnBlocked(mapa, i-1, j-1) == true) 
			{ 
				gNew = cellDetails[i][j].g + 1.414; 
				hNew = calculateHValue(i-1, j-1, dest); 
				fNew = gNew + hNew; 

				// If it isn’t on the open list, add it to 
				// the open list. Make the current square 
				// the parent of this square. Record the 
				// f, g, and h costs of the square cell 
				//			 OR 
				// If it is on the open list already, check 
				// to see if this path to that square is better, 
				// using 'f' cost as the measure. 
				if (cellDetails[i-1][j-1].f == FLT_MAX || 
						cellDetails[i-1][j-1].f > fNew) 
				{ 
					openList.insert( make_pair (fNew, make_pair (i-1, j-1))); 
					// Update the details of this cell 
					cellDetails[i-1][j-1].f = fNew; 
					cellDetails[i-1][j-1].g = gNew; 
					cellDetails[i-1][j-1].h = hNew; 
					cellDetails[i-1][j-1].parent_i = i; 
					cellDetails[i-1][j-1].parent_j = j; 
				} 
			} 
		} 

		//----------- 7th Successor (South-East) ------------ 

		// Only process this cell if this is a valid one 
		if (isValid(i+1, j+1) == true) 
		{ 
			// If the destination cell is the same as the 
			// current successor 
			if (isDestination(i+1, j+1, dest) == true) 
			{ 
				// Set the Parent of the destination cell 
				cellDetails[i+1][j+1].parent_i = i; 
				cellDetails[i+1][j+1].parent_j = j; 
				std::cout << "The destination cell is found" << endl;
				tracePath (cellDetails, dest); 
				foundDest = true; 
				return; 
			} 

			// If the successor is already on the closed 
			// list or if it is blocked, then ignore it. 
			// Else do the following 
			else if (closedList[i+1][j+1] == false && 
					isUnBlocked(mapa, i+1, j+1) == true) 
			{ 
				gNew = cellDetails[i][j].g + 1.414; 
				hNew = calculateHValue(i+1, j+1, dest); 
				fNew = gNew + hNew; 

				// If it isn’t on the open list, add it to 
				// the open list. Make the current square 
				// the parent of this square. Record the 
				// f, g, and h costs of the square cell 
				//			 OR 
				// If it is on the open list already, check 
				// to see if this path to that square is better, 
				// using 'f' cost as the measure. 
				if (cellDetails[i+1][j+1].f == FLT_MAX || 
						cellDetails[i+1][j+1].f > fNew) 
				{ 
					openList.insert(make_pair(fNew, 
										make_pair (i+1, j+1))); 

					// Update the details of this cell 
					cellDetails[i+1][j+1].f = fNew; 
					cellDetails[i+1][j+1].g = gNew; 
					cellDetails[i+1][j+1].h = hNew; 
					cellDetails[i+1][j+1].parent_i = i; 
					cellDetails[i+1][j+1].parent_j = j; 
				} 
			} 
		} 

		//----------- 8th Successor (South-West) ------------ 

		// Only process this cell if this is a valid one 
		if (isValid (i+1, j-1) == true) 
		{ 
			// If the destination cell is the same as the 
			// current successor 
			if (isDestination(i+1, j-1, dest) == true) 
			{ 
				// Set the Parent of the destination cell 
				cellDetails[i+1][j-1].parent_i = i; 
				cellDetails[i+1][j-1].parent_j = j; 
				std::cout << "The destination cell is found" << endl; 
				tracePath(cellDetails, dest); 
				foundDest = true; 
				return; 
			} 

			// If the successor is already on the closed 
			// list or if it is blocked, then ignore it. 
			// Else do the following 
			else if (closedList[i+1][j-1] == false && 
					isUnBlocked(mapa, i+1, j-1) == true) 
			{ 
				gNew = cellDetails[i][j].g + 1.414; 
				hNew = calculateHValue(i+1, j-1, dest); 
				fNew = gNew + hNew; 

				// If it isn’t on the open list, add it to 
				// the open list. Make the current square 
				// the parent of this square. Record the 
				// f, g, and h costs of the square cell 
				//			 OR 
				// If it is on the open list already, check 
				// to see if this path to that square is better, 
				// using 'f' cost as the measure. 
				if (cellDetails[i+1][j-1].f == FLT_MAX || 
						cellDetails[i+1][j-1].f > fNew) 
				{ 
					openList.insert(make_pair(fNew, 
										make_pair(i+1, j-1))); 

					// Update the details of this cell 
					cellDetails[i+1][j-1].f = fNew; 
					cellDetails[i+1][j-1].g = gNew; 
					cellDetails[i+1][j-1].h = hNew; 
					cellDetails[i+1][j-1].parent_i = i; 
					cellDetails[i+1][j-1].parent_j = j; 
				} 
			} 
		} 
	} 

	// When the destination cell is not found and the open 
	// list is empty, then we conclude that we failed to 
	// reach the destiantion cell. This may happen when the 
	// there is no way to destination cell (due to blockages) 
	if (foundDest == false) 
		std::cout << "Failed to find the Destination Cell" << endl;

	return; 
} 
