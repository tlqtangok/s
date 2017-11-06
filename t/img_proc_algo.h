// d:\jd\t\cv_test\cv_2\img_proc_algo.h 
//
#ifndef __IMG_PROC_ALGO_H__
#define __IMG_PROC_ALGO_H__

#include "stdafx.h"
#include <opencv2/opencv.hpp>
// #define img_data(img, c, i, j) (img[(i) * (c) + (j)])
#include <math.h>
#ifdef _MSC_VER
#include <Windows.h>
#endif
#include <iostream>
#include <fstream>

#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <stdint.h>  // uint64_t

#define F_W (ios::out|ios::trunc)
#define F_R (ios::in)
#define __P__  system("pause")



static int glo_var_0 = 111; 


using namespace std; 
using namespace cv; 

typedef unsigned char BYTE; 
typedef unsigned char byte; 
typedef unsigned char uchar; 

//*************
/* utilities */
//*************
#define S_(x) to_string_((int)(x))
template<typename T> string to_string_(T f);
vector<string> split_2_words(string& line);
vector<string> read_file_2_vec_str_chomp(string filename);
template<class T> vector<T> get_num_arr_from_string(const string& sb);
string fcout(string id_s, int fn_idx);
string write_uint8_2_file_2d(const string & fn, unsigned char* buf , int rows, int cols);
string write_int8_buf_2_file_2d(const string & fn, int8_t* buf , int rows, int cols);
/* end utilities */


//************
/* img proc */
//************
unsigned char * read_file_2_buf_1d(string& fn, int rows_cols , unsigned char* buf);
int * read_file_2_int_buf_1d(string& fn, int rows_cols , int* buf);
INT8 * read_file_2_int8_buf_1d(string& fn, int rows_cols , INT8* buf);
float * read_file_2_float_buf_1d(string& fn, int rows_cols , float* buf);
unsigned char * read_file_2_buf(string& fn, int rows, int cols , unsigned char* buf);
Mat read_file_2_mat(string& fn, int rows, int cols ); 
void read_file_2_mat_and_show(string& fn, int rows, int cols ); 
void read_file_2_iplimage_and_show(string& fn, int rows, int cols ); 
cv::Mat cvt_uchar_buf_2_mat(uchar* pData, int rows_, int cols_);


void show_iplimg( IplImage *id_m); 
void show_mat(Mat id_m);
void print_mat_info(Mat& id_m);
void clear_img(Mat id_m);

Mat sub_abs_mat(Mat id_m32, Mat id_m64);
void strong_img_gt_1_then_255(Mat& id_m);
vector<string>  cal_img_diff_and_accumuate(Mat& id_m);
void gradient_img_buf(unsigned char* buf , int rows, int cols, int split=20);  // here,we can define default param for interface 

string diff_int8_img_and_return_report(int8_t *img0, int8_t *img1, int rows, int cols);
string diff_uint8_img_and_return_report(uint8_t *img0, uint8_t *img1, int rows, int cols);
float percent_of_correct_pixels( Mat& id_m32, Mat& id_m64);
Mat get_rectangle_mat(Mat& id_m32, int start_rows,  int end_rows, int start_cols, int end_cols );
Mat get_center( Mat id_m32 , int divide_scale=16 );
/* end img proc */

/* serial str & bin */
void str_2_bin_file(string fn, const string& str_to_serial);
string bin_file_2_str(string fn);
/* end serial */


/* mess */



////////////////
template<typename T> string to_string_(T f){
    ostringstream ss; 
    ss << f; 
    return ss.str(); 
};

template <typename T>
string arr_to_string_1d(T *buf, int len){
        string outs = "";
        for( int i=0;i<len;i++){

			if (sizeof(buf[0]) == 1){
				outs += to_string_((int)(buf[i])) + " ";
			}
			else{
				outs += to_string_(buf[i]) + " ";
			}

        }
        outs += "\n";


        return outs;
}

template <typename T>
string arr_to_string_2d(T *buf, int rows, int cols){
        string outs = "";
        for ( int i=0;i<rows;i++){
                for( int j=0;j<cols;j++){

					if (sizeof(buf[0]) == 1){
						outs += to_string_((int)(buf[i])) + " ";
					}
					else{
						outs += to_string_(buf[i]) + " ";
					}

                }
                outs += "\n";
        }	
        return outs;
}

/////////////////////////
// str serial bin file 
template <typename T>
string serial_2_str( T&  pt)
{
	string id_s = ""; 
	char *c_pt = (char*)&pt; 
	id_s += string(c_pt, c_pt + sizeof(T)); 
	return id_s ; 
}





/*
#define TO_STRING_ string to_string_( T f){ \
  ostringstream ss; \
  ss << f; \
  return ss.str(); \
} \
;
*/
/* end mess */

#endif //__IMG_PROC_ALGO_H__


