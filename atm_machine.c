/*
Code Challenge
Use any language you wish for this challenge.
You have been asked to design the code for an ATM machine. Another group will be creating the interface. 
Your task is only to create the code portion.

Requirements:
-Assume a starting balance (make it up yourself)
-Start with withdrawal functionality in denominations of 20’s
-Do not allow transactions that will cause a negative balance.

Extra credit: (Not required)
-Dispense other denominations
-Allow account to go negative and charge a fee

Post your solution on Github and email me the link to your repo.
*/

#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include "atm_machine.h"

#define DEBUG
const int valid_denomination = 20;


int main()
{
   atm atm1;
   atm* atm_null = NULL;

   //Test 1 : Null Pointer
   printf("Test 1: \n");
   atm_deposit(atm_null, 400);
     
   //Test 2 : Uninitialized Pointer
   printf("\nTest 2: \n");
   atm_deposit(&atm1, 300);

   //Test 3 : Initialize ATM with negative/less than valid denomination
   printf("\nTest 3: \n");
   atm_init(&atm1, -500);
   atm_init(&atm1, 10);

   //Test 4 : Initialize ATM with zero amount
   printf("\nTest 4: \n");
   atm_init(&atm1, 400);

   //Test 5 : Get Balance
   printf("\nTest 5: \n");
   int curr_balance = get_balance(&atm1);

   //Test 6 : Deposit Negative Amount
   printf("\nTest 6: \n");
   atm_deposit(&atm1, -500);

   //Test 7 : Deposit Zero/Positive Amount
   printf("\nTest 7: \n");
   atm_deposit(&atm1, 0);
   atm_deposit(&atm1, 250);

   //Test 8 : Check Update Balance Function with negative value
   printf("\nTest 8: \n");
   update_balance(&atm1, -10);

   //Test 9 : Check Update Balance Function with zero or positive value
   printf("\nTest 9: \n");
   update_balance(&atm1, 0);
   update_balance(&atm1, 700);

   //Test 10 : Withdraw Negative/Zero/Less Than Valid Denomination
   printf("\nTest 10: \n");
   int twenty_notes = 0;
   withdraw_amt(&atm1, -20, &twenty_notes);
   withdraw_amt(&atm1, 0, &twenty_notes);
   withdraw_amt(&atm1, 10, &twenty_notes);

   //Test 11 : Withdraw Positive Amount Greater Than Current Balance
   printf("\nTest 11: \n");
   curr_balance = get_balance(&atm1);
   curr_balance += 100;
   withdraw_amt(&atm1, curr_balance, &twenty_notes);
   
   //Test 12 : Positive Amount And In Valid Denominations
   printf("\nTest 12: \n");
   int w_amt = 500;
   withdraw_amt(&atm1, w_amt, &twenty_notes);

   //Test 13: Positive Amount But Not In Multiples Of Valid Denominations
   printf("\nTest 13: \n");
   atm_deposit(&atm1, 200);
   withdraw_amt(&atm1, 231, &twenty_notes);
   get_balance(&atm1);
}

bool check_valid_atm(atm* atm1)
{
    if(!atm1)
    {
        #ifdef DEBUG
        printf("ATM Does Not Exist\n");
        #endif
        return false;
    }
    else
    {
        return true;
    }
}

bool is_atm_init(atm* atm)
{
    if(! (atm->atm_init) )
    {
        #ifdef DEBUG
        printf("ATM Does Not Exist\n");
        #endif
        return false;
    }
    else //ATM Machine Is Initialized
    {
        return true;
    }
}

bool atm_init(atm* atm1, int initial_amt)
{
    if(!check_valid_atm(atm1))
    {
        return false;
    }

    if(initial_amt > valid_denomination)
    {
        atm1->total_amt = initial_amt;
        #ifdef DEBUG
        printf("ATM initialized with %d\n", atm1->total_amt);
        #endif
        atm1->atm_init = true;
        return true;
    }
    else
    {
        atm1->total_amt = 0;
        #ifdef DEBUG
        printf("Invalid Initial Amount : %d\nPlease Deposit Amount Above Valid Denomination\n", initial_amt);
        #endif
        atm1->atm_init = true;
        return false;
    }
}

