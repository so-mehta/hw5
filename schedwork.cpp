#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool sched_helper(const AvailabilityMatrix& avail, const size_t dailyNeed, 
    const size_t maxShifts, DailySchedule& sched, std::vector<int>& shifts, int slot );

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below

    //first, maintain a matrix of tried attempts

    // AvailabilityMatrix attempts = avail;
    // std::vector<int> shifts_reg;
    
    //if the value for a particular unit is -1, that means it has been attempted


    //start with day1
    int num_nurse = avail[0].size(); //num of nurses
    int size = avail.size(); //number of days
    //initialize sched to have enough space 
    for (int i = 0; i < size; i++){
        std::vector<Worker_T> day(dailyNeed, INVALID_ID);
        sched.push_back(day);
    }

    std::vector<int> shifts(num_nurse, 0);
    return sched_helper(avail, dailyNeed, maxShifts, sched, shifts, 0);


}

bool sched_helper(const AvailabilityMatrix& avail, const size_t dailyNeed, 
    const size_t maxShifts, DailySchedule& sched, std::vector<int>& shifts, int slot ){

        int num_days = avail.size();
        int num_nurses = avail[0].size();
        int slots = num_days * dailyNeed;


        if (slot == slots){
            return true;
        }

        //calculate the row of sched matrix
        int day = slot /dailyNeed;
        //calculate the column of the schedule matrix
        int indexInDay = slot % dailyNeed;

        for (int i = 0; i < num_nurses; i++){
            if (avail[day][i] && (shifts[i] < maxShifts)){ //nurse is available, hasn't reached max shifts
                
                bool flag = false;
                //Case 1: nurse already assigned for that slot
                for (int j = 0; j < dailyNeed; j++){
                    if (sched[day][j] == i){
                        flag = true;
                        break;
                    }
                }
                if (flag){
                    continue;
                }
                sched[day][indexInDay] = i;
                shifts[i]++;

                if (sched_helper(avail, dailyNeed, maxShifts, sched, shifts, slot+1)){
                    return true;
                } else {
                    sched[day][indexInDay] = INVALID_ID;
                    shifts[i]--;


                }

            }
        }
        return false;
        





    }