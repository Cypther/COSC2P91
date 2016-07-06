#!/usr/bin/python


"""

  Assign4

  Created by Long Nguyen on 2015-04-16.
  Student Number: 5427059
  The Header file

Part A is choice 1
Earl did those in class, I just reuse most of it
It generate an image of colour field and it's threaded
User Define number of threads

Part B is choice 2
Generate a silhouette of a sphere
It reads in a scene file, of x,y,z and radius values
to generate the sphere
Then the ray through the image and it's threaded
and writes to file

Part C is choice 3
Reading in the sphere file
And adding each line to an Array
Passing in to the C function to do the work

User Define Size of Image
Numbers of Lights(No more than 3)
Level of reflections

"""

from ctypes import *
import image

"""The compiler name"""
libraryName = './libimagework.so'
imglib = CDLL(libraryName)

"""for choice number 1 and 2"""
def getDims():
    while True:
        try:
            w = int(raw_input("Enter width: "))
            break
        except ValueError:
            print('Yeah... no.')
    while True:
        try:
            h = int(raw_input("Enter height: "))
            break
        except ValueError:
            print('Yeah... no.')
    while True:
        try:
            p = int(raw_input("# of threads: "))
            break
        except ValueError:
            print('Yeah... no.')
    if w < 1 or h < 1 or p < 1:
        return None
    return (w, h, p)

"""for choice number 3"""
def getDims3():
    while True:
        try:
            w = int(raw_input("Enter width: "))
            break
        except ValueError:
            print('Yeah... no.')
    while True:
        try:
            h = int(raw_input("Enter height: "))
            break
        except ValueError:
            print('Yeah... no.')
    if w < 1 or h < 1:
        return None
    return (w, h)

"""default menu"""
def menu():
    #print '\n1. Part A'
    print '\nCOSC 2P91: Assignment 4'
    print '1. Part A'
    print '2. Part B'
    print '3. Part C'
    print '0. Quit'
    return raw_input()


choice = -1
while (choice != '0'):
    choice = menu()
    # print'The choice is' + str(choice)
    if choice == '1':
        dims = getDims()
        if dims:
            """ getting the file name """
            filename = raw_input('Filename: ')
            """ setting the height and width """
            img = image.image(width=dims[0], height=dims[1])
            """ calling the C function to do the work """
            imglib.initializeImage(img.width, img.height, img.data)
            """ number of thread """
            imglib.processImagePartA(dims[2])
            img.writetofile(filename)
    if choice == '2':
        print'\nThe choice is' + str(choice)
        dims = getDims()
        if dims:
             #Gets the name to read and write
            filenameRead = raw_input('Filename to read: ')
            filenameWrite = raw_input('Filename to write: ')
            #i is a counter for the array
            i = 0
            #with open('scenePartB.txt', 'rb') as line:
            with open(filenameRead, 'rb') as line:
                data = line.readlines()
                #print 'what is the lenght of data ' + str(len(data))
                #length of data time 4 for colums,
                sphereData = ((c_int * (len(data) * 4)))()
                for sphere in data:
                    #print sphere
                    #for index,value in enumerate(sphere.split()):
                    for value in sphere.split():
                        #print value
                        sphereData[i] = int(value)
                        #print value
                        i = i + 1
                        #print data

        img = image.image(width=dims[0], height=dims[1])
        imglib.initializeImage(img.width, img.height, img.data)
        imglib.initializeSpheresPartB(sphereData, (len(data)))
        #number of thread
        imglib.processImagePartB(dims[2])
        #imglib.findSphere()
        img.writetofile(filenameWrite)

    if choice == '3':
        print'\nThe choice is ' + str(choice)
        dims = getDims3()
        if dims:
            #Gets the name to read and write
            filenameRead = raw_input('Filename to read: ')
            filenameWrite = raw_input('Filename to write: ')
            #i is a counter for the array
            i = 0
            with open(filenameRead, 'rb') as line:
            #with open('scenePartC.txt', 'rb') as line:
                data = line.readlines()
                #Creating an array base on the len of data
                # and multiplying by 5
                sphereData = ((c_int * (len(data) * 5)))()
                #print 'what is the lenght ' + str(len(sphereData))
                #Adding the sphere values to the array
                for sphere in data:
                    for value in sphere.split():
                        sphereData[i] = int(value)
                        i = i + 1
        #img = image.image(800, 600)
        img = image.image(width=dims[0], height=dims[1])
        #imglib.initializeImage(800, 600, img.data)
        imglib.initializeImage(img.width, img.height, img.data)
        imglib.initializeSpheres(sphereData, (len(data)))
        Reflection = int(raw_input('Levels of Reflection: '))
        lights= int(raw_input('Numbers of Lights: '))
        if lights > 3:
            print 'Can\'t have more than 3 lights'
            break;
        imglib.processImagePartC(Reflection, lights)
        img.writetofile(filenameWrite)