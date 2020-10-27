#ifndef SETTINGS_H
#define SETTINGS_H

// Execution and output settings
#define MAX_LOOP_DUR 100
#define DIGITS_TO_PRINT 16
// Calculation settings (common)
#define TARGETED_SOLUTION {1.0f, 1.0f}
#define TARGETED_DIST 0.000001f
#define INIT_DIST (TARGETED_DIST + 1.0f)
#define ACCEPTABLE_DIFF 0.00001f
#define DIV_RATIO 2.0f
// Calculation settings (floats)
#define INIT_DEVIATION_F 0.0001f
#define FORMULA_FOR_X1_F(d) 1.0f - 10000.0f * d
#define FORMULA_FOR_X2_F(d) 1.0f + 10000.0f * d
// Calculation settings (doubles)
#define INIT_DEVIATION_D 0.0001
#define FORMULA_FOR_X1_D(d) 1.0 - 10000.0 * d
#define FORMULA_FOR_X2_D(d) 1.0 + 10000.0 * d

#endif
