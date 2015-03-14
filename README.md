wavelib
=======

C Implementation of Wavelet Transform (DWT,SWT and MODWT)

Methods Implemented

DWT/IDWT A decimated Discrete Wavelet Transform implementation using implicit signal extension and up/downsampling so it is a fast implementation. A FFT based implementation is optional but will not be usually needed. Both periodic and symmetric options are available.

SWT/ISWT Stationary Wavelet Transform. It works only for signal lengths that are multiples of 2^J where J is the number of decomposition levels. For signals of other lengths see MODWT implementation.

MODWT/IMODWT Maximal Overlap Discrete Wavelet Transform is another undecimated transform. It is implemented for signals of any length but only orthogonal wavelets (Daubechies, Symlets and Coiflets) can be deployed. This implementation is based on the method laid out in "Wavelet Methods For Wavelet Analysis" by Donald Percival and Andrew Walden. 

Documentation Available at - https://github.com/rafat/wavelib/wiki

License - BSD 3-Clause

Contace - rafat.hsn@gmail.com
