// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "imageblock.h"


imageblock::imageblock()
{
    root=0;
}



void imageblock::setSizeX(size_t x){
    SizeX = x;
}

size_t imageblock::getSizeX(){
    return SizeX;
}

void imageblock::setSizeY(size_t y){
    SizeY = y;
}

size_t imageblock::getSizeY(){
    return SizeY;
}

void imageblock::setStartPoint(size_t x, size_t y){
    startPointX = x;
    startPointY = y;
}

size_t imageblock::getStartPointX(){
    return startPointX;
}

size_t imageblock::getStartPointY(){
    return startPointY;
}


void imageblock::setPosition(int blockIndexW,int blockIndexH){
    blockPosition.push_back(blockIndexW);
    blockPosition.push_back(blockIndexH);
}



void imageblock::setParameters( int indexX, int indexY,
                                GDALDataset * data,
                                int blockSizeX, int blockSizeY,
                                int blockStartX, int blockStartY,
                                int globalSizeX, int globalSizeY,
                                int globalStartX, int globalStartY,
                                IMAGEFORMAT imageFormat,
                                bool ifDeleteNoise,
                                std::vector<double> orderMin, std::vector<double> orderMax,
                                bool ifAddProbabilityModel,
                                int nClasses, int nBins,
                                bool useStdCut,
                                std::string directoryOutPut,
                                std::string directoryProbabilities,
                                bool ifPaintRandomColor,
                                std::vector<double> lamda)
{

    this->setPosition(indexX,indexY);
    this->data = data;
    this->SizeX = blockSizeX;
    this->SizeY = blockSizeY;
    this->startPointX = blockStartX;
    this->startPointY = blockStartY;
    this->globalSizeX = globalSizeX;
    this->globalSizeY = globalSizeY;
    this->globalStartX = globalStartX;
    this->globalStartY = globalStartY;
    this->imageFormat = imageFormat;
    this->nBins = nBins;
    this->nClasses = nClasses;

    this->ifDeleteNoise = ifDeleteNoise;
    this->orderMax = orderMax;
    this->orderMin = orderMin;


    this->lamda = lamda;
    this->useStdCut = useStdCut;
    this->ifAddProbabilityModel = ifAddProbabilityModel;
    this->directoryOutput = directoryOutPut;


    if( directoryProbabilities.empty() ) {
        this->fileNameProbabilities= "i" + to_string( indexX ) + "j" + to_string(indexY) + ".dat";
    } else {
        this->fileNameProbabilities= directoryProbabilities + "/" + "i" + to_string( indexX ) + "j" + to_string(indexY) + ".dat";
    }

    this->ifPaintRandomColor = ifPaintRandomColor;



}

void imageblock::processing()
{

#pragma omp critical
    {
        //load color intensity info
        this->loadBlock();
    }

    //load probability
    if(this->ifAddProbabilityModel){
        this->loadProbabilities();
    }
    this->InitializeRag();
    this->createBPT();



    this->selectedSegmentationNodes.push_back( root );
    for(int i=0; i < this->lamda.size(); i++){
        std::vector<Node*> tempSelected;
        for(int j=0; j<this->selectedSegmentationNodes.size(); j++){
            double cost;
            std::vector<Node*> temp;
            io::bestSegmentation(this->selectedSegmentationNodes[j], temp, cost, this->lamda[i], this->useStdCut);
            tempSelected.insert( tempSelected.begin(), temp.begin(), temp.end());
        }
        this->selectedSegmentationNodes.clear();
        this->selectedSegmentationNodes = tempSelected;
        tempSelected.clear();

#pragma omp critical
        {
            this->saveToDisk(i);
        }
    }


    this->root->releaseTree();

}





void imageblock::loadBlock()
{
    /**
     * @brief Load color inforn into the imageblock
     *
     * This method read color information from the image for the tile and store
     * the informatino in a vector of Mat.
     */

    io::read2Mat(&this->bands, this->data,
                 this->startPointX, this->startPointY,
                 this->SizeX, this->SizeY,
                 this->ifDeleteNoise, this->orderMin, this->orderMax);
}



void imageblock::loadProbabilities( )
{
    /**
     * @brief Load probabilies for the tile.
     * @param fileName The binary file name which stores the probabilites.
     * This method read probabilities from disk to imageblock::probabilities.
     */

    int n_items = SizeX*SizeY*nClasses;
    std::vector<double> probData(n_items);
    std::ifstream dataFile;

    dataFile.open(this->fileNameProbabilities.c_str(), std::ios_base::in | std::ios_base::binary);
    dataFile.read(reinterpret_cast<char*>(&probData[0]), n_items*sizeof(double));
    dataFile.close();

    std::vector<std::vector<std::vector<double> > > probabilities(SizeY,std::vector< std::vector <double>  >(SizeX, std::vector<double>(nClasses)) );
    for (size_t i=0;i<probabilities.size();i++)
        for (size_t j=0;j<probabilities[0].size();j++){
            for (size_t p=0;p<probabilities[0][0].size();p++){

                probabilities[i][j][p] = probData[i*SizeX*nClasses + j*nClasses + p];
            }
        }

    this->probabilities = probabilities;

    std::cout << "Pribability loaded" << endl;
    std::cout << "Probability file size is : " << probabilities.size() << "   " << probabilities[0].size() << endl;

}




