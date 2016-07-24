

/*
 * Include Files
 *
 */
#if defined(MATLAB_MEX_FILE)
#include "tmwtypes.h"
#include "simstruc_types.h"
#else
#include "rtwtypes.h"
#endif

/* %%%-SFUNWIZ_wrapper_includes_Changes_BEGIN --- EDIT HERE TO _END */
# ifndef MATLAB_MEX_FILE

# include <Arduino.h>

typedef struct { int pinA; int pinB; int pos;} Encoder;    
volatile Encoder Enc[3] = {{0,0,0}, {0,0,0}, {0,0,0}};


/* Interrupt Service Routine: rising on pin A for Encoder 0  */
void irsPinAEn0(){
  /* read pin B right away                                   */
  int drB = digitalRead(Enc[0].pinB);
  /* this updates the counter                                */
  /* low->high on A */   
  if (drB == LOW) {  /* check pin B */
  	Enc[0].pos++;  /* going clockwise: increment         */
  } else {
  	Enc[0].pos--;  /* going counterclockwise: decrement  */
  }
} /* end ISR pin A Encoder 0                                 */


/* Interrupt Service Routine: rising on pin A for Encoder 2  */
void irsPinAEn1(){

  /* read pin B right away                                   */
  int drB = digitalRead(Enc[1].pinB);
  /* this updates the counter                                */      
  if (drB == LOW) {  /* check pin B */
  	Enc[1].pos--;  /* going clockwise: increment         */
  } else {
  	Enc[1].pos++;  /* going counterclockwise: decrement  */
  }
} /* end ISR pin A Encoder 2                                 */

# endif
/* %%%-SFUNWIZ_wrapper_includes_Changes_END --- EDIT HERE TO _BEGIN */
#define y_width 1
/*
 * Create external references here.  
 *
 */
/* %%%-SFUNWIZ_wrapper_externs_Changes_BEGIN --- EDIT HERE TO _END */
/* extern double func(double a); */
/* %%%-SFUNWIZ_wrapper_externs_Changes_END --- EDIT HERE TO _BEGIN */

/*
 * Output functions
 *
 */
void Read_Quad_Encoders_Outputs_wrapper(real_T *x1,
			real_T *x2,
			const real_T *xD,
			const uint8_T  *enc, const int_T  p_width0,
			const uint8_T  *pinA, const int_T  p_width1,
			const uint8_T  *pinB, const int_T  p_width2)
{
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_BEGIN --- EDIT HERE TO _END */
/* This sample sets the output equal to the input
      y0[0] = u0[0]; 
 For complex signals use: y0[0].re = u0[0].re; 
      y0[0].im = u0[0].im;
      y1[0].re = u1[0].re;
      y1[0].im = u1[0].im;
*/

/* wait until after initialization is done */
if (xD[0]==1) {
    
    /* don't do anything for mex file generation */
    # ifndef MATLAB_MEX_FILE
            
        /* get encoder position and set is as output */
        x1[0]=Enc[enc[0]].pos;
        x2[0]=Enc[enc[1]].pos;

    # endif
    
}
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_END --- EDIT HERE TO _BEGIN */
}

/*
  * Updates function
  *
  */
void Read_Quad_Encoders_Update_wrapper(const real_T *x1,
			const real_T *x2,
			real_T *xD,
			const uint8_T  *enc,  const int_T  p_width0,
			const uint8_T  *pinA,  const int_T  p_width1,
			const uint8_T  *pinB,  const int_T  p_width2)
{
  /* %%%-SFUNWIZ_wrapper_Update_Changes_BEGIN --- EDIT HERE TO _END */
/*
 * Code example
 *   xD[0] = u0[0];
*/

if (xD[0]!=1) {
    
    /* don't do anything for mex file generation */
    # ifndef MATLAB_MEX_FILE
    
        /* enc[0] is the encoder number and it can be 0,1 or 2   */
        /* if other encoder blocks are present in the model      */
        /* up to a maximum of 3, they need to refer to a         */
        /* different encoder number                              */
            
        /* store pinA and pinB in global encoder structure Enc   */
        /* they will be needed later by the interrupt routine    */
        /* that will not be able to access s-function parameters */   

        Enc[enc[0]].pinA=pinA[0];      /* set pin A              */
        Enc[enc[0]].pinB=pinB[0];      /* set pin B              */
        Enc[enc[1]].pinA=pinA[1];      /* set pin A              */
        Enc[enc[1]].pinB=pinB[1];      /* set pin B              */
		
        /* set encoder pins as inputs                            */
        pinMode(Enc[enc[0]].pinA, INPUT); 
        pinMode(Enc[enc[0]].pinB, INPUT); 
        pinMode(Enc[enc[1]].pinA, INPUT); 
        pinMode(Enc[enc[1]].pinB, INPUT); 
        
        /* turn on pullup resistors                              */
        digitalWrite(Enc[enc[0]].pinA, HIGH); 
        digitalWrite(Enc[enc[0]].pinB, HIGH); 
        digitalWrite(Enc[enc[1]].pinA, HIGH); 
        digitalWrite(Enc[enc[1]].pinB, HIGH); 
		
        /* attach interrupts                                     */
        attachInterrupt(Enc[0].pinA,irsPinAEn0,RISING);
        attachInterrupt(Enc[1].pinA,irsPinAEn1,RISING);

        # endif
    
    /* initialization done */ 
    xD[0]=1;
}
/* %%%-SFUNWIZ_wrapper_Update_Changes_END --- EDIT HERE TO _BEGIN */
}
