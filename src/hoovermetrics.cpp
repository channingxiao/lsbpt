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

#include "hoovermetrics.h"


static bool pixelComparator(std::vector<int> Pixel_1, std::vector<int> Pixel_2)
{
    //this function orders the pixel by cordinates, increasing
    if(Pixel_1[0] < Pixel_2[0]) return true;
    else if(Pixel_1[0] == Pixel_2[0]) return (Pixel_1[1] < Pixel_2[1]);
    else return false;
}

//template<class T>

struct FirstColumnOnlyCmp
{
    bool operator()(const std::vector<int32_t>& pixel_1,
                    const std::vector<int32_t>& pixel_2) const
    {
        bool ifSwap = false;
        if( pixel_1.size() != pixel_2.size() ) return false;
        for(size_t i=2; i < pixel_1.size(); i++ ){
            if( pixel_1[i] < pixel_2[i] ) {
                ifSwap = true;
                break;
            }
        }

        return ifSwap;
    }
};


static bool vectorComparator(std::vector<int32_t> pixel_1, std::vector<int32_t> pixel_2)
{
    //this function orders the pixel by labels

    for(size_t i=2; i < pixel_1.size(); i++ ){
        if( pixel_1[i] < pixel_2[i] ) {
            return true;
        } else if ( pixel_1[i] > pixel_2[i] ){
            return false;
        }
    }

    return false;

}





void readLabelImage(std::string fileName, int &numRegions, std::vector<std::vector<int> > *image)
{
    GDALAllRegister();
    GDALDataset *poDataset =  (GDALDataset *) GDALOpen( fileName.c_str(), GA_ReadOnly ); // open file
    if( poDataset == NULL )
    {
        std::cout<< "File open failed" <<endl;
        return;
    }
    int BandCount = poDataset->GetRasterCount();
    int sizeX = poDataset->GetRasterXSize();
    int sizeY = poDataset->GetRasterYSize();

    std::vector<std::vector<int32_t> > tempPixelSet;
    int32_t  *buffer= new int32_t [sizeX*sizeY*BandCount];
    poDataset->RasterIO( GF_Read, 0, 0,sizeX,sizeY,
                             buffer,sizeX,sizeY,GDT_Int32,BandCount,0,0,0,0);

    for(size_t x =0; x < sizeX; x++){
        for(size_t y = 0 ; y < sizeY; y++){
            std::vector<int32_t> tempPixel;
            tempPixel.push_back(x);
            tempPixel.push_back(y);
            for(int nband =0; nband < BandCount; nband++) {
                tempPixel.push_back( buffer[nband*sizeX*sizeY + y*sizeX + x] );
            }
            if(tempPixel.size() != 0){
            tempPixelSet.push_back(tempPixel);
            }
        }
    }
    delete[] buffer;




    std::sort(tempPixelSet.begin(),tempPixelSet.end(),vectorComparator);
    //std::sort(tempPixelSet.begin(),tempPixelSet.end(),FirstColumnOnlyCmp());


    int label = 0;
    std::vector<int> tempLabel(BandCount);
    for(int i=0; i<BandCount; i++) tempLabel[i] = tempPixelSet[0][i+2];


    for(size_t i=0; i < tempPixelSet.size(); i++) {
        bool ifSameRegion = true;
        for(int j=0; j<BandCount; j++){
            if( tempPixelSet[i][j+2] != tempLabel[j] ){
                tempLabel[j] = tempPixelSet[i][j+2];
                ifSameRegion = false;
            }
        }

        std::vector<int> tempRegion(3);
        if( !ifSameRegion ) {
            label++;
        }
        tempRegion[0] = tempPixelSet[i][0];
        tempRegion[1] = tempPixelSet[i][1];
        tempRegion[2] = label;
        image->push_back(tempRegion);
    }

    numRegions = label+1;


    return;
}



void LoadImage(std::string fileName, int &numRegions,
               std::vector<std::vector<int> > *image)
{ //fileName should be a csv file, each line of which contains the cordinates
    // of a pixel and regions label(make sure no pixel labeled as -1).
    //It will re-label the regions start from 0 to the total number of regions.
    numRegions=-1;
    int tempLabel = -1;
    ifstream fin;
    fin.open(fileName.c_str(), ios::in);
    if (fin.fail())
        {
        std::cout << "\Error!";
        fin.clear( );
        exit(1);
        }

    std::string line;
    std::vector<int> tempPixel(3);
    while ( std::getline( fin, line ) ){
        std::istringstream data( line );
        data >> tempPixel[0] >> tempPixel[1] >> tempPixel[2] ;

        if(tempPixel[2] != tempLabel ) {
            numRegions++;
            tempLabel = tempPixel[2];
        }

        tempPixel[2] = numRegions;
        (*image).push_back(tempPixel);

    }

    numRegions++;

    return;
}

