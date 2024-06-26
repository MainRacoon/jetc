
#ifndef JETC_TYPES_H
#define JETC_TYPES_H
typedef             char i8;
const i8 I8_MIN=-128;
const i8 I8_MAX=127;
typedef unsigned    char u8;
const u8 U8_MIN=0;
const u8 U8_MAX=255;
typedef             short i16;
const i16 I16_MIN=-32768;
const i16 I16_MAX=32767;
typedef unsigned    short u16;
const u16 U16_MIN=0;
const u16 U16_MAX=65535;
typedef             int i32;
const i32 I32_MIN=-2147483648;
const i32 I32_MAX=2147483647;
typedef unsigned    int u32;
const u32 U32_MIN=0;
const u32 U32_MAX=4294967295;
typedef             long long i64;
const i64 I64_MIN=-9223372036854775807ll-1;
const i64 I64_MAX=9223372036854775807ll;
typedef unsigned    long long u64;
const u64 U64_MIN=0;
const u64 U64_MAX=0xffffffffffffffffull;
#define MAX(x,y) x>y?x:y
#define MIN(x,y) x>y?y:x
#endif