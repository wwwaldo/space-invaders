#include <iostream>
#include <cstdlib>
#include <string>

#define SCREEN_W 40
#define SCREEN_H 60
#define N_SHIPS 20

#define FPS 30

// an alien ship
class Ship{
public:
  std::string repr = "#";
};

class player{
public:
  std::string repr = "=||=";
};
