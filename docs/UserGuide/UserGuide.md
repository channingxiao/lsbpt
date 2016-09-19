Documentation
--------------
--------------



Run a segmentation
-------------------

Launch the application simply by double click or with command line 

*path/to/the/application/LSBPT*

an interface is showed in figure ![Interface][interface]. Click the first "..." button to select an image you want to segment and click second "..." to select a directory where you want to save the results if you want to run the segmentation with default parameter then click  the button "Go", a segmentation is running. When it finishes, a dialogue like figure ![Done][done] pops up reminding you the segmentation has been done.

[interface]: ../UserGuide/figs/interface.png 
[done]: ../UserGuide/figs/done.png



Processing a part of the image
------------------------------

It is possible to process any rectangular part of the image. The input **StartX** and **StartY** indicate the coordinates of left-up corner pixel of the rectangle part of horizontal and vertical direction respectively. Coordinates are set in up-down, left-right manner ( (0,0) at the left-up corner pixel of the image). **Widt** and **Heigh** indicate the size of the rectangle you want to process. **We use 0 to indicate the rest part of the image start from "StartX" and "StartY"**. 


Processing large-scale images with tiling strategy
--------------------------------------------------

**nBlocksX** and **nBlocksY** indicates the number of tiles to split the image into in X and Y direction respectively. The image is split evenly, except that tiles in the last column and last row will may little bit larger if the size of the image can't be divided by the number of the tiles, please reference *blockSizeCalculator_evenSplite* function in *image* class for details.


Delete outliers
----------------

If you want to delete some outliers, check the check box **Delete noise**, **nStdLeft** and **nStdRight** indicates the number of standard deviation on each side. In this case, for each channel, pixel intensities which are larger than *mean + nStdLeft * sigma* will be set to *mean + nStdRight * sigma* and pixel intensities which are smaller than *mean - nStdLeft * sigma* will be set to *mean - nStdLeft * sigma*, here "mean" is the mean value of the pixel intensities of the channel , "sigma" is the standard deviation.

Parameters for constructing BPTs and segmentation
-------------------------------------------------

1. **Num. of bins**  Indicates the number of bins of the histogram in histogram model
2. **Area weighted**  If checked, use area when computing the dissimilarities between regions, check *getOrder()* function in *compoundModel* class for more details. This term is for balancing the tree
3. **Area exponent**  The strength of using area to balance the tree
4. **Min. to merge (check box)**   If use minimum size to merge
5. **Min. to merge**  If use minimum size to merge strategy, then regions which are smaller than this number will be merged first. This strategy is also for balancing the tree, and it's also effective to eliminate some small segments
6. **Segmentation Reg**  Segmentation ( Classification ) regularization term. 




Multi-scale segmentation and classification
--------------------------------------------

LSBPT can extract multi-level segmentation or classification at the same time. The level is controlled by the regularization term **Segmentation Reg** . Several regularization terms can be used at the same time, separated with ";" an example showed in [multi-scale][multi-scale] . A descending order is recommended though not mandatory. Results will be saved with names
*segmentation+level.tif*. *level* is set starting from 0. For example, if the regularization term is set to be "10000; 50000; 2000", then "segmentation0.tif" corresponds to 50000, and "segmentation1.tif corresponds to 10000, and "segmentation2.tif" corresponds to 2000.

[multi-scale]: ../UserGuide/figs/multi-scale.png




Add probability model
----------------------

When probabilities are available,  we can add probability model. Double floats are used for probabilities, and they are written into binary file row-wise. Some example of the probability files are showed in **examples/input/probabilities**,  check *loadProbabilities()* function in *imageblock* class for more details.. 
For tiling strategy, each tile has a probability file, and it is named as "i+indexX+j+indexY.dat" ( for example for a tile in the second column and third row, the name would be "i1j2.dat").

To add probability model, check the check box **if add probability model**, and select the directory where the probability files are saved. The other parameters are :

1. **Probability Model weight**  This parameter indicates the importantness of the probability model
2. **N. classes** Number of classes 


