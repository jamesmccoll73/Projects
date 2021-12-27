#include "company.cpp"
#include <iostream>
using namespace std;

int main (int argc, char* argv[]) {
   
    CompanyTracker comps(5);
    //Testing that splitting single person companies does nothing
    comps.split(0);
    cout << "Should be false: " << comps.inSameCompany(0,1) << endl;
    
    //Testing general things, confirming merge and split work
    cout << "Should be false: " << comps.inSameCompany(0,1) << endl;
    comps.merge(0,1);
    cout << "Should be true: " << comps.inSameCompany(0,1) << endl;

    comps.merge(0,2);
    cout << "Should be true: " << comps.inSameCompany(1,2) << endl;

    comps.split(0);
    cout << "Should be false: " << comps.inSameCompany(0,2) << endl;
    cout << "Should be true: " << comps.inSameCompany(0,1) << endl;

    //Testing that merge works well with only merging seperate companies 
    //then testing middle intersection
    CompanyTracker busi(4);
    busi.merge(0,1);
    busi.merge(2,3);
    busi.merge(0,3);
    cout << "Should be true: " << busi.inSameCompany(1,2) << endl;

    //Confirming you can merge multiple times without running into problem
    busi.merge(1,2);
    busi.merge(1,2);
    busi.merge(1,2);
    busi.split(0);
    cout << "Should be false: " << busi.inSameCompany(1,2) << endl;

}
