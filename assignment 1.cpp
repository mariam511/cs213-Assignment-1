
// FCAI – OOP Programming – 2023 - Assignment 1
// Program Name:               CS213.cpp
// Last Modification Date:    9/10/2023
// Author1 and ID and Emil:    Josiane Usama - 20220502 - email:josianeosama975@gmail.com
// Author2 and ID and Emil:    Eihab Muhammed - 20220520 - email: eihabmuhammed56@gmail.com
// Author3 and ID and Emil:    Mariam Ayman   - 20221141 - email:mariamayman5112003@gmail.com



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

/*7*/void Detect_Edges();

/*8*/ void EnlargeImage();

/*9*/ void shrinkImage();

/*a*/ void mirror();

/*b*/void Shuffle_Image();

/*c*/ void BlurImage();

/*d*/ void crop_image();

/*e,f*/ void skew();


int main() {
    bool cont = true;
    loadImage();
    cout << " select the filter you want : "
         << endl; //knowing the effect to call it's specicif function
    cout << "1-black_white\n" << "2-invert\n" << "3-merge\n" << "4-flip\n" << "5-rotate\n" << "6-darken_And_Lighten \n"
         <<"7-Detect Edges \n"<<"8-Enlarge Image \n"<< "9-shrinkImage \n" <<"10- mirror \n"<<"11-Shuffle Image \n"
         << "12-BlurImage \n"<<"13-crop image \n"<<"14-skew : ";


    while (cont == true) {
        cin >> effect;
        cout << endl;
        if (effect == "1") {
            Black_And_White_Image();
        } else if (effect == "2") {
            Invert_Image();
        }
        else if (effect == "3") {
            loadImage1();
            merge();
        }
        else if (effect == "4") {
            flip_image();
        }
        else if (effect == "5") {
            rotate_Images();
        }
        else if (effect == "6") {
            darken_And_Lighten();
        }
        else if(effect =="7"){
            Detect_Edges();
        }
        else if (effect=="8"){
            EnlargeImage();
        }
        else if (effect == "9") {
            shrinkImage();
        }
        else if(effect=="10"){
            mirror();
        }
        else if (effect=="11"){
            Shuffle_Image();
        }
        else if (effect == "12") {
            BlurImage();
        }
        else if(effect=="13"){
            crop_image();
        }
        else if(effect=="14"){
            skew();
        }
        cout<<"do you want another filter ?\n";
        string ans;
        cout<<"1-Yes \n"<<"2-No \n";
        cin>>ans;
        if(ans=="1"){
            cont= true;
            cout<<"select the filter :";
        }
        else if (ans =="2"){
            cont = false;}

        else {
            cout << " please enter 1 or 2 \n";
            cin>>ans;
            if(ans=="1"){
                cont= true;
            }

            else if (ans =="2"){
                cont = false;
            }
        }


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
    cout << "1- flip vertically \n"<<"2- flip horizontally : ";
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
// This function merges two images by taking the average of their pixel values
void merge() {
// Loop through each row of the images
    for (int i = 0; i < SIZE; i++) {
// Loop through each column of the images
        for (int j = 0; j< SIZE; j++) {
// Take the average of the pixel values at position (i, j) in both images and store it in image2
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
// This function darkens or lightens an image by asking the user to choose an option

void darken_And_Lighten() {
    string choice;
// Print the options to the console
    cout << "1- darken \n"" 2- lighten :";
    cin >> choice;
    cout << endl;
    if (choice == "1") {
        // Loop through each row of the image
        for (int i = 0; i < SIZE; i++) {
// Loop through each column of the image
            for (int j = 0; j < SIZE; j++) {
// Divide the pixel value at position (i, j) by 3 and store it in the same position
// This reduces the brightness of the pixel by 50%
                image[i][j] =  (image[i][j])/2;
            }
        }
    }

    else if (choice == "2") {
// Loop through each row of the image
        for (int i = 0; i < SIZE; i++) {
// Loop through each column of the image
            for (int j = 0; j < SIZE; j++) {
// Add 255 to the pixel value at position (i, j) and divide it by 2 and store it in the same position
// This increases the brightness of the pixel by 50%
                image[i][j] = (image[i][j] + 255) /2;

            }
        }
    }
}//----------------------------------------

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

//----------------------------------------
void EnlargeImage() {
    unsigned char temp[SIZE][SIZE];

    cout << "Which quarter do you want to enlarge? 1,2,3 or 4\n"; //choose  what degree do you want to rotate the image
    int n;
    cin >> n;

    if (n == 1) {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                temp[i][j] = image[i / 2][j / 2];
            }
        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image[i][j] = temp[i][j]; //get image[i][j] values from the temp ones


            }
        }
    }
    if (n == 2) {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                temp[i][j] = image[i / 2][((j / 2) + SIZE / 2)];
            }
        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image[i][j] = temp[i][j]; //get image[i][j] values from the temp ones

            }
        }
    }
    if (n == 3) {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                temp[i][j] = image[((i / 2) + SIZE / 2)][j / 2];

            }
        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image[i][j] = temp[i][j]; //get image[i][j] values from the temp ones

            }
        }
    }
    if (n == 4) {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                temp[i][j] = image[(i / 2) + SIZE / 2][((j / 2) + SIZE / 2)];
            }
        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image[i][j] = temp[i][j]; //get image[i][j] values from the temp ones

            }

        }
    }
}


