#include <iostream>
#include "clock.h"
#include <stdlib.h>
#include <time.h>
#include <map>

using namespace std;
using namespace EvolvingClocks;

int main() {
  srand(time(NULL)); rand(); rand();

  cout << "Hello" << endl;
  Component x;
  Gear y;
  y.link(&y,gearBottom,gearTop);
  cout << "One gear linked to self: isOK=" << y.isOK() << " hasLoop=" << y.hasLoop() << " hasLinkToBase=" << y.hasLinkToBase() << endl;
  Gear a,b;
  a.link(&b,gearBottom,gearTop);
  cout << "Two gears linked sanely: isOK=" << a.isOK() << " hasLoop=" << a.hasLoop() << " hasLinkToBase=" << a.hasLinkToBase() << endl;
  Gear j,k,l;
  j.link(&k,gearBottom,gearTop);
  k.link(&l,gearBottom,gearTop);
  l.link(&j,gearBottom,gearTop);
  cout << "Three gears in a vertical loop: isOK=" << j.isOK() << " hasLoop=" << j.hasLoop() << " hasLinkToBase=" << j.hasLinkToBase() << endl;
  Backplate bp;
  Gear g1,g2;
  g2.link(&g1,gearBottom,gearTop);
  g1.link(&bp,gearBottom,clockBase);
  cout << "Two gears on backplate: isOK=" << g2.isOK() << " hasLoop=" << g2.hasLoop() << " hasLinkToBase=" << g2.hasLinkToBase() << endl;
  cout << "Backplate itself: isOK=" << bp.isOK() << " hasLinkToBase=" << bp.hasLinkToBase() << endl;
  Gear z;
  z.link(&a,gearEdge,handEnd);
  cout << "Mislabelled link: isOK=" << z.isOK() << " hasLoop=" << z.hasLoop() << " hasLinkToBase=" << z.hasLinkToBase() << endl;

  cout << endl;
  cout << "Test clock..." << endl;
  
  //  Clock c(ratchetPendulumWithHand);
  Clock c(2);
  cout << "Clock isOK=" << c.isOK() << endl;

  cout << endl;

  deque<interfaceType> free = g2.freeConnectionTypes();
  for (deque<interfaceType>::iterator it = free.begin() ; it != free.end() ; it++) {
    cout << "Available connection type " << *it << endl;
  }

  cout << "teeth: " << g2.nTeeth() << endl;

  Hand h1,h2,h3;
  cout << h1.period() << " " << h2.period() << " " << h3.period() << endl;

  map<int,int> periodHist;
  for (int i = 0 ; i < 10 ; i++) periodHist[i] = 0;

  map<int,int> minutePeriodHist;
  for (int i = 0 ; i < 10 ; i++) minutePeriodHist[i] = 0;

  int N = 15;
  int nc = 10000;
  int min = 10.;
  int periodSoFar = 0;
  float evalSoFar = 0.;

  Traditionalist o(1.);
  
  for (int i = 0 ; i < nc ; i ++) {
    Clock c(N);
    deque<PeriodInfo> p = c.periods();
    periodHist[p.size()] += 1;
    bool hasHand = false;
    int countLong = 0;
    for (deque<PeriodInfo>::iterator it = p.begin() ; it != p.end() ; it++) {
      if (it->period() > float(min)) countLong++;
      if (it->type() == gearWithHand) hasHand = true;
    }
    minutePeriodHist[countLong] += 1;
    /*
    if (countLong >= 1) {
      cout << "long period clock!" << endl << endl;
      c.display();
      cout << o.eval(c) << endl << endl;
    }
    if (p.size() > periodSoFar) {
      cout << "Record number of period clock!" << endl << endl;
      c.display();
      cout << o.eval(c) << endl << endl;
      periodSoFar = p.size();
    }
    if (hasHand) {
      cout << "clock with hand!" << endl << endl;
      c.display();
      cout << o.eval(c) << endl << endl;
    }
    */
    if (o.eval(c)>evalSoFar) {
      cout << "high eval clock! " << i << "/" << nc << endl << endl;
      c.display();
      cout << o.eval(c) << endl << endl;
      evalSoFar = o.eval(c);
    }
  }

  cout << endl << endl;
  cout << "N=" << N << endl;
  for (int i = 0 ; i < 10 ; i++) {
    cout << i << " periods: " << periodHist[i] << endl;
  }
  cout << endl << endl;
  cout << "N=" << N << endl;
  for (int i = 0 ; i < 10 ; i++) {
    cout << i << " periods of " << min << "+ secs: " << minutePeriodHist[i] << endl;
  }


  //  srand(time(NULL));
  //  cout << time(NULL) << " " << (rand() % 100) << endl;

  /*
  printf ("First number: %d\n", rand() % 100);
  srand ( time(NULL) );
  printf ("First number after time: %d\n", rand() % 100);
  printf ("Random number: %d\n", rand() % 100);
  srand ( 1 );
  printf ("Again the first number: %d\n", rand() %100);
  */

  /*
  deque<Component*> fred;
  fred.push_back(&bp);

  Backplate* meh = dynamic_cast<Backplate*>((*(fred.begin())));
  if (meh) cout << "dynamic cast ok" << endl;
  */

  return 0;
}