void imageblock::saveToDisk( int level )
{
    /**
     * @brief Save the segmentation.
     *
     * This method save the segmentation of the tile. Segments which are not
     * touch any tiling boundaries will be save to the final segmentation.
     * while others will be save to temperary file named "i indexX j indexY", (eg,
     * a tile with indexX 3 and indexY 2, the temperary file is name as "i3j2")
     *
     *
     */

    string fileNameSegmentation = this->directoryOutput + "/segmentation" + std::to_string(level) + ".tif";
    string fileNameSegmentationCSV = this->directoryOutput + "/segmentation" + std::to_string(level) + ".csv";

    GDALDataset * classDataset;
    if( this->ifAddProbabilityModel ){
        std::string fileNameClassMap = this->directoryOutput + "/classMap" + std::to_string(level) + ".tif";
        classDataset =  (GDALDataset *) GDALOpen( fileNameClassMap.c_str(), GA_Update);
        if( classDataset == NULL )
        {
            std::cout<< "class map file open failed" <<endl;
            exit(1);
        }
    }


    GDALDataset * poDataset;
    GDALAllRegister();
    poDataset =  (GDALDataset *) GDALOpen( fileNameSegmentation.c_str(), GA_Update);
    if( poDataset == NULL )
    {
        std::cout<< "Segmentation file open failed" <<endl;
        exit(1);
    }

    ofstream fout;
    fout.open((fileNameSegmentationCSV).c_str(), ios::app);

    ofstream foutBoarder;
    std::string boraderFileName = "i" + std::to_string(this->blockPosition[0]) + "j" + std::to_string(this->blockPosition[1]);
    foutBoarder.open((boraderFileName).c_str(), ios::app);


    for(size_t i=0; i< selectedSegmentationNodes.size(); i++) {

        if(selectedSegmentationNodes[i]->getBoarderIndexX().size() == 0
                && selectedSegmentationNodes[i]->getBoarderIndexY().size() == 0) {
            // if not touching any tiling boundary
            int *color = new int[3];
            for(int j=0; j <3 ; j++){
                if(this->ifPaintRandomColor) {
                    color[j] = std::rand()%255;
                }else{
                    color[j] = selectedSegmentationNodes[i]->getMeanSpectrumAt(j);
                }
            }

            io::writeNodeToDisk(selectedSegmentationNodes[i], color, poDataset, this->globalStartX, this->globalStartY );
            io::writeNodeToCSV(selectedSegmentationNodes[i], rand()%135797531, fout);
            if( this->ifAddProbabilityModel ){
                io::writeClassMap( selectedSegmentationNodes[i], selectedSegmentationNodes[i]->getClassLabel() , classDataset, this->globalStartX, this->globalStartY );
            }
            delete[] color;

        } else if( level==0){
            // if touching some tiling boundaries
            io::writeBoarderNodeToCSV( selectedSegmentationNodes[i] , rand()%135797531, foutBoarder, this->ifAddProbabilityModel);
        }

    }





    delete poDataset;
    if( this->ifAddProbabilityModel ) delete classDataset;    fout.close();
    foutBoarder.close();
}


void imageblock::InitializeRag()
{
    /**
     * @brief Call functions to initialise rag.
     *
     * This method call functions  initializer::multispectralImageToRAG to
     * initialize rag.
     *
     *
     */

    switch (this->imageFormat){
    case U8I:
        this->rag = initializer::multispectralImageToRAG<uint8_t>(bands, probabilities,
                                                                  this->startPointX, this->startPointY,
                                                                  this->SizeX, this->SizeY,
                                                                  this->globalStartX, this->globalStartY,
                                                                  this->globalSizeX, this->globalSizeY,
                                                                  this->orderMin, this->orderMax, this->nBins);
        break;
    case U16I:
        this->rag = initializer::multispectralImageToRAG<uint16_t>(bands, probabilities,
                                                                   this->startPointX, this->startPointY,
                                                                   this->SizeX, this->SizeY,
                                                                   this->globalStartX, this->globalStartY,
                                                                   this->globalSizeX, this->globalSizeY,
                                                                   this->orderMin, this->orderMax, this->nBins);
        break;
    case S16I:
        this->rag = initializer::multispectralImageToRAG<int16_t>(bands, probabilities,
                                                                  this->startPointX, this->startPointY,
                                                                  this->SizeX, this->SizeY,
                                                                  this->globalStartX, this->globalStartY,
                                                                  this->globalSizeX, this->globalSizeY,
                                                                  this->orderMin, this->orderMax, this->nBins);
        break;
    case S32I:
        this->rag = initializer::multispectralImageToRAG<int32_t>(bands, probabilities,
                                                                  this->startPointX, this->startPointY,
                                                                  this->SizeX, this->SizeY,
                                                                  this->globalStartX, this->globalStartY,
                                                                  this->globalSizeX, this->globalSizeY,
                                                                  this->orderMin, this->orderMax, this->nBins);
        break;
    case F32:
        this->rag = initializer::multispectralImageToRAG<float>(bands, probabilities,
                                                                this->startPointX, this->startPointY,
                                                                this->SizeX, this->SizeY,
                                                                this->globalStartX, this->globalStartY,
                                                                this->globalSizeX, this->globalSizeY,
                                                                this->orderMin, this->orderMax, this->nBins);
        break;
    case F64:
        this->rag = initializer::multispectralImageToRAG<double>(bands, probabilities,
                                                                 this->startPointX, this->startPointY,
                                                                 this->SizeX, this->SizeY,
                                                                 this->globalStartX, this->globalStartY,
                                                                 this->globalSizeX, this->globalSizeY,
                                                                 this->orderMin, this->orderMax, this->nBins);
        break;
    default: exit(1);
    }


}




void imageblock::createBPT()
{
    /**
     * @brief Call functions to creat a BPT for the tile.
     *
     * This method call function regionMergion() (See RAG ) to create a BPT, the
     * root of the tree is assigned to root.
     *
     *
     */
    this->root = rag.regionMerging();

}


