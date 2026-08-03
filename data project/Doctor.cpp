#include "doctor.h"
#include "Patient.h"
#include <iostream>

doctor::doctor()
    : id(0), branch(0), current_state(shift_not_started), treated_patients(0),
      end_treatment(0), endbreak(0), docspec('J'), shst_t(0),
      breakafter(0), break_duration(0), current_patient(nullptr) {}

doctor::doctor(int d_id, int d_branch, char spec, int shift_start, int break_after, int break_dur)
    : id(d_id), branch(d_branch), treated_patients(0), end_treatment(0),
      endbreak(0), docspec(spec), shst_t(shift_start), breakafter(break_after),
      break_duration(break_dur), current_patient(nullptr) {
    
    
    if (shst_t == 0) {
        current_state = idle;
    } else {
        current_state = shift_not_started;
    }
}

int doctor::get_id() const { return id; }
int doctor::get_branch() const { return branch; }
docstate doctor::get_cs() const { return current_state; }
int doctor::get_tp() const { return treated_patients; }
int doctor::get_et() const { return end_treatment; }
int doctor::get_eb() const { return endbreak; }
int doctor::get_shst_t() const { return shst_t; }
char doctor::get_docspec() const { return docspec; }
Patient* doctor::get_current_patient() const { return current_patient; }


void doctor::set_id(int d_id) { id = d_id; }
void doctor::set_branch(int d_branch) { branch = d_branch; }
void doctor::set_cs(docstate a) { current_state = a; }
void doctor::set_docspec(char a) { docspec = a; }
void doctor::set_treated(int a) { treated_patients = a; }
void doctor::set_endt(int a) { end_treatment = a; }
void doctor::set_eb(int a) { endbreak = a; }
void doctor::set_shst_t(int t) { shst_t = t; }



bool doctor::is_available(int currentTime) {
    update_state(currentTime);
    return (current_state == idle);
}

void doctor::update_state(int currentTime) {
    
    if (current_state == shift_not_started) {
        if (currentTime >= shst_t) {
            current_state = idle;
        }
        return;
    }

    
    if (current_state == busy) {
        if (currentTime >= end_treatment) {
            current_patient = nullptr; 

            
            if (breakafter > 0 && treated_patients >= breakafter) {
                current_state = onbreak;
                endbreak = currentTime + break_duration;
                treated_patients = 0; 
            } else {
                current_state = idle;
            }
        }
    }

  
    if (current_state == onbreak) {
        if (currentTime >= endbreak) {
            current_state = idle;
        }
    }
}

void doctor::assign_patient(Patient* p, int currentTime, int setup_dur, int wrap_dur, int per_test_dur) {
    if (p == nullptr) return;

    current_patient = p;
    treated_patients++;


    int visit_time = setup_dur + wrap_dur + (p->getNumTest() * per_test_dur);
    
    
    int waiting_time = currentTime - p->getCheckInTime();

    p->setWaitingTime(waiting_time);
    p->setVisitTime(visit_time);

    end_treatment = currentTime + visit_time;
    current_state = busy;
    p->setFinshTime(end_treatment);
}

void doctor::print(int currentTime) const {
    std::cout << "Dr " << docspec << id << ": ";

    switch (current_state) {
        case shift_not_started:
            std::cout << "shift not started yet";
            break;
        case idle:
            std::cout << "free";
            break;
        case busy:
            std::cout << "busy until t=" << end_treatment;
            break;
        case onbreak:
            std::cout << "on break until t=" << endbreak;
            break;
    }
}