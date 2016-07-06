/*
 imagework.c
 Assign4
 
 Created by Long Nguyen on 2015-04-16.
 Student Number: 5427059
 The function file
 
 */


#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>// for malloc
#include <math.h>

#include "imagework.h"

/*global variables*/
float *image;
int width;
int height;
int poolsize;

float red = 0;
float green = 0;
float blue = 0;

int numberOfSpheres;
int numberOfLights;

Ray ray;

//Array of unknown size strucks
Material *materials;
Light *lights;
Sphere *spheres;


/* The vector structure */
struct Vector{
    float x,y,z;
};

/* The sphere */
struct Sphere{
    Vector pos;
    float  radius;
    int material;
};

/* The ray */
struct Ray{
    Vector start;
    Vector direction;
};

/* Colour */
struct Colour{
    float red, green, blue;
};

/* Material Definition */
struct Material{
    Colour diffuse;
    float reflection;
};

/* Lightsource definition */
struct Light{
    Vector pos;
    Colour ambientLighting;
};

/* Code For Part A 
   Earl Foxwell's Code that he did in Class Used for Part A */

/* The ThreadDeital structure */
struct ThreadDetails {
    int xStart;
    int finishedFlag;
};

/* Processing the Pixel for Part A */
static void processPixelPartA(int x, int y){
    float r,g,b;
    r = (x/(float)width);
    b = (y/(float)width);
    g = 0.25;
    image[y * width * 3 + x * 3] = r;
    image[y * width * 3 + x * 3 + 1] = g;
    image[y * width * 3 + x * 3 + 2] = b;
}

/* Part of the threading function to process the X and Y */
static void *processBlinds(void *td) {
    struct ThreadDetails *threadDeets;
    threadDeets=(struct ThreadDetails*)td;
    int i,j;
    for (i = 0; i < height; i++)
        for ( j = threadDeets->xStart ; j < width ; j += poolsize)
            processPixelPartA(j,i);
    threadDeets->finishedFlag=1;
    return 0;
}

/* passing in number of threads to prcoess the image file for part A */
void processImagePartA(int numberOfThreads){
    
    pthread_t pool[numberOfThreads];
    struct ThreadDetails threadDeets[numberOfThreads];
    int i;
    int notFinishedFlag;
    poolsize = numberOfThreads;
    
    //number of threads
    for (i=0; i < poolsize; i++ ) {
        threadDeets[i].xStart = i;
        threadDeets[i].finishedFlag = 0;
        pthread_create(&pool[i],NULL,processBlinds,&threadDeets[i]);
    }
    do {
        notFinishedFlag = 0;
        
        for (i = 0; i<poolsize ; i++)
            notFinishedFlag=notFinishedFlag | !threadDeets[i].finishedFlag;
        usleep(1000);
    } while (notFinishedFlag);
}

/* passing in number of threads to prcoess the image file for part B */
void processImagePartB(int numberOfThreads) {
    pthread_t pool[numberOfThreads];
    struct ThreadDetails threadDeets[numberOfThreads];
    int i;
    int notFinishedFlag;
    poolsize = numberOfThreads;
    
    //number of threads
    for (i=0; i < poolsize; i++ ) {
        threadDeets[i].xStart = i;
        threadDeets[i].finishedFlag = 0;
        pthread_create(&pool[i],NULL,processSpherePartB,&threadDeets[i]);
    }
    do {
        notFinishedFlag = 0;
        
        for (i = 0; i<poolsize ; i++)
            notFinishedFlag=notFinishedFlag | !threadDeets[i].finishedFlag;
        usleep(1000);
    } while (notFinishedFlag);
}

/* Code for Part B */

