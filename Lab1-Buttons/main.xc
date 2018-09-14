/*
 * main.xc
 *
 *  Created on: Sep 13, 2018
 *      Author: root
 */


#include <xs1.h>
#include <stdio.h>


in port iButton = XS1_PORT_32A;
out port oLed = XS1_PORT_1A;

int main_sampling(){
    unsigned value;
    while(1){
        iButton :> value;
        if(!value%2){
            printf("button pressed");
            //if the value is 0, which means the button is being pressed
            //todo illuminate the led
            //assign the value 1 to the led
            //which turns the led on
            oLed <: 0b1;
        }

        else{
            //printf("button unpressed");
            //if the value of the button is 1
            //give the led a value of 0, off
            oLed <: 0b0;
        }
        //turn off led
    }
    return 0;
}

unsigned int compute_difference(unsigned int t0, unsigned int t1){
    if(t1 < t0){
        t1 += XS1_TIMER_HZ;
    }

    return t1 - t0;
}

int main(){
    unsigned value;
    iButton :> value;
    timer tmr;
    unsigned times[2];
    tmr :> times[0];
    while(1){
        iButton when pinsneq(value) :> value;
        unsigned x = value%2;
        if(x == 0){
            oLed <: 1;
            tmr :> times[1];
        }
        else{
            oLed <: 0;
            tmr :> times[1];
        }
       unsigned total_micro = compute_difference(times[0], times[1]);
       float total_s = (float)total_micro/1000000;
       printf("Delay was %d microseconds (%f seconds)\n", total_micro, total_s);
       times[0] = times[1];

    }
    return 0;
}

