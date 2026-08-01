enum docstate {
	idle,
	busy,
	onbreak,
	shift_not_started 
};
class doctor {
	docstate current_state;
	int treated_patients;
	int end_treatment;
	int endbreak;
	char docspec;
public:
	int shst_t;
	int breakafter;
	int break_duration;
	docstate get_cs() {
		return current_state;
	}
	void set_cs(docstate a) {
		current_state = a;
	}
	void set_docspec(char a) { docspec = a; }

	void set_treated(int a) {
		treated_patients = a;
	}
	void set_endt(int a) {
		end_treatment = a;
	}
	void set_eb(int a) {
		endbreak = a;
	}
	void set_shst_t(int t) {
		shst_t = t;
	}
	int get_tp() {
		return treated_patients;
	}
	int get_et() {
		return end_treatment;
	}
	int get_eb() {
		return endbreak;
	}
	int get_shst_t() {
		return shst_t;
	}
	char get_docspec() {
		return docspec;
	}
	
};
enum patient