/* Checking what X and Y value are the sphere located */
static void *processSpherePartB(void *td){
    
    struct ThreadDetails *threadDeets;
    threadDeets = (struct ThreadDetails*)td;
    
    Ray ray;
    
    /* Ray Starting Direction*/
    ray.direction.x = 0;
    ray.direction.y = 0;
    ray.direction.z = 1;
    /* Start position of the ray, z coordinate */
    ray.start.z = 0;
    
    /* Intersect ray/sphere or not */
    int intersect = 0;
    
    int x,y,s;
    
    for(y = 0; y < height; y++){
        /* Set the y-coordinate of the start position of the ray */
        ray.start.y = y;
        for ( x = threadDeets->xStart ; x < width ; x += poolsize){
            /* Set the x-coordinate of the start position of the ray */
            ray.start.x = x;
            
            // Check if the ray intersects with the shpere
            // if it does break
            for (s = 0; s < numberOfSpheres; s++) {
                intersect = intersectRaySpherePartB(&ray, &spheres[s]);
                if (intersect == 1) {
                    break;
                }
            }
            /* if there's an interection, draws the red colour */
            if (intersect == 1) {
                processPixelRedPartB(x,y);
            }else{
            /* no interection draw black */
                processPixelBlackPartB(x,y);
            }
            
        }
        
    }
    /* thread flag to true when done */
    threadDeets->finishedFlag=1;
    return 0;
}

/* Check if the ray and sphere intersect */
int intersectRaySpherePartB(Ray *ray, Sphere *sphere){
    
    float A, B, C, root;
    
    /* The vector dot product of the direction */
    A = vectorDotProduct(&ray->direction, &ray->direction);
    
    /* The vector distance from the start of
       the ray and the position of the circle. */
    Vector distance = vectorSubtraction(&ray->start, &sphere->pos);
    
    /* Postiion - c */
    B = 2 * vectorDotProduct(&ray->direction, &distance);
    
    /* (postion - c)^2 - r^2 */
    C = vectorDotProduct(&distance, &distance) - (sphere->radius * sphere->radius);
    
    /* Solving the discriminant */
    root = B * B - 4 * A * C;
    
    /* If the root is negtive return false/zero */
    if(root < 0){
        return 0;
    }
    return 1;
}

/* Colouring in the pixel black if there's no intersection */
static void processPixelBlackPartB(int x, int y){
    float black;
    black = 0.00;
    image[ y * width * 3 + x * 3 ] = black;
}

/* Colouring in the pixel red if there's an intersection */
static void processPixelRedPartB(int x, int y){
    float red;
    red = 1.00;
    image[y * width * 3 + x * 3] = red;
}


/* Initialize the number of Sphere when it's passed in from Python */
void initializeSpheresPartB(int sphereArrayData[], int howManySpheres) {
    
    //Number of spheres set
    numberOfSpheres = howManySpheres;
    
    //allocation memory for the number of spheres
    //casting the malloc to sphere strct, and mult timees number of spheres
    //basically creating an array of spheres.
    spheres = (Sphere*)malloc(sizeof(Sphere)*numberOfSpheres);
    
    int i;
    
    //initialize sphere struct with data from the array
    for (i = 0; i < numberOfSpheres; i++) {
        (spheres + i)->pos.x = sphereArrayData[(i*4)];
        (spheres + i)->pos.y = sphereArrayData[(i*4)+1];
        (spheres + i)->pos.z = sphereArrayData[(i*4)+2];
        (spheres + i)->radius = sphereArrayData[(i*4)+3];
    }
}

/* Processing the scene 
   levels of reflections and numbers of lights being passed in
 
   The algorithm:
 
    for(y)
        for(x)
            for(level of reflection)
            - pcoess each ray:
            - look for closest ray/sphere intersection in the panel
            - loop over every spheres in the scence
               
            - check for the current light souce
            - loop every light
            - calculate the right colour
 
 */

void processImagePartC(int levelOfReflection, int howManyLights){
    
    initializeMaterial(numberOfSpheres);
    initializeLights(howManyLights);
    
    int xAxis, yAxis;
    /* Looping through x and y */
    for(yAxis = 0; yAxis < height; yAxis++){
        for(xAxis = 0; xAxis < width; xAxis++){
            
            red = 0;
            green = 0;
            blue = 0;
            
            //int level = 0;
            float levelDetail = 1.0;
            
            initializeRay(xAxis,yAxis);
            
            int i;
            for (i = 0; i < levelOfReflection; i++) {
                
                levelDetail = rayCalculation(levelDetail);
                
            }//for loop
            
            if (red > 0 || green > 0 || blue > 0) {
                processPixelImage(xAxis,yAxis);
            }else{
                //processPixelSphereImage(x,y);
                processGrayBackGround(xAxis,yAxis);
            }
            
        }
    }
}


