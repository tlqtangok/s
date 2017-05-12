// cv_2.cpp : 定义控制台应用程序的入口点。
//

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

void clear_img(Mat id_m){

    for (int i=0;i<id_m.rows;i++){
        for(int j=0;j<id_m.cols;j++){
            for (int k=0;k< id_m.channels();k++){
                auto t = (id_m.row(i).col(j)).data; 
                t[k]=0; 

            }
        }
    }

}

template<class T> 
vector<T> get_num_arr_from_string(const string& sb){
    // already go sb 
    int i=0;
    int cnt = 0; 
    int start_loc = 0; 
    bool start_flag = false; 
    int end_loc = 0; 
    bool end_flag = false; 

    vector<T> num_arr ; 
    auto *sbb = sb.c_str(); 

    for(auto i: sb){

        if( !start_flag && i>='0' && i<='9' ){

            //printf("%c ",i);

            start_loc = cnt ;
            start_flag = true; 


        }

        if ( start_flag && !(i>='0' && i<='9') ){
            end_loc = cnt ; 
            end_flag = true; 
        }


        if ( end_flag  && start_flag ){
            string id_t(sbb+start_loc, sbb+end_loc); 
            //cout << id_t << endl; 
            num_arr.push_back( (T) atoi(id_t.c_str()) ); 

            start_flag = false ; 
            end_flag = false ; 
        }

        cnt++; 
    }

    if (sizeof(T)==1){
        vector<T> new_num_arr; 
        auto it = num_arr.begin();
        auto it_end = num_arr.end();
        for(int i=0;i<3;i++){it++;}  // we don't need first three as data,they are struct

        new_num_arr.assign(it,num_arr.end());
        return new_num_arr;

    }
    return num_arr ; 

}  // end get_num_arr_from_string(){


Mat get_rectangle_mat(Mat& id_m32, int start_rows,  int end_rows, int start_cols, int end_cols ){

    // end_rows  include!!!
    int rows = id_m32.rows; 

    int cols = id_m32.cols;

    int sz_rows = end_rows - start_rows+1;  // coordinate of end_rows
    int sz_cols = end_cols - start_cols+1; 

    assert( rows>=sz_rows ); 
    assert( cols>=sz_cols ); 


    Mat id_mm(sz_rows,sz_cols, CV_8UC(id_m32.channels())); 

    for(int i=start_rows;i<end_rows; i++){
        for(int j=start_cols;j<end_cols;j++){


            auto &t_from = id_m32.row(i).col(j); 
            auto &t_to = id_mm.row(i-start_rows).col(j-start_cols);

            for (int c=0;c<id_m32.channels();c++){

                t_to.data[c] = t_from.data[c]; 

            }

        }

    } // end for i

    return id_mm; 

}




vector<string> read_file_2_vec_string(string filename){
    vector<string> id_v_str; 
    string sb=""; 
    ifstream ifs(filename.c_str()); 
    const int max_line_sz = 1024; 
    char buf[max_line_sz] = {0};

    while( ifs.getline(buf, max_line_sz)) {
        sb=string(buf+0); 
        cout << sb<< endl; 
        id_v_str.push_back(sb);
    }
    return id_v_str; 
}

Mat get_center( Mat id_m32 , int divide_scale = 16 ){

    int rows = id_m32.rows; 

    int cols = id_m32.cols;



    int center_rows = rows/2; 

    int center_cols = cols/2; 

    //int divide_scale = 16; 

    int start_rows = 0 + center_rows - rows/divide_scale; 
    int end_rows = 0 + start_rows + rows/divide_scale*2; 

    int start_cols = 0 + center_cols - cols/divide_scale;
    int end_cols = 0 + start_cols + cols/divide_scale*2; 


    int sz_rows = end_rows - start_rows; 
    int sz_cols = end_cols - start_cols; 


    Mat id_mm(sz_rows,sz_cols, CV_8UC(3)); 


    for(int i=start_rows;i<end_rows; i++){
        for(int j=start_cols;j<end_cols;j++){


            auto &t_from = id_m32.row(i).col(j); 
            auto &t_to = id_mm.row(i-start_rows).col(j-start_cols);

            for (int c=0;c<id_m32.channels();c++){

                t_to.data[c] = t_from.data[c]; 

            }

        }

    } // end for i

    // show_id_m(id_mm);
    return id_mm; 


}



