#include "company.hpp"

// Initializes the tracker with n students and their 1-person companies.
CompanyTracker::CompanyTracker(int n)
{
  numCompanies = n;
  companies = new Company* [numCompanies];
  for (int i = 0; i < numCompanies; ++i)
      companies[i] = new Company ();
}

// Deallocates all dynamically allocated memory.
CompanyTracker::~CompanyTracker()
{
  for(int j = 0; j < numCompanies; j++){
    while(companies[j] -> parent != nullptr){
      split(j);
    }
  }
  for(int i = 0; i < numCompanies; i++){
    delete companies[i];
  }
  delete [] companies;
}

void CompanyTracker::merge(int i, int j)
{
  Company* temp1 = companies[i];
  Company* temp2 = companies[j];
  if(inSameCompany(i,j)){
      return;
  }
    
  Company* largeI = largestCompany(temp1);
  Company* largeJ = largestCompany(temp2);
  Company* merger = new Company(largeI, largeJ);
  largeI -> parent = merger;
  largeJ -> parent = merger;
}

void CompanyTracker::split(int i)
{
  Company* largeI = largestCompany(companies[i]);
    if(largeI -> merge1 == nullptr){
      return;
    }
    largeI -> merge1 -> parent = nullptr;
    largeI -> merge2 -> parent = nullptr;
    delete largeI;
}

bool CompanyTracker::inSameCompany(int i, int j)
{
  return largestCompany(companies[i]) == largestCompany(companies[j]);
}