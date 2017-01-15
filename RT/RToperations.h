/*******************************************************************************
 * 
 * This file is part of BAIPROJECT.
 * 
 * BAIPROJECT is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License version 3
 * only, as published by the Free Software Foundation.
 * 
 * BAIPROJECT is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License version 3 for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 * 
 * You should have received a copy of the GNU Affero General Public License
 * version 3 along with BAIPROJECT.  If not, see <http://www.gnu.org/licenses/>
 * for a copy of the AGPLv3 License.
 * 
 *******************************************************************************/

/*******************************************************************************
 *
 * File Name: RToperations.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2012 Baxter AI (baxterai.com)
 * Project: Raytracer Functions
 * Project Version: 3c1a 11-October-2012
 *
 *******************************************************************************/


#ifndef HEADER_RT_OPERATIONS
#define HEADER_RT_OPERATIONS

//#define MISS (-1)
#define LINE_INTERSECTION_BOUNDARY_ERROR_ALLOWED (0.01)


#include "SHAREDvars.h"
#include "SHAREDvector.h"
//#include "math.h"

	/*4x4 matrix manipulation methods*/

typedef struct { double x; double y; double z; double w;} advanced_vec;

typedef struct { advanced_vec a; advanced_vec b; advanced_vec c; advanced_vec d;} advanced_mat;


void makeAdvancedMatrix(advanced_mat* matxAdv, mat* matx, int type);
void multAdvancedMatrix(advanced_mat* matxAdv1, advanced_mat* matxAdv2, advanced_mat* matxAdv);
void createIdentityMatrixAdvanced(advanced_mat* matx);
void createInverseTranslationMatrix(double xpos, double ypos, double zpos, advanced_mat* matx);
void createTranslationMatrix(double xpos, double ypos, double zpos, advanced_mat* matx);
void createScaleMatrix(double width, double length, double height, advanced_mat* matx);
void createInverseScaleMatrix(double width, double length, double height, advanced_mat* matx);
void createRotationxMatrix(double rotation, advanced_mat* matx);
void createInverseRotationxMatrix(double rotation, advanced_mat* matx);
void createRotationyMatrix(double rotation, advanced_mat* matx);
void createInverseRotationyMatrix(double rotation, advanced_mat* matx);
void createRotationzMatrix(double rotation, advanced_mat* matx);
void createInverseRotationzMatrix(double rotation, advanced_mat* matx);
void invertAdvancedMatrix(advanced_mat* matx);
void transposeAdvancedMatrix(advanced_mat* matx);
void multAdvancedMatrixByVector(advanced_vec* vecAdv1, advanced_mat* matxAdv1, advanced_vec* vecAdv);
double toRadians(double degrees);
void toAdvancedVector(vec* vec, int type, advanced_vec* vecAdv);
void fromAdvancedVector(advanced_vec* vecAdv, vec* vec);
void createAdvancedVector(advanced_vec* vec);


double findSmallestValue(double val1, double val2, double val3);
double findGreatestValue(double val1, double val2, double val3);
	/*finds the smallest/largest value of 3 given scalars*/

int findPositionOfSmallestValueAdvanced(double *array, unsigned int size);
int findPositionOfGreatestValueAdvanced(double *array, unsigned int size);

int findIntersectLineWithTri(vec * pt1, vec * pt2, vec * pt3, vec * linept1, vec * linept2, vec * pt_int, vec * norm, double * t);
	int checkSameClockDir(vec * pt1, vec * pt2, vec * pt3, vec * norm);
int findIntersectLineWithLine(vec * linept1, vec * linept2, vec * povpt1, vec * povpt2, vec * pt_int, vec * norm, double * t);
	bool findIntersectLineWithLine2D(vec* povpt1, vec* povpt2, vec* linept1, vec* linept2, vec * pt_int);
int findIntersectLineWithQuad(vec * pt1, vec * pt2, vec * pt3, vec * pt4, vec * linept1, vec * linept2, vec * pt_int, vec * norm, double * t);



double findSmallestValueAdvanced(double val1, double val2);
double findSmallestValue(double val1, double val2);
double findGreatestValueAdvanced(double val1, double val2);
double findGreatestValue(double val1, double val2);

int findPositionOfSmallestValueWhichHits(double *array, int *hitsArray, unsigned int size);
int findPositionOfGreatestValueWhichHits(double *array, int *hitsArray, unsigned int size);

#endif
