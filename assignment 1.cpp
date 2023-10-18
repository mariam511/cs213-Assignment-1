CS213-2023-20220502-20220520-20221141-A1-Part1.cpp
// Purpose: Demonstrate use of bmplip for handling
//          bmp colored and grayscale images
//          Program load a gray image and store in another file
// Author:  Mohammad El-Ramly
// Date:    30 March 2018
// Version: 1.0

#include <iostream>
#include <algorithm>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"


using namespace std;
unsigned char image[SIZE][SIZE];
unsigned char image1[SIZE][SIZE];
unsigned char image2[SIZE][SIZE];

string effect;
void loadImage ();

void loadImage1 ();

void saveImage ();

/*1*/void Black_And_White_Image();

/*2*/void Invert_Image();

/*3*/void merge();

/*4*/void flip_image();

/*5*/ void rotate_Images();

/*6*/void darken_And_Lighten();

/*7*/void mirror();

 /*8*/ void Detect_Edges();



int main()
{
    cout<<" enter the number of the filter you want from here : "<<endl; //knowing the effect to call it's specicif function
    cout<<"1-black_white\n"<<"2-invert\n"<<"3-merge\n"<<"4-flip\n"<<"5-rotate\n"<<"6-darken_And_Lighten \n"<<"7-mirror \n"<<"8-Detect edges \n";
    cin>>effect;
    cout<<endl;
    loadImage();

    if (effect=="1")
    {
        Black_And_White_Image();
    }

    if (effect=="2")
    {
        Invert_Image();
    }

    if (effect=="3")
    {
        loadImage1();
        merge();
    }

    if(effect=="4"){
        flip_image();
    }

    if(effect=="5"){
        rotate_Images();
    }

    if (effect=="6")
    {
        darken_And_Lighten();
    }

    if (effect=="7")
    {
        mirror();
    }

    if(effect=="8")
    {
     Detect_Edges();
    }
    

    saveImage();
    return 0;
}

//_________
void loadImage () {
    char imageFileName[100];

    // Get gray scale image file name
    cout << "Enter the source image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    readGSBMP(imageFileName, image);
}

//_________

void loadImage1 () {
    char imageFileName[100];

    // Get gray scale image file name
    cout << "Enter the second source image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    readGSBMP(imageFileName, image1);
}

//_________
void saveImage() {
    char imageFileName[100];

    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add .bmp extension
    strcat(imageFileName, ".bmp");

    if(effect=="3")
    {writeGSBMP(imageFileName, image2);}

    else
        writeGSBMP(imageFileName, image);


    cout << "Image saved successfully." << endl;
}



//_________
void Black_And_White_Image()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (image[i][j] > 128) {
                image[i][j] = 255;
            }
            else {
                image[i][j] = 0;
            }
        }
    }
}
//------------------
void Invert_Image(){

    unsigned char temp[SIZE][SIZE];

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {

            if (image[i][j] ==255)//to invert each white pixel to black one
                temp[i][j] = 0;
            else if(image[i][j]==0)//to invert each black pixel to white one
                temp[i][j] = 255;
            else
                temp[i][j]=255-image[i][j]; //to invert each pixel

            image[i][j]=temp[i][j];//get image[i][j] values from the temp ones
        }
    }




}

