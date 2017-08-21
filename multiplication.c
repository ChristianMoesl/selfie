void initLibrary();
void println();
void printInteger(int n);
void printHexadecimal(int n, int a);
void print(int* s);
int* malloc(int size);
int twoToThePowerOf(int n);
int leftShift(int n, int b);

int base = 65536;
int INT_MIN_;
int INT_MAX_;
int INT_OVERFLOW;
int OVERFLOW_YES = 1;
int OVERFLOW_NO = 0;

int mult(int a, int b) {
    int carry;
    int temp;
    int factorLhsHi;
    int factorLhsLo;
    int factorRhsHi;
    int factorRhsLo;
    int productHi;
    int productLo;
    int sign;

    INT_OVERFLOW = OVERFLOW_NO;

    if (a > 0) {
        if (b > 0) {
        if (a > INT_MAX_ / b)
            INT_OVERFLOW = OVERFLOW_YES;
        } else {
        if (b < INT_MIN_ / a)
            INT_OVERFLOW = OVERFLOW_YES;
        }
    } else {
        if (b > 0) {
        if (a < INT_MIN_ / b)
            INT_OVERFLOW = OVERFLOW_YES;
        } else {
        if (a != 0)
            if (b < INT_MAX_ / a)
            INT_OVERFLOW = OVERFLOW_YES;
        }
    }

    sign = 1;

    // Convert a into a positive big integer
    if (a < 0) {
        if (b >= 0)
            sign = -1;

        if (a == INT_MIN_) {
            factorLhsHi = 32768;
            factorLhsLo = 0;
        } else {
            a = a * (-1);

            factorLhsHi = a / base;
            factorLhsLo = a % base;
        }
    } else {
        factorLhsHi = a / base;
        factorLhsLo = a % base;
    }

    // Convert b into a positive big integer
    if (b < 0) {
        if (sign == 1)
            sign = -1;
        else 
            sign = 1;

        if (b == INT_MIN_) {
            factorRhsHi = 32768;
            factorRhsLo = 0;
        } else {
            b = b * (-1);

            factorRhsHi = b / base;
            factorRhsLo = b % base;
        }
    } else {
        factorRhsHi = b / base;
        factorRhsLo = b % base;
    }

    temp = factorLhsLo * factorRhsLo;
    carry = temp / base;
    productLo = temp % base;

    temp = factorLhsHi * factorRhsLo + carry;
    carry = temp / base;
    productHi = temp % base;

    temp = factorLhsLo * factorRhsHi;
    carry = temp / base;
    productHi = productHi + temp % base;

    return  (productLo + leftShift(productHi, 16)) * sign;
}

void init() {
    initLibrary();

    INT_MAX_ = (twoToThePowerOf(30) - 1) * 2 + 1;
    INT_MIN_ = -INT_MAX_ - 1;
}

int main(int argc, int* argv) {
    int n;
    int result;

    init();

    n = INT_MIN_;
    result = 1;

    while (n < INT_MAX_) {
        result = mult(n, 656851) == (n * 656851);

        if (result == 0) {
            print((int*)"Failed at: ");printInteger(n);println();
            while (1) {
                
            }
        }

        n = n + 1;
    }

    print((int*)"==============");println();

    return 0;
}