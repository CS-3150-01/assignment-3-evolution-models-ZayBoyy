#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;




//Class to make a traversable map
class Location {
    private:
    char map[255][255];
 
    public:

    Location() {
        generateTerrain();
    };

    void generateTerrain() {
       
        for(int i = 0; i<=255; i++) {
        
            for(int j = 0; j<=255; j++) {
           
                int value = rand() %10;

                //Hole in the map
                if (value == 0) {
                    map[i][j] = 'O';
                }
                
                //Sand trap
                else if (value == 9) {
                    map[i][j] = ':';
                }

                //Food space
                else if (value >= 6 && value < 9) {
                    map[i][j] = '^';
                }

                //Normal square
                else {
                    map[i][j] = '#';
                }
            }
        }
    }

    char getValueAt(int x, int y) {

        return map[x][y];

    };

};


//Time Class to make the world run on timed increments
class Time {

    private:
    int minutes;
    int hours;
    bool day;

    public:

    //This is to set time at midnight
    Time() {
        minutes = 0;
        hours = 0;
        day = false;
    };

    //This is if a specific time needs to be set
    Time(int h, int m) {
        minutes = m;
        hours = h;
    };

    //This makes it so Time objects can be incremented using the obj++ syntax
    Time operator++ () {
        ++minutes;
         if (minutes>= 60) {
            ++hours;
            minutes -= 60;
        }
        if (hours >= 20) {
            day = false;
        }
        if (hours >= 6 && hours >= 20) {
            day = true;
        }
        if (hours >= 24) {
            hours -= 24;
        }

        return Time (hours, minutes);
    }

    Time operator++ ( int ) {
        Time T(hours, minutes);
        ++minutes;
        if(minutes >= 60){
            ++hours;
            minutes -= 60;
        }
        if (hours >= 20) {
            day = false;
        }
        if (hours >= 6 && hours >= 20) {
            day = true;
        }
        if (hours >= 24) {
            hours -= 24;
        }
        return T;
    }

};

//Creature Class to create and modify creatures
class Creature {

    private:

    bool alive;
    int hungerMeter;
    int tiredMeter;
    
    int locationX;
    int locationY;

    public:

      Creature() {
        alive = true;
        hungerMeter = 100 + rand() %100;
        tiredMeter = rand() %10;
        locationX = rand() %255;
        locationY = rand() %255;
    };
    
    Creature reproduce () {
            Creature eve = Creature();
            return eve;
    };
    
    void die() {
        if (alive == false) {
            cout << "Already dead";
        }
        else{
       alive = false;
        }
    };

    void eat(int food) {
        hungerMeter += food;
    };

    void move() {
       int randomDirection = rand() %8;
        switch(randomDirection) {
            
            case 0:
                locationX += 0;
                locationY += 1;
                break;
            
            case 1:
                locationX += 1;
                locationY += 1;
                break;
            
            case 2:
                locationX += 1;
                locationY += 0;
                break;

            case 3:
                locationX += 1;
                locationY -= 1;
                break;

            case 4:
                locationX += 0;
                locationY -= 1;
                break;
            
            case 5:
                locationX -= 1;
                locationY -= 1;
                break;

            case 6:
                locationX -= 1;
                locationY -= 0;
                break; 

            case 7:
                locationX -= 1;
                locationY += 1;
                break;  

            case 8:
            break;  
        }   
        hungerMeter -= 1;
        tiredMeter += 1;
    };

    int getLocationX() {
        return locationX;
    };

     int getLocationY() {
        return locationY;
    };

};

//Child Class that utilizes the other classes to make a world
class World : public Time, public Location, public Creature { 

    private:
    Location map;
    Time clock;
    int numberOfEntities;
    Creature entities[];
    
    public: 

    World() {
        map.generateTerrain();
        clock = Time();
        numberOfEntities = 0;
    };
    
    //Creates new creature object
    void spawnCreature() {
        Creature adam = Creature();
        entities[numberOfEntities] = adam;
        numberOfEntities++;
    };
    
    void spawnCreature(Creature eve) {
        entities[numberOfEntities] = eve.reproduce();
        numberOfEntities++;
    };

    //Resets Time back to midnight
    void bitesTheDust() {
        clock = Time();
    };

    //Progresses the clock
    void tickTock() {
        ++clock;
    };

};




int main () {

    World eden = World();

    
    for (int i = 0; i <1000; i++) {
        eden.tickTock();
        Creature evangelion = Creature();
        int randomForTesting = rand() %10;

        if (randomForTesting < 4) {
            evangelion.move();
            
            
        }
        else if (randomForTesting < 8 && randomForTesting >=4) {
            eden.spawnCreature();
        }
        else if (randomForTesting >=8) {
            evangelion.die();
            //cout << "Instrumentality Occured  ";
            
        }

        //if (eden.map.getValueAt(evangelion.getLocationX(), evangelion.getLocationY()) == '^') {
            //evangelion.eat(20);
            //cout << eden.map.getLocationAt(evangelion.getLocationX(), evangelion.getLocationY()) << " ";
        //}
    

    }


    return 0;
}