//---------------------------------------------------
//function to flip the image (vertically or horizontally)
void flip_image() {
    int flip_style;
    cout << "for flip vertically enter 1 -- for flip horizontally enter 2 : ";
    cin >> flip_style;
    cout<<endl;

    //Check user input to see what we will do if = 1 we will flip vertically, otherwise if = 2 we will flip horizontally

    if (flip_style == 1) {

        //flip vertically

        for (int i = 0; i < SIZE / 2; i++) {

            /*This is the outer loop iterates from i = 0 to i < SIZE / 2
            because  we only need to swap the first half of the rows with the second half of the rows.
             Swapping the second half of the rows with
            the first half would result in swapping the same rows again, which would undo the previous swap.
             Therefore, we only need to iterate through half of the rows.
             */
            for (int j = 0; j < SIZE; j++) {

                /*
                 This is the inner loop iterates from j=0 to j<SIZE
                 because we need to swap each pixel in a row with its corresponding pixel in the
                 opposite row. This means that we need to iterate through all the pixels in each row.
                */

                unsigned char temp = image[i][j]; //stores the value of image[i][j] in temp
                image[i][j] = image[SIZE - i - 1][j];//assigns the value of image[SIZE - i - 1][j] to image[i][j]
                image[SIZE - i - 1][j] = temp;//assigns the value of temp to image[SIZE - i - 1][j].
            }
        }

        /*This means that the first row of the image is swapped with the last row,
         * the second row is swapped with the second-to-last row, and so on.*/
        //The purpose of this code is to flip the image vertically along its horizontal axis.
    }

    else {

        //flip horizontally

        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE / 2; j++) {
                unsigned char temp = image[i][j];
                image[i][j] = image[i][SIZE - j - 1];
                image[i][SIZE - j - 1] = temp;
            }
        }
    }
}
//-------------------------------------------
void merge() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            image2[i][j] = (image1[i][j]+image[i][j])/2;
        }
    }
}
//----------------------------------------------------------
void rotate_Images() {

    unsigned char temp[SIZE][SIZE];

    cout<<"How do you want to rotate?\n"; //choose  what degree do you want to rotate the image
    cout<<"1---> 90\n";
    cout<<"2---> 180\n";
    cout<<"3---> 270\n";
    //choose 1 to rotate 90 degree
    //choose 2 to rotate 180 degree
    //choose 3 to rotate 270 degree
    int n;cin>>n;

    //to rotate the image by 90 degree change the value of each element image[i][j]to[j][size-i-1]
    if(n==1){
        for (int i = 0; i <SIZE; i++) {
            for (int j = 0; j<SIZE; j++) {
                temp[j][SIZE-i-1]=image[i][j];

            }
        }
        for (int i = 0; i <SIZE; i++) {
            for (int j = 0; j<SIZE; j++) {
                image[i][j]=temp[i][j]; //get image[i][j] values from the temp ones

            }
        }
    }

        //to rotate the image by 180 degree reverse  the nested loops
    else if(n==2){
        for(int i=SIZE-1;i>=0;i--){
            for(int j=SIZE-1;j>=0;j--){
                temp[SIZE-1-i][SIZE-1-j]=image[i][j];

            }
        }
        for(int i=SIZE-1;i>=0;i--){
            for(int j=SIZE-1;j>=0;j--){
                image[i][j]=temp[i][j];//get image[i][j] values from the temp ones

            }
        }

    }

        //to rotate the image by 90 degree change the value of each element image[i][j]to[size-j-1][i]
    else if(n==3){
        for (int i = 0; i <SIZE; i++) {
            for (int j = 0; j<SIZE; j++) {
                temp[SIZE-j-1][i]=image[i][j];

            }
        }
        for (int i = 0; i <SIZE; i++) {
            for (int j = 0; j<SIZE; j++) {
                image[i][j]=temp[i][j];//get image[i][j] values from the temp ones

            }
        }

    }
}
//---------------------------------------------------
void darken_And_Lighten() {
    string choice;
    cout << "darken or lighten : ";
    cin >> choice;
    cout << endl;
    if (choice == "darken") {
        for (int i = 0; i < SIZE; i++) {
             for (int j = 0; j < SIZE; j++) {
                 image[i][j] =  (image[i][j])/2;// in this line we are adding zero to the main pixel and getting the average of the original image and the dark one
                                                // to make it darker by 50%
            }
        }
    } else if (choice == "lighten") {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image[i][j] =  (image[i][j]+255)/2;   // in this line we are adding 255 to the main pixel and getting the average of both the white image and the original
                                                // to make it brighter by 50%

            }
        }
    }

}
void mirror(){
     int mirrorType;
    cout << "Select mirroring type:" << endl;
    cout << "1- Mirror Left Half" << endl;
    cout << "2- Mirror Right Half" << endl;
    cout << "3- Mirror Upper Half" << endl;
    cout << "4- Mirror Lower Half" << endl;
    cin >> mirrorType;

    if(mirrorType==1){
            for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE / 2; ++j) {
            image[i][j] = image[i][SIZE - j - 1];
        }
    }

    }
    if(mirrorType==2)
    {
       
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE / 2; ++j) {
            image[i][SIZE - j - 1] = image[i][j];
        }
        }
    }
    
    if(mirrorType==3){
        for (int i = 0; i < SIZE / 2; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image[i][j] = image[SIZE - i - 1][j];
        }
    }
}
   if(mirrorType==4){
        for (int i = 0; i < SIZE / 2; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image[SIZE - i - 1][j] = image[i][j];
        }
    }
   }

}
void Detect_Edges() {
    unsigned char detect_image[SIZE][SIZE];
    for (int j = 0; j < SIZE-1; j++)
    {
        for (int i = 0; i< SIZE-1; i++) 
        {

            if(image[i][j]==image[i+1][j+1])
            {
                detect_image[i][j] = image[i][j];
            }
            if((abs(image[i][j]-image[i+1][j]>=24))||(abs(image[i][j]-image[i][j+1]>=24))){
                detect_image[i][j] = 0;
            }
            else{
                detect_image[i][j] = 255;
            }
        }
    }
    for (int j = 0; j < SIZE-1; j++)
    {
        for (int i = 0; i< SIZE-1; i++) {
            image[i][j] = detect_image[i][j];
        }
    }
}
