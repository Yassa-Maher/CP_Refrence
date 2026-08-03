// Extended Euclidean Algorithm
// Finds gcd(a, b) and also computes two integers x and y
// such that:
//      a * x + b * y = gcd(a, b)
// These coefficients are useful for finding modular inverses
// and solving linear Diophantine equations.

int extendedGCD(int a, int b, int &x, int &y) {

    // Base case:
    // If b becomes 0, then gcd(a, 0) = a.
    // The equation becomes:
    //      a * 1 + 0 * 0 = a
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }

    // Variables to store the coefficients returned
    // from the recursive call.
    int x1, y1;

    // Solve the smaller problem:
    //      b * x1 + (a % b) * y1 = gcd
    int gcd = extendedGCD(b, a % b, x1, y1);

    // Update the coefficients for the current equation
    // using the values obtained from recursion.
    x = y1;
    y = x1 - y1 * (a / b);

    // Return the greatest common divisor.
    return gcd;
}


*************************************************************************************************8888


// version with no comments

int extendedGCD(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1;
    int gcd = extendedGCD(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return gcd;
}
