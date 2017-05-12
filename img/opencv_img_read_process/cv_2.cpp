// cv_2.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include "img_proc_algo.h"

using namespace std; 
using namespace cv; 

int _tmain(int argc, char** argv)
{

    printf("%d\n", __LINE__);


    return -1; 
    const int start_rows = 120; 
    const int end_rows = 712; 

    const int start_cols = 188; 
    const int end_cols = 1054 ; 
    auto lines = read_file_2_vec_string( string("X:\\config.txt") ); 
    int cnt_img = 0 ; 
    for ( auto line : lines ){
        if (cnt_img++ > 0 ){break;}
        auto id_word_str = split_2_words( line ); 

        Mat id_m32 = imread(id_word_str[0], IMREAD_COLOR);

        Mat id_m64 = imread(id_word_str[2], IMREAD_COLOR);

        Mat id_rec32 = get_rectangle_mat(id_m32, start_rows,end_rows, start_cols, end_cols); 
        Mat id_rec64 = get_rectangle_mat(id_m64, start_rows,end_rows, start_cols, end_cols); 

        print_mat_info( id_rec32 ); 

        auto rate = percent_of_correct_pixels( id_rec32,  id_rec64); 
        cout << "- rate is "<< rate << endl; 

        auto id_sub_abs_m =  sub_abs_mat(id_rec32,id_rec64);
        vector<string> img_diff_and_acc = show_img_diff_and_accumuate(id_sub_abs_m); 

        for (auto i:img_diff_and_acc){
            cout << i << endl; 
        }

        strong_img(id_sub_abs_m);  // to 255 and show out later
        show_id_m( id_sub_abs_m );
        waitKey();

        cv::rectangle(id_m64, Rect(start_cols, start_rows, end_cols-start_cols+3, end_rows-start_rows+3), Scalar(20,0,255) );
        show_id_m( id_m64); 
        waitKey();


        cv::rectangle(id_m32, Rect(start_cols, start_rows, end_cols-start_cols+3, end_rows-start_rows+3), Scalar(20,0,255) );
        show_id_m( id_m32);
        waitKey();


    }  // end for(:)


    waitKey(0); 

    return 0;
} // end main()






///////