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

#include "image.h"
#include "QMessageBox"
#include "compoundmodel.h"




void image::processing()
{
    /**
     * @brief Call functions to process the image
     *
     *
     * This method calls functions to process each tile independtly, functions
     * to reprocess verticle tiling boundaries, then functions to reprocess
     * horizotal tiling boundaries.
     *
     */

    this->ProcessTiles();
    this->ProcessBoundaryX();
    this->ProcessBoundaryY();

}


void image::ProcessTiles()
{
    /**
     * @brief Process a tile.
     *
     * This method process a tile, including loading image, build a BPT and find the segmentation,
     * save segments which do not touch any tiling boundary to disk, and send the others to temperary pool.
     *
     *
     */


#pragma omp parallel for
    for(int i =0; i< this->nBlocksX; i++){
        for(int j =0; j< this->nBlocksY; j++){

#pragma omp critical
            {
                //print some basic info to log file
                this->PrintTileInfo(i,j);
            }
            imageblock temp;
            temp.setParameters( i, j, this->data,
                                this->blockSizeW[i], this->blockSizeH[j],
                                this->blocksStartPointX[i], this->blocksStartPointY[j],
                                this->imageWidth, this->imageHeight,
                                this->startPointX, this->startPointY,
                                this->imageFormat,
                                this->ifDeleteNoise, this->orderMin, this->orderMax,
                                this->ifAddProbabilityModel,
                                this->nClasses, this->nbins,
                                this->useStdCut,
                                this->directoryOutput,
                                this->directoryProbabilities,
                                this->ifPaintRandomColor,
                                this->lamda);
            temp.processing();

        }
    }

//wait all thread arrives
#pragma omp barrier


}


void image::ProcessBoundaryX()
{
    /**
     * @brief This method process verticle tiling boundaries.
     *
     * This method will reprocess segments which touch the verticle tiling
     * boundaries. Instead of processing tiling boundaries from left to right one
     * by one, we use a strategy which can run parallely. Here is an example which
     * explains the idea. For example we have 9 by 1 tiles ( we only consider
     * verticle tiling boundaries here), there are 8 verticle boundaries in total,
     * at first round, we process number 1,3,5,7 and in second round, we process
     * number 2 and 6, third round number 4 and firth round number 8. At each round,
     * the tiling boundaries can be reprocess parallely.
     *
     */

    int circle = this->ComputeCircle ( this->nBlocksX - 1 );

    for( int index=1; index < circle +1; index++){
        std::cout << "working on circle " << index << endl;
        int step = pow(2,index);

        #pragma omp parallel for schedule(runtime)
        for( int i = pow(2,index-1); i < this->nBlocksX;  i += step){
            #pragma omp parallel for schedule(dynamic)
            for( int j=0; j < this->nBlocksY; j++ ) {
                std::vector<WorkingBoundary> workingBoundaries;
                WorkingBoundary tempBoundary1(1, this->blocksStartPointX[i]-1 ,
                                              this->blocksStartPointY[j],
                                              this->blocksStartPointY[j]+this->blockSizeH[j]-1);
                WorkingBoundary tempBoundary2(1, this->blocksStartPointX[i],
                                              this->blocksStartPointY[j],
                                              this->blocksStartPointY[j]+this->blockSizeH[j]-1);
                workingBoundaries.push_back(tempBoundary1);
                workingBoundaries.push_back(tempBoundary2);

                std::vector<int> blockPosition1, blockPosition2;
                blockPosition1.push_back(i-1);
                blockPosition1.push_back(j);
                blockPosition2.push_back(i);
                blockPosition2.push_back(j);
                this->mergeBlockX( workingBoundaries, blockPosition1, blockPosition2 );
            }
        }
        #pragma omp barrier
    }


}


void image::ProcessBoundaryY()
{
    /**
     * @brief This method process horizontal tiling boundaries.
     *
     *
     *
     */

    int circle = this->ComputeCircle ( this->nBlocksY - 1);

    for( int index=1; index < circle +1; index++){
        std::cout << "working on circle " << index << endl;
        int step = pow(2,index);
#pragma omp parallel for
        for( int j = pow(2,index-1); j < this->nBlocksY;  j += step){
            for( int i=0; i < this->nBlocksX; i++ ) {
                std::vector<WorkingBoundary> workingBoundaries ;// a function to find the working boundaries smartly
                WorkingBoundary tempBoundary1(0, this->blocksStartPointY[j]-1 , this->blocksStartPointX[i],
                                              this->blocksStartPointX[i]+this->blockSizeW[i]-1);

                WorkingBoundary tempBoundary2(0, this->blocksStartPointY[j]   , this->blocksStartPointX[i],
                                              this->blocksStartPointX[i]+this->blockSizeW[i]-1);

                workingBoundaries.push_back(tempBoundary1);
                workingBoundaries.push_back(tempBoundary2);

                std::vector<int> blockPosition1, blockPosition2;
                blockPosition1.push_back(i);
                blockPosition1.push_back(j-1);
                blockPosition2.push_back(i);
                blockPosition2.push_back(j);
                this->mergeBlockY( workingBoundaries, blockPosition1, blockPosition2 );

            }
        }
#pragma omp barrier

    }

}




void image::findImageFormat()
{
    /**
     * @brief Fetch the image format.
     * This method use GDAL to fetch image format, and assign value to image::imageFormat
     *
     */

    switch ( this->data->GetRasterBand(1)->GetRasterDataType()) {
    case GDT_Byte : {
        this->imageFormat = U8I; // unsigned 8 byte integer
    }break;
    case GDT_UInt16 : {
        this->imageFormat = U16I; // unsigned 16 byte interger
    }break;
    case GDT_Int16 : {
        this->imageFormat = S16I; // signed 16 byte interger
    }break;
    case GDT_UInt32 :{
        this->imageFormat = U32I; // unsigned 32 byte integer
    }break;
    case GDT_Int32 : {
        this->imageFormat = S32I; // signed 32  byte interger
    }break;
    case GDT_Float32 : {
        this->imageFormat = F32; // float
    }break;
    case GDT_Float64 :{
        this->imageFormat = F64; // double
    }break;
    default: exit(1);

    }

}



void image::linkFile()
{
    /**
     * @brief Open image file with GDAL, set data to the returned GDALDataset pointer
     *
     */

    GDALAllRegister();
    this->data =  (GDALDataset *) GDALOpen( this->fileNameImage.c_str(), GA_ReadOnly );
    if( this->data== NULL ) {
        QMessageBox::critical(NULL,"Error!", "Open image with GDAL failed!");
    } else {
        this->findImageFormat();
        std::cout<<"Image linked" <<endl;
    }

    GetGDALDriverManager()->AutoSkipDrivers();

}



