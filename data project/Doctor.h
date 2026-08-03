#include "Patient.h"
#pragma once
enum docstate {
	idle,
	busy,
	onbreak,
	shift_not_started 
};
class doctor {
private:
    int id;
    int branch;
    docstate current_state;
    int treated_patients;
    int end_treatment;
    int endbreak;
    char docspec;
    Patient* current_patient;

public:
    int shst_t;
    int breakafter;
    int break_duration;

    
    doctor();
    doctor(int d_id, int d_branch, char spec, int shift_start, int break_after, int break_dur);

    
    int get_id() const;
    int get_branch() const;
    docstate get_cs() const;
    int get_tp() const;
    int get_et() const;
    int get_eb() const;
    int get_shst_t() const;
    char get_docspec() const;
    Patient* get_current_patient() const;

    
    void set_id(int d_id);
    void set_branch(int d_branch);
    void set_cs(docstate a);
    void set_docspec(char a);
    void set_treated(int a);
    void set_endt(int a);
    void set_eb(int a);
    void set_shst_t(int t);

    
    bool is_available(int currentTime);
    void update_state(int currentTime);
    void assign_patient(Patient* p, int currentTime, int setup_dur, int wrap_dur, int per_test_dur);
    void print(int currentTime) const;
};
