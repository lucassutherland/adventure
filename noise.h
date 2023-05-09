// Compiler must be > C99

#ifndef NOISE_H
#define NOISE_H


/*  given an array of doubles, adds an octave layer (for value noise).

    Parameters: 
     - int rows, int cols:          dimensions of 2d array
     - double arr:                  the 2d array to add a layer to
     - int x_offset, int y_offset:  if 0, the trough will be at 0,0
     - int wavelength:              the distance between peaks
     - double amplitude:            maximum value / peak

    Returns: (nothing)
*/
void add_octave (int rows, int cols,
                double arr[rows][cols], // only valid after C99
                int x_offset, int y_offset, 
                int wavelength, double amplitude);

#endif