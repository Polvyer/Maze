//
//  main.cpp
//  Maze
//
//  Created by William Ocampo on 5/4/19.
//  Copyright © 2019 William Ocampo. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <string.h>

using namespace std;

class Tile {
    
private:
    
    int chestGold;
    int type; // (Tile = 0, Wall = 1, Chest = 2, Door = 3, Player = 4)
    
public:
    
    Tile () {
        chestGold = 0;
        type = 0;
    }
    
    void setChestGold (int g) {
        chestGold = g;
    }
    
    int getChestGold () {
        return chestGold;
    }
    
    void setType (int t) {
        type = t;
    }
    
    int getType () {
        return type;
    }
    
};

class Wall : public Tile {
    
private:
    
public:
    
};

class Chest : public Tile {
    
private:
    
public:
    
};

class Door : public Tile {
    
private:
    
public:
    
};

class Room {
    
private:
    
    Tile **board;
    int rows;
    int trueRows;
    int columns;
    int trueColumns;
    
public:
    
    Room () {
        /*
        rows = x;
        trueRows = x - 2;
        columns = y;
        trueColumns = y - 2;
        
        // Dynamic allocation
        board = new Tile*[rows];
        for (int i = 0; i < rows; i++) {
            board[i] = new Tile[columns];
        }
        
        // Fill
        for (int i = 0; i < rows; i++) {
            board[i][0].setType(1);
            board[i][columns - 1].setType(1);
        }
        
        for (int j = 0; j < columns; j++) {
            board[0][j].setType(1);
            board[rows - 1][j].setType(1);
        }
        */
    }
    
    ~Room() {
        
    }
    
    void dynamicAllocation (int x, int y) {
        rows = x;
        trueRows = x - 2;
        columns = y;
        trueColumns = y - 2;
        
        // Dynamic allocation
        board = new Tile*[rows];
        for (int i = 0; i < rows; i++) {
            board[i] = new Tile[columns];
        }
        
        // Fill
        for (int i = 0; i < rows; i++) {
            board[i][0].setType(1);
            board[i][columns - 1].setType(1);
        }
        
        for (int j = 0; j < columns; j++) {
            board[0][j].setType(1);
            board[rows - 1][j].setType(1);
        }
    }
    
    void freeAllocation () {
        for (int i = 0; i < rows; i++) {
            delete [] board[i];
        }
        delete [] board;
    }
    
    void setChestGold (int x, int y, int g) {
        board[x][y].setChestGold(g);
    }
    
    int getChestGold (int x, int y) {
        return board[x][y].getChestGold();
    }
    
    void setType (int x, int y, int t) {
        board[x][y].setType(t);
    }
    
    int getType (int x, int y) {
        return board[x][y].getType();
    }
    
    void roomInfo () {
        cout << "Rows: " << trueRows << endl;
        cout << "Columns: " << trueColumns << endl;
        cout << endl;
    }
    
    void printBoard () {
        int tmpType;
        
        for (int i = 0; i < rows; i++) {
            
            for (int j = 0; j < columns; j++) {
                
                tmpType = board[i][j].getType();
                
                // Print tile
                if (tmpType == 0) {
                    cout << " ";
                }
                // Print wall
                else if (tmpType == 1) {
                    cout << "*";
                }
                // Print chest
                else if (tmpType == 2) {
                    cout << "C";
                }
                // Print door
                else if (tmpType == 3) {
                    cout << "D";
                }
                // Print player
                else if (tmpType == 4) {
                    cout << "P";
                }
            }
            cout << endl; // Whitespace
        }
    }
};

class Player {
    
private:
    
    int goldCollected;
    int tilesVisited;
    int xLocation;
    int yLocation;
    
public:
    
    Player () {
        goldCollected = 0;
        tilesVisited = 0;
        xLocation = 0;
        yLocation = 0;
    }
    
    void collectGold (int g) {
        goldCollected += g;
    }
    
    void incTilesVis () {
        tilesVisited++;
    }
    
    void setLocation (int x, int y) {
        xLocation = x;
        yLocation = y;
    }
    
    int getXLocation () {
        return xLocation;
    }
    
    int getYLocation () {
        return yLocation;
    }
    
    void playerInfo () {
        cout << "Gold collected: " << goldCollected << " g" << endl;
        cout << "Tiles visited: " << tilesVisited << " t" << endl;
        cout << "Player location: " << "(" << xLocation << ", " << yLocation << ")" << endl;
        cout << endl;
    }
    
};

