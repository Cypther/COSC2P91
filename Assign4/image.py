"""

  Assign4

  Created by Long Nguyen on 2015-04-16.
  Student Number: 5427059
  The image.py class file

This is the image class
-It gets instantiate with self
-User define width and height
-It prints the file after C does the work
-Save the file as P3, Portable Pixmap

-Most of this code was created by Earl
in class examples, I used most of it

"""
from ctypes import *


class image(object):
    """It's, like, an image. and junk!
        The image class """

    def __init__(self, width, height):
        """constructor documentation"""
        self.__width = width
        self.__height = height
        # Calculating the size of the image* 3 for ppm file type.
        self.__data = (c_float * (3 * width * height))()
        #print str(self.__data)

    def writetofile(self, filename):
        """Write. to a file. duh."""
        outfile = open(filename, 'w')
        #the head of the file
        outfile.write('P3\n')
        outfile.write(str(self.width) + ' ' + str(self.height) + '\n')
        outfile.write('255\n')
        """Prints out the values in RGB, each pixels holds three values Red, Green, Blue"""
        """Write a number from 0 to 255 in one of the three columns which makes up the colours """
        for h in range(self.height):
            for w in range(self.width):
                for c in range(3):
                    outfile.write(str(int(self.data[h * self.width * 3 + w * 3 + c] * 255)) + ' ')
                    #print number
                    #if number > 0:
                    #    print number
            outfile.write('\n')
        outfile.close()

    @property
    def data(self):
        """Raw image data"""
        return self.__data

    @property
    def width(self):
        """Width of image (number of columns)"""
        return self.__width

    @property
    def height(self):
        """Height of image"""
        return self.__height

    @data.setter
    def data(self, d):
        """This is a bad idea, mkay?"""
        raise AttributeError('That makes no sense')

    @width.setter
    def width(self, w):
        """This is a bad idea, mkay?"""
        raise AttributeError('That makes no sense')

    @height.setter
    def height(self, h):
        """This is a bad idea, mkay?"""
        raise AttributeError('That makes no sense')