void computeTable(std::vector<std::vector<int> > &image_1,
                  std::vector<std::vector<int> > &image_2,
                  std::vector<std::vector<int> > *hooverTable,
                  std::vector<int> *image_1_regions,
                  std::vector<int> *image_2_regions)

{
    //image_1 and image_2 are pixles with cordinates and labels, the labels
    //should be unique and start from 0 continueslly to the total number of reigions
    // in the image. The size of hooverTable and image_1_regions and
    //image_2_regions should be given when passing through, and all their elements
    //should be initalized to be zero

    //Initialize the elements to be zero
    for(size_t r=0; r<image_1_regions->size(); r++) {
        (*image_1_regions)[r] = 0;
        for(size_t c=0; c<image_2_regions->size(); c++) {
            (*hooverTable)[r][c] = 0;
            (*image_2_regions)[c] = 0;
        }
    }

    //sort the image by cordinates, such that the pixels cordinate are in the same
    // order in the two images.
    //std::sort(image_1.begin(),image_1.end(),pixelComparator);
    //std::sort(image_2.begin(), image_2.end(),pixelComparator);

    int label_1 = 0;
    int label_2 = 0;
    for(size_t i=0; i<image_1.size(); i++){
        label_1 = image_1[i][2];
        label_2 = image_2[i][2];

        (*image_1_regions)[label_1]++;
        (*image_2_regions)[label_2]++;
        (*hooverTable)[label_1][label_2]++;
    }
}



void regionsClassification(std::vector<int> &image_1_regions,
                           std::vector<int> &image_2_regions,
                           std::vector<std::vector<int> > &hooverTable,
                           std::vector<int> *regionType_1,
                           std::vector<int> *regionType_2,
                           float tolerance)
{//This function classifys each regions in image_1 and image_2 into five classes,
 // each class represents by a integer.
    // correctly detection = 1 ,
    // over-segmentation = 2,
    // under-segmentation = 3,
    // missed = 4,
    // noise = 5
 // tolerance should be larger than 0.5 and smaller or equal to 1
 // this function returns regionType_1 and regionType_2

    if(tolerance < 0.5 || tolerance > 1) {
        std::cout<<"Tolerance shold larger than 0.5 and smaller or equal to 1" << endl;
        exit(1);
    }

    //initialize the regionType std::vector
    for(size_t i=0; i<(*regionType_1).size(); i++) (*regionType_1)[i] = 0;
    for(size_t i=0; i<(*regionType_2).size(); i++) (*regionType_2)[i] = 0;


    for(size_t i=0; i < image_1_regions.size(); i++) {
        for(size_t j=0; j < image_2_regions.size(); j++) {
            // rule 1 satisfied, label as crectlly detection
            if( hooverTable[i][j] >= tolerance*image_1_regions[i]){
                if( hooverTable[i][j] >= tolerance*image_2_regions[j]) {
                    (*regionType_1)[i] = 1;
                    (*regionType_2)[j] = 1;
                    break;
                }
            }
        }


        // rule 2 satisfied, label as over-segmented.
        bool ifOverSeg = true;
        int sumRow = 0;
        std::vector<int> tempRegionIndex;
        for(size_t k=0; k < image_2_regions.size(); k++) {
            if(hooverTable[i][k] != 0) {
                if( hooverTable[i][k] < tolerance*image_2_regions[k]) {
                    ifOverSeg = false;
                    break;
                } else {
                    tempRegionIndex.push_back(k);
                    sumRow += hooverTable[i][k];
                }
            }
        }

        if(sumRow < tolerance * image_1_regions[i] || tempRegionIndex.size() < 2 ) ifOverSeg = false;
        if(ifOverSeg) {
            //if((*regionType_1)[i] == 0) (*regionType_1)[i] = 2;// if there are some regions that classified as multiple class, choose 1 first
            (*regionType_1)[i] = 2;
            for(size_t k=0; k<tempRegionIndex.size(); k++) {
                (*regionType_2)[tempRegionIndex[k]] = 2;
            }
        }

    }



    for(size_t i =0; i<image_2_regions.size(); i++) {
        //rule 3 satisfied, label as under-segmented
        bool ifUnderSeg = true ;
        int sumCol = 0 ;
        std::vector<int> tempRegionIndex;
        for(size_t j=0; j<image_1_regions.size(); j++) {
            if(hooverTable[j][i] != 0) {
                if(hooverTable[j][i] < tolerance * image_1_regions[j]) {
                    ifUnderSeg = false;
                    break;
                }else{
                    sumCol += hooverTable[j][i];
                    tempRegionIndex.push_back(j);
                }
            }
        }

        if(sumCol < tolerance * image_2_regions[i] || tempRegionIndex.size() < 2) ifUnderSeg = false;

        if(ifUnderSeg) {
            for(size_t k=0; k<tempRegionIndex.size(); k++){
                if((*regionType_1)[i] == 0) {
                    (*regionType_1)[tempRegionIndex[k]] = 3; // if the regions has been classified, keep it
                }
            }
            (*regionType_2)[i] = 3;
        }

    }



    //If there are some regions in image_1 which are not classified as any type,
    // classify them as missed
    for(size_t i=0; i<(*regionType_1).size(); i++) {
        if((*regionType_1)[i] ==0) (*regionType_1)[i] = 4;
    }

    //If there are some regions in image_2 which are not classified as any type,
    //classify them as noise
    for(size_t i=0; i<(*regionType_2).size(); i++) {
        if((*regionType_2)[i] == 0 ) (*regionType_2)[i] = 5;
    }

    return;
}




