#ifndef RND_H
#define RND_H

// ************************** Random Generator *****************************

#define RNG_H_DEBUG_LEVEL 0
// Level 1: states construction, destruction

#include <random>

// using namespace std;

class Random_number_generator {

  std::random_device rnd_dev;
  std::default_random_engine rnd_engine {rnd_dev()};

public:

  // Generators

  int read_int(int max = 100);                  // Read int   0 ... max
  int read_int(int min, int max);               // Read int min ... max

  double read_double(double max = 1);           // Reading double   0 ... max
  double read_double(double min, double max);   // Reading double min ... max

  // Tests
  // Output to console 10 Hz

  void test_int(int max = 100);
  void test_int(int min, int max);

  void test_float(double max = 1);
  void test_float(double min, double max);

  Random_number_generator();
  ~Random_number_generator();
};

#endif
