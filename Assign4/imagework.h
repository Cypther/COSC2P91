/*
  imagework.h
  Assign4

  Created by Long Nguyen on 2015-04-16.
  Student Number: 5427059
  The Header file
 
*/


/* Tydef struct definitions */
typedef struct ThreadDetails ThreadDetails;
typedef struct Vector Vector;
typedef struct Sphere Sphere;
typedef struct Ray Ray;
typedef struct Colour Colour;
typedef struct Material Material;
typedef struct Light Light;


/* Function Prototype Part A */
static void processPixelPartA(int x, int y);
static void *processBlinds(void *td);
void processImagePartA(int numberOfThreads);

/* Function Prototype Part B */
int intersectRaySpherePartB(Ray *ray, Sphere *sphere);
static void processPixelBlackPartB(int x, int y);
static void processPixelRedPartB(int x, int y);
void initializeSpheresPartB(int sphereArrayData[], int howManySpheres);
void processImagePartB(int numberOfThreads);
static void *processSpherePartB(void *td);


/* Function Prototype Parts C */
void processImagePartC(int levelOfReflection, int howManyLights);

/* Initialize Function */
void initializeImage(int w, int h, float *i);
void initializeLights(int howManyLights);
void initializeMaterial(int howManyMaterial);
void initializeSpheres(int sphereArrayData[], int howManySpheres);
void initializeRay(int x, int y);

/* Vector Math */
Vector vectorScalar(float c, Vector *vector);
float vectorDotProduct(Vector *vector1, Vector *vector2);
Vector vectorAddition(Vector *vector1, Vector *vector2);
Vector vectorSubtraction(Vector *vector1, Vector *vector2);

int intersectRaySphere(Ray *ray, Sphere *sphere, float *closestIntersection);
int quadraticFormula(float A, float B, float C, float *closestIntersection);

/* Process Function Part C */
static void processPixelImage(int x, int y);
static void processGrayBackGround(int x,int y);
void LambertDiffusion(float lambert, Light currentLight, Material currentMaterial);
float rayCalculation(float levelDetail);
float lightCalculation(float levelDetail, int currentSphere, Vector *newStart, Vector *normal);