//------------------------------------------
// This function shrinks an image by a given scale factor

void shrinkImage(){
    int scale;
// Ask the user to choose a scale factor from the options
    cout<< "shrink the image dimentions to : \n"<<"1---> 1/2 \n"<<"2---> 1/3 \n" <<"3---> 1/4 :";
    cin>>scale;
// Add one to the scale factor to match the options
    scale=scale+1;
    for(int a=0 ; a<SIZE ; a++){
        for(int s=0 ; s<SIZE ; s++){
// Initialize the new array with white pixels
            image2[a][s]=255;
        }
    }
// Calculate the new width and height of the image based on the scale factor
    int new_width = 256 / scale;
    int new_height = 256 / scale;

// Loop through each row of the new image
    for (int i = 0; i < new_height; i++) {
        // Loop through each column of the new image

        // Loop through each pixel in the original image that corresponds to the position (i, j) in the new image

        for (int j = 0; j < new_width; j++) {
            int sum = 0;
            for (int k = i * scale; k < (i + 1) * scale; k++) {
                for (int l = j * scale; l < (j + 1) * scale; l++) {
                    // Add the pixel value to the sum

                    sum += image[k][l];
                }
            }
            // Take the average of the sum and store it in the new image

            image2[i][j] = sum / (scale * scale);
        }
    }
// Copy the new image to the original image array

    for(int y=0;y<SIZE;y++){
        for (int u =0; u<SIZE ; u++){
            image[y][u]=image2[y][u];
        }
    }

}
//------------------------------------------------

void mirror(){
    int mirrorType;
    cout << "Select mirroring type:" << endl;
    cout << "1- Mirror left Half" << endl;
    cout << "2- Mirror right Half" << endl;
    cout << "3- Mirror upper Half" << endl;
    cout << "4- Mirror lower Half" << endl;
    cin >> mirrorType;

    if(mirrorType==1)
    {

        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE / 2; ++j) {
                image[i][SIZE - j - 1] = image[i][j];
            }
        }
    }

    else if(mirrorType==2){
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE / 2; ++j) {
                image[i][j] = image[i][SIZE - j - 1];
            }
        }

    }

    else if(mirrorType==3){
        for (int i = 0; i < SIZE / 2; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                image[SIZE - i - 1][j] = image[i][j];
            }
        }
    }

    else if(mirrorType==4){
        for (int i = 0; i < SIZE / 2; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                image[i][j] = image[SIZE - i - 1][j];
            }
        }
    }


}

//---------------------------------------------------