void image::PrintTileInfo(int indexX, int indexY)
{
    /**
     * @brief Print out some basic information about the tile under processing to log file
     *
     */

    FILE * logFile = fopen( this->logFileName.c_str(), "a" );
    fprintf( logFile, "Processing tile ( %d , %d ), the tile start point is ( %d ,%d ), tiles size is ( %d , %d )\n",
            indexX, indexY, this->blocksStartPointX[indexX], this->blocksStartPointY[indexY],
            this->blockSizeW[indexX], this->blockSizeH[indexY]);
    fclose(logFile);
}







int image::ComputeCircle( int totalTiles )
{
    /**
     * @brief Compute how many rounds needed to reprocess the tiling boundaries.
     *
     * /param totalTiles The total number of tiles in the direction to reprocess.
     * /return The number of rounds.
     */

    int counter = totalTiles;
     int circle = 0;
     while( counter >= 1){
         counter /= 2;
         circle++;
     }
     return circle;
}




void image::mergeBlockX(const std::vector< WorkingBoundary > &workingBoundaries,
                        const std::vector<int> &blockPosition1,
                        const std::vector<int> &blockPosition2)
{
    /**
     * @brief Merge two vertical neighbouring tiles.
     *
     * This function merges two vertical neighbouring tiles. It takes all segments
     * which touch the workingBoundaries, and reprocess them from pixel level.
     * Then segments whichs do not touch any non-processed tiling boundary will
     * be saved to final segmentation. Others will be saved into a proper temperary
     * file, see method saveTodisk2().
     */

    //read segments from temperary file
    std::vector<Node *> selectedBoarderNodes;
    std::string fileName1 = "i" + std::to_string( blockPosition1[0] ) + "j" + std::to_string(blockPosition1[1]);
    std::string fileName2 = "i" + std::to_string( blockPosition2[0] ) + "j" + std::to_string(blockPosition2[1]);
    this->selectBoarderSegments( &selectedBoarderNodes,  workingBoundaries, fileName1.c_str());
    this->selectBoarderSegments( &selectedBoarderNodes,  workingBoundaries, fileName2.c_str());

    if( selectedBoarderNodes.size() ==0 ) {
        qDebug() << "There is something wrong in selectBoarderNodes.";
        return;
    }


    RAG ragBoarder;
    initializer::initializeRag(ragBoarder, selectedBoarderNodes);
    Node *root;
    root = ragBoarder.regionMerging();

  //  double cost=0;
  //  std::vector<Node *> boarderSegmentationNodes;
  //  this->bestSegmentation(root,boarderSegmentationNodes, cost);


#pragma omp critical
    {
      //  saveToDisk(boarderSegmentationNodes, blockPosition1[1]);

    }



    std::vector<Node*> selectedSegmentationNodes;
    selectedSegmentationNodes.push_back(root);
    for(int i=0; i < this->lamda.size(); i++){
        std::vector<Node*> tempSelected;
        for(int j=0; j < selectedSegmentationNodes.size(); j++){
            double cost;
            std::vector<Node*> temp;
            io::bestSegmentation(selectedSegmentationNodes[j], temp, cost, this->lamda[i], this->useStdCut);
            tempSelected.insert( tempSelected.begin(), temp.begin(), temp.end());
        }
        selectedSegmentationNodes.clear();
        selectedSegmentationNodes = tempSelected;
        tempSelected.clear();

#pragma omp critical
        {
            saveToDisk(selectedSegmentationNodes, blockPosition1[1], i);
        }
    }





    root->releaseTree();


}





void image::mergeBlockY(const std::vector< WorkingBoundary > &workingBoundaries,
                        const std::vector<int> &blockPosition1,
                        const std::vector<int> &blockPosition2)
{
    /**
     * @brief Merge two verticle neighbouring tiles.
     *
     * This function merges two horizotal neighbouring tiles. It takes all segments
     * which touching the workingBoundaries, and reprocess them from pixel level.
     * Then segments whichs do not touch any non-processed tiling boundary will
     * be save to final segmentation. Others will save into a proper temperary
     * file, see method saveTodisk3().
     */


    if( workingBoundaries.size() == 0 ) { // for the first block
        qDebug() << "Working boundaries not set." ;
        return;
    }



    std::vector<Node *> selectedBoarderNodes;
    selectedBoarderNodes.clear();
    std::string fileName1 = "i" + std::to_string( blockPosition1[0] ) + "j" + std::to_string(blockPosition1[1]);
    std::string fileName2 = "i" + std::to_string( blockPosition2[0] ) + "j" + std::to_string(blockPosition2[1]);
    std::string fileName3 = "j" + std::to_string(blockPosition1[1]);
    std::string fileName4 = "j" + std::to_string(blockPosition2[1]);

    this->selectBoarderSegments( &selectedBoarderNodes,  workingBoundaries, fileName1.c_str());
    this->selectBoarderSegments( &selectedBoarderNodes,  workingBoundaries, fileName2.c_str());
    this->selectBoarderSegments( &selectedBoarderNodes,  workingBoundaries, fileName3.c_str());
    this->selectBoarderSegments( &selectedBoarderNodes,  workingBoundaries, fileName4.c_str());

    if( selectedBoarderNodes.size() ==0 ) {
        qDebug() << "There is something wrong in selectBoarderNodes.";
        //exit(1);
        return;
    }

    RAG ragBoarder;
    initializer::initializeRag( ragBoarder, selectedBoarderNodes);

    Node *root;
    root = ragBoarder.regionMerging();

 //   double cost=0;
  //  std::vector<Node *> boarderSegmentationNodes;
  //  boarderSegmentationNodes.clear();
 //   this->bestSegmentation(root,boarderSegmentationNodes, cost);

    #pragma omp critical
    {
   // saveToDisk(boarderSegmentationNodes, workingBoundaries);
    }



    std::vector<Node*> selectedSegmentationNodes;
    selectedSegmentationNodes.push_back(root);
    for(int i=0; i < this->lamda.size(); i++){
        std::vector<Node*> tempSelected;
        for(int j=0; j < selectedSegmentationNodes.size(); j++){
            double cost;
            std::vector<Node*> temp;
            io::bestSegmentation(selectedSegmentationNodes[j], temp, cost, this->lamda[i], this->useStdCut);
            tempSelected.insert( tempSelected.begin(), temp.begin(), temp.end());
        }
        selectedSegmentationNodes.clear();
        selectedSegmentationNodes = tempSelected;
        tempSelected.clear();

#pragma omp critical
        {
            saveToDisk(selectedSegmentationNodes, workingBoundaries, i);
        }
    }


    root->releaseTree();


}







