/* WARNING: Do not include any other libraries here,
 * otherwise you will get an error while running test.py
 * You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 *
 * Using printf will interfere with our script capturing the execution results.
 * At this point, you can only test correctness with ./btest.
 * After confirming everything is correct in ./btest, remove the printf
 * and run the complete tests with test.py.
 */

 /*
 * bitAnd - x & y using only ~ and |
 * Example: bitAnd(4, 5) = 4
 * Legal ops: ~ |
 * Max ops: 7
 * Difficulty: 1
 */
int bitAnd(int x, int y) {
    return ~((~x)|(~y));
}

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    return (~(x&y))&(~((~x)&(~y)));
}

/*
 * samesign - Determines if two integers have the same sign.
 *   0 is not positive, nor negative
 *   Example: samesign(0, 1) = 0, samesign(0, 0) = 1
 *            samesign(-4, -5) = 1, samesign(-4, 5) = 0
 *   Legal ops: >> << ! ^ && if else &
 *   Max ops: 12
 *   Difficulty: 2
 *
 * Parameters:
 *   x - The first integer.
 *   y - The second integer.
 *
 * Returns:
 *   1 if x and y have the same sign , 0 otherwise.
 */
int samesign(int x, int y) {
    if(!(!x)^(!y))
    {
        return !((x>>31)^(y>>31));
    }
    return 0;
}

/*
 * logtwo - Calculate the base-2 logarithm of a positive integer using bit
 *   shifting. (Think about bitCount)
 *   Note: You may assume that v > 0
 *   Example: logtwo(32) = 5
 *   Legal ops: > < >> << |
 *   Max ops: 25
 *   Difficulty: 4
 */
int logtwo(int v) {
    int count=0;
    int temp=((v>>16)>0)<<4;
    count=count|temp;
    v=v>>temp;
    temp=((v>>8)>0)<<3;
    count=count|temp;
    v=v>>temp;
    temp=((v>>4)>0)<<2;
    count=count|temp;
    v=v>>temp;
    temp=((v>>2)>0)<<1;
    count=count|temp;
    v=v>>temp;
    temp=(v>>1)>0;
    count=count|temp;
    return count;
}

/*
 *  byteSwap - swaps the nth byte and the mth byte
 *    Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *              byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *    Note: You may assume that 0 <= n <= 3, 0 <= m <= 3
 *    Legal ops: ! ~ & ^ | + << >>
 *    Max ops: 17
 *    Difficulty: 2
 */
int byteSwap(int x, int n, int m) {
    int count1=n<<3, count2=m<<3;
    int mask1=0xFF<<(count1);
    int mask2=0xFF<<(count2);
    int temp1=x&mask1;
    int temp2=x&mask2;
    int mask3=~(mask1|mask2);
    int temp3=x&mask3;
    temp1=temp1>>(count1)<<(count2)&mask2;
    temp2=temp2>>(count2)<<(count1)&mask1;
    return temp1|temp2|temp3;
}

/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
unsigned reverse(unsigned v) {
    unsigned result = 0;
    for(int i=32;i;i--)
    {
        result=(result<<1)|(v&1);
        v=v>>1;
    }
    return result;
}

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */
int logicalShift(int x, int n) {
    int mask=1<<31>>n<<1;
    return (x>>n)&(~mask);
}

/*
 * leftBitCount - returns count of number of consective 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
int leftBitCount(int x) {//先取反，再找前导0
    x=~x;
    int count=0;
    int temp;
    temp=!(x>>16)<<4;
    count=count|temp;
    x=x<<temp;

    temp=!(x>>24)<<3;
    count=count|temp;
    x=x<<temp;

    temp=!(x>>28)<<2;
    count=count|temp;
    x=x<<temp;

    temp=!(x>>30)<<1;
    count=count|temp;
    x=x<<temp;

    temp=!(x>>31);
    count=count|temp;
    x=x<<temp;

    return count+!x;
}

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned float_i2f(int x) {
    if(x==0) return 0;
    int sign=x&0x80000000;
    if(sign) x=-x;
    int temp=0;
    while(!(x&(1<<31)))
    {
        x=x<<1;
        temp+=1;
    }
    int dropped=x&0xFF;
    x=(x>>8)&0x7FFFFF;
    int guard=(dropped>>7)&1;
    int sticky=(dropped&0x7F)!=0;
    if(guard&(sticky|(x&1))) x+=1;
    if(x==(1<<23))
    {
    x=0;
    temp--;
    }
    temp=((31-temp)+127)<<23;
    return sign|temp|x;
}

/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: & >> << | if > < >= <= ! ~ else + ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatScale2(unsigned uf) {
    unsigned sign=uf&0x80000000;
    unsigned exp=(uf>>23)&0xFF;
    unsigned frac=uf&0x7FFFFF;
    if(exp==0xFF) return uf;
    if(exp==0) return uf+frac;
    if(exp==0xFE) return sign|0x7F800000;
    return uf+0x00800000;
}

/*
 * float64_f2i - Convert a 64-bit IEEE 754 floating-point number to a 32-bit signed integer.
 *   The conversion rounds towards zero.
 *   Note: Assumes IEEE 754 representation and standard two's complement integer format.
 *   Parameters:
 *     uf1 - The lower 32 bits of the 64-bit floating-point number.
 *     uf2 - The higher 32 bits of the 64-bit floating-point number.
 *   Returns:
 *     The converted integer value, or 0x80000000 on overflow, or 0 on underflow.
 *   Legal ops: >> << | & ~ ! + - > < >= <= if else
 *   Max ops: 60
 *   Difficulty: 3
 */
int float64_f2i(unsigned uf1, unsigned uf2) {
    unsigned sign=uf2&0x80000000;
    unsigned exp=(uf2>>20)&0x7FF;
    unsigned f2=uf2&0xFFFFF;
    unsigned f1=uf1;
    if(!exp) return 0;
    int e=exp-1023;
    if(e<0) return 0;
    if(e>=31) return 0x80000000;

    unsigned shift=52-e;
    f2=(1<<20)|f2;
    unsigned result;
    if(shift>=32) result=f2>>(shift-32);
    else result=(f2<<(32-shift))|(f1>>shift);
    if(sign) return -result;
    return result;
}

/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: < > <= >= << >> + - & | ~ ! if else &&
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatPower2(int x) {
    if(x>127) return 0x7F800000;
    if(x<-149) return 0;
    if(x>=-126) return (x+127)<<23;
    return 1<<(x+149);
}