void computerHooverMetrics(std::vector<int> &image_1_regions,
                           std::vector<int> &image_2_regions,
                           std::vector<int> &regionType_1,
                           std::vector<int> &regionType_2)
{
    int rc,ro,ru,rm,rn;
    rc=ro=ru=rm=rn=0;
    int n = regionType_1.size()+regionType_2.size();

    int rcw,row,ruw,rmw,rnw;
    rcw=row=ruw=rmw=rnw=0;
    int nw =0;





    for(size_t i=0; i<regionType_1.size(); i++){
        nw+= image_1_regions[i];
        switch(regionType_1[i]){
        case 1: {
            rc++;
            rcw+= image_1_regions[i];
        }break;
        case 2: {
            ro++;
            row+= image_1_regions[i];
        }break;
        case 3: {
            ru++;
            ruw+= image_1_regions[i];
        }break;
        case 4: {
            rm++;
            rmw+=image_1_regions[i];
        }break;
        default: std::cout<<"Something is wrong in regionsClassification "<< endl;break;
        }
    }

    for(size_t i=0; i<regionType_2.size(); i++){
        nw+= image_2_regions[i];
        switch(regionType_2[i]){
        case 1: {
            rc++;
            rcw+=image_2_regions[i];
        }break;
        case 2: {
            ro++;
            row+=image_2_regions[i];
        }break;
        case 3: {
            ru++;
            ruw+=image_2_regions[i];
        }break;
        case 5: {
            rn++;
            rnw+=image_2_regions[i];
        }break;
        default: std::cout<<"Something is wrong in regionsClassification" << regionType_2[i] << endl;
        }
    }

    std::cout<<"The number of regions in reference is :" << regionType_1.size() << endl;
    std::cout<<"The number of regions in tiling segmentation is :" << regionType_2.size() << endl;
    std::cout<< "The number of regions correctly detected is : " << rc << endl;
    // print the result:
    std::cout<<"The hoover metric of segmentation with and without tiling is given by : "
       << endl
       << "rc: " << rc/(1.0*n) << endl
       << "ro: " << ro/(1.0*n) << endl
       << "ru: " << ru/(1.0*n) << endl
       << "rm: " << rm/(1.0*n) << endl
       << "rn: " << rn/(1.0*n) << endl;

    std::cout<<"The number of pixles that are correctlly detected is :" << rcw << endl;
    std::cout<<"The weighted hoover metric of segmentation with and without tiling is given by : "
       << endl
       << "rc: " << rcw/(1.0*nw) << endl
       << "ro: " << row/(1.0*nw) << endl
       << "ru: " << ruw/(1.0*nw) << endl
       << "rm: " << rmw/(1.0*nw) << endl
       << "rn: " << rnw/(1.0*nw) << endl;

    std::cout << rc/(1.0*n) << "    "
         << ro/(1.0*n) << "    "
         << ru/(1.0*n) << "    "
         << rm/(1.0*n) << "    "
         << rn/(1.0*n) << endl;


    std::cout << rcw/(1.0*nw) << "   "
         << row/(1.0*nw) << "   "
         << ruw/(1.0*nw) << "   "
         << rmw/(1.0*nw) << "   "
         << rnw/(1.0*nw) << endl;

}





