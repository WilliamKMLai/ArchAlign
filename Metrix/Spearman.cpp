/*
 * Spearman.cpp
 *
 *  Created on: Jul 15, 2010
 *      Author: jbard, wklai2
 */
#include <math.h>
#include "AbstractMetrix.h"
#include "Pearson.h"
/** Forward Declaration or whatever C makes me do. */
class Pearson;
/**
 * Class for Spearman computation
 */
class Spearman: public AbstractMetrix {
	/**
	 * Concrete implemenatation of this Metrix. MUST TAKE IN THESE VARIABLES, AND RETURN A DOUBLE
	 */
	double Correlation(const double *x, const double *y, int length) {
		double* rankX = new double[length];
		double* rankY = new double[length];
		SpearRank(x, rankX, length);
		SpearRank(y, rankY, length);

		AbstractMetrix* pearson = new Pearson();
		double score =  pearson->execute(rankX, rankY, length);

		delete[] rankX;
		delete[] rankY;

		return score;
	}
	/**
	 * Helper method for main algorithm.
	 */
	void SpearRank(const double *x, double *newx, int length) {
		int j, k, t;
        double tmp;
        int tmpi;

        double* r = new double[length];
        int* c = new int[length];

        if(length <= 1) { newx[0] = 1; return; }
        for(int i = 0; i < length; i++) {
        	r[i] = x[i];
            c[i] = i;
        }
        for(int i = 2; i < length; i++) {
            t = i;
            while (t != 1) {
            	k = t / 2;
                if (r[k - 1] >= r[t - 1]) {
                	t = 1;
                } else {
                	tmp = r[k - 1];
                    r[k - 1] = r[t - 1];
                    r[t - 1] = tmp;
                    tmpi = c[k - 1];
                    c[k - 1] = c[t - 1];
                    c[t - 1] = tmpi;
                    t = k;
                	}
            }
        }
        for(int i = length - 1; i > 1; i--) {
        	tmp = r[i];
            r[i] = r[0];
            r[0] = tmp;
            tmpi = c[i];
            c[i] = c[0];
            c[0] = tmpi;
            t = 1;
            while (t != 0) {
            	k = 2 * t;
            	if (k > i) { t = 0; }
                else {
                	if (k < i) {
                		if (r[k] > r[k - 1]) { k++; }
                    }
                	if (r[t - 1] >= r[k - 1]) { t = 0; }
                    else {
                    	tmp = r[k - 1];
                        r[k - 1] = r[t - 1];
                        r[t - 1] = tmp;
                        tmpi = c[k - 1];
                        c[k - 1] = c[t - 1];
                        c[t - 1] = tmpi;
                        t = k;
                    }
                }
            }
        }

	int i = 0;
	while (i < length) {
    	j = i + 1;
    	while (j < length) {
        	if (r[j] != r[i]) { break; }
            j++;
        }
    	for (k = i; k <= j - 1; k++) {
        	r[k] = 1 + double(i + j - 1) / double(2);
    	}
        i = j;
	}

	for (i = 0; i < length; i++) {
		newx[c[i]] = r[i];
	}

	delete[] r;
	delete[] c;
	}
};