void image::selectBoarderSegments( std::vector<Node *> *selected,  const std::vector< WorkingBoundary > & workingBoundaries, std::string boarderFileName)
{ //workingBoundaries 's element looks like [ row/col, rowNumber/colNUmber, min, max], i.e, [0, 1000,2000, 4000] 0 represent row

    ifstream fin;
    fin.open(boarderFileName.c_str(), ios::in);
    if (fin.fail()){
        qDebug() << "There may have some problems in selectBoarderSegments !";
        fin.clear( );
        return;
    }

    std::string fileNameOut = boarderFileName + "temp.csv";
    ofstream fout;

    fout.open( fileNameOut.c_str(),  ios::app );



    std::vector<size_t> positionXSet;
    std::vector<size_t> positionYSet;
    std::vector<int> labelSet;
    std::vector<size_t> boarderIndexXSet;
    std::vector<size_t> boarderIndexYSet;
    std::vector<std::vector<float> > spectrumSet;
    std::vector<std::vector<double> > probabilitiesSet;


    int segmentSeperator = -1;
    bool ifSelect = false;
    std::vector<long int> minX(workingBoundaries.size());
    std::vector<long int> maxX(workingBoundaries.size());
    std::vector<long int> minY(workingBoundaries.size());
    std::vector<long int> maxY(workingBoundaries.size());
    for( int i=0; i < workingBoundaries.size(); i++) {

        minX[i] = LONG_MAX;
        minY[i] = LONG_MAX;
        maxX[i] = LONG_MIN;
        maxY[i] = LONG_MIN;
    }
    std::string line;
    while ( std::getline( fin, line ) ){

        std::istringstream data( line );

        long positionX;
        long positionY;
        int label;
        size_t boarderIndexX;
        size_t boarderIndexY;
        std::vector<float> spectrum;
        std::vector<double>probabilities;



        // read position and label
        data >> positionX >> positionY >> label >> boarderIndexX >> boarderIndexY;

        // read spectrum info
        for(int i=0; i< this->nBands; i++)
        {
            double tempValue;
            data >> tempValue;
            spectrum.push_back( tempValue );
        }

        if( this->ifAddProbabilityModel){
            //read probability info
            for(int i=0; i< this->nClasses; i++)
            {
                double tempValue;
                data >> tempValue;
                probabilities.push_back( tempValue );
            }
        }


        if( segmentSeperator == label) { // current pixel is from the same segment as the previous one

            positionXSet.push_back( positionX );
            positionYSet.push_back( positionY );
            labelSet.push_back( label );
            boarderIndexXSet.push_back( boarderIndexX );
            boarderIndexYSet.push_back( boarderIndexY );
            spectrumSet.push_back( spectrum );
            probabilitiesSet.push_back( probabilities );
            //tempLines.push_back( line );

            // To decide if select current segments
            if( !ifSelect ) {  //if have not been marked as selected, check if to select
                for( int i=0; i < workingBoundaries.size(); i++) {


                    if( workingBoundaries[i].direction == 0 ) { // x direction (horizontal tiling boundary)
                        if( workingBoundaries[i].index == positionY ){
                            if( positionX >= workingBoundaries[i].min && positionX <= workingBoundaries[i].max ) ifSelect = true;
                        }
                    } else {
                        if( workingBoundaries[i].index == positionX ){
                            if( positionY >= workingBoundaries[i].min && positionY <= workingBoundaries[i].max ) ifSelect = true;
                        }
                    }

                }
            }


        } else { // current pixel is from a different segment as the previos one

             if( ifSelect ) { // the previous segments selected
                 //create node for these pixel (add model as well
                 for(size_t k=0; k < positionXSet.size(); k++) {
                     Node *tempNode = new Node();
                     tempNode->setPosition( Point( positionXSet[k], positionYSet[k] ));
                     //remove boarder information
                     if( boarderIndexXSet[k] != 0) {
                         for( int l=0; l < workingBoundaries.size(); l++) {
                                 if( workingBoundaries[l].direction == 1 ){
                                     if( workingBoundaries[l].index == boarderIndexXSet[k] ){
                                         if( positionYSet[k] >= workingBoundaries[l].min && positionYSet[k] <= workingBoundaries[l].max ){
                                             boarderIndexXSet[k] = 0;
                                         }
                                     }
                                 }

                         }
                         if( boarderIndexXSet[k] != 0) tempNode->setBoarderIndexX( boarderIndexXSet[k] );

                     }

                     if( boarderIndexYSet[k] != 0){
                         for( int l=0; l < workingBoundaries.size(); l++) {
                                 if( workingBoundaries[l].direction == 0 ){
                                     if( workingBoundaries[l].index == boarderIndexYSet[k] ) {
                                         if( positionXSet[k] >= workingBoundaries[l].min && positionXSet[k] <= workingBoundaries[l].max ) {
                                             boarderIndexYSet[k] = 0;
                                         }
                                     }
                                 }

                         }
                         if( boarderIndexYSet[k] != 0 ) tempNode->setBoarderIndexY( boarderIndexYSet[k] );
                     }

                     tempNode->ifLeaf = true;
                     histogramModel * histogramModelTemp = new histogramModel( spectrumSet[k], this->nbins,  this->orderMin,  this->orderMax);

                     if(this->ifAddProbabilityModel) {
                         probabilityModel *probabilityModelTemp = new probabilityModel( probabilitiesSet[k] );

                         compoundModel * compoundModelTemp = new compoundModel( histogramModelTemp, probabilityModelTemp );
                         tempNode->setModel( compoundModelTemp );
                     } else {
                         compoundModel * compoundModelTemp = new compoundModel( histogramModelTemp);
                         tempNode->setModel( compoundModelTemp );

                     }


                     selected->push_back( tempNode );
                 }

             } else { // not selected, write them back to disk
                 for(size_t k=0; k<positionXSet.size(); k++){

                     fout << positionXSet[k] << "   " << positionYSet[k] << "   " << labelSet[k] << "   " << boarderIndexXSet[k] << "   " << boarderIndexYSet[k] << "   ";
                     // write spectrum info
                     for(size_t l=0; l< spectrumSet[k].size(); l++)
                     {
                         fout << spectrumSet[k][l] << " ";

                     }

                     if( this->ifAddProbabilityModel){
                         //write probability info
                         for(size_t l=0; l< probabilitiesSet[k].size(); l++)
                         {
                             fout << probabilitiesSet[k][l] << "    ";
                         }
                     }

                     fout << "\n" ;
                 }
             }


             //re-initial status for next segment
             positionXSet.clear();
             positionYSet.clear();
             labelSet.clear();
             boarderIndexXSet.clear();
             boarderIndexYSet.clear();
             spectrumSet.clear();
             probabilitiesSet.clear();
             //tempLines.clear();
             ifSelect = false;
             segmentSeperator = label;

             //save the information of current pixel
             positionXSet.push_back( positionX );
             positionYSet.push_back( positionY );
             labelSet.push_back( label );
             boarderIndexXSet.push_back( boarderIndexX );
             boarderIndexYSet.push_back( boarderIndexY );
             spectrumSet.push_back( spectrum );
             probabilitiesSet.push_back( probabilities );
             //tempLines.push_back( line );
             // To decide if select current segments
             if( !ifSelect ) {  //if have not been marked as selected, check if to select
                 for( int i=0; i < workingBoundaries.size(); i++) {


                     if( workingBoundaries[i].direction == 0 ) { // x direction (horizontal tiling boundary)
                         if( workingBoundaries[i].index == positionY ){
                             if( positionX >= workingBoundaries[i].min && positionX <= workingBoundaries[i].max ) ifSelect = true;
                         }
                     } else {
                         if( workingBoundaries[i].index == positionX ){
                             if( positionY >= workingBoundaries[i].min && positionY <= workingBoundaries[i].max ) ifSelect = true;
                         }
                     }
                 }
             }

        }

    }


    if( positionXSet.size() != 0 ) { // process the last segment

        if( ifSelect ) { //
            //create node for these pixel (add model as well
            for(size_t k=0; k < positionXSet.size(); k++) {
                Node *tempNode = new Node();
                tempNode->setPosition( Point( positionXSet[k], positionYSet[k] ));
                //remove boarder information
                if( boarderIndexXSet[k] != 0) {
                    for( int l=0; l < workingBoundaries.size(); l++) {
                            if( workingBoundaries[l].direction == 1 ){
                                if( workingBoundaries[l].index == boarderIndexXSet[k] ){
                                    if( positionYSet[k] >= workingBoundaries[l].min && positionYSet[k] <= workingBoundaries[l].max ){
                                        boarderIndexXSet[k] = 0;
                                    }
                                }
                            }

                    }
                    if( boarderIndexXSet[k] != 0) tempNode->setBoarderIndexX( boarderIndexXSet[k] );

                }

                if( boarderIndexYSet[k] != 0){
                    for( int l=0; l < workingBoundaries.size(); l++) {
                            if( workingBoundaries[l].direction == 0 ){
                                if( workingBoundaries[l].index == boarderIndexYSet[k] ) {
                                    if( positionXSet[k] >= workingBoundaries[l].min && positionXSet[k] <= workingBoundaries[l].max ) {
                                        boarderIndexYSet[k] = 0;
                                    }
                                }
                            }

                    }
                    if( boarderIndexYSet[k] != 0 ) tempNode->setBoarderIndexY( boarderIndexYSet[k] );
                }

                tempNode->ifLeaf = true;
                histogramModel * histogramModelTemp = new histogramModel( spectrumSet[k], this->nbins,  this->orderMin,  this->orderMax);

                if(this->ifAddProbabilityModel) {
                    probabilityModel *probabilityModelTemp = new probabilityModel( probabilitiesSet[k] );
                    compoundModel * compoundModelTemp = new compoundModel( histogramModelTemp, probabilityModelTemp );
                    tempNode->setModel( compoundModelTemp );
                } else {
                    compoundModel * compoundModelTemp = new compoundModel( histogramModelTemp);
                    tempNode->setModel( compoundModelTemp );

                }


                selected->push_back( tempNode );
            }

        } else { // not selected, write them back to disk
            for(size_t k=0; k<positionXSet.size(); k++){

                fout << positionXSet[k] << "   " << positionYSet[k] << "   " << labelSet[k] << "   " << boarderIndexXSet[k] << "   " << boarderIndexYSet[k] << "   ";
                // write spectrum info
                for(size_t l=0; l< spectrumSet[k].size(); l++)
                {
                    fout << spectrumSet[k][l] << " ";

                }

                if( this->ifAddProbabilityModel){
                    //write probability info
                    for(size_t l=0; l< probabilitiesSet[k].size(); l++)
                    {
                        fout << probabilitiesSet[k][l] << "    ";
                    }
                }

                fout << "\n" ;
            }
        }

    }

    fin.close();
    fout.close();
    remove(boarderFileName.c_str());
    rename(fileNameOut.c_str(), boarderFileName.c_str() );

    return;

}







