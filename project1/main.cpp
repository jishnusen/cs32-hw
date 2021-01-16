#include "City.h"
#include "Player.h"
#include "History.h"
#include <iostream>
using namespace std;

int main()
{
  City ct(3, 4);
  ct.addPlayer(2, 3);
  for (;;)
  {
    ct.preachToFlatulansAroundPlayer();
    if (ct.nFlatulansAt(1, 4) != 0)
      break;
    ct.addFlatulan(1, 4);
  }
  ct.player()->move(LEFT);
  for (int r = 1; r <= 3; r++)
  {
    for (int c = 1; c <= 3; c++)
    {
      if (r == 2 && c == 2)
        continue;
      for (int k = 0; k < MAXFLATULANS / 8; k++)
        ct.addFlatulan(r, c);
    }
  }
  ct.preachToFlatulansAroundPlayer();
  ct.preachToFlatulansAroundPlayer();
  ct.history().display();
  cout << "====" << endl;
}