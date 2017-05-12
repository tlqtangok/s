// cv_2.cpp : 定义控制台应用程序的入口点。
//
#ifndef __IMG_PROC_ALGO_H__
#define __IMG_PROC_ALGO_H__

#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include <math.h>

#include <Windows.h>
#include <iostream>
#include <fstream>

#include <string>
#include <sstream>
#include <vector>
#include <iterator>

using namespace std; 
using namespace cv; 

typedef unsigned char BYTE; 

void clear_img(Mat id_m);

template<class T> 
vector<T> get_num_arr_from_string(const string& sb);


Mat get_rectangle_mat(Mat& id_m32, int start_rows,  int end_rows, int start_cols, int end_cols );



vector<string> read_file_2_vec_string(string filename);

Mat get_center( Mat id_m32 , int divide_scale = 16 );



float percent_of_correct_pixels( Mat& id_m32, Mat& id_m64);

bool c_is_value_path_c(char c);



vector<string> split_2_words(string& line);


Mat sub_abs_mat(Mat id_m32, Mat id_m64);

void strong_img(Mat id_m);



vector<string>  show_img_diff_and_accumuate(Mat& id_m);
void print_mat_info(Mat& id_m);

void show_id_m(Mat id_m);


#endif __IMG_PROC_ALGO_H__