void image::saveToDisk(const std::vector< Node *> &selectedSegmentationNodes, int row, int level)
{ //write the regions in the segmentation which are not boarder regions anymore
    //to the disk


    string fileNameSegmentation = this->directoryOutput + "/segmentation" + std::to_string(level) + ".tif";
    string fileNameSegmentationCSV = this->directoryOutput + "/segmentation" + std::to_string(level) + ".csv";
    GDALDataset * classDataset;
    if( this->ifAddProbabilityModel ){
        string fileNameClassMap = this->directoryOutput + "/classMap" + std::to_string(level) + ".tif";
        GDALAllRegister();
        classDataset =  (GDALDataset *) GDALOpen( fileNameClassMap.c_str(), GA_Update);
        if( classDataset == NULL )
        {
            std::cout<< "class map file open failed" <<endl;
            exit(1);
        }

    }

    GDALDataset * poDataset;
    GDALAllRegister();
    poDataset =  (GDALDataset *) GDALOpen(fileNameSegmentation.c_str(), GA_Update );
    if( poDataset == NULL )
    {
        std::cout<< "Segmentation file open failed" <<endl;
        exit(1);
    }

    ofstream fout;
    fout.open(fileNameSegmentationCSV.c_str(), ios::app);



    ofstream fout_Boarder1;
    //int row;
    std::string boraderFileName = "j" + to_string(row); // should pass blockPosition
    fout_Boarder1.open((boraderFileName).c_str(), ios::app);


    for(size_t i=0; i< selectedSegmentationNodes.size(); i++) {

        if(selectedSegmentationNodes[i]->getBoarderIndexX().size() == 0
                && selectedSegmentationNodes[i]->getBoarderIndexY().size() == 0) {// if not boarders anymore
            int *color = new int[3];
            for(int j=0; j <3 ; j++){
                if(this->ifPaintRandomColor) {
                    color[j] = std::rand()%255;
                }else{
                    //color[j] = ((int) nodeSet[i]->getMeanSpectrumAt(2-j))%255;
                    color[j] = selectedSegmentationNodes[i]->getMeanSpectrumAt(j);
                }
            }
            io::writeNodeToDisk(selectedSegmentationNodes[i], color, poDataset, this->startPointX, this->startPointY );
            io::writeNodeToCSV(selectedSegmentationNodes[i], rand()%135797531, fout);
            if( this->ifAddProbabilityModel ){
                io::writeClassMap( selectedSegmentationNodes[i], selectedSegmentationNodes[i]->getClassLabel() , classDataset, this->startPointX, this->startPointY );
            }


            delete[] color;
        } else {

            // save too big segments to disk
            if( selectedSegmentationNodes[i]->getArea() > 3000000 ) {
                int *color = new int[3];
                for(int j=0; j <3 ; j++){
                    if(this->ifPaintRandomColor) {
                        color[j] = std::rand()%255;
                    }else{
                        //color[j] = ((int) nodeSet[i]->getMeanSpectrumAt(2-j))%255;
                        color[j] = selectedSegmentationNodes[i]->getMeanSpectrumAt(j);
                    }
                }
                io::writeNodeToDisk(selectedSegmentationNodes[i], color, poDataset, this->startPointX, this->startPointY );
                io::writeNodeToCSV(selectedSegmentationNodes[i], rand()%135797531, fout);
                if( this->ifAddProbabilityModel ){
                    io::writeClassMap( selectedSegmentationNodes[i], selectedSegmentationNodes[i]->getClassLabel() , classDataset, this->startPointX, this->startPointY );
                }
                delete[] color;

            } else if( level ==0 ){

                std::vector<int> borderIndexX = selectedSegmentationNodes[i]->getBoarderIndexX();
                std::vector<int> borderIndexY = selectedSegmentationNodes[i]->getBoarderIndexY();



                // if borderIndexX.size == 1 save to the coressponding block
                // if borderIndexX.size == 2, save to the block which has priority
                // if borderIndexX.size == 0, save to correspoding row.

                if( borderIndexX.size() ==0 ) {
                    int label = std::rand()%135797531;
                    io::writeBoarderNodeToCSV( selectedSegmentationNodes[i] , label, fout_Boarder1, this->ifAddProbabilityModel);
                    qDebug() << "Save to j0" << endl;
                } else if( borderIndexX.size() == 1) {
                    int Index = borderIndexX[0];
                    int blockIndexX;
                    for(int indx = 0; indx < this->nBlocksX; indx ++){
                        if( this->blocksStartPointX[indx] == Index){
                            blockIndexX = indx;
                            break;
                        }
                        if( this->blocksStartPointX[indx] + this->blockSizeW[indx]-1 == Index){
                            blockIndexX = indx;
                            break;
                        }

                    }

                    qDebug() <<"Save to block" << " " << blockIndexX << endl;
                    if(blockIndexX == -1) qDebug() << "Bug found" << endl;

                    int label = std::rand()%135797531;
                    ofstream fout_Boarder;
                    std::string tempBoraderFileName = "i"+ to_string(blockIndexX)+ "j" + to_string(row); // should pass blockPosition
                    fout_Boarder.open((tempBoraderFileName).c_str(), ios::app);
                    io::writeBoarderNodeToCSV( selectedSegmentationNodes[i] , label, fout_Boarder, this->ifAddProbabilityModel);
                    fout_Boarder.close();
                } else {
                    int indexX1 = borderIndexX[0];
                    int indexX2 = borderIndexX[1]; // indexX2 > indexX1 this is important
                    if( indexX1 == indexX2) qDebug() << "There is one bug in save funtion" << endl;


                    int blockIndexX1; // = find( indexX1)
                    int blockIndexX2; // = find (indexX2)
                    for(int indx = 0; indx < this->nBlocksX; indx ++){
                        if( this->blocksStartPointX[indx] == indexX1){
                            blockIndexX1 = indx;
                            break;
                        }
                        if( this->blocksStartPointX[indx] + this->blockSizeW[indx]-1 == indexX1){
                            blockIndexX1 = indx;
                            break;
                        }

                    }
                    for(int indx = 0; indx < this->nBlocksX; indx ++){
                        if( this->blocksStartPointX[indx] == indexX2){
                            blockIndexX2 = indx;
                            break;
                        }
                        if( this->blocksStartPointX[indx] + this->blockSizeW[indx]-1 == indexX2){
                            blockIndexX2 = indx;
                            break;
                        }

                    }



                    int label = std::rand()%135797531;
                    //decide which block to save
                    int selected = -1;
                    int circle = 1;


                    while( selected == -1 ) {
                        if( ((blockIndexX1 - (int)pow(2, circle))%((int)pow(2, circle+1))) == 0 ){
                            selected = blockIndexX1;
                        }
                        /*
                       if( (blockIndexX1+1 - (int)pow(2, circle))%(int)pow(2, circle+1) == 0 ){
                           selected = blockIndexX1;
                       }


                       if( (blockIndexX2 - (int)pow(2, circle))%(int)pow(2, circle+1) == 0 ){
                           selected = blockIndexX2;
                       }
                       */

                        if( (blockIndexX2+1 - (int)pow(2, circle))%(int)pow(2, circle+1) == 0 ){
                            selected = blockIndexX2;
                        }

                        circle++;
                    }


                    qDebug() << "A segment which has tow borders to block" << blockIndexX1 << "   " << blockIndexX2 << "saved to block     "<<selected << endl;

                    ofstream fout_Boarder;
                    //int row;
                    std::string tempBoraderFileName = "i"+ to_string(selected)+"j" + to_string(row); // should pass blockPosition
                    fout_Boarder.open((tempBoraderFileName).c_str(), ios::app);
                    io::writeBoarderNodeToCSV( selectedSegmentationNodes[i] , label, fout_Boarder, this->ifAddProbabilityModel);
                    fout_Boarder.close();



                }

            }


        }

    }

    delete poDataset;
    if( this->ifAddProbabilityModel ) delete classDataset;
    fout.close();
    fout_Boarder1.close();

}




