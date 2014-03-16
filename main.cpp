#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

static const int AREA_RADIUS = 100;

typedef double Scalar;

typedef struct Point_ {
    int x = 0;
    int y = 0;
} Point;

static Scalar getDistance(const Point& p1, const Point& p2)
{
    return std::sqrt((p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y));
}

typedef struct Zone_ {
    Point center; // center of this zone (circle radius = 100 units)
    int ownerId = -1; // ID of the team which owns this zone, -1 otherwise
} Zone;


typedef struct Drone_ {
    Point pos; // position of the drone
    
    Point* target;
    // Find closest zone
    
    Point* getClosestZone(const vector<Zone*>& zones)
    {
        Scalar d, dmin;
        int indexOfClosestZone;
        dmin = getDistance(pos, zones[0]->center);
        indexOfClosestZone=0;

        
        for(size_t i=1; i<zones.size(); ++i)
        {
            d=getDistance(pos, zones[i]->center);
            if(d < dmin) indexOfClosestZone = i;
        }
        
        return &(zones[indexOfClosestZone]->center);
    }

} Drone;




typedef struct Team_ {
    vector<Drone*> drones; // drones of the team
} Team;

typedef struct Game_ {
  vector<Zone*> zones; // all game zones
  vector<Team*> teams; // all the team of drones. Array index = team's ID
  int myTeamId; // index of my team in the array of teams

  // read initial games data (one time at the beginning of the game: P I D Z...)
  void init() {
      int p, i, d, z;
      cin >> p >> i >> d >> z;

      myTeamId = i;
      for(int areaId = 0; areaId < z; areaId++) {
          int x, y;
          Zone *z = new Zone();
          cin >> z->center.x >> z->center.y;
          zones.push_back(z);
      }

      for(int teamId = 0; teamId < p; teamId++) {
          Team *t = new Team();
          teams.push_back(t);
          for(int droneId = 0; droneId < d; droneId++) {
              Drone *drone = new Drone();
              t->drones.push_back(drone);
          }
      }
  }

  // Run the main loop (parse inputs and play)
  void run() {
      vector<Drone*> myDrones = teams[myTeamId]->drones;
      
      bool isInitialized(false);

      while (true) 
      {

        for(Zone* zone : zones) 
        {
            cin >> zone->ownerId;
        }
        for(Team* team : teams) 
        {
            for(Drone* drone : team->drones) 
            {
                cin >> drone->pos.x >> drone->pos.y; // update drones position
            }
        }

        updateNbMaxDrones();

        if(!isInitialized)
         {
            for(Drone *drone : myDrones) 
            {
                drone->target = drone->getClosestZone(zones);
            }
            isInitialized=true;
        }

          play(myDrones);
      }
  }

  // Compute logic here. This method is called for each game round.
  void play(const vector<Drone*>& myDrones) {
      
        for(Drone* drone : myDrones) {
            //cerr << drone->target->center.x << " " << drone->target->center.y << endl;
            //cerr << drone->getClosestZone(zones)->center.x << " " << drone->getClosestZone(zones)->center.x << endl; 
            
            //cerr << drone->pos.x <<endl;
            cout << drone->target->x << " " << drone->target->y << endl;
            //cout << drone->pos.x << " " << drone->pos.y << endl;
            //cout << drone->getClosestZone(zones)->center.x << " " << drone->getClosestZone(zones)->center.x << endl; 
      }
  }

void updateNbMaxDrones()
{
        for(Zone* zone : zones) 
        {
        if(zone->ownerId!=-1)
        {
            for(Drone* drone : teams[zone->ownerId]->drones)
            {
                //TODO: updateNbdeDrone
            }
        }   
        }  
}

} Game;


int main()
{
    Game g;
    g.init();
    g.run();

    return 0;
}


