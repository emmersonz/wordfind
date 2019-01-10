/*
wordfind.cc
EMMERSON ZHAIME
LAB NUMBER 2
09/12/2014

The code searches for a word in a grid and if if finds the word it changes the letters making 
the word in the grid to uppercase and it writes FOUND. If it does not find the word, it writes 
NOT FOUND.

 */
#include <wordgrid.h>

using namespace std;

//-function: bool find(string word, wordgrid & grid)------------------------
// PRE: word consists of lowercase letters
// POST: If word is found in grid, starting anywhere 
//       and in any of the 8 directions, it is converted
//       to uppercase in the grid, and true is returned.
//       otherwise, grid is unchanged, and false is returned.
string substr( const string & original, size_t start, size_t length)
{
  /* This function takes a constructed word in a given direction and 
     make a substring of the word starting from a given position of
     of the string to a given ending position
   */
  string new_string;
  for(size_t c = start; c < start + length and original.length();c++)
    new_string = new_string + original[c];
  return new_string;

}
size_t distance_to_edge(size_t row, size_t col, size_t D, int dr, int dc)
{
  /* The function calculates the distance that a cell in from the edge 
     if we count cells in a giiven direction. dr is the change is rows
     and dc is the change in column
  */
  int number_of_cells;
  /*Determines the distance from the cell to the edge if counting in the
    dr = 1 and dc = -1 direction
   */
  if(dr == 1 and dc == -1)
    {
      if (row > col)
	number_of_cells = col + 1;
      else 
	number_of_cells = row + 1;
    }
  /*Determines the distance from the cell to the edge if counting in the
    dr = 1 and dc = 0 direction
  */
  else if(dr ==-1 and dc == 0)
    number_of_cells = row + 1;

  /*Determines the distance from the cell to the edge if counting in the
    dr = 1 and dc = 0 direction
  */
  else if(dr == -1 and dc == 1)
    {
      if (row + 1 < D - col)
	number_of_cells = row + 1;
      else
        number_of_cells = D-col;
    }

  /*Determines the distance from the cell to the edge if counting in the
    dr = 0 and dc = -1  direction
  */
  else if (dr== 0 and dc == -1)
    number_of_cells = col + 1;

  /*Determines the distance from the cell to the edge if counting in the
    dr = 0 and dc = 1 direction
  */
  else if (dr == 0 and dc == 1)
    number_of_cells = D - col;

  /*Determines the distance from the cell to the edge if counting in the
    dr = 1 and dc = -1 direction
  */
  else if (dr == 1 and dc == -1)
    {
      if (col +1 < D - row)
	number_of_cells = col + 1;
      else 
	number_of_cells = D - row;
    }

  /*Determines the distance from the cell to the edge if counting in the
    dr = 1 and dc = 0 direction
  */
  else if (dr ==1 and dc == 0)
    number_of_cells = D-row;

 /*Determines the distance from the cell to the edge if counting in the
    dr = 1 and dc = 1 direction
  */
  else if (dr == 1 and dc == 1)
    {
      if (D-row < D-col)
	number_of_cells = D - row;
      else
	number_of_cells  = D - col;
    }

  return number_of_cells;

}
       	    
void uppercase(size_t r, size_t c, int dr, int dc, wordgrid & grid, string word)
{
  /* This function changes the letters of the found word in the
     grid into uppercase
   */
  for(size_t x = 0; x < word.length(); x++)
    grid.set(r + x*dr, c + x*dc, ( grid.get(r + x*dr, c + x*dc)- 'a' + 'A'));
  
} 

bool find_here(size_t r, size_t c, string word, wordgrid & grid)
{ 
  /* This function searches the word in the grid and turns its 
     letters into uppercase and returns true.
   */
  for(size_t dr = -1; dr  <= 1; dr++){
    for(size_t dc = -1; dc <= 1; dc++){
      if(dr == 0 && dc == 0)
	continue;
      size_t dis = distance_to_edge(r, c, grid.size(), dr, dc );
      string constructed_word;
      for ( size_t count = 0; count < dis; count = count + 1){
	  constructed_word += grid.get(r, c);
          r = r + dr;
	  c = c + dc;
      }
      if (substr( constructed_word, 0, word.length()) == word){
	uppercase(r, c, dr, dc, grid, word );
	return true;
      }
    }
  }
  return false;      	   	
}

bool find(string word, wordgrid & grid)
{
  /* This function calls another function that searches for the
     word at all cells in the grid
  */
  for (size_t r = 0; r < grid.size(); r++){
    for(size_t c = 0; c < grid.size(); c++){
      bool status = find_here(r,c, word, grid);
      if(status)
	return true;
    }
  }
  return false;
}

//------------------------------------------------------------------------
int main()
{
  size_t dim = 0;  // size of the word grid
  string word = ""; // word to search for
  bool found = false;  // whether the word is found in the grid.
  string one_row = ""; // dim characters (one row) read from stdin
  string all_rows = ""; // dim x dim characters

  // SETUP
  cin >> dim;  // read the dimension 
  // read each row and append to the string of all rows
  for (size_t r = 0; r < dim ; r = r + 1) {
    cin >> one_row;
    all_rows += one_row;
  }
  wordgrid grid(dim, all_rows);  // create the grid from that data
  cin >> word; // read the word

  // SEARCH  (you do)
  found = find(word, grid);
  
  // REPORT
  if (found) {
    cout << "FOUND!" << endl;
    cout << grid;
  }    
  else
    cout << "NOT FOUND!" << endl;
}