void image::saveToDisk(const std::vector< Node *> &selectedSegmentationNodes, const std::vector< WorkingBoundary > &workingBoundaries, int level)
{ //write the regions in the segmentation which are not boarder regions anymore
  //to the disk


    string fileNameSegmentation = this->directoryOutput + "/segmentation" + std::to_string(level) + ".tif";
    string fileNameSegmentationCSV = this->directoryOutput + "/segmentation" + std::to_string(level) + ".csv";

    GDALDataset * classDataset;
    if( this->ifAddProbabilityModel ){
        string fileNameClassMap = this->directoryOutput + "/classMap" + std::to_string(level) + ".tif";
        GDALAllRegister();
        classDataset =  (GDALDataset *) GDALOpen( fileNameClassMap.c_str(), GA_Update);
        if( classDataset == NULL )
        {
            std::cout<< "class map file open failed" <<endl;
            exit(1);
        }

    }

   GDALDataset * poDataset;
   GDALAllRegister();
   poDataset =  (GDALDataset *) GDALOpen(fileNameSegmentation.c_str(), GA_Update );
   if( poDataset == NULL )
   {
       std::cout<< "Segmentation file open failed" <<endl;
       exit(1);
   }

   ofstream fout;
   fout.open(fileNameSegmentationCSV.c_str(), ios::app);


   for(size_t i=0; i< selectedSegmentationNodes.size(); i++) {
       if(selectedSegmentationNodes[i]->getBoarderIndexX().size() == 0
               && selectedSegmentationNodes[i]->getBoarderIndexY().size() == 0) {// if not boarders anymore
           int *color = new int[3];
           for(int j=0; j <3 ; j++){
               if(this->ifPaintRandomColor) {
                   color[j] = std::rand()%255;
               }else{
               //color[j] = ((int) nodeSet[i]->getMeanSpectrumAt(2-j))%255;
               color[j] = selectedSegmentationNodes[i]->getMeanSpectrumAt(j);
               }
           }
           io::writeNodeToDisk(selectedSegmentationNodes[i], color, poDataset, this->startPointX, this->startPointY );
           io::writeNodeToCSV(selectedSegmentationNodes[i], rand()%135797531, fout);
           if( this->ifAddProbabilityModel ){
               io::writeClassMap( selectedSegmentationNodes[i], selectedSegmentationNodes[i]->getClassLabel() , classDataset, this->startPointX, this->startPointY );
           }

           delete[] color;
       } else {

           // save too big segments to disk
           if( selectedSegmentationNodes[i]->getArea() > 3000000 ) {

               int *color = new int[3];
               for(int j=0; j <3 ; j++){
                   if(this->ifPaintRandomColor) {
                       color[j] = std::rand()%255;
                   }else{
                   //color[j] = ((int) nodeSet[i]->getMeanSpectrumAt(2-j))%255;
                   color[j] = selectedSegmentationNodes[i]->getMeanSpectrumAt(j);
                   }
               }
               io::writeNodeToDisk(selectedSegmentationNodes[i], color, poDataset, this->startPointX, this->startPointY );
               io::writeNodeToCSV(selectedSegmentationNodes[i], rand()%135797531, fout);
               if( this->ifAddProbabilityModel ){
                   io::writeClassMap( selectedSegmentationNodes[i], selectedSegmentationNodes[i]->getClassLabel() , classDataset, this->startPointX, this->startPointY );
               }

               delete[] color;

           } else if( level == 0){

           //save to the disk

               //std::vector<int> borderIndexX = selectedSegmentationNodes[i]->getBoarderIndexX();
               std::vector<int> borderIndexY = selectedSegmentationNodes[i]->getBoarderIndexY();

               // if the segment still is the border segments of the current working boundaries, then save back
               // other wise
               //          if borderIndexY.size() == 1 save to the croeesponding rows
               //          if borderIndexY.size() == 2, find the place where to save, and save
               bool ifSaveBack = false;
               int  indexToSave;
               for( int borderIndex=0; borderIndex < borderIndexY.size(); borderIndex++){
                   for( int workingBoundaryIndex=0; workingBoundaryIndex < workingBoundaries.size(); workingBoundaryIndex++ ){
                       if( workingBoundaries[workingBoundaryIndex].direction == 0 && workingBoundaries[workingBoundaryIndex].index == borderIndexY[borderIndex]){
                           ifSaveBack = true;
                           indexToSave = borderIndexY[borderIndex];
                           break;
                       }

                   }
               }

               if( ifSaveBack ){

                   int Index = indexToSave;
                   int blockIndexY;
                   for(int indx = 0; indx < this->nBlocksY; indx ++){
                       if( this->blocksStartPointY[indx] == Index){
                           blockIndexY = indx;
                           break;
                       }
                       if( this->blocksStartPointY[indx] + this->blockSizeH[indx]-1 == Index){
                           blockIndexY = indx;
                           break;
                       }
                   }

                   int label = std::rand()%135797531;
                   ofstream fout_Boarder;
                   std::string tempBoraderFileName = "j"+ to_string(blockIndexY); // should pass blockPosition
                   fout_Boarder.open((tempBoraderFileName).c_str(), ios::app);
                   io::writeBoarderNodeToCSV( selectedSegmentationNodes[i] , label, fout_Boarder, this->ifAddProbabilityModel);
                   fout_Boarder.close();



               }else{


               if( borderIndexY.size() == 1) {
                   int Index = borderIndexY[0];
                   int blockIndexY;
                   for(int indx = 0; indx < this->nBlocksY; indx ++){
                       if( this->blocksStartPointY[indx] == Index){
                           blockIndexY = indx;
                           break;
                       }
                       if( this->blocksStartPointY[indx] + this->blockSizeH[indx]-1 == Index){
                           blockIndexY = indx;
                           break;
                       }

                   }

                   qDebug() <<"Save to block" << " " << blockIndexY << endl;


                   int label = std::rand()%135797531;
                   ofstream fout_Boarder;
                   std::string tempBoraderFileName = "j"+ to_string(blockIndexY); // should pass blockPosition
                   fout_Boarder.open((tempBoraderFileName).c_str(), ios::app);
                   io::writeBoarderNodeToCSV( selectedSegmentationNodes[i] , label, fout_Boarder, this->ifAddProbabilityModel);
                   fout_Boarder.close();
               } else {

                   int indexY1 = borderIndexY[0];
                   int indexY2 = borderIndexY[1]; // indexX2 > indexX1 this is important
                   if( indexY1 == indexY2) qDebug() << "There is one bug in save funtion" << endl;


                   int blockIndexY1; // = find( indexX1)
                   int blockIndexY2; // = find (indexX2)
                   for(int indx = 0; indx < this->nBlocksY; indx ++){
                       if( this->blocksStartPointY[indx] == indexY1){
                           blockIndexY1 = indx;
                           break;
                       }
                       if( this->blocksStartPointY[indx] + this->blockSizeH[indx]-1 == indexY1){
                           blockIndexY1 = indx;
                           break;
                       }

                   }
                   for(int indx = 0; indx < this->nBlocksY; indx ++){
                       if( this->blocksStartPointY[indx] == indexY2){
                           blockIndexY2 = indx;
                           break;
                       }
                       if( this->blocksStartPointY[indx] + this->blockSizeH[indx]-1 == indexY2){
                           blockIndexY2 = indx;
                           break;
                       }

                   }



                   int label = std::rand()%135797531;
                   //decide which block to save
                   int selected = -1;
                   int circle = 1;


                     while( selected == -1 ) {

                       if( ((blockIndexY1 - (int)pow(2, circle))%((int)pow(2, circle+1))) == 0 ){
                           selected = blockIndexY1;
                       }
                       /*
                       if( (blockIndexX1+1 - (int)pow(2, circle))%(int)pow(2, circle+1) == 0 ){
                           selected = blockIndexX1;
                       }


                       if( (blockIndexX2 - (int)pow(2, circle))%(int)pow(2, circle+1) == 0 ){
                           selected = blockIndexX2;
                       }
                       */

                       if( (blockIndexY2 + 1 - (int)pow(2, circle))%(int)pow(2, circle+1) == 0 ){
                           selected = blockIndexY2;
                       }

                       circle++;
                       if(circle >10) break;

                     }


                   qDebug() << "A segment which has tow borders to block" << blockIndexY1 << "   " << blockIndexY2 << "saved to block     "<<selected << endl;

                   ofstream fout_Boarder;
                   //int row;
                   std::string tempBoraderFileName = "j"+ to_string(selected);
                   fout_Boarder.open((tempBoraderFileName).c_str(), ios::app);
                   io::writeBoarderNodeToCSV( selectedSegmentationNodes[i] , label, fout_Boarder, this->ifAddProbabilityModel);
                   fout_Boarder.close();





               }
               }


           }



       }

   }

   delete poDataset;
   if( this->ifAddProbabilityModel ) delete classDataset;
   fout.close();

}








