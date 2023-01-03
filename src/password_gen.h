#ifndef TESTS_H
#define TESTS_H

#include <random>

// ******************************************************

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

// **********************  Random number generator ***************************


// ******************* Constructor - Destructor *****************

Random_number_generator::Random_number_generator() {}
Random_number_generator::~Random_number_generator() {}

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

// ******************************************************

#endif
