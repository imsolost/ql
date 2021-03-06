void myFunction1() {
  int i;
  int result = 0;

  for (i = 0;; i = i+1) {

    if (i < 20) result++;
    if (i <= 20) result++;
    if (i > 20) result++;
    if (i >= 20) result++;
    if (i == 20) result++;
    if (i != 20) result++;

    if (i < -1) result++;
    if (i <= -1) result++;
    if (i > -1) result++;
    if (i >= -1) result++;
    if (i == -1) result++;
    if (i != -1) result++;

    if (i < 5) result++;
    if (i <= 5) result++;
    if (i > 5) result++;
    if (i >= 5) result++;
    if (i == 5) result++;
    if (i != 5) result++;

    i = i % 7;
  }
}

void myFunction2() {
  int i;
  int result = 0;

  for (i = 0;; i++) {

    if (i < 20) result++;
    if (i <= 20) result++;
    if (i > 20) result++;
    if (i >= 20) result++;
    if (i == 20) result++;
    if (i != 20) result++;

    if (i < -1) result++;
    if (i <= -1) result++;
    if (i > -1) result++;
    if (i >= -1) result++;
    if (i == -1) result++;
    if (i != -1) result++;

    if (i < 5) result++;
    if (i <= 5) result++;
    if (i > 5) result++;
    if (i >= 5) result++;
    if (i == 5) result++;
    if (i != 5) result++;

    i = i % 7;
  }
}

int myFunction3(int i) {
  if (i < 4) {
    if (i < 5) {
      return 1;
    }
  }
  return 0;
}

int booleans(void* ptr, void* ptr2, int i) {
  if (ptr && (ptr2 || i == 4))
    if (i == 3)
      return i;
  return 0;
}

#define NUM 999
static int ranges(double a, double b) {
  if (a > NUM && b < NUM) // GOOD
    return 1;
  else if (a <= NUM && b < NUM) // GOOD
    return 2;
  else if (a > -NUM && b >= NUM) // GOOD
    return 3;
  else
    return 4;
}



int myFunction4() {
  // No result if both operands are constant.
  if (0 < 1) {
    return 1;
  }
  return 0;
}

// Pointless checks for unsigned values being negative
int unsignedBounds(unsigned int a, unsigned long b, unsigned long long c) {
  if (a < 0) {
    return 1;
  }
  if (b >= 0) { // UnsignedGEZero
    if (b > 0 && c < 0) { // Only the test of c is bad here
      return 1;
    }
  }
  return 0;
}

int twoReasons(int a, int b) {
  if (a <= 0 && b > 5) {
    return a < b;
  }
  if (a <= 100 && b > 105) {
    return a > b;
  }
  return 0;
}

int repeatedComparisons(int a) {
  if (a >= 20) {
    return a >= 20;
  }
  if (a <= 3) {
    return a > 3;
  }
  return 0;
}

// Our analysis does not yet catch these non-constant pointless comparisons
int nonConstantComparisons(int a, int b) {
  if (a < b) {
    if (a < b) {
      return 1;
    }
    if (b >= a) {
      return 1;
    }
    if (a <= b) {
      return 1;
    }
  }
  return 0;
}

// Regression test for a false positive
int myFunction7(int count)
{
  int x = 0;
  int y = 0;
  int *thing_ptr = 0;
  const char **z_ptr = 0;
  const char *z = 0;

  enum {
    THING_A = 0,
    THING_B,
    THING_C,
    THING_D,
    THING_E
  } thing = THING_A;

  thing_ptr = &thing;
  thing_ptr = &x;
  thing_ptr = &y;
  z_ptr = &z;

  if (!thing)
    thing = count ? THING_E : THING_B;

  if (z && thing != THING_B)
    return 0;

  if (x && thing != THING_E && thing != THING_C && thing != THING_D)
    return 0;

  if (y && thing != THING_C)
    return 0;

  return 1;
}

int myFunction5(int x) {
  int d, i = 0;
  if (x < 0) {
    return -1;
  }

  while (i < 3) {
    i++;
  }
  d = i;
  if (x < 0) {  // Comparison is always false.
    if (d > -x) {  // Unreachable code.
      return 1;
    }
  }
  return 0;
}

enum my_enum {
	FOO
};

int myFunction6(enum my_enum e) {
	if (e < 0) {
		return 1;
	}
	return 0;
}

typedef unsigned long long size_t;

#define SIZE_MAX (~(size_t)0)

void cpp_105_regression_test(size_t s) {
  if (s > SIZE_MAX - 1) { // GOOD
    // ...
  }
  if (s > SIZE_MAX - 2) { // GOOD
    // ...
  }
  if (s > SIZE_MAX - 4) { // GOOD
    // ...
  }
}

unsigned int global_setting;

#define MAYBE_DO(CODE) \
  if (global_setting >= 0) \
    CODE;

void macroExpansionTest() {
  int x;

  MAYBE_DO(x = 1); // GOOD (the problem is in the macro)
  MAYBE_DO(if (global_setting >= 0) {x = 2;}); // BAD (the problem is in the invocation)
}

int overeager_wraparound(unsigned int u32bound, unsigned long long u64bound) {
  unsigned int u32idx;
  unsigned long long u64idx;

  for (u32idx = 1; u32idx < u32bound; u32idx++) {
    if (u32idx == 0) // BAD [NOT DETECTED]
      return 0;
  }

  for (u64idx = 1; u64idx < u64bound; u64idx++) {
    if (u64idx == 0) // BAD [NOT DETECTED]
      return 0;
  }

  return 1;
}

int negative_zero(double dbl) {
  if (dbl >= 0) {
    return dbl >= -dbl; // GOOD [FALSE POSITIVE]
  }
  return 0;
}