void Shuffle_Image() {

    unsigned char temp1[SIZE][SIZE];
    unsigned char temp2[SIZE][SIZE];
    unsigned char temp3[SIZE][SIZE];
    unsigned char temp4[SIZE][SIZE];
    for(int i=0;i<SIZE/2;i++){
        for(int j=0;j<SIZE/2;j++){
            temp1[i][j]=image[i][j];
        }
    }
    for(int i=0;i<SIZE/2;i++){
        for(int j=SIZE/2;j<SIZE;j++){
            temp2[i][j]=image[i][j];
        }
    }
    for(int i=SIZE/2;i<SIZE;i++){
        for(int j=0;j<SIZE/2;j++){
            temp3[i][j]=image[i][j];
        }
    }
    for(int i=SIZE/2;i<SIZE;i++){
        for(int j=SIZE/2;j<SIZE;j++){
            temp4[i][j]=image[i][j];
        }
    }
    cout<<"please,Enter the new order\n";
    int  arr [4];
    for(int i=0;i<4;i++){cin>>arr[i];}
    if(arr[0]==1){
        for(int i=0;i<SIZE/2;i++){
            for(int j=0;j<SIZE/2;j++){
                image[i][j]=temp1[i][j];
            }
        }

    }
    else if(arr[0]==2){
        for(int i=0;i<SIZE/2;i++){
            for(int j=0;j<SIZE/2;j++){
                image[i][j]=temp2[i][j+(SIZE/2)];
            }
        }
    }
    else if(arr[0]==3){
        for(int i=0;i<SIZE/2;i++){
            for(int j=0;j<SIZE/2;j++){
                image[i][j]=temp3[i+(SIZE/2)][j];
            }
        }
    }
    else if(arr[0]==4){
        for(int i=0;i<SIZE/2;i++){
            for(int j=0;j<SIZE/2;j++){
                image[i][j]=temp4[i+(SIZE/2)][j+(SIZE/2)];
            }
        }
    }
    if(arr[1]==1){
        for(int i=0;i<SIZE/2;i++){
            for(int j=SIZE/2;j<SIZE;j++){
                image[i][j]=temp1[i][j-(SIZE/2)];
            }
        }

    }
    else if(arr[1]==2){
        for(int i=0;i<SIZE/2;i++){
            for(int j=SIZE/2;j<SIZE;j++){
                image[i][j]=temp2[i][j];
            }
        }
    }
    else if(arr[1]==3){
        for(int i=0;i<SIZE/2;i++){
            for(int j=SIZE/2;j<SIZE;j++){
                image[i][j]=temp3[i+(SIZE/2)][j+(SIZE/2)];
            }
        }
    }
    else if(arr[1]==4){
        for(int i=0;i<SIZE/2;i++){
            for(int j=SIZE/2;j<SIZE;j++){
                image[i][j]=temp4[i+(SIZE/2)][j];
            }
        }
    }
    if(arr[2]==1){
        for(int i=SIZE/2;i<SIZE;i++){
            for(int j=0;j<SIZE/2;j++){
                image[i][j]=temp1[i-(SIZE/2)][j];
            }
        }

    }
    else if(arr[2]==2){
        for(int i=SIZE/2;i<SIZE;i++){
            for(int j=0;j<SIZE/2;j++){
                image[i][j]=temp2[i-(SIZE/2)][j-(SIZE/2)];
            }
        }
    }
    else if(arr[2]==3){
        for(int i=SIZE/2;i<SIZE;i++){
            for(int j=0;j<SIZE/2;j++){
                image[i][j]=temp3[i][j];
            }
        }
    }
    else if(arr[2]==4){
        for(int i=SIZE/2;i<SIZE;i++){
            for(int j=0;j<SIZE/2;j++){
                image[i][j]=temp4[i][j+(SIZE/2)];
            }
        }
    }
    if(arr[3]==1){
        for(int i=SIZE/2;i<SIZE;i++){
            for(int j=SIZE/2;j<SIZE;j++){
                image[i][j]=temp1[i-(SIZE/2)][j-(SIZE/2)];
            }
        }

    }
    else if(arr[3]==2){
        for(int i=SIZE/2;i<SIZE;i++){
            for(int j=SIZE/2;j<SIZE;j++){
                image[i][j]=temp2[i-(SIZE/2)][j];
            }
        }
    }
    else if(arr[3]==3){
        for(int i=SIZE/2;i<SIZE;i++){
            for(int j=SIZE/2;j<SIZE;j++){
                image[i][j]=temp3[i][j-(SIZE/2)];
            }
        }
    }
    else if(arr[3]==4){
        for(int i=SIZE/2;i<SIZE;i++){
            for(int j=SIZE/2;j<SIZE;j++){
                image[i][j]=temp4[i][j];
            }
        }
    }
}



