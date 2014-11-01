#include<stdio.h>
#include<string.h>

/*	in the program sudokus have been represented as 9*9*10 option arrays where
	the 1st index indicates the row of the sudoku grid element
	the 2nd index indicates the column of the sudoku grid element
	the 3rd index represents the grid element chosen at the 0th position (or 0)
	and the options for the sudoku grid element in the 1-9th positions (or 0) */

//function to initialize the sudoku grid
void initialize(char grid[9][9][10]) {
	char i,j,k;
	for(i=0;i<9;++i)
		for(j=0;j<9;++j)
			for(k=0;k<10;++k)
				grid[i][j][k]=k;
}

//function to parse string of 9*9 singledigit integers into the sudoku grid
void input(char grid[9][9][10],char string[81]) {
	char i,j,k;
	for(i=0;i<9;++i)
		for(j=0;j<9;++j) {
			grid[i][j][0]=string[9*i+j]-'0';
			//nullifying choices if grid element is set
			if(grid[i][j][0])
				for(k=1;k<10;++k)
					if(k!=grid[i][j][0])
						grid[i][j][k]=0;
		}
}

//function to print the solved sudoku grid
void output(char grid[9][9][10]) {
	char i,j;
	for(i=0;i<9;++i) {
		for(j=0;j<9;++j)
			putchar('0'+grid[i][j][0]);
		putchar('\n');
	}
}

//function to check options of sudoku grid element [m][n] by cell
int cellsort(char grid[9][9][10],char m,char n) {
	if(grid[m][n][0])
		return 0;
	char i,j,k,f=0;
	//for each option of grid element [m][n]
	for(i=j=0,k=1;k<10;++k)
		//counting options of grid element
		if(!grid[m][n][k])
			++i;
		//storing last option
		else
			j=k;
	//setting grid element if only one option available
	if(i==8)
		grid[m][n][0]=j,f=1;
	return f;
}

//function to check options of sudoku grid element [m][n] by row
int rowsort(char grid[9][9][10],char m,char n) {
	if(grid[m][n][0])
		return 0;
	char i,j,k,f=0;
	//for each option of grid element [m][n]
	for(k=1;k<10;++k)
		if(grid[m][n][k]) {
			//counting options of option in row
			for(i=0,j=0;j<9;++j)
				if(!grid[m][j][k])
					i++;
			//setting grid element if only one option available
			if(i==8) {
				grid[m][n][0]=k;
				for(i=1;i<10;++i)
					if(i!=k)
						if(grid[m][n][i])
							grid[m][n][i]=0,f=1;
			}
		}
	return f;
}

//function to check options of sudoku grid element [m][n] by column
int columnsort(char grid[9][9][10],char m,char n) {
	if(grid[m][n][0])
		return 0;
	char i,j,k,f=0;
	//for each option of grid element [m][n]
	for(k=1;k<10;++k)
		if(grid[m][n][k]) {
			//counting options of option in column
			for(i=0,j=0;i<9;++i)
				if(!grid[i][n][k])
					j++;
			//setting grid element if only one option available
			if(j==8) {
				grid[m][n][0]=k;
				for(j=1;j<10;++j)
					if(j!=k)
						if(grid[m][n][j])
							grid[m][n][j]=0,f=1;
			}
		}
	return f;
}

//function to check options of sudoku grid element [m][n] by grid
int gridsort(char grid[9][9][10],char m,char n) {
	if(grid[m][n][0])
		return 0;
	char i,j,k,l,f=0;
	//for each option of grid element [m][n]
	for(k=1;k<10;++k)
		if(grid[m][n][k]) {
			l=0;
			//counting options of option in grid
			for(i=3*(m/3);i<3*(m/3+1);++i)
				for(j=3*(n/3);j<3*(n/3+1);++j)
					if(!grid[i][j][k])
						l++;
			//setting grid element if only one option available
			if(l==8) {
				grid[m][n][0]=k;
					for(l=1;l<10;++l)
						if(l!=k)
							if(grid[m][n][l])
								grid[m][n][l]=0,f=1;
			}
	}
	return f;
}

//function to eliminate options of row of sudoku grid element [m][n]
int roweliminate(char grid[9][9][10],char m,char n) {
	if(!grid[m][n][0])
		return 0;
	char j,f=0;
	//for each grid element in row of grid element [m][n]
	for(j=0;j<9;++j)
		if(j!=n)
			//eliminating option set as grid element [m][n]
			if(grid[m][j][grid[m][n][0]])
				grid[m][j][grid[m][n][0]]=0,f=1;
	return f;
}

//function to eliminate options of column of sudoku grid element [m][n]
int columneliminate(char grid[9][9][10],char m,char n) {
	if(!grid[m][n][0])
		return 0;
	char i,f=0;
	//for each grid element in column of grid element [m][n]
	for(i=0;i<9;++i)
		if(i!=m)
			//eliminating option set as grid element [m][n]
			if(grid[i][n][grid[m][n][0]])
				grid[i][n][grid[m][n][0]]=0,f=1;
	return f;
}