/* Initialize mage size */
void initializeImage(int w, int h, float *i){
    width = w;
    height = h;
    image = i;
}

void initializeLights(int howManyLights) {
    
    int i; //for loop counter
    
    /* for low ambientLighting lighting */
    if (howManyLights == 0) {
        numberOfLights = 1;
        lights = (Light*)malloc(sizeof(Light)*numberOfLights);
        float lowlightProperties[6] = {400,300,-600,0.2,0.2,0.2};
        
        for (i = 0; i < numberOfLights; i++) {
        (lights + i)->pos.x = lowlightProperties[(i*6)+0];
        (lights + i)->pos.y = lowlightProperties[(i*6)+1];
        (lights + i)->pos.z = lowlightProperties[(i*6)+2];
        (lights + i)->ambientLighting.red = lowlightProperties[(i*6)+3];
        (lights + i)->ambientLighting.green = lowlightProperties[(i*6)+4];
        (lights + i)->ambientLighting.blue = lowlightProperties[(i*6)+5];
        }
        return;
        
    }else{
     numberOfLights = howManyLights;
    }
                                    //Light:1
    float onelightProperties[6] = {400,300,-600,1,1,1};
    
                                      //Light:1          //Light:2                  //Light:3
    float threelightProperties[18] = {0,240,-100,1,1,1,  3200,3000,-1000,0.6,0.7,1,  600,0,-100,0.3,0.5,1};
    
    //allocation memory for the number of lights
    //casting the malloc to Light struct, and mult timees number of lights
    //basically creating an array of lights.
    lights = (Light*)malloc(sizeof(Light)*numberOfLights);
    
    if(howManyLights == 1){
        //initialize mater struct with data from the lightProperties array
        for (i = 0; i < numberOfLights; i++) {
            (lights + i)->pos.x = onelightProperties[(i*6)+0];
            (lights + i)->pos.y = onelightProperties[(i*6)+1];
            (lights + i)->pos.z = onelightProperties[(i*6)+2];
            (lights + i)->ambientLighting.red = onelightProperties[(i*6)+3];
            (lights + i)->ambientLighting.green = onelightProperties[(i*6)+4];
            (lights + i)->ambientLighting.blue = onelightProperties[(i*6)+5];
        }
    }else{
    //initialize mater struct with data from the lightProperties array
        for (i = 0; i < numberOfLights; i++) {
            (lights + i)->pos.x = threelightProperties[(i*6)+0];
            (lights + i)->pos.y = threelightProperties[(i*6)+1];
            (lights + i)->pos.z = threelightProperties[(i*6)+2];
            (lights + i)->ambientLighting.red = threelightProperties[(i*6)+3];
            (lights + i)->ambientLighting.green = threelightProperties[(i*6)+4];
            (lights + i)->ambientLighting.blue = threelightProperties[(i*6)+5];
        }
    }
    
}

void initializeMaterial(int howManyMaterial){
    
    
    //MaterialColour array sort the colour and reflectin data
                                //red,    //green,  //blue,  //white   //Orange
    float materialColour[20] = {1,0,0,1,  0,1,0,1,  0,0,1,1, 1,1,1,1, 1,0.5,0,1};
    
    
    //allocation memory for the number of Material
    //casting the malloc to Material struct, and mult timees number of Material
    //basically creating an array of Material.
    materials = (Material*)malloc(sizeof(Material)*howManyMaterial);
    
    int i;
    
    //initialize mater struct with data from the colour array
    for (i = 0; i < howManyMaterial; i++) {
        (materials + i)->diffuse.red = materialColour[(i*4)];
        (materials + i)->diffuse.green = materialColour[(i*4)+1];
        (materials + i)->diffuse.blue = materialColour[(i*4)+2];
        (materials + i)->reflection = materialColour[(i*4)+3];
    }
    
}

