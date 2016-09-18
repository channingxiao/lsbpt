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




#include "io.h"



io::io()
{
}



void io::read2Mat(std::vector<Mat> *bands, GDALDataset *poDataset,
                   size_t roiX, size_t roiY, size_t roiW, size_t roiH,
                  bool ifDeleteNoise,
                  std::vector<double> orderMin, std::vector<double> orderMax )
{

    /**
     * @brief Read a part of the image
     *
     * This method read the color information of a tile of a large image, and
     * store it in *bands. The start point and size of the tile are indicated in
     * parameters. It is possible to delete some outliers by setting all values
     * which out of the range, indicated in parameters orderMin and orderMax
     * @param *bands To store the color information, each Mat stores one band
     * @param *poDataset A GDALDataset object indicates where to read the data
     * @param rioX start point of horizontal direction of the current tile
     * @param roiY Start point of verticle direction of the current tile
     * @param roiW The size of the current tile in horizontal direction
     * @param roiH The size of the current tile in verticle direction
     */


    GDALAllRegister();
    if( poDataset == NULL )
    {
        std::cout<< "File open failed" <<endl;
        return;
    }

    int BandCount = poDataset->GetRasterCount();

     switch (poDataset->GetRasterBand(1)->GetRasterDataType()) {
     case GDT_Byte : {
         GByte *buffer= new GByte [roiW*roiH*BandCount];
         poDataset->RasterIO( GF_Read, roiX, roiY,roiW,roiH,
                              buffer,roiW,roiH,GDT_Byte,BandCount,0,0,0,0);

         if(ifDeleteNoise) {
             io::clip<uint8_t>(buffer, orderMin, orderMax,
                                BandCount, roiW*roiH);
         }

         for(int nband =0; nband < BandCount; nband++) {
             Mat img(roiH,roiW, CV_8UC1);  // img is a pointer
             for(size_t row = 0 ; row < roiH; row++){
                 for(size_t col =0; col < roiW; col++){
                     img.at< uint8_t>(row,col) = buffer[nband*roiW*roiH + row*roiW + col];
                 }
             }
             bands->push_back(img);
         }
         delete[] buffer;
     }
         break;
     case GDT_UInt16 : {
         uint16_t  *buffer= new uint16_t [roiW*roiH*BandCount];
         poDataset->RasterIO( GF_Read, roiX, roiY,roiW,roiH,buffer,roiW,roiH,GDT_UInt16,BandCount,0,0,0,0);

         if(ifDeleteNoise) {
             io::clip<uint16_t>(buffer, orderMin, orderMax,
                                BandCount, roiW*roiH);
         }

         //io::clip<uint16_t>(buffer, min, max, BandCount, roiW*roiH);
         for(int nband =0; nband < BandCount; nband++) {
             Mat img(roiH,roiW, CV_16UC1);  // img is a pointer
             for(size_t row = 0 ; row < roiH; row++){
                 for(size_t col =0; col < roiW; col++){
                     img.at< uint16_t>(row,col) = buffer[nband*roiW*roiH + row*roiW + col];
                 }
             }
             bands->push_back(img);
         }
         delete[] buffer;
     }
         break;
     case GDT_Int16 : {
         int16_t  *buffer= new int16_t [roiW*roiH*BandCount];
         poDataset->RasterIO( GF_Read, roiX, roiY,roiW,roiH,
                              buffer,roiW,roiH,GDT_Int16,BandCount,0,0,0,0);
         if(ifDeleteNoise) {
             io::clip<int16_t>(buffer, orderMin, orderMax,
                                BandCount, roiW*roiH);
         }

         for(int nband =0; nband < BandCount; nband++) {
             Mat img(roiH,roiW, CV_16SC1);
             for(size_t row = 0 ; row < roiH; row++){
                 for(size_t col =0; col < roiW; col++){
                     img.at< int16_t>(row,col) = buffer[nband*roiW*roiH + row*roiW + col];
                 }
             }
             bands->push_back(img);
         }
         delete[] buffer;
     }
         break;
     case GDT_Int32 : {
         int32_t  *buffer= new int32_t [roiW*roiH*BandCount];
         poDataset->RasterIO( GF_Read, roiX, roiY,roiW,roiH,
                              buffer,roiW,roiH,GDT_Int32,BandCount,0,0,0,0);

         if(ifDeleteNoise) {
             io::clip<int32_t>(buffer, orderMin, orderMax,
                                BandCount, roiW*roiH);
         }

         for(int nband =0; nband < BandCount; nband++) {
             Mat img(roiH,roiW, CV_32SC1);
             for(size_t row = 0 ; row < roiH; row++){
                 for(size_t col =0; col < roiW; col++){
                     img.at< int32_t>(row,col) = buffer[nband*roiW*roiH + row*roiW + col];
                 }
             }
             bands->push_back(img);
         }
         delete[] buffer;
     }
         break;
     case GDT_Float32 : {
         float  *buffer= new float [roiW*roiH*BandCount];
         poDataset->RasterIO( GF_Read, roiX, roiY,roiW,roiH,
                              buffer,roiW,roiH,GDT_Float32,BandCount,0,0,0,0);
         if(ifDeleteNoise) {
             io::clip<float>(buffer, orderMin, orderMax,
                                BandCount, roiW*roiH);
         }
         for(int nband =0; nband < BandCount; nband++) {
             Mat img(roiH,roiW, CV_32FC1);
             for(size_t row = 0 ; row < roiH; row++){
                 for(size_t col =0; col < roiW; col++){
                     img.at< float >(row,col) = buffer[nband*roiW*roiH + row*roiW + col];
                 }
             }
             bands->push_back(img);
         }
         delete[] buffer;
     }
         break;
     case GDT_Float64 :{
         double  *buffer= new double [roiW*roiH*BandCount];
         poDataset->RasterIO( GF_Read, roiX, roiY,roiW,roiH,
                              buffer,roiW,roiH,GDT_Float64,BandCount,0,0,0,0);
         if(ifDeleteNoise) {
             io::clip<double>(buffer, orderMin, orderMax,
                                BandCount, roiW*roiH);
         }         for(int nband =0; nband < BandCount; nband++) {
             Mat img(roiH,roiW, CV_64FC1);
             for(size_t row = 0 ; row < roiH; row++){
                 for(size_t col =0; col < roiW; col++){
                     img.at< double >(row,col) = buffer[nband*roiW*roiH + row*roiW + col];
                 }
             }
             bands->push_back(img);
         }
         delete[] buffer;
     }
         break;

      /*
     case GDT_UInt32 :{
     // case unsigned 32 bit integer doesn't exit in opencv, we throw an exception
     }
         break;
     case GDT_CInt16 : ; break;
     case GDT_CInt32:; break;
     case GDT_CFloat32 : ;break;
     case GDT_CFloat64 : ;break;
     case GDT_Unknown : ; break;
     */
     default: exit(1);

     }


     return;
}




