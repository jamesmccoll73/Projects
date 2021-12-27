#ifndef COMPANY_H
#define COMPANY_H

struct Company {
  // the parent company, or nullptr if it has no parent.
  Company *parent;

  // the subcompanies that were merged to obtain this company.
  // nullptr if this is a 1-student company.
  Company *merge1, *merge2;

  Company()
    : parent(nullptr)
    , merge1(nullptr)
    , merge2(nullptr)
  {}

  Company(Company *m1, Company *m2)
    : parent(nullptr)
    , merge1(m1)
    , merge2(m2)
  {}
};

class CompanyTracker {
public:
  
  // initializes the tracker with n students and their 1-person companies
  CompanyTracker(int n);

  // deallocates all dynamically allocated memory
  ~CompanyTracker();

  /** Merges the largest companies containing students i and j.
   *
   * Generates a new Company object which will become the parent company of
   * the largest companies currently containing students i and j. If i and j
   * already belong to the same company (or are the same), merge doesn't do
   * anything. If either i or j are out of range, merge doesn't do anything.
   */
  void merge(int i, int j);

  /** Splits the largest company that student i belongs to.
   *
   * Deletes that Company object, and makes sure that the two subcompanies
   * have no parent afterwards. If i's largest company is a 1-person company,
   * split doesn't do anything. If i is out of range, split doesn't do
   * anything.
   */
  void split(int i);

  /** Returns whether students i and j are currently in the same company.
   *
   * Returns true if i == j. Returns false if i or j (or both) is out of range.
   */
  bool inSameCompany(int i, int j);

private:
  // The number of companies you are tracking
  int numCompanies;

  /** An array of pointers to all the 1-person companies.
   *
   * Allocated in the constructor. Will not contain the merged companies.
   */
  Company** companies;


  Company* largestCompany(Company* comp)
  {
    Company* temp = comp;
    while(temp -> parent != nullptr){
      temp = temp -> parent;
    }
    return temp;
  }
  /** Feel free to add private helper functions as you see fit.
   *
   * In particular, you may want a function to find the largest company
   * that a student i is part of.
   */
};

#endif
