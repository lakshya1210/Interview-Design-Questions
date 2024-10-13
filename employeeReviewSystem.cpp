#include<bits/stdc++.h>
using namespace std;

struct Review{
    int reviewer_id;
    int employee_id;
    double rating;
    string comment;
    string date;

    Review (int reviewerId, int employeeId, double rate, const string& comm, const string& d)
        : reviewer_id(reviewerId), employee_id(employeeId), rating(rate), comment(comm), date(d) {}
};

// struct Employee{
//     int employee_id;

//     Employee(int empId) : employee_id(empId) {}
// };

class PerformanceReviewSystem{
    private:
        //map<int, Employee> employees;
        vector<Review> reviews;
    
    public:
        void insert_performance_review(int self, int employee_id, double rating, const string& comments, const string& review_date_str){
            //employees[employee_id]= Employee(employee_id);

            reviews.push_back(Review(self, employee_id, rating, comments, review_date_str));
        }

        void get_reviews_by_employee_id(int empId){
            bool found = false;
            for(const auto& it:reviews){
                if(it.employee_id == empId){
                    displayReview(it);
                    found= true;
                }
            }
            if(!found){
                cout<<"No Reviews found for Employee with ID "<<empId<<endl;
            }
        }

        double get_average_rating_by_employee_id(int empId){
            double totalRating=0;
            int count=0;
            for(const auto& it: reviews){
                if(it.employee_id == empId){
                    totalRating += it.rating;
                    count++; 
                }
            }
            if(count==0) return 0.0;
            
            return static_cast<double> (totalRating) / static_cast<double>(count);
        }

        void get_reviews_by_reviewer_id(int reviewerId){
            bool found = false;
            for(const auto&it : reviews){
                if(it.reviewer_id == reviewerId){
                    displayReview(it);
                    found = true;
                }
            }
            if(!found){
                cout<<"No reviews found with given reviewerID"<<endl;
            }
        }

        void get_reviews_within_date_range(const string& startDate, const string& endDate){
            

            bool found = false;
            for(const auto& it: reviews){
                if(isDateinRange(it.date, startDate, endDate)){
                    displayReview(it);
                    found = true;
                }
            }
            
            if(!found){
                cout<<"No reviews found in the given date range"<<endl;
            }
        }

        void get_top_performing_employees(int num_emp){
            vector<pair<int, double>> emp;
            for(const auto& it:reviews){
                double avgRating= get_average_rating_by_employee_id(it.employee_id);
                emp.push_back({it.employee_id, avgRating});
            }

            sort(emp.begin(), emp.end(), [](const pair<int, double>&a, const pair<int, double>&b){
                return b.second < a.second;
            });

            for(int i=0;i<min(num_emp, (int)emp.size());i++){
                cout<<"Employee ID : "<<emp[i].first << " With rating of "<< emp[i].second<<endl;
            }
        }

        void displayReview(const Review& review){
            cout<<"ReviewerID : "<< review.reviewer_id<<endl;
            cout<<"EmployeeID : "<< review.employee_id<<endl;
            cout<<"Rating : "<<review.rating<<endl;
            cout<<"Comment : "<<review.comment<<endl;
            cout<<"Date : "<<review.date<<endl;
            cout<<endl;
        }

        bool isDateinRange(const string &given, const string &start, const string& end){
            return given>= start && given<=end;
        }
};


int main(){
    PerformanceReviewSystem prs;

    prs.insert_performance_review(1, 101, 4.5, "Excellent Word", "2024-04-20");
    prs.insert_performance_review(1, 102, 3.8, "Good effort", "2024-04-22");
    prs.insert_performance_review(2, 101, 4.2, "Consistently meets expectations", "2024-04-23");

    prs.insert_performance_review(3, 103, 4.8, "Outstanding performance", "2024-04-25");


    prs.get_reviews_by_reviewer_id(1);
    prs.get_reviews_by_reviewer_id(101);
    prs.get_reviews_within_date_range("2024-04-20", "2024-04-23");
    cout<<"Average rating of Employee with Employee ID "<<102<<" is ";
    cout<<prs.get_average_rating_by_employee_id(102)<<endl;

    prs.get_top_performing_employees(2);
    return 0;
}
