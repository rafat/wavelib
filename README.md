wavelib
=======

C Implementation of Discrete Wavelet Transform (DWT,SWT and MODWT), Continuous Wavelet transform (CWT) and Discrete Packet Transform ( Full Tree Decomposition and Best Basis DWPT).

Discrete Wavelet Transform Methods Implemented

DWT/IDWT A decimated Discrete Wavelet Transform implementation using implicit signal extension and up/downsampling so it is a fast implementation. A FFT based implementation is optional but will not be usually needed. Both periodic and symmetric options are available.

SWT/ISWT Stationary Wavelet Transform. It works only for signal lengths that are multiples of 2^J where J is the number of decomposition levels. For signals of other lengths see MODWT implementation.

MODWT/IMODWT Maximal Overlap Discrete Wavelet Transform is another undecimated transform. It is implemented for signals of any length but only orthogonal wavelets (Daubechies, Symlets and Coiflets) can be deployed. This implementation is based on the method laid out in "Wavelet Methods For Wavelet Analysis" by Donald Percival and Andrew Walden. 

Discrete Wavelet Packet Transform Methods Implemented

WTREE A Fully Decimated Wavelet Tree Decomposition. This is a highly redundant transform and retains all coefficients at each node. This is not recommended for compression and denoising applications.

DWPT/IDWPT Is a derivative of WTREE method which retains coefficients based on entropy methods. This is a non-redundant transform and output length is of the same order as the input.

CWT/ICWT C translation ( with some modifications) of Continuous Wavelet  Transform Software provided by C. Torrence and G. Compo, and is available at URL: http://atoc.colorado.edu/research/wavelets/'. A generalized Inverse Transform with approximate reconstruction is also added.

Documentation Available at - https://github.com/rafat/wavelib/wiki

Live Demo (Emscripten) - http://rafat.github.io/wavelib/

License - BSD 3-Clause

Contace - rafat.hsn@gmail.com