void io::createEmptyImage(std::string fileName, int width, int height, int nBandCount){

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


    //int nBandCount = 3;
    //int width = globalSettings::imageWidth;
    //int height = globalSettings::imageHeight;

    //check if file existed
   // remove( fileName.c_str() );

    GDALDataset *poDataset;
    poDataset= poDriver->Create(fileName.c_str(),width,height,nBandCount,GDT_Byte,papszOptions);

    delete poDataset;




}







void io::writeNodeToDisk(Node * node, int color[], GDALDataset * poDataset, int globalStartX, int globalStartY)
{// wtire the tree whose root is "*node" to image in the disk which is connected
 // by *poDataset, and do nothing to the tree, all the pxiles of the three are
 //painted with the color[]

    if(node->isLeaf()) {
        GByte abyRaster[3];
        abyRaster[0] = color[0];
        abyRaster[1] = color[1];
        abyRaster[2] = color[2];
    poDataset->RasterIO( GF_Write,
                         node->getPosition().x - globalStartX ,
                         node->getPosition().y - globalStartY ,
                         1, 1, abyRaster,1,1,GDT_Byte,3,0,0,0,0);
    } else {
        if(node->getRightChild() != NULL)
            io::writeNodeToDisk(node->getRightChild(), color, poDataset, globalStartX, globalStartY);
        if(node->getLeftChild() != NULL )
            io::writeNodeToDisk(node->getLeftChild(), color, poDataset, globalStartX, globalStartY);
    }

    return;
}


void io::writeClassMap(Node * node, int classLabel, GDALDataset * poDataset, int globalStartX, int globalStartY)
{// wtire the tree whose root is "*node" to image in the disk which is connected
 // by *poDataset, and do nothing to the tree, all the pxiles of the three are
 //painted with the color[]

    if( node->isLeaf()) {
        GByte abyRaster[3];
        abyRaster[0] = classLabel*20 + 10;
        abyRaster[1] = classLabel*20 + 10;
        abyRaster[2] = classLabel*20 + 10;

    poDataset->RasterIO( GF_Write,
                         node->getPosition().x - globalStartX ,
                         node->getPosition().y - globalStartY ,
                         1, 1, abyRaster,1,1,GDT_Byte,3,0,0,0,0);

    } else {
        if(node->getRightChild() != NULL)
            io::writeClassMap(node->getRightChild(), classLabel, poDataset, globalStartX, globalStartY);
        if(node->getLeftChild() != NULL )
            io::writeClassMap(node->getLeftChild(), classLabel, poDataset, globalStartX, globalStartY);
    }

    return;
}






