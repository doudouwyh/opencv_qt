#include <QCoreApplication>

int bgfg_gmg_test();
int bgfg_segm_test();
int brief_match_test();
int build3d_module_test();
int camshift_test();
int chamfer_test();
int connectd_components_tset();
int contour2_test();
int convexhull_test();
int delaunay2_test();
int demhist_test();
int descriptor_extractor_macher_test();
int detector_descriptor_evaluation_test();
int dft_test();
int distrans_test();
int edge_test();
int em_test();
int fabmap_test();
int facerec_test();
int facial_features_test();
int fback_test();
int floodFill_test();
int fitellipse_test();
int fast_retina_keypoint_test();
int gencolor_test();
int match_keypoints_tset();
int grabcut_test();
int houghcircle_test();
int houghline_test();
int hybridtracking_test();
int inpaint_test();
int kalman_test();
int kmean_test();
int laplace_test();
int latent_svm_test();
int letter_recog_test();
void generate_feature_test();

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //bgfg_gmg_test();
    //bgfg_segm_test();
    //brief_match_test();  //failed!!!
    //build3d_module_test(); //failed !,should have a camera
    //camshift_test();
    //chamfer_test();
    //connectd_components_tset();
    //contour2_test();
    //convexhull_test();
    //delaunay2_test();
    //demhist_test();
    //descriptor_extractor_macher_test();
    //detector_descriptor_evaluation_test();
    //dft_test();
    //distrans_test();
    //edge_test();
    //em_test();
    //fabmap_test();
    //facerec_test();
    //facial_features_test();
    //fback_test();
    //floodFill_test();
    //fitellipse_test();
    //fast_retina_keypoint_test();
    //gencolor_test();
    //match_keypoints_tset(); //failed!!!!
    //grabcut_test();
    //houghcircle_test();
    //houghline_test();
    //hybridtracking_test();
    //inpaint_test( );
    //kalman_test();
    //kmean_test();
    //laplace_test();
    //latent_svm_test();
    //letter_recog_test();

    generate_feature_test();

    return a.exec();
}
