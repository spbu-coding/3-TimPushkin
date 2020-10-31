#include <stdio.h>
#include <math.h>

#include "error_handle.h"
#include "settings.h"

// Notations: flp - floating-point, eqn - equation, sln - solution, dvn - deviation

union flp_num_t {
    float f;
    double d;
};

struct eqn_sln_t {
    union flp_num_t x1, x2;
};

_Bool is_greater(const union flp_num_t* const num1, const float num2, const char num_type) {
    if (num_type == 'f') {
        return ((fabsf(num1->f - num2) / num2) > ACCEPTABLE_DIFF && num1->f > num2);
    } else if (num_type == 'd') {
        return ((fabs(num1->d - num2) / num2) > ACCEPTABLE_DIFF && num1->d > num2);
    } else {
        error_handle("Unknown num type passed to function \'is_greater\'");
    }
}

struct eqn_sln_t solve_sys_of_eqns(const union flp_num_t* const dvn, const char num_type) {
    struct eqn_sln_t sln;
    if (num_type == 'f') {
        sln.x1.f = FORMULA_FOR_X1_F(dvn->f);
        sln.x2.f = FORMULA_FOR_X2_F(dvn->f);
    } else if (num_type == 'd') {
        sln.x1.d = FORMULA_FOR_X1_D(dvn->d);
        sln.x2.d = FORMULA_FOR_X2_D(dvn->d);
    } else {
        error_handle("Unknown num type passed to function \'solve_sys_of_eqns\'");
    }
    return sln;
}

union flp_num_t calculate_dist(const struct eqn_sln_t cur_sln, const struct eqn_sln_t* const targeted_sln, const char num_type) {
    union flp_num_t calculated_dist;
    if (num_type == 'f') {
        calculated_dist.f = sqrtf(powf(cur_sln.x1.f - targeted_sln->x1.f, 2) + powf(cur_sln.x2.f - targeted_sln->x2.f, 2));
    } else if (num_type == 'd') {
        calculated_dist.d = sqrt(pow(cur_sln.x1.d - targeted_sln->x1.f, 2) + pow(cur_sln.x2.d - targeted_sln->x2.f, 2));
    } else {
        error_handle("Unknown num type passed to function \'calculate_dist\'");
    }
    return calculated_dist;
}

union flp_num_t calculate_dvn(const struct eqn_sln_t* const targeted_sln, const char num_type) {
    union flp_num_t dvn, dist;
    unsigned int cnt = 0;
    if (num_type == 'f') {
        for (dvn.f = INIT_DEVIATION_F, dist.f = INIT_DIST; is_greater(&dist, TARGETED_DIST, 'f') && cnt <= MAX_LOOP_DUR; dvn.f /= DIV_RATIO, cnt++) {
            dist = calculate_dist(solve_sys_of_eqns(&dvn, 'f'), targeted_sln, 'f');
        }
        if (cnt > MAX_LOOP_DUR) {
            printf("Loop duration in floats exceeded\n");
        }
    } else if (num_type == 'd') {
        for (dvn.d = INIT_DEVIATION_D, dist.d = INIT_DIST; is_greater(&dist, TARGETED_DIST, 'd') && cnt <= MAX_LOOP_DUR; dvn.d /= DIV_RATIO, cnt++) {
            dist = calculate_dist(solve_sys_of_eqns(&dvn, 'd'), targeted_sln, 'd');
        }
        if (cnt > MAX_LOOP_DUR) {
            printf("Loop duration in doubles exceeded\n");
        }
    } else {
        error_handle("Unknown num type passed to function \'calculate_dvn\'");
    }
    return dvn;
}

int main() {
    const struct eqn_sln_t targeted_sln = TARGETED_SOLUTION;
    const union flp_num_t dvn_f = calculate_dvn(&targeted_sln, 'f'), dvn_d = calculate_dvn(&targeted_sln, 'd');
    if (printf("Deviation in floats: %.*f\n", DIGITS_TO_PRINT, dvn_f.f) < 0 || printf("Deviation in doubles: %.*lf\n", DIGITS_TO_PRINT, dvn_d.d) < 0) {
        error_handle("Printing to stdout failed");
    }
    return 0;
}
