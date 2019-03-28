#ifndef ATMMACHINE_H
#define ATMMACHINE_H

typedef struct atm{
    int total_amt;
    bool atm_init;
}atm;

bool check_valid_atm(atm* atm1);
bool is_atm_init(atm* atm);
bool atm_init(atm* atm1, int initial_amt);
bool atm_deposit(atm* atm1, int deposit_amt);
bool update_balance(atm* atm1, int upd_amt);
int get_balance(atm* atm1);
bool withdraw_amt(atm* atm1, int amt_to_be_withdrawn, int* twenty_notes);

#endif