void io::writeNodeToCSV(Node * node, int label, ofstream &fout)
{//write all the leaf of a subtree whoes root is given by node to csv tab space
 // separated file. the data each line is written as:
 // x  y  label

    if(!fout) {
        std::cout <<"file open failed" << endl;
        exit(1);
    }

    if(node->isLeaf()) {
        fout<< node->getPosition().x <<"    "
            << node->getPosition().y <<"    "
            << label <<"\n";
    } else {

        if(node->getRightChild() != NULL)
            io::writeNodeToCSV(node->getRightChild(), label, fout);
        if(node->getLeftChild() != NULL )
            io::writeNodeToCSV(node->getLeftChild(), label, fout);
    }

    return;
}







void io::writeBoarderNodeToCSV(Node * node, int label, ofstream &fout, bool ifAddProbabilityModel)
{//write all the leaf of a subtree whoes root is given by node to csv tab space
 // separated file. the data each line is written as:
 // x  y  label band1 band2 ...

    if(!fout) {
        std::cout <<"file open failed" << endl;
        exit(1);
    }

    if(node->isLeaf()) {
        //write position and label
        fout<< node->getPosition().x <<"    "
            << node->getPosition().y <<"    "
            << label <<"    ";
        //write boader type
        if( node->getBoarderIndexX().size() != 0){
            fout << node->getBoarderIndexX()[0] << "    ";
        } else {
            fout << 0 << "  ";
        }

        if( node->getBoarderIndexY().size() != 0){
            fout << node->getBoarderIndexY()[0] << "    ";
        } else {
            fout << 0 << "  ";
        }

        //write histogram info
        std::vector<float> tempMeanSpectrum= node->getMeanSpectrum();
        for(size_t i=0; i < tempMeanSpectrum.size(); i++){
            fout<< tempMeanSpectrum[i] << "     ";
        }

        if(ifAddProbabilityModel) {
            //write probability info
            std::vector<double> tempProbability = node->getProbability();
            for(size_t i=0; i < tempProbability.size(); i++){
                fout<< tempProbability[i] << "     ";
            }
        }

        fout<<"\n";




    } else {

        if(node->getRightChild() != NULL)
            io::writeBoarderNodeToCSV(node->getRightChild(), label, fout, ifAddProbabilityModel);
        if(node->getLeftChild() != NULL )
            io::writeBoarderNodeToCSV(node->getLeftChild(), label, fout, ifAddProbabilityModel);
    }

    return;
}




void io::writeBoarderNodeSetToCSV(std::vector<Node *> nodeSet, ofstream &fout, bool ifAddProbabilityModel)
{
    for(size_t i=0; i < nodeSet.size(); i++) {
        int label = std::rand()%255; // rand label
        //int label = globalSettings::label_csv;
        io::writeBoarderNodeToCSV(nodeSet[i], label, fout, ifAddProbabilityModel);
        //globalSettings::label_csv++;
    }

    return;
}






void io::bestSegmentation(Node *n, std::vector<Node *> &selectedNodes, double &cost, double lamda, bool useStdCut)
{
    /**
     * @brief Find a segmentation which minimized the energy function.
     * @param n The root of the tree.
     * @param selectedNodes A vector of nodes where we store the segmentation
     * @param cost The total energy of the segmentation.
     *
     * This method use dynamic programming to find the segmentation which minimize
     * the energy function. It starts from the root, call itself recusively.
     * When it visits a node, it call itselt to find the segmentation with
     * minimum eneger of its left child node and right child node repectively.
     * Then it compares the total enegy to maintain the segmentation of its two
     * children and the energy to keep two children as one segment.
     *
     *
     */

    if (!n->isLeaf()){
        std::vector<Node*> nodesL;
        std::vector<Node*> nodesR;
        double costL;
        double costR ;

        //find segmentation of its children
        io::bestSegmentation(n->getLeftChild(),nodesL,costL,lamda, useStdCut);
        io::bestSegmentation(n->getRightChild(),nodesR,costR, lamda, useStdCut);

        // compare the cost, if to keep its children as one segment ?

        double costThis = n->getModel()->cutCost( useStdCut ) + lamda;
        if (costThis < costL+costR){
            selectedNodes.clear();
            selectedNodes.push_back(n);
            cost=costThis;
        } else {
            nodesL.insert(nodesL.end(),nodesR.begin(),nodesR.end());
            selectedNodes=nodesL;
            cost=costL+costR;
        }

    } else {
        selectedNodes.clear();
        selectedNodes.push_back(n);
        cost = n->getModel()->cutCost( useStdCut ) + lamda;
    }

}
