float percent_of_correct_pixels( Mat& id_m32, Mat& id_m64){
    float ret_f = 0.0f;

    //cout << "- into this\n"; 
    assert(id_m32.rows == id_m64.rows); 
    assert(id_m32.cols == id_m64.cols); 
    assert(id_m32.channels() == id_m64.channels()); 


    int start_rows = 0; 
    int end_rows = id_m32.rows; 

    int start_cols= 0; 
    int end_cols = id_m32.cols; 

    int channels = id_m32.channels(); 

    int correct_point_cnt = 0; 



    for(int i=start_rows;i<end_rows; i++){
        for(int j=start_cols;j<end_cols;j++){


            auto &id_t_m32 = id_m32.row(i-start_rows).col(j-start_cols);
            auto &id_t_m64 = id_m64.row(i-start_rows).col(j-start_cols);

            bool flag_equal = true; 

            int cnt_channels = 0; 
            for (int c=0;c<channels;c++){
                if ( id_t_m32.data[c]  == id_t_m64.data[c] ) {cnt_channels++;}
                else { flag_equal = false; break; }

            }

            // cout << "cnt_channels:\n" << cnt_channels <<endl; 

            if ( flag_equal ){
                correct_point_cnt++; 
            }

            // cout << "- correct_point_cnt:\n" << correct_point_cnt << endl ; 
        } // end for j 

    } // end for i

    int all_point_num = end_rows*end_cols; 

    //cout << all_point_num << " ==? "  << correct_point_cnt << endl; 

    if ( all_point_num != correct_point_cnt ){
        printf("all_point_num != correct_point_cnt\n%d ! =%d\n", all_point_num , correct_point_cnt ); 
    }
    ret_f = (float)correct_point_cnt/(float)all_point_num*1.0f; 



    return ret_f; 

}



bool c_is_value_path_c(char c){
    bool ret_t = ( ( c>='0'&& c<='9' ) || (c>='a' && c<='z') || (c>='A' && c<='Z') || (c=='_') || ( c=='\\') || (c=='/') || (c==':')||(c=='.') ); 
    return ret_t; 
}



vector<string> split_2_words(string& line){

    vector<string> id_word_str ;

    auto *line_c = line.c_str(); 

    auto loc_start = line.find_first_of("<"); 
    auto loc_end = line.find_last_of(">"); 


    string roi_str = string(line_c+loc_start+1, line_c+loc_end ); 

    //cout << "- roi_str"<<roi_str << endl; 

    auto roi_c = roi_str.c_str(); 


    int loc_w_start = 0; 
    int loc_w_end = 0; 

    int flag_start = false ; 

    int flag_end = false ; 



    int cnt =0;
    for ( auto c: roi_str){
        if( !flag_start  && c_is_value_path_c(c) ) {
            flag_start = true; 
            loc_w_start = cnt;

        }

        if( flag_start && !(c_is_value_path_c(c))  ){
            flag_end = true; 
            loc_w_end = cnt ; 

        }

        if ( flag_start && c==roi_c[roi_str.size() - 1] ){
            flag_end = true; 
            loc_w_end = cnt+1; 

        }

        if  (flag_start && flag_end){
            id_word_str.push_back( string(roi_c+loc_w_start, roi_c+loc_w_end) );
            flag_start = false ; 
            flag_end = false; 
        }


        cnt++ ; 
    } // end for 



    //printf("\n---start---\n"); 
    for ( auto t: id_word_str ){
        cout << t << endl; 
    }
    return id_word_str; 
}


Mat sub_abs_mat(Mat id_m32, Mat id_m64){
    Mat id_mm = cv::abs(id_m32 - id_m64) ; 
    return id_mm; 

}

void strong_img(Mat id_m){

    for (int i=0;i<id_m.rows;i++){
        for(int j=0;j<id_m.cols;j++){
            for (int k=0;k< id_m.channels();k++){
                auto t = (id_m.row(i).col(j)).data; 
                if (t[k]!=0) {t[k]=255;}
            }
        }
    }

}



vector<string>  show_img_diff_and_accumuate(Mat& id_m){
    vector<string> id_vec; 

    char buf[111] = {0};

    long long int acc_ret = 0; 
    char *RGB_STR="RGB";
    for (int i=0;i<id_m.rows;i++){
        for(int j=0;j<id_m.cols;j++){
            for (int k=0;k< id_m.channels();k++){
                auto t = (id_m.row(i).col(j)).data; 
                acc_ret += t[k]; 
                char LR_ = '\n';
                if ( t[k]!=0){
                    sprintf_s(buf, "(%d,%d,%c=%d)", i, j ,RGB_STR[k], t[k] );
                    string tstr = string(buf); 
                    id_vec.push_back( tstr ); 
                }
            }
        }
    } // end for i 
    sprintf_s(buf, "accumuation all is %d", acc_ret ); 
    id_vec.push_back( buf );
    return id_vec; 
}

void print_mat_info(Mat& id_m){
    int rows = id_m.rows; 
    int cols = id_m.cols; 
    cout << "- rows : "<< rows<< endl; 
    cout << "- cols : "<< cols<< endl; 
    cout << "- channels : "<< id_m.channels() << endl << endl; ; 
}


/////////////
void show_id_m(Mat id_m){
    namedWindow("image", CV_WINDOW_AUTOSIZE);  
    imshow("image", id_m);  
    // waitKey(0); 
}


///////