//---------------------------------------------------------
// This function blurs an image by applying a smoothing filter
void BlurImage() {
    int x = 2;
    // Repeat the blurring process twice
    while (x >= 0) {
// Loop through each row of the image except the first and last one
        for (int i = 1; i < 255; i++) {
// Loop through each column of the image except the first and last one
            for (int j = 1; j < 255; j++) {
                // Calculate the average of surrounding pixels and store it in a new array
                image2[i][j] = (image[i - 1][j - 1] + image[i - 1][j] + image[i - 1][j + 1] +
                                image[i][j - 1] + image[i][j + 1] +
                                image[i + 1][j - 1] + image[i + 1][j] + image[i + 1][j + 1]) / 8;
            }
        }
        for (int l = 1; l < 255; l++) {
            for (int m = 1; m < 255; m++) {
                // Calculate the average of surrounding pixels and store it back in the original array
                image[l][m] = (image2[l - 1][m - 1] + image2[l - 1][m] + image2[l - 1][m + 1] +
                               image2[l][m - 1] + image2[l][m + 1] +
                               image2[l + 1][m - 1] + image2[l + 1][m] + image2[l + 1][m + 1]) / 8;
            }
        }
        x--;
    }

}//------------------------------------------------------

void crop_image() {
    cout<<"please,enter x,y,l and w\n";


    unsigned char temp[SIZE][SIZE];
    int x,y,l,w;
    cin>>x>>y>>l>>w;
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            if(i>=x&&i<=l+x&&j>=y&&j<=y+w){temp[i][j]=image[i][j];}
            else{temp[i][j]=255;}
        }
    }
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            image[i][j]=temp[i][j];
        }
    }
}

//---------------------------------------------------------
// This function skews an image vertically or horizontally by a given angle

void skew(){
// Print the options to the console
    cout<<"1- Vertically \n"<<"2-Horizontally : ";
    int choice;
    cin>>choice;
// skew vwrtically
    if(choice==1) {
        double rad;
        cout<<"Enter the angle you want";
        cin >> rad;
// Convert the angle from degrees to radians
        rad = (rad * 22) / (180 * 7);
        unsigned char img_in[SIZE][SIZE];
        int x;
// Calculate the horizontal shift factor based on the angle
        x = (tan(rad) * 256) / (tan(rad) + 1);
// Initialize the new array with white pixels
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                img_in[i][j] = 255;

// Copy the pixel value from the original image to the new array with a horizontal shift proportional to the column index
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                img_in[i][(j * x) / SIZE] = image[i][j];
            }
        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image[i][j] = img_in[i][j];
            }
        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                img_in[i][j] = 255;
            }
        }
        double step = SIZE - x;  // The number of steps to shift the image horizontally double
        double mov = step / SIZE; // The amount of shift per row

        // Copy the pixel value from the original image to the new array with a horizontal shift inversely proportional to the row index
        for (int i = 0; i < SIZE; ++i) {
            for (int j = (int) step; j < step + x; ++j) {
                img_in[i][j] = image[i][(int) (j - step)];
            }
            step -= mov;
        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image[i][j] = img_in[i][j];
            }
        }
    }


    else if(choice==2) {
        //skew horizontally
        double rad;
        cout<<"Enter the angle you want";
        cin >> rad;
// Convert the angle from degrees to radians
        rad = (rad * 22) / (180 * 7);
        unsigned char img_in[SIZE][SIZE];
        int y;
        y = (tan(rad) * 256) / (tan(rad) + 1);

        // Initialize the output image with white pixels
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                img_in[i][j] = 255;

        // Copy the input image to the output image with horizontal skew
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                img_in[(i * y) / SIZE][j] = image[i][j];
            }
        }

        // Copy the output image back to the input image
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image[i][j] = img_in[i][j];
            }
        }

        // Initialize the output image with white pixels again
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                img_in[i][j] = 255;

        // Adjust the output image to fit the skewed input image
        double step = SIZE - y; // The number of steps
        double mov = step / SIZE;
        for (int i = 0; i < SIZE; ++i) {
            for (int j = (int) step; j < step + y; ++j) {
                img_in[j][i] = image[(int) (j - step)][i];
            }
            step -= mov;
        }

        // Copy the output image back to the input image again
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image[i][j] = img_in[i][j];
            }
        }

    }
}

//------------------------------------
//---------------------------------
