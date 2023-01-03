
// ************************** Random generator *****************************

// #include "../gsl/gsl"
#include "rnd.h"
#include <iostream>
#include <cassert>
// For tests
#include <thread>
#include <chrono>
#include <iomanip>

using namespace std;
// ******************* Constructor - Destructor *****************

Random_number_generator::Random_number_generator() {
  #if (RNG_H_DEBUG_LEVEL >= 1)
  cout << "Random number generator constructor" << endl;
  #endif
}

Random_number_generator::~Random_number_generator() {
  #if (RNG_H_DEBUG_LEVEL >= 1)
  cout << "Random number generator destructor" << endl;
  #endif
}

// ******************* Integer *****************

int Random_number_generator::read_int(int max) {
  std::uniform_int_distribution <int> uniform_dist (0, max);
  return uniform_dist (rnd_engine);
}

int Random_number_generator::read_int(int min, int max) {
  assert (min <= max);
  std::uniform_int_distribution <int> uniform_dist (min, max);
  return uniform_dist (rnd_engine);
}

// ******************* Floating point *****************

double Random_number_generator::read_double(double max) {
  std::uniform_real_distribution <double> uniform_dist (0, max);
  return uniform_dist (rnd_engine);
}

double Random_number_generator::read_double(double min, double max) {
  assert (min <= max);
  std::uniform_real_distribution <double> uniform_dist (min, max);
  return uniform_dist (rnd_engine);
}

// ******************* Test random generator *****************

void Random_number_generator::test_float(double max) {test_float (0, max);}
void Random_number_generator::test_float(double min, double max) {
  Random_number_generator rng;
    while (1) {
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
      double new_rand_value {rng.read_double(min, max)};
      cout << setw (6) << setprecision(2) << new_rand_value << " ";
      for (int i {0}; i < new_rand_value; i++) {
        cout << "*";
      }
    cout << endl;
    }
}

void Random_number_generator::test_int(int max) {test_int (0, max);}
void Random_number_generator::test_int(int min, int max) {
  Random_number_generator rng;
    while (1) {
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
      int new_rand_value {rng.read_int(min, max)};
      cout << setw (6) << new_rand_value << " ";
      for (int i {0}; i < new_rand_value; i++) {
        cout << "*";
      }
    cout << endl;
    }
}
