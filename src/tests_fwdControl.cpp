/* 
 * Copyright 2014 FLR Team. Distributed under the GPL 2 or later
 * Maintainer: Finlay Scott, JRC
 */

#include "../../inst/include/fwdControl.h"

//'@title Tests for CPP implementation of fwdControl
//
//' Once around the sun
//'@param fc a parameter
//'@param control something
//'@param fc1 something
//'@param target_no something
//'@param sim_target_no something
//'@param col something
//'@param biol_no something
//'@param fishery_no something
//'@param catch_no something
//'@param relative something
//'@param check something
//'@rdname fwdControl-cpp-tests
// [[Rcpp::export]]
fwdControl test_as_wrap_fwdControl(fwdControl control){
    return control;
}

// Checking that a deep copy has been made
// Not so important as we not actually changing any of these values
// In fact we don't have any 'write' accessors for this class
//'@rdname fwdControl-cpp-tests
// [[Rcpp::export]]
Rcpp::List test_fwdControl_copy_constructor(fwdControl fc1){
    // Just make a copy
	fwdControl fc2(fc1); 
	return Rcpp::List::create(Rcpp::Named("fc1", fc1),
                            Rcpp::Named("fc2",fc2));
}

//'@rdname fwdControl-cpp-tests
// [[Rcpp::export]]
fwdControl test_fwdControl_assignment_operator(fwdControl fc){
    fwdControl out;
    out = fc;
    return out;
}

//'@rdname fwdControl-cpp-tests
// [[Rcpp::export]]
Rcpp::DataFrame test_fwdControl_get_target(const fwdControl control){
    return control.get_target();
}

//'@rdname fwdControl-cpp-tests
// [[Rcpp::export]]
int test_fwdControl_get_ntarget(const fwdControl control){
    return control.get_ntarget();
}

//'@rdname fwdControl-cpp-tests
// [[Rcpp::export]]
int test_fwdControl_get_niter(const fwdControl control){
    return control.get_niter();
}

//'@rdname fwdControl-cpp-tests
// [[Rcpp::export]]
int test_fwdControl_get_nsim_target(const fwdControl control, unsigned int target_no){
    return control.get_nsim_target(target_no);
}

//'@rdname fwdControl-cpp-tests
// [[Rcpp::export]]
int test_fwdControl_get_target_row(const fwdControl control, unsigned int target_no, unsigned int sim_target_no){
    return control.get_target_row(target_no, sim_target_no);
}

//'@rdname fwdControl-cpp-tests
// [[Rcpp::export]]
std::vector<unsigned int> test_fwdControl_get_target_rows(const fwdControl control, unsigned int target_no){
    return control.get_target_row(target_no);
}

//'@rdname fwdControl-cpp-tests
// [[Rcpp::export]]
Rcpp::IntegerVector test_fwdControl_get_target_int_col(const fwdControl control, const int target_no, const std::string col){
    return control.get_target_int_col(target_no, col);
}

//'@rdname fwdControl-cpp-tests
// [[Rcpp::export]]
int test_fwdControl_get_target_int_col2(const fwdControl control, const int target_no, const int sim_target_no, const std::string col){
    return control.get_target_int_col(target_no, sim_target_no, col);
}

//'@rdname fwdControl-cpp-tests
// [[Rcpp::export]]
Rcpp::NumericVector test_fwdControl_get_target_num_col(const fwdControl control, const int target_no, const std::string col){
    return control.get_target_num_col(target_no, col);
}

//'@rdname fwdControl-cpp-tests
// [[Rcpp::export]]
double test_fwdControl_get_target_num_col2(const fwdControl control, const int target_no, const int sim_target_no, const std::string col){
    return control.get_target_num_col(target_no, sim_target_no, col);
}

//'@rdname fwdControl-cpp-tests
// [[Rcpp::export]]
std::vector<double> test_fwdControl_get_target_value(const fwdControl control, const int target_no, const int col){
    std::vector<double> values =  control.get_target_value(target_no, col);
	return values;
}

//'@rdname fwdControl-cpp-tests
// [[Rcpp::export]]
std::vector<double> test_fwdControl_get_target_value2(const fwdControl control, const int target_no, const int sim_target_no, const int col){
    std::vector<double> values =  control.get_target_value(target_no, sim_target_no, col);
	return values;
}

//'@rdname fwdControl-cpp-tests
// [[Rcpp::export]]
std::string test_fwdControl_get_target_quantity(const fwdControl control, const int target_no, const int sim_target_no){
    return control.get_target_quantity(target_no, sim_target_no);
}

//'@rdname fwdControl-cpp-tests
// [[Rcpp::export]]
std::vector<unsigned int> test_fwdControl_get_age_range(const fwdControl control, const int target_no, const int sim_target_no){
    return control.get_age_range(target_no, sim_target_no);
}

//'@rdname fwdControl-cpp-tests
// [[Rcpp::export]]
Rcpp::IntegerMatrix test_fwdControl_get_FC(const fwdControl control, const int biol_no){
    return control.get_FC(biol_no);
}

//'@rdname fwdControl-cpp-tests
// [[Rcpp::export]]
std::vector<unsigned int> test_fwdControl_get_B(const fwdControl control, const int fishery_no, const int catch_no){
    return control.get_B(fishery_no, catch_no);
}

//'@rdname fwdControl-cpp-tests
// [[Rcpp::export]]
std::vector<unsigned int> test_fwdControl_get_F(const fwdControl control, const int biol_no){
    return control.get_F(biol_no);
}

//'@rdname fwdControl-cpp-tests
// [[Rcpp::export]]
int test_fwdControl_get_FCB_nrow(const fwdControl control){
    return control.get_FCB_nrow();
}

//'@rdname fwdControl-cpp-tests
// [[Rcpp::export]]
int test_fwdControl_get_FCB_row_no(const fwdControl control, const unsigned int fishery_no, const unsigned int catch_no, const unsigned int biol_no){
    return control.get_FCB_row_no(fishery_no, catch_no, biol_no);
}

//'@rdname fwdControl-cpp-tests
// [[Rcpp::export]]
std::vector<int> test_fwdControl_get_FCB_nos(const fwdControl control, const unsigned int target_no, const unsigned int sim_target_no, const bool relative, const bool check){
    std::vector<unsigned int> out;
    out = control.get_FCB_nos(target_no, sim_target_no, relative, check);
    // unsigned int does not like NAs when passing back to R
    std::vector<int> out2(out.begin(), out.end());
    return out2;
}

//'@rdname fwdControl-cpp-tests
// [[Rcpp::export]]
bool test_fwdControl_shared_catch(const fwdControl control, const unsigned int biol_no){
    return control.shared_catch(biol_no);
}