bool atm_deposit(atm* atm1, int deposit_amt)
{
    if(!check_valid_atm(atm1))
    {
        return false;
    }

    if(!is_atm_init(atm1))
    {
        return false;
    }

    if(deposit_amt > 0)
    {
        atm1->total_amt += deposit_amt;
        #ifdef DEBUG
        printf("Amount Deposited: %d\n", deposit_amt);
        printf("Total Amount In Account: %d\n", atm1->total_amt);
        #endif
        return true;
    }
    else
    {
        #ifdef DEBUG
        printf("Amount To Be Deposited Invalid\n", deposit_amt);
        printf("Total Amount In Account: %d\n", atm1->total_amt);
        #endif
        return false;
    }
}

bool update_balance(atm* atm1, int upd_amt)
{
    if(!check_valid_atm(atm1))
    {
        return false;
    }

    if(!is_atm_init(atm1))
    {
        return false;
    }

    if(upd_amt >= 0)
    {
        atm1->total_amt = upd_amt;
        #ifdef DEBUG
        printf("Account Balance Set To : %d\n", atm1->total_amt);
        #endif
        return true;
    }
    else
    {
        #ifdef DEBUG
        printf("Invalid Update Amount: %d\n", upd_amt);
        #endif
        return false;
    }
}

int get_balance(atm* atm1)
{
    if(!check_valid_atm(atm1))
    {
        return -1;
    }

    if(!is_atm_init(atm1))
    {
        return -1;
    }

    #ifdef DEBUG
    printf("ATM Balance: %d\n", atm1->total_amt);
    #endif
    return atm1->total_amt;
}

bool withdraw_amt(atm* atm1, int amt_to_be_withdrawn, int* twenty_notes)
{
    if(!check_valid_atm(atm1))
    {
        *twenty_notes = 0;
        return false;
    }

    //Get Current Balance
    int curr_balance = get_balance(atm1);
    
    //Check If Amount Is Less Than 20
    if( (amt_to_be_withdrawn < valid_denomination) )
    {
        printf("Amount Less Than Valid Denomination\n");
        *twenty_notes = 0;
        return false;
    }
    
    //Check if Valid Amount Present in ATM
    if(curr_balance < valid_denomination)
    {
        *twenty_notes = 0;
        printf("Insufficient Balance in ATM. Amount Cannot Be Withdrawn\n");
        return false;
    }
    
    //Check If amt to be withdrawn is less than current balance
    if(amt_to_be_withdrawn > curr_balance)
    {
        *twenty_notes = 0;
        printf("Amount To Be Withdrawn : %d Is Greater Than the amount present in ATM : %d\n", amt_to_be_withdrawn, curr_balance);
        return false;
    }
    else //Amount to be withdrawn is less than or equal to current balance.
    {
        //Find If Total Amount Can Be Given
        if( (amt_to_be_withdrawn % valid_denomination) == 0 )
        {
            *twenty_notes = amt_to_be_withdrawn / valid_denomination;
            int new_balance = curr_balance - amt_to_be_withdrawn;
            if( !update_balance(atm1, new_balance) )
            {
                return false;
            }
            return true;
        }
        else //Complete Amount Cannot Be Given
        {
            *twenty_notes = amt_to_be_withdrawn / valid_denomination;
            int new_balance = curr_balance - (*twenty_notes * valid_denomination);
            char test;
            printf("Balance does not contain valid denomination.\nCan Withdraw %d\nDo you want to withdraw?, y(yes)/n(no): \n", *twenty_notes * valid_denomination);
            scanf("%c", &test);

            if(test == 'y')
            {
                //Update Balance
                if(!update_balance(atm1, new_balance))
                {
                    return false;
                }
                return true;
            }
            else
            {
                //As No was the answer, give zero notes.
                *twenty_notes = 0;
                return false;
            }
        }
    }
}