void image::setGlobalSettings(int imageWidth, int imageHeight,
                              int startPointX, int startPointY,
                              int nBlocksX, int nBlocksY,
                              bool ifDeleteNoise, double nStdLeft, double nStdRight,
                              bool ifUseMinimumToMerge, int floor,
                              int nbins,
                              bool areaWeighted, double areaExponent,
                              bool useStdCut,
                              bool ifAddProbabilityModel, double probabilityModelWeight,
                              int nClasses, std::vector<double> lamda,
                              bool ifPaintRandomColor)
{


    this->linkFile();

    this->ifDeleteNoise = ifDeleteNoise;
    if( ifDeleteNoise ) {
        this->nStdLeft = nStdLeft;
        this->nStdRight = nStdRight;
    }

    this->ifPaintRandomColor = ifPaintRandomColor;
    this->ifUseMinimumToMerge = ifUseMinimumToMerge;
    this->floor = floor;
    this->useStdCut = useStdCut;

    this->ifAddProbabilityModel = ifAddProbabilityModel;
    this->probabilityModelWeight = probabilityModelWeight;
    this->nClasses = nClasses;


    //Set raster image information
    this->rasterWidth = this->data->GetRasterXSize();
    this->rasterHeight = this->data->GetRasterYSize();
    this->rasterBandCount = this->data->GetRasterCount();

    //Check if the image settings out of range, if yes, re set the width and height
    if( imageWidth+startPointX > this->data->GetRasterXSize()) {
        QMessageBox::warning(NULL, "Warming!",  "Image width out of range! ");
        imageWidth = this->data->GetRasterXSize() - startPointX;
    }

    if(imageHeight+startPointY > this->data->GetRasterYSize()) {
        QMessageBox::warning(NULL, "Warming!",  "Image height out of range! ");
        imageHeight = this->data->GetRasterXSize() - startPointY;
    }

    // If the image width is 0, set the imageWidth to be to the size start from startPointX,
    // do the same to imageHeight
    this->imageWidth = imageWidth;
    this->imageHeight = imageHeight;
    if(imageWidth == 0)   this->imageWidth = this->data->GetRasterXSize() - startPointX ;
    if(imageHeight == 0)  this->imageHeight = this->data->GetRasterYSize() - startPointY;


    this->nBands = this->data->GetRasterCount();
    this->nBlocksX = nBlocksX;
    this->nBlocksY = nBlocksY;
    this->startPointX = startPointX;
    this->startPointY = startPointY;

    this->areaWeighted = areaWeighted;
    this->areaExponent = areaExponent;
    this->floor = floor;
    this->lamda = lamda;
    this->nbins = nbins;


    this->blockSizeCalculator_evenSplite();
    this->blockStartPointCalculator_evenSplite();



    // set the file names where to store the segmentation
    if( ! this->directoryOutput.empty() ){
        this->fileNameSegmentation = this->directoryOutput + "/segmentation.tif";
        this->logFileName = this->directoryOutput + "/logFile";
        this->fileNameSegmentationCSV = this->directoryOutput + "/segmentation.csv";
    } else {
        this->fileNameSegmentation = "segmentation.tif";
        this->logFileName = "logFile";
        this->fileNameSegmentationCSV = "segmentation.csv";
    }

    for( int i=0; i < this->lamda.size(); i++){
        std::string fileNameSegmentation = this->directoryOutput + "/segmentation" + std::to_string(i) + ".tif";
        std::string fileNameSegmentationCSV = this->directoryOutput + "/segmentation" + std::to_string(i) + ".csv";
        this->createEmptyImage(fileNameSegmentation);
        this->createEmptyCSV(fileNameSegmentationCSV );
        if( this->ifAddProbabilityModel ){
            std::string fileNameClassMap = this->directoryOutput + "/classMap" + std::to_string(i) + ".tif";
            //io::createEmptyImage( fileNameClassMap, this->imageWidth, this->imageHeight, 3);
            this->createEmptyImage(fileNameClassMap);

        }
    }

    this->SetStatistics();




    compoundModel::areaWeighted = this->areaWeighted;
    compoundModel::areaExponent = this->areaExponent;
    compoundModel::floor = this->floor;
    compoundModel::ifUseMinimumToMerge = this->ifUseMinimumToMerge;
    compoundModel::probabilityModelWeight = this->probabilityModelWeight;


    //Set preprocessing information


    std::cout<<"Parameters have been set successfully." <<std::endl;
    return;
}