void initializeSpheres(int sphereArrayData[], int howManySpheres) {
    
    //Number of spheres set
    numberOfSpheres = howManySpheres;
    
    //allocation memory for the number of spheres
    //casting the malloc to sphere strct, and mult timees number of spheres
    //basically creating an array of spheres.
    spheres = (Sphere*)malloc(sizeof(Sphere)*numberOfSpheres);
    
    int i;
    
    //initialize sphere struct with data from the array
    for (i = 0; i < numberOfSpheres; i++) {
        (spheres + i)->pos.x = sphereArrayData[(i*5)];
        (spheres + i)->pos.y = sphereArrayData[(i*5)+1];
        (spheres + i)->pos.z = sphereArrayData[(i*5)+2];
        (spheres + i)->radius = sphereArrayData[(i*5)+3];
        (spheres + i)->material = sphereArrayData[(i*5)+4];
    }
}

/* Our ray and a sphere */
void initializeRay(x,y){
    
    ray.start.x = x;
    ray.start.y = y;
    ray.start.z = -2000;
    
    ray.direction.x = 0;
    ray.direction.y = 0;
    ray.direction.z = 1;
    
    
}

/* Calculate Vector x Scalar and return resulting Vector*/
Vector vectorScalar(float c, Vector *vector){
    
    Vector result;
    result.x = (vector->x * c);
    result.y = (vector->y * c);
    result.z = (vector->z * c);
    
    return result;
}

/* Multiply two vectors and return the resulting scalar (dot product) */
float vectorDotProduct(Vector *vector1, Vector *vector2){
    
    float result = 0;
    
    result += (vector1->x * vector2->x);
    result += (vector1->y * vector2->y);
    result += (vector1->z * vector2->z);
    
    return result;
}

/* Add two vectors and return the resulting vector */
Vector vectorAddition(Vector *vector1, Vector *vector2){
    
    Vector result;
    result.x = (vector1->x + vector2->x);
    result.y = (vector1->y + vector2->y);
    result.z = (vector1->z + vector2->z);
    
    return result;
}


/* Subtract two vectors and return the resulting vector */
Vector vectorSubtraction(Vector *vector1, Vector *vector2){
    
    Vector result;
    result.x = (vector1->x - vector2->x);
    result.y = (vector1->y - vector2->y);
    result.z = (vector1->z - vector2->z);
    
    return result;
}

/* Check if the ray and sphere intersect */
int intersectRaySphere(Ray *ray, Sphere *sphere, float *closestIntersection){
    
    float A,B,C;
    int intersect = 0;
    
    /* A = direction * direction , the vector dot product of the direction */
    A = vectorDotProduct(&ray->direction, &ray->direction);
    
    /* The vector distance from the start of
     the ray and the position of the circle. */
    Vector distance = vectorSubtraction(&ray->start, &sphere->pos);
    
    /* 2*(postion - c) */
    B = 2 * vectorDotProduct(&ray->direction, &distance);
    
    /* (position - c)^2 - r^2 */
    C = vectorDotProduct(&distance, &distance) - (sphere->radius * sphere->radius);
    
    /*Solve the  Quadratic Formula */
    
    intersect = quadraticFormula(A, B, C, closestIntersection);
    
    return intersect;
}

/* Quadratic Formaula function */
int quadraticFormula(float A, float B, float C, float *closestIntersection){
    
    float squareRoot, pointOfIntersect1, pointOfIntersect2;
    
    float root = ((B * B)-(4 * A * C));
    
    /* If the root is negative, there are no real number.*/
    if(root < 0){
        return 0;
    }else{
        squareRoot = sqrtf(root);
        pointOfIntersect1 = ((-B + squareRoot)/(2));
        pointOfIntersect2 = ((-B - squareRoot)/(2));
        // We want the closest one
        if(pointOfIntersect1 > pointOfIntersect2){
            pointOfIntersect1 = pointOfIntersect2;
        }
        
        //Verify t1 larger than 0 and less than the original t
        if((pointOfIntersect1 > 0.001) && (pointOfIntersect1 < *closestIntersection)){
            *closestIntersection = pointOfIntersect1;
            return 1;
        }
    }
    return 0;
}

/* colouring in the pixels after the Calculation */
static void processPixelImage(int x, int y){
    
    image[y*width*3+x*3]= red;
    image[y*width*3+x*3 + 1]= green;
    image[y*width*3+x*3 + 2]= blue;
    
}