void paintHoover( std::vector<std::vector<int> > &image, std::vector<int> &regionType, std::string fileName_save)
{// image should be sorted based on cordinates, increasing
    //sort the image by cordinates, such that the pixels cordinate are in the same
    // order in the two images.
    //std::sort(image.begin(),image.end(),pixelComparator);
    //std::sort(image.begin(), image.end(),pixelComparator);

    //for(size_t k=0; k< image.size(); k++)
    //    std::cout<< image[k][0] <<"  "<< image[k][1] <<" " << image[k][2] << endl;


    int width = abs(image[image.size()-1][0] - image[0][0])+1;
    int height = abs(image[image.size()-1][1] - image[0][1])+1;

    io::createEmptyImage( fileName_save, width, height, 3);

    GDALDataset * poDataset;
    GDALAllRegister();
    poDataset =  (GDALDataset *) GDALOpen( fileName_save.c_str(), GA_Update );
    // green (0,128,0)
    GByte green[3];
    green[0] = 0;
    green[1] = 128;
    green[2] = 0;
    GByte red[3];
    red[0] = 128;
    red[1] = 0;
    red[2] = 0;
    GByte blue[3];
    blue[0] = 0;
    blue[1] = 0;
    blue[2] = 128;

    for(size_t i=0; i<image.size(); i++) {
        switch( regionType[image[i][2]] ){
        case 1: {
            poDataset->RasterIO( GF_Write,
                                 image[i][0] - image[0][0],
                                 image[i][1] - image[0][1],
                                 1, 1, green,1,1,GDT_Byte,3,0,0,0,0);
        }break;
        case 2: {//over segmented
            poDataset->RasterIO( GF_Write,
                                 image[i][0] - image[0][0],
                                 image[i][1] - image[0][1],
                                 1, 1, red,1,1,GDT_Byte,3,0,0,0,0);
        }break;
        case 3: {// under segmented
                poDataset->RasterIO( GF_Write,
                                     image[i][0] - image[0][0],
                                     image[i][1] - image[0][1],
                                     1, 1, blue,1,1,GDT_Byte,3,0,0,0,0);
        }break;
        case 4: break;
        case 5: break;
        default:break;
        }
    }


    delete poDataset;


}





void hooverCompare(std::string fileName1, std::string fileName2, std::string fileName_save, float tolerance)
{

    std::vector<std::vector<int> > image_1;
    std::vector<std::vector<int> > image_2;
    int numRegions_1;
    int numRegions_2;

    if(fileName1.substr(fileName1.find_last_of(".") + 1) == "csv") {

        LoadImage(fileName1, numRegions_1, &image_1 );
        LoadImage(fileName2, numRegions_2, &image_2 );

    } else {

        readLabelImage(fileName1, numRegions_1, &image_1 );
        readLabelImage(fileName2, numRegions_2, &image_2 );


    }

    std::cout<<"The number of regions in reference is :" << numRegions_1 << endl;
    std::cout<<"The number of regions in tiling segmentation is :" << numRegions_2 << endl;



    //sort the image by cordinates, such that the pixels cordinate are in the same
    // order in the two images.
    std::sort(image_1.begin(),image_1.end(),pixelComparator);
    std::sort(image_2.begin(), image_2.end(),pixelComparator);

    std::vector<std::vector<int> > hooverTable(numRegions_1, std::vector<int>(numRegions_2));


    std::vector<int> image_regions_1(numRegions_1);
    std::vector<int> image_regions_2(numRegions_2);

    std::vector<int> regionType_1(numRegions_1);
    std::vector<int> regionType_2(numRegions_2);


    computeTable(image_1, image_2, &hooverTable, &image_regions_1, &image_regions_2);


    regionsClassification(image_regions_1, image_regions_2, hooverTable,
                          &regionType_1, &regionType_2, tolerance);

    paintHoover(image_1, regionType_1, fileName_save);
    computerHooverMetrics(image_regions_1, image_regions_2,
                          regionType_1, regionType_2);


    return;
}




