void image::print_ImageInfo()
{// print out some basic information about the image which we are going to process

    //print image format
    switch (this->imageFormat) {
    case U8I : std::cout << "Processing eight bit unsigned integer image "<<endl;
            break;
    case U16I :std::cout << "Processing sixteen bit unsigned integer image" << endl;
            break;
    case S16I :std::cout << "Processing sixteen bit signed integer image" <<endl;
            break;
    case U32I :std::cout << "Processing thirty two bit unsigned inter image" <<endl;
            break;
    case S32I : std::cout << "Processing thirty two bit signed inter image" <<endl;
            break;
    case F32 :std::cout << "Processing thirty two bit floating point image" <<endl;
            break;
    case F64 :std::cout << "Processing sixty four bit floating point image" <<endl;
            break;
    default: exit(1);
    }
    // print image size
    std::cout<<"Image size :  " << this->imageWidth << " * "<< this->imageHeight << endl
        <<"Number of bands : " << this->nBands << endl;



    return;
}



void image::blockSizeCalculator_evenSplite()
{  // this function evenly splite the image

    blockSizeW.clear();
    blockSizeH.clear();

    int eachSizeX = imageWidth/nBlocksX;
    int eachSizeY = imageHeight/nBlocksY;

    for(int i= 0;i< nBlocksX-1; i++ )
        blockSizeW.push_back(eachSizeX);
    blockSizeW.push_back(imageWidth - eachSizeX*(nBlocksX-1));

    for(int j=0; j<nBlocksY-1; j++)
        blockSizeH.push_back(eachSizeY);
    blockSizeH.push_back(imageHeight- eachSizeY*(nBlocksY-1));

    return;
}



