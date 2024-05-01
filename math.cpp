#include <iostream>
#include "vector"

float initialpositionx = 260.00;
float initialpositiony = 666.00;
float boxsize = 70;

struct vector2
{
      float x;
      float y;
};

std::vector<vector2> coordinates;

void generatecoordinates()
{
      coordinates.push_back({initialpositionx, initialpositiony});
      std::cout << "at " << 1 << " x: " << coordinates[0].x << " y: " << coordinates[0].y << std::endl;
      for (int counter = 1; counter < 100; counter++)
      {
            // if second digit even

            if (((counter / 10) % 2) == 0)
            {

                  if (counter % 10 == 0)
                  {
                        coordinates.push_back({coordinates[counter - 1].x, coordinates[counter - 1].y - boxsize});
                                    std::cout << "at " << counter+1 << " x: " << coordinates[counter].x << " y: " << coordinates[counter].y << std::endl;
                        continue;
                  }
                  coordinates.push_back({coordinates[counter - 1].x + boxsize, coordinates[counter - 1].y});
            }
            // if second digit odd
            else if (((counter / 10) % 2) != 0)
            {
                  // move one space up if last digit 0
                  if (counter % 10 == 0)
                  {
                        coordinates.push_back({coordinates[counter - 1].x, coordinates[counter - 1].y - boxsize});
                        std::cout << "at " << counter+1 << " x: " << coordinates[counter].x << " y: " << coordinates[counter].y << std::endl;
                        continue;
                  }
                  coordinates.push_back({coordinates[counter - 1].x - boxsize, coordinates[counter - 1].y});
            }
            // Print out the output of the above code
            std::cout << "at " << counter+1 << " x: " << coordinates[counter].x << " y: " << coordinates[counter].y << std::endl;
      }
}

int main()
{
      generatecoordinates();
      return 0;
}