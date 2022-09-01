#ifndef CORDCALC_2_H_
#define CORDCALC_2_H_

#include<stdlib.h>

/*flags bitmap*/
typedef struct {
	size_t is_line : 1;/*is a arc if isnt a line*/
	size_t is_x_def : 1;
	size_t is_y_def : 1;
	size_t is_len_def : 1;
	size_t is_ang_def : 1;
	size_t is_rad_def : 1;
	size_t : 0;/*align*/
} flags;

/*beginning of the contour chain*/
struct elmnt** cnt_bgn;

struct point { float x, y; };

struct line {
	struct point tail;
	float lnth, 
		angl;/*between the line and the x-axis*/
	flags state;
};

struct arc {
	struct point tail;
	float rdus, 
		angl;/*an angle between the radius line and the x-axis*/
	flags state;
};

struct elmnt {
	struct elmnt* next;
	union {
		struct line* lne_addr;
		struct arc* arc_addr;
	} a_;
};


 struct elmnt**
	 ContourEnd(
		 struct elmnt** cnt_bgn) 
 {
	 while (*cnt_bgn != NULL)
		 cnt_bgn = &((*cnt_bgn)->next);

	 return cnt_bgn;
 }

#endif /* !CORDCALC_2_H_*/