void image::blockStartPointCalculator_evenSplite()
{

    blocksStartPointX.clear();
    blocksStartPointY.clear();

    blocksStartPointX.push_back(startPointX);
    blocksStartPointY.push_back(startPointY);

    for(int i= 1; i < nBlocksX; i++)
        blocksStartPointX.push_back(blocksStartPointX[i-1] + blockSizeW[i-1]);

    for(int j=1; j < nBlocksY; j++)
        blocksStartPointY.push_back(blocksStartPointY[j-1]+ blockSizeH[j-1]);

    return;
}


/*
void this->createEmptyImage(std::string fileName){
    Mat segmentation = Mat::zeros(imageHeight,imageWidth, CV_8UC3);
    //imwrite("segmentationAll.tif",segmentation);
    imwrite(fileName,segmentation);
}
*/

void image::createEmptyImage(std::string fileName)
{
    /**
     * @brief Create a empty tif image
     * @param fileName The full path of the empty image
     * This method uses GDAL to create a "GTiff" empty image.
     */


    GDALAllRegister();
   // GDALRegister_GTiff();
    const char *pszFormat = "GTiff";
    GDALDriver *poDriver = GetGDALDriverManager()->GetDriverByName( pszFormat );
    //GDALRegisterDriver( poDriver);
   // char **papszMetadata = poDriver->GetMetadata();
    // set some options http://www.gdal.org/frmt_gtiff.html
    char **papszOptions = NULL;
    //papszOptions = CSLSetNameValue( papszOptions, "TFW", "NO" );
    papszOptions = CSLSetNameValue( papszOptions, "TILED", "NO" );
    //const char *options = GDALGetDriverCreationOptionList(poDriver);
    papszOptions = CSLSetNameValue( papszOptions,"BIGTIFF", "IF_NEEDED" );

    int nBandCount = 3;
    int width = this->imageWidth;
    int height = this->imageHeight;

    //check if file existed
   // remove( fileName.c_str() );

    GDALDataset *poDataset;
    poDataset= poDriver->Create(fileName.c_str(),width,height,nBandCount,GDT_Byte,papszOptions);

    delete poDataset;
    //delete poDriver;

  // GetGDALDriverManager()->DeregisterDriver( poDriver);
  //  GetGDALDriverManager()->AutoSkipDrivers();

}


void image::createEmptyCSV(std::string fileName)
{
    if (FILE *file = fopen(fileName.c_str(), "r")) {
        fclose(file);
        std::cout<<fileName <<" already exists. Do you want to delete it ?" << endl;
        bool ifDeleteFile = true;
        //cin>>ifDeleteFile; // let the user to choose if to delete it or not
        if(ifDeleteFile) {
            remove(fileName.c_str());
        } else {
            exit(1);
        }
    }


    //create a new file
    ofstream out;
    out.open(fileName.c_str());
    out.close();

return;

}



void image::SetStatistics()
{//Fetch image statistics

    //clean the statistics infor
    this->rasterMin.clear();
    this->rasterMax.clear();
    this->rasterMean.clear();
    this->rasterStdDev.clear();
    this->orderMin.clear();
    this->orderMax.clear();

    for(int i=0; i < this->rasterBandCount; i++) {
        GDALRasterBand * rasterBand = this->data->GetRasterBand(i+1);
        int bApproxOK = 0;
        int bForce = 1;
        double min=0;
        double max=0;
        double mean=0;
        double stdDev=0;
        if(!rasterBand->GetStatistics(bApproxOK, bForce, &min, &max, &mean, &stdDev)){
            //rasterBand->ComputeStatistics( bApproxOK, &min, &max, &mean, &stdDev, NULL, NULL);
        }

        this->rasterMin.push_back(min);
        this->rasterMax.push_back(max);
        this->rasterMean.push_back(mean);
        this->rasterStdDev.push_back(stdDev);
        if(this->ifDeleteNoise) {
            this->orderMin.push_back( this->rasterMean[i] - this->nStdLeft*this->rasterStdDev[i] );
            this->orderMax.push_back( this->rasterMean[i] + this->nStdRight*this->rasterStdDev[i] );
        } else {

            this->orderMin.push_back(min);
            this->orderMax.push_back(max);
        }

    }



    return;

}