//function to eliminate options of grid of sudoku grid element [m][n]
int grideliminate(char grid[9][9][10],char m,char n) {
	if(!grid[m][n][0])
		return 0;
	char i,j,f=0;
	//for each grid element in grid of grid element [m][n]
	for(i=3*(m/3);i<3*(m/3+1);++i)
		for(j=3*(n/3);j<3*(n/3+1);++j)
			if(!(i==m&&j==n))
				//eliminating option set as grid element [m][n]
				if(grid[i][j][grid[m][n][0]])
					grid[i][j][grid[m][n][0]]=0,f=1;
	return f;
}

//function to eliminate options of row of sudoku grid element [m][n] by grid
int gridroweliminate(char grid[9][9][10],char m,char n) {
	char i,j,k,l,f=0;
	//for each option of grid element [m][n]
	for(k=1;k<10;++k) {
		l=0;
		//counting options of option in grid but not in row of grid element [m][n]
		for(i=3*(m/3);i<3*(m/3+1);++i)
			for(j=3*(n/3);j<3*(n/3+1);++j)
				if(i!=m)
					if(!grid[i][j][k])
						++l;
		//eliminating options of grid elements of row if only one option available
		if(l==6)
			for(j=0;j<9;++j)
				if(j<3*(n/3)||j>=3*(n/3+1))
					if(grid[m][j][k])
						grid[m][j][k]=0,f=1;
	}
	return f;
}

//function to eliminate options of column of sudoku grid element [m][n] by grid
int gridcolumneliminate(char grid[9][9][10],char m,char n) {
	char i,j,k,l,f=0;
	//for each option of grid element [m][n]
	for(k=1;k<10;++k) {
		l=0;
		//counting options of option in grid but not in column of grid element [m][n]
		for(i=3*(m/3);i<3*(m/3+1);++i)
			for(j=3*(n/3);j<3*(n/3+1);++j)
				if(j!=n)
					if(!grid[i][j][k])
						++l;
		//eliminating options of grid elements of column if only one option available
		if(l==6)
			for(i=0;i<9;++i)
				if(i<3*(m/3)||i>=3*(m/3+1))
					if(grid[i][n][k])
						grid[i][n][k]=0,f=1;
	}
	return f;
}

//function to solve the sudoku grid as far as possible without guessing
void solve(char grid[9][9][10]) {
	char i,j,f;
	do
		for(f=i=0;i<9;++i)
			for(j=0;j<9;++j) {
				f|=gridcolumneliminate(grid,i,j);
				f|=gridroweliminate(grid,i,j);
				f|=grideliminate(grid,i,j);
				f|=columneliminate(grid,i,j);
				f|=roweliminate(grid,i,j);
				f|=gridsort(grid,i,j);
				f|=columnsort(grid,i,j);
				f|=rowsort(grid,i,j);
				f|=cellsort(grid,i,j);
		}
	while(f);
}

//function to check whether sudoku grid has been solved
int solved(char grid[9][9][10]) {
	char i,j;
	for(i=0;i<9;++i)
		for(j=0;j<9;++j)
			if(!grid[i][j][0])
				return 0;
	return 1;
}

//function to initialize newgrid with oldgrid having guessed element [m][n] as o
void guessed(char oldgrid[9][9][10],char newgrid[9][9][10],char m,char n,char o) {
	char i,j,k;
	for(i=0;i<9;++i)
		for(j=0;j<9;++j)
			for(k=0;k<10;++k)
				newgrid[i][j][k]=oldgrid[i][j][k];
	newgrid[m][n][0]=o;
	for(k=1;k<10;++k)
		if(k!=o)
			newgrid[m][n][k]=0;
}

//function to recursively solve sudoku oldgrid by guessing and backtracking
int guess(char oldgrid[9][9][10]) {
	char i,j,k;
	for(i=0;i<9;++i)
		for(j=0;j<9;++j)
			if(!oldgrid[i][j][0])
				for(k=1;k<10;++k)
					if(oldgrid[i][j][k]) {
						char newgrid[9][9][10];
						//guessing
						guessed(oldgrid,newgrid,i,j,k);
						//solving according to guess
						solve(newgrid);
						//checking if solved
						if(solved(newgrid)) {
							output(newgrid);
							return 1;
						}
						//guessing recursively
						if(guess(newgrid))
							return 1;
						//eliminating guess
						oldgrid[i][j][k]=0;
						solve(oldgrid);
					}
	return 0;
}

int main(int argc,char **argv) {
	if((argc!=2)||(strlen(argv[1])!=81))	{
		printf("[USAGE] %s [INT[81]]\n",argv[0]);
		return -1;
	}
	char grid[9][9][10];
	initialize(grid);
	input(grid,argv[1]);
	solve(grid);
	if(solved(grid))
		output(grid);
	else
		guess(grid);
	return 0;
}
