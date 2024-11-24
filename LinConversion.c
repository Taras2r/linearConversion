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
  static S64 InputValue = 16661; //10mA

  static S64 InMinValue = 4000;
  static S64 InMaxValue = 20000;
  static S64 OutMinValue = 0;
  static S64 OutMaxValue = 100000; //260 Bar
  static S64 scaleVal = 1000;


   OutputValue = (U32)((InputValue - InMinValue) *
         (OutMaxValue - OutMinValue) / (InMaxValue - InMinValue)) + InMinValue;

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

   return 0;
}
