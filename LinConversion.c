#include<stdio.h>

typedef unsigned char      U8;
typedef unsigned short     U16;
typedef unsigned int       U32;
typedef unsigned long long U64;

typedef signed char        S8;
typedef signed short       S16;
typedef signed int         S32;
typedef signed long long   S64;

typedef float              F32;
typedef double             F64;




U32 ScaleAnalogIn_mA_Bar( S16 InputValue,
                          S16 ParMinmAValue,
                          S16 ParMaxmAValue,
                          U32 ParMinBarValue,
                          U32 ParMaxBarValue
                          )
{
   if(InputValue < ParMinmAValue)
   {
      InputValue = ParMinmAValue;
   }
   else if (InputValue > ParMaxmAValue)
   {
      InputValue = ParMaxmAValue;
   }

   printf("\n\nIn - InMin = %llu\n", ((U64)InputValue - (U64)ParMinmAValue));
   printf("MaxBar - MinBar = %i\n", (ParMaxBarValue - ParMinBarValue));
   printf("(In - InMin) * (MaxBar - MinBar) = %llu\n",
         ((U64)InputValue - (U64)ParMinmAValue) *
         (ParMaxBarValue - ParMinBarValue));
   printf("InMax - InMin = %llu\n", ((U64)ParMaxmAValue-(U64)ParMinmAValue));
   return (U32)((U64)InputValue - (U64)ParMinmAValue) *
         (ParMaxBarValue - ParMinBarValue) /
         ((U64)ParMaxmAValue-(U64)ParMinmAValue) + ParMinBarValue;
}

int main(void)
{
  static S64 OutputValue;
  static S64 InputValue = 7000;

  static S64 InMinValue = 4000;
  static S64 InMaxValue = 20000;
  static S64 OutMinValue = 0;
  static S64 OutMaxValue = 100000;
  static S64 scaleVal = 1000;


   OutputValue = (U32)((InputValue - InMinValue) *
         (OutMaxValue - OutMinValue) / (InMaxValue - InMinValue)) + OutMinValue;

   printf("Input Value %.3f,\nOutput Value %.3f\n",
         (F64)InputValue / scaleVal,
         (F64)OutputValue / scaleVal);
   printf("\n\nIn Min Value %.3f,\nIn Max Value %.3f\n",
         (F64)InMinValue / 1000,
         (F64)InMaxValue / 1000);
   printf("\n\nOut Min Value %.3f,\nOut Max Value %.3f\n",
         (F64)OutMinValue / 1000,
         (F64)OutMaxValue / 1000);

   S16 InputValueHydrPres = 15000;
   S16 ParMinmAValueHydrPres = 4000;
   S16 ParMaxmAValueHydrPres = 20000;
   U32 ParMinBarValueHydrPres = 0;
   U32 ParMaxBarValueHydrPres = 400000;

   printf("\n\tTest Hydr Driver.\nInput Curr.: %i\nOut Press.: %i",
         InputValueHydrPres,
         ScaleAnalogIn_mA_Bar(InputValueHydrPres,
                              ParMinmAValueHydrPres,
                              ParMaxmAValueHydrPres,
                              ParMinBarValueHydrPres,
                              ParMaxBarValueHydrPres
                              )
         );

   printf("\n\ntest hub unit press measurement\n\n");

   InMinValue = 4000;
   InMaxValue = 20000;
   OutMinValue = 0;
   OutMaxValue = 40000; //400.00 Bar
   InputValue = 20000;
   scaleVal = 100;
   U16 inValScale = 1000;

   OutputValue = (S32) ( (S32) ( InputValue - InMinValue )
         * (S32)( OutMaxValue - OutMinValue )
         / (S32)( InMaxValue - InMinValue ) + OutMinValue );
//   OutputValue += offset;

   printf("Input Value %.3f,\nOutput Value %.2f\n",
         (F64)InputValue / inValScale,
         (F64)OutputValue / scaleVal);
   printf("\n\nIn Min Value %.3f,\nIn Max Value %.2f\n",
         (F64)InMinValue / inValScale,
         (F64)InMaxValue / inValScale);
   printf("\n\nOut Min Value %.2f,\nOut Max Value %.2f\n",
         (F64)OutMinValue / scaleVal,
         (F64)OutMaxValue / scaleVal);


   printf("\n\nTest Pitch Angular Encoders\n\n");
   U16 message = 0;
   U16 P_EncoderRSA597InMin = 0;
   U16 P_EncoderRSA597InMax = 8191;
   U16 P_EncoderRSA597OutMax = 36000;
   U16 P_EncoderRSA597OutMin = 0;
   S16 P_EncoderRSA597Offset = -100;
   U16 ValScale = 10;

   S32 encPos;

   encPos = (S32)((((U32)( message - P_EncoderRSA597InMin) *
            (P_EncoderRSA597OutMax - P_EncoderRSA597OutMin)) /
            (U32)(P_EncoderRSA597InMax - P_EncoderRSA597InMin)) +
            P_EncoderRSA597OutMin );

   encPos = encPos / 10 + P_EncoderRSA597Offset;

   printf("Input Value %i,\nOutput Value %.1f\n",
         message,
         (F64)encPos / ValScale);
   printf("\n\nIn Min Value %i,\nIn Max Value %i\n",
         P_EncoderRSA597InMin,
         P_EncoderRSA597InMax);
   printf("\n\nOut Min Value %.1f,\nOut Max Value %.2f\n",
         (F64)P_EncoderRSA597OutMin / ValScale,
         (F64)P_EncoderRSA597OutMax / 100);


   return 0;
}