/* 18% percent gray RGB*/
static void processGrayBackGround(int x,int y){
    
    /* Black Back ground */
    image[y*width*3+x*3]= 0;
    image[y*width*3+x*3 + 1]= 0;
    image[y*width*3+x*3 + 2]= 0;
    
    /*image[y*width*3+x*3]= 0.47;
    image[y*width*3+x*3 + 1]= 0.47;
    image[y*width*3+x*3 + 2]= 0.47;*/
    
}

/* Lambert diffusion */
void LambertDiffusion(float lambert, Light currentLight, Material currentMaterial){
    
    
    /*Colouring the intensity of each ight*/
    /* The dot product of Lambert 
     "Lambertian reflectance is the property that defines the
     "matte" or diffusely reflected surface area" */
    red += (lambert * currentLight.ambientLighting.red * currentMaterial.diffuse.red);
    green += (lambert * currentLight.ambientLighting.green * currentMaterial.diffuse.green);
    blue += (lambert * currentLight.ambientLighting.blue * currentMaterial.diffuse.blue);

}

//void lightCalculation(){
float rayCalculation(float levelDetail){
    
    /* Default closest interection to 3000*/
    float closestIntersection = 3000;
    int currentSphere = -1;
    
    int i;
    for(i = 0; i < numberOfSpheres; i++){
        
        //if Ray and Sphere intersect
        if((intersectRaySphere(&ray, &spheres[i], &closestIntersection)) == 1){
            currentSphere = i;
        }
    }
    //if not intersection found return
    if(currentSphere == -1){
        return levelDetail;
    }
    
    //Finding the scaler value of the closestInterestion and the ray directions
    Vector scaled = vectorScalar(closestIntersection, &ray.direction);
    //Starting at the new location just found
    Vector newStart = vectorAddition(&ray.start, &scaled);
    
    //Find the normal for this new vector at the point of intersection
    Vector normal = vectorSubtraction(&newStart, &spheres[currentSphere].pos);
    
    float temp = vectorDotProduct(&normal, &normal);
    
    //if there's no dot product of the normal vector return
    if(temp == 0){
        return levelDetail;
    }
    
    temp = (1.0 / sqrtf(temp));
    //Setting the noram vector
    normal = vectorScalar(temp, &normal);
    
    //calucting the lights and shadows
    levelDetail = lightCalculation(levelDetail, currentSphere, &newStart, &normal);
    
    // The reflected ray start and direction
    ray.start = newStart;
    float reflect = 2 * vectorDotProduct(&ray.direction, &normal);
    Vector tmp = vectorScalar(reflect, &normal);
    ray.direction = vectorSubtraction(&ray.direction, &tmp);

    return levelDetail;
}



/* Calculating the lights and shadows*/
float lightCalculation(float levelDetail, int currentSphere, Vector *newStart, Vector *normal){

     // Determine  the current material
     int getMaterialIndexValue = (spheres + currentSphere)->material;
     Material currentMaterial = materials[getMaterialIndexValue];
     
     //Find the value of the light at the current position
     int j;
    
     for( j = 0; j < numberOfLights; j++){
     
         Light currentLight = lights[j];
         Vector distance = vectorSubtraction(&currentLight.pos, newStart);
     
         //If the dot product of the normal and the distance is less than or equal to zero
         //coutinue
         if(vectorDotProduct(normal, &distance) <= 0) {
             continue;
         }
     
         float closestIntersection;
         
         //setting the new closesInterection point
         closestIntersection = sqrtf(vectorDotProduct(&distance,&distance));
     
         if(closestIntersection <= 0) {
             continue;
         }
     
         Ray lightRay;
         lightRay.start = *newStart;
         lightRay.direction = vectorScalar((1/closestIntersection), &distance);
     
         // Calculate shadows
         int shadow = 0;
         int k;
     
         for (k = 0; k < numberOfSpheres; ++k){
     
             if (intersectRaySphere(&lightRay, &spheres[k], &closestIntersection) == 1){
                 shadow = 0;
                 break;
             }
         }
         if (shadow != 1){
     
             //Calculating the lambert value
             float lambert = vectorDotProduct(&lightRay.direction, normal) * levelDetail;
             //Processing the Lambert Diffusion
             LambertDiffusion(lambert, currentLight, currentMaterial);
     
         }
        }
    levelDetail *= currentMaterial.reflection;
    
    return levelDetail;

}

