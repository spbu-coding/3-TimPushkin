#ifndef SETTINGS_H
#define SETTINGS_H

// Execution and output settings
#define DIGITS_TO_PRINT 60
#define MAX_LOOP_DUR 100
// Calculation settings
#define TARGETED_SOLUTION {1.0f, 1.0f}
#define TARGETED_DIST 0.000001f
#define INIT_DIST (TARGETED_DIST + 1.0f)
#define INIT_DEVIATION 0.0001f
#define ACCEPTABLE_DIFF 0.00001f
#define DIV_RATIO 2.0f
// System of equations settings
#define FORMULA_FOR_X1(d) 1.0f - (d / 0.0001f)
#define FORMULA_FOR_X2(d) 1.0f + (d / 0.0001f)

#endif
