About
===============
LSBPT is software based on a new framework for multi-class image segmentation using a binary partition tree. It can cooperate with color information, probability information and shape information, some of which can be used or omitted depending on the information available and the application itself. For large-scale images, by using a tile-based scheme, it enables us to process arbitrarily large images with a limited memory and computation resources. Experiments prove that the algorithm can segment large images efficiently while ensuring quite similar results with respect to processing the whole image at once.

Download
---------
The latest binaries and source of LSBPT can be downloaded from:
* https://github.com/channingxiao/lsbpt.git


Installation
--------------

LSBPT is a Qt Widgets application developed with qt4, it has been tested under Linux ( fedora 23) and Mac OSX. It depends on several external libraries, listed below with version I used, other version libraries may also work.

1. opencv 2.4.12.2
2. gdal 2.0.2
3. OpenMP (gcc-4.9.2) \ Optimal. if not enabled, there may be some warnings " ignoring pragma omp ..."

Edit the "LSBPT.pro" in src folder to configure the library dependencies. 

##### Linux and Mac OS X

Once you solve the dependencies , follow the instructions to compile.

1. git clone https://github.com/channingxiao/lsbpt.git
2. cd lsbpt
3. mkdir build 
4. cd build 
5. qmake ../src
6. make
7. chmox +x apps/LSBPT

After compiling, you'll find the executable file "LSBPT" in ~/lsbpt/build/apps, simply type " path/to/LSBPT " (i.e, app/LSBPT  if you are in build directory) in bash to launch the application.

If you are using Qt creator, use "Open project" and select the "LSBPT.pro" under 
lsbpt/src ", then follow the instructions to configure  and compile the project.

##### Windows

The installation on windows has not been tested, if you succeed to compile it on windows, please let us know.


Contact information
--------------------
If you have any questions or suggestions about the software, please contact me.
Email : chunlinxiao18@gmail.com



Enjoy,

Chunlin Xiao