int main(int argc, const char * argv[]) {
    
    // Create player
    Player Polvyer;
    
    // Create board
    Room Stage;
    
    // Create variables
    char buffer[300]; // Temporarily stores char input
    int x, y, g;      // Temporarily stores int input
    ifstream inputFile;
    
    // Get level (initially 1)
    int levelInt = 0;
    string level = "Room1.txt";
    
    
    do {
    // Increment level
    levelInt++;
    
    // Open the file
    inputFile.open(level);
    
    // Get dimensions of board game
    inputFile >> x;
    inputFile >> y;
    
    // Create board game
    x += 2;       // For border
    y += 2;       // For border
    Stage.dynamicAllocation(x, y);
    
    while (inputFile >> buffer) {
        
        // Start location of person (4)
        if (strcmp(buffer, "S") == 0) {
            inputFile >> x;
            inputFile >> y;
            Stage.setType(x, y, 4);
            Polvyer.setLocation(x, y);
        }
        // List of obstacles (1)
        else if (strcmp(buffer, "O") == 0) {
            inputFile >> x;
            inputFile >> y;
            Stage.setType(x, y, 1);
        }
        // Chests (2)
        else if (strcmp(buffer, "C") == 0) {
            inputFile >> x;
            inputFile >> y;
            inputFile >> g;
            Stage.setType(x, y, 2);
            Stage.setChestGold(x, y, g);
        }
        // Doors (3)
        else if (strcmp(buffer, "D") == 0) {
            inputFile >> x;
            inputFile >> y;
            inputFile >> level;
            Stage.setType(x, y, 3);
        }
        // Exit
        else if (strcmp(buffer, "E") == 0) {
            cout << "E" << endl;
        }
    }
    
    // Close the file
    inputFile.close();
    
    cout << endl;
    Stage.printBoard();
    cout << endl;
    
    // Display the user interface
    FILE* inFile = stdin;
    char buf[300];
    char *input;
    int newX, newY;
    int oldX = Polvyer.getXLocation();
    int oldY = Polvyer.getYLocation();
    int tmpType, tmpGold;
    cout << "> ";
    input = fgets(buf, 300, inFile);
    
    while (input != NULL) {
        char *command;
        command = strtok(input, " \n\t");
        
        // Nothing
        if (command == NULL) {
            cout << endl;
            cout << "Blank Line" << endl;
            cout << endl;
        }
        // Exit the program
        else if (strcmp(command, "q") == 0) {
            return 0;
        }
        else if (strcmp(command, "w") == 0) {
            newX = oldX - 1;
            newY = oldY;
            tmpType = Stage.getType(newX, newY);
            
            // If Tile
            if (tmpType == 0) {
                cout << endl;
                cout << "-jumps to the TILE-" << endl;
                cout << endl;
                Stage.setType(oldX, oldY, 0);
                Polvyer.setLocation(newX, newY);
                Stage.setType(newX, newY, 4);
                oldX = newX;
                oldY = newY;
                Polvyer.incTilesVis();
            }
            // If Wall
            else if (tmpType == 1) {
                cout << endl;
                cout << "That's a WALL, dummy!" << endl;
                cout << endl;
            }
            // If Chest
            else if (tmpType == 2) {
                tmpGold = Stage.getChestGold(newX, newY);
                cout << endl;
                cout << "Wowie, a CHEST! + " << tmpGold << " g" << endl;
                cout << endl;
                Stage.setType(oldX, oldY, 0);
                Polvyer.setLocation(newX, newY);
                Stage.setType(newX, newY, 4);
                oldX = newX;
                oldY = newY;
                Polvyer.collectGold(tmpGold);
                Polvyer.incTilesVis();
            }
            // If Door
            else if (tmpType == 3) {
                cout << endl;
                cout << "Look, a random DOOR!" << endl;
                cout << endl;
                Stage.setType(oldX, oldY, 0);
                Polvyer.setLocation(newX, newY);
                Stage.setType(newX, newY, 4);
                oldX = newX;
                oldY = newY;
                Polvyer.incTilesVis();
                Stage.freeAllocation();
                break;
            }
        }
        else if (strcmp(command, "a") == 0) {
            newX = oldX;
            newY = oldY - 1;
            tmpType = Stage.getType(newX, newY);
            
            // If Tile
            if (tmpType == 0) {
                cout << endl;
                cout << "-jumps to the TILE-" << endl;
                cout << endl;
                Stage.setType(oldX, oldY, 0);
                Polvyer.setLocation(newX, newY);
                Stage.setType(newX, newY, 4);
                oldX = newX;
                oldY = newY;
                Polvyer.incTilesVis();
            }
            // If Wall
            else if (tmpType == 1) {
                cout << endl;
                cout << "That's a WALL, dummy!" << endl;
                cout << endl;
            }
            // If Chest
            else if (tmpType == 2) {
                tmpGold = Stage.getChestGold(newX, newY);
                cout << endl;
                cout << "Wowie, a CHEST! + " << tmpGold << " g" << endl;
                cout << endl;
                Stage.setType(oldX, oldY, 0);
                Polvyer.setLocation(newX, newY);
                Stage.setType(newX, newY, 4);
                oldX = newX;
                oldY = newY;
                Polvyer.collectGold(tmpGold);
                Polvyer.incTilesVis();
            }
            // If Door
            else if (tmpType == 3) {
                cout << endl;
                cout << "Look, a random DOOR!" << endl;
                cout << endl;
                Stage.setType(oldX, oldY, 0);
                Polvyer.setLocation(newX, newY);
                Stage.setType(newX, newY, 4);
                oldX = newX;
                oldY = newY;
                Polvyer.incTilesVis();
                Stage.freeAllocation();
                break;
            }
        }
        else if (strcmp(command, "s") == 0) {
            newX = oldX + 1;
            newY = oldY;
            tmpType = Stage.getType(newX, newY);
            
            // If Tile
            if (tmpType == 0) {
                cout << endl;
                cout << "-jumps to the TILE-" << endl;
                cout << endl;
                Stage.setType(oldX, oldY, 0);
                Polvyer.setLocation(newX, newY);
                Stage.setType(newX, newY, 4);
                oldX = newX;
                oldY = newY;
                Polvyer.incTilesVis();
            }
            // If Wall
            else if (tmpType == 1) {
                cout << endl;
                cout << "That's a WALL, dummy!" << endl;
                cout << endl;
            }
            // If Chest
            else if (tmpType == 2) {
                tmpGold = Stage.getChestGold(newX, newY);
                cout << endl;
                cout << "Wowie, a CHEST! + " << tmpGold << " g" << endl;
                cout << endl;
                Stage.setType(oldX, oldY, 0);
                Polvyer.setLocation(newX, newY);
                Stage.setType(newX, newY, 4);
                oldX = newX;
                oldY = newY;
                Polvyer.collectGold(tmpGold);
                Polvyer.incTilesVis();
            }
            // If Door
            else if (tmpType == 3) {
                cout << endl;
                cout << "Look, a random DOOR!" << endl;
                cout << endl;
                Stage.setType(oldX, oldY, 0);
                Polvyer.setLocation(newX, newY);
                Stage.setType(newX, newY, 4);
                oldX = newX;
                oldY = newY;
                Polvyer.incTilesVis();
                Stage.freeAllocation();
                break;
            }
        }
        else if (strcmp(command, "d") == 0) {
            newX = oldX;
            newY = oldY + 1;
            tmpType = Stage.getType(newX, newY);
            
            // If Tile
            if (tmpType == 0) {
                cout << endl;
                cout << "-jumps to the TILE-" << endl;
                cout << endl;
                Stage.setType(oldX, oldY, 0);
                Polvyer.setLocation(newX, newY);
                Stage.setType(newX, newY, 4);
                oldX = newX;
                oldY = newY;
                Polvyer.incTilesVis();
            }
            // If Wall
            else if (tmpType == 1) {
                cout << endl;
                cout << "That's a WALL, dummy!" << endl;
                cout << endl;
            }
            // If Chest
            else if (tmpType == 2) {
                tmpGold = Stage.getChestGold(newX, newY);
                cout << endl;
                cout << "Wowie, a CHEST! + " << tmpGold << " g" << endl;
                cout << endl;
                Stage.setType(oldX, oldY, 0);
                Polvyer.setLocation(newX, newY);
                Stage.setType(newX, newY, 4);
                oldX = newX;
                oldY = newY;
                Polvyer.collectGold(tmpGold);
                Polvyer.incTilesVis();
            }
            // If Door
            else if (tmpType == 3) {
                cout << endl;
                cout << "Look, a random DOOR!" << endl;
                cout << endl;
                Stage.setType(oldX, oldY, 0);
                Polvyer.setLocation(newX, newY);
                Stage.setType(newX, newY, 4);
                oldX = newX;
                oldY = newY;
                Polvyer.incTilesVis();
                Stage.freeAllocation();
                break;
            }
        }
        else if (strcmp(command, "h") == 0) {
            cout << endl;
            cout << "\tProgram commands" << endl;
            cout << "Q: Exit the program" << endl;
            cout << "W: Move up" << endl;
            cout << "A: Move left" << endl;
            cout << "S: Move down" << endl;
            cout << "D: Move right" << endl;
            cout << "H: Print a list of all available commands" << endl;
            cout << "G: Print Player's score" << endl;
            cout << "F: Find a path to a door using DFS and print the path" << endl;
            cout << "B: Find the Shortest path to the nearest door using BFS and print the path" << endl;
            cout << endl;
            cout << "\tCharacters" << endl;
            cout << "  Tile   0 " << endl;
            cout << "  Wall * 1 " << endl;
            cout << " Chest C 2" << endl;
            cout << "  Door D 3" << endl;
            cout << "Player P 4" << endl;
            cout << endl;
        }
        else if (strcmp(command, "g") == 0) {
            cout << endl;
            cout << "\tPlayer's score" << endl;
            Polvyer.playerInfo();
        }
        else if (strcmp(command, "f") == 0) {
            
        }
        else if (strcmp(command, "b") == 0) {
            
        }
        else {
            cout << endl;
            cout << "Invalid command..." << endl;
            cout << endl;
        }
        
        Stage.printBoard();
        cout << endl;
        cout << "> ";
        input = fgets (buf, 300, inFile);
    }
    } while(levelInt != 5);
    
    cout << "-Thanos snap-" << endl << endl;
    cout << "You won, but died." << endl << endl;
    
    cout << "\tFinal score" << endl;
    Polvyer.playerInfo();
    
    return 0;
}
